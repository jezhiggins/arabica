#ifndef JEZUK_EVENTS_EXCEPTION_H
#define JEZUK_EVENTS_EXCEPTION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <exception>

namespace Arabica
{
namespace DOM
{

namespace Events
{

class EventException : public std::runtime_error
{
public:
  EventException(CODE code = UNSPECIFED_EVENT_TYPE_ERR) : std::runtime_error("EventException") { }

  enum CODE 
  {
    UNSPECIFED_EVENT_TYPE_ERR
  }; // enum CODE
}; // class EventException

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
