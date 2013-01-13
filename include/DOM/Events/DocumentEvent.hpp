#ifndef JEZUK_DOM_EVENTS_DOCUMENEVENTS_H
#define JEZUK_DOM_EVENTS_DOCUMENEVENTS_H

/////////////////////////////////////////
// C++ DOM Events Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/Proxy.hpp>

namespace Arabica
{
namespace DOM
{

namespace Events
{

template<class stringT, class string_adaptorT> class Event;
template<class stringT, class string_adaptorT> class DocumentEvent_impl;

template<class stringT, class string_adaptorT>
class DocumentEvent : protected Arabica::DOM::Proxy<DocumentEvent_impl<stringT, string_adaptorT> >
{
  public:
    typedef DocumentEvent_impl<stringT, string_adaptorT> DocumentEvent_implT;
    typedef DOM::Proxy<DocumentEvent_implT> proxy_t;
  
    DocumentEvent() : proxy_t(0) { }
    explicit DocumentEvent(DocumentEvent_implT* const impl) : proxy_t(impl) { }
    DocumentEvent(const DocumentEvent& rhs) : proxy_t(rhs) { }
    explicit DocumentEvent(const DOM::Document<stringT, string_adaptorT>& rhs) : proxy_t(rhs.dImpl())
    {
      if(dynamic_cast<DocumentEvent_implT*>(rhs.dImpl()) == 0)
        throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR); 
    } // DocumentEvent

    virtual ~DocumentEvent() { }
    bool operator==(const DocumentEvent& rhs) const { return proxy_t::operator==(rhs); } 
    bool operator!=(const DocumentEvent& rhs) const { return proxy_t::operator!=(rhs); }
    bool operator==(int dummy) const { return proxy_t::operator==(dummy); }
    bool operator!=(int dummy) const { return proxy_t::operator!=(dummy); }

    DocumentEvent& operator=(const DocumentEvent& rhs) 
    {
      proxy_t::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////
    // DocumentEvent methods
    Event<stringT, string_adaptorT> createEvent(const stringT& eventType)
    {
      return Event<stringT, string_adaptorT>(Impl()->createEvent(eventType));
    } // createTreeWalker

  private:
  DocumentEvent_implT* Impl() const { return dynamic_cast<DocumentEvent_implT*>(Impl()); }
}; // class DocumentEvent

//////////////////////////////////////////////////////////////
// implementation class
template<class stringT, class string_adaptorT> class Event_impl;

template<class stringT, class string_adaptorT>
class DocumentEvent_impl
{
  public:
    virtual Event_impl<stringT, string_adaptorT>* createEvent(const stringT& eventType) = 0;
}; // class DocumentEvent_impl

} // namespace Events

} // namespace DOM 
} // namespace Arabica

#endif
// end of file
