#ifndef JEZUK_EVENTS_MUTATIONEVENT_H
#define JEZUK_EVENTS_MUTATIONEVENT_H

#include <DOM/Events/Event.hpp>

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT, class string_adaptorT> class MutationEvent_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class MutationEvent : public Event<stringT, string_adaptorT>
{
  public:
    typedef MutationEvent_impl<stringT, string_adaptorT> MutationEvent_implT;
    typedef Event<stringT, string_adaptorT> EventT;
    typedef DOM::Proxy<MutationEvent_implT> proxy_t;

    MutationEvent() : Event<stringT, string_adaptorT>() { }
    MutationEvent(MutationEvent_impl<stringT, string_adaptorT>* const impl) : Event<stringT, string_adaptorT>(impl) { }
    MutationEvent(const MutationEvent& rhs) : Event<stringT, string_adaptorT>(rhs) { }
    explicit MutationEvent(const Event<stringT, string_adaptorT>& rhs) : Event<stringT, string_adaptorT>(rhs)  
    {
      if(dynamic_cast<MutationEvent_impl<stringT, string_adaptorT>*>(rhs.Impl()) == 0)
        throw DOMBadCast("Element");
    } // Element
    virtual ~MutationEvent() { }
    bool operator==(const MutationEvent& rhs) const { return proxy_t::operator==(rhs); } 
    bool operator!=(const MutationEvent& rhs) const { return proxy_t::operator!=(rhs); }
    bool operator==(int dummy) const { return proxy_t::operator==(dummy); }
    bool operator!=(int dummy) const { return proxy_t::operator!=(dummy); }

    MutationEvent& operator=(const MutationEvent& rhs) 
    {
      proxy_t::operator=(rhs);
      return *this;
    } // operator=

    /////////////////////////////////////////////
    // MutationEvent methods
    enum AttrChange
    {
      MODIFICATION = 1,
      ADDITION = 2,
      REMOVAL = 3
    }; // enum Change

    DOM::Node<stringT> getRelatedNode() const { return mImpl()->getRelatedNode(); }

    stringT getPrevValue() const { return mImpl()->getPrevValue(); }

    stringT getNextValue() const { return mImpl()->getNextValue(); }

    stringT getAttrName() const { return mImpl()->getAttrName(); }

    AttrChange getAttrChange() const { return mImpl()->getAttrChange(); }

    void initMutationEvent(const stringT& typeArg,
                           bool canBubble,
                           bool canCancel,
                           DOM::Node<stringT> relatedNode,
                           const stringT& prevValueArg,
                           const stringT& nextValueArg,
                           const stringT& attrNameArg,
                           AttrChange attrChangeArg)
    {
      mImpl()->initMutationEvent(typeArg, canBubble, canCancel, relatedNode,
                                 prevValueArg, nextValueArg, attrNameArg, attrChangeArg);
    } // initMutationEvent

  private:
  MutationEvent_implT* mImpl() const { return dynamic_cast<MutationEvent_implT*>(EventT::proxy_t::operator*()); }
}; // class Event

///////////////////////////////////////////////////////////
// Event_impl
template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class MutationEvent_impl : virtual public Event_impl<stringT, string_adaptorT>
{
  public:
    ///////////////////////////////////
    // MutationEvent methods
    virtual DOM::Node<stringT> getRelatedNode() const = 0;

    virtual stringT getPrevValue() const = 0;

    virtual stringT getNextValue() const = 0;

    virtual stringT getAttrName() const = 0;

    virtual typename MutationEvent<stringT, string_adaptorT>::AttrChange getAttrChange() const = 0;

    virtual void initMutationEvent(const stringT& typeArg,
                                   bool canBubble,
                                   bool canCancel,
                                   DOM::Node<stringT> relatedNode,
                                   const stringT& prevValueArg,
                                   const stringT& nextValueArg,
                                   const stringT& attrNameArg,
                                   typename MutationEvent<stringT, string_adaptorT>::AttrChange attrChangeArg) = 0;


}; // class Event_impl

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
// end of file
