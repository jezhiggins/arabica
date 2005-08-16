#ifndef ARABICA_XPATHIC_XPATH_RELATIONAL_HPP
#define ARABICA_XPATHIC_XPATH_RELATIONAL_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

class EqualsOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  EqualsOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
       BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(areEqual(lhs()->evaluate(context, executionContext),
                                           rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class EqualsOperator

class NotEqualsOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  NotEqualsOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
       BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(!areEqual(lhs()->evaluate(context, executionContext),
                                            rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class NotEqualsOperator

class LessThanOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  LessThanOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(isLessThan(lhs()->evaluate(context, executionContext),
                                             rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class LessThanOperator

class LessThanEqualsOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  LessThanEqualsOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(isLessThanEquals(lhs()->evaluate(context, executionContext),
                                                   rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class LessThanEqualsOperator

class GreaterThanOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  GreaterThanOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(isGreaterThan(lhs()->evaluate(context, executionContext),
                                                rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class GreaterThanOperator

class GreaterThanEqualsOperator : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  GreaterThanEqualsOperator(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
      BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    return BoolValue::createValue(isGreaterThanEquals(lhs()->evaluate(context, executionContext),
                                                      rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class GreaterThanEqualsOperator

} // namespace XPath
} // namespace Arabica
#endif 
