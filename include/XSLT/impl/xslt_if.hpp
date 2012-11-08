#ifndef ARABICA_XSLT_IF_HPP
#define ARABICA_XSLT_IF_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class If : public ItemContainer<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor; 

  If(Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> test) :
    test_(test)
  { 
  } // If

  virtual ~If() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const
  {
    ChainStackFrame frame(context);
    if(test_->evaluateAsBool(node, context.xpathContext()))
      execute_children(node, context);
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> test_;
}; // class If

} // namespace XSLT
} // namespace Arabica
#endif

