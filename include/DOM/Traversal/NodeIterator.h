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
class NodeIterator : protected DOM::Proxy
{
  public:
    NodeIterator() : Proxy(0) { }
    explicit NodeIterator(NodeIterator_impl<stringT>* const impl) : Proxy(impl) { }
    NodeIterator(const NodeIterator& rhs) : Proxy(rhs) { }
    virtual ~NodeIterator() { }
    bool operator==(const NodeIterator& rhs) const { return Proxy::operator==(rhs); } 
    bool operator!=(const NodeIterator& rhs) const { return Proxy::operator!=(rhs); }
    bool operator==(int dummy) const { return Proxy::operator==(dummy); }
    bool operator!=(int dummy) const { return Proxy::operator!=(dummy); }

    NodeIterator& operator=(const NodeIterator& rhs) 
    {
      Proxy::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////////////////
    // NodeIterator methods
    DOM::Node<stringT> getRoot() const { return Impl()->getRoot(); }

    unsigned long getWhatToShow() const { return Impl()->getWhatToShow(); }

    NodeFilter<stringT>* getFilter() const { return Impl()->getFilter(); }

    bool getExpandEntityReferences() const { return Impl()->getExpandEntityReferences(); }

    DOM::Node<stringT> nextNode() { return Impl()->nextNode(); }

    DOM::Node<stringT> previousNode() { return Impl()->prevNode(); }

    void detach() { return Impl()->detach(); }

  private:
    NodeIterator_impl<stringT>* Impl() const { return dynamic_cast<NodeIterator_impl<stringT>*>(impl()); }
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