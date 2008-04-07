#ifndef ARABICA_SAX_TAGGLE_SCHEMAIMPL_HPP
#define ARABICA_SAX_TAGGLE_SCHEMAIMPL_HPP

#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include "ElementType.hpp"
#include "Schema.hpp"

namespace Arabica
{
namespace SAX
{

/**
Abstract class representing a TSSL schema.
Actual TSSL schemas are compiled into concrete subclasses of this class.

Based on code from John Cowan's super TagSoup package
**/
class SchemaImpl : public Schema
{
private:
  std::map<std::string, char> entities_;
  std::map<std::string, ElementType*> elementTypes_;

	std::string URI_;
	std::string prefix_;
	ElementType* root_;

public:
  virtual ~SchemaImpl()
  {
    for(std::map<std::string, ElementType*>::iterator i = elementTypes_.begin(), ie = elementTypes_.end(); i != ie; ++i)
      delete i->second;
  } // ~SchemaImpl

	/**
	Add or replace an element type for this schema.
	@param name Name (Qname) of the element
	@param model Models of the element's content as a vector of bits
	@param memberOf Models the element is a member of as a vector of bits
	@param flags Flags for the element
	**/
	void elementType(const std::string& name, int model, int memberOf, int flags) 
  {
		ElementType* e = new ElementType(name, model, memberOf, flags, *this);
    std::string lname = lower_case(name);
		elementTypes_[lname] = e;
		if(memberOf == M_ROOT)
      root_ = elementTypes_[lname];
	} // elementType

	/**
	Get the root element of this schema
	**/
	ElementType& rootElementType() 
  {
		return *root_;
	} // rootElementType

	/**
	Add or replace a default attribute for an element type in this schema.
	@param elemName Name (Qname) of the element type
	@param attrName Name (Qname) of the attribute
	@param type Type of the attribute
	@param value Default value of the attribute; null if no default
	**/
	void attribute(const std::string& elemName, const std::string& attrName, const std::string& type, const std::string& value) 
  {
		ElementType& e = getElementType(elemName);
    if (e == ElementType::Null) 
    {
      throw std::runtime_error("Attribute " + attrName +
				" specified for unknown element type " +
				elemName);
		}
		e.setAttribute(attrName, type, value);
	} // attribute

	/**
	Specify natural parent of an element in this schema.
	@param name Name of the child element
	@param parentName Name of the parent element
	**/
	void parent(std::string name, std::string parentName) 
  {
		ElementType& child = getElementType(name);
		ElementType& parent = getElementType(parentName);
    if (child == ElementType::Null) 
    {
      throw std::runtime_error("No child " + name + " for parent " + parentName);
		}
		if (parent == ElementType::Null) 
    {
			throw std::runtime_error("No parent " + parentName + " for child " + name);
		}
		child.setParent(parent);
	} // parent

	/**
	Add to or replace a character entity in this schema.
	@param name Name of the entity
	@param value Value of the entity
	**/
	void entity(const std::string& name, int value) 
  {
		entities_[name] = value;
	} // entity

	/**
	Get an ElementType by name.
	@param name Name (Qname) of the element type
	@return The corresponding ElementType
	**/
	ElementType& getElementType(const std::string& name)
  {
    std::map<std::string, ElementType*>::iterator elemType = elementTypes_.find(lower_case(name));
    if(elemType == elementTypes_.end())
      return ElementType::Null;
    return *elemType->second;
	} // getElementType

	/**
	Get an entity value by name.
	@param name Name of the entity
	@return The corresponding character, or 0 if none
	**/
	int getEntity(const std::string& name) const
  {
    std::map<std::string, char>::const_iterator ent = entities_.find(name);
    if(ent == entities_.end())
      return 0;
		return ent->second;
	} // getEntity

	/**
	Return the URI (namespace name) of this schema.
	**/
	const std::string& getURI() const
  {
		return URI_;
	} // getURI

	/**
	Return the prefix of this schema.
	**/
	const std::string& getPrefix() const
  {
		return prefix_;
	} // getPrefix

	/**
	Change the URI (namespace name) of this schema.
	**/
	void setURI(std::string uri) 
  {
		URI_ = uri;
	} // setURI

	/**
	Change the prefix of this schema.
	**/
	void setPrefix(std::string prefix) 
  {
		prefix_ = prefix;
	} // setPrefix

private:
  static std::string lower_case(const std::string& str) 
  {
    std::string lower;
    std::transform(str.begin(), str.end(), std::back_inserter(lower), (int(*)(int))std::tolower);
    return lower;
  } // lower_case
}; // class Schema

} // namespace SAX

} // namespace Arabica
#endif
