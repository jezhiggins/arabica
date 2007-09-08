#ifndef JEZUK_SimpleDOM_ATTRMAP_H
#define JEZUK_SimpleDOM_ATTRMAP_H

#include <DOM/Simple/NamedNodeMapImpl.hpp>
#include <DOM/Simple/AttrImpl.hpp>
#include <DOM/Simple/AttrNSImpl.hpp>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class AttrMap : public NamedNodeMapImpl<stringT, string_adaptorT>
{
  public:
    typedef NamedNodeMapImpl<stringT, string_adaptorT> NamedNodeMapImplT;
    typedef AttrImpl<stringT, string_adaptorT> AttrImplT;
    typedef AttrNSImpl<stringT, string_adaptorT> AttrNSImplT;
    typedef ElementImpl<stringT, string_adaptorT> ElementImplT;
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;
    typedef DocumentTypeImpl<stringT, string_adaptorT> DocumentTypeImplT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::Attr_impl<stringT, string_adaptorT> DOMAttr_implT;
    typedef DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;

    AttrMap(DocumentImplT* ownerDoc) : 
        NamedNodeMapImplT(ownerDoc),
        ownerElement_(0)
    { 
    } // AttrMap

    ~AttrMap() 
    { 
    } // ~AttrMap

    /////////////////////////////////////////////////////
    const stringT& getAttribute(const stringT& name) const
    {
      DOMNode_implT* attr = NamedNodeMapImplT::getNamedItem(name);
      return attr ? attr->getNodeValue() : NamedNodeMapImplT::ownerDoc_->empty_string();
    } // getAttribute

    void setAttribute(const stringT& name, const stringT& value)    
    {
      AttrImplT* a = new AttrImplT(NamedNodeMapImplT::ownerDoc_, name, value);
      a->setOwnerElement(ownerElement_);
      NamedNodeMapImplT::setNamedItem(a);
    } // setAttribute

    void removeAttribute(const stringT& name)    
    {
      NamedNodeMapImplT::removeNamedItem(name);
      createDefault(name);
    } // removeAttribute

    DOMAttr_implT* getAttributeNode(const stringT& name) const    
    {
      return dynamic_cast<DOMAttr_implT*>(NamedNodeMapImplT::getNamedItem(name));
    } // getAttributeNode

    DOMAttr_implT* setAttributeNode(DOMAttr_implT* newAttr)
    {
      dynamic_cast<AttrImplT*>(newAttr)->setOwnerElement(ownerElement_);
      return dynamic_cast<DOMAttr_implT*>(NamedNodeMapImplT::setNamedItem(newAttr));
    } // setAttributeNode

    DOMAttr_implT* removeAttributeNode(DOMAttr_implT* oldAttr)    
    {
      if(NamedNodeMapImplT::removeNamedItem(oldAttr->getNodeName()) == 0)
        throw DOM::DOMException(DOM::DOMException::NOT_FOUND_ERR);
      createDefault(oldAttr->getNodeName());
      return oldAttr;
    } // removeAttributeNode

    stringT getAttributeNS(const stringT& namespaceURI, const stringT& localName) const    
    {
      DOMNode_implT* attr = NamedNodeMapImplT::getNamedItemNS(namespaceURI, localName);
      return attr ? attr->getNodeValue() : stringT();
    } // getAttributeNS

    void setAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName, const stringT& value)    
    {
      AttrNSImplT* a = new AttrNSImplT(NamedNodeMapImplT::ownerDoc_, 
                                       namespaceURI, 
                                       !string_adaptorT::empty(namespaceURI), 
                                       qualifiedName);
      a->setValue(value);
      a->setOwnerElement(ownerElement_);
      NamedNodeMapImplT::setNamedItemNS(a);
    } // setAttributeNS

    void removeAttributeNS(const stringT& namespaceURI, const stringT& localName)    
    {
      NamedNodeMapImplT::removeNamedItemNS(namespaceURI, localName);
      createDefault(namespaceURI, localName);
    } // removeAttributeNS

    DOMAttr_implT* getAttributeNodeNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return dynamic_cast<DOMAttr_implT*>(NamedNodeMapImplT::getNamedItemNS(namespaceURI, localName));
    } // getAttributeNodeNS

    DOMAttr_implT* setAttributeNodeNS(DOMAttr_implT* newAttr)    
    {
      dynamic_cast<AttrImplT*>(newAttr)->setOwnerElement(ownerElement_);
      return dynamic_cast<DOMAttr_implT*>(NamedNodeMapImplT::setNamedItemNS(newAttr));
    } // setAttributeNodeNS

    bool hasAttribute(const stringT& name) const    
    {
      return (NamedNodeMapImplT::getNamedItem(name) != 0);
    } // hasAttribute

    bool hasAttributeNS(const stringT& namespaceURI, const stringT& localName) const    
    {
      return (NamedNodeMapImplT::getNamedItemNS(namespaceURI, localName) != 0);
    } // hasAttributeNS

    void setOwnerElement(ElementImplT* element)
    {
      ownerElement_ = element;
      getDefaults();
    } // setOwnerElement

    virtual void setOwnerDoc(DocumentImplT* ownerDoc)
    {
      NamedNodeMapImplT::setOwnerDoc(ownerDoc);
      getDefaults();
    } // setOwnerDoc

  private:
    void createDefault(const stringT& name) 
    {
      DOMNamedNodeMap_implT* attrs = getDefaultAttrs();
      if(attrs)
      {
        DOMNode_implT* attr = attrs->getNamedItem(name);
        if(attr)
          setAttributeNode(dynamic_cast<DOMAttr_implT*>(attr->cloneNode(true)));
      }
    } // createDefault

    void createDefault(const stringT& namespaceURI, const stringT& localName) 
    {
      DOMNamedNodeMap_implT* attrs = getDefaultAttrs();
      if(attrs)
      {
        DOMNode_implT* attr = attrs->getNamedItemNS(namespaceURI, localName);
        if(attr)
          setAttributeNodeNS(dynamic_cast<DOMAttr_implT*>(attr->cloneNode(true)));
      } 
    } // createDefault

    void getDefaults()
    {
      DOMNamedNodeMap_implT* attrs = getDefaultAttrs();
      if(attrs)
      {
        for(unsigned int i = 0; i < attrs->getLength(); ++i)
        {
          DOMNode_implT* attr = attrs->item(i);
          if(getAttributeNodeNS(attr->getNamespaceURI(), attr->getNodeName()) == 0)
            setAttributeNodeNS(dynamic_cast<DOMAttr_implT*>(attr->cloneNode(true)));
        }
      } 
    } // getDefaults

    DOMNamedNodeMap_implT* getDefaultAttrs()
    {
      if(!NamedNodeMapImplT::ownerDoc_)
        return 0;

      DocumentTypeImplT* docType = dynamic_cast<DocumentTypeImplT*>(NamedNodeMapImplT::ownerDoc_->getDoctype());
      if(docType)
      {
        DOMNode_implT* exemplar = docType->getElements()->getNamedItem(ownerElement_->getNodeName());
        if(exemplar)
          return exemplar->getAttributes();
      }
      return 0;
    } // getDefaultAttrs

    ElementImplT* ownerElement_;
}; // class AttrMap


} // namespace SAX2DOM
} // namespace Arabica

#endif

