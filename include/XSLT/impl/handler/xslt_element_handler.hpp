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
  typedef StylesheetConstant<string_type, string_adaptor> SC;
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
    static const ValueRule<string_type> rules[] = { { SC::name, true, 0, 0 },
                                                    { SC::namespace_, false, string_adaptor::empty_string(), 0 },
                                                    { SC::use_attribute_sets, false, 0, 0 },
                                                    { string_adaptor::empty_string(), false, 0, 0 } };

    std::map<string_type, string_type> attrs = gatherAttributes(qName, atts, rules);

    Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> name = 
                          baseT::context().xpath_attribute_value_template(attrs[SC::name]);

    if(attrs[SC::use_attribute_sets] != string_adaptor::empty_string())
      throw SAX::SAXException("don't understand use-attribute-sets yet");
    
    if(attrs[SC::namespace_] == string_adaptor::empty_string())
      return new Element<string_type, string_adaptor>(name, 
                         baseT::context().inScopeNamespaces(),
                         attrs[SC::use_attribute_sets]);

    return new Element<string_type, string_adaptor>(name, 
                       baseT::context().xpath_attribute_value_template(attrs[SC::namespace_]),
                       attrs[SC::use_attribute_sets]);
  } // createContainer
}; // class ElementHandler

} // namespace XSLT
} // namespace Arabica

#endif 

