#ifndef ARABICA_XSLT_WITH_PARAM_HANDLER_HPP
#define ARABICA_XSLT_WITH_PARAM_HANDLER_HPP

#include "../xslt_with_param.hpp"
#include "xslt_variable_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class WithParamHandler : public VariableHandler<WithParam>
{
public:
  WithParamHandler(CompilationContext& context,
                   WithParamable& paramee) :
    VariableHandler<WithParam>(context),
    paramee_(paramee)
  {
  } // WithParamHandler

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    paramee_.add_with_param(container());
    context().pop();
  } // endElement

private:
  WithParamable& paramee_;
}; // WithParamHandler

} // namespace XSLT
} // namespace Arabica

#endif

