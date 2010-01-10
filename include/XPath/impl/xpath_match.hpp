#ifndef ARABICA_XPATHIC_MATCH_HPP
#define ARABICA_XPATHIC_MATCH_HPP

#include <vector>
#include "xpath_expression.hpp"
#include "xpath_value.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class MatchExpr
{
public:
  MatchExpr(XPathExpression_impl<string_type, string_adaptor>* match, double priority);
  MatchExpr(const MatchExpr& rhs) :
    match_(rhs.match_), priority_(rhs.priority_) { } 
  MatchExpr& operator=(const MatchExpr& rhs)
  { match_ = rhs.match_; priority_ = rhs.priority_; return *this; }

  double priority() const { return priority_; }
  bool evaluate(const DOM::Node<string_type, string_adaptor>& context,
                const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return match_.evaluateAsBool(context, executionContext);
  } // evaluate

  void override_priority(double p) { priority_ = p; }

private:
  XPathExpression<string_type, string_adaptor> match_;
  double priority_;

  MatchExpr();
  bool operator==(const MatchExpr&) const;
}; // MatchExpr

namespace impl
{

template<class string_type, class string_adaptor>
class MatchExpressionWrapper : public XPathExpression_impl<string_type, string_adaptor>
{
public:
  MatchExpressionWrapper(XPathExpression_impl<string_type, string_adaptor>* expr, double priority)
  {
    add_match(expr, priority);
  } // MatchExpressionWrapper

  MatchExpressionWrapper(XPathExpression_impl<string_type, string_adaptor>* expr)
  {
    add_matches(expr);
  } // MatchExpressionWrapper

  virtual ValueType type() const { return BOOL; }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& /* context */,
							   const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    throw std::runtime_error("MatchExpressionWrapper - you should never see this");
  } // evaluate

  const std::vector<MatchExpr<string_type, string_adaptor> >& matches() const
  {
    return matches_;
  } // matches

  void add_match(XPathExpression_impl<string_type, string_adaptor>* match, double priority) 
  {
    matches_.push_back(MatchExpr<string_type, string_adaptor>(match, priority));
  } // add_match

  void add_matches(XPathExpression_impl<string_type, string_adaptor>* wrapper) 
  {
    const std::vector<MatchExpr<string_type, string_adaptor> >& more = static_cast<impl::MatchExpressionWrapper<string_type, string_adaptor>*>(wrapper)->matches();
    for(typename std::vector<MatchExpr<string_type, string_adaptor> >::const_iterator m = more.begin(), me = more.end(); m != me; ++m)
      matches_.push_back(*m);
    delete wrapper;
  } // add_matches

private:
  std::vector<MatchExpr<string_type, string_adaptor> >  matches_;

  MatchExpressionWrapper();
  MatchExpressionWrapper(const MatchExpressionWrapper&);
  MatchExpressionWrapper& operator=(const MatchExpressionWrapper&);
  bool operator==(const MatchExpressionWrapper&) const;
}; // class MatchExpressionWrapper

} // namespace impl 
} // namespace XPath
} // namespace Arabica

#endif
