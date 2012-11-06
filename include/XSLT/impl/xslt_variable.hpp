#ifndef ARABICA_XSLT_VARIABLE_HPP
#define ARABICA_XSLT_VARIABLE_HPP

#include "xslt_variable_impl.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class Variable : public Variable_impl<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  Variable(const string_type& name, 
           const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& select,
           const Precedence precedence) :
      Variable_impl(name, select, precedence)
  {
  } // Variable

  virtual ~Variable() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext& context) const 
  {
    context.declareVariable(node, *this);
  } // declare
}; // Variable

} // namespace XSLT
} // namespace Arabica
#endif

