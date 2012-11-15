#ifndef ARABICA_XSLT_PROCESSING_INSTRUCTION_HANDLER_HPP
#define ARABICA_XSLT_PROCESSING_INSTRUCTION_HANDLER_HPP

#include "../xslt_processing_instruction.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ProcessingInstructionHandler : public ItemContainerHandler<ProcessingInstruction<string_type, string_adaptor> >
{
  typedef ItemContainerHandler<ProcessingInstruction<string_type, string_adaptor> > baseT;
  typedef StylesheetConstant<string_type, string_adaptor> SC;
  typedef AttributeValidators<string_type, string_adaptor> AV;

public:
  ProcessingInstructionHandler(CompilationContext<string_type, string_adaptor>& context) :
      ItemContainerHandler<ProcessingInstruction<string_type, string_adaptor> >(context)
  {
  } // ProcessingInstructionHandler

  virtual ProcessingInstruction<string_type, string_adaptor>* createContainer(const string_type& /* namespaceURI */,
                                                 const string_type& /* localName */,
                                                 const string_type& qName,
                                                 const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const AV rules = AV::rule(SC::name, true);
    string_type name = rules.gather(qName, atts)[SC::name];

    return new ProcessingInstruction<string_type, string_adaptor>(baseT::context().xpath_attribute_value_template(name));
  } // createContainer
}; // class ProcessingInstructionHandler

} // namespace XSLT
} // namespace Arabica

#endif

