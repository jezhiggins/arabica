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
    typedef DOM::Text_impl<stringT> TextT;
    using TextT::splitText;
    using TextT::throwIfReadOnly;
    using TextT::getLength;
    using TextT::getOwnerDoc;
    using TextT::getParentNode;
    using TextT::getNextSibling;
    using TextT::cloneNode;
    using TextT::ownerDoc_;
    using TextT::getData;

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
      throwIfReadOnly();

      stringT second = substringData(offset, getLength() - offset);
      deleteData(offset, getLength() - offset);

      TextImpl* splitNode = new TextImpl(getOwnerDoc(), second);
      getParentNode()->insertBefore(splitNode, getNextSibling());
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
      return ownerDoc_->createTextNode(getData());
    } // cloneNode

    virtual stringT getNodeName() const 
    {
      string_adaptorT SA;
      return SA.makeStringT("#text");
    } // getNodeName
}; // class TextImpl

} // namespace SAX2DOM

#endif

