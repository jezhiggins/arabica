#ifndef JEZUK_SimpleDOM_ELEMENTIMPL_H
#define JEZUK_SimpleDOM_ELEMENTIMPL_H

#include <DOM/Element.h>
#include <DOM/Simple/NodeImpl.h>
#include <DOM/Simple/ElementByTagImpl.h>
#include <DOM/Simple/AttrMap.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class ElementImpl : public DOM::Element_impl<stringT>,
                    public NodeImplWithChildren<stringT, string_adaptorT>
{
  protected:
    typedef NodeImplWithChildren<stringT, string_adaptorT> NodeT;

  public:
    ElementImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc, const stringT& tagName) : 
        DOM::Element_impl<stringT>(),
        NodeImplWithChildren<stringT, string_adaptorT>(ownerDoc),
        attributes_(ownerDoc),
        tagName_(tagName)
    { 
      attributes_.setOwnerElement(this);
    } // ElementImpl

    virtual ~ElementImpl() 
    { 
    } // ~ElementImpl

    /////////////////////////////////////////////////////
    // DOM::Element functions
    virtual stringT getTagName() const { return getNodeName(); }

    virtual stringT getAttribute(const stringT& name) const
    {
      return attributes_.getAttribute(name);
    } // getAttribute

    virtual void setAttribute(const stringT& name, const stringT& value)    
    {
      attributes_.setAttribute(name, value);
    } // setAttribute

    virtual void removeAttribute(const stringT& name)    
    {
      attributes_.removeAttribute(name);
    } // removeAttribute

    virtual DOM::Attr_impl<stringT>* getAttributeNode(const stringT& name) const    
    {
      return attributes_.getAttributeNode(name);
    } // getAttributeNode

    virtual DOM::Attr_impl<stringT>* setAttributeNode(DOM::Attr_impl<stringT>* newAttr)
    {
      return attributes_.setAttributeNode(newAttr);
    } // setAttributeNode

    virtual DOM::Attr_impl<stringT>* removeAttributeNode(DOM::Attr_impl<stringT>* oldAttr)    
    {
      return attributes_.removeAttributeNode(oldAttr);
    } // removeAttributeNode

    virtual DOM::NodeList_impl<stringT>* getElementsByTagName(const stringT& tagName) const    
    {
      return new ElementByTagList<stringT, string_adaptorT>(NodeT::ownerDoc_,
                                                            const_cast<ElementImpl*>(this),
                                                            tagName);
    } // getElementsByTagName

    virtual stringT getAttributeNS(const stringT& namespaceURI, const stringT& localName) const    
    {
      return attributes_.getAttributeNS(namespaceURI, localName);
    } // getAttributeNS

    virtual void setAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName, const stringT& value)    
    {
      attributes_.setAttributeNS(namespaceURI, qualifiedName, value);
    } // setAttributeNS

    virtual void removeAttributeNS(const stringT& namespaceURI, const stringT& localName)    
    {
      attributes_.removeAttributeNS(namespaceURI, localName);
    } // removeAttributeNS

    virtual DOM::Attr_impl<stringT>* getAttributeNodeNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return attributes_.getAttributeNodeNS(namespaceURI, localName);
    } // getAttributeNodeNS

    virtual DOM::Attr_impl<stringT>* setAttributeNodeNS(DOM::Attr_impl<stringT>* newAttr)    
    {
      return attributes_.setAttributeNodeNS(newAttr);
    } // setAttributeNodeNS

    virtual DOM::NodeList_impl<stringT>* getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const    
    {
      return new ElementByTagList<stringT, string_adaptorT>(NodeT::ownerDoc_,
                                                            const_cast<ElementImpl*>(this),
                                                            namespaceURI, localName);
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

    virtual stringT getNodeName() const
    {
      return tagName_;
    } // getNodeName

    virtual DOM::NamedNodeMap_impl<stringT>* getAttributes() const
    {
      return const_cast<AttrMap<stringT, string_adaptorT>*>(&attributes_);
    } // getAttributes

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      ElementImpl* clone = dynamic_cast<ElementImpl*>(NodeT::ownerDoc_->createElement(tagName_));
      cloneChildren(clone, deep);
      return clone;
    } // cloneNode

    virtual bool hasAttributes() const
    {
      return (attributes_.getLength() > 0);
    } // hasAttributes

    virtual void setOwnerDoc(DocumentImpl<stringT, string_adaptorT>* ownerDoc)
    {
      attributes_.setOwnerDoc(ownerDoc);
      NodeImplWithChildren<stringT, string_adaptorT>::setOwnerDoc(ownerDoc);
    } // setOwnerDoc

    virtual void setReadOnly(bool readOnly)
    {
      attributes_.setReadOnly(readOnly);
      NodeImplWithChildren<stringT, string_adaptorT>::setReadOnly(readOnly);
    } // setReadOnly

  protected:
    void cloneChildren(ElementImpl* clone, bool deep) const
    {
      for(unsigned int i = 0; i < attributes_.getLength(); ++i)
      {
        DOM::Attr_impl<stringT>* a = dynamic_cast<DOM::Attr_impl<stringT>*>(attributes_.item(i));
        if(a->getSpecified())
        {
          DOM::Attr_impl<stringT>* newA = dynamic_cast<DOM::Attr_impl<stringT>*>(a->cloneNode(true));
          if(a->getLocalName().empty())
            clone->setAttributeNode(newA);
          else
            clone->setAttributeNodeNS(newA);
        } // if ...
      } // for

      if(deep)
        for(DOM::Node_impl<stringT>* c = NodeT::getFirstChild(); c != 0; c = c->getNextSibling())
          clone->appendChild(c->cloneNode(true));
    } // cloneChildren

  private:
    virtual void checkChildType(DOM::Node_impl<stringT>* child)
    {
      typename DOM::Node<stringT>::Type type = child->getNodeType();
      if((type != DOM::Node<stringT>::ELEMENT_NODE) && 
         (type != DOM::Node<stringT>::TEXT_NODE) && 
         (type != DOM::Node<stringT>::COMMENT_NODE) && 
         (type != DOM::Node<stringT>::PROCESSING_INSTRUCTION_NODE) && 
         (type != DOM::Node<stringT>::CDATA_SECTION_NODE) && 
         (type != DOM::Node<stringT>::ENTITY_REFERENCE_NODE)) 
        throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // checkChildType

    AttrMap<stringT, string_adaptorT> attributes_;
  protected:
    stringT tagName_;
}; // class ElementImpl


} // namespace SAX2DOM

#endif

