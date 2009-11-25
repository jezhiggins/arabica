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

template<class stringT, class string_adaptorT> class Node;
template<class stringT, class string_adaptorT> class NamedNodeMap_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class NamedNodeMap 
{
  public:
    typedef Node<stringT, string_adaptorT> NodeT;
 
    NamedNodeMap() : impl_(0) { }
    explicit NamedNodeMap(NamedNodeMap_impl<stringT, string_adaptorT>* impl) : impl_(impl) { }
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

    NodeT getNamedItem(const stringT& name) const { return NodeT(impl_->getNamedItem(name)); }

    NodeT setNamedItem(const NodeT& arg) { return NodeT(impl_->setNamedItem(*arg.impl_)); }

    NodeT removeNamedItem(const stringT& name) const { return NodeT(impl_->removeNamedItem(name)); }

    NodeT item(unsigned int index) const { return NodeT(impl_->item(index)); }

    unsigned int getLength() const { return impl_->getLength(); }

    NodeT getNamedItemNS(const stringT& namespaceURI, const stringT& localName) const 
    { 
      return NodeT(impl_->getNamedItemNS(namespaceURI, localName)); 
    } // getNamedItemNS

    NodeT setNamedItemNS(const NodeT& arg) { return NodeT(impl_->setNamedItemNS(*arg.impl_)); }

    NodeT removeNamedItemNS(const stringT& namespaceURI, const stringT& localName) const 
    { 
      return NodeT(impl_->removeNamedItemNS(namespaceURI, localName)); 
    } // removeNamedItemNS

  private:
    Proxy<NamedNodeMap_impl<stringT, string_adaptorT> > impl_;
}; // class NamedNodeMap

////////////////////////////////////////////////////
// NamedNodeMap_impl
template<class stringT, class string_adaptorT> class Node_impl;

template<class stringT, class string_adaptorT>
class NamedNodeMap_impl 
{
  public:
    typedef Node_impl<stringT, string_adaptorT> Node_implT;

    virtual ~NamedNodeMap_impl() { }

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() = 0;
    virtual void releaseRef() = 0;

    ///////////////////////////////////////////////////////
    // NamedNodeMap methods
    virtual Node_implT* getNamedItem(const stringT& name) const = 0;
    virtual Node_implT* setNamedItem(Node_implT* arg) = 0;
    virtual Node_implT* removeNamedItem(const stringT& name) = 0;

    virtual Node_implT* item(unsigned int index) const = 0;

    virtual unsigned int getLength() const = 0;

    virtual Node_implT* getNamedItemNS(const stringT& namespaceURI, const stringT& localName) const  = 0;
    virtual Node_implT* setNamedItemNS(Node_implT* arg) = 0;
    virtual Node_implT* removeNamedItemNS(const stringT& namespaceURI, const stringT& localName) = 0;
}; // class NamedNodeMap_impl

} // namespace DOM
} // namespace Arabica

#endif

