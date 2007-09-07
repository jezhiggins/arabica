#ifndef JEZUK_DOM_TRAVERSAL_TREEWALKER_IMPL_H
#define JEZUK_DOM_TRAVERSAL_TREEWALKER_IMPL_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id: TreeWalker.h 2 2002-06-21 11:16:28Z jez_higgins $
/////////////////////////////////////////

#include <DOM/Traversal/DocumentTraversal.hpp>

namespace Arabica
{
namespace DOM
{
namespace Traversal
{

template<class stringT, class string_adaptorT>
class TreeWalkerImpl : public TreeWalker_impl<stringT, string_adaptorT>
{
public:
  typedef DOM::Node<stringT, string_adaptorT> node_t;
  typedef NodeFilter<stringT, string_adaptorT> filter_t;
  typedef typename filter_t::Result filter_result_t;

  TreeWalkerImpl
  (
    node_t root,
    unsigned long whatToShow,
    filter_t* nodeFilter,
    bool expandEntityRef
  ) 
  : root_(root),
    currentNode_(root_),
    whatToShow_(whatToShow), 
    nodeFilter_(nodeFilter), 
    expandEntityRef_(expandEntityRef)
  {}



  //todo: copy ctor, assignment op
  //default ok?

  node_t getRoot() { return root_; }

  unsigned long getWhatToShow() { return whatToShow_; }

  filter_t* getFilter() { return nodeFilter_; }

  bool getExpandEntityReferences() { return expandEntityRef_; }

  node_t getCurrentNode() { return currentNode_; }

  void setCurrentNode(const node_t& currentNode) { currentNode_ = currentNode; }

  node_t parentNode()
  {
    node_t n = getParentNodeImpl(currentNode_);
    if(n != 0)
      currentNode_ = n;
    return n;
  }

  node_t firstChild()
  {
    node_t n = getFirstChildImpl(currentNode_);
    if(n != 0)
      currentNode_ = n;
    return n;
  }

  node_t lastChild()
  {
    node_t n = getLastChildImpl(currentNode_);
    if(n != 0)
      currentNode_ = n;
    return n;
  }

  node_t previousSibling()
  {
    node_t n = getPreviousSiblingImpl(currentNode_);
    if(n != 0)
      currentNode_ = n;
    return n;
  }

  node_t nextSibling()
  {
    node_t n = getPreviousSiblingImpl(currentNode_);
    if(n != 0)
      currentNode_ = n;
    return n;
  }

  node_t previousNode()
  {
    node_t n = getPreviousSiblingImpl(currentNode_);
    if(n != 0)
    {
      node_t last_child = getLastChildImpl(n);
      currentNode_ = (last_child != 0) ? last_child : n;
      return currentNode_;
    }
    else
    {
      n = getParentNodeImpl(n);
      if(n != 0)
        currentNode_ = n;
      return n;
    }
  }

  node_t nextNode()
  {
    node_t n = getFirstChildImpl(currentNode_);
    if(n != 0)
    {
      currentNode_ = n;
      return n;
    }

    n = getNextSiblingImpl(currentNode_);
    if(n != 0)
    {
      currentNode_ = n;
      return n;
    }

    for(node_t parent = getParentNodeImpl(currentNode_); parent != 0; parent = getParentNodeImpl(parent))
    { 
      n = getNextSiblingImpl(parent);
      if(n != 0)
      {
        currentNode_ = n;
        return n;
      }
    }

    return empty_node();
  }

  static const node_t& empty_node()
  {
    static const node_t empty_node_;
    return empty_node_;
  }

protected:
  node_t getParentNodeImpl(node_t& node)
  {
    if(node == 0 || node == root_)
      return empty_node();

    node_t new_node = node.getParentNode();
    if (new_node == 0|| new_node == root_) //todo: check for root here?
      return empty_node();

    filter_result_t accept = acceptNode(new_node);
    if (filter_t::FILTER_ACCEPT == accept)
      return new_node;
    else
      return getParentNodeImpl(new_node);
  }

  node_t getNextSiblingImpl(node_t& node)
  {
    if(node == 0 || node == root_)
      return empty_node();

    node_t new_node = node.getNextSibling();
    if (new_node == 0)
    {
      new_node = node.getParentNode();
      if (new_node == 0 || new_node == root_)
        return empty_node();

      filter_result_t accept = acceptNode(new_node);
      if (filter_t::FILTER_SKIP == accept)
        return getNextSiblingImpl(new_node);
      else
        return empty_node();
    }

    filter_result_t accept = acceptNode(new_node);
    if (filter_t::FILTER_ACCEPT == accept)
      return new_node;
    else if (filter_t::FILTER_SKIP == accept)
    {
      node_t child = getFirstChildImpl(new_node);
      if (child == 0 && !new_node.hasChildNodes())
        return getNextSiblingImpl(new_node);
      else
        return child;
    }
    else
      return getNextSiblingImpl(new_node);
  }
  
  node_t getPreviousSiblingImpl(node_t& node)
  {
    if(node == 0 || node == root_)
      return empty_node();

    node_t new_node = node.getPreviousSibling();
    if (new_node == 0)
    {
      new_node = node.getParentNode();
      if (new_node == 0 || new_node == root_)
        return empty_node();
     
      filter_result_t accept = acceptNode(new_node);
      if (filter_t::FILTER_SKIP == accept)
        return getPreviousSiblingImpl(new_node);
      else
        return empty_node();
    }

    filter_result_t accept = acceptNode(new_node);
    if (filter_t::FILTER_ACCEPT == accept)
      return new_node;
    else if (filter_t::FILTER_SKIP == accept)
    {
      node_t child = getLastChildImpl(new_node);
      if (child == 0 && !new_node.hasChildNodes())
        return getPreviousSiblingImpl(new_node);
      else
        return child;
    }
    else
      return getPreviousSiblingImpl(new_node);
  }

  node_t getFirstChildImpl(node_t& node)
  {
    if(!expandEntityRef_ && node.getNodeType() == node_t::ENTITY_REFERENCE_NODE)
      return empty_node();

    node_t new_node = node.getFirstChild();
    if (new_node == 0)
      return empty_node();

    filter_result_t accept = acceptNode(new_node);
    if (filter_t::FILTER_ACCEPT == accept)
      return new_node;
    else if (filter_t::FILTER_SKIP == accept && new_node.hasChildNodes())
      return getFirstChildImpl(new_node);
    else
      return getNextSiblingImpl(new_node);
  }

  node_t getLastChildImpl(node_t& node)
  {
    if(!expandEntityRef_ && node.getNodeType() == node_t::ENTITY_REFERENCE_NODE)
      return empty_node();

    node_t new_node = node.getLastChild();
    if (new_node == 0)
      return empty_node();

    filter_result_t accept = acceptNode(new_node);
    if (filter_t::FILTER_ACCEPT == accept)
      return new_node;
    else if (filter_t::FILTER_SKIP == accept && new_node.hasChildNodes())
      return getLastChildImpl(new_node);
    else
      return getPreviousSiblingImpl(new_node);
  }
  
  //node-filter will only be checked if what-to-show succeeds
  filter_result_t acceptNode(node_t const& node)
  {
    unsigned long f = 1 << (node.getNodeType() - 1);
    filter_result_t accept = 
      ((whatToShow_ & f) != 0) ? 
      filter_t::FILTER_ACCEPT : 
      filter_t::FILTER_SKIP;

    if (filter_t::FILTER_ACCEPT == accept && nodeFilter_)
    {
      accept = nodeFilter_->acceptNode(node);
    }
    return accept;
  }


private:
  node_t root_;
  node_t currentNode_;
  unsigned long whatToShow_;
  filter_t* nodeFilter_;
  bool expandEntityRef_;

}; // class TreeWalkerImpl


} // namespace Traversal
} // namespace DOM
} // namespace Arabica

#endif //JEZUK_DOM_TRAVERSAL_TREEWALKER_IMPL_H
