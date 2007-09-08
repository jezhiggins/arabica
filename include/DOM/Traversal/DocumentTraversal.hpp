#ifndef JEZUK_DOM_TRAVERSAL_DOCUMENTRAVERSAL_H
#define JEZUK_DOM_TRAVERSAL_DOCUMENTRAVERSAL_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id$
/////////////////////////////////////////

#include <DOM/Traversal/NodeIterator.hpp>
#include <DOM/Traversal/TreeWalker.hpp>
#include <DOM/Traversal/NodeFilter.hpp>
#include <DOM/Node.hpp>
#include <DOM/Traversal/TraversalImpl.hpp>

namespace Arabica
{
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

template<class stringT, class string_adaptorT> class NodeIterator;
template<class stringT, class string_adaptorT> class TreeWalker;
template<class stringT, class string_adaptorT> class DocumentTraversal_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class DocumentTraversal : protected DOM::Proxy<DocumentTraversal_impl<stringT, string_adaptorT> >
{
  public:
    typedef NodeFilter<stringT, string_adaptorT> NodeFilterT;
    typedef TreeWalker<stringT, string_adaptorT> TreeWalkerT;
    typedef NodeIterator<stringT, string_adaptorT> NodeIteratorT;
    typedef DocumentTraversal_impl<stringT, string_adaptorT> DocumentTraversal_implT;
    typedef DOM::Proxy<DocumentTraversal_implT> proxy_t;
    typedef typename proxy_t::value_type impl_t;
    typedef DOM::Document<stringT, string_adaptorT> DocumentT;
    typedef DOM::Node<stringT, string_adaptorT> NodeT;

    DocumentTraversal() : proxy_t(0) { }
    explicit DocumentTraversal(DocumentTraversal_implT* const impl) : proxy_t(impl) { }
    DocumentTraversal(const DocumentTraversal& rhs) : proxy_t(rhs) { }
    explicit DocumentTraversal(const DocumentT& rhs) : proxy_t(rhs.dImpl()) 
    {
      if(dynamic_cast<impl_t*>(rhs.dImpl()) == 0)
        throw DOM::DOMException(DOM::DOMException::NOT_SUPPORTED_ERR); 
    } // DocumentTraversal

    virtual ~DocumentTraversal() { }
    bool operator==(const DocumentTraversal& rhs) const { return proxy_t::operator==(rhs); } 
    bool operator!=(const DocumentTraversal& rhs) const { return proxy_t::operator!=(rhs); }
    bool operator==(int dummy) const { return proxy_t::operator==(dummy); }
    bool operator!=(int dummy) const { return proxy_t::operator!=(dummy); }

    DocumentTraversal& operator=(const DocumentTraversal& rhs) 
    {
      proxy_t::operator=(rhs);
      return *this;
    } // operator=

    ///////////////////////////////////////////////////
    // DocumentTraversal methods
    NodeIteratorT createNodeIterator(NodeT root,
                                     unsigned long whatToShow,
                                     bool entityRefExpansion)
    {
      return NodeIteratorT(proxy_t::impl()->createNodeIterator(root, whatToShow, 0, entityRefExpansion));
    } // createNodeIterator

    NodeIteratorT createNodeIterator(NodeT root,
                                     unsigned long whatToShow,
                                     NodeFilterT& filter,
                                     bool entityRefExpansion)
    {
      return NodeIteratorT(proxy_t::impl()->createNodeIterator(root, whatToShow, &filter, entityRefExpansion));
    } // createNodeIterator

    TreeWalkerT createTreeWalker(NodeT root,
                                 unsigned long whatToShow,
                                 bool entityRefExpansion)
    {
      return TreeWalkerT(proxy_t::impl()->createTreeWalker(root, whatToShow, 0, entityRefExpansion));
    } // createTreeWalker

    TreeWalkerT createTreeWalker(NodeT root,
                                 unsigned long whatToShow,
                                 NodeFilterT& filter,
                                 bool entityRefExpansion)
    {
      return TreeWalkerT(proxy_t::impl()->createTreeWalker(root, whatToShow, &filter, entityRefExpansion));
    } // createTreeWalker
}; // class DocumentTraversal

//////////////////////////////////////////////////////////////
// implementation class
template<class stringT, class string_adaptorT> class NodeIterator_impl;
template<class stringT, class string_adaptorT> class TreeWalker_impl;

template<class stringT, class string_adaptorT>
class DocumentTraversal_impl : virtual public TraversalImpl
{
  public:
    typedef DOM::Node<stringT, string_adaptorT> NodeT;
    typedef NodeFilter<stringT, string_adaptorT> NodeFilterT;
    typedef TreeWalker_impl<stringT, string_adaptorT> TreeWalker_implT;
    typedef NodeIterator_impl<stringT, string_adaptorT> NodeIterator_implT;

    virtual NodeIterator_implT* createNodeIterator(NodeT root,
                                                   unsigned long whatToShow,
                                                   NodeFilterT* filter,
                                                   bool entityRefExpansion) = 0;

    virtual TreeWalker_implT* createTreeWalker(NodeT root,
                                               unsigned long whatToShow,
                                               NodeFilterT* filter,
                                               bool entityRefExpansion) = 0;
}; // class DocumentTraveral_impl

} // namespace Traversal

} // namespace DOM 
} // namespace Arabica

#endif
// end of file

