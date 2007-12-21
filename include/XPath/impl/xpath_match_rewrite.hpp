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
      if(pred->type() == NUMBER)
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
