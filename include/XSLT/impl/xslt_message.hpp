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
    RedirectionFrame toMessageSink(context);
    execute_children(node, context);

    if(terminate_)
      throw SAX::SAXException("Stylesheet terminated by xsl:message");
  } // execute

private:
  bool terminate_;

  class RedirectionFrame
  {
  public:
    RedirectionFrame(ExecutionContext& context) : context_(context) { context_.redirectToMessageSink(); }
    ~RedirectionFrame() { context_.revertFromMessageSink(); }

  private:
    ExecutionContext& context_;

    RedirectionFrame();
    RedirectionFrame(const RedirectionFrame&);
    bool operator=(const RedirectionFrame&);
  }; // class RedirectionFrame
}; // class Message

} // namespace XSLT
} // namespace Arabica

#endif

