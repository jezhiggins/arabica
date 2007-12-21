#ifndef ARABICA_ATTRIBUTES_H
#define ARABICA_ATTRIBUTES_H

// Attributes.h
// $Id$

#include <string>

#include <SAX/ArabicaConfig.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Interface for a list of XML attributes.
 *
 * <p>This interface allows access to a list of attributes in
 * three different ways:</p>
 *
 * <ol>
 * <li>by attribute index;</li>
 * <li>by Namespace-qualified name; or</li>
 * <li>by qualified (prefixed) name.</li>
 * </ol>
 *
 * <p>The list will not contain attributes that were declared
 * #IMPLIED but not specified in the start tag.  It will also not
 * contain attributes used as Namespace declarations (xmlns*) unless
 * the <code>http://xml.org/sax/features/namespace-prefixes</code> 
 * feature is set to <var>true</var> (it is <var>false</var> by 
 * default).</p>
 *
 * <p>If the namespace-prefixes feature (see above) is <var>false</var>, 
 * access by qualified name may not be available; if the 
 * <code>http://xml.org/sax/features/namespaces</code>
 * feature is <var>false</var>, access by Namespace-qualified names 
 * may not be available.</p>
 *
 * <p>This interface replaces the now-deprecated SAX1 {@link
 * AttributeList AttributeList} interface, which does not 
 * contain Namespace support.  In addition to Namespace support, it 
 * adds the <var>getIndex</var> methods (below).</p>
 *
 * <p>The order of attributes in the list is unspecified, and will
 * vary from implementation to implementation.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see AttributesImpl
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class AttributeType 
{
public:
  static const string_type CDATA;
  static const string_type ID;
  static const string_type IDREF;
  static const string_type IDREFS;
  static const string_type NMTOKEN;
  static const string_type NMTOKENS;
  static const string_type ENTITY;
  static const string_type ENTITIES;
  static const string_type NOTATION;
}; // AttributeType

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class Attributes
{
public:

  typedef string_type stringT;

  virtual ~Attributes() { }

  //
  // indexed access
  //
  /**
   * Return the number of attributes in the list.
   *
   * <p>Once you know the number of attributes, you can iterate
   * through the list.</p>
   *
   * @return The number of attributes in the list.
   * @see #getURI(unsigned int)
   * @see #getLocalName(unsigned int)
   * @see #getQName(unsigned int)
   * @see #getType(unsigned int)
   * @see #getValue(unsigned int)
   */
  virtual int getLength() const = 0;

  /**
   * Look up an attribute's Namespace URI by index.
   *
   * @param index The attribute index (zero-based).
   * @return The Namespace URI, or the empty string if none
   *         is available, or if the index is out of range.
   * @see #getLength
   */
  virtual stringT getURI(unsigned int index) const = 0;

  /**
   * Look up an attribute's local name by index.
   *
   * @param index The attribute index (zero-based).
   * @return The local name, or the empty string if Namespace
   *         processing is not being performed, or 
   *         if the index is out of range.
   * @see #getLength
   */
  virtual stringT getLocalName(unsigned int index) const = 0;

  /**
   * Look up an attribute's XML 1.0 qualified name by index.
   *
   * @param index The attribute index (zero-based).
   * @return The XML 1.0 qualified name, or the empty string
   *         if none is available, or if the index
   *         is out of range.
   * @see #getLength
   */
  virtual stringT getQName(unsigned int index) const = 0;

  /**
   * Look up an attribute's type by index.
   *
   * <p>The attribute type is one of the strings "CDATA", "ID",
   * "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY", "ENTITIES",
   * or "NOTATION" (always in upper case).</p>
   *
   * <p>If the parser has not read a declaration for the attribute,
   * or if the parser does not report attribute types, then it must
   * return the value "CDATA" as stated in the XML 1.0 Recommentation
   * (clause 3.3.3, "Attribute-Value Normalization").</p>
   *
   * <p>For an enumerated attribute that is not a notation, the
   * parser will report the type as "NMTOKEN".</p>
   *
   * @param index The attribute index (zero-based).
   * @return The attribute's type as a string, or an empty string if the
   *         index is out of range.
   * @see #getLength
   */
  virtual stringT getType(unsigned int index) const = 0;

  /**
   * Look up an attribute's value by index.
   *
   * <p>If the attribute value is a list of tokens (IDREFS,
   * ENTITIES, or NMTOKENS), the tokens will be concatenated
   * into a single string with each token separated by a
   * single space.</p>
   *
   * @param index The attribute index (zero-based).
   * @return The attribute's value as a string, or an empty string if the
   *         index is out of range.
   * @see #getLength
   */
  virtual stringT getValue(unsigned int index) const = 0;

  //
  // name based query
  //
  /**
   * Look up the index of an attribute by Namespace name.
   *
   * @param uri The Namespace URI, or the empty string if
   *        the name has no Namespace URI.
   * @param localName The attribute's local name.
   * @return The index of the attribute, or -1 if it does not
   *         appear in the list.
   */
  virtual int getIndex(const stringT& uri, const stringT& localName) const = 0;

  /**
   * Look up the index of an attribute by XML 1.0 qualified name.
   *
   * @param qName The qualified (prefixed) name.
   * @return The index of the attribute, or -1 if it does not
   *         appear in the list.
   */
  virtual int getIndex(const stringT& qName) const = 0;

  /**
   * Look up an attribute's type by Namespace name.
   *
   * <p>See {@link #getType(unsigned int) getType(unsigned int)} for a description
   * of the possible types.</p>
   *
   * @param uri The Namespace URI, or the empty String if the
   *        name has no Namespace URI.
   * @param localName The local name of the attribute.
   * @return The attribute type as a string, or an empty string if the
   *         attribute is not in the list or if Namespace
   *         processing is not being performed.
   */
  virtual stringT getType(const stringT& uri, const stringT& localName) const = 0;

  /**
   * Look up an attribute's type by XML 1.0 qualified name.
   *
   * <p>See {@link #getType(unsigned int) getType(unsigned int)} for a description
   * of the possible types.</p>
   *
   * @param qName The XML 1.0 qualified name.
   * @return The attribute type as a string, or an empty string if the
   *         attribute is not in the list or if qualified names
   *         are not available.
   */
  virtual stringT getType(const stringT& qName) const = 0;

  /**
   * Look up an attribute's value by Namespace name.
   *
   * <p>See {@link #getValue(unsigned int) getValue(unsigned int)} for a
   * description of the possible values.</p>
   *
   * @param uri The Namespace URI, or the empty String if the
   *        name has no Namespace URI.
   * @param localName The local name of the attribute.
   * @return The attribute value as a string, or an empty string if the
   *         attribute is not in the list.
   */
  virtual stringT getValue(const stringT& uri, const stringT& localName) const = 0;

  /**
   * Look up an attribute's value by XML 1.0 qualified name.
   *
   * <p>See {@link #getValue(unsigned int) getValue(unsigned int)} for a
   * description of the possible values.</p>
   *
   * @param qName The XML 1.0 qualified name.
   * @return The attribute value as a string, or an empty string if the
   *         attribute is not in the list or if qualified names
   *         are not available.
   */
  virtual stringT getValue(const stringT& qName) const = 0;

private:
  static AttributeType<string_type, string_adaptor> types_;
}; // class Attributes

template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::CDATA = string_adaptor::construct_from_utf8("CDATA");
template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::ID = string_adaptor::construct_from_utf8("ID");
template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::IDREF = string_adaptor::construct_from_utf8("IDREF");
template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::IDREFS = string_adaptor::construct_from_utf8("IDREFS");
template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::NMTOKEN = string_adaptor::construct_from_utf8("NMTOKEN");
template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::NMTOKENS = string_adaptor::construct_from_utf8("NMTOKENS");
template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::ENTITY = string_adaptor::construct_from_utf8("ENTITY");
template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::ENTITIES = string_adaptor::construct_from_utf8("ENTITIES");
template<class string_type, class string_adaptor>
const string_type AttributeType<string_type, string_adaptor>::NOTATION = string_adaptor::construct_from_utf8("NOTATION");

} // namespace SAX
} // namespace Arabica

#endif
// end of file
