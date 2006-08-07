#ifndef JEZUK_DOM_TRAVERSAL_TREEWALKER_H
#define JEZUK_DOM_TRAVERSAL_TREEWALKER_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/Node.h>

namespace DOM
{

namespace Traversal
{

template<class stringT> class TreeWalker_impl;

template<class stringT>
class TreeWalker : protected DOM::Proxy
{
  public:
    TreeWalker() : Proxy(0) { }
    explicit TreeWalker(TreeWalker_impl<stringT>* const impl) : Proxy(impl) { }
    TreeWalker(const TreeWalker& rhs) : Proxy(rhs) { }
    virtual ~TreeWalker() { }
    bool operator==(const TreeWalker& rhs) const { return Proxy::operator==(rhs); } 
    bool operator!=(const TreeWalker& rhs) const { return Proxy::operator!=(rhs); }
    bool operator==(int dummy) const { return Proxy::operator==(dummy); }
    bool operator!=(int dummy) const { return Proxy::operator!=(dummy); }

    TreeWalker& operator=(const TreeWalker& rhs) 
    {
      Proxy::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////////////////
    // TreeWalker methods
    DOM::Node<stringT> getRoot() const { return Impl()->getRoot(); }

    int getWhatToShow() const { return Impl()->getWhatToShow(); }

    NodeFilter<stringT>* getFilter() const { return Impl()->getFilter(); }

    bool getExpandEntityReferences() const { return Impl()->getExpandEntityReferences(); }

    DOM::Node<stringT> getCurrentNode() const { return Impl()->getCurretNode(); }
    void setCurrentNode(const DOM::Node<stringT>& currentNode) { Impl()->setCurrentNode(currentNode); }

    DOM::Node<stringT> parentNode() const { return Impl()->parentNode(); }

    DOM::Node<stringT> firstChild() const { return Impl()->firstChild(); }
    
    DOM::Node<stringT> lastChild() const { return Impl()->lastChild(); }

    DOM::Node<stringT> previousSibling() const { return Impl()->previousSibling(); }

    DOM::Node<stringT> nextSibling() { return Impl()->nextSibling(); }

    DOM::Node<stringT> previousNode() { return Impl()->prevNode(); }

    DOM::Node<stringT> nextNode() { return Impl()->nextNode(); }

  private:
    TreeWalker_impl<stringT>* Impl() const { return dynamic_cast<TreeWalker_impl<stringT>*>(impl()); }
}; // class TreeWalker

////////////////////////////////////////////////
template<class stringT>
class TreeWalker_impl : virtual public DOM::Impl
{
  public:
    virtual DOM::Node<stringT> getRoot() const = 0;

    virtual int getWhatToShow() const = 0;

    virtual NodeFilter<stringT>* getFilter() const = 0;

    virtual bool getExpandEntityReferences() const = 0;

    virtual DOM::Node<stringT> getCurrentNode() const = 0;

    virtual void setCurrentNode(const DOM::Node<stringT>& currentNode) = 0;

    virtual DOM::Node<stringT> parentNode() const = 0;

    virtual DOM::Node<stringT> firstChild() const = 0;

    virtual DOM::Node<stringT> lastChild() const = 0;

    virtual DOM::Node<stringT> previousSibling() const = 0;

    virtual DOM::Node<stringT> nextSibling() = 0;

    virtual DOM::Node<stringT> previousNode() = 0;

    virtual DOM::Node<stringT> nextNode() = 0;
}; // class TreeWalker_impl

} // namespace Traversal

} // namespace DOM

#endif 
// end of file