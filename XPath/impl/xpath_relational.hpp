#ifndef ARABICA_XPATHIC_XPATH_RELATIONAL_HPP
#define ARABICA_XPATHIC_XPATH_RELATIONAL_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

class EqualsOperator : private BinaryExpression, public XPathExpression
{
public:
  EqualsOperator(XPathExpression* lhs, XPathExpression* rhs) :
       BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(areEqual(lhs()->evaluate(context, executionContext),
                                           rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class EqualsOperator

class NotEqualsOperator : private BinaryExpression, public XPathExpression
{
public:
  NotEqualsOperator(XPathExpression* lhs, XPathExpression* rhs) :
       BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(!areEqual(lhs()->evaluate(context, executionContext),
                                            rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class NotEqualsOperator

class LessThanOperator : private BinaryExpression, public XPathExpression
{
public:
  LessThanOperator(XPathExpression* lhs, XPathExpression* rhs) :
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(isLessThan(lhs()->evaluate(context, executionContext),
                                             rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class LessThanOperator

class LessThanEqualsOperator : private BinaryExpression, public XPathExpression
{
public:
  LessThanEqualsOperator(XPathExpression* lhs, XPathExpression* rhs) :
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(isLessThanEquals(lhs()->evaluate(context, executionContext),
                                                   rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class LessThanEqualsOperator

class GreaterThanOperator : private BinaryExpression, public XPathExpression
{
public:
  GreaterThanOperator(XPathExpression* lhs, XPathExpression* rhs) :
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(isGreaterThan(lhs()->evaluate(context, executionContext),
                                                rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class GreaterThanOperator

class GreaterThanEqualsOperator : private BinaryExpression, public XPathExpression
{
public:
  GreaterThanEqualsOperator(XPathExpression* lhs, XPathExpression* rhs) :
      BinaryExpression(lhs, rhs) { }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(isGreaterThanEquals(lhs()->evaluate(context, executionContext),
                                                      rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class GreaterThanEqualsOperator

} // namespace XPath
} // namespace Arabica
#endif 
