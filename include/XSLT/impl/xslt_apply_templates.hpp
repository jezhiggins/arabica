#ifndef ARABICA_XSLT_APPLY_TEMPLATES_HPP
#define ARABICA_XSLT_APPLY_TEMPLATES_HPP

#include "xslt_compiled_stylesheet.hpp"
#include "xslt_sort.hpp"
#include "xslt_with_param.hpp"

namespace Arabica
{
namespace XSLT
{

class ApplyTemplates : public Item,
                       public Sortable,
                       public WithParamable
{
public:
  ApplyTemplates(Arabica::XPath::XPathExpressionPtr<std::string> select,
                 std::string& mode) :
    select_(select),
    mode_(mode)
  {
  } // ApplyTemplates

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    ParamPasser passer(*this, node, context);

    if(!has_sort() && select_ == 0)
    {
      if(node.hasChildNodes())
        context.stylesheet().applyTemplates(node.getChildNodes(), context, mode_);
      return;
    }

    Arabica::XPath::NodeSet<std::string> nodes;
    if(select_ == 0)
      for(DOM::Node<std::string> n = node.getFirstChild(); n != 0; n = n.getNextSibling())
        nodes.push_back(n);
    else
    {
      Arabica::XPath::XPathValue<std::string> value = select_->evaluate(node, context.xpathContext());
      if(value.type() != Arabica::XPath::NODE_SET)
        throw std::runtime_error("apply-templates select expression is not a node-set");
      nodes = value.asNodeSet();
    }
    sort(node, nodes, context);
    context.stylesheet().applyTemplates(nodes, context, mode_);
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<std::string> select_;
  std::string mode_;
}; // class ApplyTemplates

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_APPLY_TEMPLATES_HPP

