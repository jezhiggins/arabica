#ifndef JEZUK_DOM_SimpleDOM_MUTATIONEVENT_IMPL_H
#define JEZUK_DOM_SimpleDOM_MUTATIONEVENT_IMPL_H

////////////////////////////
// C++ MutationEvent implementation
////////////////////////////

#include <DOM/Events/MutationEvent.hpp>
#include <DOM/Events/EventImpl.hpp>
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
class MutationEventImpl : virtual public DOM::Events::MutationEvent_impl<stringT, string_adaptorT>,
                          public DOM::Events::EventImpl<stringT, string_adaptorT>
{
  public:
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::Text_impl<stringT, string_adaptorT> DOMText_implT;
    typedef DOM::Document_impl<stringT, string_adaptorT> DOMDocument_implT;
    typedef DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;
    typedef DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;
    typedef DOM::Events::Event<stringT, string_adaptorT> EventT;
    typedef DOM::Events::EventImpl<stringT, string_adaptorT> EventImplT;
    typedef DOM::Events::EventTarget<stringT, string_adaptorT> EventTargetT;
    typedef DOM::Events::MutationEventImpl<stringT, string_adaptorT> MutationEventImplT;

    MutationEventImpl()
    {
        //std::cout << std::endl << "born " << this << std::endl;
    } // MutationEventImpl
    
    virtual ~MutationEventImpl() 
    { 
        //std::cout << std::endl << "die  " << this << std::endl;
    }

    virtual DOM::Node<stringT> getRelatedNode() const
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

    virtual typename MutationEvent<stringT, string_adaptorT>::AttrChange getAttrChange() const
    {
      return attrChange_;
    }

    virtual void initMutationEvent(const stringT& typeArg,
                                   bool canBubble,
                                   bool canCancel,
                                   DOM::Node<stringT> relatedNode,
                                   const stringT& prevValueArg,
                                   const stringT& nextValueArg,
                                   const stringT& attrNameArg,
                                   typename MutationEvent<stringT, string_adaptorT>::AttrChange attrChangeArg)
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

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() {};
    virtual void releaseRef() {};

  protected:
    DOM::Node<stringT> relatedNode_;
    stringT prevValue_;
    stringT nextValue_;
    stringT attrName_;
    typename MutationEvent<stringT, string_adaptorT>::AttrChange attrChange_;
}; // class MutationEventImpl

} // namespace DOM
} // namespace Events
} // namespace Arabica

#endif // JEZUK_DOM_SimpleDOM_EVENTTARGET_H
// end of file
