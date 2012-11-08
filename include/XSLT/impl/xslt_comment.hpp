#ifndef ARABICA_XSLT_COMMENT_HPP
#define ARABICA_XSLT_COMMENT_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class Comment : public ItemContainer<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor; 

  Comment() { }
  virtual ~Comment() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    context.sink().start_comment();

    execute_children(node, context);

    context.sink().end_comment();
  } // execute
}; // class Comment

} // namespace XSLT
} // namespace Arabica

#endif

