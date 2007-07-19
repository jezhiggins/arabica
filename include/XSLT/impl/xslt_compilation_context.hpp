#ifndef ARABICA_XSLT_COMPILATION_CONTEXT
#define ARABICA_XSLT_COMPILATION_CONTEXT

#include <SAX/XMLReader.h>
#include <SAX/helpers/DefaultHandler.h>
#include <XPath/XPath.hpp>
#include <stack>

namespace Arabica
{
namespace XSLT
{

class Stylesheet;
class ItemContainer;

class CompilationContext
{
public:
  CompilationContext(SAX::NamespaceTracker<std::string>& parser,
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

  SAX::basic_XMLReader<std::string>& parser() const { return parser_; }
  const Arabica::XPath::XPath<std::string>& xpath() const { return xpath_; }
  Stylesheet& stylesheet() const { return stylesheet_; }

  std::pair<std::string, std::string> processQName(const std::string& qName) const
  {
    return parser_.process(qName);
  } // processQName

  std::string makeAbsolute(const std::string& href) const
  {
    SAX::XMLBaseTracker<std::string>* tracker = static_cast<SAX::XMLBaseTracker<std::string>*>(parser_.getParent());
    return tracker->makeAbsolute(href);
  } // makeAbsolute

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

  SAX::DefaultHandler& parentHandler() const
  {
    return *handlerStack_.top();
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

  SAX::NamespaceTracker<std::string>& parser_;
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

