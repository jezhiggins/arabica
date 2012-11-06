#ifndef ARABICA_XSLT_APPLY_TEMPLATES_HPP
#define ARABICA_XSLT_APPLY_TEMPLATES_HPP

#include "xslt_compiled_stylesheet.hpp"
#include "xslt_sort.hpp"
#include "xslt_with_param.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ApplyTemplates : public Item,
                       public Sortable<string_type, string_adaptor>,
                       public WithParamable<string_type, string_adaptor>
{
  typedef Sortable<string_type, string_adaptor> SortableT;

public:
  ApplyTemplates(Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> select,
                 string_type& mode) :
    select_(select),
    mode_(mode)
  {
  } // ApplyTemplates

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const
  {
    ParamPasser<string_type, string_adaptor> passer(*this, node, context);

    if(!SortableT::has_sort() && select_ == 0)
    {
      if(node.hasChildNodes())
        context.stylesheet().applyTemplates(node.getChildNodes(), context, mode_);
      return;
    }

    Arabica::XPath::NodeSet<string_type, string_adaptor> nodes;
    if(select_ == 0)
      for(DOM::Node<string_type, string_adaptor> n = node.getFirstChild(); n != 0; n = n.getNextSibling())
        nodes.push_back(n);
    else
    {
      Arabica::XPath::XPathValue<string_type, string_adaptor> value = select_->evaluate(node, context.xpathContext());
      if(value.type() != Arabica::XPath::NODE_SET)
        throw std::runtime_error("apply-templates select expression is not a node-set");
      nodes = value.asNodeSet();
    }
    sort(node, nodes, context);
    context.stylesheet().applyTemplates(nodes, context, mode_);
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> select_;
  string_type mode_;
}; // class ApplyTemplates

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_APPLY_TEMPLATES_HPP

