#ifndef XSLT_FOR_EACH_HPP
#define XSLT_FOR_EACH_HPP

#include "xslt_item.hpp"
#include "xslt_sort.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ForEach : public ItemContainer,
                public Sortable
{
public:
  ForEach(const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& select) : 
    Sortable(),
    select_(select)
  {
  } // ForEach

  virtual ~ForEach() 
  {
  } // ForEach

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const
  {
    Arabica::XPath::XPathValue<string_type, string_adaptor> sel = select_->evaluate(node, context.xpathContext());
    if(sel.type() != Arabica::XPath::NODE_SET)
      throw SAX::SAXException("xsl:for-each must select a node set");

    Arabica::XPath::NodeSet<string_type, string_adaptor> nodes = sel.asNodeSet();
    sort(node, nodes, context);

    LastFrame last(context, nodes.size());
    for(size_t n = 0, e = nodes.size(); n != e; ++n)
    {
      ChainStackFrame frame(context);
      context.setPosition(nodes[n], n+1);
      execute_children(nodes[n], context);
    } // for ...
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> select_;
}; // class ForEach

} // namespace XSLT
} // namespace Arabica

#endif

