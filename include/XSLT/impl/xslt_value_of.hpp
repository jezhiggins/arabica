#ifndef ARABICA_XSLT_VALUE_OF_HPP
#define ARABICA_XSLT_VALUE_OF_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ValueOf : public Item
{
public:
  ValueOf(Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> expr,
          bool disable_output_escaping) :
    expr_(expr),
    disable_(disable_output_escaping)
  {
  } // ValueOf

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const
  {
    if(disable_)
      context.sink().disableOutputEscaping(true);

    context.sink().characters(expr_->evaluateAsString(node, context.xpathContext()));
    
    if(disable_)
      context.sink().disableOutputEscaping(false);
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> expr_;
  const bool disable_;
}; // class ValueOf

} // namespace XSLT
} // namespace Arabica
#endif

