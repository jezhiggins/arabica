#ifndef ARABICA_ATTRIBUTES_IMPL_H
#define ARABICA_ATTRIBUTES_IMPL_H

// AttributesImpl.h - default implementation of Attributes.
// $Id$

#include <SAX/ArabicaConfig.hpp>
#include <SAX/Attributes.hpp>
#include <stdexcept>
#include <deque>

namespace Arabica
{
namespace SAX
{

/**
 * Default implementation of the Attributes interface.
 *
 * <p>This class provides a default implementation of the SAX2
 * {@link Attributes Attributes} interface, with the 
 * addition of manipulators so that the list can be modified or 
 * reused.</p>
 *
 * <p>There are two typical uses of this class:</p>
 *
 * <ol>
 * <li>to take a persistent snapshot of an Attributes object
 *  in a {@link ContentHandler#startElement startElement} event; or</li>
 * <li>to construct or modify an Attributes object in a SAX2 driver or filter.</li>
 * </ol>
 *
 * <p>This class replaces the now-deprecated SAX1 {@link 
 * AttributeListImpl AttributeListImpl}
 * class.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class AttributesImpl : public Attributes<string_type, string_adaptor>
{
public:
  typedef Attributes<string_type, string_adaptor> AttributesT;

  struct Attr
  {
    Attr(const string_type& uri, 
         const string_type& localName, 
         const string_type& qName, 
         const string_type& type, 
         const string_type& value) :
         uri_(uri), localName_(localName), qName_(qName), type_(type), value_(value) 
         { } 
    Attr() { }
    Attr& operator=(const Attr& rhs) 
    {
      uri_ = rhs.uri_;
      localName_ = rhs.localName_;
      qName_ = rhs.qName_;
      type_ = rhs.type_;
      value_ = rhs.value_;

      return *this;
    } // operator=
    bool operator==(const Attr& rhs) const
    {
      return (uri_ == rhs.uri_) && 
             (localName_ == rhs.localName_) && 
             (qName_ == rhs.qName_) && 
             (type_ == rhs.type_) && 
             (value_ == rhs.value_);
    } // operator==

    string_type uri_;
	  string_type localName_;
	  string_type qName_;
	  string_type type_;
	  string_type value_;
  }; // Attr

  ////////////////////////////////////////////////////////////////////
  // Constructors.
  AttributesImpl() { } 
  AttributesImpl(const AttributesT& rhs)
  {
    setAttributes(rhs);
  } // AttributesImpl

  AttributesImpl& operator=(const AttributesT& rhs) 
  {
    setAttributes(rhs);
  } // operator=

  bool operator==(const AttributesImpl& rhs) const
  {
    return attributes_ == rhs.attributes_;
  } // operator==

  ////////////////////////////////////////////////////////////////////
  // Implementation of SAX::Attributes.
  /**
   * Return the number of attributes in the list.
   *
   * @return The number of attributes in the list.
   * @see Attributes#getLength
   */
  virtual int getLength() const
  {
    return static_cast<int>(attributes_.size());
  } // getLength

  /**
   * Return an attribute's Namespace URI.
   *
   * @param index The attribute's index (zero-based).
   * @return The Namespace URI, the empty string if none is
   *         available, or if the index is out of range.
   * @see Attributes#getURI
   */
  virtual string_type getURI(unsigned int index) const
  {
	  if(index < attributes_.size())
      return attributes_[index].uri_;
    return emptyString_;
  } // getUri

  /**
   * Return an attribute's local name.
   *
   * @param index The attribute's index (zero-based).
   * @return The attribute's local name, the empty string if 
   *         none is available, or if the index if out of range.
   * @see Attributes#getLocalName
   */
  virtual string_type getLocalName(unsigned int index) const
  {
	  if(index < attributes_.size())
      return attributes_[index].localName_;
	
    return emptyString_;
  } // getLocalName

  /**
   * Return an attribute's qualified (prefixed) name.
   *
   * @param index The attribute's index (zero-based).
   * @return The attribute's qualified name, the empty string if 
   *         none is available, or if the index is out of bounds.
   * @see Attributes#getQName
   */
  virtual string_type getQName(unsigned int index) const
  {
    if(index < attributes_.size())
      return attributes_[index].qName_;

    return emptyString_;
  } // getQName

  /**
   * Return an attribute's type by index.
   *
   * @param index The attribute's index (zero-based).
   * @return The attribute's type, "CDATA" if the type is unknown, or an empty
   *         string if the index is out of bounds.
   * @see Attributes#getType(int)
   */
  virtual string_type getType(unsigned int index) const
  {
	  if(index < attributes_.size())
	    return attributes_[index].type_;

    return emptyString_;
  } // getType

  /**
   * Return an attribute's value by index.
   *
   * @param index The attribute's index (zero-based).
   * @return The attribute's value or an empty string if the index is out of bounds.
   * @see Attributes#getValue(int)
   */
  virtual string_type getValue(unsigned int index) const
  {
	  if(index < attributes_.size())
	    return attributes_[index].value_;
	
    return emptyString_;
  } // getValue

  /**
   * Look up an attribute's index by Namespace name.
   *
   * <p>In many cases, it will be more efficient to look up the name once and
   * use the index query methods rather than using the name query methods
   * repeatedly.</p>
   *
   * @param uri The attribute's Namespace URI, or the empty
   *        string if none is available.
   * @param localName The attribute's local name.
   * @return The attribute's index, or -1 if none matches.
   * @see Attributes#getIndex(const string_type&,const string_type&)
   */
  virtual int getIndex(const string_type& uri, const string_type& localName) const
  {
    typename AttrList::const_iterator a = std::find_if(attributes_.begin(), attributes_.end(), AttributeNamed(uri, localName));
    if(a != attributes_.end())
      return static_cast<int>(std::distance(attributes_.begin(), a));
    return -1;
  } // getIndex

  /**
   * Look up an attribute's index by qualified (prefixed) name.
   *
   * @param qName The qualified name.
   * @return The attribute's index, or -1 if none matches.
   * @see Attributes#getIndex(const string_type&)
   */
  virtual int getIndex(const string_type& qName) const
  {
	  size_t max = attributes_.size();
	  for(size_t i = 0; i < max; ++i)
    {
	    if(attributes_[i].qName_ == qName)
		    return static_cast<int>(i);
    }
    return -1;
  } // getIndex

  /**
   * Look up an attribute's type by Namespace-qualified name.
   *
   * @param uri The Namespace URI, or the empty string for a name
   *        with no explicit Namespace URI.
   * @param localName The local name.
   * @return The attribute's type, or an empty string if there is no
   *         matching attribute.
   * @see Attributes#getType(const string_type&,const string_type&)
   */
  virtual string_type getType(const string_type& uri, const string_type& localName) const
  {
    typename AttrList::const_iterator a = std::find_if(attributes_.begin(), attributes_.end(), AttributeNamed(uri, localName));
    if(a != attributes_.end())
      return a->type_;
	  return emptyString_;
  } // getType

  /**
   * Look up an attribute's type by qualified (prefixed) name.
   *
   * @param qName The qualified name.
   * @return The attribute's type, or an empty string if there is no
   *         matching attribute.
   * @see Attributes#getType(const string_type&)
   */
  virtual string_type getType(const string_type& qName) const
  {
	  size_t max = attributes_.size();
	  for(size_t i = 0; i < max; ++i) 
    {
	    if(attributes_[i].qName_ == qName) 
		    return attributes_[i].type_;
    } // for ...
    return emptyString_;
  } // getType

  /**
   * Look up an attribute's value by Namespace-qualified name.
   *
   * @param uri The Namespace URI, or the empty string for a name
   *        with no explicit Namespace URI.
   * @param localName The local name.
   * @return The attribute's value, or an empty string if there is no
   *         matching attribute.
   * @see Attributes#getValue(const string_type&,const string_type&)
   */
  virtual string_type getValue(const string_type& uri, const string_type& localName) const
  {
    typename AttrList::const_iterator a = std::find_if(attributes_.begin(), attributes_.end(), AttributeNamed(uri, localName));
    if(a != attributes_.end())
        return a->value_;
	  return emptyString_;
  } // getType

  /**
   * Look up an attribute's value by qualified (prefixed) name.
   *
   * @param qName The qualified name.
   * @return The attribute's value, or an empty string if there is no
   *         matching attribute.
   * @see Attributes#getValue(const string_type&)
   */
  virtual string_type getValue(const string_type& qName) const
  {
	  size_t max = attributes_.size();
	  for(size_t i = 0; i < max; ++i) 
    {
	    if(attributes_[i].qName_ == qName) 
		    return attributes_[i].value_;
    } // for ...
    return emptyString_;
  } // getValue

  ////////////////////////////////////////////////////////////////////
  // Manipulators.
  /**
   * Clear the attribute list for reuse.
   */
  void clear()
  {
	  attributes_.erase(attributes_.begin(), attributes_.end());
  } // clear

  /**
   * Copy an entire Attributes object.
   *
   * <p>It may be more efficient to reuse an existing object
   * rather than constantly allocating new ones.</p>
   * 
   * @param atts The attributes to copy.
   */
  void setAttributes(const AttributesT& atts)
  {
	  clear();
	  
    int max = atts.getLength();
	  for(int i = 0; i < max; ++i) 
      attributes_.push_back(Attr(atts.getURI(i),
                          atts.getLocalName(i),
                          atts.getQName(i),
                          atts.getType(i),
                          atts.getValue(i)));
  } // setAttributes

  /**
   * Add an attribute to the end of the list.
   *
   * <p>For the sake of speed, this method does no checking
   * to see if the attribute is already in the list: that is
   * the responsibility of the application.</p>
   *
   * @param uri The Namespace URI, or the empty string if
   *        none is available or Namespace processing is not
   *        being performed.
   * @param localName The local name, or the empty string if
   *        Namespace processing is not being performed.
   * @param qName The qualified (prefixed) name, or the empty string
   *        if qualified names are not available.
   * @param type The attribute type as a string.
   * @param value The attribute value.
   */
  void addAttribute(const string_type& uri, 
                    const string_type& localName, 
                    const string_type& qName,
	 	                const string_type& type, 
                    const string_type& value)
  {
    attributes_.push_back(Attr(uri, localName, qName, type, value));
  } // addAttribute

  void addAttribute(const Attr& attr)
  {
    attributes_.push_back(attr);
  } // addAttribute

  /**
   * Add an attribute to the end of the list.
   *
   * @param uri The Namespace URI, or the empty string if
   *        none is available or Namespace processing is not
   *        being performed.
   * @param localName The local name, or the empty string if
   *        Namespace processing is not being performed.
   * @param qName The qualified (prefixed) name, or the empty string
   *        if qualified names are not available.
   * @param type The attribute type as a string.
   * @param value The attribute value.
   */
  void addOrReplaceAttribute(const string_type& uri, 
                             const string_type& localName, 
                             const string_type& qName,
	 	                         const string_type& type, 
                             const string_type& value)
  {
    typename AttrList::iterator a = std::find_if(attributes_.begin(), attributes_.end(), AttributeNamed(uri, localName));
    if(a != attributes_.end())
    {
      a->value_ = value;
      return;
    } // if ...

    attributes_.push_back(Attr(uri, localName, qName, type, value));
  } // addOrReplaceAttribute

  /**
   * Set an attribute in the list.
   *
   * <p>For the sake of speed, this method does no checking
   * for name conflicts or well-formedness: such checks are the
   * responsibility of the application.</p>
   *
   * @param index The index of the attribute (zero-based).
   * @param uri The Namespace URI, or the empty string if
   *        none is available or Namespace processing is not
   *        being performed.
   * @param localName The local name, or the empty string if
   *        Namespace processing is not being performed.
   * @param qName The qualified name, or the empty string
   *        if qualified names are not available.
   * @param type The attribute type as a string.
   * @param value The attribute value.
   * @exception java.lang.ArrayIndexOutOfBoundsException When the
   *            supplied index does not point to an attribute
   *            in the list.
   */
  void setAttribute(unsigned int index,
                    const string_type& uri, 
                    const string_type& localName, 
                    const string_type& qName,
			              const string_type& type, 
                    const string_type& value)
  {
	  if(index < attributes_.size()) 
    {
      Attr& a = attributes_[index];
	    a.uri_ = uri;
	    a.localName_ = localName;
	    a.qName_ = qName;
	    a.type_ = type;
	    a.value_ = value;
    } 
    else 
	    badIndex(index);
  } // setAttribute

  /**
   * Remove an attribute from the list.
   *
   * @param index The index of the attribute (zero-based).
   * @exception std::out_of_range When the
   *            supplied index does not point to an attribute
   *            in the list.
   */
  void removeAttribute(unsigned int index)
  {
	  if(index < attributes_.size()) 
      attributes_.erase(attributes_.begin() + index);
    else 
	    badIndex(index);
  } // removeAttribute

  /**
   * Set the Namespace URI of a specific attribute.
   *
   * @param index The index of the attribute (zero-based).
   * @param uri The attribute's Namespace URI, or the empty
   *        string for none.
   * @exception std::out_of_range When the
   *            supplied index does not point to an attribute
   *            in the list.
   */
  void setURI(unsigned int index, const string_type& uri)
  {
	  if(index < attributes_.size())
      attributes_[index].uri_ = uri;
	  else 
	    badIndex(index);
  } // setURI

  /**
   * Set the local name of a specific attribute.
   *
   * @param index The index of the attribute (zero-based).
   * @param localName The attribute's local name, or the empty
   *        string for none.
   * @exception std::out_of_range When the
   *            supplied index does not point to an attribute
   *            in the list.
   */
  void setLocalName(unsigned int index, const string_type& localName)
  {
	  if(index < attributes_.size())
      attributes_[index].localName_ = localName;
	  else 
	    badIndex(index);
  } // setLocalName

  /**
   * Set the qualified name of a specific attribute.
   *
   * @param index The index of the attribute (zero-based).
   * @param qName The attribute's qualified name, or the empty
   *        string for none.
   * @exception std::out_of_range When the
   *            supplied index does not point to an attribute
   *            in the list.
   */
  void setQName(unsigned int index, const string_type& qName)
  {
	  if(index >= 0 && index < attributes_.size()) 
      attributes_[index].qName_ = qName;
	  else 
	    badIndex(index);
  } // setQName

  /**
   * Set the type of a specific attribute.
   *
   * @param index The index of the attribute (zero-based).
   * @param type The attribute's type.
   * @exception std::out_of_range When the
   *            supplied index does not point to an attribute
   *            in the list.
   */
  void setType(unsigned int index, const string_type& type)
  {
    if(index >= 0 && index < attributes_.size()) 
      attributes_[index].type_ = type;
    else 
      badIndex(index);
  } // setType

  /**
   * Set the value of a specific attribute.
   *
   * @param index The index of the attribute (zero-based).
   * @param value The attribute's value.
   * @exception std::out_of_range When the
   *            supplied index does not point to an attribute
   *            in the list.
   */
  void setValue(unsigned int index, const string_type& value)
  {
    if(index < attributes_.size()) 
      attributes_[index].value_ = value;
    else 
      badIndex(index);
  } // setURI

private:
  ////////////////////////////////////////////////////////////////////
  // Internal methods.
  ////////////////////////////////////////////////////////////////////
  void badIndex(unsigned int index)
  {
    // sort out
    std::string msg =
	    "Attempt to modify attribute at illegal index: " + index;
    throw std::out_of_range(msg);
  }

  class AttributeNamed
  {
  public:
    AttributeNamed(const string_type& uri, const string_type& localName) :
        uri_(uri), localName_(localName) { }
    AttributeNamed(const AttributeNamed& rhs) :
        uri_(rhs.uri_), localName_(rhs.localName_) { }
    ~AttributeNamed() { }

    bool operator()(const Attr& attr) const
    {
      return (attr.uri_ == uri_) && (attr.localName_ == localName_);
    } // operator()

  private:
    const string_type& uri_;
    const string_type& localName_;

    AttributeNamed& operator=(const AttributeNamed&);
    bool operator==(const AttributeNamed&) const;
  }; // class AttributeNamed

  typedef typename std::deque<Attr> AttrList;
  AttrList attributes_;
  
  string_type emptyString_;
}; // class AttributesImpl

} // namespace SAX
} // namespace Arabica

#endif 

