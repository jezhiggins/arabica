#ifndef JEZUK_SimpleDOM_COMMENTIMPL_H
#define JEZUK_SimpleDOM_COMMENTIMPL_H

#include <DOM/Comment.hpp>
#include <DOM/Simple/CharacterDataImpl.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class CommentImpl : public DOM::Comment_impl<stringT, string_adaptorT>,
                    public CharacterDataImpl<stringT, string_adaptorT>
{
    typedef CharacterDataImpl<stringT, string_adaptorT> CharDataT;
  public:
    CommentImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& data) : 
        CharacterDataImpl<stringT, string_adaptorT>(ownerDoc, data)
    { 
    } // CommentImpl

    virtual ~CommentImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::COMMENT_NODE;
    } // getNodeType

    virtual DOM::Node_impl<stringT, string_adaptorT>* cloneNode(bool /*deep*/) const
    {
      return CharDataT::ownerDoc_->createComment(CharDataT::getData());
    } // cloneNode

    virtual const stringT& getNodeName() const 
    {
      static const stringT comment = string_adaptorT::construct_from_utf8("#comment");
      return comment;
    } // getNodeName
}; // class CommentImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif

