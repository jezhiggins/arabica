#ifndef ARABICA_XSLT_PROCESSING_INSTRUCTION_HANDLER_HPP
#define ARABICA_XSLT_PROCESSING_INSTRUCTION_HANDLER_HPP

#include "../xslt_processing_instruction.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class ProcessingInstructionHandler : public ItemContainerHandler<ProcessingInstruction>
{
public:
  ProcessingInstructionHandler(CompilationContext& context) :
      ItemContainerHandler<ProcessingInstruction>(context)
  {
  } // ProcessingInstructionHandler

  virtual ProcessingInstruction* createContainer(const std::string& /* namespaceURI */,
                                                 const std::string& /* localName */,
                                                 const std::string& qName,
                                                 const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "name", true, 0, 0 },
                                       { 0, false, 0, 0} };
    std::string name = gatherAttributes(qName, atts, rules)["name"];

    return new ProcessingInstruction(ItemContainerHandler<ProcessingInstruction>::context().xpath_attribute_value_template(name));
  } // createContainer
}; // class ProcessingInstructionHandler

} // namespace XSLT
} // namespace Arabica

#endif

