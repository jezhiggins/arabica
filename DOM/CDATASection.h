#ifndef JEZUK_DOM_CDATASECTION_H
#define JEZUK_DOM_CDATASECTION_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Text.h>

namespace DOM
{
template<class stringT> class CDATASection_impl;

template<class stringT>
class CDATASection : public Text<stringT>
{
    typedef Text<stringT> TextT;
  public:
    CDATASection() : Text<stringT>() { }
    explicit CDATASection(CDATASection_impl<stringT>* impl) : Text<stringT>(impl) { }
    CDATASection(const CDATASection& rhs) : Text<stringT>(rhs) { }
    explicit CDATASection(const Node<stringT>& rhs) : Text<stringT>(rhs, 0)  
    {
      if(rhs.getNodeType() != Node_base::CDATA_SECTION_NODE)
        //throw std::runtime_error("bad_cast: Cannot convert Node to CDATA section");
        throw std::bad_cast();
    } // CDATASection

    CDATASection<stringT> splitText(int offset) 
    { 
      TextT::tImpl()->throwIfReadOnly();
      return static_cast<CDATASection<stringT> >(TextT::tImpl()->splitText(offset)); 
    } // splitText
}; // class CDATASection

////////////////////////////////////////////////////////////////////
template<class stringT>
class CDATASection_impl : public virtual Text_impl<stringT>
{
  public:
    virtual ~CDATASection_impl() { }
}; // CDATASection_impl


} // namespace DOM

#endif
