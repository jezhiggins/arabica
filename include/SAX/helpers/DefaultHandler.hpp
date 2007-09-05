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
 * <li>{@link basic_EntityResolver EntityResolver}</li>
 * <li>{@link basic_DTDHandler DTDHandler}</li>
 * <li>{@link basic_ContentHandler ContentHandler}</li>
 * <li>{@link ErrorHandler ErrorHandler}</li>
 * </ul>
 *
 * <p>Application writers can extend this class when they need to
 * implement only part of an interface; parser writers can
 * instantiate this class to provide default handlers when the
 * application has not supplied its own.</p>
 *
 * <p>This class replaces the deprecated SAX1
 * {@link basic_HandlerBase HandlerBase} class.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see basic_EntityResolver
 * @see basic_DTDHandler
 * @see basic_ContentHandler
 * @see basic_ErrorHandler
 */
template<class string_type>
class basic_DefaultHandler : public basic_EntityResolver<string_type>, 
					public basic_DTDHandler<string_type>,
					public basic_ContentHandler<string_type>, 
					public basic_ErrorHandler<string_type>, 
					public basic_LexicalHandler<string_type>,
					public basic_DeclHandler<string_type>
{
public:
  typedef string_type stringT;
  typedef basic_InputSource<stringT> InputSourceT;
  typedef basic_Locator<stringT> LocatorT;
  typedef basic_Attributes<stringT> AttributesT;
  typedef basic_SAXParseException<stringT> SAXParseExceptionT;

  basic_DefaultHandler() { }
  virtual ~basic_DefaultHandler() { }

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
   * @see basic_EntityResolver#resolveEntity
   */
  virtual InputSourceT resolveEntity(const stringT& /* publicId */, const stringT& /* systemId */)
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
   * @see basic_DTDHandler#notationDecl
   */
  virtual void notationDecl(const stringT& /* name */,
                            const stringT& /* publicId */,
                            const stringT& /* systemId */)
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
   * @see basic_DTDHandler#unparsedEntityDecl
   */
  virtual void unparsedEntityDecl(const stringT& /* name */,
	                                const stringT& /* publicId */,
                                  const stringT& /* systemId */,
                                  const stringT& /* notationName */)
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
   * @see basic_ContentHandler#setDocumentLocator
   * @see basic_Locator
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
   * @see basic_ContentHandler#startDocument
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
   * @see basic_ContentHandler#endDocument
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
   * @see basic_ContentHandler#startPrefixMapping
   */
  virtual void startPrefixMapping(const stringT& /* prefix */, const stringT& /* uri */) { }
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
   * @see basic_ContentHandler#endPrefixMapping
   */
  virtual void endPrefixMapping(const stringT& /* prefix */) { }

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
   * @see basic_ContentHandler#startElement
   */
  virtual void startElement(const stringT& /* namespaceURI */, const stringT& /* localName */,
                            const stringT& /* qName */, const AttributesT& /* atts */) { }
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
   * @see basic_ContentHandler#endElement
   */
  virtual void endElement(const stringT& /* namespaceURI */, const stringT& /* localName */,
                          const stringT& /* qName */) { }

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
   * @see basic_ContentHandler#characters
   */
  virtual void characters(const stringT& /* ch */) { }
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
   * @see basic_ContentHandler#ignorableWhitespace
   */
  virtual void ignorableWhitespace(const stringT& /* ch */) { }

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
   * @see basic_ContentHandler#processingInstruction
   */
  virtual void processingInstruction(const stringT& /* target */, const stringT& /* data */) { }

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
   * @see basic_ContentHandler#processingInstruction
   */
  virtual void skippedEntity(const stringT& /* name */) { }

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
   * @see basic_ErrorHandler#warning
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
   * @see basic_ErrorHandler#error
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
   * @see basic_ErrorHandler#fatalError
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
   *        external DTD subset, or an empty string if none was declared.
   * @param systemId The declared system identifier for the
   *        external DTD subset, or an empty string if none was declared.
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
   * @param text A string holding the comment.
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
   * @param elementName The name of the associated element.
   * @param attributeName The name of the attribute.
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
   *        an empty string if none was declared.
   * @param systemId The declared system identifier of the entity.
   * @see #internalEntityDecl
   * @see basic_DTDHandler#unparsedEntityDecl
   */
  virtual void externalEntityDecl(const stringT& name, 
                                  const stringT& publicId,
                                  const stringT& systemId) { }
private:
  basic_DefaultHandler(const basic_DefaultHandler&);
  basic_DefaultHandler& operator=(const basic_DefaultHandler&);
  bool operator==(const basic_DefaultHandler&);
}; // class basic_DefaultHandler

typedef basic_DefaultHandler<std::string> DefaultHandler;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_DefaultHandler<std::wstring> wDefaultHandler;
#endif 

} // namespace SAX
} // namespace Arabica

#endif
