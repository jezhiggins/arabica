#ifndef JEZUK_DOM_ATTR_H
#define JEZUK_DOM_ATTR_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.h>

namespace DOM
{

template<class stringT> class Element;
template<class stringT> class Attr_impl;

template<class stringT>
class Attr : public Node<stringT>
{
    using Node<stringT>::impl_;
  public:
    Attr() : Node<stringT>() { }
    explicit Attr(Attr_impl<stringT>* impl) : Node<stringT>(impl) { }
    Attr(const Attr& rhs) : Node<stringT>(rhs) { }
    explicit Attr(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT>::ATTRIBUTE_NODE)
        throw std::bad_cast();
    } // Attr

    stringT getName() const { return attrImpl()->getName(); }

    bool getSpecified() const { return attrImpl()->getSpecified(); }

    stringT getValue() const { return attrImpl()->getValue(); }
    void setValue(const stringT& value) 
    { 
      attrImpl()->throwIfReadOnly();
      attrImpl()->setValue(value); 
    } // setValue 

    Element<stringT> getOwnerElement() const { return Element<stringT>(attrImpl()->getOwnerElement()); }

  private:
    Attr_impl<stringT>* attrImpl() const { return dynamic_cast<Attr_impl<stringT>*>(*impl_); }

    typedef Element<stringT> ElementT;
    friend class Element<stringT>;
}; // class DocumentFragment


//////////////////////////////////////////////////////////
template<class stringT> class Element_impl;

template<class stringT>
class Attr_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~Attr_impl() { }

    ///////////////////////////////////////////////////
    // DOM::Attribute methods
    virtual stringT getName() const = 0;

    virtual bool getSpecified() const = 0;

    virtual stringT getValue() const = 0;
    virtual void setValue(const stringT& value) = 0;

    virtual Element_impl<stringT>* getOwnerElement() const = 0;
}; // class Attr_impl

} // namespace DOM

#endif
