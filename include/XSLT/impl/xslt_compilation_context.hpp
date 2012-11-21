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
template<class string_type, class string_adaptor> class CompiledStylesheet;
template<class string_type, class string_adaptor> class ItemContainer;

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class CompilationContext :
    private Arabica::XPath::FunctionResolver<string_type, string_adaptor>,
    private Arabica::XPath::NamespaceContext<string_type, string_adaptor>,
    private Arabica::XPath::DefaultVariableCompileTimeResolver<string_type, string_adaptor>
{
private:
  typedef Arabica::XPath::DefaultVariableCompileTimeResolver<string_type, string_adaptor> CTVariableResolverT;
  typedef StylesheetConstant<string_type, string_adaptor> SC;

public:
  typedef StylesheetParser<string_type, string_adaptor> StylesheetParserT;
  typedef CompiledStylesheet<string_type, string_adaptor> CompiledStylesheetT;
  typedef SAX::DefaultHandler<string_type, string_adaptor> DefaultHandlerT;
  typedef SAX::ContentHandler<string_type, string_adaptor> ContentHandlerT;
  typedef SAX::Attributes<string_type, string_adaptor> AttributesT;
  typedef Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> XPathExpressionPtrT;
  typedef Arabica::XPath::MatchExpr<string_type, string_adaptor> MatchExprT;
  typedef XML::QualifiedName<string_type, string_adaptor> QualifiedNameT;


  CompilationContext(StylesheetParserT& parser,
                     CompiledStylesheetT& stylesheet) :
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
  std::vector<Arabica::XPath::MatchExpr<string_type, string_adaptor> > xpath_match_no_variables(const string_type& match) const
  {
    Disallow variables(variables_allowed_);
    return xpath_match(match);
  } // xpath_match_no_variables

  XPathExpressionPtrT xpath_attribute_value_template(const string_type& expr) const { return xpath_.compile_attribute_value_template(expr); } 
  CompiledStylesheetT& stylesheet() const { return stylesheet_; }

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

  void push(ItemContainer<string_type, string_adaptor>* parent,
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

  ItemContainer<string_type, string_adaptor>& parentContainer() const
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
    std::basic_ostringstream<typename string_adaptor::value_type> ss;
    ss << SC::auto_ns << autoNs_++;
    return string_adaptor::construct(ss.str());
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
  virtual Arabica::XPath::XPathExpression_impl<string_type, string_adaptor>* 
    compileVariable(const string_type& namespace_uri, const string_type& name) const 
  {
    if(!variables_allowed_)
      return 0;
    return CTVariableResolverT::compileVariable(namespace_uri, name);
  } // compileVariable

  // FunctionResolver 
  virtual Arabica::XPath::XPathFunction<string_type, string_adaptor>* resolveFunction(
                                         const string_type& namespace_uri, 
                                         const string_type& name,
                                         const std::vector<Arabica::XPath::XPathExpression<string_type, string_adaptor> >& argExprs) const
  {
    if(!string_adaptor::empty(namespace_uri))
      return new UndefinedFunction<string_type, string_adaptor>(namespace_uri, name, argExprs);

    // document
    if(name == DocumentFunction<string_type, string_adaptor>::name())
      return new DocumentFunction<string_type, string_adaptor>(parser_.currentBase(), argExprs);
    // key
    if(name == KeyFunction<string_type, string_adaptor>::name())
      return new KeyFunction<string_type, string_adaptor>(stylesheet_.keys(), parser_.inScopeNamespaces(), argExprs);
    // format-number
    // current
    if((name == CurrentFunction<string_type, string_adaptor>::name()) && (current_allowed_))
      return new CurrentFunction<string_type, string_adaptor>(argExprs);
    // unparsed-entity-uri
    //if(name == UnparsedEntityUriFunction<string_type, string_adaptor>::name())
    //  return new UnparsedEntityUriFunction<string_type, string_adaptor>(argExprs);
    // generate-id
    if(name == GenerateIdFunction<string_type, string_adaptor>::name())
      return new GenerateIdFunction<string_type, string_adaptor>(argExprs);
    if(name == SystemPropertyFunction<string_type, string_adaptor>::name())
      return new SystemPropertyFunction<string_type, string_adaptor>(argExprs);
    // element-available
    if(name == ElementAvailableFunction<string_type, string_adaptor>::name())
    {
      std::vector<std::pair<string_type, string_type> > dummy;
      return new ElementAvailableFunction<string_type, string_adaptor>(dummy, parser_.inScopeNamespaces(), argExprs);
    } 
    // function-available
    if(name == FunctionAvailableFunction<string_type, string_adaptor>::name())
      return new FunctionAvailableFunction<string_type, string_adaptor>(validNames(), parser_.inScopeNamespaces(), argExprs);

    return 0;
  } // resolveFunction

  virtual std::vector<std::pair<string_type, string_type> > validNames() const 
  {
    static string_type functionNames[] = { DocumentFunction<string_type, string_adaptor>::name(), 
                                           KeyFunction<string_type, string_adaptor>::name(), 
                                           /* format-number, */ 
                                           CurrentFunction<string_type, string_adaptor>::name(),
					                                 UnparsedEntityUriFunction<string_type, string_adaptor>::name(), 
                                           GenerateIdFunction<string_type, string_adaptor>::name(), 
                                           SystemPropertyFunction<string_type, string_adaptor>::name(), 
					                                 ElementAvailableFunction<string_type, string_adaptor>::name(),
                                           FunctionAvailableFunction<string_type, string_adaptor>::name(), 
                                           string_adaptor::empty_string() };

    std::vector<std::pair<string_type,string_type> > names;

    for(int i = 0; functionNames[i] != string_adaptor::empty_string(); ++i)
      names.push_back(std::make_pair(string_adaptor::empty_string(), functionNames[i]));

    return names;
  } // validNames

  // NamespaceContext 
  virtual string_type namespaceURI(const string_type& prefix) const
  {
    return parser_.namespaceURI(prefix);
  } // namespaceURI

  typedef std::pair<string_type, string_type> Namespace;

  StylesheetParser<string_type, string_adaptor>& parser_;
  CompiledStylesheetT& stylesheet_;
  mutable int autoNs_;
  mutable bool current_allowed_;
  mutable bool variables_allowed_;
  Precedence precedence_;
  Arabica::XPath::XPath<string_type, string_adaptor> xpath_;
  std::stack<SAX::DefaultHandler<string_type, string_adaptor>*> handlerStack_;
  std::stack<ItemContainer<string_type, string_adaptor>*> parentStack_;
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

