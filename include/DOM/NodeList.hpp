#ifndef JEZUK_DOM_NODELIST_H
#define JEZUK_DOM_NODELIST_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>

namespace Arabica
{
namespace DOM
{

template<class stringT, class string_adaptorT> class Node;
template<class stringT, class string_adaptorT> class NodeList_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class NodeList 
{
  public:
    NodeList() : impl_(0) { }
    explicit NodeList(NodeList_impl<stringT, string_adaptorT>* const impl) : impl_(impl) { }
    NodeList(const NodeList& rhs) : impl_(rhs.impl_) { }
    virtual ~NodeList() { }

    bool operator==(const NodeList& rhs) const { return impl_ == rhs.impl_; } 
    bool operator!=(const NodeList& rhs) const { return impl_ != rhs.impl_; }
    bool operator==(int dummy) const { return impl_ == dummy; }
    bool operator!=(int dummy) const { return impl_ != dummy; }

    NodeList& operator=(const NodeList& rhs) 
    {
      impl_ = rhs.impl_;
      return *this;
    } // operator=

    Node<stringT, string_adaptorT> item(unsigned int index) const { return impl_->item(index); }

    unsigned int getLength() const { return impl_->getLength(); }

  private:
    Proxy<NodeList_impl<stringT, string_adaptorT> > impl_;
}; // class NodeList

/////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class NodeList_impl 
{
  public:
    virtual ~NodeList_impl() { }

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef() = 0;
    virtual void releaseRef() = 0;

    ///////////////////////////////////////////////////////
    // NodeList methods
    virtual Node_impl<stringT, string_adaptorT>* item(unsigned int index) const = 0;

    virtual unsigned int getLength() const = 0;
}; // class NodeList_impl

} // namespace DOM
} // namespace Arabica

#endif

