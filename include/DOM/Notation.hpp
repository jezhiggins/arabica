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

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class Notation : public Node<stringT, string_adaptorT>
{
  public:
    typedef Node<stringT, string_adaptorT> NodeT;
    typedef Notation_impl<stringT, string_adaptorT> Notation_implT;

    Notation() : NodeT() { }
    explicit Notation(Notation_implT* impl) : NodeT(nImpl()) { }
    Notation(const Notation& rhs) : NodeT(rhs) { }
    explicit Notation(const NodeT& rhs) : NodeT(rhs)  
    {
      if(rhs.getNodeType() != Node_base::NOTATION_NODE)
        throw std::bad_cast();
    }

    stringT getPublicId() const { nImpl()->getPublicId(); }

    stringT getSystemId() const { nImpl()->getSystemId(); }

  private:
    Notation_implT* nImpl() { return dynamic_cast<Notation_implT*>(NodeT::impl()); }
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

