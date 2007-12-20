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
  // match is a RelativeLocationPath
  //   foreach step in the steplist
  //     foreach predicate in the predicatelist
  //       should rewrite?
} // MatchExpr

} // namespace XPath

} // namespace Arabica

#endif
