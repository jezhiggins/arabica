#ifndef JEZUK_SIMPLEDOM_ATTRIMPL_H
#define JEZUK_SIMPLEDOM_ATTRIMPL_H

#include <DOM/Attr.h>
#include <DOM/Simple/NodeImpl.h>
#include <DOM/Simple/TextImpl.h>
#include <DOM/Simple/DocumentTypeImpl.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT> class ElementImpl;

template<class stringT, class string_adaptorT>
class AttrImpl : public DOM::Attr_impl<stringT>,
                 public NodeImplWithChildren<stringT, string_adaptorT>
{
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeT;
  public:
    AttrImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& name) : 
        DOM::Attr_impl<stringT>(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc),
        name_(ownerDoc->stringPool(name)),
        ownerElement_(0),
        specified_(true)
    {
    } // AttrImpl

    AttrImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& name, const stringT& value) : 
        DOM::Attr_impl<stringT>(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc),
        name_(ownerDoc->stringPool(name)),
        ownerElement_(0),
        specified_(true)
    {
      setNodeValue(value);
    } // AttrImpl

    virtual ~AttrImpl() { }

    ///////////////////////////////////////////////////
    // DOM::Attribute methods
    stringT getName() const { return getNodeName(); }

    virtual bool getSpecified() const
    {
      return specified_;
    } // getSpecified

    stringT getValue() const { return getNodeValue(); }
    void setValue(const stringT& value) { setNodeValue(value); }

    virtual DOM::Element_impl<stringT>* getOwnerElement() const
    {
      return ownerElement_;
    } // getOwnerElement

    /////////////////////////////////////////////////////
    // DOM::Node methods
    virtual typename DOM::Node<stringT>::Type getNodeType() const
    {
      return DOM::Node<stringT>::ATTRIBUTE_NODE;
    } // getNodeType

    virtual DOM::Node_impl<stringT>* getParentNode() const { return 0; }
    virtual DOM::Node_impl<stringT>* getPreviousSibling() const { return 0; }
    virtual DOM::Node_impl<stringT>* getNextSibling() const { return 0; }

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      AttrImpl* a = dynamic_cast<AttrImpl*>(NodeT::ownerDoc_->createAttribute(*name_));
      cloneChildren(a);
      a->setSpecified(getSpecified());
      return a;
    } // cloneNode

    virtual stringT getNodeName() const 
    {
      return *name_;
    } // getNodeName

    virtual stringT getNodeValue() const
    {
      stringT value;
      for(DOM::Node_impl<stringT>* c = NodeT::getFirstChild(); c != 0; c = c->getNextSibling())
        string_adaptorT::append(value, c->getNodeValue());
      return value;
    } // getNodeValue

    virtual void setNodeValue(const stringT& data)
    {
      NodeT::throwIfReadOnly();

      // remove all children
      for(DOM::Node_impl<stringT>* c = NodeT::getFirstChild(); c != 0; c = NodeT::getFirstChild())
        NodeT::removeChild(c);

      // add a new text node
      NodeT::appendChild(new TextImpl<stringT, string_adaptorT>(0, data));

      specified_ = true;
    } // setNodeValue

    /////////////////////////////////////////////////////////////
    // this implementation
    void setOwnerElement(ElementImpl<stringT, string_adaptorT>* element)
    {
      ownerElement_ = element;
      if(NodeT::ownerDoc_)
      {
        NodeT::ownerDoc_->adopted(this);  // don't have a parent but are owned
        DocumentTypeImpl<stringT, string_adaptorT>* docType = dynamic_cast<DocumentTypeImpl<stringT, string_adaptorT>*>(NodeT::ownerDoc_->getDoctype());
        if(!docType || docType->getElementIds()->empty())
          return;
        std::vector<stringT>* elemIds = docType->getElementIds();
        if(std::find(elemIds->begin(), elemIds->end(), *name_) != elemIds->end())
          NodeT::ownerDoc_->setElementId(this);
      } // if(ownerDoc_)
    } // setOwnerElement

    void setSpecified(bool specified) { specified_ = specified; }

  protected:
    void cloneChildren(AttrImpl* clone) const
    {
      for(DOM::Node_impl<stringT>* c = NodeT::getFirstChild(); c != 0; c = c->getNextSibling())
        clone->appendChild(c->cloneNode(true));
    } // cloneChildren

  private:
    virtual void checkChildType(DOM::Node_impl<stringT>* child)
    {
      typename DOM::Node<stringT>::Type type = child->getNodeType();
      if((type != DOM::Node<stringT>::TEXT_NODE) && 
         (type != DOM::Node<stringT>::ENTITY_REFERENCE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

  protected:
    stringT const* name_;
    ElementImpl<stringT, string_adaptorT>* ownerElement_;
    bool specified_;
}; // class CDATAImpl

} // namespace SimpleDOM

#endif
