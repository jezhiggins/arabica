#ifndef JEZUK_DOM_SimpleDOM_EVENT_IMPL_H
#define JEZUK_DOM_SimpleDOM_EVENT_IMPL_H

////////////////////////////
// C++ Event implementation
////////////////////////////

#include <DOM/Events/Event.hpp>
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
class EventImpl : virtual public DOM::Events::Event_impl<stringT, string_adaptorT>
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
    typedef DOM::Events::EventImpl<stringT, string_adaptorT> EventImplT;

    EventImpl() : stopped_(false), defaultsPrevented_(false), timeStamp_(0)
    {
        //std::cout << std::endl << "born " << this << std::endl;
    } // EventImpl
    
    virtual ~EventImpl() 
    { 
        //std::cout << std::endl << "die  " << this << std::endl;
    }

    virtual stringT getType() const
    {
      return type_;
    }

    virtual EventTargetT getTarget() const 
    {
      return target_;
    }

    virtual EventTargetT getCurrentTarget() const
    {
      return currTarget_;
    }

    virtual typename EventT::Phase getEventPhase() const 
    {
      return phase_;
    }

    virtual bool getBubbles() const 
    {
      return canBubble_;
    }

    virtual bool getCancelable() const
    {
      return canCancel_;
    }

    virtual long getTimeStamp() const 
    {
      return timeStamp_;
    }

    virtual void stopPropagation()
    {
      if (canCancel_)
        stopped_ = true;
    }

    virtual void preventDefault() 
    {
      defaultsPrevented_ = true;
    }

    virtual void initEvent(const stringT& eventTypeArg, bool canBubble, bool cancelable)
    {
      type_ = eventTypeArg;
      canBubble_ = canBubble;
      canCancel_ = cancelable;
    }

  protected:
    stringT type_;
		EventTargetT target_;
		EventTargetT currTarget_;
		typename EventT::Phase phase_;
		long timeStamp_;
    bool canBubble_;
    bool canCancel_;
    bool stopped_;
    bool defaultsPrevented_;
}; // class EventImpl

} // namespace DOM
} // namespace Events
} // namespace Arabica

#endif // JEZUK_DOM_SimpleDOM_EVENTTARGET_H
// end of file
