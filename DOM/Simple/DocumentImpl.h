#ifndef JEZUK_SimpleDOM_DOCUMENTIMPL_H
#define JEZUK_SimpleDOM_DOCUMENTIMPL_H


#include <DOM/Document.h>
#include <DOM/Simple/ElementNSImpl.h>
#include <DOM/Simple/ProcessingInstructionImpl.h>
#include <DOM/Simple/DocumentFragmentImpl.h>
#include <DOM/Simple/CommentImpl.h>
#include <DOM/Simple/TextImpl.h>
#include <DOM/Simple/CDATASectionImpl.h>
#include <DOM/Simple/AttrNSImpl.h>
#include <DOM/Simple/EntityReferenceImpl.h>
#include <DOM/Simple/EntityImpl.h>
#include <DOM/Simple/NotationImpl.h>
#include <DOM/Simple/ElementByTagImpl.h>
#include <DOM/Simple/NodeImpl.h>

#include <set>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class valueIs : public std::unary_function<AttrImpl<stringT, string_adaptorT>*, bool>
{
  public:
    valueIs(const stringT& value) : value_(value) { }
    bool operator()(const AttrImpl<stringT, string_adaptorT>* node) const
    {
      return (node->getNodeValue() == value_);
    } // operator()

  private:
    stringT value_;
}; // class valueIs

template<class stringT, class string_adaptorT>
class DocumentImpl : public DOM::Document_impl<stringT>,
                     public NodeImplWithChildren<stringT, string_adaptorT>
{
    typedef NodeImpl<stringT, string_adaptorT> NodeImplT;
    typedef AttrImpl<stringT, string_adaptorT> AttrImplT;

  public:
    DocumentImpl() : 
        NodeImplWithChildren<stringT, string_adaptorT>(0),
        documentElement_(0),
        documentType_(0),
				domImplementation_(),
        namespaceURI_(),
        qualifiedName_(),
        changesCount_(0),
        refCount_(0)
    { 
      setOwnerDoc(this);
    } // DocumentBaseImpl

    DocumentImpl(DOM::DOMImplementation<stringT> domImpl) : 
        NodeImplWithChildren<stringT, string_adaptorT>(0),
        documentElement_(0),
        documentType_(0),
        domImplementation_(domImpl),
        namespaceURI_(),
        qualifiedName_(),
        changesCount_(0),
        refCount_(0)
    { 
      setOwnerDoc(this);
    } // DocumentBaseImpl

    DocumentImpl(const stringT& namespaceURI,
                 const stringT& qualifiedName,
                 DOM::DocumentType_impl<stringT>* docType,
                 DOM::DOMImplementation<stringT> domImpl) : 
        NodeImplWithChildren<stringT, string_adaptorT>(0),
        documentElement_(0),
        documentType_(0),
        domImplementation_(domImpl),
        namespaceURI_(namespaceURI),
        qualifiedName_(qualifiedName),
        changesCount_(0),
        refCount_(0)
    { 
      setOwnerDoc(this);
      if(docType)
      {
        if(docType->getOwnerDocument() != 0)
          throw DOM::DOMException(DOM::DOMException::WRONG_DOCUMENT_ERR);
        appendChild(docType);
      } // if(docType)
    } // DocumentBaseImpl

    virtual ~DocumentImpl() 
    { 
      for(typename std::set<NodeImplT*>::iterator n = orphans_.begin(); n != orphans_.end(); ++n)
        delete *n;
    } // ~DocumentImpl

    /////////////////////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef()
    {
      ++refCount_;
    } // addRef

    virtual void releaseRef()
    {
      if(--refCount_ == 0)
        delete this;
    } // releaseRef

    /////////////////////////////////////////////////////////////////////
    // DOM::Document functions
    virtual DOM::DocumentType_impl<stringT>* getDoctype() const
    {
      return documentType_;
    } // getDocType

    virtual DOM::DOMImplementation<stringT> getImplementation() const
    {
      return domImplementation_;
    } // getImplementation

    virtual DOM::Element_impl<stringT>* getDocumentElement() const
    {
      return documentElement_;
    } // getDocumentElement

    virtual DOM::Element_impl<stringT>* createElement(const stringT& tagName) const
    {
      ElementImpl<stringT, string_adaptorT>* n = new ElementImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), tagName);
      orphaned(n);
      return n;
    } // createElement

    virtual DOM::DocumentFragment_impl<stringT>* createDocumentFragment() const
    {
      DocumentFragmentImpl<stringT, string_adaptorT>* n = new DocumentFragmentImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this));
      orphaned(n);
      return n;
    } // createDocumentFragment

    virtual DOM::Text_impl<stringT>* createTextNode(const stringT& data) const
    {
      TextImpl<stringT, string_adaptorT>* n = new TextImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), data);
      orphaned(n);
      return n;
    } // createTextNode

    virtual DOM::Comment_impl<stringT>* createComment(const stringT& data) const
    {
      CommentImpl<stringT, string_adaptorT>* n = new CommentImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), data);
      orphaned(n);
      return n;
    } // createComment

    virtual DOM::CDATASection_impl<stringT>* createCDATASection(const stringT& data) const
    {
      CDATASectionImpl<stringT, string_adaptorT>* n = new CDATASectionImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), data);
      orphaned(n);
      return n;
    } // createCDATASection

    virtual DOM::ProcessingInstruction_impl<stringT>* createProcessingInstruction(const stringT& target, const stringT& data) const
    {
      ProcessingInstructionImpl<stringT, string_adaptorT>* n = new ProcessingInstructionImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), target, data);
      orphaned(n);
      return n;
    } // createProcessingInstruction

    virtual DOM::Attr_impl<stringT>* createAttribute(const stringT& name) const
    {
      AttrImpl<stringT, string_adaptorT>* n = new AttrImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), name);
      orphaned(n);
      return n;
    } // createAttribute

    virtual DOM::EntityReference_impl<stringT>* createEntityReference(const stringT& name) const
    {
      EntityReferenceImpl<stringT, string_adaptorT>* n = new EntityReferenceImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), name);
      if((documentType_ != 0) && (documentType_->getEntities()->getNamedItem(name) != 0))
      {
        DOM::Node_impl<stringT>* entity = documentType_->getEntities()->getNamedItem(name);
        for(DOM::Node_impl<stringT>* child = entity->getFirstChild(); child != 0; child = child->getNextSibling())
          n->appendChild(importNode(child, true));
      } // if ...
      orphaned(n);
      n->setReadOnly(true);
      return n;
    } // createEntityReference

    virtual DOM::NodeList_impl<stringT>* getElementsByTagName(const stringT& tagname) const
    {
      return new ElementByTagList<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this),
                                                            const_cast<DocumentImpl*>(this),
                                                            tagname);
    } // getElementsByTagName

    virtual DOM::Node_impl<stringT>* importNode(DOM::Node_impl<stringT>* importedNode, bool deep) const
    {
      DOM::Node_impl<stringT>* newNode = 0;

      switch(importedNode->getNodeType())
      {
        case DOM::Node<stringT>::ATTRIBUTE_NODE:
          if(importedNode->getLocalName().empty())
            newNode = createAttribute(importedNode->getNodeName());
          else
            newNode = createAttributeNS(importedNode->getNamespaceURI(), importedNode->getNodeName());
          deep = true;
          break;
        case DOM::Node<stringT>::DOCUMENT_FRAGMENT_NODE:
          newNode = createDocumentFragment();
          break;
        case DOM::Node<stringT>::DOCUMENT_NODE:
          throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR);
        case DOM::Node<stringT>::DOCUMENT_TYPE_NODE:
          throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR);
        case DOM::Node<stringT>::ELEMENT_NODE:
          {
            DOM::Element_impl<stringT>* elem;
            if(importedNode->getLocalName().empty())
              elem = createElement(importedNode->getNodeName());
            else
              elem = createElementNS(importedNode->getNamespaceURI(), importedNode->getNodeName());

            const DOM::NamedNodeMap_impl<stringT>* attrs = importedNode->getAttributes();
            if(attrs)
              for(unsigned int i = 0; i < attrs->getLength(); ++i)
              {
                DOM::Attr_impl<stringT>* a = dynamic_cast<DOM::Attr_impl<stringT>*>(attrs->item(i));
                if(a->getSpecified())
                {
                  DOM::Attr_impl<stringT>* newA = dynamic_cast<DOM::Attr_impl<stringT>*>(importNode(a, true));
                  if(a->getLocalName().empty())
                    elem->setAttributeNode(newA);
                  else
                    elem->setAttributeNodeNS(newA);
                } // if ...
              } // for
            newNode = elem;
          }
          break;
        case DOM::Node<stringT>::ENTITY_NODE:
          {
            DOM::Entity_impl<stringT>* entity = dynamic_cast<DOM::Entity_impl<stringT>*>(importedNode);
            newNode = new EntityImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this),
                                              entity->getNodeName(),
                                              entity->getPublicId(),
                                              entity->getSystemId(),
                                              entity->getNotationName());
          } 
          break;
        case DOM::Node<stringT>::ENTITY_REFERENCE_NODE:
          newNode = createEntityReference(importedNode->getNodeName());
          deep = false;
          break;
        case DOM::Node<stringT>::NOTATION_NODE:
          {
            DOM::Notation_impl<stringT>* entity = dynamic_cast<DOM::Notation_impl<stringT>*>(importedNode);
            newNode = new NotationImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this),
                                                entity->getNodeName(),
                                                entity->getPublicId(),
                                                entity->getSystemId());
          } 
          break;
        case DOM::Node<stringT>::PROCESSING_INSTRUCTION_NODE:
          newNode = createProcessingInstruction(importedNode->getNodeName(), importedNode->getNodeValue());
          break;
        case DOM::Node<stringT>::TEXT_NODE:
          newNode = createTextNode(importedNode->getNodeValue());
          break;
        case DOM::Node<stringT>::CDATA_SECTION_NODE:
          newNode = createCDATASection(importedNode->getNodeValue());
          break;
        case DOM::Node<stringT>::COMMENT_NODE:
          newNode = createComment(importedNode->getNodeValue());
          break;
      } // switch

      if(deep)
      {
        for(DOM::Node_impl<stringT>* child = importedNode->getFirstChild(); child != 0; child = child->getNextSibling())
          newNode->appendChild(importNode(child, true));
      } // if(deep)

      if(newNode->getNodeType() == DOM::Node<stringT>::ENTITY_NODE)
        dynamic_cast<NodeImplT*>(newNode)->setReadOnly(true);
      orphaned(dynamic_cast<NodeImplT*>(newNode));

      return newNode;
    } // importNode

    virtual DOM::Element_impl<stringT>* createElementNS(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      ElementNSImpl<stringT, string_adaptorT>* n = new ElementNSImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), namespaceURI, !namespaceURI.empty(), qualifiedName);
      orphaned(n);
      return n;
    } // createElementNS

    virtual DOM::Attr_impl<stringT>* createAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      AttrNSImpl<stringT, string_adaptorT>* n = new AttrNSImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), namespaceURI, !namespaceURI.empty(), qualifiedName);
      orphaned(n);
      return n;
    } // createAttrNS

    virtual DOM::NodeList_impl<stringT>* getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return new ElementByTagList<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this),
                                                            const_cast<DocumentImpl*>(this),
                                                            namespaceURI, localName);
    } // getElementsByTagNameNS

    virtual DOM::Element_impl<stringT>* getElementById(const stringT& elementId) const
    {
      typename std::set<AttrImplT*>::const_iterator i = std::find_if(idNodes_.begin(), idNodes_.end(), valueIs<stringT, string_adaptorT>(elementId));
      if(i == idNodes_.end())
        return 0;
      return (*i)->getOwnerElement();
    } // getElementById

    ////////////////////////////////////////////////////////
    // DOM Node methods 
    virtual typename DOM::Node<stringT>::Type getNodeType() const
    {
      return DOM::Node<stringT>::DOCUMENT_NODE;
    } // getNodeType
    
    virtual DOM::Node_impl<stringT>* getParentNode() const { return 0; }

    virtual DOM::Document_impl<stringT>* getOwnerDocument() const { return 0; }

    virtual stringT getNodeName() const
    {
      string_adaptorT SA_;
      return SA_.makeStringT("#document");
    } // getNodeName

    virtual DOM::Node_impl<stringT>* insertBefore(DOM::Node_impl<stringT>* newChild, DOM::Node_impl<stringT>* refChild)
    {
      if((newChild->getNodeType() == DOM::Node<stringT>::ELEMENT_NODE) && (documentElement_ != 0))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
      if((newChild->getNodeType() == DOM::Node<stringT>::DOCUMENT_TYPE_NODE) && (documentType_ != 0))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);

      DOM::Node_impl<stringT>* result = NodeImplWithChildren<stringT, string_adaptorT>::insertBefore(newChild, refChild);

      if((newChild->getNodeType() == DOM::Node<stringT>::ELEMENT_NODE) && (documentElement_ == 0))
        documentElement_ = dynamic_cast<DOM::Element_impl<stringT>*>(newChild);
      if((newChild->getNodeType() == DOM::Node<stringT>::DOCUMENT_TYPE_NODE) && (documentType_ == 0))
        documentType_ = dynamic_cast<DOM::DocumentType_impl<stringT>*>(newChild);

      return result;
    } // insertBefore

    virtual DOM::Node_impl<stringT>* replaceChild(DOM::Node_impl<stringT>* newChild, DOM::Node_impl<stringT>* oldChild)
    {
      checkChildType(newChild);

      if((newChild->getNodeType() == DOM::Node<stringT>::DOCUMENT_TYPE_NODE) && (documentType_ == oldChild))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
      if((newChild->getNodeType() == DOM::Node<stringT>::ELEMENT_NODE) && 
         (documentElement_ != 0) && 
         (documentElement_ != oldChild))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
      
      DOM::Node_impl<stringT>* result = NodeImplWithChildren<stringT, string_adaptorT>::replaceChild(newChild, oldChild);

      if((newChild->getNodeType() == DOM::Node<stringT>::ELEMENT_NODE) && 
         ((documentElement_ == 0) || (documentElement_ == oldChild)))
        documentElement_ = dynamic_cast<DOM::Element_impl<stringT>*>(newChild);

      return result;
    } // replaceChild

    virtual DOM::Node_impl<stringT>* removeChild(DOM::Node_impl<stringT>* oldChild)
    {
      if((documentType_ == oldChild))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
      DOM::Node_impl<stringT>* result = NodeImplWithChildren<stringT, string_adaptorT>::removeChild(oldChild);
 
      if(documentElement_ == oldChild)
        documentElement_ = static_cast<DOM::Element_impl<stringT>*>(0);

      return result;
    } // removeChild

    virtual DOM::Node_impl<stringT>* appendChild(DOM::Node_impl<stringT>* newChild)
    {
      return insertBefore(newChild, 0);
    } // appendChild

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      DocumentImpl* clone = new DocumentImpl(namespaceURI_, qualifiedName_, 0, domImplementation_);
      if(documentType_ != 0)
      {
        DocumentTypeImpl<stringT, string_adaptorT>* dt = dynamic_cast<DocumentTypeImpl<stringT, string_adaptorT>*>(documentType_->cloneNode(true));
        dt->setOwnerDoc(clone);
        clone->appendChild(dt);
      } 

      if(deep)
        for(DOM::Node_impl<stringT>* child = getFirstChild(); child != 0; child = child->getNextSibling())
          if((documentType_ != child) && (child != clone->getDocumentElement()))
            clone->appendChild(clone->importNode(child, true));

      return clone;
    } // cloneNode

    ////////////////////////////
    // extensions
    void markChanged() { ++changesCount_; }
    unsigned long changes() const { return changesCount_; }

    void orphaned(NodeImplT* node) const
    { 
      orphans_.insert(node); 
    } // orphaned
    void adopted(NodeImplT* node)
    {
      typename std::set<NodeImplT*>::iterator n = orphans_.find(node);
      if(n != orphans_.end())
        orphans_.erase(n);
    } // adopted

    void setElementId(AttrImplT* attr) 
    {
      idNodes_.insert(attr);
    } // setElementId
    void removeElementId(AttrImplT* attr)
    {
      typename std::set<AttrImplT*>::iterator n = idNodes_.find(node);
      if(n != idNodes_.end())
        idNodes_.erase(n);
    } // removeElementId

  private:
    virtual void checkChildType(typename DOM::Node_impl<stringT>* child)
    {
      typename DOM::Node<stringT>::Type type = child->getNodeType();
      if((type != DOM::Node<stringT>::ELEMENT_NODE) && 
         (type != DOM::Node<stringT>::PROCESSING_INSTRUCTION_NODE) && 
         (type != DOM::Node<stringT>::COMMENT_NODE) && 
         (type != DOM::Node<stringT>::DOCUMENT_TYPE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

  private:
    DOM::Element_impl<stringT>* documentElement_;
    DOM::DocumentType_impl<stringT>* documentType_;
    DOM::DOMImplementation<stringT> domImplementation_;
    stringT namespaceURI_;
    stringT qualifiedName_;
    unsigned long changesCount_;
    unsigned long refCount_;

    mutable std::set<NodeImplT*> orphans_;
    std::set<AttrImplT*> idNodes_;
}; // class DocumentImpl


} // namespace SAX2DOM
#endif
// end of file
