#ifndef JEZUK_DOM_ATTR_H
#define JEZUK_DOM_ATTR_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>

namespace Arabica
{
namespace DOM
{

template<class stringT, class string_adaptorT> class Element;
template<class stringT, class string_adaptorT> class Attr_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class Attr : public Node<stringT, string_adaptorT>
{
  public:
    typedef Node<stringT, string_adaptorT> NodeT;
    typedef Element<stringT, string_adaptorT> ElementT;
    typedef Attr_impl<stringT, string_adaptorT> Attr_implT;

    Attr() : NodeT() { }

    explicit Attr(Attr_implT* impl) : NodeT(impl) { }
    Attr(const Attr& rhs) : NodeT(rhs) { }
    explicit Attr(const NodeT& rhs) : NodeT(rhs)  
    {
      if(rhs.getNodeType() != NodeT::ATTRIBUTE_NODE)
        throw std::bad_cast();
    } // Attr

    const stringT& getName() const { return attrImpl()->getName(); }

    bool getSpecified() const { return attrImpl()->getSpecified(); }

    const stringT& getValue() const { return attrImpl()->getValue(); }
    void setValue(const stringT& value) { attrImpl()->setValue(value); } 

    ElementT getOwnerElement() const { return ElementT(attrImpl()->getOwnerElement()); }

  private:
    Attr_implT* attrImpl() const { return dynamic_cast<Attr_implT*>(*NodeT::impl_); }

    friend class Element<stringT, string_adaptorT>;
}; // class Attr


//////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class Element_impl;

template<class stringT, class string_adaptorT>
class Attr_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    virtual ~Attr_impl() { }

    ///////////////////////////////////////////////////
    // DOM::Attribute methods
    virtual const stringT& getName() const = 0;

    virtual bool getSpecified() const = 0;

    virtual const stringT& getValue() const = 0;
    virtual void setValue(const stringT& value) = 0;

    virtual Element_impl<stringT, string_adaptorT>* getOwnerElement() const = 0;
}; // class Attr_impl

} // namespace DOM
} // namespace Arabica

#endif
