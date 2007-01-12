#ifndef JEZUK_DOM_TRAVERSAL_NODEITERATOR_H
#define JEZUK_DOM_TRAVERSAL_NODEITERATOR_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/Traversal/NodeFilter.h>
#include <DOM/Node.h>

namespace DOM
{

namespace Traversal
{

template<class stringT> class NodeIterator_impl;

template<class stringT>
class NodeIterator : protected DOM::Proxy<NodeIterator_impl<stringT> >
{
  private:
    typedef DOM::Proxy<NodeIterator_impl<stringT> > proxy_t;

  public:
    NodeIterator() : proxy_t(0) { }
    explicit NodeIterator(NodeIterator_impl<stringT>* const impl) : proxy_t(impl) { }
    NodeIterator(const NodeIterator& rhs) : proxy_t(rhs) { }
    virtual ~NodeIterator() { }
    bool operator==(const NodeIterator& rhs) const { return proxy_t::operator==(rhs); } 
    bool operator!=(const NodeIterator& rhs) const { return proxy_t::operator!=(rhs); }
    bool operator==(int dummy) const { return proxy_t::operator==(dummy); }
    bool operator!=(int dummy) const { return proxy_t::operator!=(dummy); }

    NodeIterator& operator=(const NodeIterator& rhs) 
    {
      proxy_t::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////////////////
    // NodeIterator methods
    DOM::Node<stringT> getRoot() const { return proxy_t::impl()->getRoot(); }

    unsigned long getWhatToShow() const { return proxy_t::impl()->getWhatToShow(); }

    NodeFilter<stringT>* getFilter() const { return proxy_t::impl()->getFilter(); }

    bool getExpandEntityReferences() const { return proxy_t::impl()->getExpandEntityReferences(); }

    DOM::Node<stringT> nextNode() { return proxy_t::impl()->nextNode(); }

    DOM::Node<stringT> previousNode() { return proxy_t::impl()->prevNode(); }

    void detach() { return proxy_t::impl()->detach(); }
}; // class NodeIterator

////////////////////////////////////////////////
template<class stringT>
class NodeIterator_impl
{
  public:
    virtual DOM::Node<stringT> getRoot() const = 0;

    virtual unsigned long getWhatToShow() const = 0;

    virtual NodeFilter<stringT>* getFilter() const = 0;

    virtual bool getExpandEntityReferences() const = 0;

    virtual DOM::Node<stringT> nextNode() = 0;

    virtual DOM::Node<stringT> previousNode() = 0;

    virtual void detach() = 0;
}; // class NodeIterator_impl

} // namespace Traversal

} // namespace DOM

#endif 
// end of file

