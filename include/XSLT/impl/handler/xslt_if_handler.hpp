#ifndef ARABICA_XSLT_IF_HANDLER_HPP
#define ARABICA_XSLT_IF_HANDLER_HPP

#include "../xslt_if.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class IfHandler : public ItemContainerHandler<If>
{
public:
  IfHandler(CompilationContext& context) :
      ItemContainerHandler<If>(context)
  {
  } // IfHandler

  virtual If* createContainer(const std::string& /* namespaceURI */,
                              const std::string& /* localName */,
                              const std::string& qName,
                              const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "test", true, 0, 0 },
                                       { 0, false, 0, 0 } };
    std::string test = gatherAttributes(qName, atts, rules)["test"];

    return new If(ItemContainerHandler<If>::context().xpath_expression(test));
  } // startElement
}; // class IfHandler

} // namespace XSLT
} // namespace Arabica

#endif

