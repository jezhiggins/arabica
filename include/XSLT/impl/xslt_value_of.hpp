#ifndef ARABICA_XSLT_VALUE_OF_HPP
#define ARABICA_XSLT_VALUE_OF_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

class ValueOf : public Item
{
public:
  ValueOf(Arabica::XPath::XPathExpressionPtr<std::string> expr,
          bool disable_output_escaping) :
    expr_(expr),
    disable_(disable_output_escaping)
  {
  } // ValueOf

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    if(disable_)
      context.sink().disableOutputEscaping(true);

    context.sink().characters(expr_->evaluateAsString(node, context.xpathContext()));
    
    if(disable_)
      context.sink().disableOutputEscaping(false);
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<std::string> expr_;
  bool disable_;
}; // class ValueOf

} // namespace XSLT
} // namespace Arabica
#endif

