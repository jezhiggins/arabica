#ifndef JEZUK_SimpleDOM_DOCUMENTTYPEIMPL_H
#define JEZUK_SimpleDOM_DOCUMENTTYPEIMPL_H

#include <DOM/DocumentType.h>
#include <DOM/Simple/NodeImpl.h>
#include <vector>

namespace SimpleDOM
{
template<class stringT, class string_adaptorT> class ElementImpl;
template<class stringT, class string_adaptorT> class NotationImpl;
template<class stringT, class string_adaptorT> class EntityImpl;

template<class stringT, class string_adaptorT>
class DocumentTypeImpl : public DOM::DocumentType_impl<stringT>,
                         public ChildlessNodeImpl<stringT, string_adaptorT>
{
  public:
    DocumentTypeImpl(const stringT& qualifiedName,
                     const stringT& publicId,
                     const stringT& systemId) :
      DOM::DocumentType_impl<stringT>(),
      ChildlessNodeImpl<stringT, string_adaptorT>(0),
      qualifiedName_(qualifiedName),
      publicId_(publicId),
      systemId_(systemId),
      entities_(0),
      notations_(0),
      elements_(0),
      refCount_(0)
    {
      entities_.setReadOnly(true);
      notations_.setReadOnly(true);
    } // DOMImplemenationImpl

    virtual ~DocumentTypeImpl() { }

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef()
    {
      if(ownerDoc_)
        ownerDoc_->addRef();
      else
        ++refCount_;
    } // addRef
    virtual void releaseRef() 
    {
      if(ownerDoc_)
        ownerDoc_->releaseRef();
      else
        if(--refCount_ == 0)
          delete this;
    } // releaseRef

    //////////////////////////////////////////////////////
    // DOM::DOMImplementation methods
    virtual stringT getName() const 
    { 
      return getNodeName(); 
    } // getName

    virtual DOM::NamedNodeMap_impl<stringT>* getEntities() 
    {
      return &entities_;
    } // getEntities

    virtual DOM::NamedNodeMap_impl<stringT>* getNotations()
    {
      return &notations_;
    } // getNotations

    virtual stringT getPublicId() const
    {
      return publicId_;
    } // getPublicId

    virtual stringT getSystemId() const
    {
      return systemId_;
    } // getSystemId

    virtual stringT getInternalSubset() const
    {
      return string_adaptorT().makeStringT("");
    } // getInternalSubset

    //////////////////////////////////////////////////////////
    // DOM::Node methods
    typename DOM::Node<stringT>::Type getNodeType() const
    {
      return DOM::Node<stringT>::DOCUMENT_TYPE_NODE;
    } // getNodeType

    virtual stringT getNodeName() const
    {
      return qualifiedName_;
    } // getNodeName

    DOM::Node_impl<stringT>* cloneNode(bool deep) const 
    { 
      DocumentTypeImpl* clone = new DocumentTypeImpl(qualifiedName_, publicId_, systemId_);
      return clone;
    } // cloneNode

    virtual void setOwnerDoc(DocumentImpl<stringT, string_adaptorT>* ownerDoc)
    {
      entities_.setOwnerDoc(ownerDoc);
      notations_.setOwnerDoc(ownerDoc);
      ChildlessNodeImpl<stringT, string_adaptorT>::setOwnerDoc(ownerDoc);
      while(refCount_--)
        ownerDoc_->addRef();
    } // setOwnerDocument

    NamedNodeMapImpl<stringT, string_adaptorT>* getElements() 
    {
      return &elements_;
    } // getElements

    std::vector<stringT>* getElementIds() 
    {
      return &IDs_;
    } // getIDs

  protected:
    void addEntity(SimpleDOM::EntityImpl<stringT, string_adaptorT>* entity)
    {
      entities_.setReadOnly(false);
      entity->setOwnerDoc(ownerDoc_);
      entities_.setNamedItem(entity);
      entities_.setReadOnly(true);
    } // setEntity

    void addNotation(SimpleDOM::NotationImpl<stringT, string_adaptorT>* notation)
    {
      notations_.setReadOnly(false);
      notation->setOwnerDoc(ownerDoc_);
      notations_.setNamedItem(notation);
      notations_.setReadOnly(true);
    } // setNotation

    void addElement(SimpleDOM::ElementImpl<stringT, string_adaptorT>* element)
    {
      element->setOwnerDoc(ownerDoc_);
      elements_.setNamedItem(element);
    } // addElements

    void addElementId(const stringT& elementId)
    {
      IDs_.push_back(elementId);
    } // addId

  private:
    DocumentTypeImpl(const DocumentTypeImpl&);
    DocumentTypeImpl& operator=(const DocumentTypeImpl&);

    stringT qualifiedName_;
    stringT publicId_;
    stringT systemId_;
    NamedNodeMapImpl<stringT, string_adaptorT> entities_;
    NamedNodeMapImpl<stringT, string_adaptorT> notations_;
    NamedNodeMapImpl<stringT, string_adaptorT> elements_;
    std::vector<stringT> IDs_;
    unsigned int refCount_;
}; // class DOMImplementation

} // namespace SAX2DOM

#endif
// end of file
