#ifndef ARABICA_XPATHIC_XPATH_UNION_HPP
#define ARABICA_XPATHIC_XPATH_UNION_HPP

#include "xpath_value.hpp"
#include <algorithm>

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class string_type, class string_adaptor>
class UnionExpression : private BinaryExpression<string_type, string_adaptor>, 
                        public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  UnionExpression(XPathExpression<string_type, string_adaptor>* lhs, 
                  XPathExpression<string_type, string_adaptor>* rhs) :
       BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    XPathValuePtr<string_type> p1 = baseT::lhs()->evaluate(context, executionContext);
    if(p1->type() != NODE_SET)
      throw RuntimeException("Union operator joins node-sets.  First argument is not a node-set.");
    XPathValuePtr<string_type> p2 = baseT::rhs()->evaluate(context, executionContext);
    if(p2->type() != NODE_SET)
      throw RuntimeException("Union operator joins node-sets.  Second argument is not a node-set.");

    NodeSet<string_type> ns1(p1->asNodeSet());
    NodeSet<string_type> ns2(p2->asNodeSet());

    // do the obvious optimizations
    if(ns1.empty())
      return wrap(ns2);
    if(ns2.empty())
      return wrap(ns1);

    ns1.to_document_order();
    ns2.to_document_order();
    typename NodeSet<string_type>::const_iterator n1 = ns1.begin(), n1e = ns1.end();
    typename NodeSet<string_type>::const_iterator n2 = ns2.begin(), n2e = ns2.end();

    NodeSet<string_type> result(true);

    while((n1 != n1e) && (n2 != n2e))
    {
      int c = compareNodes(*n1, *n2);
      if(c < 0)
        result.push_back(*n1++);
      else if(c > 0)
        result.push_back(*n2++);
      else
      { // same node, so bin out duplicate
        result.push_back(*n1++);
        ++n2;
      } // if ...
    } // while ...

    // pop on any left overs, leftovers
    std::copy(n1, n1e, std::back_inserter(result));
    std::copy(n2, n2e, std::back_inserter(result));

    return wrap(result);
  } // evaluate

private:
  XPathValuePtr<string_type> wrap(const NodeSet<string_type>& ns) const
  {
    return XPathValuePtr<string_type>(new NodeSetValue<string_type, string_adaptor>(ns));
  } // wrap
}; // UnionExpression

} // namespace impl
} // namespace XPath
} // namespace Arabica
#endif
