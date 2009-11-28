#ifndef JEZUK_SimpleDOM_NOTATIONIMPL_H
#define JEZUK_SimpleDOM_NOTATIONIMPL_H

#include <DOM/Notation.hpp>
#include <DOM/Simple/NodeImpl.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class NotationImpl : public DOM::Notation_impl<stringT, string_adaptorT>,
                     public NodeImplWithChildren<stringT, string_adaptorT>
{
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeWithChildrenT;
  public:
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;

    NotationImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, 
                 stringT name,
                 stringT publicId,
                 stringT systemId) :
        DOM::Notation_impl<stringT, string_adaptorT>(),
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
    virtual typename DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::NOTATION_NODE;
    } // getNodeType

    virtual const stringT& getNodeName() const
    {
      return name_;
    } // getNodeName

    virtual DOMNode_implT* cloneNode(bool /*deep*/) const
    {
      NotationImpl* clone = new NotationImpl(NodeWithChildrenT::ownerDoc_, name_, publicId_, systemId_);
      NodeWithChildrenT::ownerDoc_->orphaned(clone);
      return clone;
    } // cloneNode

    virtual DOMNode_implT* getParentNode() const { return 0; }

  protected:
    ///////////////////////////////////////////////
    virtual void checkChildType(DOMNode_implT* /*child*/)
    {
      throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);
    } // checkChildType

  private:
    stringT name_;
    stringT publicId_;
    stringT systemId_;
}; // class NotationImpl


} // namespace SAX2DOM
} // namespace Arabica

#endif

