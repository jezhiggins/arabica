#ifndef ARABICA_XSLT_COMPILATION_CONTEXT
#define ARABICA_XSLT_COMPILATION_CONTEXT

#include <SAX/XMLReader.hpp>
#include <SAX/helpers/DefaultHandler.hpp>
#include <XML/strings.hpp>
#include <XPath/XPath.hpp>
#include <stack>

#include "xslt_stylesheet_parser.hpp"
#include "xslt_functions.hpp"

namespace Arabica
{
namespace XSLT
{
class CompiledStylesheet;
class ItemContainer;

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class CompilationContext :
    private Arabica::XPath::FunctionResolver<string_type, string_adaptor>,
    private Arabica::XPath::NamespaceContext<string_type, string_adaptor>,
    private Arabica::XPath::DefaultVariableCompileTimeResolver<string_type, string_adaptor>
{
private:
  typedef Arabica::XPath::DefaultVariableCompileTimeResolver<string_type, string_adaptor> CTVariableResolverT;

public:
  typedef StylesheetParser<string_type, string_adaptor> StylesheetParserT;
  typedef SAX::DefaultHandler<string_type, string_adaptor> DefaultHandlerT;
  typedef SAX::ContentHandler<string_type, string_adaptor> ContentHandlerT;
  typedef SAX::Attributes<string_type, string_adaptor> AttributesT;
  typedef Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> XPathExpressionPtrT;
  typedef Arabica::XPath::MatchExpr<string_type, string_adaptor> MatchExprT;
  typedef XML::QualifiedName<string_type, string_adaptor> QualifiedNameT;


  CompilationContext(StylesheetParserT& parser,
                     CompiledStylesheet& stylesheet) :
    parser_(parser),
    stylesheet_(stylesheet),
    autoNs_(1),
    current_allowed_(false),
    variables_allowed_(true),    
    precedence_(Precedence::InitialPrecedence())
  {
    xpath_.setNamespaceContext(*this);
    xpath_.setFunctionResolver(*this);
    xpath_.setVariableCompileTimeResolver(*this);
  } // CompilationContext

  ~CompilationContext()
  {
    // delete any left over - will only be the case if unwinding
    while(handlerStack_.size() > 1)
    {
      delete handlerStack_.top();
      handlerStack_.pop();
    } // while ...
  } // ~CompilationContext

  void root(DefaultHandlerT& root)
  {
    handlerStack_.push(&root);
  } // root

  StylesheetParserT& parser() const { return parser_; }
  XPathExpressionPtrT xpath_expression(const string_type& expr) const { return xpath_.compile_expr(expr); } 
  XPathExpressionPtrT xpath_expression_no_variables(const string_type& expr) const
  {
    Disallow variables(variables_allowed_);
    return xpath_expression(expr);
  } // xpath_expression_no_variables
  std::vector<MatchExprT> xpath_match(const string_type& match) const 
  {
    Disallow current(current_allowed_);
    return xpath_.compile_match(match); 
  } // xpath_match
  std::vector<Arabica::XPath::MatchExpr<string_type> > xpath_match_no_variables(const string_type& match) const
  {
    Disallow variables(variables_allowed_);
    return xpath_match(match);
  } // xpath_match_no_variables

  XPathExpressionPtrT xpath_attribute_value_template(const string_type& expr) const { return xpath_.compile_attribute_value_template(expr); } 
  CompiledStylesheet& stylesheet() const { return stylesheet_; }

  QualifiedNameT processElementQName(const string_type& qName) const
  {
    return parser_.processElementQName(qName);
  } // processElementQName

  QualifiedNameT processInternalQName(const string_type& qName) const
  {
    return parser_.processInternalQName(qName);
  } // processInternalQName

  string_type makeAbsolute(const string_type& href) const
  {
    return parser_.makeAbsolute(href);
  } // makeAbsolute

  string_type setBase(const string_type& href) const
  {
    return parser_.setBase(href);
  } // setBase

  string_type currentBase() const
  {
    return parser_.currentBase();
  } // currentBase

  void push(ItemContainer* parent,
            DefaultHandlerT* newHandler,
            const string_type& namespaceURI,
            const string_type& localName,
            const string_type& qName,
            const AttributesT& atts)
  {
    parentStack_.push(parent);
    handlerStack_.push(newHandler);
    parser_.setContentHandler(*newHandler);
    newHandler->startElement(namespaceURI, localName, qName, atts);
  } // push

  void pop()
  {
    parentStack_.pop();
    delete handlerStack_.top();
    handlerStack_.pop();
    parser_.setContentHandler(*handlerStack_.top());
  } // pop

  ItemContainer& parentContainer() const
  { 
    return *parentStack_.top();
  } // parentContainer

  ContentHandlerT& parentHandler() const
  {
    parser_.setContentHandler(*handlerStack_.top());
    return parser_.contentHandler();
  } // parentHandler

  std::map<string_type, string_type> inScopeNamespaces() const
  {
    return parser_.inScopeNamespaces();
  } // inScopeNamespaces

  void addNamespaceAlias(const string_type& stylesheet_namespace,
			 const string_type& result_prefix,
			 const string_type& result_namespace)
  { 
    namespaceRemap_[stylesheet_namespace] = std::make_pair(result_prefix, result_namespace);
  } // addNamespaceAlias

  bool isRemapped(const string_type& namespaceURI) const
  {
    return namespaceRemap_.find(namespaceURI) != namespaceRemap_.end();
  } // isRemapped

  const std::pair<string_type, string_type>& remappedNamespace(const string_type& namespaceURI) 
  {
    return namespaceRemap_[namespaceURI];
  } // remappedNamespace
  
  string_type autoNamespacePrefix() const
  {
    std::ostringstream ss;
    ss << "auto-ns" << autoNs_++;
    return ss.str();
  } // autoNamespacePrefix

  void set_precedence(const Precedence& prec)
  {
    precedence_ = prec;
  } // set_precedence

  Precedence next_precedence()
  {
    return precedence_.next_generation();
  } // next_precedence

  const Precedence& precedence() const
  {
    return precedence_;
  } // precedence

private:
  virtual Arabica::XPath::XPathExpression_impl<string_type, Arabica::default_string_adaptor<string_type> >* 
    compileVariable(const string_type& namespace_uri, const string_type& name) const 
  {
    if(!variables_allowed_)
      return 0;
    return CTVariableResolverT::compileVariable(namespace_uri, name);
  } // compileVariable

  // FunctionResolver 
  virtual Arabica::XPath::XPathFunction<string_type>* resolveFunction(
                                         const string_type& namespace_uri, 
                                         const string_type& name,
                                         const std::vector<Arabica::XPath::XPathExpression<string_type> >& argExprs) const
  {
    if(!namespace_uri.empty())
      return new UndefinedFunction(namespace_uri, name, argExprs);

    // document
    if(name == "document")
      return new DocumentFunction(parser_.currentBase(), argExprs);
    // key
    if(name == "key")
      return new KeyFunction(stylesheet_.keys(), parser_.inScopeNamespaces(), argExprs);
    // format-number
    // current
    if((name == "current") && (current_allowed_))
      return new CurrentFunction(argExprs);
    // unparsed-entity-uri
    //if(name == "unparsed-entity-uri")
    //  return new UnparsedEntityUriFunction(argExprs);
    // generate-id
    if(name == "generate-id")
      return new GenerateIdFunction(argExprs);
    if(name == "system-property")
      return new SystemPropertyFunction(argExprs);
    // element-available
    if(name == "element-available")
    {
      std::vector<std::pair<string_type, string_type> > dummy;
      return new ElementAvailableFunction(dummy, parser_.inScopeNamespaces(), argExprs);
    } 
    // function-available
    if(name == "function-available")
      return new FunctionAvailableFunction(validNames(), parser_.inScopeNamespaces(), argExprs);

    return 0;
  } // resolveFunction

  virtual std::vector<std::pair<string_type, string_type> > validNames() const 
  {
    static const char* functionNames[] = { "document", "key", /* format-number, */ "current",
					   /* unparsed-entity-uri, */ "generate-id", "system-property", 
					   /* element-available, */ "function-available", 0 };

    std::vector<std::pair<string_type,string_type> > names;

    for(int i = 0; functionNames[i] != 0; ++i)
      names.push_back(std::make_pair("", functionNames[i]));

    return names;
  } // validNames

  // NamespaceContext 
  virtual string_type namespaceURI(const string_type& prefix) const
  {
    return parser_.namespaceURI(prefix);
  } // namespaceURI

  typedef std::pair<string_type, string_type> Namespace;

  StylesheetParser<string_type, string_adaptor>& parser_;
  CompiledStylesheet& stylesheet_;
  mutable int autoNs_;
  mutable bool current_allowed_;
  mutable bool variables_allowed_;
  Precedence precedence_;
  Arabica::XPath::XPath<string_type> xpath_;
  std::stack<SAX::DefaultHandler<string_type>*> handlerStack_;
  std::stack<ItemContainer*> parentStack_;
  std::map<string_type, Namespace> namespaceRemap_;

  CompilationContext(const CompilationContext&);

  class Disallow
  { 
    public:
      Disallow(bool& allow) : allow_(allow) { allow_ = false; }
      ~Disallow() { allow_ = true; }
    private:
      bool& allow_;
  }; // DisallowCurrent 
}; // class CompilationContext

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_COMPILATION_CONTEXT

