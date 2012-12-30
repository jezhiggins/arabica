#ifndef JEZUK_DOM_SimpleDOM_EVENTTARGET_IMPL_H
#define JEZUK_DOM_SimpleDOM_EVENTTARGET_IMPL_H

////////////////////////////
// C++ EventTarget implementation
////////////////////////////

#include <DOM/Node.hpp>
#include <DOM/Events/EventTarget.hpp>
#include <DOM/DOMException.hpp>
#include <XML/XMLCharacterClasses.hpp>
#include <deque>
#include <algorithm>
#include <map>

//#include <iostream>

namespace Arabica
{
namespace DOM
{
namespace Events
{

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class DocumentImpl;

template<class stringT, class string_adaptorT>
class EventTargetImpl : virtual public DOM::Events::EventTarget_impl<stringT, string_adaptorT>
{
  public:
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::Text_impl<stringT, string_adaptorT> DOMText_implT;
    typedef DOM::Document_impl<stringT, string_adaptorT> DOMDocument_implT;
    typedef DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;
    typedef DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;
    typedef DOM::Events::Event<stringT, string_adaptorT> EventT;
    typedef DOM::Events::EventTarget<stringT, string_adaptorT> EventTargetT;
    typedef DOM::Events::EventTargetImpl<stringT, string_adaptorT> EventTargetImplT;
    typedef DOM::Events::EventListener<stringT, string_adaptorT> EventListenerT;

    EventTargetImpl()
    {
        //std::cout << std::endl << "born " << this << std::endl;
    } // EventTargetImpl
    
    virtual ~EventTargetImpl() 
    { 
        //std::cout << std::endl << "die  " << this << std::endl;
    }

    ///////////////////////////////////////////////////////
    // EventTarget methods
    virtual void addEventListener(const stringT type,
                                  EventListenerT& listener,
                                  bool useCapture)
    {
      typedef typename std::multimap<stringT, EventListenerT*>::iterator iterator;
      if (useCapture) {
        std::pair<iterator, iterator> range = eventCapturers_.equal_range(type);
        for (iterator it = range.first; it != range.second; ++it) {
          if (it->second == &listener)
            return;
        }
        eventCapturers_.insert(std::make_pair(type, &listener));
      } else {
        std::pair<iterator, iterator> range = eventListeners_.equal_range(type);
        for (iterator it = range.first; it != range.second; ++it) {
          if (it->second == &listener)
            return;
        }
        eventListeners_.insert(std::make_pair(type, &listener));
      }
    }

    virtual void removeEventListener(const stringT type,
                                     EventListenerT& listener,
                                     bool useCapture)
    {
      typedef typename std::multimap<stringT, EventListenerT*>::iterator iterator;
      if (useCapture) {
        std::pair<iterator, iterator> range = eventCapturers_.equal_range(type);
        for (iterator it = range.first; it != range.second; ++it) {
          if (it->second == &listener)
            eventCapturers_.erase(it);
          return;
        }
      } else {
        std::pair<iterator, iterator> range = eventListeners_.equal_range(type);
        for (iterator it = range.first; it != range.second; ++it) {
          if (it->second == &listener)
            eventListeners_.erase(it);
            return;
        }
      }
    }
  
    virtual bool dispatchEvent(EventT& event)
    {
      typedef typename std::multimap<stringT, EventListenerT*>::iterator eventListenerIterator;

      std::list<EventTargetT> eventTargetChain;
      DOMNode_implT* curr = dynamic_cast<DOMNode_implT*>(this);
      eventTargetChain.push_front(EventTargetT(curr));
      while((curr = curr->getParentNode())) {
        eventTargetChain.push_front(EventTargetT(curr));
      }
      
      // capturing
      typename std::list<EventTargetT>::iterator it = eventTargetChain.begin();
      while(it != eventTargetChain.end()) {
        EventTargetImplT* nodeImpl = dynamic_cast<EventTargetImplT*>(it->Impl());
        if (nodeImpl != NULL) {
          std::pair<eventListenerIterator, eventListenerIterator> range = nodeImpl->eventCapturers_.equal_range(event.getType());
          for (eventListenerIterator it = range.first; it != range.second; ++it) {
            it->second->handleEvent(event);
          }
        }
        ++it;
      }

      // bubbling
      typename std::list<EventTargetT>::reverse_iterator rit = eventTargetChain.rbegin();
      while(rit != eventTargetChain.rend()) {
        EventTargetImplT* nodeImpl = dynamic_cast<EventTargetImplT*>(rit->Impl());
        if (nodeImpl != NULL) {
          std::pair<eventListenerIterator, eventListenerIterator> range = nodeImpl->eventListeners_.equal_range(event.getType());
          for (eventListenerIterator rit = range.first; rit != range.second; ++rit) {
            rit->second->handleEvent(event);
          }
        }
        ++rit;
      }

      return true;
    }

  protected:
    std::multimap<stringT, EventListenerT*> eventListeners_;
	  std::multimap<stringT, EventListenerT*> eventCapturers_;
}; // class EventTargetImpl

} // namespace DOM
} // namespace Events
} // namespace Arabica

#endif // JEZUK_DOM_SimpleDOM_EVENTTARGET_H
// end of file
