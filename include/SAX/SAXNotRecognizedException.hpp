#ifndef ARABICA_SAXNOTRECOGNIZEDEXCEPTION_H
#define ARABICA_SAXNOTRECOGNIZEDEXCEPTION_H

// SAXNotRecognizedException.h
// $Id$


#include <SAX/SAXException.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Exception class for an unrecognized identifier.
 *
 * <p>An XMLReader will throw this exception when it finds an
 * unrecognized feature or property identifier; SAX applications and
 * extensions may use this class for other, similar purposes.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see SAXNotSupportedException
 */
class SAXNotRecognizedException : public SAXException
{
public:
  SAXNotRecognizedException(const std::string& message) :
    SAXException(message)
  {
  } // SAXNotRecognizedException

  SAXNotRecognizedException(const SAXNotRecognizedException& rhs) :
    SAXException(rhs)
  {
  } // SAXNotRecognizedException

  SAXNotRecognizedException& operator=(const SAXNotRecognizedException& rhs)
  {
    SAXException::operator =(rhs);
    return *this;
  } // operator=

  virtual ~SAXNotRecognizedException() throw() { }
}; // class SAXNotRecognizedException

} // namespace SAX
} // namespace Arabica

#endif 
// end of file
