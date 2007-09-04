#ifndef JEZUK_DOM_TEXT_H
#define JEZUK_DOM_TEXT_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/CharacterData.hpp>

namespace DOM
{
template<class stringT> class Text_impl;

template<class stringT>
class Text : public CharacterData<stringT>
{
    typedef CharacterData<stringT> CharDataT;
  public:
    Text() : CharacterData<stringT>() { }
    explicit Text(Text_impl<stringT>* impl) : CharacterData<stringT>(impl) { }
    Text(const Text& rhs) : CharacterData<stringT>(rhs) { }
    explicit Text(const Node<stringT>& rhs) : CharacterData<stringT>(rhs, 0)  
    {
      typename Text::Type type = rhs.getNodeType();
      if((type != Text::TEXT_NODE) && (type != Text::CDATA_SECTION_NODE))
        //throw std::runtime_error("bad_cast: Cannot cast Node to Text");
        throw std::bad_cast();
    } // Text

  protected:
    Text(const Node<stringT>& rhs, int dummy) : CharacterData<stringT>(rhs, 0) { }

    Text splitText(int offset) 
    { 
      return tImpl()->splitText(offset); 
    } // splitText

  protected:
    Text_impl<stringT>* tImpl() const { return dynamic_cast<Text_impl<stringT>*>(CharDataT::impl()); }
}; // class Text

////////////////////////////////////////////////////////////////////
template<class stringT>
class Text_impl : virtual public CharacterData_impl<stringT>
{
  public:
    virtual ~Text_impl() { }

    ////////////////////////////////////////////////////////////
    // DOM::Text methods
    virtual Text_impl<stringT>* splitText(int offset) = 0;
}; // Text_impl

} // namespace DOM

#endif

