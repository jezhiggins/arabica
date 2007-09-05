#ifndef ARARBICA_SAXNOTSUPPORTEDEXCEPTION_H
#define ARARBICA_SAXNOTSUPPORTEDEXCEPTION_H

// SAXNotSupportedException.h
// $Id$


#include <SAX/SAXException.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Exception class for an unsupported operation.
 *
 * <p>An XMLReader will throw this exception when it recognizes a
 * feature or property identifier, but cannot perform the requested
 * operation (setting a state or value).  Other SAX2 applications and
 * extensions may use this class for similar purposes.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see SAXNotRecognizedException 
 */
class SAXNotSupportedException : public SAXException
{
public:
  SAXNotSupportedException(const std::string& message) :
    SAXException(message)
  {
  } // SAXNotSupportedException

  SAXNotSupportedException(const SAXNotSupportedException& rhs) :
    SAXException(rhs)
  {
  } // SAXNotSupportedException

  SAXNotSupportedException& operator=(const SAXNotSupportedException& rhs)
  {
    SAXException::operator =(rhs);
    return *this;
  } // operator=

  virtual ~SAXNotSupportedException() throw() { }

}; // class SAXNotSupportedException

} // namespace SAX
} // namespace Arabica

#endif 
// end of file
