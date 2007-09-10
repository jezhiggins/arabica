#ifndef ARABICA_ERRORHANDLER_H
#define ARABICA_ERRORHANDLER_H

// EntityResolver.h 
// $Id$

#include <string>

#include <SAX/ArabicaConfig.hpp>
#include <Arabica/StringAdaptor.hpp>
#include <SAX/SAXParseException.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Basic interface for SAX error handlers.
 *
 * <p>If a SAX application needs to implement customized error
 * handling, it must implement this interface and then register an
 * instance with the XML reader using the
 * {@link XMLReader#setErrorHandler setErrorHandler}
 * method.  The parser will then report all errors and warnings
 * through this interface.</p>
 *
 * <p><strong>WARNING:</strong> If an application does <em>not</em>
 * register an ErrorHandler, XML parsing errors will go unreported
 * and bizarre behaviour may result.</p>
 *
 * <p>For XML processing errors, a SAX driver must use this interface 
 * instead of throwing an exception: it is up to the application 
 * to decide whether to throw an exception for different types of 
 * errors and warnings.  Note, however, that there is no requirement that 
 * the parser continue to provide useful information after a call to 
 * {@link #fatalError fatalError} (in other words, a SAX driver class 
 * could catch an exception and report a fatalError).</p>
 *
 * @since SAX 1.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see Parser#setErrorHandler
 * @see SAXParseException 
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class ErrorHandler
{
public:
  typedef SAXParseException<string_type, string_adaptor> SAXParseExceptionT;

  virtual ~ErrorHandler() { };

  /**
   * Receive notification of a warning.
   *
   * <p>SAX parsers will use this method to report conditions that
   * are not errors or fatal errors as defined by the XML 1.0
   * recommendation.  The default behaviour is to take no action.</p>
   *
   * <p>The SAX parser must continue to provide normal parsing events
   * after invoking this method: it should still be possible for the
   * application to process the document through to the end.</p>
   *
   * <p>Filters may use this method to report other, non-XML warnings
   * as well.</p>
   *
   * @param exception The warning information encapsulated in a
   *                  SAX parse exception.
   * @see SAXParseException 
   */
  virtual void warning(const SAXParseExceptionT& exception) = 0;
  /**
   * Receive notification of a recoverable error.
   *
   * <p>This corresponds to the definition of "error" in section 1.2
   * of the W3C XML 1.0 Recommendation.  For example, a validating
   * parser would use this callback to report the violation of a
   * validity constraint.  The default behaviour is to take no
   * action.</p>
   *
   * <p>The SAX parser must continue to provide normal parsing events
   * after invoking this method: it should still be possible for the
   * application to process the document through to the end.  If the
   * application cannot do so, then the parser should report a fatal
   * error even if the XML 1.0 recommendation does not require it to
   * do so.</p>
   *
   * <p>Filters may use this method to report other, non-XML errors
   * as well.</p>
   *
   * @param exception The error information encapsulated in a
   *                  SAX parse exception.
   * @see SAXParseException 
   */
  virtual void error(const SAXParseExceptionT& exception) = 0;
  /**
   * Receive notification of a non-recoverable error.
   *
   * <p>This corresponds to the definition of "fatal error" in
   * section 1.2 of the W3C XML 1.0 Recommendation.  For example, a
   * parser would use this callback to report the violation of a
   * well-formedness constraint.</p>
   *
   * <p>The application must assume that the document is unusable
   * after the parser has invoked this method, and should continue
   * (if at all) only for the sake of collecting addition error
   * messages: in fact, SAX parsers are free to stop reporting any
   * other events once this method has been invoked.</p>
   *
   * @param exception The error information encapsulated in a
   *                  SAX parse exception.  
   * @see SAXParseException
   */
  virtual void fatalError(const SAXParseExceptionT& exception) = 0;
}; // class ErrorHandler

} // namespace SAX
} // namespace Arabica

#endif
//end of file
