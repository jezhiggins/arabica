#ifndef JEZUK_SIMPLEDOM_ATTRIMPL_H
#define JEZUK_SIMPLEDOM_ATTRIMPL_H

#include <DOM/Attr.hpp>
#include <DOM/Simple/NodeImpl.hpp>
#include <DOM/Simple/TextImpl.hpp>
#include <DOM/Simple/DocumentTypeImpl.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT> class ElementImpl;

template<class stringT, class string_adaptorT>
class AttrImpl : public DOM::Attr_impl<stringT, string_adaptorT>,
                 public NodeImplWithChildren<stringT, string_adaptorT>
{
  public:
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeT;
    typedef ElementImpl<stringT, string_adaptorT> ElementImplT;
    typedef DOM::Attr_impl<stringT, string_adaptorT> DOMAttr_implT;
    typedef DOM::Element_impl<stringT, string_adaptorT> DOMElement_implT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;

    AttrImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& name) : 
        DOMAttr_implT(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc),
        name_(ownerDoc->stringPool(name)),
        ownerElement_(0),
        specified_(true),
        valueCalculated_(false)
    {
    } // AttrImpl

    AttrImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& name, const stringT& value) : 
        DOMAttr_implT(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc),
        name_(ownerDoc->stringPool(name)),
        ownerElement_(0),
        specified_(true),
        valueCalculated_(false)
    {
      setNodeValue(value);
    } // AttrImpl

    virtual ~AttrImpl() { }

    ///////////////////////////////////////////////////
    // DOM::Attribute methods
    virtual const stringT& getName() const { return getNodeName(); }

    virtual bool getSpecified() const
    {
      return specified_;
    } // getSpecified

    const stringT& getValue() const { return getNodeValue(); }
    void setValue(const stringT& value) { setNodeValue(value); }

    virtual DOMElement_implT* getOwnerElement() const
    {
      return ownerElement_;
    } // getOwnerElement

    /////////////////////////////////////////////////////
    // DOM::Node methods
    virtual typename DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::ATTRIBUTE_NODE;
    } // getNodeType

    virtual DOMNode_implT* getParentNode() const { return 0; }
    virtual DOMNode_implT* getPreviousSibling() const { return 0; }
    virtual DOMNode_implT* getNextSibling() const { return 0; }

    virtual DOMNode_implT* cloneNode(bool /*deep*/) const
    {
      AttrImpl* a = dynamic_cast<AttrImpl*>(NodeT::ownerDoc_->createAttribute(*name_));
      cloneChildren(a);
      a->setSpecified(getSpecified());
      return a;
    } // cloneNode

    virtual const stringT& getNodeName() const 
    {
      return *name_;
    } // getNodeName

    virtual const stringT& getNodeValue() const
    {
      if(!valueCalculated_)
      {
        value_ = string_adaptorT::construct_from_utf8("");
        for(DOMNode_implT* c = NodeT::getFirstChild(); c != 0; c = c->getNextSibling())
          string_adaptorT::append(value_, c->getNodeValue());
        valueCalculated_ = true;
      }
      return value_;
    } // getNodeValue

    virtual void setNodeValue(const stringT& data)
    {
      NodeT::throwIfReadOnly();

      // remove all children
      for(DOMNode_implT* c = NodeT::getFirstChild(); c != 0; c = NodeT::getFirstChild())
        NodeT::removeChild(c);

      // add a new text node
      NodeT::appendChild(new TextImpl<stringT, string_adaptorT>(0, data));

      valueCalculated_ = false;
      specified_ = true;
    } // setNodeValue

    /////////////////////////////////////////////////////////////
    // this implementation
    void setOwnerElement(ElementImplT* element)
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
      for(DOMNode_implT* c = NodeT::getFirstChild(); c != 0; c = c->getNextSibling())
        clone->appendChild(c->cloneNode(true));
    } // cloneChildren

  private:
    virtual void checkChildType(DOMNode_implT* child)
    {
      typename DOM::Node_base::Type type = child->getNodeType();
      if((type != DOM::Node_base::TEXT_NODE) && 
         (type != DOM::Node_base::ENTITY_REFERENCE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

  protected:
    stringT const* name_;
    ElementImplT* ownerElement_;
    bool specified_;
    mutable bool valueCalculated_;
    mutable stringT value_;
}; // class CDATAImpl

} // namespace SimpleDOM
} // namespace Arabica

#endif
