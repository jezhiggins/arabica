#ifndef JEZUK_DOM_NOTATION_H
#define JEZUK_DOM_NOTATION_H

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

template<class stringT, class string_adaptorT> class Notation_impl;

template<class stringT, class string_adaptorT>
class Notation : public Node<stringT, string_adaptorT>
{
    typedef Node<stringT, string_adaptorT> NodeT;
  public:
    Notation() : Node<stringT, string_adaptorT>() { }
    explicit Notation(Notation_impl<stringT, string_adaptorT>* impl) : Node<stringT>(dynamic_cast<Node_impl<stringT>*>(impl)) { }
    Notation(const Notation& rhs) : Node<stringT, string_adaptorT>(rhs) { }
    explicit Notation(const Node<stringT, string_adaptorT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT, string_adaptorT>::NOTATION_NODE)
        throw std::bad_cast();
    }

    stringT getPublicId() const { nImpl()->getPublicId(); }

    stringT getSystemId() const { nImpl()->getSystemId(); }

  private:
    Notation_impl<stringT, string_adaptorT>* nImpl() { return dynamic_cast<Notation_impl<stringT>*>(NodeT::impl()); }
}; // class Notation

//////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class NamedNodeMap_impl;

template<class stringT, class string_adaptorT>
class Notation_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    virtual ~Notation_impl () { }

    /////////////////////////////////////////////
    // DOM::Notation
    virtual stringT getPublicId() const = 0;

    virtual stringT getSystemId() const = 0;
}; // class Notation_impl

} // namespace DOM
} // namespace Arabica

#endif

