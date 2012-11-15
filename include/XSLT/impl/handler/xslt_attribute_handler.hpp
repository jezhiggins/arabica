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
  typedef StylesheetConstant<string_type, string_adaptor> SC;
  typedef AttributeValidators<string_type, string_adaptor> AV;
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
    static const AV rules = AV::rule(SC::name, true)
                               .rule(SC::namespace_, false, string_adaptor::empty_string());

    std::map<string_type, string_type> attrs = rules.gather(qName, atts);

    Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> name = 
                         baseT::context().xpath_attribute_value_template(attrs[SC::name]);

    if(attrs[SC::namespace_] == string_adaptor::empty_string())
      return new Attribute<string_type, string_adaptor>(name, baseT::context().inScopeNamespaces());

    return new Attribute<string_type, string_adaptor>(name, baseT::context().xpath_attribute_value_template(attrs[SC::namespace_]));
  } // createContainer
}; // class AttributeHandler

} // namespace XSLT
} // namespace Arabica

#endif 

