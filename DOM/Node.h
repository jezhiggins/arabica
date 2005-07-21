#ifndef JEZUK_DOM_NODE_H
#define JEZUK_DOM_NODE_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////
#include <DOM/Proxy.h>
#include <typeinfo>
#include <deque>
#include <algorithm>

namespace DOM
{

namespace Events {
  template<class stringT> class EventTarget;
} // namespace Events 

template<class stringT> class Document;
template<class stringT> class NodeList;
template<class stringT> class NamedNodeMap;
template<class stringT> class Node_impl;

class Node_base
{
  public:
    enum Type 
    {
      ELEMENT_NODE,
      ATTRIBUTE_NODE,
      TEXT_NODE,
      CDATA_SECTION_NODE,
      ENTITY_REFERENCE_NODE,
      ENTITY_NODE,
      PROCESSING_INSTRUCTION_NODE,
      COMMENT_NODE,
      DOCUMENT_NODE,
      DOCUMENT_TYPE_NODE,
      DOCUMENT_FRAGMENT_NODE,
      NOTATION_NODE,
      MAX_TYPE
    }; // Type
}; // class Node_base

/////////////////////////////////////////////////
template<class string_type>
class Node : public Node_base
{
  public:
	  typedef string_type stringT;
    typedef string_type string_type;

    Node() : impl_() { }
    Node(Node_impl<stringT>* const impl) : impl_(impl) { }
    Node(const Node& rhs) : impl_(rhs.impl_) { }
    virtual ~Node() { }

    bool operator==(const Node& rhs) const { return impl_ == rhs.impl_; }
    bool operator!=(const Node& rhs) const { return impl_ != rhs.impl_; }
    bool operator==(int dummy) const { return impl_ == dummy; } 
    bool operator!=(int dummy) const { return impl_ != dummy; }

    Node& operator=(const Node& rhs) 
    {
      impl_ = rhs.impl_;
      return *this;
    } // operator=

    stringT getNodeName() const { return impl_->getNodeName(); }

    stringT getNodeValue() const { return impl_->getNodeValue(); }
    void setNodeValue(const stringT& nodeValue) { impl_->setNodeValue(nodeValue); }

    Type getNodeType() const { return impl_->getNodeType(); }
    
    Node getParentNode() const { return impl_->getParentNode(); }

    const NodeList<stringT> getChildNodes() const { return NodeList<stringT>(impl_->getChildNodes()); }
    
    Node getFirstChild() const { return impl_->getFirstChild(); }
    Node getLastChild() const { return impl_->getLastChild(); }
    Node getPreviousSibling() const { return impl_->getPreviousSibling(); }
    Node getNextSibling() const { return impl_->getNextSibling(); }

    const NamedNodeMap<stringT> getAttributes() const { return NamedNodeMap<stringT>(impl_->getAttributes()); }

    Document<stringT> getOwnerDocument() const { return impl_->getOwnerDocument(); }

    Node insertBefore(const Node& newChild, const Node& refChild) { return impl_->insertBefore(*newChild.impl_, *refChild.impl_); } 
    Node replaceChild(const Node& newChild, const Node& oldChild) { return impl_->replaceChild(*newChild.impl_, *oldChild.impl_); }
    Node removeChild(const Node& oldChild) { return impl_->removeChild(*oldChild.impl_); } 
    Node appendChild(const Node& newChild) { return impl_->appendChild(*newChild.impl_); }

    bool hasChildNodes() const { return impl_->hasChildNodes(); }

    Node cloneNode(bool deep) const { return impl_->cloneNode(deep); }

    void normalize() { impl_->normalize(); }

    bool isSupported(const stringT& feature, const stringT& version) const { return impl_->isSupported(feature, version); }

    stringT getNamespaceURI() const { return impl_->getNamespaceURI(); }
    stringT getPrefix() const { return impl_->getPrefix(); }
    void setPrefix(const stringT& prefix) const { impl_->setPrefix(prefix); }
    stringT getLocalName() const { return impl_->getLocalName(); }

    // additional three methods - since C++ std::string (and by implication
    // stringT) don't differenciate between a null string and an empty string,
    // but the DOM recommendation does, I have to introduce these three methods 
    // to disambiguate.  If they return false, the corresponding attribute should be
    // considered null.  If they return true, the attribute has been set EVEN IF 
    // it has been set to the empty string
    bool hasNamespaceURI() const { return impl_->hasNamespaceURI(); } 
    bool hasPrefix() const { return impl_->hasPrefix(); }

    bool hasAttributes() const { return impl_->hasAttributes(); }

    // you almost certainly don't need to use this function
    Node_impl<stringT>* unlying_impl() const { return *impl_; }

  protected:
    Proxy<Node_impl<stringT> > impl_;

    typedef class Document<stringT> DocumentT;
    friend class Document<stringT>;
    typedef class Events::EventTarget<stringT> EventTargetT;
    friend class Events::EventTarget<stringT>;
}; // class Node

////////////////////////////////////////////////////////////////////
// derive from this class to implement your own
// DOM provider
template<class string_type> class Document_impl;
template<class string_type> class NodeList_impl;
template<class string_type> class NamedNodeMap_impl;

template<class string_type>
class Node_impl
{
  public:
    typedef string_type stringT;

    virtual ~Node_impl() { }

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() = 0;
    virtual void releaseRef() = 0;

    ///////////////////////////////////////////////////////
    // Node methods
    virtual stringT getNodeName() const = 0;

    virtual stringT getNodeValue() const = 0;
    virtual void setNodeValue(const stringT& nodeValue) = 0;

    virtual Node_base::Type getNodeType() const = 0;
    
    virtual Node_impl<stringT>* getParentNode() const = 0;

    virtual NodeList_impl<stringT>* getChildNodes() const = 0;
    
    virtual Node_impl<stringT>* getFirstChild() const = 0;
    virtual Node_impl<stringT>* getLastChild() const = 0;

    virtual Node_impl<stringT>* getPreviousSibling() const = 0;
    virtual Node_impl<stringT>* getNextSibling() const = 0;

    virtual NamedNodeMap_impl<stringT>* getAttributes() const = 0;

    virtual Document_impl<stringT>* getOwnerDocument() const = 0;

    virtual Node_impl<stringT>* insertBefore(Node_impl<stringT>* newChild, Node_impl<stringT>* refChild) = 0;
    virtual Node_impl<stringT>* replaceChild(Node_impl<stringT>*  newChild, Node_impl<stringT>* oldChild) = 0;
    virtual Node_impl<stringT>* removeChild(Node_impl<stringT>*  oldChild) = 0;
    virtual Node_impl<stringT>* appendChild(Node_impl<stringT>*  newChild) = 0;

    virtual bool hasChildNodes() const = 0;

    virtual Node_impl<stringT>* cloneNode(bool deep) const = 0;

    virtual void normalize() = 0;

    virtual bool isSupported(const stringT& feature, const stringT& version) const = 0;

    virtual stringT getNamespaceURI() const = 0;
    virtual stringT getPrefix() const = 0;
    virtual void setPrefix(const stringT& prefix) = 0;
    virtual stringT getLocalName() const = 0;

    // additional methods - since C++ std::string (and by implication
    // stringT) don't differenciate between a null string and an empty string,
    // but the DOM recommendation does, I have to introduce these three methods 
    // to disambiguate.  If they return false, the corresponding attribute should be
    // considered null.  If they return true, the attribute has been set EVEN IF 
    // it has been set to the empty string
    virtual bool hasNamespaceURI() const = 0;
    virtual bool hasPrefix() const = 0;

    virtual bool hasAttributes() const = 0;
}; // class Node_impl

} // namespace DOM

#endif // JEZUK_DOM_NODE_H
// end of file
