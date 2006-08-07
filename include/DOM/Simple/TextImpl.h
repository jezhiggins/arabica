#ifndef JEZUK_SimpleDOM_TEXTIMPL_H
#define JEZUK_SimpleDOM_TEXTIMPL_H

#include <DOM/Text.h>
#include <DOM/Simple/CharacterDataImpl.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class TextImpl : public DOM::Text_impl<stringT>,
                 public CharacterDataImpl<stringT, string_adaptorT>
{
    typedef CharacterDataImpl<stringT, string_adaptorT> CharDataT;
  public:
    TextImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& data) : 
        DOM::Text_impl<stringT>(),
        CharacterDataImpl<stringT, string_adaptorT>(ownerDoc, data)
    { 
    } // TextImpl

    virtual ~TextImpl() { }

    //////////////////////////////////////////////////////////////////
    // DOM::Text methods
    virtual DOM::Text_impl<stringT>* splitText(int offset)
    {
      CharDataT::throwIfReadOnly();

      stringT second = CharDataT::substringData(offset, CharDataT::getLength() - offset);
      CharDataT::deleteData(offset, CharDataT::getLength() - offset);

      TextImpl* splitNode = new TextImpl(CharDataT::getOwnerDoc(), second);
      CharDataT::getParentNode()->insertBefore(splitNode, CharDataT::getNextSibling());
      return splitNode;
    } // splitText

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::TEXT_NODE;
    } // getNodeType

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      return CharDataT::ownerDoc_->createTextNode(CharDataT::getData());
    } // cloneNode

    virtual const stringT& getNodeName() const 
    {
      static const stringT text = string_adaptorT::construct_from_utf8("#text");
      return text;
    } // getNodeName
}; // class TextImpl

} // namespace SAX2DOM

#endif

