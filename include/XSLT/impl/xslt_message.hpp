#ifndef ARABICA_XSLT_MESSAGE_HPP
#define ARABICA_XSLT_MESSAGE_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

class Message : public ItemContainer
{
public:
  Message(bool terminate) :
      terminate_(terminate)
  {
  } // Message

  virtual ~Message() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    context.redirectToMessageSink(true);
    execute_children(node, context);
    context.redirectToMessageSink(false);

    if(terminate_)
      throw SAX::SAXException("Stylesheet terminated by xsl:message");
  } // execute

private:
  bool terminate_;
}; // class Message

} // namespace XSLT
} // namespace Arabica

#endif

