#ifndef ARABICA_XSLT_CALL_TEMPLATE_HPP
#define ARABICA_XSLT_CALL_TEMPLATE_HPP

#include "xslt_compiled_stylesheet.hpp"
#include "xslt_with_param.hpp"

namespace Arabica
{
namespace XSLT
{

class CallTemplate : public Item,
                     public WithParamable
{
public:
  CallTemplate(const std::string& name) :
    name_(name)
  {
  } // CallTemplate

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    ParamPasser passer(*this, node, context);
    context.stylesheet().callTemplate(name_, node, context);
  } // execute

private:
  const std::string name_;
}; // class CallTemplate

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CALL_TEMPLATE_HPP

