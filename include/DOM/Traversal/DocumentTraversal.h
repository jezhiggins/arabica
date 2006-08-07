#ifndef JEZUK_DOM_TRAVERSAL_DOCUMENTRAVERSAL_H
#define JEZUK_DOM_TRAVERSAL_DOCUMENTRAVERSAL_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/Traversal/NodeIterator.h>
#include <DOM/Traversal/TreeWalker.h>
#include <DOM/Traversal/NodeFilter.h>
#include <DOM/Node.h>

namespace DOM
{

namespace Traversal
{

enum whatToShowFlags
{
  SHOW_ALL                    = 0xFFFFFFFF,
  SHOW_ELEMENT                = 0x00000001,
  SHOW_ATTRIBUTE              = 0x00000002,
  SHOW_TEXT                   = 0x00000004,
  SHOW_CDATA_SECTION          = 0x00000008,
  SHOW_ENTITY_REFERENCE       = 0x00000010,
  SHOW_ENTITY                 = 0x00000020,
  SHOW_PROCESSING_INSTRUCTION = 0x00000040,
  SHOW_COMMENT                = 0x00000080,
  SHOW_DOCUMENT               = 0x00000100,
  SHOW_DOCUMENT_TYPE          = 0x00000200,
  SHOW_DOCUMENT_FRAGMENT      = 0x00000400,
  SHOW_NOTATION               = 0x00000800
};

template<class stringT> class NodeIterator;
template<class stringT> class TreeWalker;
template<class stringT> class DocumentTraversal_impl;

template<class stringT>
class DocumentTraversal : protected DOM::Proxy
{
  public:
    DocumentTraversal() : Proxy(0) { }
    explicit DocumentTraversal(DocumentTraversal_impl<stringT>* const impl) : Proxy(impl) { }
    DocumentTraversal(const DocumentTraversal& rhs) : Proxy(rhs) { }
    explicit DocumentTraversal(const DOM::Document<stringT>& rhs) : Proxy(rhs.dImpl()) 
    {
      if(dynamic_cast<DocumentTraversal_impl<stringT>*>(rhs.dImpl()) == 0)
        throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR); 
    } // DocumentTraversal

    virtual ~DocumentTraversal() { }
    bool operator==(const DocumentTraversal& rhs) const { return Proxy::operator==(rhs); } 
    bool operator!=(const DocumentTraversal& rhs) const { return Proxy::operator!=(rhs); }
    bool operator==(int dummy) const { return Proxy::operator==(dummy); }
    bool operator!=(int dummy) const { return Proxy::operator!=(dummy); }

    DocumentTraversal& operator=(const DocumentTraversal& rhs) 
    {
      Proxy::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////
    // DocumentTraversal methods
    NodeIterator<stringT> createNodeIterator(DOM::Node<stringT> root,
                                             int whatToShow,
                                             bool entityRefExpansion)
    {
      return NodeIterator<stringT>(Impl()->createNodeIterator(root, whatToShow, 0, entityRefExpansion));
    } // createNodeIterator

    NodeIterator<stringT> createNodeIterator(DOM::Node<stringT> root,
                                             int whatToShow,
                                             NodeFilter<stringT>& filter,
                                             bool entityRefExpansion)
    {
      return NodeIterator<stringT>(Impl()->createNodeIterator(root, whatToShow, *filter, entityRefExpansion));
    } // createNodeIterator

    TreeWalker<stringT> createTreeWalker(DOM::Node<stringT> root,
                                         int whatToShow,
                                         bool entityRefExpansion)
    {
      return TreeWalker<stringT>(Impl()->createTreeWalker(root, whatToShow, 0, entityRefExpansion));
    } // createTreeWalker

    TreeWalker<stringT> createTreeWalker(DOM::Node<stringT> root,
                                         int whatToShow,
                                         NodeFilter<stringT>& filter,
                                         bool entityRefExpansion)
    {
      return TreeWalker<stringT>(Impl()->createTreeWalker(root, whatToShow, *filter, entityRefExpansion));
    } // createTreeWalker

  private:
    DocumentTraversal_impl<stringT>* Impl() const { return dynamic_cast<DocumentTraversal_impl<stringT>*>(impl()); }
}; // class DocumentTraversal

//////////////////////////////////////////////////////////////
// implementation class
template<class stringT> class NodeIterator_impl;
template<class stringT> class TreeWalker_impl;

template<class stringT>
class DocumentTraversal_impl : virtual public DOM::Impl
{
  public:
    virtual NodeIterator_impl<stringT>* createNodeIterator(DOM::Node<stringT> root,
                                                           int whatToShow,
                                                           NodeFilter<stringT>* filter,
                                                           bool entityRefExpansion) = 0;

    virtual TreeWalker_impl<stringT>* createTreeWalker(DOM::Node<stringT> root,
                                                       int whatToShow,
                                                       NodeFilter<stringT>* filter,
                                                       bool entityRefExpansion) = 0;
}; // class DocumentTraveral_impl

} // namespace Traversal

} // namespace DOM 

#endif
// end of file