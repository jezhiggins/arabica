#ifndef ARABICA_XPATHIC_XPATH_AXIS_ENUMERATOR_H
#define ARABICA_XPATHIC_XPATH_AXIS_ENUMERATOR_H

#include <DOM/Node.hpp>
#include <DOM/Document.hpp>
#include <DOM/NamedNodeMap.hpp>
#include "xpath_namespace_node.hpp"
#include "xpath_object.hpp"

namespace Arabica
{
namespace XPath
{

enum Axis
{
  ANCESTOR,
  ANCESTOR_OR_SELF,
  ATTRIBUTE,
  CHILD,
  DESCENDANT,
  DESCENDANT_OR_SELF,
  FOLLOWING,
  FOLLOWING_SIBLING,
  NAMESPACE,
  PARENT,
  PRECEDING,
  PRECEDING_SIBLING,
  SELF
}; // Axis

namespace impl
{
template<class string_type, class string_adaptor> class AxisWalker;

template<class axis_walker, class string_type, class string_adaptor>
AxisWalker<string_type, string_adaptor>* CreateAxis(const DOM::Node<string_type, string_adaptor>& context) 
{ 
  return new axis_walker(context.underlying_impl()); 
} // CreateAxis

} // namespace impl

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class AxisEnumerator
{
  typedef impl::AxisWalker<string_type, string_adaptor>* (*CreateAxisPtr)(const DOM::Node<string_type, string_adaptor>& context);

  struct NamedAxis { Axis name; CreateAxisPtr creator; };
  static const NamedAxis AxisLookupTable[];

public:
  AxisEnumerator(const DOM::Node<string_type, string_adaptor>& context, Axis axis) :
      walker_(0),
      node_(0)
  { 
    for(const NamedAxis* ax = AxisLookupTable; ax->creator != 0; ++ax)
      if(axis == ax->name)
        walker_ = ax->creator(context);

    if(!walker_)
      throw std::runtime_error("Unknown Axis specifier");
    grab();
  } // AxisEnumerator

  AxisEnumerator(const AxisEnumerator& rhs) :
    walker_(rhs.walker_->clone())
  {
    grab();
  } // AxisEnumerator

  AxisEnumerator& operator=(const AxisEnumerator& rhs)
  {
    impl::AxisWalker<string_type, string_adaptor>* newwalker = rhs.walker_->clone();
    delete walker_;
    walker_ = newwalker;
    grab();
    return *this;
  } // operator=

  ~AxisEnumerator() 
  {
    delete walker_;
  } // ~AxisEnumerator

  bool forward() const { return walker_->forward(); }
  bool reverse() const { return !walker_->forward(); }
  const DOM::Node<string_type, string_adaptor>& operator*() const { return node_; }
  const DOM::Node<string_type, string_adaptor>* operator->() const { return &node_; }
  AxisEnumerator& operator++() { advance(); return *this; }
  AxisEnumerator operator++(int) { AxisEnumerator copy(*this); advance(); return copy; }

private:
  void advance() 
  {
    walker_->advance();
    grab();
  } // advance
  void grab()
  {
    node_.set_underlying_impl(walker_->get());
  } // grab

  impl::AxisWalker<string_type, string_adaptor>* walker_;  
  mutable DOM::Node<string_type, string_adaptor> node_;

  AxisEnumerator();
}; // class AxisEnumerator  


////////////////////////////////////////////////////
namespace impl 
{

template<class string_type, class string_adaptor>
class AxisWalker
{
public:
  virtual ~AxisWalker() { }
  DOM::Node_impl<string_type, string_adaptor>* get() const { return current_; }
  virtual void advance() = 0;
  bool forward() { return forward_; }
  virtual AxisWalker<string_type, string_adaptor>* clone() const = 0;

protected:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;

  AxisWalker(bool forward) : current_(0), forward_(forward) { }
  AxisWalker(const AxisWalker& rhs) : current_(rhs.current_), forward_(rhs.forward_) { }
  void set(const RawNodeT current) { current_ = current; }
  void end() { current_ = 0; }

  static RawNodeT walkDown(const RawNodeT context, 
                           const RawNodeT origin)
  {
    if(context->getNodeType() == DOM::Node_base::ATTRIBUTE_NODE)
      return 0;

    RawNodeT next = context->getFirstChild();
    if((next == 0) && (context == origin)) // node with no children
      return 0;

    if(next != 0)
      return next;

    next = findNextSibling(context);
    if(next != 0)
      return next;
            
    RawNodeT parent = context->getParentNode();
    while(parent != origin && next == 0)
    {
      next = parent->getNextSibling();
      parent = parent->getParentNode();
    } // while ...

    return next;
  } // walkDown

  static RawNodeT findNextSibling(const RawNodeT node)
  {
    if(!nodeIsText(node))
      return node->getNextSibling();

    RawNodeT next = node->getNextSibling();
    while((next != 0) && nodeIsText(next))
      next = next->getNextSibling();
    return next;
  } // findNextSibling

  static RawNodeT findPreviousSibling(const RawNodeT node)
  {
    RawNodeT prev = node->getPreviousSibling();

    if((prev == 0) || (!nodeIsText(prev)))
      return prev;

    RawNodeT prev_again = prev->getPreviousSibling();
    while((prev_again != 0) && (nodeIsText(prev_again)))
    {
      prev = prev_again;
      prev_again = prev->getPreviousSibling();
    } // while

    return prev;
  } // findPreviousSibling

private:
  static bool nodeIsText(const RawNodeT node)
  {
    return (node->getNodeType() == DOM::Node_base::TEXT_NODE) ||
           (node->getNodeType() == DOM::Node_base::CDATA_SECTION_NODE);
  } // nodeIsText

  RawNodeT current_;
  bool forward_;

  AxisWalker& operator=(const AxisWalker&);
  bool operator==(const AxisWalker&);
}; // AxisWalker

template<class string_type, class string_adaptor>
class AncestorAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef DOM::Node_impl<string_type, string_adaptor> const* RawNodeT;
  typedef AxisWalker<string_type, string_adaptor> BaseT;

public:
  AncestorAxisWalker(const RawNodeT context) : AxisWalker<string_type, string_adaptor>(false)
  {
    if(context == 0)
      return;

    if(context->getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      BaseT::set(context->getParentNode());
    else
      BaseT::set((dynamic_cast<const DOM::Attr_impl<string_type, string_adaptor>* const>(context))->getOwnerElement());
  } // AncestorAxisWalker

  virtual void advance()
  {
    if(BaseT::get() != 0)
      BaseT::set(BaseT::get()->getParentNode());
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new AncestorAxisWalker(*this); }

private:
  AncestorAxisWalker(const AncestorAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class AncestorAxisWalker

template<class string_type, class string_adaptor>
class AncestorOrSelfAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;

  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  AncestorOrSelfAxisWalker(const RawNodeT context) : AxisWalker<string_type, string_adaptor>(false)
  {
    if(context != 0)
      BaseT::set(context);
  } // AncestorAxisWalker

  virtual void advance()
  {
    if(BaseT::get() == 0)
      return;

    if(BaseT::get()->getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      BaseT::set(BaseT::get()->getParentNode());
    else
      BaseT::set((dynamic_cast<const DOM::Attr_impl<string_type, string_adaptor>* const>(BaseT::get()))->getOwnerElement());
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new AncestorOrSelfAxisWalker(*this); }

private:
  AncestorOrSelfAxisWalker(const AncestorOrSelfAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class AncestorOrSelfAxisWalker

template<class string_type, class string_adaptor>
class AttributeAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;


  AttributeAxisWalker(const RawNodeT context) : AxisWalker<string_type, string_adaptor>(true),
      index_(0), count_(0)
  { 
    if((context != 0) && (context->hasAttributes()))
    {
      attrs_ = context->getAttributes();
      count_ = attrs_->getLength();
      set_next();
    } // if ...
  } // AttributeAxisWalker

  virtual void advance()
  {
    if(BaseT::get() == 0)
      return;
    set_next();
  } // advance

  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new AttributeAxisWalker(*this); } 

private:
  AttributeAxisWalker(const AttributeAxisWalker& rhs) : 
        AxisWalker<string_type, string_adaptor>(rhs), 
        attrs_(rhs.attrs_), 
        index_(rhs.index_),
        count_(rhs.count_) { }

  DOM::NamedNodeMap_impl<string_type, string_adaptor>* attrs_;
  unsigned int index_;
  unsigned int count_;

  void set_next() 
  {
    if(index_ == count_)
    {
      BaseT::end();
      return;
    } // if ...

    RawNodeT a;
    do
    {
      a = attrs_->item(index_++);
    } while ((a != 0) && (a->getNamespaceURI() == string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/")));

    BaseT::set(a);
  } // set_next
}; // class AttributeAxisEnumerator

template<class string_type, class string_adaptor>
class ChildAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;


  ChildAxisWalker(const RawNodeT context) : AxisWalker<string_type, string_adaptor>(true)
  {
    if(context != 0)
      BaseT::set(context->getFirstChild());
  } // ChildAxisWalker

  virtual void advance() 
  { 
    if(BaseT::get() != 0)
      BaseT::set(BaseT::findNextSibling(BaseT::get()));
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new ChildAxisWalker(*this); } 

private:
  ChildAxisWalker(const ChildAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class ChildAxisWalker

template<class string_type, class string_adaptor>
class DescendantAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;


  DescendantAxisWalker(const RawNodeT context) : AxisWalker<string_type, string_adaptor>(true),
      origin_(context)
  {
    if((context != 0) && (context->getNodeType() != DOM::Node_base::ATTRIBUTE_NODE))
      BaseT::set(context->getFirstChild());
  } // DescendantAxisWalker

  virtual void advance()
  {
    BaseT::set(nextDescendant());
  } // advance

  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new DescendantAxisWalker(*this); }

private:
  RawNodeT nextDescendant()
  {
    RawNodeT next = BaseT::get()->getFirstChild();
    if(next == 0)
      next = BaseT::findNextSibling(BaseT::get());
    if(next != 0)
      return next;
          
    RawNodeT parent = BaseT::get()->getParentNode();
    while(parent != origin_ && next == 0)
    {
      next = parent->getNextSibling();
      parent = parent->getParentNode();
    } // while ...

    return next;
  } // nextDescendant

  DescendantAxisWalker(const DescendantAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs), origin_(rhs.origin_) { }
  const RawNodeT origin_;
}; // class DescendantAxisWalker

template<class string_type, class string_adaptor>
class DescendantOrSelfAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;


  DescendantOrSelfAxisWalker(const RawNodeT context) : AxisWalker<string_type, string_adaptor>(true),
      origin_(context)
  {
    if(context != 0)
      BaseT::set(context);
  } // DescendantOrSelfAxisWalker

  virtual void advance()
  {
    BaseT::set(BaseT::walkDown(BaseT::get(), origin_));
  } // advance

  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new DescendantOrSelfAxisWalker(*this); }

private:
  DescendantOrSelfAxisWalker(const DescendantOrSelfAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs), origin_(rhs.origin_) { }
  const RawNodeT origin_;
}; // class DescendantOrSelfAxisWalker

template<class string_type, class string_adaptor>
class FollowingAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;


  FollowingAxisWalker(const RawNodeT context) : AxisWalker<string_type, string_adaptor>(true)
  {
    BaseT::set(firstFollowing(context));
  } // FollowingAxisWalker

  virtual void advance()
  {
    BaseT::set(BaseT::walkDown(BaseT::get(), BaseT::get()->getOwnerDocument()));
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new FollowingAxisWalker(*this); }

private:
  RawNodeT firstFollowing(const RawNodeT context) const
  {
    if(context->getNodeType() == DOM::Node_base::ATTRIBUTE_NODE)
    {
      RawNodeT owner = dynamic_cast<const DOM::Attr_impl<string_type, string_adaptor>* const>(context)->getOwnerElement();
      if(owner->hasChildNodes())
        return owner->getFirstChild();
      return firstFollowing(owner);
    } // if attribute

    RawNodeT next = BaseT::findNextSibling(context);

    if(next != 0)
      return next;
          
    RawNodeT parent = context->getParentNode();
    while(parent != context->getOwnerDocument() && next == 0)
    {
      next = parent->getNextSibling();
      parent = parent->getParentNode();
    } // while ...

    return next;
  } // firstFollowing

  FollowingAxisWalker(const FollowingAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class FollowingAxisWalker

template<class string_type, class string_adaptor>
class FollowingSiblingAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;

  
  FollowingSiblingAxisWalker(const RawNodeT context) : BaseT(true)
  {
    if(context != 0)
      BaseT::set(BaseT::findNextSibling(context));
  } // FollowingSiblingAxisWalker

  virtual void advance()
  {
    if(BaseT::get() != 0)
      BaseT::set(BaseT::findNextSibling(BaseT::get()));
  } // advance

  virtual BaseT* clone() const { return new FollowingSiblingAxisWalker(*this); }

private:
  FollowingSiblingAxisWalker(const FollowingSiblingAxisWalker& rhs) : BaseT(rhs) { }
}; // class FollowingSiblingAxisWalker

template<class string_type, class string_adaptor>
class NamespaceAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;
  
  NamespaceAxisWalker(const RawNodeT context) : BaseT(true),
    xmlns_prefix_(string_adaptor::construct_from_utf8("xmlns")),
    index_(0)
  {
    RawNodeT current = context;
    if(current->getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      push_back(context, 
                string_adaptor::construct_from_utf8("xml"), 
                string_adaptor::construct_from_utf8("http://www.w3.org/XML/1998/namespace"));
    while(current->getNodeType() == DOM::Node_base::ELEMENT_NODE)
    {
      for(unsigned int a = 0, ae = current->getAttributes()->getLength(); a != ae; ++a)
      {
        RawNodeT attr = current->getAttributes()->item(a);
        if(attr->getPrefix() == xmlns_prefix_)
          push_back(context, attr->getLocalName(), attr->getNodeValue());
        if(attr->getNodeName() == xmlns_prefix_)
          push_back(context, string_adaptor::empty_string(), attr->getNodeValue());
      } // for ...
      current = current->getParentNode();
    } // while
    list_.push_back(0);
    BaseT::set(list_[index_]);
  } // NamespaceAxisWalker

  virtual ~NamespaceAxisWalker()
  {
    for(int i = 0; list_[i] != 0; ++i)
      list_[i]->releaseRef();
  } // ~NamespaceAxisWalker

  virtual void advance()
  {
    if(index_ != list_.size())
      BaseT::set(list_[++index_]);
  } // advance
  
  virtual BaseT* clone() const { return new NamespaceAxisWalker(*this); }

private:
  void push_back(RawNodeT context, const string_type& prefix, const string_type& uri)
  {
    RawNodeT node = new NamespaceNodeImpl<string_type, string_adaptor>(context, prefix, uri);
    node->addRef();
    list_.push_back(node);
  } // push_back

  NamespaceAxisWalker(const NamespaceAxisWalker& rhs) : BaseT(rhs) { }
  std::vector<RawNodeT> list_;
  const string_type xmlns_prefix_;
  unsigned int index_;
}; // class NamespaceAxisWalker

template<class string_type, class string_adaptor>
class ParentAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;

  
  ParentAxisWalker(const RawNodeT context) : BaseT(false)
  {
    if(context == 0)
      return;

    if(context->getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      BaseT::set(context->getParentNode());
    else
      BaseT::set((dynamic_cast<const DOM::Attr_impl<string_type, string_adaptor>* const>(context))->getOwnerElement());
  } // ParentAxisWalker

  virtual void advance()
  {
    if(BaseT::get() != 0)
      BaseT::set(0);
  } // advance
  virtual BaseT* clone() const { return new ParentAxisWalker(*this); }

private:
  ParentAxisWalker(const ParentAxisWalker& rhs) : BaseT(rhs) { }
}; // class ParentAxisWalker

template<class string_type, class string_adaptor>
class PrecedingAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;
  
  PrecedingAxisWalker(const RawNodeT context) : BaseT(false)
  {
    if(context->getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      firstPreceding(context);
    else
      firstPreceding((dynamic_cast<const DOM::Attr_impl<string_type, string_adaptor>* const>(context))->getOwnerElement());
  } // PrecedingAxisWalker

  virtual void advance()
  {
    BaseT::set(previousInDocument(BaseT::get()));
  } // advance
  virtual BaseT* clone() const { return new PrecedingAxisWalker(*this); }

private:
  void firstPreceding(const RawNodeT context)
  {
    nextAncestor_ = context->getParentNode();
    BaseT::set(previousInDocument(context));
  } // firstPreceding

  RawNodeT previousInDocument(const RawNodeT context)
  {
    RawNodeT next = BaseT::findPreviousSibling(context);
    if(next != 0)
      return getLastDescendant(next);

    next = context->getParentNode();
    if(next != nextAncestor_)
      return next;

    // ancestor collision!!  woorp, woorp!
    if(nextAncestor_ != 0)
    {
      nextAncestor_ = nextAncestor_->getParentNode();
      if(nextAncestor_ != 0)
        return previousInDocument(next);
    } // 

    return 0;
  } // previousInDocument

  RawNodeT getLastDescendant(const RawNodeT context)
  {
    if(context->getFirstChild() == 0)
      return context;

    RawNodeT c = context->getFirstChild();
    while(c->getNextSibling() != 0)
      c = c->getNextSibling();

    return getLastDescendant(c);
  } // getLastDescendant

  PrecedingAxisWalker(const PrecedingAxisWalker& rhs) : BaseT(rhs), nextAncestor_(rhs.nextAncestor_) { }
  RawNodeT nextAncestor_;
}; // PrecedingAxisWalker

template<class string_type, class string_adaptor>
class PrecedingSiblingAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;

  
  PrecedingSiblingAxisWalker(const RawNodeT& context) : BaseT(false)
  {
    if(context != 0)
      BaseT::set(BaseT::findPreviousSibling(context));
  } // PrecedingSiblingAxisWalker

  virtual void advance()
  {
    if(BaseT::get() != 0)
      BaseT::set(BaseT::findPreviousSibling(BaseT::get()));
  } // advance
  virtual BaseT* clone() const { return new PrecedingSiblingAxisWalker(*this); }

private:
  PrecedingSiblingAxisWalker(const PrecedingSiblingAxisWalker& rhs) : BaseT(rhs) { }
}; // class PrecedingSiblingAxisWalker

template<class string_type, class string_adaptor>
class SelfAxisWalker : public AxisWalker<string_type, string_adaptor>
{
  typedef AxisWalker<string_type, string_adaptor> BaseT;
public:
  typedef DOM::Node_impl<string_type, string_adaptor>* RawNodeT;

  
  SelfAxisWalker(const RawNodeT context) : BaseT(true)
  { 
    BaseT::set(context); 
  } // SelfAxisWalker

  virtual void advance() 
  { 
    BaseT::end(); 
  } // advance
  
  virtual BaseT* clone() const { return new SelfAxisWalker(*this); }

private:
  SelfAxisWalker(const SelfAxisWalker& rhs) : BaseT(rhs) { }
}; // class SelfAxisWalker

} // namespace impl

template<class string_type, class string_adaptor>
const typename AxisEnumerator<string_type, string_adaptor>::NamedAxis 
AxisEnumerator<string_type, string_adaptor>::AxisLookupTable[] = 
{ 
  { ANCESTOR,           impl::CreateAxis<impl::AncestorAxisWalker<string_type, string_adaptor>, string_type> },
  { ANCESTOR_OR_SELF,   impl::CreateAxis<impl::AncestorOrSelfAxisWalker<string_type, string_adaptor>, string_type> },
  { ATTRIBUTE,          impl::CreateAxis<impl::AttributeAxisWalker<string_type, string_adaptor>, string_type> },
  { CHILD,              impl::CreateAxis<impl::ChildAxisWalker<string_type, string_adaptor>, string_type> },
  { DESCENDANT,         impl::CreateAxis<impl::DescendantAxisWalker<string_type, string_adaptor>, string_type> },
  { DESCENDANT_OR_SELF, impl::CreateAxis<impl::DescendantOrSelfAxisWalker<string_type, string_adaptor>, string_type> },
  { FOLLOWING,          impl::CreateAxis<impl::FollowingAxisWalker<string_type, string_adaptor>, string_type> },
  { FOLLOWING_SIBLING,  impl::CreateAxis<impl::FollowingSiblingAxisWalker<string_type, string_adaptor>, string_type> },
  { NAMESPACE,          impl::CreateAxis<impl::NamespaceAxisWalker<string_type, string_adaptor>, string_type> },
  { PARENT,             impl::CreateAxis<impl::ParentAxisWalker<string_type, string_adaptor>, string_type> },
  { PRECEDING,          impl::CreateAxis<impl::PrecedingAxisWalker<string_type, string_adaptor>, string_type> },
  { PRECEDING_SIBLING,  impl::CreateAxis<impl::PrecedingSiblingAxisWalker<string_type, string_adaptor>, string_type> },
  { SELF,               impl::CreateAxis<impl::SelfAxisWalker<string_type, string_adaptor>, string_type> },
  { static_cast<Axis>(0), 0 } 
};

} // namespace XPath
} // namespace Arabica

#endif

