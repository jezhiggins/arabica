#ifndef JEZUK_DOM_ENTITY_H
#define JEZUK_DOM_ENTITY_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.h>

namespace DOM
{

template<class stringT> class Entity_impl;

template<class stringT>
class Entity : public Node<stringT>
{
  public:
    Entity() : Node<stringT>() { }
    explicit Entity(Entity_impl<stringT>* impl) : Node<stringT>(impl) { }
    Entity(const Entity& rhs) : Node<stringT>(rhs) { }
    explicit Entity(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT>::Entity_NODE)
        throw std::bad_cast();
    }

    stringT getPublicId() const { nImpl()->getPublicId(); }

    stringT getSystemId() const { nImpl()->getSystemId(); }

    stringT getNotationName() const { nImpl()->getNotationName(); }

  private:
    Entity_impl<stringT>* nImpl() { return dynamic_cast<Entity_impl<stringT>*>(impl()); }
}; // class Entity

//////////////////////////////////////////////////////////
template<class stringT> class NamedNodeMap_impl;

template<class stringT>
class Entity_impl : virtual public Node_impl<stringT>
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

#endif

