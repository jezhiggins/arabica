#ifndef JEZUK_DOM_DOCUMENTFRAGMENT_H
#define JEZUK_DOM_DOCUMENTFRAGMENT_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>
#include <typeinfo>

namespace DOM
{

template<class stringT> class DocumentFragment_impl;

template<class stringT>
class DocumentFragment : public Node<stringT>
{
  public:
    DocumentFragment() : Node<stringT>() { }
    explicit DocumentFragment(DocumentFragment_impl<stringT>* impl) : Node<stringT>(impl) { }
    DocumentFragment(const DocumentFragment& rhs) : Node<stringT>(rhs) { }
    explicit DocumentFragment(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT>::DOCUMENT_FRAGMENT_NODE)
        throw std::bad_cast();
    }
}; // class DocumentFragment

//////////////////////////////////////////////////////////
template<class stringT>
class DocumentFragment_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~DocumentFragment_impl() { }
}; // class DocumentFragment_impl

} // namespace DOM

#endif

