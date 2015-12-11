#ifndef JEZUK_SimpleDOM_ELEMENTIMPL_H
#define JEZUK_SimpleDOM_ELEMENTIMPL_H

#include <DOM/Element.hpp>
#include <DOM/Simple/NodeImpl.hpp>
#include <DOM/Simple/ElementByTagImpl.hpp>
#include <DOM/Simple/AttrMap.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class ElementImpl : public DOM::Element_impl<stringT, string_adaptorT>,
                    public NodeImplWithChildren<stringT, string_adaptorT>
{
  protected:
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeT;
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;
    typedef AttrMap<stringT, string_adaptorT> AttrMapT;
    typedef ElementByTagList<stringT, string_adaptorT> ElementByTagListT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::Attr_impl<stringT, string_adaptorT> DOMAttr_implT;
    typedef DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;
    typedef DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;
    typedef DOM::Element_impl<stringT, string_adaptorT> DOMElement_implT;

  public:
    ElementImpl(DocumentImplT* ownerDoc, const stringT& tagName) :
        DOMElement_implT(),
        NodeT(ownerDoc),
        attributes_(ownerDoc),
        tagName_(ownerDoc->stringPool(tagName))
    {
      attributes_.setOwnerElement(this);
    } // ElementImpl

    virtual ~ElementImpl()
    {
    } // ~ElementImpl

    /////////////////////////////////////////////////////
    // DOM::Element functions
    virtual const stringT& getTagName() const { return getNodeName(); }

    virtual const stringT& getAttribute(const stringT& name) const
    {
      return attributes_.getAttribute(name);
    } // getAttribute

    virtual void setAttribute(const stringT& name, const stringT& value)
    {
      this->checkName(name);
      stringT oldValue = getAttribute(name);
      attributes_.setAttribute(name, value);
    } // setAttribute

    virtual void removeAttribute(const stringT& name)
    {
      stringT oldValue = getAttribute(name);
      attributes_.removeAttribute(name);
    } // removeAttribute

    virtual DOMAttr_implT* getAttributeNode(const stringT& name) const
    {
      return attributes_.getAttributeNode(name);
    } // getAttributeNode

    virtual DOMAttr_implT* setAttributeNode(DOMAttr_implT* newAttr)
    {
      return attributes_.setAttributeNode(newAttr);
    } // setAttributeNode

    virtual DOMAttr_implT* removeAttributeNode(DOMAttr_implT* oldAttr)
    {
      return attributes_.removeAttributeNode(oldAttr);
    } // removeAttributeNode

    virtual DOMNodeList_implT* getElementsByTagName(const stringT& tagName) const
    {
      return new ElementByTagListT(NodeT::ownerDoc_,
                                   const_cast<ElementImpl*>(this),
                                   tagName);
    } // getElementsByTagName

    virtual stringT getAttributeNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return attributes_.getAttributeNS(namespaceURI, localName);
    } // getAttributeNS

    virtual void setAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName, const stringT& value)
    {
      this->checkName(qualifiedName);
      attributes_.setAttributeNS(namespaceURI, qualifiedName, value);
    } // setAttributeNS

    virtual void removeAttributeNS(const stringT& namespaceURI, const stringT& localName)
    {
      attributes_.removeAttributeNS(namespaceURI, localName);
    } // removeAttributeNS

    virtual DOMAttr_implT* getAttributeNodeNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return attributes_.getAttributeNodeNS(namespaceURI, localName);
    } // getAttributeNodeNS

    virtual DOMAttr_implT* setAttributeNodeNS(DOMAttr_implT* newAttr)
    {
      return attributes_.setAttributeNodeNS(newAttr);
    } // setAttributeNodeNS

    virtual DOMNodeList_implT* getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return new ElementByTagListT(NodeT::ownerDoc_,
                                   const_cast<ElementImpl*>(this),
                                   namespaceURI,
                                   localName);
    } // getElementsByTagNameNS

    virtual bool hasAttribute(const stringT& name) const
    {
      return attributes_.hasAttribute(name);
    } // hasAttribute

    virtual bool hasAttributeNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return attributes_.hasAttributeNS(namespaceURI, localName);
    } // hasAttributeNS

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return DOM::Node_base::ELEMENT_NODE;
    } // getNodeType

    virtual const stringT& getNodeName() const
    {
      return *tagName_;
    } // getNodeName

    virtual DOMNamedNodeMap_implT* getAttributes() const
    {
      return const_cast<AttrMapT*>(&attributes_);
    } // getAttributes

    virtual DOMNode_implT* cloneNode(bool deep) const
    {
      ElementImpl* clone = dynamic_cast<ElementImpl*>(NodeT::ownerDoc_->createElement(*tagName_));
      cloneChildren(clone, deep);
      return clone;
    } // cloneNode

    virtual bool hasAttributes() const
    {
      return (attributes_.getLength() > 0);
    } // hasAttributes

    virtual void setOwnerDoc(DocumentImplT* ownerDoc)
    {
      attributes_.setOwnerDoc(ownerDoc);
      NodeT::setOwnerDoc(ownerDoc);
    } // setOwnerDoc

    virtual void setReadOnly(bool readOnly)
    {
      attributes_.setReadOnly(readOnly);
      NodeT::setReadOnly(readOnly);
    } // setReadOnly

  protected:
    void cloneChildren(ElementImpl* clone, bool deep) const
    {
      for(unsigned int i = 0; i < attributes_.getLength(); ++i)
      {
        DOMAttr_implT* a = dynamic_cast<DOMAttr_implT*>(attributes_.item(i));
        if(a->getSpecified())
        {
          DOMAttr_implT* newA = dynamic_cast<DOMAttr_implT*>(a->cloneNode(true));
          if(string_adaptorT::empty(a->getLocalName()))
            clone->setAttributeNode(newA);
          else
            clone->setAttributeNodeNS(newA);
        } // if ...
      } // for

      if(deep)
        for(DOMNode_implT* c = NodeT::getFirstChild(); c != 0; c = c->getNextSibling())
          clone->appendChild(c->cloneNode(true));
    } // cloneChildren

  private:
    virtual void checkChildType(DOMNode_implT* child)
    {
      typename DOM::Node_base::Type type = child->getNodeType();
      if((type != DOM::Node_base::ELEMENT_NODE) &&
         (type != DOM::Node_base::TEXT_NODE) &&
         (type != DOM::Node_base::COMMENT_NODE) &&
         (type != DOM::Node_base::PROCESSING_INSTRUCTION_NODE) &&
         (type != DOM::Node_base::CDATA_SECTION_NODE) &&
         (type != DOM::Node_base::ENTITY_REFERENCE_NODE))
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

    AttrMapT attributes_;
  protected:
    stringT const* tagName_;
}; // class ElementImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif
