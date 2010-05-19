#ifndef ARABICA_XSLT_NAMESPACE_ALIAS_HANDLER_HPP
#define ARABICA_XSLT_NAMESPACE_ALIAS_HANDLER_HPP

#include <XML/XMLCharacterClasses.hpp>

namespace Arabica
{
namespace XSLT
{

class NamespaceAliasHandler : public SAX::DefaultHandler<std::string>
{
public:
  NamespaceAliasHandler(CompilationContext& context) : 
    context_(context),
    done_(false)
  {
  } // NamespaceAliasHandler

  virtual void startElement(const std::string& /* namespaceURI */,
                            const std::string& /* localName */,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(!done_)
    {
      static const ValueRule rules[] = { { "stylesheet-prefix", true, 0, 0 },
                                         { "result-prefix", true, 0, 0 },
                                         { 0, false, 0, 0 } };

      std::map<std::string, std::string> attrs = gatherAttributes(qName, atts, rules);
      std::string stylesheet_prefix = attrs["stylesheet-prefix"];
      std::string result_prefix = attrs["result-prefix"];

      if(stylesheet_prefix == "#default") 
        stylesheet_prefix = "";
      if(result_prefix == "#default")
        result_prefix = "";

      std::map<std::string, std::string> namespaces = context_.inScopeNamespaces();
      if((namespaces.find(stylesheet_prefix) == namespaces.end()) && 
         (!stylesheet_prefix.empty()))
        throw SAX::SAXException("xslt:namespace-alias " + stylesheet_prefix + " is not a declared namespace prefix");
      if((namespaces.find(result_prefix) == namespaces.end()) &&
         (!result_prefix.empty()))
        throw SAX::SAXException("xslt:namespace-alias " + result_prefix + " is not a declared namespace prefix");

      context_.addNamespaceAlias(namespaces[stylesheet_prefix], result_prefix, namespaces[result_prefix]);
      return;
    } // if(!done_)

    throw SAX::SAXException(qName + " can not contain elements");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    verifyNoCharacterData(ch, "xsl:namespace-alias");
  } // characters

private:
  CompilationContext& context_;
  bool done_;
}; // class NamespaceAliasHandler

} //namespace XSLT
} //namespace Arabica

#endif 

