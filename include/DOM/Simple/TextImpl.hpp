#ifndef JEZUK_SimpleDOM_TEXTIMPL_H
#define JEZUK_SimpleDOM_TEXTIMPL_H

#include <DOM/Text.hpp>
#include <DOM/Simple/CharacterDataImpl.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class TextImpl : public DOM::Text_impl<stringT, string_adaptorT>,
                 public CharacterDataImpl<stringT, string_adaptorT>
{
  public:
    typedef CharacterDataImpl<stringT, string_adaptorT> CharacterDataT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::Text_impl<stringT, string_adaptorT> DOMText_implT;

    TextImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& data) : 
        DOMText_implT(),
        CharacterDataImpl<stringT, string_adaptorT>(ownerDoc, data)
    { 
    } // TextImpl

    virtual ~TextImpl() { }

    //////////////////////////////////////////////////////////////////
    // DOM::Text methods
    virtual DOMText_implT* splitText(int offset)
    {
      CharacterDataT::throwIfReadOnly();

      stringT second = CharacterDataT::substringData(offset, CharacterDataT::getLength() - offset);
      CharacterDataT::deleteData(offset, CharacterDataT::getLength() - offset);

      TextImpl* splitNode = new TextImpl(CharacterDataT::getOwnerDoc(), second);
      DOMNode_implT *parent = CharacterDataT::getParentNode();
      if(parent)
        parent->insertBefore(splitNode, CharacterDataT::getNextSibling());
      return splitNode;
    } // splitText

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::TEXT_NODE;
    } // getNodeType

    virtual DOMNode_implT* cloneNode(bool /*deep*/) const
    {
      return CharacterDataT::ownerDoc_->createTextNode(CharacterDataT::getData());
    } // cloneNode

    virtual const stringT& getNodeName() const 
    {
      static const stringT text = string_adaptorT::construct_from_utf8("#text");
      return text;
    } // getNodeName
}; // class TextImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif

