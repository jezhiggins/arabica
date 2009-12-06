#ifndef JEZUK_SimpleDOM_ENTITYREFERENCEIMPL_H
#define JEZUK_SimpleDOM_ENTITYREFERENCEIMPL_H

#include <DOM/EntityReference.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class EntityReferenceImpl : public DOM::EntityReference_impl<stringT, string_adaptorT>,
                            public NodeImplWithChildren<stringT, string_adaptorT>
{
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeT;
  public:
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;

    EntityReferenceImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT name) : 
        DOM::EntityReference_impl<stringT, string_adaptorT>(),
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

    virtual const stringT& getNodeName() const 
    {
      return name_;
    } // getNodeName

    virtual void setNodeValue(const stringT& /*x*/)
    {
      throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);
    } // setNodeValue

    virtual DOMNode_implT* cloneNode(bool /*deep*/) const
    {
      return NodeT::ownerDoc_->createEntityReference(name_);
    } // cloneNode

    //////////////////////////////////////////////////////
    // this implementation
  private:
    virtual void checkChildType(DOMNode_implT* child)
    {
      if(NodeT::readOnly_)
        throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);

      typename DOM::Node_base::Type type = child->getNodeType();
      if((type != DOM::Node_base::ELEMENT_NODE) && 
         (type != DOM::Node_base::PROCESSING_INSTRUCTION_NODE) && 
         (type != DOM::Node_base::COMMENT_NODE) && 
         (type != DOM::Node_base::TEXT_NODE) && 
         (type != DOM::Node_base::CDATA_SECTION_NODE) && 
         (type != DOM::Node_base::ENTITY_REFERENCE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

    stringT name_;
}; // class EntityReferenceImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif

