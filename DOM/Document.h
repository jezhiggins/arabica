#ifndef JEZUK_DOM_DOCUMENT_H
#define JEZUK_DOM_DOCUMENT_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.h>
#include <DOM/NodeList.h>
#include <DOM/NamedNodeMap.h>
#include <DOM/Element.h>
#include <DOM/Attr.h>
#include <DOM/ProcessingInstruction.h>
#include <DOM/DocumentType.h>
#include <DOM/DOMImplementation.h>
#include <DOM/DocumentFragment.h>
#include <DOM/EntityReference.h>
#include <DOM/CDATASection.h>
#include <DOM/Text.h>
#include <DOM/Comment.h>

namespace DOM
{

namespace Traversal {
  template<class stringT> class DocumentTraversal;
} // namespace Traversal 

namespace Events {
  template<class stringT> class DocumentEvent;
} // namespace Events 

template<class stringT> class Document_impl;

template<class stringT>
class Document : public Node<stringT>
{
  public:
    Document() : Node<stringT>() { }
    Document(Document_impl<stringT>* impl) : Node<stringT>(impl) { }
    Document(const Document& rhs) : Node<stringT>(rhs) { }
    explicit Document(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT>::DOCUMENT_NODE)
        throw std::bad_cast();
    } // Document
    ~Document() { }

    Document& operator=(const Document& rhs) 
    {
      Node<stringT>::operator=(rhs);
      return *this;
    } // operator

    DocumentType<stringT> getDoctype() const { return dImpl()->getDoctype(); }

    DOMImplementation<stringT> getImplementation() const { return DOMImplementation<stringT>(dImpl()->getImplementation()); }

    Element<stringT> getDocumentElement() const { return Element<stringT>(dImpl()->getDocumentElement()); }

    Element<stringT> createElement(const stringT& tagName) const { return Element<stringT>(dImpl()->createElement(tagName)); }

    DocumentFragment<stringT> createDocumentFragment() const { return DocumentFragment<stringT>(dImpl()->createDocumentFragment()); }

    Text<stringT> createTextNode(const stringT& data) const { return Text<stringT>(dImpl()->createTextNode(data)); }

    Comment<stringT> createComment(const stringT& data) const { return Comment<stringT>(dImpl()->createComment(data)); }

    CDATASection<stringT> createCDATASection(const stringT& data) const { return CDATASection<stringT>(dImpl()->createCDATASection(data)); }

    ProcessingInstruction<stringT> createProcessingInstruction(const stringT& target, const stringT& data) const
    {
      return ProcessingInstruction<stringT>(dImpl()->createProcessingInstruction(target, data)); 
    } // createProcessingInstruction

    Attr<stringT> createAttribute(const stringT& name) const { return Attr<stringT>(dImpl()->createAttribute(name)); }

    EntityReference<stringT> createEntityReference(const stringT& name) const { return EntityReference<stringT>(dImpl()->createEntityReference(name)); }

    NodeList<stringT> getElementsByTagName(const stringT& tagname) const { return NodeList<stringT>(dImpl()->getElementsByTagName(tagname)); }

    Node<stringT> importNode(const Node<stringT>& importedNode, bool deep) const { return Node<stringT>(dImpl()->importNode(*importedNode.impl_, deep)); }

    Element<stringT> createElementNS(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      return Element<stringT>(dImpl()->createElementNS(namespaceURI, qualifiedName)); 
    } // createElementNS

    Attr<stringT> createAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      return Attr<stringT>(dImpl()->createAttributeNS(namespaceURI, qualifiedName)); 
    } // createAttributeNS

    NodeList<stringT> getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return NodeList<stringT>(dImpl()->getElementsByTagNameNS(namespaceURI, localName));
    } // getElementsByTagNameNS

    Element<stringT> getElementById(const stringT& elementId) const { return Element<stringT>(dImpl()->getElementById(elementId)); }

  private:
    Document_impl<stringT>* dImpl() const { return dynamic_cast<Document_impl<stringT>*>(*impl_); }

    typedef class Traversal::DocumentTraversal<stringT> DocumentTraversalT;
    friend class Traversal::DocumentTraversal<stringT>;
    typedef class Events::DocumentEvent<stringT> DocumentEventT;
    friend class Events::DocumentEvent<stringT>;
}; // class DocumentFragment

//////////////////////////////////////////////////////////
template<class stringT> class DocumentType_impl;
template<class stringT> class DOMImplementation_impl;
template<class stringT> class Element_impl;
template<class stringT> class DocumentFragment_impl;
template<class stringT> class Text_impl;
template<class stringT> class Comment_impl;
template<class stringT> class CDATASection_impl;
template<class stringT> class ProcessingInstruction_impl;
template<class stringT> class Attr_impl;
template<class stringT> class EntityReference_impl;
template<class stringT> class NodeList_impl;

template<class stringT>
class Document_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~Document_impl() { }

    virtual DocumentType_impl<stringT>* getDoctype() const = 0;

    virtual DOMImplementation<stringT> getImplementation() const = 0;

    virtual Element_impl<stringT>* getDocumentElement() const = 0;

    virtual Element_impl<stringT>* createElement(const stringT& tagName) const = 0;

    virtual DocumentFragment_impl<stringT>* createDocumentFragment() const = 0;

    virtual Text_impl<stringT>* createTextNode(const stringT& data) const = 0;

    virtual Comment_impl<stringT>* createComment(const stringT& data) const = 0;

    virtual CDATASection_impl<stringT>* createCDATASection(const stringT& data) const = 0;

    virtual ProcessingInstruction_impl<stringT>* createProcessingInstruction(const stringT& target, const stringT& data) const = 0;

    virtual Attr_impl<stringT>* createAttribute(const stringT& name) const = 0;

    virtual EntityReference_impl<stringT>* createEntityReference(const stringT& name) const = 0;

    virtual NodeList_impl<stringT>* getElementsByTagName(const stringT& tagname) const = 0;

    virtual Node_impl<stringT>* importNode(Node_impl<stringT>* importedNode, bool deep) const = 0;

    virtual Element_impl<stringT>* createElementNS(const stringT& namespaceURI, const stringT& qualifiedName) const = 0;

    virtual Attr_impl<stringT>* createAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName) const = 0;

    virtual NodeList_impl<stringT>* getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const = 0;

    virtual Element_impl<stringT>* getElementById(const stringT& elementId) const = 0;
}; // class Document_impl

} // namespace DOM

#endif

