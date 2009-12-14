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

class Variable_impl : public ItemContainer, public Variable_declaration
{
protected:
  Variable_impl(const std::string& name, 
                const Arabica::XPath::XPathExpressionPtr<std::string>& select,
                const Precedence& precedence) :
      name_(name),
      select_(select),
      precedence_(precedence)
  {
  } // Variable_impl
  
  virtual ~Variable_impl() { }

public:
  virtual const std::string& name() const { return name_; } 
  
  virtual Arabica::XPath::XPathValue<std::string> value(const DOM::Node<std::string>& node, 
                                                        ExecutionContext& context,
	                                                DOMSink& sink) const
  {
    if(select_)
      return select_->evaluate(node, context.xpathContext());

    execute_children(node, context);

    if(sink.node() == 0)
      return Arabica::XPath::StringValue<std::string, Arabica::default_string_adaptor<std::string> >::createValue("");

    Arabica::XPath::NodeSet<std::string> nodeset;
    for(DOM::Node<std::string> n = sink.node().getFirstChild(); n != 0; n = n.getNextSibling())
      nodeset.push_back(n);

    return Arabica::XPath::NodeSetValue<std::string, Arabica::default_string_adaptor<std::string> >::createValue(nodeset);
  } // value

  virtual const Precedence& precedence() const { return precedence_; }

private:
  std::string name_;
  Arabica::XPath::XPathExpressionPtr<std::string> select_;
  Precedence precedence_;
}; // Variable_impl

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_VARIABLE_IMPL_HPP

