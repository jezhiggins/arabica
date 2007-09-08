#ifndef JEZUK_DOM_ENTITY_H
#define JEZUK_DOM_ENTITY_H

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

template<class stringT, class string_adaptorT> class Entity_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class Entity : public Node<stringT, string_adaptorT>
{
  public:
    typedef Node<stringT, string_adaptorT> NodeT;
    typedef Entity_impl<stringT, string_adaptorT> Entity_implT;

    Entity() : Node<stringT, string_adaptorT>() { }
    explicit Entity(Entity_impl<stringT, string_adaptorT>* impl) : Node<stringT>(impl) { }
    Entity(const Entity& rhs) : Node<stringT, string_adaptorT>(rhs) { }
    explicit Entity(const Node<stringT, string_adaptorT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT, string_adaptorT>::Entity_NODE)
        throw std::bad_cast();
    }

    stringT getPublicId() const { nImpl()->getPublicId(); }

    stringT getSystemId() const { nImpl()->getSystemId(); }

    stringT getNotationName() const { nImpl()->getNotationName(); }

  private:
    Entity_implT* nImpl() { return dynamic_cast<Entity_implT*>(NodeT::impl()); }
}; // class Entity

//////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class NamedNodeMap_impl;

template<class stringT, class string_adaptorT>
class Entity_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    virtual ~Entity_impl () { }

    /////////////////////////////////////////////
    // DOM::Entity
    virtual stringT getPublicId() const = 0;

    virtual stringT getSystemId() const = 0;

    virtual stringT getNotationName() const = 0;
}; // class Entity_impl

} // namespace DOM
} // namespace Arabica
#endif

