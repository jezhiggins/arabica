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
class Element 
{
private:
  ElementType* type_;		// type of element
  AttributesImpl<std::string> atts_;		// attributes of element
  const Element* next_;		// successor of element
  bool preclosed_;		// this element has been preclosed

public:
  static const Element Null;

  Element() :
    type_(&ElementType::Null),
    atts_(),
    next_(0),
    preclosed_(false)
  {
  } // Element

  Element(const Element& rhs):
    type_(rhs.type_),
    atts_(rhs.atts_),
    next_(0),
    preclosed_(rhs.preclosed_)
  {
    if(rhs.next_)
      next_ = new Element(*rhs.next_);
  } // Element

  /**
     Return an Element from a specified ElementType.
     @param type The element type of the newly constructed element
     @param defaultAttributes True if default attributes are wanted
  */
  Element(ElementType& type, bool defaultAttributes) :
    type_(&type),
    atts_(),
    next_(0),
    preclosed_(false)
  {
    if (defaultAttributes) 
      atts_ = type.atts();
  } // Element

  ~Element()
  {
    if(next_ && (*next_ != Null))
      delete next_;
  } // ~Element

  Element& operator=(const Element& rhs)
  {
    type_ = rhs.type_;
    atts_ = rhs.atts_;
    preclosed_ = rhs.preclosed_;
    if(next_ && (*next_ != Null))
      delete next_;
    if(rhs.next_)
      next_ = new Element(*rhs.next_);
    else
      next_ = 0;
    return *this;
  } // operator=

  bool operator==(const Element& rhs) const
  {
    bool ok = (type_ == rhs.type_) && 
              (atts_ == rhs.atts_) &&
              (preclosed_ == rhs.preclosed_);
    if(!ok)
      return false;

    if(!next_ && !rhs.next_)
      return true;

    if((!next_ && rhs.next_) ||
       (next_ && !rhs.next_))
     return false;

    return (*next_ == *rhs.next_);
  } // operator==

  bool operator!=(const Element& rhs) const
  {
    return !(*this == rhs);
  } // operator!=

  /**
     Return the element type.
     @return The element type.
  */
  const ElementType& type() const 
  { 
    return *type_; 
  } // type

  /**
   Return the attributes as an AttributesImpl object.
   Returning an AttributesImpl makes the attributes mutable.
   @return The attributes
   @see AttributesImpl
  */
  const AttributesImpl<std::string>& atts() const 
  { 
    return atts_; 
  } // atts

  /**
     Return the next element in an element stack or queue.
     @return The next element
  */
  Element next() const 
  { 
    if(!next_)
      return Null;
    return *next_; 
  } // next
  
  /**
     Change the next element in an element stack or queue.
     @param next The new next element
  */
  void setNext(const Element& next) 
  { 
    if(next_ && (*next_ != Null))
      delete next_;
    next_ = new Element(next);
  } // setNext

  /**
     Return the name of the element's type.
     Convenience method.
     @return The element type name
  */
  std::string name() const 
  { 
    return type_->name(); 
  } // name

  /**
     Return the namespace name of the element's type.
     Convenience method.
     @return The element type namespace name
  */
  std::string namespaceName() const 
  { 
    return type_->namespaceName(); 
  } // namespaceName

  /**
     Return the local name of the element's type.
     Convenience method.
     @return The element type local name
  */
  std::string localName() const 
  { 
    return type_->localName(); 
  } // localName

  /**
     Return the content model vector of the element's type.
     Convenience method.
     @return The content model vector
  */
  int model() const 
  {
    return type_->model(); 
  } // model

  /**
     Return the member-of vector of the element's type.
     Convenience method.
     @return The member-of vector
  */
  int memberOf() const 
  { 
    return type_->memberOf(); 
  } // memberOf

  /**
     Return the flags vector of the element's type.
     Convenience method.
     @return The flags vector
  */
  int flags() const 
  {
    return type_->flags(); 
  } // flags

  /**
     Return the parent element type of the element's type.
     Convenience method.
     @return The parent element type
  */
  ElementType& parent() const 
  { 
    return type_->parent(); 
  } // parent

  /**
     Return true if the type of this element can contain the type of
     another element.
     Convenience method.
     @param other The other element
  */
  bool canContain(const Element& other) const
  {
    return type_->canContain(*(other.type_));
  } // canContain

  /**
     Set an attribute and its value into this element.
     @param name The attribute name (Qname)
     @param type The attribute type
     @param value The attribute value
  */
  void setAttribute(const std::string& name, const std::string& type, const std::string& value) 
  {
    type_->setAttribute(atts_, name, type, value);
  } // setAttribute
  
  /**
     Make this element anonymous.
     Remove any <tt>id</tt> or <tt>name</tt> attribute present
     in the element's attributes.
  */
  void anonymize() 
  {
    for (int i = atts_.getLength() - 1; i >= 0; i--) 
    {
      if((atts_.getType(i) == "ID") ||
	 (atts_.getQName(i) == "name"))
      {
	atts_.removeAttribute(i);
      }
    } // for ...
  } // anonymize

  /**
     Clean the attributes of this element.
     Attributes with null name (the name was ill-formed)
     or null value (the attribute was present in the element type but
     not in this actual element) are removed.
  */
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

  /**
     Force this element to preclosed status, meaning that an end-tag has
     been seen but the element cannot yet be closed for structural reasons.
  */
  void preclose() 
  {
    preclosed_ = true;
  } // preclose

  /**
     Return true if this element has been preclosed.
  */
  bool isPreclosed() const
  {
    return preclosed_;
  } // isPreclosed
}; // class Element

const Element Element::Null;

} // namespace SAX

} // namespace Arabica

#endif
