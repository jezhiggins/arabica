#ifndef ParserH
#define ParserH

// Parser.h
// $Id$

#pragma message("Parser is a SAX1 class.  Consider using XMLReader instead.")

#include <string>
#include <saxfwd.h>

namespace SAX 
{

/**
 * Basic interface for SAX (Simple API for XML) parsers.
 *
 * <p>This was the main event supplier interface for SAX1; it has
 * been replaced in SAX2 by {@link basic_XMLReader XMLReader},
 * which includes Namespace support and sophisticated configurability
 * and extensibility.</p>
 *
 * <p>All SAX1 parsers must implement this basic interface: it allows
 * applications to register handlers for different types of events
 * and to initiate a parse from a URI, or a character stream.</p>
 *
 * <p>All SAX1 parsers must also implement a zero-argument constructor
 * (though other constructors are also allowed).</p>
 *
 * <p>SAX1 parsers are reusable but not re-entrant: the application
 * may reuse a parser object (possibly with a different input source)
 * once the first parse has completed successfully, but it may not
 * invoke the parse() methods recursively within a parse.</p>
 *
 * @deprecated This interface has been replaced by the SAX2
 *             {@link basic_XMLReader XMLReader}
 *             interface, which includes Namespace support.
 * @since SAX 1.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see basic_EntityResolver
 * @see basic_DTDHandler
 * @see basic_DocumentHandler
 * @see ErrorHandler
 * @see basic_HandlerBase
 * @see basic_InputSource
 */
template<class string_type>
class basic_Parser
{
public:
  typedef string_name stringT;
  typedef basic_EntityResolver<stringT> EntityResolverT;
  typedef basic_DTDHandler<stringT> DTDHandlerT;
  typedef basic_DocumentHandler<stringT> DocumentHandlerT;
  typedef basic_InputSource<stringT> InputSourceT;

  virtual ~basic_Parser() { }

  //  virtual void setLocale(Locale locale) throws SAXException = 0;
  /**
   * Allow an application to register a custom entity resolver.
   *
   * <p>If the application does not register an entity resolver, the
   * SAX parser will resolve system identifiers and open connections
   * to entities itself (this is the default behaviour implemented in
   * HandlerBase).</p>
   *
   * <p>Applications may register a new or different entity resolver
   * in the middle of a parse, and the SAX parser must begin using
   * the new resolver immediately.</p>
   *
   * @param resolver The object for resolving entities.
   * @see basic_EntityResolver
   * @see basic_HandlerBase
   */
  virtual void setEntityResolver(EntityResolverT& resolver) = 0;
  /**
   * Allow an application to register a DTD event handler.
   *
   * <p>If the application does not register a DTD handler, all DTD
   * events reported by the SAX parser will be silently
   * ignored (this is the default behaviour implemented by
   * HandlerBase).</p>
   *
   * <p>Applications may register a new or different
   * handler in the middle of a parse, and the SAX parser must
   * begin using the new handler immediately.</p>
   *
   * @param handler The DTD handler.
   * @see basic_DTDHandler
   * @see basic_HandlerBase
   */
  virtual void setDTDHandler(DTDHandlerT& handler) = 0;
  /**
   * Allow an application to register a document event handler.
   *
   * <p>If the application does not register a document handler, all
   * document events reported by the SAX parser will be silently
   * ignored (this is the default behaviour implemented by
   * HandlerBase).</p>
   *
   * <p>Applications may register a new or different handler in the
   * middle of a parse, and the SAX parser must begin using the new
   * handler immediately.</p>
   *
   * @param handler The document handler.
   * @see basic_DocumentHandler
   * @see basic_HandlerBase
   */
  virtual void setDocumentHandler(DocumentHandlerT& handler) = 0;
  /**
   * Allow an application to register an error event handler.
   *
   * <p>If the application does not register an error event handler,
   * all error events reported by the SAX parser will be silently
   * ignored, except for fatalError, which will throw a SAXException
   * (this is the default behaviour implemented by HandlerBase).</p>
   *
   * <p>Applications may register a new or different handler in the
   * middle of a parse, and the SAX parser must begin using the new
   * handler immediately.</p>
   *
   * @param handler The error handler.
   * @see ErrorHandler
   * @see basic_SAXException
   * @see basic_HandlerBase
   */
  virtual void setErrorHandler(ErrorHandler& handler) = 0;

  /**
   * Parse an XML document.
   *
   * <p>The application can use this method to instruct the SAX parser
   * to begin parsing an XML document from any valid input
   * source (a character stream, a byte stream, or a URI).</p>
   *
   * <p>Applications may not invoke this method while a parse is in
   * progress (they should create a new Parser instead for each
   * additional XML document).  Once a parse is complete, an
   * application may reuse the same Parser object, possibly with a
   * different input source.</p>
   *
   * @param source The input source for the top-level of the
   *        XML document.
   * @see basic_InputSource
   * @see #setEntityResolver
   * @see #setDTDHandler
   * @see #setDocumentHandler
   * @see #setErrorHandler
   */
  virtual void parse(InputSourceT& source) = 0;
}; // class basic_Parser

typedef basic_Parser<std::string> Parser;
typedef basic_Parser<std::wstring> wParser;

}; // namespace SAX

#endif
// end of file

