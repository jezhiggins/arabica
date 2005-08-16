#ifndef ARABICA_XPATHIC_XPATH_UNION_HPP
#define ARABICA_XPATHIC_XPATH_UNION_HPP

#include "xpath_value.hpp"
#include <algorithm>

namespace Arabica
{
namespace XPath
{

class UnionExpression : private BinaryExpression<std::string>, public XPathExpression<std::string>
{
public:
  UnionExpression(XPathExpression<std::string>* lhs, XPathExpression<std::string>* rhs) :
       BinaryExpression<std::string>(lhs, rhs) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, 
                                              const ExecutionContext& executionContext) const
  {
    XPathValuePtr<std::string> p1 = lhs()->evaluate(context, executionContext);
    if(p1->type() != NODE_SET)
      throw RuntimeException("Union operator joins node-sets.  First argument is not a node-set.");
    XPathValuePtr<std::string> p2 = rhs()->evaluate(context, executionContext);
    if(p2->type() != NODE_SET)
      throw RuntimeException("Union operator joins node-sets.  Second argument is not a node-set.");

    NodeSet<std::string> ns1(p1->asNodeSet());
    NodeSet<std::string> ns2(p2->asNodeSet());

    // do the obvious optimizations
    if(ns1.empty())
      return wrap(ns2);
    if(ns2.empty())
      return wrap(ns1);

    ns1.to_document_order();
    ns2.to_document_order();
    NodeSet<std::string>::const_iterator n1 = ns1.begin(), n1e = ns1.end();
    NodeSet<std::string>::const_iterator n2 = ns2.begin(), n2e = ns2.end();

    NodeSet<std::string> result(true);

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
  XPathValuePtr<std::string> wrap(const NodeSet<std::string>& ns) const
  {
    return XPathValuePtr<std::string>(new NodeSetValue(ns));
  } // wrap
}; // UnionExpression

} // namespace XPath

} // namespace Arabica
#endif
