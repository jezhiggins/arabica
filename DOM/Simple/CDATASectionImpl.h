#ifndef JEZUK_SIMPLEDOM_CDATASECTIONIMPL_H
#define JEZUK_SIMPLEDOM_CDATASECTIONIMPL_H

#include <DOM/CDATASection.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class CDATASectionImpl : public DOM::CDATASection_impl<stringT>,
                         public CharacterDataImpl<stringT, string_adaptorT> 
{
    typedef CharacterDataImpl<stringT, string_adaptorT> CharDataT;
  public:
    CDATASectionImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& data) : 
        CharacterDataImpl<stringT, string_adaptorT>(ownerDoc, data)
    { 
    } // CDATASectionImpl

    virtual ~CDATASectionImpl() { }

    //////////////////////////////////////////////////////////////////
    // DOM::CDATASection methods
    // on a compiler which implemented covariant return types this would return DOM::CDATASection
    virtual DOM::Text_impl<stringT>* splitText(int offset)
    {
      CharDataT::throwIfReadOnly();

      stringT second = CharDataT::substringData(offset, CharDataT::getLength() - offset);
      CharDataT::deleteData(offset, CharDataT::getLength() - offset);

      CDATASectionImpl* splitNode = new CDATASectionImpl(CharDataT::getOwnerDoc(), second);
      CharDataT::getParentNode()->insertBefore(splitNode, CharDataT::getNextSibling());
      return splitNode;
    } // splitText

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::CDATA_SECTION_NODE;
    } // getNodeType

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      return CharDataT::ownerDoc_->createCDATASection(CharDataT::getData());
    } // cloneNode

    virtual const stringT& getNodeName() const 
    {
      static const stringT cdata_section = string_adaptorT::construct_from_utf8("#cdata-section");
      return cdata_section;
    } // getNodeName
}; // class CDATAImpl

} // namespace SAX2DOM

#endif

