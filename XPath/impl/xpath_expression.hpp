#ifndef ARABICA_XPATHIC_XPATH_EXPRESSION_H
#define ARABICA_XPATHIC_XPATH_EXPRESSION_H

#include <string>
#include <DOM/Node.h>
#include "xpath_object.hpp"
#include "xpath_execution_context.hpp"

namespace Arabica
{
namespace XPath
{

class XPathExpression
{
protected:
  XPathExpression() { }

public:
  virtual ~XPathExpression() { }

  XPathValuePtr evaluate(const DOM::Node<std::string>& context) const
  {
    ExecutionContext executionContext;
    return evaluate(context, executionContext);
  } // evaluate

  virtual bool evaluateAsBool(const DOM::Node<std::string>& context) const { return evaluate(context)->asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<std::string>& context) const { return evaluate(context)->asNumber(); }
  virtual std::string evaluateAsString(const DOM::Node<std::string>& context) const { return evaluate(context)->asString(); }
  virtual NodeSet evaluateAsNodeSet(const DOM::Node<std::string>& context) const { return evaluate(context)->asNodeSet(); }

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const Arabica::XPath::ExecutionContext& executionContext) const = 0;

private:
  XPathExpression(const XPathExpression&);
  bool operator==(const XPathExpression&);
  XPathExpression& operator=(const XPathExpression&);
}; // class XPathExpression

typedef boost::shared_ptr<XPathExpression> XPathExpressionPtr;

class UnaryExpression
{
public:
  UnaryExpression(XPathExpression* expr) :
      expr_(expr) { }

protected:
  ~UnaryExpression() 
  {
    delete expr_;
  } // ~UnaryExpression

  XPathExpression* expr() const { return expr_; }

private:
  XPathExpression* expr_;
}; // class UnaryExpression

class BinaryExpression
{
public:
  BinaryExpression(XPathExpression* lhs, XPathExpression* rhs) :
      lhs_(lhs), rhs_(rhs) { }

protected:
  ~BinaryExpression() 
  { 
    delete lhs_;
    delete rhs_;
  } // ~BinaryExpression

  XPathExpression* lhs() const { return lhs_; }
  XPathExpression* rhs() const { return rhs_; }

private:
  XPathExpression* lhs_;
  XPathExpression* rhs_;
}; // class BinaryExpression

} // namespace XPath
} // namespace Arabica

#endif
