#ifndef JEZUK_DOM_NAMEDNODEMAP_H
#define JEZUK_DOM_NAMEDNODEMAP_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Proxy.hpp>

namespace Arabica
{
namespace DOM
{

template<class stringT> class Node;
template<class stringT> class NamedNodeMap_impl;

template<class stringT>
class NamedNodeMap 
{
  public:
    NamedNodeMap() : impl_(0) { }
    explicit NamedNodeMap(NamedNodeMap_impl<stringT>* impl) : impl_(impl) { }
    NamedNodeMap(const NamedNodeMap& rhs) : impl_(rhs.impl_) { }
    virtual ~NamedNodeMap() { }

    bool operator==(const NamedNodeMap& rhs) const { return impl_ == rhs.impl_; } 
    bool operator!=(const NamedNodeMap& rhs) const { return impl_ != rhs.impl_; }
    bool operator==(int dummy) const { return impl_ == dummy; }
    bool operator!=(int dummy) const { return impl_ != dummy; }

    NamedNodeMap& operator=(const NamedNodeMap& rhs) 
    {
      impl_ = rhs.impl_;
      return *this;
    } // operator=

    Node<stringT> getNamedItem(const stringT& name) const { return Node<stringT>(impl_->getNamedItem(name)); }

    Node<stringT> setNamedItem(const Node<stringT>& arg) { return Node<stringT>(impl_->setNamedItem(arg)); }

    Node<stringT> removeNamedItem(const stringT& name) const { return Node<stringT>(impl_->removeNamedItem(name)); }

    Node<stringT> item(unsigned int index) const { return Node<stringT>(impl_->item(index)); }

    unsigned int getLength() const { return impl_->getLength(); }

    Node<stringT> getNamedItemNS(const stringT& namespaceURI, const stringT& localName) const 
    { 
      return Node<stringT>(impl_->getNamedItemNS(namespaceURI, localName)); 
    } // getNamedItemNS

    Node<stringT> setNamedItemNS(const Node<stringT>& arg) { return Node<stringT>(impl_->setNamedItemNS(arg)); }

    Node<stringT> removeNamedItemNS(const stringT& namespaceURI, const stringT& localName) const 
    { 
      return Node<stringT>(impl_->removeNamedItem(namespaceURI, localName)); 
    } // removeNamedItemNS

  private:
    Proxy<NamedNodeMap_impl<stringT> > impl_;
}; // class NamedNodeMap

////////////////////////////////////////////////////
// NamedNodeMap_impl
template<class stringT> class Node_impl;

template<class stringT>
class NamedNodeMap_impl 
{
  public:
    virtual ~NamedNodeMap_impl() { }

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() = 0;
    virtual void releaseRef() = 0;

    ///////////////////////////////////////////////////////
    // NamedNodeMap methods
    virtual Node_impl<stringT>* getNamedItem(const stringT& name) const = 0;
    virtual Node_impl<stringT>* setNamedItem(Node_impl<stringT>* arg) = 0;
    virtual Node_impl<stringT>* removeNamedItem(const stringT& name) = 0;

    virtual Node_impl<stringT>* item(unsigned int index) const = 0;

    virtual unsigned int getLength() const = 0;

    virtual Node_impl<stringT>* getNamedItemNS(const stringT& namespaceURI, const stringT& localName) const  = 0;
    virtual Node_impl<stringT>* setNamedItemNS(Node_impl<stringT>* arg) = 0;
    virtual Node_impl<stringT>* removeNamedItemNS(const stringT& namespaceURI, const stringT& localName) = 0;
}; // class NamedNodeMap_impl

} // namespace DOM
} // namespace Arabica

#endif

