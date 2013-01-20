#ifndef JEZUK_DOM_SimpleDOM_DOCUMENTEVENT_IMPL_H
#define JEZUK_DOM_SimpleDOM_DOCUMENTEVENT_IMPL_H

////////////////////////////
// C++ DocumentEvent implementation
////////////////////////////

#include <DOM/Node.hpp>
#include <DOM/Events/DocumentEvent.hpp>
#include <DOM/Events/MutationEventImpl.hpp>
#include <DOM/DOMException.hpp>
#include <XML/XMLCharacterClasses.hpp>

//#include <iostream>

namespace Arabica
{
namespace DOM
{
namespace Events
{

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class DocumentImpl;

template<class stringT, class string_adaptorT>
class DocumentEventImpl : virtual public DOM::Events::DocumentEvent_impl<stringT, string_adaptorT>
{
  public:
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::Text_impl<stringT, string_adaptorT> DOMText_implT;
    typedef DOM::Document_impl<stringT, string_adaptorT> DOMDocument_implT;
    typedef DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;
    typedef DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;
    typedef DOM::Events::Event<stringT, string_adaptorT> EventT;
    typedef DOM::Events::EventTarget<stringT, string_adaptorT> EventTargetT;
    typedef DOM::Events::DocumentEventImpl<stringT, string_adaptorT> DocumentEventImplT;

    DocumentEventImpl()
    {
        //std::cout << std::endl << "born " << this << std::endl;
    } // DocumentEventImpl
    
    virtual ~DocumentEventImpl() 
    { 
        //std::cout << std::endl << "die  " << this << std::endl;
    }

    virtual Event_impl<stringT, string_adaptorT>* createEvent(const stringT& eventType)
    {
      if (eventType == string_adaptorT::construct_from_utf8("MutationEvent")) {
        return new MutationEventImpl<stringT, string_adaptorT>();
      }
      return NULL;
    }

  protected:

}; // class DocumentEventImpl

} // namespace DOM
} // namespace Events
} // namespace Arabica

#endif // JEZUK_DOM_SimpleDOM_EVENTTARGET_H
// end of file
