#ifndef JEZUK_DOM_SimpleDOM_DOCUMENTEVENT_IMPL_H
#define JEZUK_DOM_SimpleDOM_DOCUMENTEVENT_IMPL_H

////////////////////////////
// C++ DocumentEvent implementation
////////////////////////////

#include <DOM/Node.hpp>
#include <DOM/Events/DocumentEvent.hpp>
#include <DOM/Simple/MutationEventImpl.hpp>
#include <DOM/DOMException.hpp>
#include <XML/XMLCharacterClasses.hpp>

//#include <iostream>

namespace Arabica
{
namespace SimpleDOM
{

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class DocumentEventImpl : virtual public Arabica::DOM::Events::DocumentEvent_impl<stringT, string_adaptorT>
{
  public:
    typedef Arabica::DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef Arabica::DOM::Text_impl<stringT, string_adaptorT> DOMText_implT;
    typedef Arabica::DOM::Document_impl<stringT, string_adaptorT> DOMDocument_implT;
    typedef Arabica::DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;
    typedef Arabica::DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;
    typedef Arabica::DOM::Events::Event<stringT, string_adaptorT> EventT;
    typedef Arabica::DOM::Events::EventTarget<stringT, string_adaptorT> EventTargetT;

    typedef Arabica::DOM::Events::Event_impl<stringT, string_adaptorT> Event_implT;
    typedef DocumentEventImpl<stringT, string_adaptorT> DocumentEventImplT;

    DocumentEventImpl()
    {
        //std::cout << std::endl << "born " << this << std::endl;
    } // DocumentEventImpl

    virtual ~DocumentEventImpl()
    {
        //std::cout << std::endl << "die  " << this << std::endl;
    }

    virtual Event_implT* createEvent(const char* eventType)
    {
      const stringT eT = string_adaptorT::construct_from_utf8(eventType);
      if (eT == string_adaptorT::construct_from_utf8("MutationEvent")) {
        return new MutationEventImpl<stringT, string_adaptorT>();
      }
      return NULL;
    }

  protected:

}; // class DocumentEventImpl

} // namespace SimpleDOM
} // namespace Arabica

#endif // JEZUK_DOM_SimpleDOM_EVENTTARGET_H
// end of file
