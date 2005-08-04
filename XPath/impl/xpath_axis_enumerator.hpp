#ifndef ARABICA_XPATHIC_XPATH_AXIS_ENUMERATOR_H
#define ARABICA_XPATHIC_XPATH_AXIS_ENUMERATOR_H

#include <DOM/Node.h>
#include <DOM/Document.h>
#include <DOM/NamedNodeMap.h>
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

class AxisEnumerator
{
  class AxisWalker;

  template<class axis_walker>
  static AxisWalker* CreateAxis(const DOM::Node<std::string>& context) { return new axis_walker(context); }

  typedef AxisWalker* (*CreateAxisPtr)(const DOM::Node<std::string>& context);

  struct NamedAxis { Axis name; CreateAxisPtr creator; };

  static const NamedAxis AxisLookupTable[];

public:
  AxisEnumerator(const DOM::Node<std::string>& context, Axis axis) :
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
    AxisWalker* newwalker = rhs.walker_->clone();
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
  const DOM::Node<std::string>& operator*() const { return walker_->get(); }
  const DOM::Node<std::string>* const operator->() const { return &(walker_->get()); }
  AxisEnumerator& operator++() { walker_->advance(); return *this; }
  AxisEnumerator operator++(int) { AxisEnumerator copy(*this);  walker_->advance(); return copy; }

private:
  AxisWalker* walker_;  

  AxisEnumerator();

  ////////////////////////////////////////////////////
  class AxisWalker
  {
  public:
    virtual ~AxisWalker() { }
    const DOM::Node<std::string>& get() const { return current_; }
    virtual void advance() = 0;
    bool forward() { return forward_; }
    virtual AxisWalker* clone() const = 0;

  protected:
    AxisWalker(bool forward) : forward_(forward) { }
    AxisWalker(const AxisWalker& rhs) : current_(rhs.current_), forward_(rhs.forward_) { }
    void set(const DOM::Node<std::string>& current) { current_ = current; }
    void end() { current_ = 0; }

  private:
    DOM::Node<std::string> current_;
    bool forward_;

    AxisWalker& operator=(const AxisWalker&);
    bool operator==(const AxisWalker&);
  }; // AxisWalker

  class AncestorAxisWalker : public AxisWalker
  {
  public:
    AncestorAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(false)
    {
      if(context == 0)
        return;

      if(context.getNodeType() != DOM::Node<std::string>::ATTRIBUTE_NODE)
        set(context.getParentNode());
      else
        set((static_cast<DOM::Attr<std::string> >(context)).getOwnerElement());
    } // AncestorAxisWalker

    virtual void advance()
    {
      if(get() != 0)
        set(get().getParentNode());
    } // advance
    virtual AxisWalker* clone() const { return new AncestorAxisWalker(*this); }

  private:
    AncestorAxisWalker(const AncestorAxisWalker& rhs) : AxisWalker(rhs) { }
  }; // class AncestorAxisWalker

  class AncestorOrSelfAxisWalker : public AxisWalker
  {
  public:
    AncestorOrSelfAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(false)
    {
      if(context != 0)
        set(context);
    } // AncestorAxisWalker

    virtual void advance()
    {
      if(get() == 0)
        return;

      if(get().getNodeType() != DOM::Node<std::string>::ATTRIBUTE_NODE)
        set(get().getParentNode());
      else
        set((static_cast<DOM::Attr<std::string> >(get())).getOwnerElement());
   } // advance
    virtual AxisWalker* clone() const { return new AncestorOrSelfAxisWalker(*this); }

  private:
    AncestorOrSelfAxisWalker(const AncestorOrSelfAxisWalker& rhs) : AxisWalker(rhs) { }
  }; // class AncestorOrSelfAxisWalker

  class AttributeAxisWalker : public AxisWalker
  {
  public:
    AttributeAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(true),
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
      if(get() == 0)
        return;
      set_next();
    } // advance

    virtual AxisWalker* clone() const { return new AttributeAxisWalker(*this); } 

  private:
    AttributeAxisWalker(const AttributeAxisWalker& rhs) : 
         AxisWalker(rhs), 
         attrs_(rhs.attrs_), 
         index_(rhs.index_),
         count_(rhs.count_) { }

    DOM::NamedNodeMap<std::string> attrs_;
    unsigned int index_;
    unsigned int count_;

    void set_next() 
    {
      if(index_ == count_)
      {
        end();
        return;
      } // if ...

      DOM::Node<std::string> a;
      do
      {
        a = attrs_.item(index_++);
      } while ((a != 0) && (a.getNamespaceURI() == "http://www.w3.org/2000/xmlns/"));

      set(a);
    } // set_next
  }; // class AttributeAxisEnumerator

  class ChildAxisWalker : public AxisWalker
  {
  public:
    ChildAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(true)
    {
      if(context != 0)
        set(context.getFirstChild());
    } // ChildAxisWalker

    virtual void advance() 
    { 
      if(get() != 0)
        set(get().getNextSibling());
    } // advance
    virtual AxisWalker* clone() const { return new ChildAxisWalker(*this); } 

  private:
    ChildAxisWalker(const ChildAxisWalker& rhs) : AxisWalker(rhs) { }
  }; // class ChildAxisWalker

  class DescendantAxisWalker : public AxisWalker
  {
  public:
    DescendantAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(true),
        origin_(context)
    {
      if((context != 0) && (context.getNodeType() != DOM::Node<std::string>::ATTRIBUTE_NODE))
        set(context.getFirstChild());
    } // DescendantAxisWalker

    virtual void advance()
    {
      set(nextDescendant());
    } // advance

    virtual AxisWalker* clone() const { return new DescendantAxisWalker(*this); }

  private:
    DOM::Node<std::string> nextDescendant()
    {
      DOM::Node<std::string> next = get().getFirstChild();
      if(next == 0)
        next = get().getNextSibling();
      if(next != 0)
        return next;
            
      DOM::Node<std::string> parent = get().getParentNode();
      while(parent != origin_ && next == 0)
      {
        next = parent.getNextSibling();
        parent = parent.getParentNode();
      } // while ...

      return next;
    } // nextDescendant

    DescendantAxisWalker(const DescendantAxisWalker& rhs) : AxisWalker(rhs), origin_(rhs.origin_) { }
    const DOM::Node<std::string> origin_;
  }; // class DescendantAxisWalker

  class DescendantOrSelfAxisWalker : public AxisWalker
  {
  public:
    DescendantOrSelfAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(true),
        origin_(context)
    {
      if(context != 0)
        set(context);
    } // DescendantAxisWalker

    virtual void advance()
    {
      set(walkDown(get(), origin_));
    } // advance

    virtual AxisWalker* clone() const { return new DescendantOrSelfAxisWalker(*this); }

  private:
    DescendantOrSelfAxisWalker(const DescendantOrSelfAxisWalker& rhs) : AxisWalker(rhs), origin_(rhs.origin_) { }
    const DOM::Node<std::string> origin_;
  }; // class DescendantOrSelfAxisWalker

  class FollowingAxisWalker : public AxisWalker
  {
  public:
    FollowingAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(true)
    {
      set(firstFollowing(context));
    } // FollowingAxisWalker

    virtual void advance()
    {
      set(walkDown(get(), get().getOwnerDocument()));
    } // advance
    virtual AxisWalker* clone() const { return new FollowingAxisWalker(*this); }

  private:
    DOM::Node<std::string> firstFollowing(const DOM::Node<std::string>& context) const
    {
      if(context.getNodeType() == DOM::Node<std::string>::ATTRIBUTE_NODE)
        return 0;

      DOM::Node<std::string> next = context.getNextSibling();
      if(next != 0)
        return next;
            
      DOM::Node<std::string> parent = context.getParentNode();
      while(parent != context.getOwnerDocument() && next == 0)
      {
        next = parent.getNextSibling();
        parent = parent.getParentNode();
      } // while ...

      return next;
    } // firstFollowing

    FollowingAxisWalker(const FollowingAxisWalker& rhs) : AxisWalker(rhs) { }
  }; // class FollowingAxisWalker

  class FollowingSiblingAxisWalker : public AxisWalker
  {
  public:
    FollowingSiblingAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(true)
    {
      if(context != 0)
        set(context.getNextSibling());
    } // FollowingSiblingAxisWalker

    virtual void advance()
    {
      if(get() != 0)
        set(get().getNextSibling());
    } // advance
    virtual AxisWalker* clone() const { return new FollowingSiblingAxisWalker(*this); }

  private:
    FollowingSiblingAxisWalker(const FollowingSiblingAxisWalker& rhs) : AxisWalker(rhs) { }
  }; // class FollowingSiblingAxisWalker

  class NamespaceAxisWalker : public AxisWalker
  {
  public:
    NamespaceAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(true),
      index_(0)
    {
      DOM::Node<std::string> current = context;
      while(current.getNodeType() == DOM::Node<std::string>::ELEMENT_NODE)
      {
        for(unsigned int a = 0, ae = current.getAttributes().getLength(); a != ae; ++a)
        {
          DOM::Node<std::string> attr = current.getAttributes().item(a);
          if(attr.getPrefix() == "xmlns")
            list_.push_back(DOM::Node<std::string>(
                       new NamespaceNodeImpl<std::string>(attr.getLocalName(), 
                                                          attr.getNodeValue())
                                                   )
                            );
        } // for ...
        current = current.getParentNode();
      } // while
      list_.push_back(DOM::Node<std::string>(0));
      set(list_[index_]);
    } // NamespaceAxisWalker

    virtual void advance()
    {
      if(index_ != list_.size())
        set(list_[++index_]);
    } // advance
    
    virtual AxisWalker* clone() const { return new NamespaceAxisWalker(*this); }

  private:
    NamespaceAxisWalker(const NamespaceAxisWalker& rhs) : AxisWalker(rhs) { }
    std::vector<DOM::Node<std::string> > list_;
    unsigned int index_;
  }; // class NamespaceAxisWalker

  class ParentAxisWalker : public AxisWalker
  {
  public:
    ParentAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(false)
    {
      if(context == 0)
        return;

      if(context.getNodeType() != DOM::Node<std::string>::ATTRIBUTE_NODE)
        set(context.getParentNode());
      else
        set((static_cast<DOM::Attr<std::string> >(context)).getOwnerElement());
    } // ParentAxisWalker

    virtual void advance()
    {
      if(get() != 0)
        set(0);
    } // advance
    virtual AxisWalker* clone() const { return new ParentAxisWalker(*this); }

  private:
    ParentAxisWalker(const ParentAxisWalker& rhs) : AxisWalker(rhs) { }
  }; // class ParentAxisWalker

  class PrecedingAxisWalker : public AxisWalker
  {
  public:
    PrecedingAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(false)
    {
      nextAncestor_ = context.getParentNode();
      set(previousInDocument(context));
    } // PrecedingAxisWalker

    virtual void advance()
    {
      set(previousInDocument(get()));
    } // advance
    virtual AxisWalker* clone() const { return new PrecedingAxisWalker(*this); }

  private:
    DOM::Node<std::string> previousInDocument(const DOM::Node<std::string>& context)
    {
      DOM::Node<std::string> next = context.getPreviousSibling();
      if(next != 0)
        return getLastDescendant(next);

      next = context.getParentNode();
      if(next != nextAncestor_)
        return next;

      // ancestor collision!!  woorp, woorp!
      nextAncestor_ = nextAncestor_.getParentNode();
      if(nextAncestor_ != 0)
        return previousInDocument(next);

      return 0;
    } // previousInDocument

    DOM::Node<std::string> getLastDescendant(const DOM::Node<std::string>& context)
    {
      if(context.getFirstChild() == 0)
        return context;

      DOM::Node<std::string> c = context.getFirstChild();
      while(c.getNextSibling() != 0)
        c = c.getNextSibling();

      return getLastDescendant(c);
    } // getLastDescendant

    PrecedingAxisWalker(const PrecedingAxisWalker& rhs) : AxisWalker(rhs), nextAncestor_(rhs.nextAncestor_) { }
    DOM::Node<std::string> nextAncestor_;
  }; // PrecedingAxisWalker

  class PrecedingSiblingAxisWalker : public AxisWalker
  {
  public:
    PrecedingSiblingAxisWalker(const DOM::Node<std::string>& context) : AxisWalker(false)
    {
      if(context != 0)
        set(context.getPreviousSibling());
    } // PrecedingSiblingAxisWalker

    virtual void advance()
    {
      if(get() != 0)
        set(get().getPreviousSibling());
    } // advance
    virtual AxisWalker* clone() const { return new PrecedingSiblingAxisWalker(*this); }

  private:
    PrecedingSiblingAxisWalker(const PrecedingSiblingAxisWalker& rhs) : AxisWalker(rhs) { }
  }; // class PrecedingSiblingAxisWalker

  class SelfAxisWalker : public AxisWalker
  {
  public:
    SelfAxisWalker(const DOM::Node<std::string>& context)  : AxisWalker(true)
    { 
      set(context); 
    } // SelfAxisWalker

    virtual void advance() { end(); }
    virtual AxisWalker* clone() const { return new SelfAxisWalker(*this); }

  private:
    SelfAxisWalker(const SelfAxisWalker& rhs) : AxisWalker(rhs) { }
  }; // class SelfAxisWalker

  static DOM::Node<std::string> walkDown(const DOM::Node<std::string>& context, const DOM::Node<std::string>& origin)
  {
    if(context.getNodeType() == DOM::Node<std::string>::ATTRIBUTE_NODE)
      return 0;

    DOM::Node<std::string> next = context.getFirstChild();
    if((next == 0) && (context == origin)) // node with no children
      return 0;

    if(next != 0)
      return next;

    next = context.getNextSibling();
    if(next != 0)
      return next;
            
    DOM::Node<std::string> parent = context.getParentNode();
    while(parent != origin && next == 0)
    {
      next = parent.getNextSibling();
      parent = parent.getParentNode();
    } // while ...

    return next;
  } // walkDown
}; // class AxisEnumerator  

} // namespace XPath
} // namespace Arabica

#endif

