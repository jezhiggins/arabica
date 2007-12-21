#ifndef ARABICA_XPATHIC_MATCH_REWRITE_HPP
#define ARABICA_XPATHIC_MATCH_REWRITE_HPP

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class ReplacementExpression : public XPathExpression_impl<string_type, string_adaptor>
{
public:
  ReplacementExpression(impl::NodeTest<string_type, string_adaptor>* test, 
                        XPathExpression_impl<string_type, string_adaptor>* pred) 
  {
    test_ = new impl::TestStepExpression<string_type, string_adaptor>(CHILD, test, pred);
  } // ReplacementExpression

  ~ReplacementExpression()
  {
    delete test_;
  } // ~ReplacementExpression

  virtual ValueType type() const { return BOOL; }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                                           const ExecutionContext<string_type, string_adaptor>& executionContext) const 
  {
    DOM::Node<string_type, string_adaptor> parent = context.getParentNode();
    NodeSet<string_type, string_adaptor> nodes = test_->evaluateAsNodeSet(parent, executionContext);
    bool found = false;
    for(typename NodeSet<string_type, string_adaptor>::const_iterator n = nodes.begin(), ne = nodes.end(); 
        !found && (n != ne); ++n)
      found = (context == *n);
    return XPathValue<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(found));  
  } // evaluate

private:
  impl::TestStepExpression<string_type, string_adaptor>* test_;
}; // class ReplacementExpression

namespace impl
{
  template<class string_type, class string_adaptor>
  class PositionFnScanner : public Expression_scanner<string_type, string_adaptor>
  {
  public:
    PositionFnScanner() : found_(false) { }

    bool found() const { return found_; }

    virtual void scan(const XPathExpression_impl<string_type, string_adaptor>* const expr)
    {
      const FunctionHolder<string_type, string_adaptor>* const fn = dynamic_cast<const FunctionHolder<string_type, string_adaptor>* const>(expr);
      if(fn == 0)
        return;

      if(!string_adaptor::empty(fn->namespace_uri()))
        return;

      found_ = found_ || ((fn->name() == FN_POSITION) || (fn->name() == FN_LAST));
    } // scan

  private:
    bool found_;

    static const string_type FN_POSITION;
    static const string_type FN_LAST;
  }; // class PositionFnScanner

  template<class string_type, class string_adaptor>
  const string_type PositionFnScanner<string_type, string_adaptor>::FN_POSITION = string_adaptor::construct_from_utf8("position");
  template<class string_type, class string_adaptor>
  const string_type PositionFnScanner<string_type, string_adaptor>::FN_LAST = string_adaptor::construct_from_utf8("last");

  template<class string_type, class string_adaptor>
  bool should_rewrite(XPathExpression_impl<string_type, string_adaptor>* expr)
  {
    if(expr->type() == NUMBER)
      return true;

    PositionFnScanner<string_type, string_adaptor> scanner;
    expr->scan(scanner);
    return scanner.found();
  } // should_rewrite
} // namespace impl

template<class string_type, class string_adaptor>
MatchExpr<string_type, string_adaptor>::MatchExpr(XPathExpression_impl<string_type, string_adaptor>* match, double priority) :
  match_(match), priority_(priority) 
{
  typedef impl::RelativeLocationPath<string_type, string_adaptor> RelativeLocation;
  typedef impl::StepList<string_type, string_adaptor> StepList;
  typedef impl::TestStepExpression<string_type, string_adaptor> Step;
  typedef XPathExpression_impl<string_type, string_adaptor> Expression;
  typedef std::vector<Expression*> Predicates;
  // match is a RelativeLocationPath
  RelativeLocation* path = dynamic_cast<RelativeLocation*>(match);
  //   foreach step in the steplist
  StepList& steps = path->steps_;
  for(StepList::const_iterator s = steps.begin(), se = steps.end(); s != se; ++s)
  {
  //     foreach predicate in the predicatelist
    Step* step = dynamic_cast<Step*>(*s);
    if(step->has_predicates() == false)
      continue;

    Predicates& predicates = step->predicates_;
    for(Predicates::iterator p = predicates.begin(), pe = predicates.end(); p != pe; ++p)
    {
  //       should rewrite?
      Expression* pred = *p;
      if(impl::should_rewrite<string_type, string_adaptor>(pred))
      {
        Expression* replacement_expression = new ReplacementExpression<string_type, string_adaptor>(step->test_->clone(), pred);
        // replacement_expression now owns pred
        *p = replacement_expression;
      } // if ...
    } // for(Predicates::iterator ...
  } // for(StepList::const_iterator ...
} // MatchExpr

} // namespace XPath

} // namespace Arabica

#endif
