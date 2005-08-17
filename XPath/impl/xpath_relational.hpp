#ifndef ARABICA_XPATHIC_XPATH_RELATIONAL_HPP
#define ARABICA_XPATHIC_XPATH_RELATIONAL_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class EqualsOperator : private BinaryExpression<string_type, string_adaptor>, 
                       public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  EqualsOperator(XPathExpression<string_type, string_adaptor>* lhs,   
                 XPathExpression<string_type, string_adaptor>* rhs) :
       BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(areEqual(baseT::lhs()->evaluate(context, executionContext),
                                           baseT::rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class EqualsOperator

template<class string_type, class string_adaptor>
class NotEqualsOperator : private BinaryExpression<string_type, string_adaptor>, 
                          public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  NotEqualsOperator(XPathExpression<string_type, string_adaptor>* lhs, 
                    XPathExpression<string_type, string_adaptor>* rhs) :
       BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(!areEqual(baseT::lhs()->evaluate(context, executionContext),
                                            baseT::rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class NotEqualsOperator

template<class string_type, class string_adaptor>
class LessThanOperator : private BinaryExpression<string_type, string_adaptor>, 
                         public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  LessThanOperator(XPathExpression<string_type, string_adaptor>* lhs, 
                   XPathExpression<string_type, string_adaptor>* rhs) :
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(isLessThan(baseT::lhs()->evaluate(context, executionContext),
                                             baseT::rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class LessThanOperator

template<class string_type, class string_adaptor>
class LessThanEqualsOperator : private BinaryExpression<string_type, string_adaptor>, 
                               public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  LessThanEqualsOperator(XPathExpression<string_type, string_adaptor>* lhs, 
                         XPathExpression<string_type, string_adaptor>* rhs) :
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(isLessThanEquals(baseT::lhs()->evaluate(context, executionContext),
                                                   baseT::rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class LessThanEqualsOperator

template<class string_type, class string_adaptor>
class GreaterThanOperator : private BinaryExpression<string_type, string_adaptor>, 
                            public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  GreaterThanOperator(XPathExpression<string_type, string_adaptor>* lhs, 
                      XPathExpression<string_type, string_adaptor>* rhs) :
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(isGreaterThan(baseT::lhs()->evaluate(context, executionContext),
                                                baseT::rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class GreaterThanOperator

template<class string_type, class string_adaptor>
class GreaterThanEqualsOperator : private BinaryExpression<string_type, string_adaptor>, 
                                  public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  GreaterThanEqualsOperator(XPathExpression<string_type, string_adaptor>* lhs, 
                            XPathExpression<string_type, string_adaptor>* rhs) :
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(isGreaterThanEquals(baseT::lhs()->evaluate(context, executionContext),
                                                      baseT::rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class GreaterThanEqualsOperator

} // namespace XPath
} // namespace Arabica
#endif 
