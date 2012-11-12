#ifndef ARABICA_XSLT_NAMESPACE_ALIAS_HANDLER_HPP
#define ARABICA_XSLT_NAMESPACE_ALIAS_HANDLER_HPP

#include <XML/XMLCharacterClasses.hpp>

#include "xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class NamespaceAliasHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;

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
      static const ValueRule<string_type> rules[] = { { SC::stylesheet_prefix, true, 0, 0 },
                                                      { SC::result_prefix, true, 0, 0 },
                                                      { string_adaptor::empty_string(), false, 0, 0 } };

      std::map<string_type, string_type> attrs = gatherAttributes(qName, atts, rules);
      string_type stylesheet_prefix = attrs[SC::stylesheet_prefix];
      string_type result_prefix = attrs[SC::result_prefix];

      if(stylesheet_prefix == SC::hash_default) 
        stylesheet_prefix = string_adaptor::empty_string();
      if(result_prefix == SC::hash_default)
        result_prefix = string_adaptor::empty_string();

      std::map<string_type, string_type> namespaces = context_.inScopeNamespaces();
      if((namespaces.find(stylesheet_prefix) == namespaces.end()) && 
         (!stylesheet_prefix.empty()))
        throw SAX::SAXException(string_adaptor::asStdString(SC::namespace_alias) + " " + string_adaptor::asStdString(stylesheet_prefix) + " is not a declared namespace prefix");
      if((namespaces.find(result_prefix) == namespaces.end()) &&
         (!result_prefix.empty()))
        throw SAX::SAXException(string_adaptor::asStdString(SC::namespace_alias) + " " + string_adaptor::asStdString(result_prefix) + " is not a declared namespace prefix");

      context_.addNamespaceAlias(namespaces[stylesheet_prefix], result_prefix, namespaces[result_prefix]);
      return;
    } // if(!done_)

    throw SAX::SAXException(string_adaptor::asStdString(qName) + " can not contain elements");
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData<string_type, string_adaptor>(ch, SC::namespace_alias);
  } // characters

private:
  CompilationContext<string_type, string_adaptor>& context_;
  bool done_;
}; // class NamespaceAliasHandler

} //namespace XSLT
} //namespace Arabica

#endif 

