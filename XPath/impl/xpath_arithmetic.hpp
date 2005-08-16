#ifndef ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP
#define ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

class PlusOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  PlusOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) : 
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const 
  {
    return NumericValue::createValue(lhs()->evaluateAsNumber(context) + rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class PlusOperator

class MinusOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  MinusOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) : 
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(lhs()->evaluateAsNumber(context) - rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class MinusOperator

class MultiplyOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  MultiplyOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(lhs()->evaluateAsNumber(context) * rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class MultiplyOperator

class DivideOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  DivideOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(lhs()->evaluateAsNumber(context) / rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class DivideOperator

class ModOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  ModOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(static_cast<long>(lhs()->evaluateAsNumber(context)) % static_cast<long>(rhs()->evaluateAsNumber(context)));
  } // evaluate
}; // class ModOperator

class UnaryNegative : private UnaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  UnaryNegative(XPathExpression<std::string>* expr) :
      UnaryExpression<std::string>(expr) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return NumericValue::createValue(-expr()->evaluate(context, executionContext)->asNumber());
  } // evaluate
}; // class UnaryNegative

} // XPath
} // Arabica

#endif
