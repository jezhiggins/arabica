#ifndef JEZUK_DOM_NODE_H
#define JEZUK_DOM_NODE_H

////////////////////////////
// C++ DOM definition
////////////////////////////
#include <DOM/Proxy.hpp>
#include <DOM/DOMException.hpp>
#include <Arabica/StringAdaptor.hpp>


#include <typeinfo>
#include <algorithm>

namespace Arabica
{
namespace DOM
{

namespace Events {
  template<class stringT, class string_adaptorT> class EventTarget;
} // namespace Events

template<class stringT, class string_adaptorT> class Document;
template<class stringT, class string_adaptorT> class NodeList;
template<class stringT, class string_adaptorT> class NamedNodeMap;
template<class stringT, class string_adaptorT> class Node_impl;

class Node_base
{
public:
  typedef int Type;

  static const int ELEMENT_NODE = 1;
  static const int ATTRIBUTE_NODE = 2;
  static const int TEXT_NODE = 3;
  static const int CDATA_SECTION_NODE = 4;
  static const int ENTITY_REFERENCE_NODE = 5;
  static const int ENTITY_NODE = 6;
  static const int PROCESSING_INSTRUCTION_NODE = 7;
  static const int COMMENT_NODE = 8;
  static const int DOCUMENT_NODE = 9;
  static const int DOCUMENT_TYPE_NODE = 10;
  static const int DOCUMENT_FRAGMENT_NODE = 11;
  static const int NOTATION_NODE = 12;
  static const int MAX_TYPE = 13;
}; // class Node_base

/////////////////////////////////////////////////
template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class Node : public Node_base
{
  public:
    Node() : impl_() { }
    Node(Node_impl<stringT, string_adaptorT>* const impl) : impl_(impl) { }
    Node(const Node& rhs) : impl_(rhs.impl_) { }
    virtual ~Node() { }

    operator bool() const { return impl_; }
    bool operator< (const Node& rhs) const { return impl_ < rhs.impl_; }
    bool operator==(const Node& rhs) const { return impl_ == rhs.impl_; }
    bool operator!=(const Node& rhs) const { return impl_ != rhs.impl_; }
    bool operator==(int dummy) const { return impl_ == dummy; }
    bool operator!=(int dummy) const { return impl_ != dummy; }

    Node& operator=(const Node& rhs)
    {
      impl_ = rhs.impl_;
      return *this;
    } // operator=

    const stringT& getNodeName() const { return impl_->getNodeName(); }

    const stringT& getNodeValue() const { return impl_->getNodeValue(); }
    void setNodeValue(const stringT& nodeValue) { impl_->setNodeValue(nodeValue); }

    Type getNodeType() const { return impl_->getNodeType(); }

    Node getParentNode() const { return impl_->getParentNode(); }

    const NodeList<stringT, string_adaptorT> getChildNodes() const { return NodeList<stringT, string_adaptorT>(impl_->getChildNodes()); }

    Node getFirstChild() const { return impl_->getFirstChild(); }
    Node getLastChild() const { return impl_->getLastChild(); }
    Node getPreviousSibling() const { return impl_->getPreviousSibling(); }
    Node getNextSibling() const { return impl_->getNextSibling(); }

    const NamedNodeMap<stringT, string_adaptorT> getAttributes() const { return NamedNodeMap<stringT, string_adaptorT>(impl_->getAttributes()); }

    Document<stringT, string_adaptorT> getOwnerDocument() const { return impl_->getOwnerDocument(); }

    Node insertBefore(const Node& newChild, const Node& refChild) { return impl_->insertBefore(*newChild.impl_, *refChild.impl_); }
    Node replaceChild(const Node& newChild, const Node& oldChild) { return impl_->replaceChild(*newChild.impl_, *oldChild.impl_); }
    Node removeChild(const Node& oldChild) { return impl_->removeChild(*oldChild.impl_); }
    Node appendChild(const Node& newChild) { return impl_->appendChild(*newChild.impl_); }
    void purgeChild(Node& oldChild)
    {
      Node_impl<stringT, string_adaptorT>* child = *oldChild.impl_;
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

    bool isSupported(const stringT& feature, const stringT& version) const { return impl_->isSupported(feature, version); }

    const stringT& getNamespaceURI() const { return impl_->getNamespaceURI(); }
    const stringT& getPrefix() const { return impl_->getPrefix(); }
    void setPrefix(const stringT& prefix) const { impl_->setPrefix(prefix); }
    const stringT& getLocalName() const { return impl_->getLocalName(); }

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
    Node_impl<stringT, string_adaptorT>* underlying_impl() const { return *impl_; }
    void set_underlying_impl(Node_impl<stringT, string_adaptorT>* new_impl) { impl_ = new_impl; }

  protected:
    Proxy<Node_impl<stringT, string_adaptorT> > impl_;

    typedef class Document<stringT, string_adaptorT> DocumentT;
    friend class Document<stringT, string_adaptorT>;
    friend class NamedNodeMap<stringT, string_adaptorT>;
    typedef class Events::EventTarget<stringT, string_adaptorT> EventTargetT;
    friend class Events::EventTarget<stringT, string_adaptorT>;
}; // class Node

////////////////////////////////////////////////////////////////////
// derive from this class to implement your own
// DOM provider
template<class stringT, class string_adaptorT> class Document_impl;
template<class stringT, class string_adaptorT> class NodeList_impl;
template<class stringT, class string_adaptorT> class NamedNodeMap_impl;

template<class stringT, class string_adaptorT>
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
    virtual const stringT& getNodeName() const = 0;

    virtual const stringT& getNodeValue() const = 0;
    virtual void setNodeValue(const stringT& nodeValue) = 0;

    virtual Node_base::Type getNodeType() const = 0;

    virtual Node_impl<stringT, string_adaptorT>* getParentNode() const = 0;

    virtual NodeList_impl<stringT, string_adaptorT>* getChildNodes() const = 0;

    virtual Node_impl<stringT, string_adaptorT>* getFirstChild() const = 0;
    virtual Node_impl<stringT, string_adaptorT>* getLastChild() const = 0;

    virtual Node_impl<stringT, string_adaptorT>* getPreviousSibling() const = 0;
    virtual Node_impl<stringT, string_adaptorT>* getNextSibling() const = 0;

    virtual NamedNodeMap_impl<stringT, string_adaptorT>* getAttributes() const = 0;

    virtual Document_impl<stringT, string_adaptorT>* getOwnerDocument() const = 0;

    virtual Node_impl<stringT, string_adaptorT>* insertBefore(Node_impl<stringT, string_adaptorT>* newChild, Node_impl<stringT, string_adaptorT>* refChild) = 0;
    virtual Node_impl<stringT, string_adaptorT>* replaceChild(Node_impl<stringT, string_adaptorT>*  newChild, Node_impl<stringT, string_adaptorT>* oldChild) = 0;
    virtual Node_impl<stringT, string_adaptorT>* removeChild(Node_impl<stringT, string_adaptorT>*  oldChild) = 0;
    virtual Node_impl<stringT, string_adaptorT>* appendChild(Node_impl<stringT, string_adaptorT>*  newChild) = 0;
    virtual void purgeChild(Node_impl<stringT, string_adaptorT>* oldChild) = 0;

    virtual bool hasChildNodes() const = 0;

    virtual Node_impl<stringT, string_adaptorT>* cloneNode(bool deep) const = 0;

    virtual void normalize() = 0;

    virtual bool isSupported(const stringT& feature, const stringT& version) const = 0;

    virtual const stringT& getNamespaceURI() const = 0;
    virtual const stringT& getPrefix() const = 0;
    virtual void setPrefix(const stringT& prefix) = 0;
    virtual const stringT& getLocalName() const = 0;

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
} // namespace Arabica

#endif // JEZUK_DOM_NODE_H
// end of file
