#ifndef JEZUK_SimpleDOM_NOTATIONIMPL_H
#define JEZUK_SimpleDOM_NOTATIONIMPL_H

#include <DOM/Notation.h>
#include <DOM/Simple/NodeImpl.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class NotationImpl : public DOM::Notation_impl<stringT>,
                     public NodeImplWithChildren<stringT, string_adaptorT>
{
    typedef DOM::Notation_impl<stringT> NotationT;
    using NotationT::ownerDoc_;

  public:
    NotationImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, 
                 stringT name,
                 stringT publicId,
                 stringT systemId) :
        DOM::Notation_impl<stringT>(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc),
        name_(name),
        publicId_(publicId),
        systemId_(systemId)
    { 
    } // NotationImpl

    virtual ~NotationImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Notation methods
    virtual stringT getPublicId() const { return publicId_; }
    virtual stringT getSystemId() const { return systemId_; }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual typename DOM::Node<stringT>::Type getNodeType() const
    {
      return DOM::Node<stringT>::NOTATION_NODE;
    } // getNodeType

    virtual stringT getNodeName() const
    {
      return name_;
    } // getNodeName

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      NotationImpl* clone = new NotationImpl(ownerDoc_, name_, publicId_, systemId_);
      ownerDoc_->orphaned(clone);
      return clone;
    } // cloneNode

    virtual DOM::Node_impl<stringT>* getParentNode() const { return 0; }

  protected:
    ///////////////////////////////////////////////
    virtual void checkChildType(DOM::Node_impl<stringT>* child)
    {
      throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);
    } // checkChildType

  private:
    stringT name_;
    stringT publicId_;
    stringT systemId_;
}; // class NotationImpl


} // namespace SAX2DOM

#endif

