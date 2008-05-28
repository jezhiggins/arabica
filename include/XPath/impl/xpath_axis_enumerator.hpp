#ifndef ARABICA_XPATHIC_XPATH_AXIS_ENUMERATOR_H
#define ARABICA_XPATHIC_XPATH_AXIS_ENUMERATOR_H

#include <DOM/Node.hpp>
#include <DOM/Document.hpp>
#include <DOM/NamedNodeMap.hpp>
#include "xpath_namespace_node.hpp"

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
AxisWalker<string_type, string_adaptor>* CreateAxis(const DOM::Node<string_type, string_adaptor>& context) { return new axis_walker(context); }
} // namespace impl

template<class string_type, class string_adaptor>
class AxisEnumerator
{
  typedef impl::AxisWalker<string_type, string_adaptor>* (*CreateAxisPtr)(const DOM::Node<string_type, string_adaptor>& context);

  struct NamedAxis { Axis name; CreateAxisPtr creator; };
  static const NamedAxis AxisLookupTable[];

public:
  AxisEnumerator(const DOM::Node<string_type, string_adaptor>& context, Axis axis) :
      walker_(0)
  { 
    for(const NamedAxis* ax = AxisLookupTable; ax->creator != 0; ++ax)
      if(axis == ax->name)
        walker_ = ax->creator(context);

    if(!walker_)
      throw std::runtime_error("Unknown Axis specifier");
  } // AxisEnumerator

  AxisEnumerator(const AxisEnumerator& rhs) :
    walker_(rhs.walker_->clone())
  {
  } // AxisEnumerator

  AxisEnumerator& operator=(const AxisEnumerator& rhs)
  {
    impl::AxisWalker<string_type, string_adaptor>* newwalker = rhs.walker_->clone();
    delete walker_;
    walker_ = newwalker;
    return *this;
  } // operator=

  ~AxisEnumerator() 
  {
    delete walker_;
  } // ~AxisEnumerator

  bool forward() const { return walker_->forward(); }
  bool reverse() const { return !walker_->forward(); }
  const DOM::Node<string_type, string_adaptor>& operator*() const { return walker_->get(); }
  const DOM::Node<string_type, string_adaptor>* const operator->() const { return &(walker_->get()); }
  AxisEnumerator& operator++() { walker_->advance(); return *this; }
  AxisEnumerator operator++(int) { AxisEnumerator copy(*this);  walker_->advance(); return copy; }

private:
  impl::AxisWalker<string_type, string_adaptor>* walker_;  

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
  const DOM::Node<string_type, string_adaptor>& get() const { return current_; }
  virtual void advance() = 0;
  bool forward() { return forward_; }
  virtual AxisWalker<string_type, string_adaptor>* clone() const = 0;

protected:
  AxisWalker(bool forward) : forward_(forward) { }
  AxisWalker(const AxisWalker& rhs) : current_(rhs.current_), forward_(rhs.forward_) { }
  void set(const DOM::Node<string_type, string_adaptor>& current) { current_ = current; }
  void end() { current_ = 0; }

  static DOM::Node<string_type, string_adaptor> walkDown(const DOM::Node<string_type, string_adaptor>& context, const DOM::Node<string_type, string_adaptor>& origin)
  {
    if(context.getNodeType() == DOM::Node_base::ATTRIBUTE_NODE)
      return 0;

    DOM::Node<string_type, string_adaptor> next = context.getFirstChild();
    if((next == 0) && (context == origin)) // node with no children
      return 0;

    if(next != 0)
      return next;

    next = context.getNextSibling();
    if(next != 0)
      return next;
            
    DOM::Node<string_type, string_adaptor> parent = context.getParentNode();
    while(parent != origin && next == 0)
    {
      next = parent.getNextSibling();
      parent = parent.getParentNode();
    } // while ...

    return next;
  } // walkDown

private:
  DOM::Node<string_type, string_adaptor> current_;
  bool forward_;

  AxisWalker& operator=(const AxisWalker&);
  bool operator==(const AxisWalker&);
}; // AxisWalker

template<class string_type, class string_adaptor>
class AncestorAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  AncestorAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(false)
  {
    if(context == 0)
      return;

    if(context.getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      AxisWalker<string_type, string_adaptor>::set(context.getParentNode());
    else
      AxisWalker<string_type, string_adaptor>::set((static_cast<DOM::Attr<string_type, string_adaptor> >(context)).getOwnerElement());
  } // AncestorAxisWalker

  virtual void advance()
  {
    if(AxisWalker<string_type, string_adaptor>::get() != 0)
      AxisWalker<string_type, string_adaptor>::set(AxisWalker<string_type, string_adaptor>::get().getParentNode());
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new AncestorAxisWalker(*this); }

private:
  AncestorAxisWalker(const AncestorAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class AncestorAxisWalker

template<class string_type, class string_adaptor>
class AncestorOrSelfAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  AncestorOrSelfAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(false)
  {
    if(context != 0)
      AxisWalker<string_type, string_adaptor>::set(context);
  } // AncestorAxisWalker

  virtual void advance()
  {
    if(AxisWalker<string_type, string_adaptor>::get() == 0)
      return;

    if(AxisWalker<string_type, string_adaptor>::get().getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      AxisWalker<string_type, string_adaptor>::set(AxisWalker<string_type, string_adaptor>::get().getParentNode());
    else
      AxisWalker<string_type, string_adaptor>::set((static_cast<DOM::Attr<string_type, string_adaptor> >(AxisWalker<string_type, string_adaptor>::get())).getOwnerElement());
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new AncestorOrSelfAxisWalker(*this); }

private:
  AncestorOrSelfAxisWalker(const AncestorOrSelfAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class AncestorOrSelfAxisWalker

template<class string_type, class string_adaptor>
class AttributeAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  AttributeAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(true),
      index_(0), count_(0)
  { 
    if((context != 0) && (context.hasAttributes()))
    {
      attrs_ = context.getAttributes();
      count_ = attrs_.getLength();
      set_next();
    } // if ...
  } // AttributeAxisWalker

  virtual void advance()
  {
    if(AxisWalker<string_type, string_adaptor>::get() == 0)
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

  DOM::NamedNodeMap<string_type, string_adaptor> attrs_;
  unsigned int index_;
  unsigned int count_;

  void set_next() 
  {
    if(index_ == count_)
    {
      AxisWalker<string_type, string_adaptor>::end();
      return;
    } // if ...

    DOM::Node<string_type, string_adaptor> a;
    do
    {
      a = attrs_.item(index_++);
    } while ((a != 0) && (a.getNamespaceURI() == string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/")));

    AxisWalker<string_type, string_adaptor>::set(a);
  } // set_next
}; // class AttributeAxisEnumerator

template<class string_type, class string_adaptor>
class ChildAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  ChildAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(true)
  {
    if(context != 0)
      AxisWalker<string_type, string_adaptor>::set(context.getFirstChild());
  } // ChildAxisWalker

  virtual void advance() 
  { 
    if(AxisWalker<string_type, string_adaptor>::get() != 0)
      AxisWalker<string_type, string_adaptor>::set(AxisWalker<string_type, string_adaptor>::get().getNextSibling());
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new ChildAxisWalker(*this); } 

private:
  ChildAxisWalker(const ChildAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class ChildAxisWalker

template<class string_type, class string_adaptor>
class DescendantAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  DescendantAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(true),
      origin_(context)
  {
    if((context != 0) && (context.getNodeType() != DOM::Node_base::ATTRIBUTE_NODE))
      AxisWalker<string_type, string_adaptor>::set(context.getFirstChild());
  } // DescendantAxisWalker

  virtual void advance()
  {
    AxisWalker<string_type, string_adaptor>::set(nextDescendant());
  } // advance

  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new DescendantAxisWalker(*this); }

private:
  DOM::Node<string_type, string_adaptor> nextDescendant()
  {
    DOM::Node<string_type, string_adaptor> next = AxisWalker<string_type, string_adaptor>::get().getFirstChild();
    if(next == 0)
      next = AxisWalker<string_type, string_adaptor>::get().getNextSibling();
    if(next != 0)
      return next;
          
    DOM::Node<string_type, string_adaptor> parent = AxisWalker<string_type, string_adaptor>::get().getParentNode();
    while(parent != origin_ && next == 0)
    {
      next = parent.getNextSibling();
      parent = parent.getParentNode();
    } // while ...

    return next;
  } // nextDescendant

  DescendantAxisWalker(const DescendantAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs), origin_(rhs.origin_) { }
  const DOM::Node<string_type, string_adaptor> origin_;
}; // class DescendantAxisWalker

template<class string_type, class string_adaptor>
class DescendantOrSelfAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  DescendantOrSelfAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(true),
      origin_(context)
  {
    if(context != 0)
      AxisWalker<string_type, string_adaptor>::set(context);
  } // DescendantAxisWalker

  virtual void advance()
  {
    AxisWalker<string_type, string_adaptor>::set(AxisWalker<string_type, string_adaptor>::walkDown(AxisWalker<string_type, string_adaptor>::get(), origin_));
  } // advance

  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new DescendantOrSelfAxisWalker(*this); }

private:
  DescendantOrSelfAxisWalker(const DescendantOrSelfAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs), origin_(rhs.origin_) { }
  const DOM::Node<string_type, string_adaptor> origin_;
}; // class DescendantOrSelfAxisWalker

template<class string_type, class string_adaptor>
class FollowingAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  FollowingAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(true)
  {
    AxisWalker<string_type, string_adaptor>::set(firstFollowing(context));
  } // FollowingAxisWalker

  virtual void advance()
  {
    AxisWalker<string_type, string_adaptor>::set(AxisWalker<string_type, string_adaptor>::walkDown(AxisWalker<string_type, string_adaptor>::get(), AxisWalker<string_type, string_adaptor>::get().getOwnerDocument()));
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new FollowingAxisWalker(*this); }

private:
  DOM::Node<string_type, string_adaptor> firstFollowing(const DOM::Node<string_type, string_adaptor>& context) const
  {
    if(context.getNodeType() == DOM::Node_base::ATTRIBUTE_NODE)
    {
      DOM::Node<string_type, string_adaptor> owner = static_cast<DOM::Attr<string_type, string_adaptor> >(context).getOwnerElement();
      if(owner.hasChildNodes())
        return owner.getFirstChild();
      return firstFollowing(owner);
    } // if attribute

    DOM::Node<string_type, string_adaptor> next = context.getNextSibling();

    if(next != 0)
      return next;
          
    DOM::Node<string_type, string_adaptor> parent = context.getParentNode();
    while(parent != context.getOwnerDocument() && next == 0)
    {
      next = parent.getNextSibling();
      parent = parent.getParentNode();
    } // while ...

    return next;
  } // firstFollowing

  FollowingAxisWalker(const FollowingAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class FollowingAxisWalker

template<class string_type, class string_adaptor>
class FollowingSiblingAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  FollowingSiblingAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(true)
  {
    if(context != 0)
      AxisWalker<string_type, string_adaptor>::set(context.getNextSibling());
  } // FollowingSiblingAxisWalker

  virtual void advance()
  {
    if(AxisWalker<string_type, string_adaptor>::get() != 0)
      AxisWalker<string_type, string_adaptor>::set(AxisWalker<string_type, string_adaptor>::get().getNextSibling());
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new FollowingSiblingAxisWalker(*this); }

private:
  FollowingSiblingAxisWalker(const FollowingSiblingAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class FollowingSiblingAxisWalker

template<class string_type, class string_adaptor>
class NamespaceAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  NamespaceAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(true),
    xmlns_prefix_(string_adaptor::construct_from_utf8("xmlns")),
    index_(0)
  {
    DOM::Node<string_type, string_adaptor> current = context;
    if(current.getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      list_.push_back(DOM::Node<string_type, string_adaptor>(
             new NamespaceNodeImpl<string_type, string_adaptor>(context,
                                                                string_adaptor::construct_from_utf8("xml"), 
                                                                string_adaptor::construct_from_utf8("http://www.w3.org/XML/1998/namespace"))
                                            )
                     );
    while(current.getNodeType() == DOM::Node_base::ELEMENT_NODE)
    {
      for(unsigned int a = 0, ae = current.getAttributes().getLength(); a != ae; ++a)
      {
        DOM::Node<string_type, string_adaptor> attr = current.getAttributes().item(a);
        if(attr.getPrefix() == xmlns_prefix_)
          list_.push_back(DOM::Node<string_type, string_adaptor>(
                   new NamespaceNodeImpl<string_type, string_adaptor>(context,
                                                                      attr.getLocalName(), 
                                                                      attr.getNodeValue())
                                                  )
                          );
        if(attr.getNodeName() == xmlns_prefix_)
          list_.push_back(DOM::Node<string_type, string_adaptor>(
                   new NamespaceNodeImpl<string_type, string_adaptor>(context,
                                                                      "", 
                                                                      attr.getNodeValue())
                                                  )
                          );
      } // for ...
      current = current.getParentNode();
    } // while
    list_.push_back(DOM::Node<string_type, string_adaptor>(0));
    AxisWalker<string_type, string_adaptor>::set(list_[index_]);
  } // NamespaceAxisWalker

  virtual void advance()
  {
    if(index_ != list_.size())
      AxisWalker<string_type, string_adaptor>::set(list_[++index_]);
  } // advance
  
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new NamespaceAxisWalker(*this); }

private:
  NamespaceAxisWalker(const NamespaceAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
  std::vector<DOM::Node<string_type, string_adaptor> > list_;
  const string_type xmlns_prefix_;
  unsigned int index_;
}; // class NamespaceAxisWalker

template<class string_type, class string_adaptor>
class ParentAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  ParentAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(false)
  {
    if(context == 0)
      return;

    if(context.getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      AxisWalker<string_type, string_adaptor>::set(context.getParentNode());
    else
      AxisWalker<string_type, string_adaptor>::set((static_cast<DOM::Attr<string_type, string_adaptor> >(context)).getOwnerElement());
  } // ParentAxisWalker

  virtual void advance()
  {
    if(AxisWalker<string_type, string_adaptor>::get() != 0)
      AxisWalker<string_type, string_adaptor>::set(0);
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new ParentAxisWalker(*this); }

private:
  ParentAxisWalker(const ParentAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class ParentAxisWalker

template<class string_type, class string_adaptor>
class PrecedingAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  PrecedingAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(false)
  {
    if(context.getNodeType() != DOM::Node_base::ATTRIBUTE_NODE)
      firstPreceding(context);
    else
      firstPreceding((static_cast<DOM::Attr<string_type, string_adaptor> >(context)).getOwnerElement());
  } // PrecedingAxisWalker

  virtual void advance()
  {
    AxisWalker<string_type, string_adaptor>::set(previousInDocument(AxisWalker<string_type, string_adaptor>::get()));
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new PrecedingAxisWalker(*this); }

private:
  void firstPreceding(const DOM::Node<string_type, string_adaptor>& context)
  {
    nextAncestor_ = context.getParentNode();
    AxisWalker<string_type, string_adaptor>::set(previousInDocument(context));
  } // firstPreceding

  DOM::Node<string_type, string_adaptor> previousInDocument(const DOM::Node<string_type, string_adaptor>& context)
  {
    DOM::Node<string_type, string_adaptor> next = context.getPreviousSibling();
    if(next != 0)
      return getLastDescendant(next);

    next = context.getParentNode();
    if(next != nextAncestor_)
      return next;

    // ancestor collision!!  woorp, woorp!
    if(nextAncestor_ != 0)
    {
      nextAncestor_ = nextAncestor_.getParentNode();
      if(nextAncestor_ != 0)
        return previousInDocument(next);
    } // 

    return 0;
  } // previousInDocument

  DOM::Node<string_type, string_adaptor> getLastDescendant(const DOM::Node<string_type, string_adaptor>& context)
  {
    if(context.getFirstChild() == 0)
      return context;

    DOM::Node<string_type, string_adaptor> c = context.getFirstChild();
    while(c.getNextSibling() != 0)
      c = c.getNextSibling();

    return getLastDescendant(c);
  } // getLastDescendant

  PrecedingAxisWalker(const PrecedingAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs), nextAncestor_(rhs.nextAncestor_) { }
  DOM::Node<string_type, string_adaptor> nextAncestor_;
}; // PrecedingAxisWalker

template<class string_type, class string_adaptor>
class PrecedingSiblingAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  PrecedingSiblingAxisWalker(const DOM::Node<string_type, string_adaptor>& context) : AxisWalker<string_type, string_adaptor>(false)
  {
    if(context != 0)
      AxisWalker<string_type, string_adaptor>::set(context.getPreviousSibling());
  } // PrecedingSiblingAxisWalker

  virtual void advance()
  {
    if(AxisWalker<string_type, string_adaptor>::get() != 0)
      AxisWalker<string_type, string_adaptor>::set(AxisWalker<string_type, string_adaptor>::get().getPreviousSibling());
  } // advance
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new PrecedingSiblingAxisWalker(*this); }

private:
  PrecedingSiblingAxisWalker(const PrecedingSiblingAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
}; // class PrecedingSiblingAxisWalker

template<class string_type, class string_adaptor>
class SelfAxisWalker : public AxisWalker<string_type, string_adaptor>
{
public:
  SelfAxisWalker(const DOM::Node<string_type, string_adaptor>& context)  : AxisWalker<string_type, string_adaptor>(true)
  { 
    AxisWalker<string_type, string_adaptor>::set(context); 
  } // SelfAxisWalker

  virtual void advance() { AxisWalker<string_type, string_adaptor>::end(); }
  virtual AxisWalker<string_type, string_adaptor>* clone() const { return new SelfAxisWalker(*this); }

private:
  SelfAxisWalker(const SelfAxisWalker& rhs) : AxisWalker<string_type, string_adaptor>(rhs) { }
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

