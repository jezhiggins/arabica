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
class XPathExpression_impl;

namespace impl
{

template<class string_type, class string_adaptor>
class Expression_scanner
{
protected:
  Expression_scanner() { }
  Expression_scanner(const Expression_scanner&) { }
  ~Expression_scanner() { }

public:
  virtual void scan(const XPathExpression_impl<string_type, string_adaptor>* const expr) = 0;

private:
  bool operator==(const Expression_scanner&) const;
  Expression_scanner& operator=(const Expression_scanner&);
}; // class Expression_scanner

} // namespace impl

template<class string_type, class string_adaptor>
class XPathExpression_impl
{
protected:
  XPathExpression_impl() { }

public:
  virtual ~XPathExpression_impl() { }

  virtual ValueType type() const = 0;

  XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context) const
  {
    return evaluate(context, StaticExecutionContext());
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<string_type, string_adaptor>& context) const 
  { 
    return evaluateAsBool(context, StaticExecutionContext()); 
  }
  virtual double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context) const 
  { 
    return evaluateAsNumber(context, StaticExecutionContext()); 
  }
  virtual string_type evaluateAsString(const DOM::Node<string_type, string_adaptor>& context) const 
  { 
    return evaluateAsString(context, StaticExecutionContext()); 
  }
  virtual NodeSet<string_type, string_adaptor> evaluateAsNodeSet(const DOM::Node<string_type, string_adaptor>& context) const 
  { 
    return evaluateAsNodeSet(context, StaticExecutionContext()); 
  }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;

  virtual bool evaluateAsBool(const DOM::Node<string_type, string_adaptor>& context, 
															const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  { 
    return evaluate(context, executionContext).asBool(); 
  }
  virtual double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context, 
                                  const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  { 
    return evaluate(context, executionContext).asNumber(); 
  }
  virtual string_type evaluateAsString(const DOM::Node<string_type, string_adaptor>& context, 
                                       const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  { 
    return evaluate(context, executionContext).asString(); 
  }
  virtual NodeSet<string_type, string_adaptor> evaluateAsNodeSet(const DOM::Node<string_type, string_adaptor>& context, 
                                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  {
    return evaluate(context, executionContext).asNodeSet(); 
  }

  virtual void scan(impl::Expression_scanner<string_type, string_adaptor>& scanner) const { scanner.scan(this); }

private:
  static const ExecutionContext<string_type, string_adaptor>& StaticExecutionContext() 
  {
    static ExecutionContext<string_type, string_adaptor> executionContext;
    return executionContext;
  } // StaticExecutionContext

  XPathExpression_impl(const XPathExpression_impl&);
  bool operator==(const XPathExpression_impl&);
  XPathExpression_impl& operator=(const XPathExpression_impl&);
}; // class XPathExpression_impl

template<class string_type, class string_adaptor> class XPathExpressionPtr;

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XPathExpression
{ 
public:
  XPathExpression() : ptr_() { }
  explicit XPathExpression(XPathExpression_impl<string_type, string_adaptor>* xp) : ptr_(xp) { }
  XPathExpression(const XPathExpression& rhs) : ptr_(rhs.ptr_) { }
  XPathExpression& operator=(const XPathExpression& rhs)
  {
    ptr_ = rhs.ptr_;
    return *this;
  } // operator=

  ValueType type() const { return ptr_->type(); }

  const XPathExpression_impl<string_type, string_adaptor>* get() const { return ptr_.get(); }

  operator bool() const { return ptr_.get() != 0; }

  XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context) const
  {
    return ptr_->evaluate(context);
  } // evaluate

  bool evaluateAsBool(const DOM::Node<string_type, string_adaptor>& context) const
  {
    return ptr_->evaluateAsBool(context);
  } // evaluateAsBool

  double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context) const
  {
    return ptr_->evaluateAsNumber(context);
  } // evaluateAsNumber

  string_type evaluateAsString(const DOM::Node<string_type, string_adaptor>& context) const
  {
    return ptr_->evaluateAsString(context);
  } // evaluateAsString

  NodeSet<string_type, string_adaptor> evaluateAsNodeSet(const DOM::Node<string_type, string_adaptor>& context) const
  { 
    return ptr_->evaluate(context).asNodeSet(); 
  } // evaluateAsNodeSet


  XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context,
                                                   const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return ptr_->evaluate(context, executionContext);
  } // evaluate

  bool evaluateAsBool(const DOM::Node<string_type, string_adaptor>& context,
                      const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return ptr_->evaluateAsBool(context, executionContext);
  } // evaluateAsBool

  double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& context, 
                          const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return ptr_->evaluateAsNumber(context, executionContext);
  } // evaluateAsNumber

  string_type evaluateAsString(const DOM::Node<string_type, string_adaptor>& context, 
                               const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return ptr_->evaluateAsString(context, executionContext);
  } // evaluateAsString

  NodeSet<string_type, string_adaptor> evaluateAsNodeSet(const DOM::Node<string_type, string_adaptor>& context, 
                                                         const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  { 
    return ptr_->evaluate(context, executionContext).asNodeSet(); 
  } // evaluateAsNodeSet

private:
  typedef boost::shared_ptr<const XPathExpression_impl<string_type, string_adaptor> > ExpressionPtr;
  ExpressionPtr ptr_;

  explicit XPathExpression(ExpressionPtr ptr) : ptr_(ptr) { }

  friend class XPathExpressionPtr<string_type, string_adaptor>;
}; // class XPathExpression

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XPathExpressionPtr
{
public:
  explicit XPathExpressionPtr() : ptr_() { }
  explicit XPathExpressionPtr(const XPathExpression_impl<string_type, string_adaptor>* v) : ptr_(v) { }
  XPathExpressionPtr(const XPathExpression<string_type, string_adaptor>& rhs) : ptr_(rhs.ptr_) { }
  XPathExpressionPtr(const XPathExpressionPtr& rhs) : ptr_(rhs.ptr_) { }
  XPathExpressionPtr& operator=(const XPathExpression<string_type, string_adaptor>& rhs)
  {
    ptr_ = rhs.ptr_;
    return *this;
  } // operator=
  XPathExpressionPtr& operator=(const XPathExpressionPtr& rhs)
  {
    ptr_ = rhs.ptr_;
    return *this;
  } // operator=

  const XPathExpression_impl<string_type, string_adaptor>* operator->() const { return ptr_.get(); }

  operator bool() const { return (ptr_.get() != 0); }
  operator XPathExpression<string_type, string_adaptor>() const { return XPathExpression<string_type, string_adaptor>(ptr_); }

private:
  bool operator==(const XPathExpressionPtr&) const;

  typedef boost::shared_ptr<const XPathExpression_impl<string_type, string_adaptor> > ExpressionPtr;
  ExpressionPtr ptr_;
}; // class XPathExpressionPtr

namespace impl
{
template<class string_type, class string_adaptor>
class UnaryExpression : virtual public XPathExpression_impl<string_type, string_adaptor>
{
public:
  UnaryExpression(XPathExpression_impl<string_type, string_adaptor>* expr) :
      expr_(expr) { }

  virtual void scan(impl::Expression_scanner<string_type, string_adaptor>& scanner) const
  {
    expr_->scan(scanner);
    scanner.scan(this);
  } // scan

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
class BinaryExpression : virtual public XPathExpression_impl<string_type, string_adaptor>
{
public:
  BinaryExpression(XPathExpression_impl<string_type, string_adaptor>* lhs, 
                   XPathExpression_impl<string_type, string_adaptor>* rhs) :
      lhs_(lhs), 
      rhs_(rhs) 
  { 
  } // BinaryExpression

  virtual void scan(impl::Expression_scanner<string_type, string_adaptor>& scanner) const
  {
    lhs_->scan(scanner);
    rhs_->scan(scanner);
    scanner.scan(this);
  } // scan

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
