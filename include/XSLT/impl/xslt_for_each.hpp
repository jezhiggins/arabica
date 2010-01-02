#ifndef XSLT_FOR_EACH_HPP
#define XSLT_FOR_EACH_HPP

#include "xslt_item.hpp"
#include "xslt_sort.hpp"

namespace Arabica
{
namespace XSLT
{

class ForEach : public ItemContainer,
                public Sortable
{
public:
  ForEach(const Arabica::XPath::XPathExpressionPtr<std::string>& select) : 
    Sortable(),
    select_(select)
  {
  } // ForEach

  virtual ~ForEach() 
  {
  } // ForEach

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    Arabica::XPath::XPathValue<std::string> sel = select_->evaluate(node, context.xpathContext());
    if(sel.type() != Arabica::XPath::NODE_SET)
      throw SAX::SAXException("xsl:for-each must select a node set");

    Arabica::XPath::NodeSet<std::string> nodes = sel.asNodeSet();
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
  Arabica::XPath::XPathExpressionPtr<std::string> select_;
}; // class ForEach

} // namespace XSLT
} // namespace Arabica

#endif

