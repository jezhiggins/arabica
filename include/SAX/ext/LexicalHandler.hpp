#ifndef ARABICA_LEXICAL_HANDLER_H
#define ARABICA_LEXICAL_HANDLER_H

// LexicalHandler.h 
// $Id$

#include <string>
#include <SAX/ArabicaConfig.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX 
{

/**
 * SAX2 extension handler for lexical events.
 *
 * <p>This is an optional extension handler for SAX2 to provide
 * lexical information about an XML document, such as comments
 * and CDATA section boundaries; XML readers are not required to 
 * support this handler, and it is not part of the core SAX2
 * distribution.</p>
 *
 * <p>The events in the lexical handler apply to the entire document,
 * not just to the document element, and all lexical handler events
 * must appear between the content handler's startDocument and
 * endDocument events.</p>
 *
 * <p>To set the LexicalHandler for an XML reader, use the
 * {@link XMLReader#setProperty setProperty} method
 * with the propertyId "http://xml.org/sax/properties/lexical-handler".
 * If the reader does not support lexical events, it will throw a
 * {@link SAXNotRecognizedException SAXNotRecognizedException}
 * or a
 * {@link SAXNotSupportedException SAXNotSupportedException}
 * when you attempt to register the handler.</p>
 *
 * @since 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 1.0
 * @see XMLReader#setProperty
 * @see SAXNotRecognizedException
 * @see SAXNotSupportedException
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class LexicalHandler
{
public:
  virtual ~LexicalHandler() { }

   /**
   * Report the start of DTD declarations, if any.
   *
   * <p>This method is intended to report the beginning of the
   * DOCTYPE declaration; if the document has no DOCTYPE declaration,
   * this method will not be invoked.</p>
   *
   * <p>All declarations reported through 
   * {@link DTDHandler DTDHandler} or
   * {@link DeclHandler DeclHandler} events must appear
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
   * {@link ContentHandler#startElement startElement}
   * event.</p>
   *
   * @param name The document type name.
   * @param publicId The declared public identifier for the
   *        external DTD subset, or an empty string if none was declared.
   * @param systemId The declared system identifier for the
   *        external DTD subset, or an empty string if none was declared.
   * @see #endDTD
   * @see #startEntity
   */
  virtual void startDTD(const string_type& name,
                        const string_type& publicId,
                        const string_type& systemId) = 0;
  /**
   * Report the end of DTD declarations.
   *
   * <p>This method is intended to report the end of the
   * DOCTYPE declaration; if the document has no DOCTYPE declaration,
   * this method will not be invoked.</p>
   *
   * @see #startDTD
   */
  virtual void endDTD() = 0;

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
   * {@link DeclHandler DeclHandler} or
   * {@link DTDHandler DTDHandler} be properly ordered.</p>
   *
   * <p>Note that skipped entities will be reported through the
   * {@link ContentHandler#skippedEntity skippedEntity}
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
   * @see DeclHandler#internalEntityDecl
   * @see DeclHandler#externalEntityDecl 
   */
  virtual void startEntity(const string_type& name) = 0;
  /**
   * Report the end of an entity.
   *
   * @param name The name of the entity that is ending.
   * @see #startEntity
   */
  virtual void endEntity(const string_type& name) = 0;

  /**
   * Report the start of a CDATA section.
   *
   * <p>The contents of the CDATA section will be reported through
   * the regular {@link ContentHandler#characters
   * characters} event; this event is intended only to report
   * the boundary.</p>
   *
   * @see #endCDATA
   */
  virtual void startCDATA() = 0;
  /**
   * Report the end of a CDATA section.
   *
   * @see #startCDATA
   */
  virtual void endCDATA() = 0;

  /**
   * Report an XML comment anywhere in the document.
   *
   * <p>This callback will be used for comments inside or outside the
   * document element, including comments in the external DTD
   * subset (if read).  Comments in the DTD must be properly
   * nested inside start/endDTD and start/endEntity events (if
   * used).</p>
   *
   * @param text A string holding the comment.
   */
  virtual void comment(const string_type& text) = 0;
}; // class LexicalHandler

} // namespace SAX
} // namespace Arabica

#endif
// end of file
