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
template<class stringT> class Comment_impl;

template<class stringT>
class Comment : public CharacterData<stringT>
{
  public:
    Comment() : CharacterData<stringT>() { }
    explicit Comment(Comment_impl<stringT>* impl) : CharacterData<stringT>(dynamic_cast<Comment_impl<stringT>*>(impl)) { }
    Comment(const Comment& rhs) : CharacterData<stringT>(rhs) { }
    explicit Comment(const Node<stringT>& rhs) : CharacterData<stringT>(rhs)  
    {
      if(dynamic_cast<Comment_impl<stringT>*>(rhs.impl()) == 0)
        throw std::bad_cast();
    } // Comment
}; // class Comment

////////////////////////////////////////////////////////////////////
template<class stringT>
class Comment_impl : virtual public CharacterData_impl<stringT>
{
  public:
    virtual ~Comment_impl() { }
}; // Comment_impl

} // namespace DOM
} // namespace Arabica

#endif
