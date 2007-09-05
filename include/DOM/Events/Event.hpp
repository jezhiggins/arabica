#ifndef JEZUK_EVENTS_EVENT_H
#define JEZUK_EVENTS_EVENT_H

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT> class Event_impl;

template<class stringT>
class Event : protected DOM::Proxy
{
  public:
    Event() : Proxy(0) { }
    Event(Event_impl<stringT>* const impl) : Proxy(impl) { }
    Event(const Event& rhs) : Proxy(rhs) { }
    virtual ~Event() { }
    bool operator==(const Event& rhs) const { return Proxy::operator==(rhs); } 
    bool operator!=(const Event& rhs) const { return Proxy::operator!=(rhs); }
    bool operator==(int dummy) const { return Proxy::operator==(dummy); }
    bool operator!=(int dummy) const { return Proxy::operator!=(dummy); }

    Event& operator=(const Event& rhs) 
    {
      Proxy::operator=(rhs);
      return *this;
    } // operator=

    /////////////////////////////////////////////
    // Event methods
    enum Phase
    {
      CAPTURING_PHASE = 1,
      AT_TARGET = 2,
      BUBBLING_PHASE = 3
    }; // enum Phase

    stringT getType() const { return Impl()->getType(); }

    EventTarget<stringT> getTarget() const { return Impl()->getTarget(); }

    EventTarget<stringT> getCurrentTarget() const { return Impl()->getCurrentTarget(); }

    Phase getEventPhase() const { return Impl()->getEventPhase(); }

    bool getBubbles() const { return Impl()->getBubbles(); }

    bool getCancelable() const { return Impl()->getCancelable(); }

    long getTimeStamp() const { return Impl()->getTimeStamp(); }

    void stopPropagation() { return Impl()->stopPropagation(); }

    void preventDefault() { return Impl()->preventDefault(); }

    void initEvent(const stringT& eventTypeArg, bool canBubble, bool cancelable) 
    {
      return Impl()->initEvent(eventTypeArg, canBubble, cancelable);
    } // initEvent

  protected:
    Event_impl<stringT>* Impl() const { return dynamic_cast<Event_impl<stringT>*>(impl()); }
}; // class Event

///////////////////////////////////////////////////////////
// Event_impl
template<class stringT>
class Event_impl : virtual public Impl
{
  public:
    //////////////////////////////////////////////////
    // Event methods
    virtual stringT getType() const = 0;

    virtual EventTarget<stringT> getTarget() const  = 0;

    virtual EventTarget<stringT> getCurrentTarget() const = 0;

    virtual Event<stringT>::Phase getEventPhase() const = 0;

    virtual bool getBubbles() const = 0;

    virtual bool getCancelable() const = 0;

    virtual long getTimeStamp() const = 0;

    virtual void stopPropagation() = 0;

    virtual void preventDefault() = 0;

    virtual void initEvent(const stringT& eventTypeArg, bool canBubble, bool cancelable) = 0;
}; // class Event_impl

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
// end of file
