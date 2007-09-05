#ifndef ARABICA_ATTRIBUTES_LIST_H
#define ARABICA_ATTRIBUTES_LIST_H

// SAX Attribute List Interface.
// $Id$

#include <string>

#include <SAX/ArabicaConfig.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Interface for an element's attribute specifications.
 *
 * <p>This is the original SAX1 interface for reporting an element's
 * attributes.  Unlike the new {@link Attributes Attributes}
 * interface, it does not support Namespace-related information.</p>
 *
 * <p>When an attribute list is supplied as part of a
 * {@link DocumentHandler#startElement startElement}
 * event, the list will return valid results only during the
 * scope of the event; once the event handler returns control
 * to the parser, the attribute list is invalid.  To save a
 * persistent copy of the attribute list, use the SAX1
 * {@link AttributeListImpl AttributeListImpl}
 * helper class.</p>
 *
 * <p>An attribute list includes only attributes that have been
 * specified or defaulted: #IMPLIED attributes will not be included.</p>
 *
 * <p>There are two ways for the SAX application to obtain information
 * from the AttributeList.  First, it can iterate through the entire
 * list:</p>
 *
 * <pre>
 * void startElement(const stringT& name, const AttributeListT& atts) 
 * {
 *   for(int i = 0; i < atts.getLength(); ++i) 
 *   {
 *     stringT name = atts.getName(i);
 *     stringT type = atts.getType(i);
 *     stringT value = atts.getValue(i);
 *     [...]
 *   }
 * }
 * </pre>
 *
 * <p>(Note that the result of getLength() will be zero if there
 * are no attributes.)
 *
 * <p>As an alternative, the application can request the value or
 * type of specific attributes:</p>
 *
 * <pre>
 * void startElement(const string& name, const AttributeListT& atts) 
 * {
 *   stringT identifier = atts.getValue("id");
 *   stringT label = atts.getValue("label");
 *   [...]
 * }
 * </pre>
 *
 * @deprecated This interface has been replaced by the SAX2
 *             {@link Attributes Attributes}
 *             interface, which includes Namespace support.
 * @since SAX 1.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see DocumentHandler#startElement startElement
 * @see AttributeListImpl 
 */
template<class string_type, class string_adaptor>
class AttributeList
{
public:
  typedef string_type stringT;

  virtual ~AttributeList() { }

  //
  // Iteration methods.
  //
  /**
   * Return the number of attributes in this list.
   *
   * <p>The SAX parser may provide attributes in any
   * arbitrary order, regardless of the order in which they were
   * declared or specified.  The number of attributes may be
   * zero.</p>
   *
   * @return The number of attributes in the list.  
   */
  virtual int getLength() const = 0;
  /**
   * Return the name of an attribute in this list (by position).
   *
   * <p>The names must be unique: the SAX parser shall not include the
   * same attribute twice.  Attributes without values (those declared
   * #IMPLIED without a value specified in the start tag) will be
   * omitted from the list.</p>
   *
   * <p>If the attribute name has a namespace prefix, the prefix
   * will still be attached.</p>
   *
   * @param i The index of the attribute in the list (starting at 0).
   * @return The name of the indexed attribute, or an empty string
   *         if the index is out of range.
   * @see #getLength 
   */
  virtual const stringT& getName(int i) const = 0;
  /**
   * Return the type of an attribute in the list (by position).
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
   * @param i The index of the attribute in the list (starting at 0).
   * @return The attribute type as a string, or
   *         an empty string if the index is out of range.
   * @see #getLength 
   * @see #getType(const stringT&)
   */
  virtual const stringT& getType(int i) const = 0;
  /**
   * Return the value of an attribute in the list (by position).
   *
   * <p>If the attribute value is a list of tokens (IDREFS,
   * ENTITIES, or NMTOKENS), the tokens will be concatenated
   * into a single string separated by whitespace.</p>
   *
   * @param i The index of the attribute in the list (starting at 0).
   * @return The attribute value as a string, or
   *         an empty string if the index is out of range.
   * @see #getLength
   * @see #getValue(stringT)
   */
  virtual const stringT& getValue(int i) const = 0;

  //
  // Lookup methods.
  //
  /**
   * Return the type of an attribute in the list (by name).
   *
   * <p>The return value is the same as the return value for
   * getType(int).</p>
   *
   * <p>If the attribute name has a namespace prefix in the document,
   * the application must include the prefix here.</p>
   *
   * @param name The name of the attribute.
   * @return The attribute type as a string, or an empty string if no
   *         such attribute exists.
   * @see #getType(int)
   */
  virtual const stringT& getType(const stringT& name) const = 0;
  /**
   * Return the value of an attribute in the list (by name).
   *
   * <p>The return value is the same as the return value for
   * getValue(int).</p>
   *
   * <p>If the attribute name has a namespace prefix in the document,
   * the application must include the prefix here.</p>
   *
   * @param name The name of the attribute in the list.
   * @return The attribute value as a string, or an empty string if
   *         no such attribute exists.
   * @see #getValue(int)
   */
  virtual const stringT& getValue(const stringT& name) const = 0;

}; // class AttributeList

} // namespace SAX
} // namespace Arabica

#endif
// end of file
