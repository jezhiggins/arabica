#ifndef JEZUK_DOM_TEXT_H
#define JEZUK_DOM_TEXT_H

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
template<class stringT, class string_adaptorT> class Text_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class Text : public CharacterData<stringT, string_adaptorT>
{
    typedef Text_impl<stringT, string_adaptorT> Text_implT;
  public:
    typedef Node<stringT, string_adaptorT> NodeT;
    typedef CharacterData<stringT, string_adaptorT> CharacterDataT;

    Text() : CharacterDataT() { }
    explicit Text(Text_implT* impl) : CharacterDataT(impl) { }
    Text(const Text& rhs) : CharacterDataT(rhs) { }
    explicit Text(const NodeT& rhs) : CharacterDataT(rhs, 0)  
    {
      typename Text::Type type = rhs.getNodeType();
      if((type != Text::TEXT_NODE) && (type != Text::CDATA_SECTION_NODE))
        //throw std::runtime_error("bad_cast: Cannot cast Node to Text");
        throw std::bad_cast();
    } // Text

    Text splitText(int offset) 
    { 
      return Text(tImpl()->splitText(offset)); 
    } // splitText

  protected:
    Text(const NodeT& rhs, int dummy) : CharacterDataT(rhs, dummy) { }
    Text_implT* tImpl() const { return dynamic_cast<Text_implT*>(*NodeT::impl_); }
}; // class Text

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class Text_impl : virtual public CharacterData_impl<stringT, string_adaptorT>
{
  public:
    virtual ~Text_impl() { }

    ////////////////////////////////////////////////////////////
    // DOM::Text methods
    virtual Text_impl<stringT, string_adaptorT>* splitText(int offset) = 0;
}; // Text_impl

} // namespace DOM
} // namespace Arabica

#endif

