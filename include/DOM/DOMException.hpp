#ifndef JEZUK_DOM_EXCEPTION_H
#define JEZUK_DOM_EXCEPTION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <stdexcept>

namespace Arabica
{
namespace DOM
{

class DOMException : public std::runtime_error
{
public:
  enum CODE 
  {
    INDEX_SIZE_ERR,
    DOMSTRING_SIZE_ERR,
    HIERARCHY_REQUEST_ERR,
    WRONG_DOCUMENT_ERR,
    INVALID_CHARACTER_ERR,
    NO_DATA_ALLOWED_ERR,
    NO_MODIFICATION_ALLOWED_ERR,
    NOT_FOUND_ERR,
    NOT_SUPPORTED_ERR,
    INUSE_ATTRIBUTE_ERR,
    INVALID_STATE_ERR,
    SYNTAX_ERR,
    INVALID_MODIFICATION_ERR,
    NAMESPACE_ERR,
    INVALID_ACCESS_ERR
  }; // enum CODE

  DOMException(CODE code) : std::runtime_error("DOMException"), code_(code) { }

  CODE code() const { return code_; }

  virtual const char* what() const throw()
  {
    switch(code_)
    {
      case INDEX_SIZE_ERR:
        return "Index size error";
      case DOMSTRING_SIZE_ERR:
        return "DOMString size error";
      case HIERARCHY_REQUEST_ERR:
        return "Hierarchy request error";
      case WRONG_DOCUMENT_ERR:
        return "Wrong Document error";
      case INVALID_CHARACTER_ERR:
        return "Invalid Character error";
      case NO_DATA_ALLOWED_ERR:
        return "No data allowed error";
      case NO_MODIFICATION_ALLOWED_ERR:
        return "No modification allowed error";
      case NOT_FOUND_ERR:
        return "Not found error";
      case NOT_SUPPORTED_ERR:
        return "Not supported error";
      case INUSE_ATTRIBUTE_ERR:
        return "Attribute inuse error";
      case INVALID_STATE_ERR:
        return "Invalid state";
      case SYNTAX_ERR:
        return "Syntax error";
      case INVALID_MODIFICATION_ERR:
        return "Invalid modification error";
      case NAMESPACE_ERR:
        return "Namespace error";
      case INVALID_ACCESS_ERR:
        return "Invalid access error";
    } // switch(code_)

    return "DOM error";
  } // what

private:
  CODE code_;
}; // class DOMException

} // namespace DOM
} // namespace Arabica

#endif

