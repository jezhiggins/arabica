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
class UnionExpression : public BinaryExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  UnionExpression(XPathExpression_impl<string_type, string_adaptor>* lhs, 
                  XPathExpression_impl<string_type, string_adaptor>* rhs) :
       BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual ValueType type() const { return NODE_SET; }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    XPathValue<string_type, string_adaptor> p1 = baseT::lhs()->evaluate(context, executionContext);
    if(p1.type() != NODE_SET)
      throw RuntimeException("Union operator joins node-sets.  First argument is not a node-set.");
    XPathValue<string_type, string_adaptor> p2 = baseT::rhs()->evaluate(context, executionContext);
    if(p2.type() != NODE_SET)
      throw RuntimeException("Union operator joins node-sets.  Second argument is not a node-set.");

    NodeSet<string_type, string_adaptor> ns1(p1.asNodeSet());
    NodeSet<string_type, string_adaptor> ns2(p2.asNodeSet());

    // do the obvious optimizations
    if(ns1.empty())
      return wrap(ns2);
    if(ns2.empty())
      return wrap(ns1);

    ns1.insert(ns1.end()-1, ns2.begin(), ns2.end());
    ns1.to_document_order();

    return wrap(ns1);
  } // evaluate

private:
  XPathValue<string_type, string_adaptor> wrap(const NodeSet<string_type, string_adaptor>& ns) const
  {
    return XPathValue<string_type, string_adaptor>(new NodeSetValue<string_type, string_adaptor>(ns));
  } // wrap
}; // UnionExpression

} // namespace impl
} // namespace XPath
} // namespace Arabica
#endif
