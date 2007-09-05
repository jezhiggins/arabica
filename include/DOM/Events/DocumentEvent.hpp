#ifndef JEZUK_DOM_EVENTS_DOCUMENEVENTS_H
#define JEZUK_DOM_EVENTS_DOCUMENEVENTS_H

/////////////////////////////////////////
// C++ DOM Events Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/ImplProxy.hpp>

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT> class Event;
template<class stringT> class DocumentEvent_impl;

template<class stringT>
class DocumentEvent : protected DOM::Proxy
{
  public:
    DocumentEvent() : Proxy(0) { }
    explicit DocumentEvent(DocumentEvent_impl<stringT>* const impl) : Proxy(impl) { }
    DocumentEvent(const DocumentEvent& rhs) : Proxy(rhs) { }
    explicit DocumentEvent(const DOM::Document<stringT>& rhs) : Proxy(rhs.dImpl()) 
    {
      if(dynamic_cast<DocumentEvent_impl<stringT>*>(rhs.dImpl()) == 0)
        throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR); 
    } // DocumentEvent

    virtual ~DocumentEvent() { }
    bool operator==(const DocumentEvent& rhs) const { return Proxy::operator==(rhs); } 
    bool operator!=(const DocumentEvent& rhs) const { return Proxy::operator!=(rhs); }
    bool operator==(int dummy) const { return Proxy::operator==(dummy); }
    bool operator!=(int dummy) const { return Proxy::operator!=(dummy); }

    DocumentEvent& operator=(const DocumentEvent& rhs) 
    {
      Proxy::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////
    // DocumentEvent methods
    Event<stringT> createEvent(const stringT& eventType)
    {
      return Event(Impl()->createEvent(const stringT& eventType));
    } // createTreeWalker

  private:
    DocumentEvent_impl<stringT>* Impl() const { return dynamic_cast<DocumentEvent_impl<stringT>*>(impl()); }
}; // class DocumentEvent

//////////////////////////////////////////////////////////////
// implementation class
template<class stringT> class Event_impl;

template<class stringT>
class DocumentEvent_impl : virtual public DOM::Impl
{
  public:
    virtual Event_impl<stringT>* createEvent(const stringT& eventType) = 0;
}; // class DocumentEvent_impl

} // namespace Events

} // namespace DOM 
} // namespace Arabica

#endif
// end of file
