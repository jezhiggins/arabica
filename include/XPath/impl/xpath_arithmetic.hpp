#ifndef ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP
#define ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP

#include <functional>
#include "xpath_value.hpp"
#include "xpath_expression_impl.hpp"

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class string_type, class string_adaptor, class Op>
class ArithmeticOperator : public BinaryExpression<string_type, string_adaptor>,
                           public NumericExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  ArithmeticOperator(XPathExpression_impl<string_type, string_adaptor>* lhs, XPathExpression_impl<string_type, string_adaptor>* rhs) : 
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual double doEvaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context, 
                                  const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  {
    return Op()(baseT::lhs()->evaluateAsNumber(context, executionContext),
                baseT::rhs()->evaluateAsNumber(context, executionContext));
  } // evaluateAsNumber
}; // class ArithmeticOperator

template<class string_type, class string_adaptor>
class PlusOperator : public ArithmeticOperator<string_type, string_adaptor, std::plus<double> >
{
public:
  PlusOperator(XPathExpression_impl<string_type, string_adaptor>* lhs, XPathExpression_impl<string_type, string_adaptor>* rhs) : 
      ArithmeticOperator<string_type, string_adaptor, std::plus<double> >(lhs, rhs) { }
}; // class PlusOperator

template<class string_type, class string_adaptor>
class MinusOperator : public ArithmeticOperator<string_type, string_adaptor, std::minus<double> >
{
public:
  MinusOperator(XPathExpression_impl<string_type, string_adaptor>* lhs, XPathExpression_impl<string_type, string_adaptor>* rhs) : 
      ArithmeticOperator<string_type, string_adaptor, std::minus<double> >(lhs, rhs) { }
}; // class MinusOperator

template<class string_type, class string_adaptor>
class MultiplyOperator : public ArithmeticOperator<string_type, string_adaptor, std::multiplies<double> >
{
public:
  MultiplyOperator(XPathExpression_impl<string_type, string_adaptor>* lhs, XPathExpression_impl<string_type, string_adaptor>* rhs) :
      ArithmeticOperator<string_type, string_adaptor, std::multiplies<double> >(lhs, rhs) { }
}; // class MultiplyOperator

template<class string_type, class string_adaptor>
class DivideOperator : public ArithmeticOperator<string_type, string_adaptor, std::divides<double> >
{
public:
  DivideOperator(XPathExpression_impl<string_type, string_adaptor>* lhs, XPathExpression_impl<string_type, string_adaptor>* rhs) :
      ArithmeticOperator<string_type, string_adaptor, std::divides<double> >(lhs, rhs) { }
}; // class DivideOperator


struct NaN_aware_modulus
{	
  double operator()(const double& lhs, const double& rhs) const
	{	// apply operator% to operands 
    if(isNaN(lhs) || isNaN(rhs)) 
      return NaN; 
    return (static_cast<long>(lhs) % static_cast<long>(rhs)); 
	}
}; // NaN_aware_modulus

template<class string_type, class string_adaptor>
class ModOperator : public ArithmeticOperator<string_type, string_adaptor, NaN_aware_modulus>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  ModOperator(XPathExpression_impl<string_type, string_adaptor>* lhs, XPathExpression_impl<string_type, string_adaptor>* rhs) :
      ArithmeticOperator<string_type, string_adaptor, NaN_aware_modulus>(lhs, rhs) { }
}; // class ModOperator

template<class string_type, class string_adaptor>
class UnaryNegative : public UnaryExpression<string_type, string_adaptor>
{
  typedef UnaryExpression<string_type, string_adaptor> baseT;
public:
  UnaryNegative(XPathExpression_impl<string_type, string_adaptor>* expr) :
      UnaryExpression<string_type, string_adaptor>(expr) { }

  virtual ValueType type() const { return NUMBER; }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return NumericValue<string_type, string_adaptor>::createValue(evaluateAsNumber(context, executionContext));
  } // evaluate
  virtual double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context, 
                                  const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  {
    return -baseT::expr()->evaluateAsNumber(context, executionContext);
  } // evaluateAsNumber
}; // class UnaryNegative

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
