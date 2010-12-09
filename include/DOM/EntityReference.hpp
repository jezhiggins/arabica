#ifndef JEZUK_DOM_ENTITYREFERENCE_H
#define JEZUK_DOM_ENTITYREFERENCE_H

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
template<class stringT, class string_adaptorT> class EntityReference_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class EntityReference : public Node<stringT, string_adaptorT>
{
    typedef EntityReference_impl<stringT, string_adaptorT> EntityReference_implT;

  public:
    typedef Node<stringT, string_adaptorT> NodeT;

    EntityReference() : NodeT() { }
    explicit EntityReference(EntityReference_implT* impl) : NodeT(impl) { }
    EntityReference(const EntityReference& rhs) : NodeT(rhs) { }
    explicit EntityReference(const NodeT& rhs) : NodeT(rhs)  
    {
	  if(NodeT::impl_ == 0) // null nodes can always be cast
		return;
      if(rhs.getNodeType() != Node_base::ENTITY_REFERENCE_NODE)
        throw std::bad_cast();
    } // EntityReference
}; // class EntityReference

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class EntityReference_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    virtual ~EntityReference_impl () { }
}; // EntityReference_impl

} // namespace DOM
} // namespace Arabica

#endif

