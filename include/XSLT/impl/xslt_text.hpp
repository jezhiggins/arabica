#ifndef ARABICA_XSLT_TEXT_HPP
#define ARABICA_XSLT_TEXT_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class Text : public Item<string_type, string_adaptor>
{
public:
  Text(bool disable_output_escaping) : 
    disable_(disable_output_escaping)
  { 
  } // Text

  Text(const string_type& text) :
      text_(text),
      disable_(false)
  {
  } // Text

  void set(const string_type& text) { text_ = text; }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& /* node */, 
		                   ExecutionContext<string_type, string_adaptor>& context) const
  {
    if(disable_)
      context.sink().disableOutputEscaping(true);

    context.sink().characters(text_);

    if(disable_)
      context.sink().disableOutputEscaping(false);
  } // execute

private:
  string_type text_;
  const bool disable_;
}; // class Text

} // namespace XSLT
} // namespace Arabica
#endif

