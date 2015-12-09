#ifndef JEZUK_DOM_DOCUMENT_H
#define JEZUK_DOM_DOCUMENT_H

////////////////////////////
// C++ DOM definition
////////////////////////////

#include <DOM/Node.hpp>
#include <DOM/NodeList.hpp>
#include <DOM/NamedNodeMap.hpp>
#include <DOM/Element.hpp>
#include <DOM/Attr.hpp>
#include <DOM/ProcessingInstruction.hpp>
#include <DOM/DocumentType.hpp>
#include <DOM/DOMImplementation.hpp>
#include <DOM/DocumentFragment.hpp>
#include <DOM/EntityReference.hpp>
#include <DOM/CDATASection.hpp>
#include <DOM/Text.hpp>
#include <DOM/Comment.hpp>

#include <DOM/Traversal/DocumentTraversal.hpp>
#include <DOM/Traversal/DocumentTraversalImpl.hpp>

namespace Arabica
{
namespace DOM
{

namespace Events {
  template<class stringT, class string_adaptorT> class DocumentEvent;
} // namespace Events

template<class stringT, class string_adaptorT> class Document_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class Document : public Node<stringT, string_adaptorT>
{
    typedef Node<stringT, string_adaptorT> NodeT;
  public:
    Document() : Node<stringT, string_adaptorT>() { }
    Document(Document_impl<stringT, string_adaptorT>* impl) : Node<stringT, string_adaptorT>(impl) { }
    Document(const Document& rhs) : Node<stringT, string_adaptorT>(rhs) { }
    explicit Document(const Node<stringT, string_adaptorT>& rhs) : Node<stringT, string_adaptorT>(rhs)
    {
      if(NodeT::impl_ == 0) // null nodes can always be cast
	return;
      if(rhs.getNodeType() != Node<stringT, string_adaptorT>::DOCUMENT_NODE)
        throw DOMBadCast("Document");
    } // Document
    ~Document() { }

    Document& operator=(const Document& rhs)
    {
      Node<stringT, string_adaptorT>::operator=(rhs);
      return *this;
    } // operator

    DocumentType<stringT, string_adaptorT> getDoctype() const { return dImpl()->getDoctype(); }

    DOMImplementation<stringT, string_adaptorT> getImplementation() const { return DOMImplementation<stringT, string_adaptorT>(dImpl()->getImplementation()); }

    Element<stringT, string_adaptorT> getDocumentElement() const { return Element<stringT, string_adaptorT>(dImpl()->getDocumentElement()); }

    Element<stringT, string_adaptorT> createElement(const stringT& tagName) const { return Element<stringT, string_adaptorT>(dImpl()->createElement(tagName)); }

    DocumentFragment<stringT, string_adaptorT> createDocumentFragment() const { return DocumentFragment<stringT, string_adaptorT>(dImpl()->createDocumentFragment()); }

    Text<stringT, string_adaptorT> createTextNode(const stringT& data) const { return Text<stringT, string_adaptorT>(dImpl()->createTextNode(data)); }

    Comment<stringT, string_adaptorT> createComment(const stringT& data) const { return Comment<stringT, string_adaptorT>(dImpl()->createComment(data)); }

    CDATASection<stringT, string_adaptorT> createCDATASection(const stringT& data) const { return CDATASection<stringT, string_adaptorT>(dImpl()->createCDATASection(data)); }

    ProcessingInstruction<stringT, string_adaptorT> createProcessingInstruction(const stringT& target, const stringT& data) const
    {
      return ProcessingInstruction<stringT, string_adaptorT>(dImpl()->createProcessingInstruction(target, data));
    } // createProcessingInstruction

    Attr<stringT, string_adaptorT> createAttribute(const stringT& name) const { return Attr<stringT, string_adaptorT>(dImpl()->createAttribute(name)); }

    EntityReference<stringT, string_adaptorT> createEntityReference(const stringT& name) const { return EntityReference<stringT, string_adaptorT>(dImpl()->createEntityReference(name)); }

    NodeList<stringT, string_adaptorT> getElementsByTagName(const stringT& tagname) const { return NodeList<stringT, string_adaptorT>(dImpl()->getElementsByTagName(tagname)); }

    Node<stringT, string_adaptorT> importNode(const Node<stringT, string_adaptorT>& importedNode, bool deep) const { return Node<stringT, string_adaptorT>(dImpl()->importNode(*importedNode.impl_, deep)); }

    Element<stringT, string_adaptorT> createElementNS(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      return Element<stringT, string_adaptorT>(dImpl()->createElementNS(namespaceURI, qualifiedName));
    } // createElementNS

    Attr<stringT, string_adaptorT> createAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName) const
    {
      return Attr<stringT, string_adaptorT>(dImpl()->createAttributeNS(namespaceURI, qualifiedName));
    } // createAttributeNS

    NodeList<stringT, string_adaptorT> getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return NodeList<stringT, string_adaptorT>(dImpl()->getElementsByTagNameNS(namespaceURI, localName));
    } // getElementsByTagNameNS

    Element<stringT, string_adaptorT> getElementById(const stringT& elementId) const { return Element<stringT, string_adaptorT>(dImpl()->getElementById(elementId)); } // getElementById

    Traversal::DocumentTraversal<stringT, string_adaptorT> createDocumentTraversal()
    {
      Traversal::DocumentTraversal<stringT, string_adaptorT> docTraversal(new Traversal::DocumentTraversalImpl<stringT, string_adaptorT>());
      return docTraversal;
    } // createDocumentTraversal

  private:
    Document_impl<stringT, string_adaptorT>* dImpl() const { return dynamic_cast<Document_impl<stringT, string_adaptorT>*>(*NodeT::impl_); }

    typedef class Traversal::DocumentTraversal<stringT, string_adaptorT> DocumentTraversalT;
    friend class Traversal::DocumentTraversal<stringT, string_adaptorT>;
    typedef class Events::DocumentEvent<stringT, string_adaptorT> DocumentEventT;
    friend class Events::DocumentEvent<stringT, string_adaptorT>;
}; // class Document

//////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class DocumentType_impl;
template<class stringT, class string_adaptorT> class DOMImplementation_impl;
template<class stringT, class string_adaptorT> class Element_impl;
template<class stringT, class string_adaptorT> class DocumentFragment_impl;
template<class stringT, class string_adaptorT> class Text_impl;
template<class stringT, class string_adaptorT> class Comment_impl;
template<class stringT, class string_adaptorT> class CDATASection_impl;
template<class stringT, class string_adaptorT> class ProcessingInstruction_impl;
template<class stringT, class string_adaptorT> class Attr_impl;
template<class stringT, class string_adaptorT> class EntityReference_impl;
template<class stringT, class string_adaptorT> class NodeList_impl;

template<class stringT, class string_adaptorT>
class Document_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    virtual ~Document_impl() { }

    virtual DocumentType_impl<stringT, string_adaptorT>* getDoctype() const = 0;

    virtual DOMImplementation<stringT, string_adaptorT> getImplementation() const = 0;

    virtual Element_impl<stringT, string_adaptorT>* getDocumentElement() const = 0;

    virtual Element_impl<stringT, string_adaptorT>* createElement(const stringT& tagName) const = 0;

    virtual DocumentFragment_impl<stringT, string_adaptorT>* createDocumentFragment() const = 0;

    virtual Text_impl<stringT, string_adaptorT>* createTextNode(const stringT& data) const = 0;

    virtual Comment_impl<stringT, string_adaptorT>* createComment(const stringT& data) const = 0;

    virtual CDATASection_impl<stringT, string_adaptorT>* createCDATASection(const stringT& data) const = 0;

    virtual ProcessingInstruction_impl<stringT, string_adaptorT>* createProcessingInstruction(const stringT& target, const stringT& data) const = 0;

    virtual Attr_impl<stringT, string_adaptorT>* createAttribute(const stringT& name) const = 0;

    virtual EntityReference_impl<stringT, string_adaptorT>* createEntityReference(const stringT& name) const = 0;

    virtual NodeList_impl<stringT, string_adaptorT>* getElementsByTagName(const stringT& tagname) const = 0;

    virtual Node_impl<stringT, string_adaptorT>* importNode(Node_impl<stringT, string_adaptorT>* importedNode, bool deep) const = 0;

    virtual Element_impl<stringT, string_adaptorT>* createElementNS(const stringT& namespaceURI, const stringT& qualifiedName) const = 0;

    virtual Attr_impl<stringT, string_adaptorT>* createAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName) const = 0;

    virtual NodeList_impl<stringT, string_adaptorT>* getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const = 0;

    virtual Element_impl<stringT, string_adaptorT>* getElementById(const stringT& elementId) const = 0;
}; // class Document_impl

} // namespace DOM
} // namespace Arabica

#endif
