#ifndef JEZUK_SimpleDOM_ATTRMAP_H
#define JEZUK_SimpleDOM_ATTRMAP_H

#include <DOM/Simple/NamedNodeMapImpl.h>
#include <DOM/Simple/AttrImpl.h>
#include <DOM/Simple/AttrNSImpl.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class AttrMap : public NamedNodeMapImpl<stringT, string_adaptorT>
{
    typedef NamedNodeMapImpl<stringT, string_adaptorT> MapT;
  public:
    AttrMap(DocumentImpl<stringT, string_adaptorT>* ownerDoc) : 
        NamedNodeMapImpl<stringT, string_adaptorT>(ownerDoc),
        ownerElement_(0)
    { 
    } // AttrMap

    ~AttrMap() 
    { 
    } // ~AttrMap

    /////////////////////////////////////////////////////
    const stringT& getAttribute(const stringT& name) const
    {
      DOM::Node_impl<stringT>* attr = MapT::getNamedItem(name);
      return attr ? attr->getNodeValue() : MapT::ownerDoc_->empty_string();
    } // getAttribute

    void setAttribute(const stringT& name, const stringT& value)    
    {
      AttrImpl<stringT, string_adaptorT>* a = new AttrImpl<stringT, string_adaptorT>(MapT::ownerDoc_, name, value);
      a->setOwnerElement(ownerElement_);
      MapT::setNamedItem(a);
    } // setAttribute

    void removeAttribute(const stringT& name)    
    {
      MapT::removeNamedItem(name);
      createDefault(name);
    } // removeAttribute

    DOM::Attr_impl<stringT>* getAttributeNode(const stringT& name) const    
    {
      return dynamic_cast<DOM::Attr_impl<stringT>*>(MapT::getNamedItem(name));
    } // getAttributeNode

    DOM::Attr_impl<stringT>* setAttributeNode(DOM::Attr_impl<stringT>* newAttr)
    {
      dynamic_cast<AttrImpl<stringT, string_adaptorT>*>(newAttr)->setOwnerElement(ownerElement_);
      return dynamic_cast<DOM::Attr_impl<stringT>*>(MapT::setNamedItem(newAttr));
    } // setAttributeNode

    DOM::Attr_impl<stringT>* removeAttributeNode(DOM::Attr_impl<stringT>* oldAttr)    
    {
      if(MapT::removeNamedItem(oldAttr->getNodeName()) == 0)
        throw DOM::DOMException(DOM::DOMException::NOT_FOUND_ERR);
      createDefault(oldAttr->getNodeName());
      return oldAttr;
    } // removeAttributeNode

    stringT getAttributeNS(const stringT& namespaceURI, const stringT& localName) const    
    {
      DOM::Node_impl<stringT>* attr = MapT::getNamedItemNS(namespaceURI, localName);
      return attr ? attr->getNodeValue() : stringT();
    } // getAttributeNS

    void setAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName, const stringT& value)    
    {
      AttrNSImpl<stringT, string_adaptorT>* a = 
        new AttrNSImpl<stringT, string_adaptorT>(MapT::ownerDoc_, 
                                                 namespaceURI, 
                                                 !string_adaptorT::empty(namespaceURI), 
                                                 qualifiedName);
      a->setValue(value);
      a->setOwnerElement(ownerElement_);
      MapT::setNamedItemNS(a);
    } // setAttributeNS

    void removeAttributeNS(const stringT& namespaceURI, const stringT& localName)    
    {
      MapT::removeNamedItemNS(namespaceURI, localName);
      createDefault(namespaceURI, localName);
    } // removeAttributeNS

    DOM::Attr_impl<stringT>* getAttributeNodeNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return dynamic_cast<DOM::Attr_impl<stringT>*>(MapT::getNamedItemNS(namespaceURI, localName));
    } // getAttributeNodeNS

    DOM::Attr_impl<stringT>* setAttributeNodeNS(DOM::Attr_impl<stringT>* newAttr)    
    {
      dynamic_cast<AttrImpl<stringT, string_adaptorT>*>(newAttr)->setOwnerElement(ownerElement_);
      return dynamic_cast<DOM::Attr_impl<stringT>*>(MapT::setNamedItemNS(newAttr));
    } // setAttributeNodeNS

    bool hasAttribute(const stringT& name) const    
    {
      return (MapT::getNamedItem(name) != 0);
    } // hasAttribute

    bool hasAttributeNS(const stringT& namespaceURI, const stringT& localName) const    
    {
      return (MapT::getNamedItemNS(namespaceURI, localName) != 0);
    } // hasAttributeNS

    void setOwnerElement(ElementImpl<stringT, string_adaptorT>* element)
    {
      ownerElement_ = element;
      getDefaults();
    } // setOwnerElement

    virtual void setOwnerDoc(DocumentImpl<stringT, string_adaptorT>* ownerDoc)
    {
      NamedNodeMapImpl<stringT, string_adaptorT>::setOwnerDoc(ownerDoc);
      getDefaults();
    } // setOwnerDoc

  private:
    void createDefault(const stringT& name) 
    {
      DOM::NamedNodeMap_impl<stringT>* attrs = getDefaultAttrs();
      if(attrs)
      {
        DOM::Node_impl<stringT>* attr = attrs->getNamedItem(name);
        if(attr)
          setAttributeNode(dynamic_cast<DOM::Attr_impl<stringT>*>(attr->cloneNode(true)));
      }
    } // createDefault

    void createDefault(const stringT& namespaceURI, const stringT& localName) 
    {
      DOM::NamedNodeMap_impl<stringT>* attrs = getDefaultAttrs();
      if(attrs)
      {
        DOM::Node_impl<stringT>* attr = attrs->getNamedItemNS(namespaceURI, localName);
        if(attr)
          setAttributeNodeNS(dynamic_cast<DOM::Attr_impl<stringT>*>(attr->cloneNode(true)));
      } 
    } // createDefault

    void getDefaults()
    {
      DOM::NamedNodeMap_impl<stringT>* attrs = getDefaultAttrs();
      if(attrs)
      {
        for(unsigned int i = 0; i < attrs->getLength(); ++i)
        {
          DOM::Node_impl<stringT>* attr = attrs->item(i);
          if(getAttributeNodeNS(attr->getNamespaceURI(), attr->getNodeName()) == 0)
            setAttributeNodeNS(dynamic_cast<DOM::Attr_impl<stringT>*>(attr->cloneNode(true)));
        }
      } 
    } // getDefaults

    DOM::NamedNodeMap_impl<stringT>* getDefaultAttrs()
    {
      if(!MapT::ownerDoc_)
        return 0;

      DocumentTypeImpl<stringT, string_adaptorT>* docType = dynamic_cast<DocumentTypeImpl<stringT, string_adaptorT>*>(MapT::ownerDoc_->getDoctype());
      if(docType)
      {
        DOM::Node_impl<stringT>* exemplar = docType->getElements()->getNamedItem(ownerElement_->getNodeName());
        if(exemplar)
          return exemplar->getAttributes();
      }
      return 0;
    } // getDefaultAttrs

    ElementImpl<stringT, string_adaptorT>* ownerElement_;
}; // class AttrMap


} // namespace SAX2DOM

#endif

