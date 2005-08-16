#ifndef ARABICA_XPATH_VARIABLE_HPP
#define ARABICA_XPATH_VARIABLE_HPP

#include "xpath_value.hpp"
#include "xpath_execution_context.hpp"
#include "xpath_variable_resolver.hpp"

namespace Arabica
{
namespace XPath
{

class Variable : public XPathExpression
{
public:
  Variable(const std::string& name) : name_(name) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return executionContext.variableResolver().resolveVariable(name_);
  } // evaluate

private:
  const std::string name_;
}; // class Variable

} // namespace XPath
} // namespace Arabica

#endif
