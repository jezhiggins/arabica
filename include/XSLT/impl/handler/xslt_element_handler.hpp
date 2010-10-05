#ifndef ARABICA_XSLT_ELEMENT_HANDLER_HPP
#define ARABICA_XSLT_ELEMENT_HANDLER_HPP

#include "../xslt_element.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class ElementHandler : public ItemContainerHandler<Element>
{
public:
  ElementHandler(CompilationContext& context) :
      ItemContainerHandler<Element>(context)
  {
  } // ElementHandler

protected:
  virtual Element* createContainer(const std::string& /* namespaceURI */,
                                   const std::string& /* localName */,
                                   const std::string& qName,
                                   const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "name", true, 0, 0 },
                                       { "namespace", false, "", 0 },
                                       { "use-attribute-sets", false, 0, 0 },
                                       { 0, false, 0, 0 } };

    std::map<std::string, std::string> attrs = gatherAttributes(qName, atts, rules);

    Arabica::XPath::XPathExpressionPtr<std::string> name = context().xpath_attribute_value_template(attrs["name"]);

    if(attrs["use-attribute-sets"] != "")
      throw SAX::SAXException("don't understand use-attribute-sets yet");
    
    if(attrs["namespace"] == "")
      return new Element(name, 
                         context().inScopeNamespaces(),
                         attrs["use-attribute-sets"]);

    return new Element(name, 
                       context().xpath_attribute_value_template(attrs["namespace"]),
                       attrs["use-attribute-sets"]);
  } // createContainer
}; // class ElementHandler

} // namespace XSLT
} // namespace Arabica

#endif 

