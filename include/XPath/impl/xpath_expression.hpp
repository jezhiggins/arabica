#ifndef ARABICA_XPATHIC_XPATH_EXPRESSION_H
#define ARABICA_XPATHIC_XPATH_EXPRESSION_H

#include <string>
#include <DOM/Node.hpp>
#include "xpath_object.hpp"
#include "xpath_execution_context.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class XPathExpression_impl
{
protected:
  XPathExpression_impl() { }

public:
  virtual ~XPathExpression_impl() { }

  XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context) const
  {
    ExecutionContext<string_type, string_adaptor> executionContext;
    return evaluate(context, executionContext);
  } // evaluate

  virtual bool evaluateAsBool(const DOM::Node<string_type, string_adaptor>& context) const { return evaluate(context).asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context) const { return evaluate(context).asNumber(); }
  virtual string_type evaluateAsString(const DOM::Node<string_type, string_adaptor>& context) const { return evaluate(context).asString(); }
  virtual NodeSet<string_type, string_adaptor> evaluateAsNodeSet(const DOM::Node<string_type, string_adaptor>& context) const { return evaluate(context).asNodeSet(); }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;

  virtual bool evaluateAsBool(const DOM::Node<string_type, string_adaptor>& context, 
															const ExecutionContext<string_type, string_adaptor>& executionContext) const { return evaluate(context, executionContext).asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context, 
                                  const ExecutionContext<string_type, string_adaptor>& executionContext) const { return evaluate(context, executionContext).asNumber(); }
  virtual string_type evaluateAsString(const DOM::Node<string_type, string_adaptor>& context, 
                                       const ExecutionContext<string_type, string_adaptor>& executionContext) const { return evaluate(context, executionContext).asString(); }
  virtual NodeSet<string_type, string_adaptor> evaluateAsNodeSet(const DOM::Node<string_type, string_adaptor>& context, 
                                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const { return evaluate(context, executionContext).asNodeSet(); }


private:
  XPathExpression_impl(const XPathExpression_impl&);
  bool operator==(const XPathExpression_impl&);
  XPathExpression_impl& operator=(const XPathExpression_impl&);
}; // class XPathExpression_impl

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XPathExpressionPtr
{ 
public:
  XPathExpressionPtr() : ptr_() { }
  explicit XPathExpressionPtr(XPathExpression_impl<string_type, string_adaptor>* xp) : ptr_(xp) { }
  XPathExpressionPtr(const XPathExpressionPtr& rhs) : ptr_(rhs.ptr_) { }
  XPathExpressionPtr& operator=(const XPathExpressionPtr& rhs)
  {
    ptr_ = rhs.ptr_;
    return *this;
  } // operator=

  const XPathExpression_impl<string_type, string_adaptor>* get() const { return ptr_.get(); }
  const XPathExpression_impl<string_type, string_adaptor>* operator->() const { return ptr_.get(); }

  operator bool() const { return ptr_.get(); }

private:
  typedef boost::shared_ptr<const XPathExpression_impl<string_type, string_adaptor> > ExpressionPtr;
  ExpressionPtr ptr_;
}; // class XPathExpressionPtr

namespace impl
{
template<class string_type, class string_adaptor>
class UnaryExpression
{
public:
  UnaryExpression(XPathExpression_impl<string_type, string_adaptor>* expr) :
      expr_(expr) { }

protected:
  ~UnaryExpression() 
  {
    delete expr_;
  } // ~UnaryExpression

  XPathExpression_impl<string_type, string_adaptor>* expr() const { return expr_; }

private:
  XPathExpression_impl<string_type, string_adaptor>* expr_;
}; // class UnaryExpression

template<class string_type, class string_adaptor>
class BinaryExpression
{
public:
  BinaryExpression(XPathExpression_impl<string_type, string_adaptor>* lhs, 
                   XPathExpression_impl<string_type, string_adaptor>* rhs) :
      lhs_(lhs), 
      rhs_(rhs) 
  { 
  } // BinaryExpression

protected:
  ~BinaryExpression() 
  { 
    delete lhs_;
    delete rhs_;
  } // ~BinaryExpression

  XPathExpression_impl<string_type, string_adaptor>* lhs() const { return lhs_; }
  XPathExpression_impl<string_type, string_adaptor>* rhs() const { return rhs_; }

private:
  XPathExpression_impl<string_type, string_adaptor>* lhs_;
  XPathExpression_impl<string_type, string_adaptor>* rhs_;
}; // class BinaryExpression

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
