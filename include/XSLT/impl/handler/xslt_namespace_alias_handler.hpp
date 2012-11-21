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
  typedef AttributeValidators<string_type, string_adaptor> AV;

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
      static const AV rules = AV::rule(SC::stylesheet_prefix, true)
                                 .rule(SC::result_prefix, true);

      std::map<string_type, string_type> attrs = rules.gather(qName, atts);
      string_type stylesheet_prefix = attrs[SC::stylesheet_prefix];
      string_type result_prefix = attrs[SC::result_prefix];

      if(stylesheet_prefix == SC::hash_default) 
        stylesheet_prefix = string_adaptor::empty_string();
      if(result_prefix == SC::hash_default)
        result_prefix = string_adaptor::empty_string();

      std::map<string_type, string_type> namespaces = context_.inScopeNamespaces();
      if((namespaces.find(stylesheet_prefix) == namespaces.end()) && 
         (!string_adaptor::empty(stylesheet_prefix)))
        throw SAX::SAXException(string_adaptor::asStdString(SC::namespace_alias) + " " + string_adaptor::asStdString(stylesheet_prefix) + " is not a declared namespace prefix");
      if((namespaces.find(result_prefix) == namespaces.end()) &&
         (!string_adaptor::empty(result_prefix)))
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

