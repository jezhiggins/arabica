#ifndef ARABICA_HANDLERBASE_H
#define ARABICA_HANDLERBASE_H
// SAX default handler base class.
// $Id$

#include <string>

#include <SAX/ArabicaConfig.hpp>

#include <SAX/EntityResolver.hpp>
#include <SAX/DTDHandler.hpp>
#include <SAX/DocumentHandler.hpp>
#include <SAX/ErrorHandler.hpp>
#include <SAX/Locator.hpp>
#include <SAX/AttributeList.hpp>
#include <SAX/SAXException.hpp>

namespace Arabica
{
namespace SAX
{

/**
  * Default base class for handlers.
  *
  * <p>This class implements the default behaviour for four SAX1
  * interfaces: EntityResolver, DTDHandler, DocumentHandler,
  * and ErrorHandler.  It is now obsolete, but is included in SAX2 to
  * support legacy SAX1 applications.  SAX2 applications should use
  * the {@link DefaultHandler DefaultHandler}
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
  *             {@link DocumentHandler DocumentHandler}
  *             interface.  It has been replaced by the SAX2
  *             {@link DefaultHandler DefaultHandler}
  *             class.
  * @since SAX 1.0
  * @author Jez Higgins, <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
  * @version 1.0
  * @see EntityResolver
  * @see DTDHandler
  * @see DocumentHandler
  * @see ErrorHandler
  */
template<class string_type, class string_adaptor>
class HandlerBase : public EntityResolver<string_type, string_adaptor>, 
					public DTDHandler<string_type, string_adaptor>,
					public DocumentHandler<string_type, string_adaptor>, 
					public ErrorHandler<string_type, string_adaptor>
{
public:
  typedef string_name stringT;
  typedef Locator<string_type, string_adaptor> LocatorT;
  typedef AttributeList<string_type, string_adaptor> AttributeListT;
  typedef InputSource<string_type, string_adaptor> InputSourceT;
  typedef ErrorHandler<string_type, string_adaptor>::SAXParseExceptionT SAXParseExceptionT;

  virtual ~HandlerBase() { }

  //////////////////////////////////////////////////////////////////////
  // Default implementation of the EntityResolver interface.
  //////////////////////////////////////////////////////////////////////
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
   * @return The new input source, or an empty string to require the
   *         default behaviour.
   * @see EntityResolver#resolveEntity
   */
  virtual InputSourceT resolveEntity(const stringT& publicId, 
				     const stringT& systemId)
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
   * @param publicId The notation public identifier, or an empty string if not
   *                 available.
   * @param systemId The notation system identifier.
   * @see DTDHandler#notationDecl
   */
  virtual void notationDecl(const stringT& name,
                            const stringT& publicId,
                            const stringT& systemId) { }

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
   * @see DTDHandler#unparsedEntityDecl
   */
  virtual void unparsedEntityDecl(const stringT& name,
				  const stringT& publicId,
				  const stringT& systemId,
				  const stringT& notationName) { }

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
   * @see DocumentHandler#setDocumentLocator
   * @see Locator
   */
  virtual void setDocumentLocator(const LocatorT& locator) { }

  /**
   * Receive notification of the beginning of the document.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the beginning
   * of a document (such as allocating the root node of a tree or
   * creating an output file).</p>
   *
   * @see DocumentHandler#startDocument
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
   * @see DocumentHandler#endDocument
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
   * @see DocumentHandler#startElement
   */
  virtual void startElement(const stringT& name,
			    const AttributeListT& attributes) { }
  /**
   * Receive notification of the end of an element.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method in a subclass to take specific actions at the end of
   * each element (such as finalising a tree node or writing
   * output to a file).</p>
   *
   * @param name The element type name.
   * @see DocumentHandler#endElement
   */
  virtual void endElement(const stringT& name) { }

  /**
   * Receive notification of character data inside an element.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method to take specific actions for each chunk of character data
   * (such as adding the data to a node or buffer, or printing it to
   * a file).</p>
   *
   * @param ch The characters.
   * @see DocumentHandler#characters
   */
  virtual void characters(const stringT& ch) { }
  /**
   * Receive notification of ignorable whitespace in element content.
   *
   * <p>By default, do nothing.  Application writers may override this
   * method to take specific actions for each chunk of ignorable
   * whitespace (such as adding data to a node or buffer, or printing
   * it to a file).</p>
   *
   * @param ch The whitespace characters.
   * @see DocumentHandler#ignorableWhitespace
   */
  virtual void ignorableWhitespace(const stringT& ch) { }

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
   * @see DocumentHandler#processingInstruction
   */
  virtual void processingInstruction(const stringT& target,
				     const stringT& data) { }

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
   * @see ErrorHandler#warning
   * @see SAXParseException
   */
  virtual void warning(const SAXParseExceptionT& e) { }
  /**
   * Receive notification of a recoverable parser error.
   *
   * <p>The default implementation does nothing.  Application writers
   * may override this method in a subclass to take specific actions
   * for each error, such as inserting the message in a log file or
   * printing it to the console.</p>
   *
   * @param e The warning information encoded as an exception.
   * @see ErrorHandler#warning
   * @see SAXParseException
   */
  virtual void error(const SAXParseExceptionT& e) { }
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
   * @see ErrorHandler#fatalError
   * @see SAXParseException
   */
  virtual void fatalError(const SAXParseExceptionT& e) { throw e; }
}; // class HandlerBase

} // namespace SAX
} // namespace Arabica

#endif
// end of file
