#ifndef ARABICA_XSLT_VARIABLE_IMPL_HPP
#define ARABICA_XSLT_VARIABLE_IMPL_HPP

#include <XPath/XPath.hpp>
#include <memory>
#include "xslt_item.hpp"
#include "xslt_execution_context.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class Variable_impl : public ItemContainer, public Variable_declaration<string_type, string_adaptor>
{
protected:
  typedef Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> XPathExpressionPtr;
  typedef Arabica::XPath::XPathValue<string_type, string_adaptor> XPathValue;
  typedef Arabica::XPath::StringValue<string_type, string_adaptor> StringValue;
  typedef Arabica::XPath::NodeSetValue<string_type, string_adaptor> NodeSetValue;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;

  Variable_impl(const string_type& name, 
                const XPathExpressionPtr& select,
                const Precedence& precedence) :
      name_(name),
      select_(select),
      precedence_(precedence)
  {
  } // Variable_impl
  
  virtual ~Variable_impl() { }

public:
  virtual const string_type& name() const { return name_; } 
  
  virtual XPathValue value(const DOMNode& node, 
                           ExecutionContext& context,
	                         DOMSink<string_type, string_adaptor>& sink) const
  {
    if(select_)
      return select_->evaluate(node, context.xpathContext());

    execute_children(node, context);

    if(sink.node() == 0)
      return StringValue::createValue("");

    NodeSet nodeset;
    for(DOMNode n = sink.node().getFirstChild(); n != 0; n = n.getNextSibling())
      nodeset.push_back(n);

    return NodeSetValue::createValue(nodeset);
  } // value

  virtual const Precedence& precedence() const { return precedence_; }

private:
  string_type name_;
  XPathExpressionPtr select_;
  Precedence precedence_;
}; // Variable_impl

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_VARIABLE_IMPL_HPP

