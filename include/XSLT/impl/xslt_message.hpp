#ifndef ARABICA_XSLT_MESSAGE_HPP
#define ARABICA_XSLT_MESSAGE_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class Message : public ItemContainer<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  Message(bool terminate) :
      terminate_(terminate)
  {
  } // Message

  virtual ~Message() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    RedirectionFrame toMessageSink(context);
    this->execute_children(node, context);

    if(terminate_)
      throw SAX::SAXException("Stylesheet terminated by xsl:message");
  } // execute

private:
  const bool terminate_;

  class RedirectionFrame
  {
  public:
    RedirectionFrame(ExecutionContext<string_type, string_adaptor>& context) : context_(context) { context_.redirectToMessageSink(); }
    ~RedirectionFrame() { context_.revertFromMessageSink(); }

  private:
    ExecutionContext<string_type, string_adaptor>& context_;

    RedirectionFrame();
    RedirectionFrame(const RedirectionFrame&);
    bool operator=(const RedirectionFrame&);
  }; // class RedirectionFrame
}; // class Message

} // namespace XSLT
} // namespace Arabica

#endif

