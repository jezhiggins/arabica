#ifndef JEZUK_SimpleDOM_DOCUMENTIMPL_H
#define JEZUK_SimpleDOM_DOCUMENTIMPL_H


#include <DOM/Document.hpp>
#include <DOM/Simple/ElementNSImpl.hpp>
#include <DOM/Simple/ProcessingInstructionImpl.hpp>
#include <DOM/Simple/DocumentFragmentImpl.hpp>
#include <DOM/Simple/CommentImpl.hpp>
#include <DOM/Simple/TextImpl.hpp>
#include <DOM/Simple/CDATASectionImpl.hpp>
#include <DOM/Simple/AttrNSImpl.hpp>
#include <DOM/Simple/EntityReferenceImpl.hpp>
#include <DOM/Simple/EntityImpl.hpp>
#include <DOM/Simple/NotationImpl.hpp>
#include <DOM/Simple/ElementByTagImpl.hpp>
#include <DOM/Simple/NodeImpl.hpp>

#include <set>
#include <algorithm>

namespace Arabica
{
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
class DocumentImpl : public DOM::Document_impl<stringT, string_adaptorT>,
                     public NodeImplWithChildren<stringT, string_adaptorT>

{
    typedef NodeImpl<stringT, string_adaptorT> NodeImplT;
    typedef AttrImpl<stringT, string_adaptorT> AttrImplT;
    typedef ElementImpl<stringT, string_adaptorT> ElementImplT;
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeWithChildrenT;
  public:
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::Attr_impl<stringT, string_adaptorT> DOMAttr_implT;
    typedef DOM::Element_impl<stringT, string_adaptorT> DOMElement_implT;
    typedef DOM::Document_impl<stringT, string_adaptorT> DOMDocument_implT;
    typedef DOM::DocumentType_impl<stringT, string_adaptorT> DOMDocumentType_implT;
    typedef DOM::DOMImplementation<stringT, string_adaptorT> DOMDOMImplementationT;

    DocumentImpl() :
        NodeWithChildrenT(0),
        documentElement_(0),
        documentType_(0),
	      domImplementation_(),
        namespaceURI_(),
        qualifiedName_(),
        changesCount_(0),
        refCount_(0),
        empty_()
    {
      NodeImplT::setOwnerDoc(this);
    } // DocumentBaseImpl

    DocumentImpl(DOMDOMImplementationT domImpl) :
        NodeWithChildrenT(0),
        documentElement_(0),
        documentType_(0),
        domImplementation_(domImpl),
        namespaceURI_(),
        qualifiedName_(),
        changesCount_(0),
        refCount_(0)
    {
      NodeImplT::setOwnerDoc(this);
    } // DocumentBaseImpl

    DocumentImpl(const stringT& namespaceURI,
                 const stringT& qualifiedName,
                 DOMDocumentType_implT* docType,
                 DOMDOMImplementationT domImpl) :
        NodeWithChildrenT(0),
        documentElement_(0),
        documentType_(0),
        domImplementation_(domImpl),
        namespaceURI_(namespaceURI),
        qualifiedName_(qualifiedName),
        changesCount_(0),
        refCount_(0)
    {
      NodeImplT::setOwnerDoc(this);
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
    virtual DOMDocumentType_implT* getDoctype() const
    {
      return documentType_;
    } // getDocType

    virtual DOMDOMImplementationT getImplementation() const
    {
      return domImplementation_;
    } // getImplementation

    virtual DOMElement_implT* getDocumentElement() const
    {
      return documentElement_;
    } // getDocumentElement

    virtual DOMElement_implT* createElement(const stringT& tagName) const
    {
      this->checkName(tagName);
      return createElement_nocheck(tagName);
    } // createElement

    DOMElement_implT* createElement_nocheck(const stringT& tagName) const
    {
      ElementImplT* n =
        new ElementImplT(const_cast<DocumentImpl*>(this), tagName);
      orphaned(n);
      return n;
    } // createElement_nocheck

    virtual DOM::DocumentFragment_impl<stringT, string_adaptorT>* createDocumentFragment() const
    {
      DocumentFragmentImpl<stringT, string_adaptorT>* n = new DocumentFragmentImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this));
      orphaned(n);
      return n;
    } // createDocumentFragment

    virtual DOM::Text_impl<stringT, string_adaptorT>* createTextNode(const stringT& data) const
    {
      TextImpl<stringT, string_adaptorT>* n = new TextImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), data);
      orphaned(n);
      return n;
    } // createTextNode

    virtual DOM::Comment_impl<stringT, string_adaptorT>* createComment(const stringT& data) const
    {
      CommentImpl<stringT, string_adaptorT>* n = new CommentImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), data);
      orphaned(n);
      return n;
    } // createComment

    virtual DOM::CDATASection_impl<stringT, string_adaptorT>* createCDATASection(const stringT& data) const
    {
      CDATASectionImpl<stringT, string_adaptorT>* n = new CDATASectionImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), data);
      orphaned(n);
      return n;
    } // createCDATASection

    virtual DOM::ProcessingInstruction_impl<stringT, string_adaptorT>* createProcessingInstruction(const stringT& target, const stringT& data) const
    {
      this->checkName(target);
      this->checkChars(data);
      return createProcessingInstruction_nocheck(target, data);
    } // createProcessingInstruction

    DOM::ProcessingInstruction_impl<stringT, string_adaptorT>* createProcessingInstruction_nocheck(const stringT& target, const stringT& data) const
    {
      ProcessingInstructionImpl<stringT, string_adaptorT>* n = new ProcessingInstructionImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), target, data);
      orphaned(n);
      return n;
    } // createProcessingInstruction_nocheck

    virtual DOMAttr_implT* createAttribute(const stringT& name) const
    {
      this->checkName(name);
      return createAttribute_nocheck(name);
    } // createAttribute

    DOMAttr_implT* createAttribute_nocheck(const stringT& name) const
    {
      AttrImpl<stringT, string_adaptorT>* n = new AttrImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), name);
      orphaned(n);
      return n;
    } // createAttribute_nocheck

    virtual DOM::EntityReference_impl<stringT, string_adaptorT>* createEntityReference(const stringT& name) const
    {
      this->checkName(name);
      return createEntityReference_nocheck(name);
    } // createEntityRef

    DOM::EntityReference_impl<stringT, string_adaptorT>* createEntityReference_nocheck(const stringT& name) const
    {
      EntityReferenceImpl<stringT, string_adaptorT>* n = new EntityReferenceImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), name);
      if((documentType_ != 0) && (documentType_->getEntities()->getNamedItem(name) != 0))
      {
        DOMNode_implT* entity = documentType_->getEntities()->getNamedItem(name);
        for(DOMNode_implT* child = entity->getFirstChild(); child != 0; child = child->getNextSibling())
          n->appendChild(importNode(child, true));
      } // if ...
      orphaned(n);
      n->setReadOnly(true);
      return n;
    } // createEntityReference

    virtual DOM::NodeList_impl<stringT, string_adaptorT>* getElementsByTagName(const stringT& tagname) const
    {
      return new ElementByTagList<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this),
                                                            const_cast<DocumentImpl*>(this),
                                                            tagname);
    } // getElementsByTagName

    virtual DOMNode_implT* importNode(DOMNode_implT* importedNode, bool deep) const
    {
      DOMNode_implT* newNode = 0;

      switch(importedNode->getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
          if(string_adaptorT::empty(importedNode->getLocalName()))
            newNode = createAttribute_nocheck(importedNode->getNodeName());
          else
            newNode = createAttributeNS_nocheck(importedNode->getNamespaceURI(), importedNode->getNodeName());
          deep = true;
          break;
        case DOM::Node_base::DOCUMENT_FRAGMENT_NODE:
          newNode = createDocumentFragment();
          break;
        case DOM::Node_base::DOCUMENT_NODE:
          throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR);
        case DOM::Node_base::DOCUMENT_TYPE_NODE:
          throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR);
        case DOM::Node_base::ELEMENT_NODE:
          {
            DOMElement_implT* elem;
            if(string_adaptorT::empty(importedNode->getLocalName()))
              elem = createElement_nocheck(importedNode->getNodeName());
            else
              elem = createElementNS_nocheck(importedNode->getNamespaceURI(), importedNode->getNodeName());

            const DOM::NamedNodeMap_impl<stringT, string_adaptorT>* attrs = importedNode->getAttributes();
            if(attrs)
              for(unsigned int i = 0; i < attrs->getLength(); ++i)
              {
                DOMAttr_implT* a = dynamic_cast<DOMAttr_implT*>(attrs->item(i));
                if(a->getSpecified())
                {
                  DOMAttr_implT* newA = dynamic_cast<DOMAttr_implT*>(importNode(a, true));
                  if(string_adaptorT::empty(a->getLocalName()))
                    elem->setAttributeNode(newA);
                  else
                    elem->setAttributeNodeNS(newA);
                } // if ...
              } // for
            newNode = elem;
          }
          break;
        case DOM::Node_base::ENTITY_NODE:
          {
            DOM::Entity_impl<stringT, string_adaptorT>* entity = dynamic_cast<DOM::Entity_impl<stringT, string_adaptorT>*>(importedNode);
            newNode = new EntityImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this),
                                              entity->getNodeName(),
                                              entity->getPublicId(),
                                              entity->getSystemId(),
                                              entity->getNotationName());
          }
          break;
        case DOM::Node_base::ENTITY_REFERENCE_NODE:
          newNode = createEntityReference_nocheck(importedNode->getNodeName());
          deep = false;
          break;
        case DOM::Node_base::NOTATION_NODE:
          {
            DOM::Notation_impl<stringT, string_adaptorT>* entity = dynamic_cast<DOM::Notation_impl<stringT, string_adaptorT>*>(importedNode);
            newNode = new NotationImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this),
                                                entity->getNodeName(),
                                                entity->getPublicId(),
                                                entity->getSystemId());
          }
          break;
        case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
          newNode = createProcessingInstruction_nocheck(importedNode->getNodeName(), importedNode->getNodeValue());
          break;
        case DOM::Node_base::TEXT_NODE:
          newNode = createTextNode(importedNode->getNodeValue());
          break;
        case DOM::Node_base::CDATA_SECTION_NODE:
          newNode = createCDATASection(importedNode->getNodeValue());
          break;
        case DOM::Node_base::COMMENT_NODE:
          newNode = createComment(importedNode->getNodeValue());
          break;
        default:
          throw std::runtime_error("Bad node type value in importNode");
      } // switch

      if(deep)
      {
        for(DOMNode_implT* child = importedNode->getFirstChild(); child != 0; child = child->getNextSibling())
          newNode->appendChild(importNode(child, true));
      } // if(deep)

      if(newNode->getNodeType() == DOM::Node_base::ENTITY_NODE)
        dynamic_cast<NodeImplT*>(newNode)->setReadOnly(true);
      orphaned(dynamic_cast<NodeImplT*>(newNode));

      return newNode;
    } // importNode

    virtual DOMElement_implT* createElementNS(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      this->checkName(qualifiedName);
      return createElementNS_nocheck(namespaceURI, qualifiedName);
    } // createElementNS

    DOMElement_implT* createElementNS_nocheck(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      ElementNSImpl<stringT, string_adaptorT>* n =
        new ElementNSImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), namespaceURI, !string_adaptorT::empty(namespaceURI), qualifiedName);
      orphaned(n);
      return n;
    } // createElementNS

    virtual DOMAttr_implT* createAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      this->checkName(qualifiedName);
      return createAttributeNS_nocheck(namespaceURI, qualifiedName);
    } // createAttributeNS

    virtual DOMAttr_implT* createAttributeNS_nocheck(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      AttrNSImpl<stringT, string_adaptorT>* n = new AttrNSImpl<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this), namespaceURI, !string_adaptorT::empty(namespaceURI), qualifiedName);
      orphaned(n);
      return n;
    } // createAttributeNS_nocheck

    virtual DOM::NodeList_impl<stringT, string_adaptorT>* getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return new ElementByTagList<stringT, string_adaptorT>(const_cast<DocumentImpl*>(this),
                                                            const_cast<DocumentImpl*>(this),
                                                            namespaceURI, localName);
    } // getElementsByTagNameNS

    virtual DOMElement_implT* getElementById(const stringT& elementId) const
    {
      typename std::set<AttrImplT*>::const_iterator i = std::find_if(idNodes_.begin(), idNodes_.end(), valueIs<stringT, string_adaptorT>(elementId));
      if(i == idNodes_.end())
        return 0;
      return (*i)->getOwnerElement();
    } // getElementById

    ////////////////////////////////////////////////////////
    // DOM Node methods
    virtual typename DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::DOCUMENT_NODE;
    } // getNodeType

    virtual DOMNode_implT* getParentNode() const { return 0; }

    virtual DOMDocument_implT* getOwnerDocument() const { return 0; }

    virtual const stringT& getNodeName() const
    {
      static const stringT doc = string_adaptorT::construct_from_utf8("#document");
      return doc;
    } // getNodeName

    virtual DOMNode_implT* insertBefore(DOMNode_implT* newChild, DOMNode_implT* refChild)
    {
      if((newChild->getNodeType() == DOM::Node_base::ELEMENT_NODE) && (documentElement_ != 0))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
      if((newChild->getNodeType() == DOM::Node_base::DOCUMENT_TYPE_NODE) && (documentType_ != 0))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);

      DOMNode_implT* result = NodeWithChildrenT::insertBefore(newChild, refChild);

      if((newChild->getNodeType() == DOM::Node_base::ELEMENT_NODE) && (documentElement_ == 0))
        documentElement_ = dynamic_cast<DOMElement_implT*>(newChild);
      if((newChild->getNodeType() == DOM::Node_base::DOCUMENT_TYPE_NODE) && (documentType_ == 0))
        documentType_ = dynamic_cast<DOMDocumentType_implT*>(newChild);

      return result;
    } // insertBefore

    virtual DOMNode_implT* replaceChild(DOMNode_implT* newChild, DOMNode_implT* oldChild)
    {
      checkChildType(newChild);

      if((newChild->getNodeType() == DOM::Node_base::DOCUMENT_TYPE_NODE) && (documentType_ == oldChild))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
      if((newChild->getNodeType() == DOM::Node_base::ELEMENT_NODE) &&
         (documentElement_ != 0) &&
         (documentElement_ != oldChild))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);

      DOMNode_implT* result = NodeWithChildrenT::replaceChild(newChild, oldChild);

      if((newChild->getNodeType() == DOM::Node_base::ELEMENT_NODE) &&
         ((documentElement_ == 0) || (documentElement_ == oldChild)))
        documentElement_ = dynamic_cast<DOMElement_implT*>(newChild);

      return result;
    } // replaceChild

    virtual DOMNode_implT* removeChild(DOMNode_implT* oldChild)
    {
      if(documentType_ == oldChild)
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
      DOMNode_implT* result = NodeWithChildrenT::removeChild(oldChild);

      if(documentElement_ == oldChild)
        documentElement_ = static_cast<DOMElement_implT*>(0);

      return result;
    } // removeChild

    virtual DOMNode_implT* appendChild(DOMNode_implT* newChild)
    {
      return insertBefore(newChild, 0);
    } // appendChild

    virtual DOMNode_implT* cloneNode(bool deep) const
    {
      DocumentImpl* clone = new DocumentImpl(namespaceURI_, qualifiedName_, 0, domImplementation_);
      if(documentType_ != 0)
      {
        DocumentTypeImpl<stringT, string_adaptorT>* dt = dynamic_cast<DocumentTypeImpl<stringT, string_adaptorT>*>(documentType_->cloneNode(true));
        dt->setOwnerDoc(clone);
        clone->appendChild(dt);
      }

      if(deep)
        for(DOMNode_implT* child = NodeWithChildrenT::getFirstChild(); child != 0; child = child->getNextSibling())
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

    bool isOrphaned(NodeImplT* node) const
    {
      return orphans_.find(node) != orphans_.end();
    } // isOrphaned

    void purge(NodeImplT* node)
    {
      orphans_.erase(node);
      delete node;
    } // purge

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
      typename std::set<AttrImplT*>::iterator n = idNodes_.find(attr);
      if(n != idNodes_.end())
        idNodes_.erase(n);
    } // removeElementId

    stringT const* stringPool(const stringT& str) const
    {
      return &(*stringPool_.insert(str).first);
    } // stringPool

    const stringT& empty_string() const { return empty_; }

  private:
    void checkChildType(DOMNode_implT* child)
    {
      typename DOM::Node_base::Type type = child->getNodeType();
      if((type != DOM::Node_base::ELEMENT_NODE) &&
         (type != DOM::Node_base::PROCESSING_INSTRUCTION_NODE) &&
         (type != DOM::Node_base::COMMENT_NODE) &&
         (type != DOM::Node_base::DOCUMENT_TYPE_NODE))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

  private:
    DOMElement_implT* documentElement_;
    DOMDocumentType_implT* documentType_;
    DOMDOMImplementationT domImplementation_;
    stringT namespaceURI_;
    stringT qualifiedName_;
    unsigned long changesCount_;
    unsigned long refCount_;

    mutable std::set<NodeImplT*> orphans_;
    std::set<AttrImplT*> idNodes_;
    mutable std::set<stringT> stringPool_;
    const stringT empty_;
}; // class DocumentImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif
// end of file
