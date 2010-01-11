#ifndef ARABICA_XSLT_TEXT_HPP
#define ARABICA_XSLT_TEXT_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

class Text : public Item
{
public:
  Text(bool disable_output_escaping) : 
    disable_(disable_output_escaping)
  { 
  } // Text

  Text(const std::string& text) :
      text_(text),
      disable_(false)
  {
  } // Text

  void set(const std::string& text) { text_ = text; }

  virtual void execute(const DOM::Node<std::string>& /* node */, 
		       ExecutionContext& context) const
  {
    if(disable_)
      context.sink().disableOutputEscaping(true);

    context.sink().characters(text_);

    if(disable_)
      context.sink().disableOutputEscaping(false);
  } // execute

private:
  std::string text_;
  bool disable_;
}; // class Text

} // namespace XSLT
} // namespace Arabica
#endif

