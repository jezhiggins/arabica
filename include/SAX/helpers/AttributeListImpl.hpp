#ifndef ARABICA_ATTRIBUTES_LIST_IMPL_H
#define ARABICA_ATTRIBUTES_LIST_IMPL_H
// SAX default implementation for AttributeList.
// $Id$

#include <SAX/ArabicaConfig.hpp>
#include <AttributeList.hpp>
#include <vector>
#include <algorithm>

namespace Arabica
{
namespace SAX
{

template<class string_type, class string_adaptor>
class Attribute
{
public:
  Attribute(const string_type& name, const string_adaptor& type, const string_adaptor& value)
		: name_(name), type_(type), value_(value)
	{}
	virtual ~Attribute() { }

public:
	string_type name_;
	const string_type& type_;
	string_type value_;
};

static const std::string empty_;
const std::string const types[] = { empty_, "CDATA", "ID", "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY", "ENTITIES", "NOTATION" }; // TV

/**
 * Default implementation for AttributeList.
 *
 * <p>AttributeList implements the deprecated SAX1 {@link
 * AttributeList AttributeList} interface, and has been
 * replaced by the new SAX2 {@link AttributesImpl
 * AttributesImpl} interface.</p>
 *
 * <p>This class provides a convenience implementation of the SAX
 * {@link AttributeList AttributeList} interface.  This 
 * implementation is useful both for SAX parser writers, who can use 
 * it to provide attributes to the application, and for SAX application 
 * writers, who can use it to create a persistent copy of an element's 
 * attribute specifications:</p>
 *
 * <pre>
 * private AttributeList myatts;
 *
 * void startElement(const string_type& name, const AttributeList& atts)
 * {
 *   // create a persistent copy of the attribute list
 *   // for use outside this method
 *   AttributeListImpl myatts(atts);
 *   [...]
 * }
 * </pre>
 *
 * <p>Please note that SAX parsers are not required to use this
 * class to provide an implementation of AttributeList; it is
 * supplied only as an optional convenience.  In particular, 
 * parser writers are encouraged to invent more efficient
 * implementations.</p>
 *
 * @deprecated This class implements a deprecated interface,
 *             {@link AttributeList AttributeList};
 *             that interface has been replaced by
 *             {@link Attributes Attributes},
 *             which is implemented in the
 *             {@link AttributesImpl 
 *            AttributesImpl} helper class.
 * @since SAX 1.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see AttributeList
 * @see DocumentHandler#startElement 
 */
template<class string_type, class string_adaptor>
class AttributeListImpl : public AttributeList<string_type, string_adaptor>
{
public:
  AttributeListImpl() : atts_() { }
  AttributeListImpl(const AttributeList& atts)
	  : atts_(atts.getLength())
  {
    setAttributeList(atts);
  } // AttributeListImpl

  AttributeListImpl& operator=(const AttributeList& atts)
  { 
    setAttributeList(atts);
    
    return *this;
  } // operator=

  virtual ~AttributeListImpl() { clear(); }

  //////////////////////////////////////////////////////////////////////
  // Methods specific to this class.
  //////////////////////////////////////////////////////////////////////
  /**
   * Set the attribute list, discarding previous contents.
   *
   * <p>This method allows an application writer to reuse an
   * attribute list easily.</p>
   *
   * @param atts The attribute list to copy.
   */
  void setAttributeList(const AttributeList& atts)
  {
    int count = atts.getLength();

    clear();

    for (int i = 0; i < count; ++i) 
      addAttribute(atts.getName(i), atts.getType(i), atts.getValue(i));
  } // setAttributeList

  /**
   * Add an attribute to an attribute list.
   *
   * <p>This method is provided for SAX parser writers, to allow them
   * to build up an attribute list incrementally before delivering
   * it to the application.</p>
   *
   * @param name The attribute name.
   * @param type The attribute type ("NMTOKEN" for an enumeration).
   * @param value The attribute value.
   * @see #removeAttribute
   * @see DocumentHandler#startElement
   */
  void addAttribute(const string_type& name, const string_adaptor& type, const string_adaptor& value)
  {
	  atts_.push_back(new Attribute<string_type, string_adaptor>(name, type, value)); // TV
  } // addAttribute

  /**
   * Remove an attribute from the list.
   *
   * <p>SAX application writers can use this method to filter an
   * attribute out of an AttributeList.  Note that invoking this
   * method will change the length of the attribute list and
   * some of the attribute's indices.</p>
   *
   * <p>If the requested attribute is not in the list, this is
   * a no-op.</p>
   *
   * @param name The attribute name.
   * @see #addAttribute
   */
  void removeAttribute(const string_type& name)
  {
    int i = index(name);

    if(i < 0) return;
	    delete atts_[i];
    atts_.erase(atts_.begin() + i);
  } // removeAttribute

  /**
   * Clear the attribute list.
   *
   * <p>SAX parser writers can use this method to reset the attribute
   * list between DocumentHandler.startElement events.  Normally,
   * it will make sense to reuse the same AttributeListImpl object
   * rather than allocating a new one each time.</p>
   *
   * @see DocumentHandler#startElement
   */
  void clear()
  {
	  while(!atts_.empty()) 
    {
		  delete atts_.back();
		  atts_.pop_back();
	  }
  } // clear

  //////////////////////////////////////////////////////////////////////
  // Implementation of AttributeList
  //////////////////////////////////////////////////////////////////////
  /**
   * Return the number of attributes in the list.
   *
   * @return The number of attributes in the list.
   * @see AttributeList#getLength
   */
  virtual int getLength() const
  {
    return atts_.size();
  } // getLength

  /**
   * Get the name of an attribute (by position).
   *
   * @param i The position of the attribute in the list.
   * @return The attribute name as a string, or an empty string if there
   *         is no attribute at that position.
   * @see AttributeList#getName(int)
   */
  virtual const string_type& getName(int i) const
  {
	  if(i > atts_.size())
		  return empty_;
    return atts_[i]->name_;
  } // getName

  /**
   * Get the type of an attribute (by position).
   *
   * @param i The position of the attribute in the list.
   * @return The attribute type as a string ("NMTOKEN" for an
   *         enumeration, and "CDATA" if no declaration was
   *         read), or an empty string if there is no attribute at
   *         that position.
   * @see AttributeList#getType(int)
   */
  virtual const string_type& getType(int i) const
  {
	  if(i > atts_.size())
		  return empty_;
	  return atts_[i]->type_;
  } // getType

  /**
   * Get the value of an attribute (by position).
   *
   * @param i The position of the attribute in the list.
   * @return The attribute value as a string, or an empty string if
   *         there is no attribute at that position.
   * @see AttributeList#getValue(int)
   */
  virtual const string_type& getValue(int i) const
  {
	  if(i > atts_.size())
		  return empty_;
	  return atts_[i]->value_;
  } // getValue

  /**
   * Get the type of an attribute (by name).
   *
   * @param name The attribute name.
   * @return The attribute type as a string ("NMTOKEN" for an
   *         enumeration, and "CDATA" if no declaration was
   *         read).
   * @see AttributeList#getType(java.lang.String)
   */
  virtual const string_type& getType(const string_adaptor& name) const
  {
	  int i = index(name);
	  return i < 0 ? empty_ : getType(i);
  } // getType

  /**
   * Get the value of an attribute (by name).
   *
   * @param name The attribute name.
   * @see AttributeList#getValue(java.lang.String)
   */
  virtual const string_type& getValue(const string_adaptor& name) const
  {
	  int i = index(name);
	  return i < 0 ? empty_ : getValue(i);
  } // getValue

private:
  //////////////////////////////////////////////////////////////////////
  // Internal state.
  //////////////////////////////////////////////////////////////////////
  std::vector<Attribute<string_type, string_adaptor> *> atts_;

  int index(const string_type& name) const
  {
	  int i = 0, res = -1;
	  std::vector<Attribute<string_type, string_adaptor>*>::const_iterator iter;
	  for (iter = atts_.begin() ; iter != atts_.end() ; i++, iter++)
		  if ((*iter)->name_ == name) {
			  res = i;
			  break;
		  }
	  return res;
  } // index

  bool operator==(const AttributeList&) const; // not implemented
}; // class AttributeListImpl

} // namespace SAX
} // namespace Arabica

#endif
// end of file

