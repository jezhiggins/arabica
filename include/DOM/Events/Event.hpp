#ifndef JEZUK_EVENTS_EVENT_H
#define JEZUK_EVENTS_EVENT_H

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT, class string_adaptorT> class Event_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class Event : protected Arabica::DOM::Proxy<Event_impl<stringT, string_adaptorT> >
{
  public:
    typedef Event_impl<stringT, string_adaptorT> Event_implT;
    typedef DOM::Proxy<Event_implT> proxy_t;

    Event() : proxy_t(0) { }
    Event(Event_impl<stringT, string_adaptorT>* const impl) : proxy_t(impl) { }
    Event(const Event& rhs) : proxy_t(rhs) { }
    virtual ~Event() { }
    bool operator==(const Event& rhs) const { return proxy_t::operator==(rhs); } 
    bool operator!=(const Event& rhs) const { return proxy_t::operator!=(rhs); }
    bool operator==(int dummy) const { return proxy_t::operator==(dummy); }
    bool operator!=(int dummy) const { return proxy_t::operator!=(dummy); }

    Event& operator=(const Event& rhs) 
    {
      proxy_t::operator=(rhs);
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

    EventTarget<stringT, string_adaptorT> getTarget() const { return Impl()->getTarget(); }

    EventTarget<stringT, string_adaptorT> getCurrentTarget() const { return Impl()->getCurrentTarget(); }

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

//  protected:
  Event_impl<stringT, string_adaptorT>* Impl() const { return dynamic_cast<Event_impl<stringT, string_adaptorT>*>(proxy_t::operator*()); }
}; // class Event

///////////////////////////////////////////////////////////
// Event_impl
template<class stringT, class string_adaptorT>
class Event_impl
{
  public:
    //////////////////////////////////////////////////
    // Event methods
    virtual stringT getType() const = 0;

    virtual EventTarget<stringT, string_adaptorT> getTarget() const  = 0;

    virtual EventTarget<stringT, string_adaptorT> getCurrentTarget() const = 0;

    virtual typename Event<stringT, string_adaptorT>::Phase getEventPhase() const = 0;

    virtual bool getBubbles() const = 0;

    virtual bool getCancelable() const = 0;

    virtual long getTimeStamp() const = 0;

    virtual void stopPropagation() = 0;

    virtual void preventDefault() = 0;

    virtual void initEvent(const stringT& eventTypeArg, bool canBubble, bool cancelable) = 0;
    
    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() = 0;
    virtual void releaseRef() = 0;

}; // class Event_impl

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
// end of file
