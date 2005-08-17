#ifndef ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP
#define ARABICA_XPATHIC_XPATH_ARITHMETIC_HPP

#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class PlusOperator : private BinaryExpression<string_type, string_adaptor>, 
                     public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  PlusOperator(XPathExpression<string_type, string_adaptor>* lhs, XPathExpression<string_type, string_adaptor>* rhs) : 
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  {
    return NumericValue<string_type, string_adaptor>::createValue(baseT::lhs()->evaluateAsNumber(context) + baseT::rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class PlusOperator

template<class string_type, class string_adaptor>
class MinusOperator : private BinaryExpression<string_type, string_adaptor>, 
                      public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  MinusOperator(XPathExpression<string_type, string_adaptor>* lhs, XPathExpression<string_type, string_adaptor>* rhs) : 
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return NumericValue<string_type, string_adaptor>::createValue(baseT::lhs()->evaluateAsNumber(context) - baseT::rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class MinusOperator

template<class string_type, class string_adaptor>
class MultiplyOperator : private BinaryExpression<string_type, string_adaptor>, 
                         public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  MultiplyOperator(XPathExpression<string_type, string_adaptor>* lhs, XPathExpression<string_type, string_adaptor>* rhs) :
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return NumericValue<string_type, string_adaptor>::createValue(baseT::lhs()->evaluateAsNumber(context) * baseT::rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class MultiplyOperator

template<class string_type, class string_adaptor>
class DivideOperator : private BinaryExpression<string_type, string_adaptor>, 
                       public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  DivideOperator(XPathExpression<string_type, string_adaptor>* lhs, XPathExpression<string_type, string_adaptor>* rhs) :
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return NumericValue<string_type, string_adaptor>::createValue(baseT::lhs()->evaluateAsNumber(context) / baseT::rhs()->evaluateAsNumber(context));
  } // evaluate
}; // class DivideOperator

template<class string_type, class string_adaptor>
class ModOperator : private BinaryExpression<string_type, string_adaptor>, 
                    public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  ModOperator(XPathExpression<string_type, string_adaptor>* lhs, XPathExpression<string_type, string_adaptor>* rhs) :
      BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return NumericValue<string_type, string_adaptor>::createValue(static_cast<long>(baseT::lhs()->evaluateAsNumber(context)) % static_cast<long>(baseT::rhs()->evaluateAsNumber(context)));
  } // evaluate
}; // class ModOperator

template<class string_type, class string_adaptor>
class UnaryNegative : private UnaryExpression<string_type, string_adaptor>, 
                      public XPathExpression<string_type, string_adaptor>
{
  typedef UnaryExpression<string_type, string_adaptor> baseT;
public:
  UnaryNegative(XPathExpression<string_type, string_adaptor>* expr) :
      UnaryExpression<string_type, string_adaptor>(expr) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return NumericValue<string_type, string_adaptor>::createValue(-baseT::expr()->evaluate(context, executionContext)->asNumber());
  } // evaluate
}; // class UnaryNegative

} // XPath
} // Arabica

#endif
