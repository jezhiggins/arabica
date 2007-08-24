#ifndef ARABICA_XSLT_COMPILATION_CONTEXT
#define ARABICA_XSLT_COMPILATION_CONTEXT

#include <SAX/XMLReader.h>
#include <SAX/helpers/DefaultHandler.h>
#include <XPath/XPath.hpp>
#include <stack>

#include "xslt_stylesheet_parser.hpp"

namespace Arabica
{
namespace XSLT
{

class Stylesheet;
class ItemContainer;

class CompilationContext
{
public:
  CompilationContext(StylesheetParser& parser,
                     Arabica::XPath::XPath<std::string>& xpathCompiler,
                     Stylesheet& stylesheet) :
    parser_(parser),
    xpath_(xpathCompiler),
    stylesheet_(stylesheet),
    autoNs_(1)
  {
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

  void root(SAX::DefaultHandler& root)
  {
    handlerStack_.push(&root);
  } // root

  StylesheetParser& parser() const { return parser_; }
  const Arabica::XPath::XPath<std::string>& xpath() const { return xpath_; }
  Stylesheet& stylesheet() const { return stylesheet_; }

  std::pair<std::string, std::string> processQName(const std::string& qName) const
  {
    return parser_.processQName(qName);
  } // processQName

  std::string makeAbsolute(const std::string& href) const
  {
    return parser_.makeAbsolute(href);
  } // makeAbsolute

  std::string setBase(const std::string& href) const
  {
    return parser_.setBase(href);
  } // setBase

  void push(ItemContainer* parent,
            SAX::DefaultHandler* newHandler,
            const std::string& namespaceURI,
            const std::string& localName,
            const std::string& qName,
            const SAX::Attributes& atts)
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

  SAX::ContentHandler& parentHandler() const
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


private:
  typedef std::pair<std::string, std::string> Namespace;

  StylesheetParser& parser_;
  const Arabica::XPath::XPath<std::string>& xpath_;
  Stylesheet& stylesheet_;
  std::stack<SAX::DefaultHandler*> handlerStack_;
  std::stack<ItemContainer*> parentStack_;
  std::map<std::string, Namespace> namespaceRemap_;

  CompilationContext(const CompilationContext&);
  mutable int autoNs_;
}; // class CompilationContext

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_COMPILATION_CONTEXT

