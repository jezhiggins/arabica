#ifndef ARABICA_XSLT_PROCESSING_INSTRUCTION_HPP
#define ARABICA_XSLT_PROCESSING_INSTRUCTION_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

class ProcessingInstruction : public ItemContainer
{
public:
  ProcessingInstruction(const Arabica::XPath::XPathExpressionPtr<std::string>& name) :
    name_(name)
  { 
  } // ProcessingInstruction

  virtual ~ProcessingInstruction() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    std::string name = name_->evaluateAsString(node, context.xpathContext());
    if(name.empty())
      throw SAX::SAXException("xsl:processing-instruction : name attribute must evaluate to a valid name");

    context.sink().start_processing_instruction(name);

    execute_children(node, context);

    context.sink().end_processing_instruction();
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<std::string> name_;
}; // class ProcessingInstruction

} // namespace XSLT
} // namespace Arabica

#endif

