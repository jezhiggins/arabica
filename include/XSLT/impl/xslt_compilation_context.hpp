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
    private Arabica::XPath::FunctionResolver<std::string>,
    private Arabica::XPath::NamespaceContext<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  CompilationContext(StylesheetParser& parser,
                     CompiledStylesheet& stylesheet) :
    parser_(parser),
    stylesheet_(stylesheet),
    autoNs_(1),
    current_allowed_(false)
  {
    xpath_.setNamespaceContext(*this);
    xpath_.setFunctionResolver(*this);
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
  std::vector<Arabica::XPath::MatchExpr<std::string> > xpath_match(const std::string& match) const 
  {
    DisallowCurrent guard(current_allowed_);
    return xpath_.compile_match(match); 
  } // xpath_match
  Arabica::XPath::XPathExpressionPtr<std::string> xpath_attribute_value_template(const std::string& expr) const { return xpath_.compile_attribute_value_template(expr); } 
  CompiledStylesheet& stylesheet() const { return stylesheet_; }

  std::pair<std::string, std::string> processInternalQName(const std::string& qName) const
  {
    if(!Arabica::XML::is_qname(qName))
      throw SAX::SAXException("Bad name : " + qName);
    // 2.4 The default namespace is not used for unprefixed names.
    if(qName.find(':') == std::string::npos)
      return std::make_pair("", qName);
    return parser_.processQName(qName);
  } // processInternalQName

  std::string makeAbsolute(const std::string& href) const
  {
    return parser_.makeAbsolute(href);
  } // makeAbsolute

  std::string setBase(const std::string& href) const
  {
    return parser_.setBase(href);
  } // setBase

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
    newHandler->startElement(namespaceURI, qName, localName, atts);
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

  void push_import_precedence()
  {
    precedenceStack_.push();
  } // push_import_precedence

  void pop_import_precedence()
  {
    precedenceStack_.pop();
  } // pop_import_precedence

  // void set_precedence(const Prcedence& prec)

  // const Precedence& next_precedence()

  const Precedence& precedence() const
  {
    return precedenceStack_.top();
  } // precedence

private:
  // FunctionResolver 
  virtual Arabica::XPath::XPathFunction<std::string>* resolveFunction(
                                         const std::string& namespace_uri, 
                                         const std::string& name,
                                         const std::vector<Arabica::XPath::XPathExpression<std::string> >& argExprs) const
  {
    if(!namespace_uri.empty())
      return 0;

    // document
    if(name == "document")
      return new DocumentFunction(parser_.currentBase(), argExprs);
    // key
    // format-number
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
    // function-available
    
    return 0;
  } // resolveFunction

  // NamespaceContext 
  virtual std::string namespaceURI(const std::string& prefix) const
  {
    return parser_.namespaceURI(prefix);
  } // namespaceURI

  typedef std::pair<std::string, std::string> Namespace;

  StylesheetParser& parser_;
  Arabica::XPath::XPath<std::string> xpath_;
  CompiledStylesheet& stylesheet_;
  std::stack<SAX::DefaultHandler<std::string>*> handlerStack_;
  std::stack<ItemContainer*> parentStack_;
  std::map<std::string, Namespace> namespaceRemap_;
  PrecedenceStack precedenceStack_;

  CompilationContext(const CompilationContext&);
  mutable int autoNs_;
  mutable bool current_allowed_;

  class DisallowCurrent
  { 
    public:
      DisallowCurrent(bool& allow) : allow_(allow) { allow_ = false; }
      ~DisallowCurrent() { allow_ = true; }
    private:
      bool& allow_;
  }; // DisallowCurrent 
}; // class CompilationContext

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_COMPILATION_CONTEXT

