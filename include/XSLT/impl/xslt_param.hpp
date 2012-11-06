#ifndef ARABICA_XSLT_PARAM_HPP
#define ARABICA_XSLT_PARAM_HPP

#include "xslt_variable_impl.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class Param : public Variable_impl
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  Param(const string_type& name, 
        const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& select,
        const Precedence& precedence) :
      Variable_impl(name, select, precedence)
  {
  } // Param

  virtual ~Param() { }

protected:
  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext& context) const 
  {
    context.declareParam(node, *this);
  } // declare
}; // Param


} // namespace XSLT
} // namespace Arabica
#endif

