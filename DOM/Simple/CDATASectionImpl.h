#ifndef JEZUK_SIMPLEDOM_CDATASECTIONIMPL_H
#define JEZUK_SIMPLEDOM_CDATASECTIONIMPL_H

#include <DOM/CDATASection.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class CDATASectionImpl : public DOM::CDATASection_impl<stringT>,
                         public CharacterDataImpl<stringT, string_adaptorT> 
{
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
      throwIfReadOnly();

      stringT second = substringData(offset, getLength() - offset);
      deleteData(offset, getLength() - offset);

      CDATASectionImpl* splitNode = new CDATASectionImpl(getOwnerDoc(), second);
      getParentNode()->insertBefore(splitNode, getNextSibling());
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
      return ownerDoc_->createCDATASection(getData());
    } // cloneNode

    virtual stringT getNodeName() const 
    {
      string_adaptorT SA;
      return SA.makeStringT("#cdata-section");
    } // getNodeName
}; // class CDATAImpl

} // namespace SAX2DOM

#endif

