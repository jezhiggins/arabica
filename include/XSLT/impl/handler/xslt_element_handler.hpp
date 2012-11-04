#ifndef ARABICA_XSLT_ELEMENT_HANDLER_HPP
#define ARABICA_XSLT_ELEMENT_HANDLER_HPP

#include "../xslt_element.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ElementHandler : public ItemContainerHandler<Element<string_type, string_adaptor> >
{
  typedef ItemContainerHandler<Element<string_type, string_adaptor> > baseT;
public:
  ElementHandler(CompilationContext<string_type, string_adaptor>& context) :
      ItemContainerHandler<Element<string_type, string_adaptor> >(context)
  {
  } // ElementHandler

protected:
  virtual Element<string_type, string_adaptor>* createContainer(const string_type& /* namespaceURI */,
                                   const string_type& /* localName */,
                                   const string_type& qName,
                                   const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const ValueRule rules[] = { { "name", true, 0, 0 },
                                       { "namespace", false, "", 0 },
                                       { "use-attribute-sets", false, 0, 0 },
                                       { 0, false, 0, 0 } };

    std::map<string_type, string_type> attrs = gatherAttributes(qName, atts, rules);

    Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> name = baseT::context().xpath_attribute_value_template(attrs["name"]);

    if(attrs["use-attribute-sets"] != "")
      throw SAX::SAXException("don't understand use-attribute-sets yet");
    
    if(attrs["namespace"] == "")
      return new Element<string_type, string_adaptor>(name, 
                         baseT::context().inScopeNamespaces(),
                         attrs["use-attribute-sets"]);

    return new Element<string_type, string_adaptor>(name, 
                       baseT::context().xpath_attribute_value_template(attrs["namespace"]),
                       attrs["use-attribute-sets"]);
  } // createContainer
}; // class ElementHandler

} // namespace XSLT
} // namespace Arabica

#endif 

