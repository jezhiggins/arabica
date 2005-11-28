#ifndef JEZUK_DOM_NODE_H
#define JEZUK_DOM_NODE_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////
#include <DOM/Proxy.h>
#include <DOM/DOMException.h>
#include <typeinfo>
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
template<class node_string_type>
class Node : public Node_base
{
  public:
    typedef node_string_type string_type;

    Node() : impl_() { }
    Node(Node_impl<string_type>* const impl) : impl_(impl) { }
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

    string_type getNodeName() const { return impl_->getNodeName(); }

    string_type getNodeValue() const { return impl_->getNodeValue(); }
    void setNodeValue(const string_type& nodeValue) { impl_->setNodeValue(nodeValue); }

    Type getNodeType() const { return impl_->getNodeType(); }
    
    Node getParentNode() const { return impl_->getParentNode(); }

    const NodeList<string_type> getChildNodes() const { return NodeList<string_type>(impl_->getChildNodes()); }
    
    Node getFirstChild() const { return impl_->getFirstChild(); }
    Node getLastChild() const { return impl_->getLastChild(); }
    Node getPreviousSibling() const { return impl_->getPreviousSibling(); }
    Node getNextSibling() const { return impl_->getNextSibling(); }

    const NamedNodeMap<string_type> getAttributes() const { return NamedNodeMap<string_type>(impl_->getAttributes()); }

    Document<string_type> getOwnerDocument() const { return impl_->getOwnerDocument(); }

    Node insertBefore(const Node& newChild, const Node& refChild) { return impl_->insertBefore(*newChild.impl_, *refChild.impl_); } 
    Node replaceChild(const Node& newChild, const Node& oldChild) { return impl_->replaceChild(*newChild.impl_, *oldChild.impl_); }
    Node removeChild(const Node& oldChild) { return impl_->removeChild(*oldChild.impl_); } 
    Node appendChild(const Node& newChild) { return impl_->appendChild(*newChild.impl_); }
    void purgeChild(Node& oldChild) 
    { 
      Node_impl<string_type>* child = *oldChild.impl_;
      oldChild = 0;

      try {
        impl_->purgeChild(child); 
      }
      catch(DOMException&)
      {
        oldChild = child;
        throw;
      } // catch
    } // purge
 
    bool hasChildNodes() const { return impl_->hasChildNodes(); }

    Node cloneNode(bool deep) const { return impl_->cloneNode(deep); }

    void normalize() { impl_->normalize(); }

    bool isSupported(const string_type& feature, const string_type& version) const { return impl_->isSupported(feature, version); }

    string_type getNamespaceURI() const { return impl_->getNamespaceURI(); }
    string_type getPrefix() const { return impl_->getPrefix(); }
    void setPrefix(const string_type& prefix) const { impl_->setPrefix(prefix); }
    string_type getLocalName() const { return impl_->getLocalName(); }

    // additional three methods - since C++ std::string (and by implication
    // string_type) don't differenciate between a null string and an empty string,
    // but the DOM recommendation does, I have to introduce these three methods 
    // to disambiguate.  If they return false, the corresponding attribute should be
    // considered null.  If they return true, the attribute has been set EVEN IF 
    // it has been set to the empty string
    bool hasNamespaceURI() const { return impl_->hasNamespaceURI(); } 
    bool hasPrefix() const { return impl_->hasPrefix(); }

    bool hasAttributes() const { return impl_->hasAttributes(); }

    // you almost certainly don't need to use this function
    Node_impl<string_type>* unlying_impl() const { return *impl_; }

  protected:
    Proxy<Node_impl<string_type> > impl_;

    typedef class Document<string_type> DocumentT;
    friend class Document<string_type>;
    typedef class Events::EventTarget<string_type> EventTargetT;
    friend class Events::EventTarget<string_type>;
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
    virtual ~Node_impl() { }

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() = 0;
    virtual void releaseRef() = 0;

    ///////////////////////////////////////////////////////
    // Node methods
    virtual string_type getNodeName() const = 0;

    virtual string_type getNodeValue() const = 0;
    virtual void setNodeValue(const string_type& nodeValue) = 0;

    virtual Node_base::Type getNodeType() const = 0;
    
    virtual Node_impl<string_type>* getParentNode() const = 0;

    virtual NodeList_impl<string_type>* getChildNodes() const = 0;
    
    virtual Node_impl<string_type>* getFirstChild() const = 0;
    virtual Node_impl<string_type>* getLastChild() const = 0;

    virtual Node_impl<string_type>* getPreviousSibling() const = 0;
    virtual Node_impl<string_type>* getNextSibling() const = 0;

    virtual NamedNodeMap_impl<string_type>* getAttributes() const = 0;

    virtual Document_impl<string_type>* getOwnerDocument() const = 0;

    virtual Node_impl<string_type>* insertBefore(Node_impl<string_type>* newChild, Node_impl<string_type>* refChild) = 0;
    virtual Node_impl<string_type>* replaceChild(Node_impl<string_type>*  newChild, Node_impl<string_type>* oldChild) = 0;
    virtual Node_impl<string_type>* removeChild(Node_impl<string_type>*  oldChild) = 0;
    virtual Node_impl<string_type>* appendChild(Node_impl<string_type>*  newChild) = 0;
    virtual void purgeChild(Node_impl<string_type>* oldChild) = 0;

    virtual bool hasChildNodes() const = 0;

    virtual Node_impl<string_type>* cloneNode(bool deep) const = 0;

    virtual void normalize() = 0;

    virtual bool isSupported(const string_type& feature, const string_type& version) const = 0;

    virtual string_type getNamespaceURI() const = 0;
    virtual string_type getPrefix() const = 0;
    virtual void setPrefix(const string_type& prefix) = 0;
    virtual string_type getLocalName() const = 0;

    // additional methods - since C++ std::string (and by implication
    // string_type) don't differenciate between a null string and an empty string,
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
