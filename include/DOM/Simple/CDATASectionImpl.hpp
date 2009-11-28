#ifndef JEZUK_SIMPLEDOM_CDATASECTIONIMPL_H
#define JEZUK_SIMPLEDOM_CDATASECTIONIMPL_H

#include <DOM/CDATASection.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class CDATASectionImpl : public DOM::CDATASection_impl<stringT, string_adaptorT>,
                         public CharacterDataImpl<stringT, string_adaptorT> 
{
  public:
    typedef CharacterDataImpl<stringT, string_adaptorT> CharacterDataImplT;
    typedef DOM::Text_impl<stringT, string_adaptorT> DOMText_implT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;

    CDATASectionImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& data) : 
        CharacterDataImplT(ownerDoc, data)
    { 
    } // CDATASectionImpl

    virtual ~CDATASectionImpl() { }

    //////////////////////////////////////////////////////////////////
    // DOM::CDATASection methods
    // on a compiler which implemented covariant return types this would return DOM::CDATASection
    virtual DOMText_implT* splitText(int offset)
    {
      CharacterDataImplT::throwIfReadOnly();

      stringT second = CharacterDataImplT::substringData(offset, CharacterDataImplT::getLength() - offset);
      CharacterDataImplT::deleteData(offset, CharacterDataImplT::getLength() - offset);

      CDATASectionImpl* splitNode = new CDATASectionImpl(CharacterDataImplT::getOwnerDoc(), second);
      CharacterDataImplT::getParentNode()->insertBefore(splitNode, CharacterDataImplT::getNextSibling());
      return splitNode;
    } // splitText

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::CDATA_SECTION_NODE;
    } // getNodeType

    virtual DOMNode_implT* cloneNode(bool /*deep*/) const
    {
      return CharacterDataImplT::ownerDoc_->createCDATASection(CharacterDataImplT::getData());
    } // cloneNode

    virtual const stringT& getNodeName() const 
    {
      static const stringT cdata_section = string_adaptorT::construct_from_utf8("#cdata-section");
      return cdata_section;
    } // getNodeName
}; // class CDATAImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif

