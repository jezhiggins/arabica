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
class Variable : public XPathExpression_impl<string_type, string_adaptor>
{
public:
  Variable(const string_type& namespace_uri,
           const string_type& name) : 
    namespace_uri_(namespace_uri),
    name_(name) 
  { 
  } // Variable

  virtual ValueType type() const { return ANY; }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& /* context */, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return executionContext.variableResolver().resolveVariable(namespace_uri_, name_);
  } // evaluate

private:
  const string_type namespace_uri_;
  const string_type name_;
}; // class Variable

} // namespace XPath
} // namespace Arabica

#endif
