#ifndef ARABICA_XPATHIC_XPATH_LOGICAL_HPP
#define ARABICA_XPATHIC_XPATH_LOGICAL_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class OrOperator : private BinaryExpression<string_type, string_adaptor>, 
                   public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  OrOperator(XPathExpression<string_type, string_adaptor>* lhs, 
             XPathExpression<string_type, string_adaptor>* rhs) :
       BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    // From XPath 1.0 Rec, section 3.4
    // An or expression is evaluated by evaluating each operand and converting its value 
    // to a boolean as if by a call to the boolean function. The result is true if either 
    // value is true and false otherwise. The right operand is not evaluated if the 
    // left operand evaluates to true.
    if(baseT::lhs()->evaluate(context, executionContext)->asBool())
      return BoolValue<string_type, string_adaptor>::createValue(true);
    return BoolValue<string_type, string_adaptor>::createValue(baseT::rhs()->evaluate(context, executionContext)->asBool());
  } // evaluate
}; // class OrOperator

template<class string_type, class string_adaptor>
class AndOperator : private BinaryExpression<string_type, string_adaptor>, 
                    public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  AndOperator(XPathExpression<string_type, string_adaptor>* lhs, 
              XPathExpression<string_type, string_adaptor>* rhs) :
       BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    // From XPath 1.0 Rec, section 3.4
    // An and expression is evaluated by evaluating each operand and converting its value 
    // to a boolean as if by a call to the boolean function. The result is true if both 
    // values are true and false otherwise. The right operand is not evaluated if the left 
    // operand evaluates to false.
    if(!baseT::lhs()->evaluate(context, executionContext)->asBool())
      return BoolValue<string_type, string_adaptor>::createValue(false);
    return BoolValue<string_type, string_adaptor>::createValue(baseT::rhs()->evaluate(context, executionContext)->asBool());
  } // evaluate
}; // class AndOperator

} // namespace XPath
} // namespace Arabica
#endif 
