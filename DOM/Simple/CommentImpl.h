#ifndef JEZUK_SimpleDOM_COMMENTIMPL_H
#define JEZUK_SimpleDOM_COMMENTIMPL_H

#include <DOM/Comment.h>
#include <DOM/Simple/CharacterDataImpl.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class CommentImpl : public DOM::Comment_impl<stringT>,
                    public CharacterDataImpl<stringT, string_adaptorT>
{
    typedef DOM::Comment_impl<stringT> CommentT;
    using CommentT::ownerDoc_;
    using CommentT::cloneNode;
    using CommentT::getData;

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

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      return ownerDoc_->createComment(getData());
    } // cloneNode

    virtual stringT getNodeName() const 
    {
      string_adaptorT SA;
      return SA.makeStringT("#comment");
    } // getNodeName
}; // class CommentImpl

} // namespace SAX2DOM

#endif

