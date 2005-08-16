#ifndef ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP
#define ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type>
class PlusOperator : private BinaryExpression<string_type>, public XPathExpression<string_type>
{
  typedef BinaryExpression<string_type> baseT;
public:
  PlusOperator(XPathExpression<string_type>* lhs, XPathExpression<string_type>* rhs) : 
      BinaryExpression<string_type>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext& executionContext) const 
  {
    return NumericValue::createValue(baseT::lhs()->evaluateAsNumber(context) + baseT::rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class PlusOperator

template<class string_type>
class MinusOperator : private BinaryExpression<string_type>, public XPathExpression<string_type>
{
  typedef BinaryExpression<string_type> baseT;
public:
  MinusOperator(XPathExpression<string_type>* lhs, XPathExpression<string_type>* rhs) : 
      BinaryExpression<string_type>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(baseT::lhs()->evaluateAsNumber(context) - baseT::rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class MinusOperator

template<class string_type>
class MultiplyOperator : private BinaryExpression<string_type>, public XPathExpression<string_type>
{
  typedef BinaryExpression<string_type> baseT;
public:
  MultiplyOperator(XPathExpression<string_type>* lhs, XPathExpression<string_type>* rhs) :
      BinaryExpression<string_type>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(baseT::lhs()->evaluateAsNumber(context) * baseT::rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class MultiplyOperator

template<class string_type>
class DivideOperator : private BinaryExpression<string_type>, public XPathExpression<string_type>
{
  typedef BinaryExpression<string_type> baseT;
public:
  DivideOperator(XPathExpression<string_type>* lhs, XPathExpression<string_type>* rhs) :
      BinaryExpression<string_type>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(baseT::lhs()->evaluateAsNumber(context) / baseT::rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class DivideOperator

template<class string_type>
class ModOperator : private BinaryExpression<string_type>, public XPathExpression<string_type>
{
  typedef BinaryExpression<string_type> baseT;
public:
  ModOperator(XPathExpression<string_type>* lhs, XPathExpression<string_type>* rhs) :
      BinaryExpression<string_type>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(static_cast<long>(baseT::lhs()->evaluateAsNumber(context)) % static_cast<long>(baseT::rhs()->evaluateAsNumber(context)));
  } // evaluate
}; // class ModOperator

template<class string_type>
class UnaryNegative : private UnaryExpression<string_type>, public XPathExpression<string_type>
{
  typedef UnaryExpression<string_type> baseT;
public:
  UnaryNegative(XPathExpression<string_type>* expr) :
      UnaryExpression<string_type>(expr) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(-baseT::expr()->evaluate(context, executionContext)->asNumber());
  } // evaluate
}; // class UnaryNegative

} // XPath
} // Arabica

#endif
