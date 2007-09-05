
#ifndef JEZUK_EVENTS_EVENTTARGET_H
#define JEZUK_EVENTS_EVENTTARGET_H
////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/ImplProxy.hpp>

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT> class Event;
template<class stringT> class EventListener;
template<class stringT> class EventTarget_impl;

template<class stringT>
class EventTarget : protected DOM::Proxy
{
  public:
    EventTarget() : Proxy(0) { }
    EventTarget(EventTarget_impl<stringT>* const impl) : Proxy(impl) { }
    EventTarget(const EventTarget& rhs) : Proxy(rhs) { }
    explicit EventTarget(const DOM::Node<stringT>& rhs) : Proxy(rhs.nImpl()) 
    {
      if(dynamic_cast<EventTarget_impl<stringT>*>(rhs.nImpl()) == 0)
        throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR); 
    } // DocumentTraversal
    virtual ~EventTarget() { }
    bool operator==(const EventTarget& rhs) const { return Proxy::operator==(rhs); } 
    bool operator!=(const EventTarget& rhs) const { return Proxy::operator!=(rhs); }
    bool operator==(int dummy) const { return Proxy::operator==(dummy); }
    bool operator!=(int dummy) const { return Proxy::operator!=(dummy); }

    EventTarget& operator=(const EventTarget& rhs) 
    {
      Proxy::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////////////////
    // EventTarget methods
    void addEventListener(const stringT type,
                          EventListener<stringT>& listener,
                          bool useCapture)
    {
      Impl()->addEventListener(type, listener, useCapture)
    } // addEventListener

    void removeEventListener(const stringT type,
                             EventListener<stringT>& listener,
                             bool useCapture)
    {
      Impl()->removeEventListener(type, listener, useCapture);
    } // removeEventListener

    bool dispatchEvent(Event<stringT>& event)
    {
      Impl()->dispatchEvent(event);
    } // dispatchEvent

  private:
    EventTarget_impl<stringT>* Impl() const { return dynamic_cast<EventTarget_impl<stringT>*>(impl()); }
}; // class EventTarget

//////////////////////////////////////////////////////////////////////
// Event_impl
template<class stringT>
class EventTarget_impl : virtual public Impl
{
    ///////////////////////////////////////////////////////////////
    // EventTarget methods
    virtual void addEventListener(const stringT type,
                                  EventListener<stringT>& listener,
                                  bool useCapture) = 0;

    virtual void removeEventListener(const stringT type,
                                     EventListener<stringT>& listener,
                                     bool useCapture) = 0;

    virtual bool dispatchEvent(Event<stringT>& event) = 0;
}; // class EventTarget_impl

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
