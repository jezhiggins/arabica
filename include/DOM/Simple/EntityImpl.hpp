#ifndef JEZUK_SimpleDOM_ENTITYIMPL_H
#define JEZUK_SimpleDOM_ENTITYIMPL_H

#include <DOM/Entity.hpp>
#include <DOM/Simple/NodeImpl.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class EntityImpl : public DOM::Entity_impl<stringT, string_adaptorT>,
                   public NodeImplWithChildren<stringT, string_adaptorT>
{
  public:
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeImplWithChildrenT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;

    EntityImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, 
               stringT name,
               stringT publicId,
               stringT systemId,
               stringT notationName) :
        DOM::Entity_impl<stringT, string_adaptorT>(),
        NodeImplWithChildrenT(ownerDoc),
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
    virtual typename DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::ENTITY_NODE;
    } // getNodeType

    virtual const stringT& getNodeName() const
    {
      return name_;
    } // getNodeName

    virtual DOMNode_implT* cloneNode(bool deep) const
    {
      EntityImpl* clone = new EntityImpl(NodeImplWithChildrenT::ownerDoc_, name_, publicId_, systemId_, notationName_);
      if(deep)
        for(DOMNode_implT* c = NodeImplWithChildrenT::getFirstChild(); c != 0; c = c->getNextSibling())
          clone->appendChild(c->cloneNode(true));
      NodeImplWithChildrenT::ownerDoc_->orphaned(clone);
      return clone;
    } // cloneNode

    virtual DOMNode_implT* getParentNode() const 
    { 
      return 0; 
    } // getParentNode

    ///////////////////////////////////////////////
    virtual void checkChildType(DOMNode_implT* child)
    {
      typename DOM::Node_base::Type type = child->getNodeType();
      if((type != DOM::Node_base::ELEMENT_NODE) && 
         (type != DOM::Node_base::PROCESSING_INSTRUCTION_NODE) && 
         (type != DOM::Node_base::COMMENT_NODE) && 
         (type != DOM::Node_base::TEXT_NODE) && 
         (type != DOM::Node_base::CDATA_SECTION_NODE) && 
         (type != DOM::Node_base::ENTITY_REFERENCE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

  private:
    stringT name_;
    stringT publicId_;
    stringT systemId_;
    stringT notationName_;
}; // class EntityImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif

