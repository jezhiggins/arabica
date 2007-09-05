#ifndef JEZUK_EVENTS_MUTATIONEVENT_H
#define JEZUK_EVENTS_MUTATIONEVENT_H

#include <DOM/Events/Event.hpp>

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT> class MutationEvent_impl;

template<class stringT>
class MutationEvent : public Event<stringT>
{
  public:
    MutationEvent() : Event<stringT>() { }
    MutationEvent(MutationEvent_impl<stringT>* const impl) : Event<stringT>(impl) { }
    MutationEvent(const MutationEvent& rhs) : Event<stringT>(rhs) { }
    explicit MutationEvent(const Event<stringT>& rhs) : Event<stringT>(rhs)  
    {
      if(dynamic_cast<MutationEvent_impl<stringT>*>(rhs.Impl()) == 0)
        throw std::runtime_error("bad_cast: Cannot cast Node to Element");
    } // Element
    virtual ~MutationEvent() { }
    bool operator==(const MutationEvent& rhs) const { return Proxy::operator==(rhs); } 
    bool operator!=(const MutationEvent& rhs) const { return Proxy::operator!=(rhs); }
    bool operator==(int dummy) const { return Proxy::operator==(dummy); }
    bool operator!=(int dummy) const { return Proxy::operator!=(dummy); }

    MutationEvent& operator=(const MutationEvent& rhs) 
    {
      Proxy::operator=(rhs);
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
    MutationEvent_impl<stringT>* mImpl() const { return dynamic_cast<MutationEvent_impl<stringT>*>(impl()); }
}; // class Event

///////////////////////////////////////////////////////////
// Event_impl
template<class stringT>
class MutationEvent_impl : virtual public Event_impl<stringT>
{
  public:
    ///////////////////////////////////
    // MutationEvent methods
    virtual DOM::Node<stringT> getRelatedNode() const = 0;

    virtual stringT getPrevValue() const = 0;

    virtual stringT getNextValue() const = 0;

    virtual stringT getAttrName() const = 0;

    virtual MutationEvent<stringT>::AttrChange getAttrChange() const = 0;

    virtual void initMutationEvent(const stringT& typeArg,
                                   bool canBubble,
                                   bool canCancel,
                                   DOM::Node<stringT> relatedNode,
                                   const stringT& prevValueArg,
                                   const stringT& nextValueArg,
                                   const stringT& attrNameArg,
                                   MutationEvent<stringT>::AttrChange attrChangeArg) = 0;
}; // class Event_impl

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
// end of file
