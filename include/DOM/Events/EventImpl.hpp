#ifndef JEZUK_DOM_SimpleDOM_EVENT_IMPL_H
#define JEZUK_DOM_SimpleDOM_EVENT_IMPL_H

////////////////////////////
// C++ Event implementation
////////////////////////////

#include <DOM/Events/Event.hpp>
#include <DOM/DOMException.hpp>
#include <XML/XMLCharacterClasses.hpp>

#ifdef _WIN32
# ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#   define __UNDEF_LEAN_AND_MEAN
# endif
# include <windows.h>
# ifdef __UNDEF_LEAN_AND_MEAN
#   undef WIN32_LEAN_AND_MEAN
#   undef __UNDEF_LEAN_AND_MEAN
# endif
#else
# include <sys/time.h>
#endif
//#include <iostream>

namespace Arabica
{
namespace DOM
{
namespace Events
{

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class DocumentImpl;
template<class stringT, class string_adaptorT> class EventTargetImpl;

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

    EventImpl() : timeStamp_(0), stopped_(false), defaultsPrevented_(false)
    {
        //std::cout << std::endl << "born " << this << std::endl;
        timeStamp_ = timeStamp();
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

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef()
    {
      ++refCount_;
    } // addRef

    virtual void releaseRef()
    {
      if(--refCount_ == 0)
        delete this;
    } // releaseRef

  protected:
  
    virtual unsigned long long timeStamp() 
    {
      unsigned long long time = 0;
#ifdef _WIN32
      FILETIME tv;
      GetSystemTimeAsFileTime(&tv); 
      time = (((uint64_t) tv.dwHighDateTime) << 32) + tv.dwLowDateTime;
      time /= 10000;
#else
      struct timeval tv;
      gettimeofday(&tv, NULL);
      time += tv.tv_sec * 1000;
      time += tv.tv_usec / 1000;
#endif
      return time;
    }

    stringT type_;
    EventTargetT target_;
    EventTargetT currTarget_;
    typename EventT::Phase phase_;
    unsigned long long timeStamp_;
    bool canBubble_;
    bool canCancel_;
    bool stopped_;
    bool defaultsPrevented_;
    unsigned long refCount_;
    
    friend class EventTargetImpl<stringT, string_adaptorT>;
}; // class EventImpl

} // namespace DOM
} // namespace Events
} // namespace Arabica

#endif // JEZUK_DOM_SimpleDOM_EVENTTARGET_H
// end of file
