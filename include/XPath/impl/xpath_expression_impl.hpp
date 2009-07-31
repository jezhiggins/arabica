#ifndef ARABICA_XPATHIC_XPATH_EXPRESSION_IMPL_H
#define ARABICA_XPATHIC_XPATH_EXPRESSION_IMPL_H

#include "xpath_expression.hpp"

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class string_type, class string_adaptor>
class NumericExpression : virtual public XPathExpression_impl<string_type, string_adaptor>
{
public:
  NumericExpression() { } 

  virtual ValueType type() const { return NUMBER; }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return NumericValue<string_type, string_adaptor>::createValue(doEvaluateAsNumber(context, executionContext));
  } // evaluate

  virtual double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context, 
                                  const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  { 
    return doEvaluateAsNumber(context, executionContext); 
  } // evaluateAsNumber 

protected:
  virtual double doEvaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context, 
                                  const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;


  ~NumericExpression() { }  
}; // class NumericExpression

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
