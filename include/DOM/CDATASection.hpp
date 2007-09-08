#ifndef JEZUK_DOM_CDATASECTION_H
#define JEZUK_DOM_CDATASECTION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Text.hpp>

namespace Arabica
{
namespace DOM
{
template<class stringT, class string_adaptorT> class CDATASection_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class CDATASection : public Text<stringT, string_adaptorT>
{
    typedef Text<stringT, string_adaptorT> TextT;
  public:
    CDATASection() : Text<stringT, string_adaptorT>() { }
    explicit CDATASection(CDATASection_impl<stringT, string_adaptorT>* impl) : Text<stringT, string_adaptorT>(impl) { }
    CDATASection(const CDATASection& rhs) : Text<stringT, string_adaptorT>(rhs) { }
    explicit CDATASection(const Node<stringT, string_adaptorT>& rhs) : Text<stringT, string_adaptorT>(rhs, 0)  
    {
      if(rhs.getNodeType() != Node_base::CDATA_SECTION_NODE)
        //throw std::runtime_error("bad_cast: Cannot convert Node to CDATA section");
        throw std::bad_cast();
    } // CDATASection

    CDATASection<stringT, string_adaptorT> splitText(int offset) 
    { 
      TextT::tImpl()->throwIfReadOnly();
      return static_cast<CDATASection<stringT, string_adaptorT> >(TextT::tImpl()->splitText(offset)); 
    } // splitText
}; // class CDATASection

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class CDATASection_impl : public virtual Text_impl<stringT, string_adaptorT>
{
  public:
    virtual ~CDATASection_impl() { }
}; // CDATASection_impl

} // namespace DOM
} // namespace Arabica

#endif
