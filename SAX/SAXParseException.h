#ifndef ARARBICA_SAXPARSEEXCEPTION_H
#define ARARBICA_SAXPARSEEXCEPTION_H

// SAXParseException.h
// $Id$

#include <SAX/SAXException.h>
#include <SAX/Locator.h>
#include <sstream>
#include <Utils/convertstream.h>

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
 * @see basic_ErrorHandler
 */
template<class string_type>
class basic_SAXParseException : public SAXException
{
public:
  typedef string_type stringT;
  typedef basic_Locator<stringT> LocatorT;

  basic_SAXParseException(const std::string& message) :
    SAXException(message),
    publicId_(), 
    systemId_(),
    lineNumber_(-1),
    columnNumber_(-1)
  {
    setMsg();
  } // basic_SAXParseException

  basic_SAXParseException(const std::string& message,
                          const LocatorT& locator) :
    SAXException(message),
    publicId_(locator.getPublicId()), 
    systemId_(locator.getSystemId()),
    lineNumber_(locator.getLineNumber()),
    columnNumber_(locator.getColumnNumber())
  {
    setMsg();
  } // basic_SAXParseException

  basic_SAXParseException(const std::string& message,
	                        const stringT& publicId, 
                          const stringT& systemId,
                          int lineNumber, 
                          int columnNumber) :
    SAXException(message),
    publicId_(publicId), 
    systemId_(systemId),
    lineNumber_(lineNumber),
    columnNumber_(columnNumber)
  {
    setMsg();
  } // basic_SAXParseException

  basic_SAXParseException(const basic_SAXParseException& rhs) :
    SAXException(rhs),
    publicId_(rhs.publicId_), 
    systemId_(rhs.systemId_),
    lineNumber_(rhs.lineNumber_),
    columnNumber_(rhs.columnNumber_)
  {
    setMsg();
  } // basic_SAXParseException

  basic_SAXParseException& operator=(const basic_SAXParseException& rhs)
  {
    SAXException::operator =(rhs);

    publicId_ = rhs.publicId_;
    systemId_ = rhs.systemId_;
    lineNumber_ = rhs.lineNumber_;
    columnNumber_ = rhs.columnNumber_;

    setMsg();
  } // operator=

  virtual ~basic_SAXParseException() throw() { }

  /**
   * Get the public identifier of the entity where the exception occurred.
   *
   * @return A string containing the public identifier, or an empty string
   *         if none is available.
   * @see basic_Locator#getPublicId
   */
  const stringT& getPublicId() const { return publicId_; }
  /**
   * Get the system identifier of the entity where the exception occurred.
   *
   * <p>If the system identifier is a URL, it will be resolved
   * fully.</p>
   *
   * @return A string containing the system identifier, or an empty string
   *         if none is available.
   * @see basic_Locator#getSystemId
   */
  const stringT& getSystemId() const { return systemId_; }
  /**
   * The line number of the end of the text where the exception occurred.
   *
   * @return An integer representing the line number, or -1
   *         if none is available.
   * @see basic_Locator#getLineNumber
   */
  int getLineNumber() const { return lineNumber_; }
  /**
   * The column number of the end of the text where the exception occurred.
   *
   * <p>The first column in a line is position 1.</p>
   *
   * @return An integer representing the column number, or -1
   *         if none is available.
   * @see basic_Locator#getColumnNumber
   */
  int getColumnNumber() const { return columnNumber_; }

  virtual const char* what() const throw()
  {
    return msg.c_str();
  } // what

private:
  void setMsg()
  {
    std::ostringstream str;
    str << "Parse exception at " << lineNumber_ << "," << columnNumber_ << std::endl;
    str << SAXException::what();
    msg = str.str();
  } // setMsg

  std::string msg;

  stringT publicId_;
  stringT systemId_;
  int lineNumber_;
  int columnNumber_;

  basic_SAXParseException();
}; // class basic_SAXParseException

typedef basic_SAXParseException<std::string> SAXParseException;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_SAXParseException<std::wstring> wSAXParseException;
#endif 

}; // namespace SAX

#endif 
// end of file
