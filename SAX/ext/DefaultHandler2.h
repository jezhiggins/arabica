#ifndef DEFAULTHANDLER2_H
#define DEFAULTHANDLER2_H

// DefaultHandler.h 
// $Id$

#include <SAX/helpers/DefaultHandler.h>
#include <SAX/ext/DeclHandler.h>
#include <SAX/ext/LexicalHandler.h>

namespace SAX {

/**
 * Default base class for SAX2 event handlers.
 *
 * <p>This class extends the SAX2 base 
 * {@link basic_DefaultHandler} handler class to 
 * support the SAX2 {@link basic_LexicalHandler LexicalHandler}
 * and {@link basic_DeclHandler DeclHandler} extensions. 
 * The added handler methods just return; subclassers may 
 * override on a method-by-method basis.
 *
 * Note: this class might yet learn that the 
 * ContentHandler.setDocumentLocator() call might be 
 * passed a {@link basic_Locator2 Locator2} object, and 
 * that the ContentHandler.startElement() call might be 
 * passed a {@link basic_Attributes2 Attributes2} object.
 * 
 * @since SAX 2.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see basic_DefaultHandler
 * @see basic_LexicalHandler
 * @see basic_DeclHandler
 */
template<class string_type>
class basic_DefaultHandler2 : public basic_DefaultHandler<string_type>, 
					public basic_LexicalHandler<string_type>,
					public basic_DeclHandler<string_type>
{
public:
  typedef string_type stringT;

  basic_DefaultHandler2() { }
  virtual ~basic_DefaultHandler2() { }

  //////////////////////////////////////////////////////////
  // LexicalHandler
  /**
   * Report the start of DTD declarations, if any.
   *
   * <p>This method is intended to report the beginning of the
   * DOCTYPE declaration; if the document has no DOCTYPE declaration,
   * this method will not be invoked.</p>
   *
   * <p>All declarations reported through 
   * {@link basic_DTDHandler DTDHandler} or
   * {@link basic_DeclHandler DeclHandler} events must appear
   * between the startDTD and {@link #endDTD endDTD} events.
   * Declarations are assumed to belong to the internal DTD subset
   * unless they appear between {@link #startEntity startEntity}
   * and {@link #endEntity endEntity} events.  Comments and
   * processing instructions from the DTD should also be reported
   * between the startDTD and endDTD events, in their original 
   * order of (logical) occurrence; they are not required to
   * appear in their correct locations relative to DTDHandler
   * or DeclHandler events, however.</p>
   *
   * <p>Note that the start/endDTD events will appear within
   * the start/endDocument events from ContentHandler and
   * before the first 
   * {@link basic_ContentHandler#startElement startElement}
   * event.</p>
   *
   * @param name The document type name.
   * @param publicId The declared public identifier for the
   *        external DTD subset, or null if none was declared.
   * @param systemId The declared system identifier for the
   *        external DTD subset, or null if none was declared.
   * @see #endDTD
   * @see #startEntity
   */
  virtual void startDTD(const stringT& name,
                        const stringT& publicId,
                        const stringT& systemId) { } 

  /**
   * Report the end of DTD declarations.
   *
   * <p>This method is intended to report the end of the
   * DOCTYPE declaration; if the document has no DOCTYPE declaration,
   * this method will not be invoked.</p>
   *
   * @see #startDTD
   */
  virtual void endDTD() { }

  /**
   * Report the beginning of some internal and external XML entities.
   *
   * <p>The reporting of parameter entities (including
   * the external DTD subset) is optional, and SAX2 drivers that
   * support LexicalHandler may not support it; you can use the
   * <code
   * >http://xml.org/sax/features/lexical-handler/parameter-entities</code>
   * feature to query or control the reporting of parameter entities.</p>
   *
   * <p>General entities are reported with their regular names,
   * parameter entities have '%' prepended to their names, and 
   * the external DTD subset has the pseudo-entity name "[dtd]".</p>
   *
   * <p>When a SAX2 driver is providing these events, all other 
   * events must be properly nested within start/end entity 
   * events.  There is no additional requirement that events from 
   * {@link basic_DeclHandler DeclHandler} or
   * {@link basic_DTDHandler DTDHandler} be properly ordered.</p>
   *
   * <p>Note that skipped entities will be reported through the
   * {@link basic_ContentHandler#skippedEntity skippedEntity}
   * event, which is part of the ContentHandler interface.</p>
   *
   * <p>Because of the streaming event model that SAX uses, some
   * entity boundaries cannot be reported under any 
   * circumstances:</p>
   *
   * <ul>
   * <li>general entities within attribute values</li>
   * <li>parameter entities within declarations</li>
   * </ul>
   *
   * <p>These will be silently expanded, with no indication of where
   * the original entity boundaries were.</p>
   *
   * <p>Note also that the boundaries of character references (which
   * are not really entities anyway) are not reported.</p>
   *
   * <p>All start/endEntity events must be properly nested.
   *
   * @param name The name of the entity.  If it is a parameter
   *        entity, the name will begin with '%', and if it is the
   *        external DTD subset, it will be "[dtd]".
   * @see #endEntity
   * @see basic_DeclHandler#internalEntityDecl
   * @see basic_DeclHandler#externalEntityDecl 
   */
  virtual void startEntity(const stringT& name) { }
  /**
   * Report the end of an entity.
   *
   * @param name The name of the entity that is ending.
   * @see #startEntity
   */
  virtual void endEntity(const stringT& name) { }

  /**
   * Report the start of a CDATA section.
   *
   * <p>The contents of the CDATA section will be reported through
   * the regular {@link basic_ContentHandler#characters
   * characters} event; this event is intended only to report
   * the boundary.</p>
   *
   * @see #endCDATA
   */
  virtual void startCDATA() { }
  /**
   * Report the end of a CDATA section.
   *
   * @see #startCDATA
   */
  virtual void endCDATA() { }

  /**
   * Report an XML comment anywhere in the document.
   *
   * <p>This callback will be used for comments inside or outside the
   * document element, including comments in the external DTD
   * subset (if read).  Comments in the DTD must be properly
   * nested inside start/endDTD and start/endEntity events (if
   * used).</p>
   *
   * @param ch An holding the comment.
   */
  virtual void comment(const stringT& text) { }

  ////////////////////////////////////////////////////////////
  // DeclHandler
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
  virtual void elementDecl(const stringT& name, const stringT& model) { }
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
   * @param eName The name of the associated element.
   * @param aName The name of the attribute.
   * @param type A string representing the attribute type.
   * @param valueDefault A string representing the attribute default
   *        ("#IMPLIED", "#REQUIRED", or "#FIXED") or empty string if
   *        none of these applies.
   * @param value A string representing the attribute's default value,
   *        or empty string if there is none.
   */
  virtual void attributeDecl(const stringT& elementName,
                             const stringT& attributeName,
                             const stringT& type,
                             const stringT& valueDefault,
                             const stringT& value) { }
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
   * @see basic_DTDHandler#unparsedEntityDecl
   */
  virtual void internalEntityDecl(const stringT& name, const stringT& value) { }
  /**
   * Report a parsed external entity declaration.
   *
   * <p>Only the effective (first) declaration for each entity
   * will be reported.</p>
   *
   * @param name The name of the entity.  If it is a parameter
   *        entity, the name will begin with '%'.
   * @param publicId The declared public identifier of the entity, or
   *        null if none was declared.
   * @param systemId The declared system identifier of the entity.
   * @see #internalEntityDecl
   * @see basic_DTDHandler#unparsedEntityDecl
   */
  virtual void externalEntityDecl(const stringT& name, 
                                  const stringT& publicId,
                                  const stringT& systemId) { }
private:
  basic_DefaultHandler2(const basic_DefaultHandler2&);
  basic_DefaultHandler2& operator=(const basic_DefaultHandler2&);
  bool operator==(const basic_DefaultHandler2&);
}; // class basic_DefaultHandler

typedef basic_DefaultHandler2<std::string> DefaultHandler2;
typedef basic_DefaultHandler2<std::wstring> wDefaultHandler2;

} // namespace SAX

#endif
