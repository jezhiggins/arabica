#ifndef ARABICA_SAXPARSEEXCEPTION_H
#define ARABICA_SAXPARSEEXCEPTION_H

// SAXParseException.h
// $Id$

#include <SAX/SAXException.hpp>
#include <SAX/Locator.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Encapsulate an XML parse error or warning.
 *
 * <p>This exception will include information for locating the error
 * in the original XML document.  Note that although the application
 * will receive a SAXParseException as the argument to the handlers
 * in the {@link ErrorHandler ErrorHandler} interface, 
 * the application is not actually required to throw the exception; 
 * instead, it can simply read the information in it and take a 
 * different action.</p>
 *
 * <p>Since this exception is a subclass of {@link SAXException 
 * SAXException}, it inherits the ability to wrap another exception.</p>
 *
 * @since SAX 1.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see SAXException
 * @see Locator
 * @see ErrorHandler
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class SAXParseException : public SAXException
{
public:
  typedef Locator<string_type, string_adaptor> LocatorT;

  SAXParseException(const std::string& message) :
    SAXException(message),
    publicId_(), 
    systemId_(),
    lineNumber_(-1),
    columnNumber_(-1)
  {
    setMsg();
  } // SAXParseException

  SAXParseException(const std::string& message,
                          const LocatorT& locator) :
    SAXException(message),
    publicId_(locator.getPublicId()), 
    systemId_(locator.getSystemId()),
    lineNumber_(locator.getLineNumber()),
    columnNumber_(locator.getColumnNumber())
  {
    setMsg();
  } // SAXParseException

  SAXParseException(const std::string& message,
	                        const string_type& publicId, 
                          const string_type& systemId,
                          int lineNumber, 
                          int columnNumber) :
    SAXException(message),
    publicId_(publicId), 
    systemId_(systemId),
    lineNumber_(lineNumber),
    columnNumber_(columnNumber)
  {
    setMsg();
  } // SAXParseException

  SAXParseException(const SAXParseException& rhs) :
    SAXException(rhs),
    msg_(rhs.msg_),
    publicId_(rhs.publicId_), 
    systemId_(rhs.systemId_),
    lineNumber_(rhs.lineNumber_),
    columnNumber_(rhs.columnNumber_)
  {
  } // SAXParseException

  SAXParseException& operator=(const SAXParseException& rhs)
  {
    SAXException::operator=(rhs);

    msg_ = rhs.msg_;
    publicId_ = rhs.publicId_;
    systemId_ = rhs.systemId_;
    lineNumber_ = rhs.lineNumber_;
    columnNumber_ = rhs.columnNumber_;

    return *this;
  } // operator=

  virtual ~SAXParseException() throw() { }

  /**
   * Get the public identifier of the entity where the exception occurred.
   *
   * @return A string containing the public identifier, or an empty string
   *         if none is available.
   * @see Locator#getPublicId
   */
  const string_type& getPublicId() const { return publicId_; }
  /**
   * Get the system identifier of the entity where the exception occurred.
   *
   * <p>If the system identifier is a URL, it will be resolved
   * fully.</p>
   *
   * @return A string containing the system identifier, or an empty string
   *         if none is available.
   * @see Locator#getSystemId
   */
  const string_type& getSystemId() const { return systemId_; }
  /**
   * The line number of the end of the text where the exception occurred.
   *
   * @return An integer representing the line number, or -1
   *         if none is available.
   * @see Locator#getLineNumber
   */
  int getLineNumber() const { return lineNumber_; }
  /**
   * The column number of the end of the text where the exception occurred.
   *
   * <p>The first column in a line is position 1.</p>
   *
   * @return An integer representing the column number, or -1
   *         if none is available.
   * @see Locator#getColumnNumber
   */
  int getColumnNumber() const { return columnNumber_; }

  virtual const char* what() const throw()
  {
    return msg_.c_str();
  } // what

private:
  void setMsg()
  {
    std::ostringstream str;
    str << "Parse exception at " << lineNumber_ << "," << columnNumber_ << std::endl;
    str << SAXException::what();
    msg_ = str.str();
  } // setMsg

  std::string msg_;

  string_type publicId_;
  string_type systemId_;
  int lineNumber_;
  int columnNumber_;

  SAXParseException();
}; // class SAXParseException

} // namespace SAX
} // namespace Arabica

#endif 
// end of file
