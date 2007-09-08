#ifndef JEZUK_DOM_TRAVERSAL_NODEITERATOR_H
#define JEZUK_DOM_TRAVERSAL_NODEITERATOR_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/Traversal/NodeFilter.hpp>
#include <DOM/Node.hpp>

namespace Arabica
{
namespace DOM
{

namespace Traversal
{

template<class stringT, class string_adaptorT> class NodeIterator_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class NodeIterator : protected DOM::Proxy<NodeIterator_impl<stringT, string_adaptorT> >
{
  public:
    typedef NodeFilter<stringT, string_adaptorT> NodeFilterT;
    typedef NodeIterator_impl<stringT, string_adaptorT> NodeIterator_implT;
    typedef DOM::Node<stringT, string_adaptorT> NodeT;

  private:
    typedef DOM::Proxy<NodeIterator_implT> proxy_t;

  public:
    NodeIterator() : proxy_t(0) { }
    explicit NodeIterator(NodeIterator_implT* const impl) : proxy_t(impl) { }
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
    NodeT getRoot() const { return proxy_t::impl()->getRoot(); }

    unsigned long getWhatToShow() const { return proxy_t::impl()->getWhatToShow(); }

    NodeFilterT* getFilter() const { return proxy_t::impl()->getFilter(); }

    bool getExpandEntityReferences() const { return proxy_t::impl()->getExpandEntityReferences(); }

    NodeT nextNode() { return proxy_t::impl()->nextNode(); }

    NodeT previousNode() { return proxy_t::impl()->prevNode(); }

    void detach() { return proxy_t::impl()->detach(); }
}; // class NodeIterator

////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class NodeIterator_impl
{
  public:
    typedef NodeFilter<stringT, string_adaptorT> NodeFilterT;
    typedef DOM::Node<stringT, string_adaptorT> NodeT;

    virtual NodeT getRoot() const = 0;

    virtual unsigned long getWhatToShow() const = 0;

    virtual NodeFilterT* getFilter() const = 0;

    virtual bool getExpandEntityReferences() const = 0;

    virtual NodeT nextNode() = 0;

    virtual NodeT previousNode() = 0;

    virtual void detach() = 0;
}; // class NodeIterator_impl

} // namespace Traversal

} // namespace DOM
} // namespace Arabica

#endif 
// end of file

