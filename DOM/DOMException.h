#ifndef JEZUK_DOM_EXCEPTION_H
#define JEZUK_DOM_EXCEPTION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <stdexcept>

namespace DOM
{

class DOMException : public std::runtime_error
{
public:
  DOMException(int code) : std::runtime_error("DOMException") { }

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

  //virtual const char* what() const throw()
}; // class Entity

} // namespace DOM

#endif

