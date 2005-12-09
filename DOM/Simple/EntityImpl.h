#ifndef JEZUK_SimpleDOM_ENTITYIMPL_H
#define JEZUK_SimpleDOM_ENTITYIMPL_H

#include <DOM/Entity.h>
#include <DOM/Simple/NodeImpl.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class EntityImpl : public DOM::Entity_impl<stringT>,
                   public NodeImplWithChildren<stringT, string_adaptorT>
{
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeT;
  public:
    EntityImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, 
               stringT name,
               stringT publicId,
               stringT systemId,
               stringT notationName) :
        DOM::Entity_impl<stringT>(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc),
        name_(name),
        publicId_(publicId),
        systemId_(systemId),
        notationName_(notationName)
    { 
    } // EntityImpl

    virtual ~EntityImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Entity methods
    virtual stringT getPublicId() const { return publicId_; }
    virtual stringT getSystemId() const { return systemId_; }
    virtual stringT getNotationName() const { return notationName_; }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual typename DOM::Node<stringT>::Type getNodeType() const
    {
      return DOM::Node<stringT>::ENTITY_NODE;
    } // getNodeType

    virtual const stringT& getNodeName() const
    {
      return name_;
    } // getNodeName

    virtual typename DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      EntityImpl* clone = new EntityImpl(NodeT::ownerDoc_, name_, publicId_, systemId_, notationName_);
      if(deep)
        for(DOM::Node_impl<stringT>* c = NodeT::getFirstChild(); c != 0; c = c->getNextSibling())
          clone->appendChild(c->cloneNode(true));
      NodeT::ownerDoc_->orphaned(clone);
      return clone;
    } // cloneNode

    virtual DOM::Node_impl<stringT>* getParentNode() const 
    { 
      return 0; 
    } // getParentNode

    ///////////////////////////////////////////////
    virtual void checkChildType(DOM::Node_impl<stringT>* child)
    {
      typename DOM::Node<stringT>::Type type = child->getNodeType();
      if((type != DOM::Node<stringT>::ELEMENT_NODE) && 
         (type != DOM::Node<stringT>::PROCESSING_INSTRUCTION_NODE) && 
         (type != DOM::Node<stringT>::COMMENT_NODE) && 
         (type != DOM::Node<stringT>::TEXT_NODE) && 
         (type != DOM::Node<stringT>::CDATA_SECTION_NODE) && 
         (type != DOM::Node<stringT>::ENTITY_REFERENCE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

  private:
    stringT name_;
    stringT publicId_;
    stringT systemId_;
    stringT notationName_;
}; // class EntityImpl


} // namespace SAX2DOM

#endif

