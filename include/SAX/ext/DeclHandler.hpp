#ifndef ARABICA_DECL_HANDLER_H
#define ARABICA_DECL_HANDLER_H

// DeclHandler.h 
// $Id$

#include <string>
#include <SAX/ArabicaConfig.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX 
{

/**
 * SAX2 extension handler for DTD declaration events.
 *
 * <p>This is an optional extension handler for SAX2 to provide
 * information about DTD declarations in an XML document.  XML
 * readers are not required to support this handler, and this
 * handler is not included in the core SAX2 distribution.</p>
 *
 * <p>Note that data-related DTD declarations (unparsed entities and
 * notations) are already reported through the {@link
 * DTDHandler DTDHandler} interface.</p>
 *
 * <p>If you are using the declaration handler together with a lexical
 * handler, all of the events will occur between the
 * {@link LexicalHandler#startDTD startDTD} and the
 * {@link LexicalHandler#endDTD endDTD} events.</p>
 *
 * <p>To set the DeclHandler for an XML reader, use the
 * {@link XMLReader#setProperty setProperty} method
 * with the propertyId "http://xml.org/sax/properties/declaration-handler".
 * If the reader does not support declaration events, it will throw a
 * {@link SAXNotRecognizedException SAXNotRecognizedException}
 * or a
 * {@link SAXNotSupportedException SAXNotSupportedException}
 * when you attempt to register the handler.</p>
 *
 * @since 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 1.0
 * @see XMLReader
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class DeclHandler
{
public:
  virtual ~DeclHandler() { }

  /**
   * Report an element type declaration.
   *
   * <p>The content model will consist of the string "EMPTY", the
   * string "ANY", or a parenthesised group, optionally followed
   * by an occurrence indicator.  The model will be normalized so
   * that all parameter entities are fully resolved and all whitespace 
   * is removed,and will include the enclosing parentheses.  Other
   * normalization (such as removing redundant parentheses or 
   * simplifying occurrence indicators) is at the discretion of the
   * parser.</p>
   *
   * @param name The element type name.
   * @param model The content model as a normalized string.
   */
  virtual void elementDecl(const string_type& name, const string_type& model) = 0;
  /**
   * Report an attribute type declaration.
   *
   * <p>Only the effective (first) declaration for an attribute will
   * be reported.  The type will be one of the strings "CDATA",
   * "ID", "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY",
   * "ENTITIES", a parenthesized token group with 
   * the separator "|" and all whitespace removed, or the word
   * "NOTATION" followed by a space followed by a parenthesized
   * token group with all whitespace removed.</p>
   *
   * <p>Any parameter entities in the attribute value will be
   * expanded, but general entities will not.</p>
   *
   * @param elementName The name of the associated element.
   * @param attributeName The name of the attribute.
   * @param type A string representing the attribute type.
   * @param valueDefault A string representing the attribute default
   *        ("#IMPLIED", "#REQUIRED", or "#FIXED") or empty string if
   *        none of these applies.
   * @param value A string representing the attribute's default value,
   *        or empty string if there is none.
   */
  virtual void attributeDecl(const string_type& elementName,
                             const string_type& attributeName,
                             const string_type& type,
                             const string_type& valueDefault,
                             const string_type& value) = 0;
  /**
   * Report an internal entity declaration.
   *
   * <p>Only the effective (first) declaration for each entity
   * will be reported.  All parameter entities in the value
   * will be expanded, but general entities will not.</p>
   *
   * @param name The name of the entity.  If it is a parameter
   *        entity, the name will begin with '%'.
   * @param value The replacement text of the entity.
   * @see #externalEntityDecl
   * @see DTDHandler#unparsedEntityDecl
   */
  virtual void internalEntityDecl(const string_type& name, const string_type& value) = 0;
  /**
   * Report a parsed external entity declaration.
   *
   * <p>Only the effective (first) declaration for each entity
   * will be reported.</p>
   *
   * @param name The name of the entity.  If it is a parameter
   *        entity, the name will begin with '%'.
   * @param publicId The declared public identifier of the entity, or
   *        an empty string if none was declared.
   * @param systemId The declared system identifier of the entity.
   * @see #internalEntityDecl
   * @see DTDHandler#unparsedEntityDecl
   */
  virtual void externalEntityDecl(const string_type& name, 
                                  const string_type& publicId,
                                  const string_type& systemId) = 0;
}; // class DeclHandler

} // namespace SAX
} // namespace Arabica

#endif
// end of file
