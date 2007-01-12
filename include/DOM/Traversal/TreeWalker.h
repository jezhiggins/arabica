#ifndef JEZUK_DOM_TRAVERSAL_TREEWALKER_H
#define JEZUK_DOM_TRAVERSAL_TREEWALKER_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/Node.h>
#include <DOM/Traversal/NodeFilter.h>
#include <DOM/Traversal/TraversalImpl.h>

namespace DOM
{

namespace Traversal
{

template<class stringT> class TreeWalker_impl;

template<class stringT>
class TreeWalker : protected DOM::Proxy<TreeWalker_impl<stringT> >
{
  private:
    typedef DOM::Proxy<TreeWalker_impl<stringT> > proxy_t;
    typedef typename proxy_t::value_type impl_t;
  public:
    TreeWalker() : proxy_t(0) { }
    explicit TreeWalker(TreeWalker_impl<stringT>* const impl) : proxy_t(impl) { }
    TreeWalker(const TreeWalker& rhs) : proxy_t(rhs) { }
    virtual ~TreeWalker() { }
    bool operator==(const TreeWalker& rhs) const { return proxy_t::operator==(rhs); } 
    bool operator!=(const TreeWalker& rhs) const { return proxy_t::operator!=(rhs); }
    bool operator==(int dummy) const { return proxy_t::operator==(dummy); }
    bool operator!=(int dummy) const { return proxy_t::operator!=(dummy); }

    TreeWalker& operator=(const TreeWalker& rhs) 
    {
      proxy_t::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////////////////
    // TreeWalker methods
    DOM::Node<stringT> getRoot() { return proxy_t::impl()->getRoot(); }

    unsigned long getWhatToShow() { return proxy_t::impl()->getWhatToShow(); }

    NodeFilter<stringT>* getFilter() { return proxy_t::impl()->getFilter(); }

    bool getExpandEntityReferences() { return proxy_t::impl()->getExpandEntityReferences(); }

    DOM::Node<stringT> getCurrentNode() { return proxy_t::impl()->getCurrentNode(); }
    void setCurrentNode(const DOM::Node<stringT>& currentNode) { proxy_t::impl()->setCurrentNode(currentNode); }

    DOM::Node<stringT> parentNode() { return proxy_t::impl()->parentNode(); }

    DOM::Node<stringT> firstChild() { return proxy_t::impl()->firstChild(); }
    
    DOM::Node<stringT> lastChild() { return proxy_t::impl()->lastChild(); }

    DOM::Node<stringT> previousSibling() { return proxy_t::impl()->previousSibling(); }

    DOM::Node<stringT> nextSibling() { return proxy_t::impl()->nextSibling(); }

    DOM::Node<stringT> previousNode() { return proxy_t::impl()->previousNode(); }

    DOM::Node<stringT> nextNode() { return proxy_t::impl()->nextNode(); }
}; // class TreeWalker

////////////////////////////////////////////////
template<class stringT>
class TreeWalker_impl : public TraversalImpl
{
  public:
    virtual DOM::Node<stringT> getRoot() = 0;

    virtual unsigned long getWhatToShow() = 0;

    virtual NodeFilter<stringT>* getFilter() = 0;

    virtual bool getExpandEntityReferences() = 0;

    virtual DOM::Node<stringT> getCurrentNode() = 0;

    virtual void setCurrentNode(const DOM::Node<stringT>& currentNode) = 0;

    virtual DOM::Node<stringT> parentNode() = 0;

    virtual DOM::Node<stringT> firstChild() = 0;

    virtual DOM::Node<stringT> lastChild() = 0;

    virtual DOM::Node<stringT> previousSibling() = 0;

    virtual DOM::Node<stringT> nextSibling() = 0;

    virtual DOM::Node<stringT> previousNode() = 0;

    virtual DOM::Node<stringT> nextNode() = 0;
}; // class TreeWalker_impl

} // namespace Traversal

} // namespace DOM

#endif 
// end of file
