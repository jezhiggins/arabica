#ifndef ARABICA_DEFAULT_HANDLER_H
#define ARABICA_DEFAULT_HANDLER_H

// DefaultHandler.h 
// $Id$

#include <SAX/ArabicaConfig.h>
#include <string>
#include <SAX/EntityResolver.h>
#include <SAX/DTDHandler.h>
#include <SAX/ContentHandler.h>
#include <SAX/ErrorHandler.h>
#include <SAX/Locator.h>
#include <SAX/Attributes.h>
#include <SAX/SAXException.h>

namespace SAX {

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
					public basic_ErrorHandler<string_type>
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

#endif
