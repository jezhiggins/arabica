#ifndef SAXExceptionH
#define SAXExceptionH

// SAXParseException.h
// $Id$

#include <stdexcept>

namespace SAX
{

/**
 * Encapsulate a general SAX error or warning.
 *
 * <p>This class can contain basic error or warning information from
 * either the XML parser or the application: a parser writer or
 * application writer can subclass it to provide additional
 * functionality.  SAX handlers may throw this exception or
 * any exception subclassed from it.</p>
 *
 * <p>If the parser or application needs to include information about a
 * specific location in an XML document, it should use the
 * {@link basic_SAXParseException SAXParseException} subclass.</p>
 *
 * @since SAX 1.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see basic_SAXParseException
 */
class SAXException : public std::runtime_error
{
public:
  SAXException() : std::runtime_error("Unknown Error")
  {
  } // SAXException

  SAXException(const std::string& message) :
    std::runtime_error(message)
  {
  } // SAXException

  SAXException(const SAXException& rhs) :
    std::runtime_error(rhs.what())
  {
  } // SAXException

  virtual ~SAXException() throw() { }

  SAXException& operator=(const SAXException& rhs)
  {
    std::runtime_error* re = static_cast<std::runtime_error*>(this);
    *re = rhs;
    return *this;
  } // operator=

private:
  bool operator==(const SAXException&);
}; // class SAXException

}; // namespace SAX

#endif // SAXExceptionH
