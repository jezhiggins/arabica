#ifndef ARABICA_XPATHIC_XPATH_RELATIONAL_HPP
#define ARABICA_XPATHIC_XPATH_RELATIONAL_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{
namespace impl
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

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(areEqual<string_type, string_adaptor>(baseT::lhs()->evaluate(context, executionContext),
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

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(areNotEqual<string_type, string_adaptor>(baseT::lhs()->evaluate(context, executionContext),
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

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(isLessThan<string_type, string_adaptor>(baseT::lhs()->evaluate(context, executionContext),
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

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(isLessThanEquals<string_type, string_adaptor>(baseT::lhs()->evaluate(context, executionContext),
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

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(isGreaterThan<string_type, string_adaptor>(baseT::lhs()->evaluate(context, executionContext),
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

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return BoolValue<string_type, string_adaptor>::createValue(isGreaterThanEquals<string_type, string_adaptor>(baseT::lhs()->evaluate(context, executionContext),
                                                      baseT::rhs()->evaluate(context, executionContext)));
  } // evaluate
}; // class GreaterThanEqualsOperator

} // namespace impl
} // namespace XPath
} // namespace Arabica
#endif 
