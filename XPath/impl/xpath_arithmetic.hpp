#ifndef ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP
#define ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

class PlusOperator : private BinaryExpression, public XPathExpression
{
public:
  PlusOperator(XPathExpression* lhs, XPathExpression* rhs) : 
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const 
  {
    return NumericValue::createValue(lhs()->evaluateAsNumber(context) + rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class PlusOperator

class MinusOperator : private BinaryExpression, public XPathExpression
{
public:
  MinusOperator(XPathExpression* lhs, XPathExpression* rhs) : 
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(lhs()->evaluateAsNumber(context) - rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class MinusOperator

class MultiplyOperator : private BinaryExpression, public XPathExpression
{
public:
  MultiplyOperator(XPathExpression* lhs, XPathExpression* rhs) :
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(lhs()->evaluateAsNumber(context) * rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class MultiplyOperator

class DivideOperator : private BinaryExpression, public XPathExpression
{
public:
  DivideOperator(XPathExpression* lhs, XPathExpression* rhs) :
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(lhs()->evaluateAsNumber(context) / rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class DivideOperator

class ModOperator : private BinaryExpression, public XPathExpression
{
public:
  ModOperator(XPathExpression* lhs, XPathExpression* rhs) :
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(static_cast<long>(lhs()->evaluateAsNumber(context)) % static_cast<long>(rhs()->evaluateAsNumber(context)));
  } // evaluate
}; // class ModOperator

class UnaryNegative : private UnaryExpression, public XPathExpression
{
public:
  UnaryNegative(XPathExpression* expr) :
      UnaryExpression(expr) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(-expr()->evaluate(context, executionContext)->asNumber());
  } // evaluate
}; // class UnaryNegative

} // XPath
} // Arabica

#endif
