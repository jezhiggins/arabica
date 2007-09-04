#ifndef JEZUK_DOM_ENTITYREFERENCE_H
#define JEZUK_DOM_ENTITYREFERENCE_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>

namespace DOM
{
template<class stringT> class EntityReference_impl;

template<class stringT>
class EntityReference : public Node<stringT>
{
  public:
    EntityReference() : Node<stringT>() { }
    explicit EntityReference(EntityReference_impl<stringT>* impl) : Node<stringT>(impl) { }
    EntityReference(const EntityReference& rhs) : Node<stringT>(rhs) { }
    explicit EntityReference(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(dynamic_cast<EntityReference_impl<stringT>*>(rhs.impl()) == 0)
        throw std::bad_cast();
    } // EntityReference
}; // class EntityReference

////////////////////////////////////////////////////////////////////
template<class stringT>
class EntityReference_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~EntityReference_impl () { }
}; // EntityReference_impl


} // namespace DOM

#endif

