#ifndef ARABICA_XSLT_IF_HANDLER_HPP
#define ARABICA_XSLT_IF_HANDLER_HPP

#include "../xslt_if.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class IfHandler : public ItemContainerHandler<If<string_type, string_adaptor> >
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
  typedef AttributeValidators<string_type, string_adaptor> AV;
public:
  IfHandler(CompilationContext<string_type, string_adaptor>& context) :
      ItemContainerHandler<If<string_type, string_adaptor> >(context)
  {
  } // IfHandler

  virtual If<string_type, string_adaptor>* createContainer(const string_type& /* namespaceURI */,
                              const string_type& /* localName */,
                              const string_type& qName,
                              const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const AV rules = AV::rule(SC::test, true);
    string_type test = rules.gather(qName, atts)[SC::test];

    return new If<string_type, string_adaptor>(ItemContainerHandler<If<string_type, string_adaptor> >::context().xpath_expression(test));
  } // startElement
}; // class IfHandler

} // namespace XSLT
} // namespace Arabica

#endif

