#ifndef JEZUK_SimpleDOM_ENTITYREFERENCEIMPL_H
#define JEZUK_SimpleDOM_ENTITYREFERENCEIMPL_H

#include <DOM/EntityReference.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class EntityReferenceImpl : public DOM::EntityReference_impl<stringT>,
                            public NodeImplWithChildren<stringT, string_adaptorT>
{
    typedef DOM::EntityReference_impl<stringT> EntityReferenceT;
    using EntityReferenceT::ownerDoc_;
    using EntityReferenceT::readOnly_;

  public:
    EntityReferenceImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT name) : 
        DOM::EntityReference_impl<stringT>(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc), 
        name_(name)
    { 
    } // EntityReferenceImpl

    virtual ~EntityReferenceImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::ENTITY_REFERENCE_NODE;
    } // getNodeType

    virtual stringT getNodeName() const 
    {
      return name_;
    } // getNodeName

    virtual void setNodeValue(const stringT& x)
    {
      throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);
    } // setNodeValue

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      return ownerDoc_->createEntityReference(name_);
    } // cloneNode

    //////////////////////////////////////////////////////
    // this implementation
  private:
    virtual void checkChildType(DOM::Node_impl<stringT>* child)
    {
      if(readOnly_)
        throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);

      typename DOM::Node<stringT>::Type type = child->getNodeType();
      if((type != DOM::Node<stringT>::ELEMENT_NODE) && 
         (type != DOM::Node<stringT>::PROCESSING_INSTRUCTION_NODE) && 
         (type != DOM::Node<stringT>::COMMENT_NODE) && 
         (type != DOM::Node<stringT>::TEXT_NODE) && 
         (type != DOM::Node<stringT>::CDATA_SECTION_NODE) && 
         (type != DOM::Node<stringT>::ENTITY_REFERENCE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

    stringT name_;
}; // class EntityReferenceImpl


} // namespace SAX2DOM

#endif

