#ifndef ARABICA_XSLT_ATTRIBUTE_HANDLER_HPP
#define ARABICA_XSLT_ATTRIBUTE_HANDLER_HPP

#include "../xslt_attribute.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class AttributeHandler : public ItemContainerHandler<Attribute<string_type, string_adaptor> >
{
  typedef ItemContainerHandler<Attribute<string_type, string_adaptor> > baseT;
public:
  AttributeHandler(CompilationContext<string_type, string_adaptor>& context) :
      baseT(context)
  {
  } // AttributeHandler

protected:
  virtual Attribute<string_type, string_adaptor>* createContainer(const string_type& /* namespaceURI */,
                                     const string_type& /* localName */,
                                     const string_type& qName,
                                     const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const ValueRule rules[] = { { "name", true, 0, 0 },
                                       { "namespace", false, "", 0 },
                                       { 0, false, 0, 0 } };

    std::map<string_type, string_type> attrs = gatherAttributes(qName, atts, rules);

    Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> name = baseT::context().xpath_attribute_value_template(attrs["name"]);

    if(attrs["namespace"] == "")
      return new Attribute<string_type, string_adaptor>(name, baseT::context().inScopeNamespaces());

    return new Attribute<string_type, string_adaptor>(name, baseT::context().xpath_attribute_value_template(attrs["namespace"]));
  } // createContainer
}; // class AttributeHandler

} // namespace XSLT
} // namespace Arabica

#endif 

