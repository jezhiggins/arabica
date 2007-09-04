#ifndef JEZUK_DOM_NOTATION_H
#define JEZUK_DOM_NOTATION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>
#include <typeinfo>

namespace DOM
{

template<class stringT> class Notation_impl;

template<class stringT>
class Notation : public Node<stringT>
{
    typedef Node<stringT> NodeT;
  public:
    Notation() : Node<stringT>() { }
    explicit Notation(Notation_impl<stringT>* impl) : Node<stringT>(dynamic_cast<Node_impl<stringT>*>(impl)) { }
    Notation(const Notation& rhs) : Node<stringT>(rhs) { }
    explicit Notation(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT>::NOTATION_NODE)
        throw std::bad_cast();
    }

    stringT getPublicId() const { nImpl()->getPublicId(); }

    stringT getSystemId() const { nImpl()->getSystemId(); }

  private:
    Notation_impl<stringT>* nImpl() { return dynamic_cast<Notation_impl<stringT>*>(NodeT::impl()); }
}; // class Notation

//////////////////////////////////////////////////////////
template<class stringT> class NamedNodeMap_impl;

template<class stringT>
class Notation_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~Notation_impl () { }

    /////////////////////////////////////////////
    // DOM::Notation
    virtual stringT getPublicId() const = 0;

    virtual stringT getSystemId() const = 0;
}; // class Notation_impl

} // namespace DOM

#endif

