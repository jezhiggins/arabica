#ifndef JEZUK_EVENTS_EVENTLISTENER_H
#define JEZUK_EVENTS_EVENTLISTENER_H
////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT> class Event;

template<class stringT>
class EventListener
{
public:
  void handleEvent(Event<stringT>& event) = 0;

protected:
  virtual ~EventListener() { }
}; // class EventListener

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
