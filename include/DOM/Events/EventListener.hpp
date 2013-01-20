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

template<class stringT, class string_adaptorT> class Event;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class EventListener
{
public:
  virtual void handleEvent(Event<stringT, string_adaptorT>& event) = 0;

protected:
  virtual ~EventListener() { }
}; // class EventListener

} // namespace Events

} // namespace DOM
} // namespace Arabica

#endif
