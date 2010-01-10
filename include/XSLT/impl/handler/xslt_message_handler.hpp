#ifndef ARABICA_XSLT_MESSAGE_HANDLER_HPP
#define ARABICA_XSLT_MESSAGE_HANDLER_HPP

#include "../xslt_message.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class MessageHandler : public ItemContainerHandler<Message>
{
public:
  MessageHandler(CompilationContext& context) :
      ItemContainerHandler<Message>(context)
  {
  } // MessageHandler

protected:
  virtual Message* createContainer(const std::string& /* namespaceURI */,
                                   const std::string& /* localName */,
                                   const std::string& qName,
                                   const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "terminate", false, No, AllowedYesNo },
                                       { 0, false, 0, 0 } };
    return new Message(gatherAttributes(qName, atts, rules)["terminate"] == Yes);
  } // createContainer
}; // class MessageHandler

} // namespace XSLT
} // namespace Arabica

#endif 

