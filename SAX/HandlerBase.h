#ifndef HandlerBaseH
#define HandlerBaseH
// SAX default handler base class.
// $Id$

#include <string>
#include "EntityResolver.h"
#include "DTDHandler.h"
#include "DocumentHandler.h"
#include "ErrorHandler.h"
#include "Locator.h"
#include "AttributeList.h"
#include "SAXException.h"

namespace SAX
{

/**
  * Default base class for handlers.
  *
  * <p>This class implements the default behaviour for four SAX1
  * interfaces: EntityResolver, DTDHandler, DocumentHandler,
  * and ErrorHandler.  It is now obsolete, but is included in SAX2 to
  * support legacy SAX1 applications.  SAX2 applications should use
  * the {@link basic_DefaultHandler DefaultHandler}
  * class instead.</p>
  *
  * <p>Application writers can extend this class when they need to
  * implement only part of an interface; parser writers can
  * instantiate this class to provide default handlers when the
  * application has not supplied its own.</p>
  *
  * <p>Note that the use of this class is optional.</p>
  *
  * @deprecated This class works with the deprecated
  *             {@link basic_DocumentHandler DocumentHandler}
  *             interface.  It has been replaced by the SAX2
  *             {@link basic_DefaultHandler DefaultHandler}
  *             class.
  * @since SAX 1.0
  * @author Jez Higgins, <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
  * @version 1.0
  * @see basic_EntityResolver
  * @see basic_DTDHandler
  * @see basic_DocumentHandler
  * @see basic_ErrorHandler
  */
template<class string_type>
class basic_HandlerBase : public basic_EntityResolver<string_type>, 
					public basic_DTDHandler<string_type>,
					public basic_DocumentHandler<string_type>, 
					public ErrorHandler
{
public:
  typedef string_name stringT;
  typedef basic_Locator<stringT> LocatorT;
  typedef basic_AttributeList<stringT> AttributeListT;
  typedef basic_InputSource<stringT> InputSourceT;

  virtual ~basic_HandlerBase() { }

  //////////////////////////////////////////////////////////////////////
  // Default implementation of the EntityResolver interface.
  //////////////////////////////////////////////////////////////////////
  /**
   * Resolve an external entity.
   *
   * <p>Always return null, so that the parser will use the system
   * identifier provided in the XML document.  This method implements
   * the SAX default behaviour: application writers can override it
   * in a subclass to do special translations such as catalog lookups
   * or URI redirection.</p>
   *
   * @param publicId The public identifer, or null if none is
   *                 available.
   * @param systemId The system identifier provided in the XML 
   *                 document.
   * @return The new input source, or null to require the
   *         default behaviour.
   * @see basic_EntityResolver#resolveEntity
   */
  virtual InputSourceT resolveEntity(const stringT&, const stringT&)
  {
    return InputSourceT();
  } // resolverEntity

  //////////////////////////////////////////////////////////////////////
  // Default implementation of DTDHandler interface.
  //////////////////////////////////////////////////////////////////////
  /**
   * Receive notification of a notation declaration.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass if they wish to keep track of the notations
   * declared in a document.</p>
   *
   * @param name The notation name.
   * @param publicId The notation public identifier, or null if not
   *                 available.
   * @param systemId The notation system identifier.
   * @see basic_DTDHandler#notationDecl
   */
  virtual void notationDecl(const stringT&,
			                      const stringT&,
                            const stringT&) { }

  /**
   * Receive notification of an unparsed entity declaration.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to keep track of the unparsed entities
   * declared in a document.</p>
   *
   * @param name The entity name.
   * @param publicId The entity public identifier, or null if not
   *                 available.
   * @param systemId The entity system identifier.
   * @param notationName The name of the associated notation.
   * @see basic_DTDHandler#unparsedEntityDecl
   */
  virtual void unparsedEntityDecl(const stringT&,
					              const stringT&,
					              const stringT&,
                        const stringT&) { }

  //////////////////////////////////////////////////////////////////////
  // Default implementation of DocumentHandler interface.
  //////////////////////////////////////////////////////////////////////
  /**
   * Receive a Locator object for document events.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass if they wish to store the locator for use
   * with other document events.</p>
   *
   * @param locator A locator for all SAX document events.
   * @see basic_DocumentHandler#setDocumentLocator
   * @see basic_Locator
   */
  virtual void setDocumentLocator(const LocatorT&) { }

  /**
   * Receive notification of the beginning of the document.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the beginning
   * of a document (such as allocating the root node of a tree or
   * creating an output file).</p>
   *
   * @see basic_DocumentHandler#startDocument
   */
  virtual void startDocument() { }
  /**
   * Receive notification of the end of the document.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the beginning
   * of a document (such as finalising a tree or closing an output
   * file).</p>
   *
   * @see basic_DocumentHandler#endDocument
   */
  virtual void endDocument() { }

  /**
   * Receive notification of the start of an element.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the start of
   * each element (such as allocating a new tree node or writing
   * output to a file).</p>
   *
   * @param name The element type name.
   * @param attributes The specified or defaulted attributes.
   * @see basic_DocumentHandler#startElement
   */
  virtual void startElement(const stringT&, const AttributeListT&) { }
  /**
   * Receive notification of the end of an element.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the end of
   * each element (such as finalising a tree node or writing
   * output to a file).</p>
   *
   * @param name The element type name.
   * @param attributes The specified or defaulted attributes.
   * @see basic_DocumentHandler#endElement
   */
  virtual void endElement(const stringT&) { }

  /**
   * Receive notification of character data inside an element.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method to take specific actions for each chunk of character data
   * (such as adding the data to a node or buffer, or printing it to
   * a file).</p>
   *
   * @param ch The characters.
   * @see basic_DocumentHandler#characters
   */
  virtual void characters(const stringT&) { }
  /**
   * Receive notification of ignorable whitespace in element content.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method to take specific actions for each chunk of ignorable
   * whitespace (such as adding data to a node or buffer, or printing
   * it to a file).</p>
   *
   * @param ch The whitespace characters.
   * @see basic_DocumentHandler#ignorableWhitespace
   */
  virtual void ignorableWhitespace(const stringT&) { }

  /**
   * Receive notification of a processing instruction.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions for each
   * processing instruction, such as setting status variables or
   * invoking other methods.</p>
   *
   * @param target The processing instruction target.
   * @param data The processing instruction data, or null if
   *             none is supplied.
   * @see basic_DocumentHandler#processingInstruction
   */
  virtual void processingInstruction(const stringT&, const stringT&) { }

  //////////////////////////////////////////////////////////////////////
  // Default implementation of the ErrorHandler interface.
  //////////////////////////////////////////////////////////////////////
  /**
   * Receive notification of a parser warning.
   *
   * <p>The default implementation does nothing.  Application writers
   * may override this method in a subclass to take specific actions
   * for each warning, such as inserting the message in a log file or
   * printing it to the console.</p>
   *
   * @param e The warning information encoded as an exception.
   * @see basic_ErrorHandler#warning
   * @see basic_SAXParseException
   */
  virtual void warning(const SAXException&) { }
  /**
   * Receive notification of a recoverable parser error.
   *
   * <p>The default implementation does nothing.  Application writers
   * may override this method in a subclass to take specific actions
   * for each error, such as inserting the message in a log file or
   * printing it to the console.</p>
   *
   * @param e The warning information encoded as an exception.
   * @see basic_ErrorHandler#warning
   * @see basic_SAXParseException
   */
  virtual void error(const SAXException&) { }
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
   * @see basic_ErrorHandler#fatalError
   * @see basic_SAXParseException
   */
  virtual void fatalError(const SAXException& e) { throw e; }
}; // class HandlerBase

typedef basic_HandlerBase<std::string> HandlerBase;
typedef basic_HandlerBase<std::wstring> wHandlerBase;

}; // namespace SAX

#endif
// end of file
