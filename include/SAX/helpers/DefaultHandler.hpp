#ifndef ARABICA_DEFAULT_HANDLER_H
#define ARABICA_DEFAULT_HANDLER_H

// DefaultHandler.h 
// $Id$

#include <SAX/ArabicaConfig.hpp>
#include <string>
#include <SAX/EntityResolver.hpp>
#include <SAX/DTDHandler.hpp>
#include <SAX/ContentHandler.hpp>
#include <SAX/ErrorHandler.hpp>
#include <SAX/Locator.hpp>
#include <SAX/Attributes.hpp>
#include <SAX/SAXException.hpp>
#include <SAX/ext/DeclHandler.hpp>
#include <SAX/ext/LexicalHandler.hpp>

#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX 
{

/**
 * Default base class for SAX2 event handlers.
 *
 * <p>This class is available as a convenience base class for SAX2
 * applications: it provides default implementations for all of the
 * callbacks in the four core SAX2 handler classes:</p>
 *
 * <ul>
 * <li>{@link EntityResolver EntityResolver}</li>
 * <li>{@link DTDHandler DTDHandler}</li>
 * <li>{@link ContentHandler ContentHandler}</li>
 * <li>{@link ErrorHandler ErrorHandler}</li>
 * </ul>
 *
 * <p>Application writers can extend this class when they need to
 * implement only part of an interface; parser writers can
 * instantiate this class to provide default handlers when the
 * application has not supplied its own.</p>
 *
 * <p>This class replaces the deprecated SAX1
 * {@link HandlerBase HandlerBase} class.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see EntityResolver
 * @see DTDHandler
 * @see ContentHandler
 * @see ErrorHandler
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class DefaultHandler : public EntityResolver<string_type, string_adaptor>, 
					public DTDHandler<string_type, string_adaptor>,
					public ContentHandler<string_type, string_adaptor>, 
					public ErrorHandler<string_type, string_adaptor>, 
					public LexicalHandler<string_type, string_adaptor>,
					public DeclHandler<string_type, string_adaptor>
{
public:
  typedef InputSource<string_type, string_adaptor> InputSourceT;
  typedef Locator<string_type, string_adaptor> LocatorT;
  typedef Attributes<string_type, string_adaptor> AttributesT;
  typedef SAXParseException<string_type, string_adaptor> SAXParseExceptionT;

  DefaultHandler() { }
  virtual ~DefaultHandler() { }

  //////////////////////////////////////////////
  // EntityResolver
  /**
   * Resolve an external entity.
   *
   * <p>Always return a default-constructed <code>InputSourceT</code>, so that
   * the parser will use the system identifier provided in the XML document.
   * This method implements the SAX default behaviour: application writers can
   * override it in a subclass to do special translations such as catalog
   * lookups or URI redirection.</p>
   *
   * @param publicId The public identifer, or an empty string if none is
   *                 available.
   * @param systemId The system identifier provided in the XML 
   *                 document.
   * @return The new input source, (empty to require the
   *         default behaviour).
   * @exception SAXException Any SAX exception.
   * @see EntityResolver#resolveEntity
   */
  virtual InputSourceT resolveEntity(const string_type& /* publicId */, const string_type& /* systemId */)
  {
    return InputSourceT();
  } // resolveEntity

  //////////////////////////////////////////////
  // DTDHandler
  /**
   * Receive notification of a notation declaration.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass if they wish to keep track of the notations
   * declared in a document.</p>
   *
   * @param name The notation name.
   * @param publicId The notation public identifier, or an empty string if not
   *                 available.
   * @param systemId The notation system identifier.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see DTDHandler#notationDecl
   */
  virtual void notationDecl(const string_type& /* name */,
                            const string_type& /* publicId */,
                            const string_type& /* systemId */)
  {
  } // notationDecl

  /**
   * Receive notification of an unparsed entity declaration.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to keep track of the unparsed entities
   * declared in a document.</p>
   *
   * @param name The entity name.
   * @param publicId The entity public identifier, or an empty string if not
   *                 available.
   * @param systemId The entity system identifier.
   * @param notationName The name of the associated notation.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see DTDHandler#unparsedEntityDecl
   */
  virtual void unparsedEntityDecl(const string_type& /* name */,
	                                const string_type& /* publicId */,
                                  const string_type& /* systemId */,
                                  const string_type& /* notationName */)
  {
  } // unparsedEntityDecl

  ////////////////////////////////////////////////////
  // ContentHandler
  /**
   * Receive a Locator object for document events.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass if they wish to store the locator for use
   * with other document events.</p>
   *
   * @param locator A locator for all SAX document events.
   * @see ContentHandler#setDocumentLocator
   * @see Locator
   */
  virtual void setDocumentLocator(const LocatorT& /* locator */) { }

  /**
   * Receive notification of the beginning of the document.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the beginning
   * of a document (such as allocating the root node of a tree or
   * creating an output file).</p>
   *
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#startDocument
   */
  virtual void startDocument() { }
  /**
   * Receive notification of the end of the document.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the end
   * of a document (such as finalising a tree or closing an output
   * file).</p>
   *
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#endDocument
   */
  virtual void endDocument() { }

  /**
   * Receive notification of the start of a Namespace mapping.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the start of
   * each Namespace prefix scope (such as storing the prefix mapping).</p>
   *
   * @param prefix The Namespace prefix being declared.
   * @param uri The Namespace URI mapped to the prefix.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#startPrefixMapping
   */
  virtual void startPrefixMapping(const string_type& /* prefix */, const string_type& /* uri */) { }
  /**
   * Receive notification of the end of a Namespace mapping.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the end of
   * each prefix mapping.</p>
   *
   * @param prefix The Namespace prefix being declared.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#endPrefixMapping
   */
  virtual void endPrefixMapping(const string_type& /* prefix */) { }

  /**
   * Receive notification of the start of an element.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the start of
   * each element (such as allocating a new tree node or writing
   * output to a file).</p>
   *
   * @param namespaceURI The Namespace URI, or the empty string if the element
   *                     has no Namespace URI or if Namespace processing is not
   *                     being performed.
   * @param localName The local name (without prefix), or the empty string if
   *                  Namespace processing is not being performed.
   * @param qName The qualified name (with prefix), or the empty string if
   *              qualified names are not available.
   * @param atts The attributes attached to the element. If there are no
   *             attributes, it shall be an empty Attributes object.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#startElement
   */
  virtual void startElement(const string_type& /* namespaceURI */, const string_type& /* localName */,
                            const string_type& /* qName */, const AttributesT& /* atts */) { }
  /**
   * Receive notification of the end of an element.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the end of
   * each element (such as finalising a tree node or writing
   * output to a file).</p>
   *
   * @param namespaceURI The Namespace URI, or the empty string if the element
   *                     has no Namespace URI or if Namespace processing is not
   *                     being performed.
   * @param localName The local name (without prefix), or the empty string if
   *                  Namespace processing is not being performed.
   * @param qName The qualified name (with prefix), or the empty string if
   *              qualified names are not available.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#endElement
   */
  virtual void endElement(const string_type& /* namespaceURI */, const string_type& /* localName */,
                          const string_type& /* qName */) { }

  /**
   * Receive notification of character data inside an element.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method to take specific actions for each chunk of character data
   * (such as adding the data to a node or buffer, or printing it to
   * a file).</p>
   *
   * @param ch The characters.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#characters
   */
  virtual void characters(const string_type& /* ch */) { }
  /**
   * Receive notification of ignorable whitespace in element content.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method to take specific actions for each chunk of ignorable
   * whitespace (such as adding data to a node or buffer, or printing
   * it to a file).</p>
   *
   * @param ch The whitespace characters.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#ignorableWhitespace
   */
  virtual void ignorableWhitespace(const string_type& /* ch */) { }

  /**
   * Receive notification of a processing instruction.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions for each
   * processing instruction, such as setting status variables or
   * invoking other methods.</p>
   *
   * @param target The processing instruction target.
   * @param data The processing instruction data, or an empty string if
   *             none is supplied.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#processingInstruction
   */
  virtual void processingInstruction(const string_type& /* target */, const string_type& /* data */) { }

  /**
   * Receive notification of a skipped entity.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions for each
   * processing instruction, such as setting status variables or
   * invoking other methods.</p>
   *
   * @param name The name of the skipped entity.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ContentHandler#processingInstruction
   */
  virtual void skippedEntity(const string_type& /* name */) { }

  /////////////////////////////////////////////////////
  // ErrorHandler
  /**
   * Receive notification of a parser warning.
   *
   * <p>The default implementation does nothing.  Application writers
   * may override this method in a subclass to take specific actions
   * for each warning, such as inserting the message in a log file or
   * printing it to the console.</p>
   *
   * @param e The warning information encoded as an exception.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ErrorHandler#warning
   * @see SAXParseException
   */
  virtual void warning(const SAXParseExceptionT& /* e */) { }
  /**
   * Receive notification of a recoverable parser error.
   *
   * <p>The default implementation does nothing.  Application writers
   * may override this method in a subclass to take specific actions
   * for each error, such as inserting the message in a log file or
   * printing it to the console.</p>
   *
   * @param e The warning information encoded as an exception.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ErrorHandler#error
   * @see SAXParseException
   */
  virtual void error(const SAXParseExceptionT& /* e */) { }
  /**
   * Report a fatal XML parsing error.
   *
   * <p>The default implementation throws a SAXParseException.
   * Application writers may override this method in a subclass if
   * they need to take specific actions for each fatal error (such as
   * collecting all of the errors into a single report): in any case,
   * the application must stop all regular processing when this
   * method is invoked, since the document is no longer reliable, and
   * the parser may no longer report parsing events.</p>
   *
   * @param e The error information encoded as an exception.
   * @exception SAXException Any SAX exception, possibly
   *            wrapping another exception.
   * @see ErrorHandler#fatalError
   * @see SAXParseException
   */
  virtual void fatalError(const SAXParseExceptionT& e) 
  {  
    throw SAXParseExceptionT(e); 
    // VS.NET refuses throw e; saying the copy constructor is inaccessible
    // GCC likes throw e; 
    // one of them, I presume, is wrong
  } // fatalError

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
  virtual void startDTD(const string_type& /*name*/,
                        const string_type& /*publicId*/,
                        const string_type& /*systemId*/) { } 

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
  virtual void startEntity(const string_type& /*name*/) { }
  /**
   * Report the end of an entity.
   *
   * @param name The name of the entity that is ending.
   * @see #startEntity
   */
  virtual void endEntity(const string_type& /*name*/) { }

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
   * @param text A string holding the comment.
   */
  virtual void comment(const string_type& /*text*/) { }

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
  virtual void elementDecl(const string_type& /*name*/, const string_type& /*model*/) { }
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
  virtual void attributeDecl(const string_type& /*elementName*/,
                             const string_type& /*attributeName*/,
                             const string_type& /*type*/,
                             const string_type& /*valueDefault*/,
                             const string_type& /*value*/) { }
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
  virtual void internalEntityDecl(const string_type& /*name*/, const string_type& /*value*/) { }
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
  virtual void externalEntityDecl(const string_type& /*name*/,
                                  const string_type& /*publicId*/,
                                  const string_type& /*systemId*/) { }
private:
  DefaultHandler(const DefaultHandler&);
  DefaultHandler& operator=(const DefaultHandler&);
  bool operator==(const DefaultHandler&);
}; // class DefaultHandler

} // namespace SAX
} // namespace Arabica

#endif
