
#ifndef JEZUK_EVENTS_EVENTTARGET_H
#define JEZUK_EVENTS_EVENTTARGET_H
////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Proxy.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT, class string_adaptorT> class Event;
template<class stringT, class string_adaptorT> class EventListener;
template<class stringT, class string_adaptorT> class EventTarget_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
  class EventTarget : protected Arabica::DOM::Proxy<EventTarget_impl<stringT, string_adaptorT> >
{
  public:
    typedef EventTarget_impl<stringT, string_adaptorT> EventTarget_implT;
    typedef Event<stringT, string_adaptorT> EventT;
    typedef EventListener<stringT, string_adaptorT> EventListenerT;
    typedef DOM::Proxy<EventTarget_implT> proxy_t;

    EventTarget() : proxy_t(0) { }
    EventTarget(EventTarget_implT* const impl) : proxy_t(impl) { }
    EventTarget(const EventTarget& rhs) : proxy_t(rhs) { }
  explicit EventTarget(const DOM::Node<stringT, string_adaptorT>& rhs) : proxy_t(dynamic_cast<EventTarget_implT*>(rhs.underlying_impl()))
    {
      if(dynamic_cast<EventTarget_implT*>(rhs.underlying_impl()) == 0)
        throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR); 
    }
    virtual ~EventTarget() { }
    bool operator==(const EventTarget& rhs) const { return proxy_t::operator==(rhs); } 
    bool operator!=(const EventTarget& rhs) const { return proxy_t::operator!=(rhs); }
    bool operator==(int dummy) const { return proxy_t::operator==(dummy); }
    bool operator!=(int dummy) const { return proxy_t::operator!=(dummy); }

    EventTarget& operator=(const EventTarget& rhs) 
    {
      proxy_t::operator=(rhs);
      return *this;
    } // operator=

#if 0
    DOM::Node<stringT> asNode() {
      return DOM::Node<stringT>(dynamic_cast<Node_impl<stringT, string_adaptorT>*>(proxy_t::operator*()));
    }
#endif
    ///////////////////////////////////////////////////////////////
    // EventTarget methods
    void addEventListener(const stringT type,
                          EventListenerT& listener,
                          bool useCapture)
    {
      Impl()->addEventListener(type, listener, useCapture);
    } // addEventListener

    void removeEventListener(const stringT type,
                             EventListenerT& listener,
                             bool useCapture)
    {
      Impl()->removeEventListener(type, listener, useCapture);
    } // removeEventListener

    bool dispatchEvent(EventT& event)
    {
      return Impl()->dispatchEvent(event);
    } // dispatchEvent
  
//  private:
  EventTarget_implT* Impl() const { return dynamic_cast<EventTarget_implT*>(proxy_t::operator*()); }
}; // class EventTarget

//////////////////////////////////////////////////////////////////////
// Event_impl
template<class stringT, class string_adaptorT>
class EventTarget_impl
{
  public:
    typedef Event<stringT, string_adaptorT> EventT;
    typedef EventListener<stringT, string_adaptorT> EventListenerT;

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() = 0;
    virtual void releaseRef() = 0;

    ///////////////////////////////////////////////////////////////
    // EventTarget methods
    virtual void addEventListener(const stringT type,
                                  EventListenerT& listener,
                                  bool useCapture) = 0;

    virtual void removeEventListener(const stringT type,
                                     EventListenerT& listener,
                                     bool useCapture) = 0;

    virtual bool dispatchEvent(EventT& event) = 0;
}; // class EventTarget_impl

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
