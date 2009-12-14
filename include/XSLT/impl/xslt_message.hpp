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
    MessageRedirectionFrame toMessageSink(context);
    execute_children(node, context);

    if(terminate_)
      throw SAX::SAXException("Stylesheet terminated by xsl:message");
  } // execute

private:
  bool terminate_;

  class MessageRedirectionFrame
  {
  public:
    MessageRedirectionFrame(ExecutionContext& context) : context_(context) { context_.redirectToMessageSink(); }
    ~MessageRedirectionFrame() { context_.revertFromMessageSink(); }

  private:
    ExecutionContext& context_;

    MessageRedirectionFrame();
    MessageRedirectionFrame(const MessageRedirectionFrame&);
    bool operator=(const MessageRedirectionFrame&);
  }; // class MessageRedirectionFrame
}; // class Message

} // namespace XSLT
} // namespace Arabica

#endif

