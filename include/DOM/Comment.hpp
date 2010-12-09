#ifndef JEZUK_DOM_COMMENT_H
#define JEZUK_DOM_COMMENT_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/CharacterData.hpp>

namespace Arabica
{
namespace DOM
{
template<class stringT, class string_adaptor> class Comment_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class Comment : public CharacterData<stringT, string_adaptorT>
{
  public:
    Comment() : CharacterData<stringT, string_adaptorT>() { }
    explicit Comment(Comment_impl<stringT, string_adaptorT>* impl) : CharacterData<stringT, string_adaptorT>(dynamic_cast<Comment_impl<stringT, string_adaptorT>*>(impl)) { }
    Comment(const Comment& rhs) : CharacterData<stringT, string_adaptorT>(rhs) { }
    explicit Comment(const Node<stringT, string_adaptorT>& rhs) : CharacterData<stringT, string_adaptorT>(rhs)  
    {
	  if(NodeT::impl_ == 0) // null nodes can always be cast
		return;
      if(rhs.getNodeType() != Node<stringT, string_adaptorT>::COMMENT_NODE)
        throw std::bad_cast();
    } // Comment
}; // class Comment

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class Comment_impl : virtual public CharacterData_impl<stringT, string_adaptorT>
{
  public:
    virtual ~Comment_impl() { }
}; // Comment_impl

} // namespace DOM
} // namespace Arabica

#endif
