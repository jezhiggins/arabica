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

class CompilationContext :
    private Arabica::XPath::FunctionResolver<std::string, Arabica::default_string_adaptor<std::string> >,
    private Arabica::XPath::NamespaceContext<std::string, Arabica::default_string_adaptor<std::string> >,
    private Arabica::XPath::DefaultVariableCompileTimeResolver<std::string, Arabica::default_string_adaptor<std::string> >
{
private:
  typedef Arabica::XPath::DefaultVariableCompileTimeResolver<std::string, Arabica::default_string_adaptor<std::string> > CTVariableResolverT;

public:
  CompilationContext(StylesheetParser& parser,
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

  void root(SAX::DefaultHandler<std::string>& root)
  {
    handlerStack_.push(&root);
  } // root

  StylesheetParser& parser() const { return parser_; }
  Arabica::XPath::XPathExpressionPtr<std::string> xpath_expression(const std::string& expr) const { return xpath_.compile_expr(expr); } 
  Arabica::XPath::XPathExpressionPtr<std::string> xpath_expression_no_variables(const std::string& expr) const
  {
    Disallow variables(variables_allowed_);
    return xpath_expression(expr);
  } // xpath_expression_no_variables
  std::vector<Arabica::XPath::MatchExpr<std::string> > xpath_match(const std::string& match) const 
  {
    Disallow current(current_allowed_);
    return xpath_.compile_match(match); 
  } // xpath_match
  std::vector<Arabica::XPath::MatchExpr<std::string> > xpath_match_no_variables(const std::string& match) const
  {
    Disallow variables(variables_allowed_);
    return xpath_match(match);
  } // xpath_match_no_variables

  Arabica::XPath::XPathExpressionPtr<std::string> xpath_attribute_value_template(const std::string& expr) const { return xpath_.compile_attribute_value_template(expr); } 
  CompiledStylesheet& stylesheet() const { return stylesheet_; }

  XML::QualifiedName<std::string> processElementQName(const std::string& qName) const
  {
    return parser_.processElementQName(qName);
  } // processElementQName

  XML::QualifiedName<std::string> processInternalQName(const std::string& qName) const
  {
    return parser_.processInternalQName(qName);
  } // processInternalQName

  std::string makeAbsolute(const std::string& href) const
  {
    return parser_.makeAbsolute(href);
  } // makeAbsolute

  std::string setBase(const std::string& href) const
  {
    return parser_.setBase(href);
  } // setBase

  std::string currentBase() const
  {
    return parser_.currentBase();
  } // currentBase

  void push(ItemContainer* parent,
            SAX::DefaultHandler<std::string>* newHandler,
            const std::string& namespaceURI,
            const std::string& localName,
            const std::string& qName,
            const SAX::Attributes<std::string>& atts)
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

  SAX::ContentHandler<std::string>& parentHandler() const
  {
    parser_.setContentHandler(*handlerStack_.top());
    return parser_.contentHandler();
  } // parentHandler

  std::map<std::string, std::string> inScopeNamespaces() const
  {
    return parser_.inScopeNamespaces();
  } // inScopeNamespaces

  void addNamespaceAlias(const std::string& stylesheet_namespace,
			 const std::string& result_prefix,
			 const std::string& result_namespace)
  { 
    namespaceRemap_[stylesheet_namespace] = std::make_pair(result_prefix, result_namespace);
  } // addNamespaceAlias

  bool isRemapped(const std::string& namespaceURI) const
  {
    return namespaceRemap_.find(namespaceURI) != namespaceRemap_.end();
  } // isRemapped

  const std::pair<std::string, std::string>& remappedNamespace(const std::string& namespaceURI) 
  {
    return namespaceRemap_[namespaceURI];
  } // remappedNamespace
  
  std::string autoNamespacePrefix() const
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
  virtual Arabica::XPath::XPathExpression_impl<std::string, Arabica::default_string_adaptor<std::string> >* 
    compileVariable(const std::string& namespace_uri, const std::string& name) const 
  {
    if(!variables_allowed_)
      return 0;
    return CTVariableResolverT::compileVariable(namespace_uri, name);
  } // compileVariable

  // FunctionResolver 
  virtual Arabica::XPath::XPathFunction<std::string>* resolveFunction(
                                         const std::string& namespace_uri, 
                                         const std::string& name,
                                         const std::vector<Arabica::XPath::XPathExpression<std::string> >& argExprs) const
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
      std::vector<std::pair<std::string, std::string> > dummy;
      return new ElementAvailableFunction(dummy, parser_.inScopeNamespaces(), argExprs);
    } 
    // function-available
    if(name == "function-available")
      return new FunctionAvailableFunction(validNames(), parser_.inScopeNamespaces(), argExprs);

    return 0;
  } // resolveFunction

  virtual std::vector<std::pair<std::string, std::string> > validNames() const 
  {
    static const char* functionNames[] = { "document", "key", /* format-number, */ "current",
					   /* unparsed-entity-uri, */ "generate-id", "system-property", 
					   /* element-available, */ "function-available", 0 };

    std::vector<std::pair<std::string,std::string> > names;

    for(int i = 0; functionNames[i] != 0; ++i)
      names.push_back(std::make_pair("", functionNames[i]));

    return names;
  } // validNames

  // NamespaceContext 
  virtual std::string namespaceURI(const std::string& prefix) const
  {
    return parser_.namespaceURI(prefix);
  } // namespaceURI

  typedef std::pair<std::string, std::string> Namespace;

  StylesheetParser& parser_;
  CompiledStylesheet& stylesheet_;
  mutable int autoNs_;
  mutable bool current_allowed_;
  mutable bool variables_allowed_;
  Precedence precedence_;
  Arabica::XPath::XPath<std::string> xpath_;
  std::stack<SAX::DefaultHandler<std::string>*> handlerStack_;
  std::stack<ItemContainer*> parentStack_;
  std::map<std::string, Namespace> namespaceRemap_;

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

