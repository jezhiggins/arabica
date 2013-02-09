#ifndef JEZUK_DOM_SimpleDOM_MUTATIONEVENT_IMPL_H
#define JEZUK_DOM_SimpleDOM_MUTATIONEVENT_IMPL_H

////////////////////////////
// C++ MutationEvent implementation
////////////////////////////

#include <DOM/Events/MutationEvent.hpp>
#include <DOM/Simple/EventImpl.hpp>
#include <DOM/DOMException.hpp>
#include <XML/XMLCharacterClasses.hpp>

//#include <iostream>

namespace Arabica
{
namespace SimpleDOM
{

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class MutationEventImpl : virtual public Arabica::DOM::Events::MutationEvent_impl<stringT, string_adaptorT>,
                          public EventImpl<stringT, string_adaptorT>
{
  public:
    typedef Arabica::DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef Arabica::DOM::Text_impl<stringT, string_adaptorT> DOMText_implT;
    typedef Arabica::DOM::Document_impl<stringT, string_adaptorT> DOMDocument_implT;
    typedef Arabica::DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;
    typedef Arabica::DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;
    typedef Arabica::DOM::Events::Event<stringT, string_adaptorT> EventT;
    typedef Arabica::DOM::Events::MutationEvent<stringT, string_adaptorT> MutationEventT;
    typedef EventImpl<stringT, string_adaptorT> EventImplT;
    typedef Arabica::DOM::Events::EventTarget<stringT, string_adaptorT> EventTargetT;
    typedef MutationEventImpl<stringT, string_adaptorT> MutationEventImplT;

    MutationEventImpl()
    {
        //std::cout << std::endl << "born " << this << std::endl;
    } // MutationEventImpl

    virtual ~MutationEventImpl()
    {
        //std::cout << std::endl << "die  " << this << std::endl;
    }

    virtual DOM::Node<stringT, string_adaptorT> getRelatedNode() const
    {
      return relatedNode_;
    }

    virtual stringT getPrevValue() const
    {
    	return prevValue_;
    }

    virtual stringT getNextValue() const
    {
      return nextValue_;
    }

    virtual stringT getAttrName() const
    {
      return attrName_;
    }

    virtual typename MutationEventT::AttrChange getAttrChange() const
    {
      return attrChange_;
    }

    virtual void initMutationEvent(const stringT& typeArg,
                                   bool canBubble,
                                   bool canCancel,
                                   DOM::Node<stringT, string_adaptorT> relatedNode,
                                   const stringT& prevValueArg,
                                   const stringT& nextValueArg,
                                   const stringT& attrNameArg,
                                   typename MutationEventT::AttrChange attrChangeArg)
    {
      EventImplT::type_ = typeArg;
      EventImplT::canBubble_ = canBubble;
      EventImplT::canCancel_ = canCancel;
      relatedNode_ = relatedNode;
      prevValue_ = prevValueArg;
      nextValue_ = nextValueArg;
      attrName_ = attrNameArg;
      attrChange_ = attrChangeArg;
    }

  protected:
  DOM::Node<stringT, string_adaptorT> relatedNode_;
    stringT prevValue_;
    stringT nextValue_;
    stringT attrName_;
    typename MutationEventT::AttrChange attrChange_;
}; // class MutationEventImpl

} // namespace SimpleDOM
} // namespace Arabica

#endif // JEZUK_DOM_SimpleDOM_EVENTTARGET_H
// end of file
