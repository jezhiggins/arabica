#ifndef ARABICA_XSLT_COMMENT_HPP
#define ARABICA_XSLT_COMMENT_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class Comment : public ItemContainer
{
public:
  Comment() { }
  virtual ~Comment() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext& context) const
  {
    context.sink().start_comment();

    execute_children(node, context);

    context.sink().end_comment();
  } // execute
}; // class Comment

} // namespace XSLT
} // namespace Arabica

#endif

