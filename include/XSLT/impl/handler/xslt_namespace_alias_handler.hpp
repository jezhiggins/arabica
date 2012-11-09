#ifndef ARABICA_XSLT_NAMESPACE_ALIAS_HANDLER_HPP
#define ARABICA_XSLT_NAMESPACE_ALIAS_HANDLER_HPP

#include <XML/XMLCharacterClasses.hpp>

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class NamespaceAliasHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
public:
  NamespaceAliasHandler(CompilationContext<string_type, string_adaptor>& context) : 
    context_(context),
    done_(false)
  {
  } // NamespaceAliasHandler

  virtual void startElement(const string_type& /* namespaceURI */,
                            const string_type& /* localName */,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(!done_)
    {
      static const ValueRule rules[] = { { "stylesheet-prefix", true, 0, 0 },
                                         { "result-prefix", true, 0, 0 },
                                         { 0, false, 0, 0 } };

      std::map<string_type, string_type> attrs = gatherAttributes(qName, atts, rules);
      string_type stylesheet_prefix = attrs["stylesheet-prefix"];
      string_type result_prefix = attrs["result-prefix"];

      if(stylesheet_prefix == "#default") 
        stylesheet_prefix = "";
      if(result_prefix == "#default")
        result_prefix = "";

      std::map<string_type, string_type> namespaces = context_.inScopeNamespaces();
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

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData<string_type>(ch, "xsl:namespace-alias");
  } // characters

private:
  CompilationContext<string_type, string_adaptor>& context_;
  bool done_;
}; // class NamespaceAliasHandler

} //namespace XSLT
} //namespace Arabica

#endif 

