#ifndef JEZUK_DOM_DOCUMENTFRAGMENT_H
#define JEZUK_DOM_DOCUMENTFRAGMENT_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>
#include <typeinfo>

namespace Arabica
{
namespace DOM
{

template<class stringT, class string_adaptorT> class DocumentFragment_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class DocumentFragment : public Node<stringT, string_adaptorT>
{
  public:
    typedef Node<stringT, string_adaptorT> NodeT;

    DocumentFragment() : Node<stringT, string_adaptorT>() { }
    explicit DocumentFragment(DocumentFragment_impl<stringT, string_adaptorT>* impl) : Node<stringT, string_adaptorT>(impl) { }
    DocumentFragment(const DocumentFragment& rhs) : Node<stringT, string_adaptorT>(rhs) { }
    explicit DocumentFragment(const Node<stringT, string_adaptorT>& rhs) : Node<stringT, string_adaptorT>(rhs)  
    {
      if(NodeT::impl_ == 0) // null nodes can always be cast
	return;
      if(rhs.getNodeType() != Node_base::DOCUMENT_FRAGMENT_NODE)
        throw DOMBadCast("DocumentFragment");
    }
}; // class DocumentFragment

//////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class DocumentFragment_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    virtual ~DocumentFragment_impl() { }
}; // class DocumentFragment_impl

} // namespace DOM
} // namespace Arabica

#endif

