#ifndef JEZUK_SimpleDOM_DOCUMENTTYPEIMPL_H
#define JEZUK_SimpleDOM_DOCUMENTTYPEIMPL_H

#include <DOM/DocumentType.hpp>
#include <DOM/Simple/NodeImpl.hpp>
#include <vector>

namespace Arabica
{
namespace SimpleDOM
{
template<class stringT, class string_adaptorT> class ElementImpl;
template<class stringT, class string_adaptorT> class NotationImpl;
template<class stringT, class string_adaptorT> class EntityImpl;

template<class stringT, class string_adaptorT>
class DocumentTypeImpl : public DOM::DocumentType_impl<stringT, string_adaptorT>,
                         public ChildlessNodeImpl<stringT, string_adaptorT>
{
  public:
    typedef ChildlessNodeImpl<stringT, string_adaptorT> NodeT;
    typedef NamedNodeMapImpl<stringT, string_adaptorT> NamedNodeMapT;
    typedef DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;

    DocumentTypeImpl(const stringT& qualifiedName,
                     const stringT& publicId,
                     const stringT& systemId) :
      DOM::DocumentType_impl<stringT, string_adaptorT>(),
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
      if(NodeT::ownerDoc_)
        NodeT::ownerDoc_->addRef();
      else
        ++refCount_;
    } // addRef
    virtual void releaseRef() 
    {
      if(NodeT::ownerDoc_)
        NodeT::ownerDoc_->releaseRef();
      else
        if(--refCount_ == 0)
          delete this;
    } // releaseRef

    //////////////////////////////////////////////////////
    // DOM::DOMImplementation methods
    virtual const stringT& getName() const 
    { 
      return getNodeName(); 
    } // getName

    virtual DOMNamedNodeMap_implT* getEntities() 
    {
      return &entities_;
    } // getEntities

    virtual DOMNamedNodeMap_implT* getNotations()
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
      return string_adaptorT::construct_from_utf8("");
    } // getInternalSubset

    //////////////////////////////////////////////////////////
    // DOM::Node methods
    typename DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::DOCUMENT_TYPE_NODE;
    } // getNodeType

    virtual const stringT& getNodeName() const
    {
      return qualifiedName_;
    } // getNodeName

    DOMNode_implT* cloneNode(bool /*deep*/) const
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
        NodeT::ownerDoc_->addRef();
    } // setOwnerDocument

    NamedNodeMapT* getElements() 
    {
      return &elements_;
    } // getElements

    std::vector<stringT>* getElementIds() 
    {
      return &IDs_;
    } // getIDs

  protected:
    void addEntity(Arabica::SimpleDOM::EntityImpl<stringT, string_adaptorT>* entity)
    {
      entities_.setReadOnly(false);
      entity->setOwnerDoc(NodeT::ownerDoc_);
      entities_.setNamedItem(entity);
      entities_.setReadOnly(true);
    } // setEntity

    void addNotation(Arabica::SimpleDOM::NotationImpl<stringT, string_adaptorT>* notation)
    {
      notations_.setReadOnly(false);
      notation->setOwnerDoc(NodeT::ownerDoc_);
      notations_.setNamedItem(notation);
      notations_.setReadOnly(true);
    } // setNotation

    void addElement(Arabica::SimpleDOM::ElementImpl<stringT, string_adaptorT>* element)
    {
      if(elements_.getNamedItem(element->getNodeName()) != 0)
      {
        delete element;
        return;  // already have an element decl for it
      } // if ...
      element->setOwnerDoc(NodeT::ownerDoc_);
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
    NamedNodeMapT entities_;
    NamedNodeMapT notations_;
    NamedNodeMapT elements_;
    std::vector<stringT> IDs_;
    unsigned int refCount_;
}; // class DOMImplementation

} // namespace SAX2DOM
} // namespace Arabica

#endif
// end of file
