#ifndef JEZUK_DOM_TRAVERSAL_DOCUMENT_TRAVERSAL_IMPL_H
#define JEZUK_DOM_TRAVERSAL_DOCUMENT_TRAVERSAL_IMPL_H

/////////////////////////////////////////
// C++ DOM Traversal Implementation
/////////////////////////////////////////

#include <DOM/Traversal/TreeWalkerImpl.hpp>

namespace Arabica
{
namespace DOM
{
namespace Traversal
{


template<class stringT, class string_adaptorT>
class DocumentTraversalImpl : public DocumentTraversal_impl<stringT, string_adaptorT>
{
  public:
    typedef DOM::Node<stringT, string_adaptorT> NodeT;
    typedef NodeFilter<stringT, string_adaptorT> NodeFilterT;
    typedef NodeIterator_impl<stringT, string_adaptorT> NodeIterator_implT;
    typedef TreeWalker_impl<stringT, string_adaptorT> TreeWalker_implT;
    typedef TreeWalkerImpl<stringT, string_adaptorT> TreeWalkerImplT;

    DocumentTraversalImpl() {}

    virtual NodeIterator_implT* 
                createNodeIterator(NodeT /* root */,
                                   unsigned long /* whatToShow */,
                                   NodeFilterT* /* filter */,
                                   bool /* entityRefExpansion */) 
    {
      return 0;
    }

    virtual TreeWalker_implT* 
                createTreeWalker(NodeT root,
                                 unsigned long whatToShow,
                                 NodeFilterT* filter,
                                 bool entityRefExpansion)
    {
      return new TreeWalkerImplT(root, whatToShow, filter, entityRefExpansion);
    }
}; // class DocumentTraversalImpl



//todo: move to DOM::Document?
template<class stringT, class string_adaptorT>
DocumentTraversal<stringT, string_adaptorT> make_document_traversal_t()
{
  DocumentTraversal<stringT, string_adaptorT> docTraversal(new DocumentTraversalImpl<stringT, string_adaptorT>());
  return docTraversal;
}

} // namespace Traversal
} // namespace DOM
} // namespace Arabica

#endif //JEZUK_DOM_TRAVERSAL_DOCUMENT_TRAVERSAL_IMPL_H
// end of file
