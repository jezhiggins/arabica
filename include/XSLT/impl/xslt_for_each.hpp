#ifndef XSLT_FOR_EACH_HPP
#define XSLT_FOR_EACH_HPP

#include "xslt_item.hpp"
#include "xslt_sort.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class ForEach : public ItemContainer,
                public Sortable<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor; 

  typedef Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> XPathExpressionPtr;
  typedef Arabica::XPath::XPathValue<string_type, string_adaptor> XPathValue;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;

  ForEach(const XPathExpressionPtr& select) : 
    Sortable<stringT, adaptorT>(),
    select_(select)
  {
  } // ForEach

  virtual ~ForEach() 
  {
  } // ForEach

  virtual void execute(const DOMNode& node, 
                       ExecutionContext& context) const
  {
    XPathValue sel = select_->evaluate(node, context.xpathContext());
    if(sel.type() != Arabica::XPath::NODE_SET)
      throw SAX::SAXException("xsl:for-each must select a node set");

    NodeSet nodes = sel.asNodeSet();
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
  XPathExpressionPtr select_;
}; // class ForEach

} // namespace XSLT
} // namespace Arabica

#endif

