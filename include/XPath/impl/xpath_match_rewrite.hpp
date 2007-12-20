#ifndef ARABICA_XPATHIC_MATCH_REWRITE_HPP
#define ARABICA_XPATHIC_MATCH_REWRITE_HPP

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
MatchExpr<string_type, string_adaptor>::MatchExpr(XPathExpression_impl<string_type, string_adaptor>* match, double priority) :
  match_(match), priority_(priority) 
{
  impl::StepExpression<string_type, string_adaptor>* step = static_cast<impl::StepExpression<string_type, string_adaptor>*>(match);
  // loop through predicates here
} // MatchExpr

} // namespace XPath

} // namespace Arabica

#endif
