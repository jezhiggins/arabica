#ifndef JEZUK_DOM_TRAVERSAL_TREEWALKER_H
#define JEZUK_DOM_TRAVERSAL_TREEWALKER_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/Node.hpp>
#include <DOM/Traversal/NodeFilter.hpp>
#include <DOM/Traversal/TraversalImpl.hpp>

namespace Arabica
{
namespace DOM
{

namespace Traversal
{

template<class stringT, class string_adaptorT> class TreeWalker_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class TreeWalker : protected DOM::Proxy<TreeWalker_impl<stringT, string_adaptorT> >
{
  public:  
    typedef TreeWalker_impl<stringT, string_adaptorT> TreeWalker_implT;
    typedef NodeFilter<stringT, string_adaptorT> NodeFilterT;
    typedef DOM::Node<stringT, string_adaptorT> NodeT;

  private:
    typedef DOM::Proxy<TreeWalker_implT> proxy_t;
    typedef typename proxy_t::value_type impl_t;

  public:
    TreeWalker() : proxy_t(0) { }
    explicit TreeWalker(TreeWalker_implT* const impl) : proxy_t(impl) { }
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
    NodeT getRoot() { return proxy_t::impl()->getRoot(); }

    unsigned long getWhatToShow() { return proxy_t::impl()->getWhatToShow(); }

    NodeFilterT* getFilter() { return proxy_t::impl()->getFilter(); }

    bool getExpandEntityReferences() { return proxy_t::impl()->getExpandEntityReferences(); }

    NodeT getCurrentNode() { return proxy_t::impl()->getCurrentNode(); }
    void setCurrentNode(const NodeT& currentNode) { proxy_t::impl()->setCurrentNode(currentNode); }

    NodeT parentNode() { return proxy_t::impl()->parentNode(); }

    NodeT firstChild() { return proxy_t::impl()->firstChild(); }
    
    NodeT lastChild() { return proxy_t::impl()->lastChild(); }

    NodeT previousSibling() { return proxy_t::impl()->previousSibling(); }

    NodeT nextSibling() { return proxy_t::impl()->nextSibling(); }

    NodeT previousNode() { return proxy_t::impl()->previousNode(); }

    NodeT nextNode() { return proxy_t::impl()->nextNode(); }
}; // class TreeWalker

////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class TreeWalker_impl : public TraversalImpl
{
  public:
    typedef DOM::Node<stringT, string_adaptorT> NodeT;
    typedef NodeFilter<stringT, string_adaptorT> NodeFilterT;

    virtual NodeT getRoot() = 0;

    virtual unsigned long getWhatToShow() = 0;

    virtual NodeFilterT* getFilter() = 0;

    virtual bool getExpandEntityReferences() = 0;

    virtual NodeT getCurrentNode() = 0;

    virtual void setCurrentNode(const NodeT& currentNode) = 0;

    virtual NodeT parentNode() = 0;

    virtual NodeT firstChild() = 0;

    virtual NodeT lastChild() = 0;

    virtual NodeT previousSibling() = 0;

    virtual NodeT nextSibling() = 0;

    virtual NodeT previousNode() = 0;

    virtual NodeT nextNode() = 0;
}; // class TreeWalker_impl

} // namespace Traversal

} // namespace DOM
} // namespace Arabica

#endif 
// end of file
