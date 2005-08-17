#ifndef ARABICA_XPATH_VARIABLE_HPP
#define ARABICA_XPATH_VARIABLE_HPP

#include "xpath_value.hpp"
#include "xpath_execution_context.hpp"
#include "xpath_variable_resolver.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class Variable : public XPathExpression<string_type, string_adaptor>
{
public:
  Variable(const string_type& name) : name_(name) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return executionContext.variableResolver().resolveVariable(name_);
  } // evaluate

private:
  const string_type name_;
}; // class Variable

} // namespace XPath
} // namespace Arabica

#endif
