#ifndef ARABICA_XSLT_IF_HPP
#define ARABICA_XSLT_IF_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

class If : public ItemContainer
{
public:
  If(Arabica::XPath::XPathExpressionPtr<std::string> test) :
    test_(test)
  { 
  } // If

  virtual ~If() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    ChainStackFrame frame(context);
    if(test_->evaluateAsBool(node, context.xpathContext()))
      execute_children(node, context);
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<std::string> test_;
}; // class If

} // namespace XSLT
} // namespace Arabica
#endif

