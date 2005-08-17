#ifndef ARABICA_XPATHIC_XPATH_LOGICAL_HPP
#define ARABICA_XPATHIC_XPATH_LOGICAL_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

class OrOperator : private BinaryExpression<std::string, Arabica::default_string_adaptor<std::string> >, 
                   public XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  OrOperator(XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >* lhs, 
             XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >* rhs) :
       BinaryExpression<std::string, Arabica::default_string_adaptor<std::string> >(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    // From XPath 1.0 Rec, section 3.4
    // An or expression is evaluated by evaluating each operand and converting its value 
    // to a boolean as if by a call to the boolean function. The result is true if either 
    // value is true and false otherwise. The right operand is not evaluated if the 
    // left operand evaluates to true.
    if(lhs()->evaluate(context, executionContext)->asBool())
      return BoolValue<std::string, Arabica::default_string_adaptor<std::string> >::createValue(true);
    return BoolValue<std::string, Arabica::default_string_adaptor<std::string> >::createValue(rhs()->evaluate(context, executionContext)->asBool());
  } // evaluate
}; // class OrOperator

class AndOperator : private BinaryExpression<std::string, Arabica::default_string_adaptor<std::string> >, 
                    public XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  AndOperator(XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >* lhs, 
              XPathExpression<std::string, Arabica::default_string_adaptor<std::string> >* rhs) :
       BinaryExpression<std::string, Arabica::default_string_adaptor<std::string> >(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    // From XPath 1.0 Rec, section 3.4
    // An and expression is evaluated by evaluating each operand and converting its value 
    // to a boolean as if by a call to the boolean function. The result is true if both 
    // values are true and false otherwise. The right operand is not evaluated if the left 
    // operand evaluates to false.
    if(!lhs()->evaluate(context, executionContext)->asBool())
      return BoolValue<std::string, Arabica::default_string_adaptor<std::string> >::createValue(false);
    return BoolValue<std::string, Arabica::default_string_adaptor<std::string> >::createValue(rhs()->evaluate(context, executionContext)->asBool());
  } // evaluate
}; // class AndOperator

} // namespace XPath
} // namespace Arabica
#endif 
