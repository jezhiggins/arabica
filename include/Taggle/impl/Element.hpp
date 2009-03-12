#ifndef ARABICA_SAX_TAGSOUP_ELEMENT_HPP
#define ARABICA_SAX_TAGSOUP_ELEMENT_HPP

#include <string>
#include <SAX/helpers/AttributesImpl.hpp>
#include "ElementType.hpp"

namespace Arabica
{

namespace SAX
{

/**
 The internal representation of an actual element (not an element type).
 An Element has an element type, attributes, and a successor Element
 for use in constructing stacks and queues of Elements.
 @see ElementType
 @see AttributesImpl
   
 Based on code from John Cowan's super TagSoup package
*/

class Element_impl;

class Element
{
public:
  static const Element Null;

  Element(ElementType& type, bool defaultAttributes);
  Element(const Element& rhs);
  ~Element();

  Element& operator=(const Element& rhs);
  bool operator==(const Element& rhs) const;
  bool operator!=(const Element& rhs) const;

  /** 
     Return the element type.
     @return The element type.
  */
  const ElementType& type() const;

  /**
     Return the attributes as an AttributesImpl object.
     @return The attributes
     @see AttributesImpl
  */
  const AttributesImpl<std::string>& atts() const;

  /**
     return the next element in the element stack or queue
     @return the next element
  */
  Element next() const;

  /**
     Change the next element in an element stack or queue.
     @param next The new next element
  */
  void setNext(const Element& next);

  /**
     Return the name of the element's type.
     Convenience method.
     @return the element type name
  */
  std::string name() const;


  /**
     Return the namespace name of the element's type.
     Convenience method.
     @return The element type namespace name
  */
  std::string namespaceName() const;

  /**
     Return the local name of the element's type.
     Convenience method.
     @return The element type local name
  */
  std::string localName() const;

  /**
     Return the content model vector of the element's type.
     Convenience method.
     @return The content model vector
  */
  int model() const; 


  /**
     Return the member-of vector of the element's type.
     Convenience method.
     @return The member-of vector
  */
  int memberOf() const; 

  /**
     Return the flags vector of the element's type.
     Convenience method.
     @return The flags vector
  */
  int flags() const;

  /**
     Return the parent element type of the element's type
     Convenience method
     @return the parent element type
  */
  ElementType& parent() const;

  /**
     Return true if the type of this element can contain the type of
     another element.
     Convenience method.
     @param other The other element
  */
  bool canContain(const Element& other) const;

  /**
     Set an attribute and its value into this element.
     @param name The attribute name (Qname)
     @param type The attribute type
     @param value The attribute value
  */
  void setAttribute(const std::string& name, const std::string& type, const std::string& value);

  /**
     Make this element anonymous.
     Remove any <tt>id</tt> or <tt>name</tt> attribute present
     in the element's attributes.
  */
  void anonymize();

  /**
     Clean the attributes of this element.
     Attributes with null name (the name was ill-formed)
     or null value (the attribute was present in the element type but
     not in this actual element) are removed.
  */
  void clean();

  /**
     Force this element to preclosed status, meaning that an end-tag has
     been seen but the element cannot yet be closed for structural reasons.
  */
  void preclose();

  /**
     Return true if this element has been preclosed.
  */
  bool isPreclosed() const;

private:
  Element() : impl_(0) { }
  bool is_null() const { return impl_ == 0; }

  Element_impl* impl_;

  friend class Element_impl;
}; // class Element

class Element_impl 
{
private:
  ElementType* type_;		// type of element
  AttributesImpl<std::string> atts_;		// attributes of element
  Element next_;		// successor of element
  bool preclosed_;		// this element has been preclosed
  int refCount_;

public:
  /**
     Return an Element from a specified ElementType.
     @param type The element type of the newly constructed element
     @param defaultAttributes True if default attributes are wanted
  */
  Element_impl(ElementType& type, bool defaultAttributes) :
    type_(&type),
    atts_(),
    next_(),
    preclosed_(false),
    refCount_(1)
  {
    if (defaultAttributes) 
      atts_ = type.atts();
  } // Element_impl

  const ElementType& type() const { return *type_; }
  const AttributesImpl<std::string>& atts() const { return atts_; }

  Element next() const 
  { 
    if(next_.is_null())
      return Element::Null;
    return next_; 
  } // next()
  void setNext(const Element& next) { next_ = next; }

  std::string name() const { return type_->name(); }
  std::string namespaceName() const { return type_->namespaceName(); }
  std::string localName() const { return type_->localName(); }
  int model() const { return type_->model(); }
  int memberOf() const { return type_->memberOf(); }
  int flags() const { return type_->flags(); }
  ElementType& parent() const { return type_->parent(); }
  bool canContain(const Element_impl* const other) const { return type_->canContain(*(other->type_)); }

  void setAttribute(const std::string& name, const std::string& type, const std::string& value) 
  {
    type_->setAttribute(atts_, name, type, value);
  } // setAttribute
  
  void anonymize() 
  {
    for (int i = atts_.getLength() - 1; i >= 0; i--) 
    {
      if((atts_.getType(i) == "ID") || (atts_.getQName(i) == "name"))
	atts_.removeAttribute(i);
    } // for ...
  } // anonymize

  void clean() 
  {
    for (int i = atts_.getLength() - 1; i >= 0; i--) 
    {
      const std::string& name = atts_.getLocalName(i);
      if (atts_.getValue(i) == "" || name == "" || name.length() == 0) 
      {
	atts_.removeAttribute(i);
	continue;
      } // if ...
    } // for ...
  } // clean

  void preclose() 
  {
    preclosed_ = true;
  } // preclose

  bool isPreclosed() const
  {
    return preclosed_;
  } // isPreclosed

  void add_ref() 
  { 
    ++refCount_; 
  } // add_ref

  void remove_ref() 
  {
    --refCount_;
    if(refCount_ == 0)
      delete this;
  } // remove_ref

private:
  Element_impl();

  ~Element_impl()
  {
  } // ~Element_impl


  Element_impl(const Element_impl& rhs);
  Element_impl& operator=(const Element_impl& rhs);
  bool operator==(const Element_impl& rhs) const;
  bool operator!=(const Element_impl& rhs) const;
}; // class Element_impl

const Element Element::Null = Element(ElementType::Null, false);

//////////////////////////////////////////////
Element::Element(const Element& rhs) :
  impl_(rhs.impl_)
{
  impl_->add_ref();
} // Element

Element::Element(ElementType& type, bool defaultAttributes) :
    impl_(new Element_impl(type, defaultAttributes))
{
} // Element

Element::~Element() 
{
  if(impl_)
    impl_->remove_ref();
} // ~Element

Element& Element::operator=(const Element& rhs)
{
  if(impl_ == rhs.impl_)
    return *this;

  if(impl_)
   impl_->remove_ref();
  impl_ = rhs.impl_;
  if(impl_)
    impl_->add_ref();
  return *this;
} // operator=

bool Element::operator==(const Element& rhs) const
{
  return impl_ == rhs.impl_;
} // operator==

bool Element::operator!=(const Element& rhs) const
{
  return !(operator==(rhs));
} // operator!=

const ElementType& Element::type() const
{
  return impl_->type();
} // type

const AttributesImpl<std::string>& Element::atts() const
{
  return impl_->atts();
} // atts

Element Element::next() const
{
  return impl_->next();
} // next

void Element::setNext(const Element& next)
{
  impl_->setNext(next);
} // setNext

std::string Element::name() const { return impl_->name(); }
std::string Element::namespaceName() const { return impl_->namespaceName(); }
std::string Element::localName() const { return impl_->localName(); }

int Element::model() const { return impl_->model(); }
int Element::memberOf() const { return impl_->memberOf(); }
int Element::flags() const { return impl_->flags(); }

ElementType& Element::parent() const { return impl_->parent(); }
bool Element::canContain(const Element& other) const { return impl_->canContain(other.impl_); }

void Element::setAttribute(const std::string& name, const std::string& type, const std::string& value) 
{
  impl_->setAttribute(name, type, value);
} // setAttribute

void Element::anonymize() { impl_->anonymize(); }
void Element::clean() { impl_->clean(); }
void Element::preclose() { impl_->preclose(); }
bool Element::isPreclosed() const { return impl_->isPreclosed(); }

} // namespace SAX

} // namespace Arabica

#endif
