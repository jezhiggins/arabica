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
  public:
    typedef DOM::Proxy<TreeWalker_impl<stringT> > proxy_t;
    typedef typename proxy_t::value_type impl_t;

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
    DOM::Node<stringT> getRoot() { return Impl()->getRoot(); }

    unsigned long getWhatToShow() { return Impl()->getWhatToShow(); }

    NodeFilter<stringT>* getFilter() { return Impl()->getFilter(); }

    bool getExpandEntityReferences() { return Impl()->getExpandEntityReferences(); }

    DOM::Node<stringT> getCurrentNode() { return Impl()->getCurrentNode(); }
    void setCurrentNode(const DOM::Node<stringT>& currentNode) { Impl()->setCurrentNode(currentNode); }

    DOM::Node<stringT> parentNode() { return Impl()->parentNode(); }

    DOM::Node<stringT> firstChild() { return Impl()->firstChild(); }
    
    DOM::Node<stringT> lastChild() { return Impl()->lastChild(); }

    DOM::Node<stringT> previousSibling() { return Impl()->previousSibling(); }

    DOM::Node<stringT> nextSibling() { return Impl()->nextSibling(); }

    DOM::Node<stringT> previousNode() { return Impl()->previousNode(); }

    DOM::Node<stringT> nextNode() { return Impl()->nextNode(); }

  private:
    impl_t* Impl() { return impl(); }
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
