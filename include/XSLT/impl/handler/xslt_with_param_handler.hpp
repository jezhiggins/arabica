#ifndef ARABICA_XSLT_WITH_PARAM_HANDLER_HPP
#define ARABICA_XSLT_WITH_PARAM_HANDLER_HPP

#include "../xslt_with_param.hpp"
#include "xslt_variable_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class WithParamHandler : public VariableHandler<WithParam<string_type, string_adaptor> >
{
  typedef VariableHandler<WithParam<string_type, string_adaptor> > baseT;
public:
  WithParamHandler(CompilationContext<string_type, string_adaptor>& context,
                   WithParamable<string_type, string_adaptor>& paramee) :
    baseT(context),
    paramee_(paramee)
  {
  } // WithParamHandler

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    paramee_.add_with_param(baseT::container());
    baseT::context().pop();
  } // endElement

private:
  WithParamable<string_type, string_adaptor>& paramee_;
}; // WithParamHandler

} // namespace XSLT
} // namespace Arabica

#endif

