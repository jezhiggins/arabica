#ifndef ARABICA_XSLT_PARAM_HPP
#define ARABICA_XSLT_PARAM_HPP

#include "xslt_variable_impl.hpp"

namespace Arabica
{
namespace XSLT
{

class Param : public Variable_impl
{
public:
  Param(const std::string& name, 
        const Arabica::XPath::XPathExpressionPtr<std::string>& select,
        const Precedence& precedence) :
      Variable_impl(name, select, precedence)
  {
  } // Param

  virtual ~Param() { }

protected:
  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const 
  {
    context.declareParam(node, *this);
  } // declare
}; // Param


} // namespace XSLT
} // namespace Arabica
#endif

