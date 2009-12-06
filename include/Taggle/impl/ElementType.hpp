#ifndef ARABICA_SAX_ELEMENT_TYPE_HPP
#define ARABICA_SAX_ELEMENT_TYPE_HPP

#include <SAX/helpers/AttributesImpl.hpp>
#include <text/normalize_whitespace.hpp>
#include "Schema.hpp"

namespace Arabica
{

namespace SAX
{


/**
This class represents an element type in the schema.
An element type has a name, a content model vector, a member-of vector,
a flags vector, default attributes, and a schema to which it belongs.

Based on code from John Cowan's super TagSoup package
@see Schema
*/
class ElementType 
{
private:
	std::string name_;		// element type name (Qname)
	std::string namespace_;	// element type namespace name
	std::string localName_;	// element type local name
	int model_;		// bitmap: what the element contains
	int memberOf_;	// bitmap: what element is contained in
	int flags_;		// bitmap: element flags
	AttributesImpl<std::string> atts_;	// default attributes
	ElementType* parent_;	// parent of this element type
	Schema* schema_;	// schema to which this belongs

public:
  static ElementType Null;

private:
  ElementType() :
    name_("<null>"),
    namespace_("<null>"),
    localName_("<null>"),
    model_(0),
    memberOf_(0),
    flags_(0),
    atts_(),
    parent_(0),
    schema_(0)
  {
  } // ElementType

	/**
	Construct an ElementType:
	but it's better to use Schema.element() instead.
	The content model, member-of, and flags vectors are specified as ints.
	@param name The element type name
	@param model ORed-together bits representing the content models
	   allowed in the content of this element type
	@param memberOf ORed-together bits representing the content models
	   to which this element type belongs
	@param flags ORed-together bits representing the flags associated
	   with this element type
	@param schema The schema with which this element type will be
	associated
	*/
	ElementType(const std::string& name, int model, int memberOf, int flags, Schema& schema) :
    name_(name),
    namespace_(),
    localName_(),
    model_(model),
    memberOf_(memberOf),
    flags_(flags),
    parent_(0),
    schema_(&schema)
  {
    namespace_ = namespaceName(name, false);
    localName_ = localName(name);
  } // ElementType

	ElementType(const ElementType& rhs) :
    name_(rhs.name_),
    namespace_(rhs.namespace_),
    localName_(rhs.localName_),
    model_(rhs.model_),
    memberOf_(rhs.memberOf_),
    flags_(rhs.flags_),
    parent_(rhs.parent_),
    schema_(rhs.schema_)
  {
  } // ElementType

  friend class SchemaImpl;

public:
	/**
	Return a namespace name from a Qname.
	The attribute flag tells us whether to return an empty namespace
	name if there is no prefix, or use the schema default instead.
	@param name The Qname
	@param attribute True if name is an attribute name
	@return The namespace name
	**/
	std::string namespaceName(const std::string& name, bool attribute) const
  {
		size_t colon = name.find(':');
    if (colon == std::string::npos) 
			return attribute ? "" : schema_->getURI();

		std::string prefix = name.substr(0, colon);
		if (prefix == "xml") 
			return "http://www.w3.org/XML/1998/namespace";
		else 
			return "urn:x-prefix:" + prefix;
  } // namespaceName

	/**
	Return a local name from a Qname.
	@param name The Qname
	@return The local name
	**/
	std::string localName(const std::string& name) const
  {
		size_t colon = name.find(':');
    if (colon == std::string::npos) 
			return name;
		else 
			return name.substr(colon+1);
  } // localName

	/**
	Returns the name of this element type.
	@return The name of the element type
	*/
	std::string name() const { return name_; }

	/**
	Returns the namespace name of this element type.
	@return The namespace name of the element type
	*/
	std::string namespaceName() const { return namespace_; }

	/**
	Returns the local name of this element type.
	@return The local name of the element type
	*/
	std::string localName() const { return localName_; }

	/**
	Returns the content models of this element type.
	@return The content models of this element type as a vector of bits
	*/
	int model() const { return model_; }

	/**
	Returns the content models to which this element type belongs.
	@return The content models to which this element type belongs as a
	   vector of bits
	*/
	int memberOf() const { return memberOf_; }

	/**
	Returns the flags associated with this element type.
	@return The flags associated with this element type as a vector of bits
	*/
	int flags() const { return flags_; }

	/**
	Returns the default attributes associated with this element type.
	Attributes of type CDATA that don't have default values are
	typically not included.  Other attributes without default values
	have an internal value of <tt>null</tt>.
	The return value is an AttributesImpl to allow the caller to mutate
	the attributes.
	*/
	const AttributesImpl<std::string>& atts() const { return atts_; }

	/**
	Returns the parent element type of this element type.
	@return The parent element type
	*/
	ElementType& parent() const 
  {
    return *parent_;
  } // parent

	/**
	Returns the schema which this element type is associated with.
	@return The schema
	*/
	Schema& schema() const 
  { 
    return *schema_; 
  } // schema


	/**
	Returns true if this element type can contain another element type.
	That is, if any of the models in this element's model vector
	match any of the models in the other element type's member-of
	vector.
	@param other The other element type
	*/
	bool canContain(const ElementType& other) const
  {
		return (model_ & other.memberOf_) != 0;
  } // canContain


	/**
	Sets an attribute and its value into an AttributesImpl object.
	Attempts to set a namespace declaration are ignored.
	@param atts The AttributesImpl object
	@param name The name (Qname) of the attribute
	@param type The type of the attribute
	@param value The value of the attribute
	*/
	void setAttribute(AttributesImpl<std::string>& atts, 
                    const std::string& name, 
                    const std::string& type, 
                    const std::string& value) 
  {
		if (name == "xmlns" || name.find("xmlns:") == 0) 
    {
			return;
    }

		std::string namespaceN = namespaceName(name, true);
		std::string localN = localName(name);
    std::string actualType = type;
    std::string actualValue = value;

		int i = atts.getIndex(name);
		if (i == -1) 
    {
			if (actualType == "") 
        actualType = "CDATA";
			if (actualType != "CDATA") 
        actualValue = Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(value);
			atts.addAttribute(namespaceN, localN, name, actualType, actualValue);
    }
		else 
    {
			if (actualType == "")
        actualType = atts.getType(i);
			if (actualType != ("CDATA")) 
        actualValue = Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(value);
			atts.setAttribute(i, namespaceN, localN, name, actualType, actualValue);
    }
  } // setAttribute

	/**
	Sets an attribute and its value into this element type.
	@param name The name of the attribute
	@param type The type of the attribute
	@param value The value of the attribute
	*/
	void setAttribute(const std::string& name, const std::string& type, const std::string& value) 
  {
		setAttribute(atts_, name, type, value);
  } // setAttribute

	/**
	Sets the models of this element type.
	@param model The content models of this element type as a vector of bits
	*/
	void setModel(int model) 
  { 
    model_ = model; 
  } // setModel

	/**
	Sets the content models to which this element type belongs.
	@param memberOf The content models to which this element type belongs as a vector of bits
	*/
	void setMemberOf(int memberOf) 
  { 
    memberOf_ = memberOf; 
  } // setMemberOf

	/**
	Sets the flags of this element type.
	@param flags associated with this element type The flags as a vector of bits
	*/
	void setFlags(int flags) 
  { 
    flags_ = flags; 
  } // setFlags

	/**
	Sets the parent element type of this element type.
	@param parent The parent element type
	*/
	void setParent(ElementType& parent)
  { 
    parent_ = &parent; 
  } // setParent

  bool operator==(const ElementType& rhs) const
  {
    return (name_ == rhs.name_) &&
           (namespace_ == rhs.namespace_) && 
           (localName_ == rhs.localName_) &&
           (model_ == rhs.model_) &&
           (memberOf_ == rhs.memberOf_) && 
           (flags_ == rhs.flags_) &&
           (parent_ == rhs.parent_) &&
           (schema_ == rhs.schema_);
  } // operator ==

  ElementType& operator=(const ElementType& rhs)
  {
    name_ = rhs.name_;
    namespace_ = rhs.namespace_;
    localName_ = rhs.localName_;
    model_ = rhs.model_;
    memberOf_ = rhs.memberOf_; 
    flags_ = rhs.flags_;
    atts_ = rhs.atts_;
    parent_ = rhs.parent_;
    schema_ = rhs.schema_;

    return *this;
  } // operator=
}; // class ElementType

ElementType ElementType::Null;

} // namespace SAX

} // namespace Arabica

#endif
