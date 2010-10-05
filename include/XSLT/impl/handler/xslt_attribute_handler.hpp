#ifndef ARABICA_XSLT_ATTRIBUTE_HANDLER_HPP
#define ARABICA_XSLT_ATTRIBUTE_HANDLER_HPP

#include "../xslt_attribute.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class AttributeHandler : public ItemContainerHandler<Attribute>
{
public:
  AttributeHandler(CompilationContext& context) :
      ItemContainerHandler<Attribute>(context)
  {
  } // AttributeHandler

protected:
  virtual Attribute* createContainer(const std::string& /* namespaceURI */,
                                     const std::string& /* localName */,
                                     const std::string& qName,
                                     const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "name", true, 0, 0 },
                                       { "namespace", false, "", 0 },
                                       { 0, false, 0, 0 } };

    std::map<std::string, std::string> attrs = gatherAttributes(qName, atts, rules);

    Arabica::XPath::XPathExpressionPtr<std::string> name = context().xpath_attribute_value_template(attrs["name"]);

    if(attrs["namespace"] == "")
      return new Attribute(name, 
                           context().inScopeNamespaces());

    return new Attribute(name, 
                         context().xpath_attribute_value_template(attrs["namespace"]));
  } // createContainer
}; // class AttributeHandler

} // namespace XSLT
} // namespace Arabica

#endif 

