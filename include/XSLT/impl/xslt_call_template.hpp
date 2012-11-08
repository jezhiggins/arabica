#ifndef ARABICA_XSLT_CALL_TEMPLATE_HPP
#define ARABICA_XSLT_CALL_TEMPLATE_HPP

#include "xslt_compiled_stylesheet.hpp"
#include "xslt_with_param.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class CallTemplate : public Item<string_type, string_adaptor>,
                     public WithParamable<string_type, string_adaptor>
{
public:
  CallTemplate(const string_type& name) :
    name_(name)
  {
  } // CallTemplate

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const
  {
    ParamPasser<string_type, string_adaptor> passer(*this, node, context);
    context.stylesheet().callTemplate(name_, node, context);
  } // execute

private:
  const string_type name_;
}; // class CallTemplate

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CALL_TEMPLATE_HPP

