#ifndef JEZUK_DOM_TRAVERSAL_DOCUMENT_TRAVERSAL_IMPL_H
#define JEZUK_DOM_TRAVERSAL_DOCUMENT_TRAVERSAL_IMPL_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
//
// $Id: TreeWalker.h 2 2002-06-21 11:16:28Z jez_higgins $
/////////////////////////////////////////

#include <DOM/Traversal/TreeWalkerImpl.h>

namespace DOM
{
namespace Traversal
{


template<class stringT>
class DocumentTraversalImpl : public DocumentTraversal_impl<stringT>
{
  public:
    DocumentTraversalImpl() {}

    virtual NodeIterator_impl<stringT>* createNodeIterator(DOM::Node<stringT> root,
                                                           unsigned long whatToShow,
                                                           NodeFilter<stringT>* filter,
                                                           bool entityRefExpansion) 
    {
      return 0;
    }

    virtual TreeWalker_impl<stringT>* createTreeWalker(DOM::Node<stringT> root,
                                                       unsigned long whatToShow,
                                                       NodeFilter<stringT>* filter,
                                                       bool entityRefExpansion)
    {
      return new TreeWalkerImpl<stringT>(root, whatToShow, filter, entityRefExpansion);
    }
}; // class DocumentTraversalImpl



//todo: move to DOM::Document?
template<class stringT>
DocumentTraversal<stringT> make_document_traversal_t()
{
  DocumentTraversal<stringT> docTraversal(new DocumentTraversalImpl<stringT>());
  return docTraversal;
}



} // namespace Traversal
} // namespace DOM

#endif //JEZUK_DOM_TRAVERSAL_DOCUMENT_TRAVERSAL_IMPL_H
// end of file
