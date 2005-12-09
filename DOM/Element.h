#ifndef JEZUK_DOM_ELEMENT_H
#define JEZUK_DOM_ELEMENT_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.h>
#include <DOM/Attr.h>
#include <DOM/NamedNodeMap.h>

namespace DOM
{

template<class stringT> class Attr;
template<class stringT> class NodeList;
template<class stringT> class Element_impl;

template<class stringT> 
class Element : public Node<stringT>
{
    typedef Node<stringT> NodeT;
  public:
    Element() : Node<stringT>() { }
    explicit Element(Element_impl<stringT>* impl) : Node<stringT>(impl) { }
    Element(const Element& rhs) : Node<stringT>(rhs) { }
    explicit Element(const Node<stringT>& rhs) : Node<stringT>(rhs)  
    {
      if(rhs.getNodeType() != Node<stringT>::ELEMENT_NODE)
        throw std::bad_cast();
    } // Element

    const stringT& getTagName() const { return eImpl()->getTagName(); }

    stringT getAttribute(const stringT& name) const { return eImpl()->getAttribute(name); }
    void setAttribute(const stringT& name, const stringT& value) { eImpl()->setAttribute(name, value); } 
    void removeAttribute(const stringT& name) { eImpl()->removeAttribute(name); }

    Attr<stringT> getAttributeNode(const stringT& name) const { return Attr<stringT>(eImpl()->getAttributeNode(name)); }
    Attr<stringT> setAttributeNode(const Attr<stringT>& newAttr) { return Attr<stringT>(eImpl()->setAttributeNode(newAttr.attrImpl())); }
    Attr<stringT> removeAttributeNode(const Attr<stringT>& oldAttr) { return Attr<stringT>(eImpl()->removeAttributeNode(oldAttr.attrImpl())); }

    NodeList<stringT> getElementsByTagName(const stringT& tagName) const { return NodeList<stringT>(eImpl()->getElementsByTagName(tagName)); }

    stringT getAttributeNS(const stringT& namespaceURI, const stringT& localName) const  { return eImpl()->getAttributeNS(namespaceURI, localName); }
    void setAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName, const stringT& value) { eImpl()->setAttributeNS(namespaceURI, qualifiedName, value); }
    void removeAttributeNS(const stringT& namespaceURI, const stringT& localName) { return eImpl()->removeAttributeNS(namespaceURI, localName); }

    Attr<stringT> getAttributeNodeNS(const stringT& namespaceURI, const stringT& localName) const { return Attr<stringT>(eImpl()->getAttributeNodeNS(namespaceURI, localName)); }
    Attr<stringT> setAttributeNodeNS(const Attr<stringT>& newAttr) { return Attr<stringT>(eImpl()->getAttributeNodeNS(newAttr)); } 

    NodeList<stringT> getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const { return NodeList<stringT>(eImpl()->getElementsByTagNameNS(namespaceURI, localName)); }

    bool hasAttribute(const stringT& name) const { return eImpl()->hasAttribute(name); }

    bool hasAttributeNS(const stringT& namespaceURI, const stringT& localName) const { return eImpl()->hasAttributeNS(namespaceURI, localName); } 

  private:
    Element_impl<stringT>* eImpl() const { return dynamic_cast<Element_impl<stringT>*>(*NodeT::impl_); }
}; // class Element

///////////////////////////////////////////////////////////
template<class stringT>
class Element_impl : virtual public Node_impl<stringT>
{
  public:
    virtual ~Element_impl () { }

    ////////////////////////////////////////////////////////
    // DOM::Element 
    virtual const stringT& getTagName() const = 0;

    virtual stringT getAttribute(const stringT& name) const = 0;
    virtual void setAttribute(const stringT& name, const stringT& value) = 0;
    virtual void removeAttribute(const stringT& name) = 0;

    virtual Attr_impl<stringT>* getAttributeNode(const stringT& name) const = 0;
    virtual Attr_impl<stringT>* setAttributeNode(Attr_impl<stringT>* newAttr) = 0;
    virtual Attr_impl<stringT>* removeAttributeNode(Attr_impl<stringT>* oldAttr) = 0;

    virtual NodeList_impl<stringT>* getElementsByTagName(const stringT& tagName) const = 0;

    virtual stringT getAttributeNS(const stringT& namespaceURI, const stringT& localName) const = 0;
    virtual void setAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName, const stringT& value) = 0;
    virtual void removeAttributeNS(const stringT& namespaceURI, const stringT& localName) = 0;

    virtual Attr_impl<stringT>* getAttributeNodeNS(const stringT& namespaceURI, const stringT& localName) const = 0;
    virtual Attr_impl<stringT>* setAttributeNodeNS(Attr_impl<stringT>* newAttr) = 0;

    virtual NodeList_impl<stringT>* getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const = 0;

    virtual bool hasAttribute(const stringT& name) const = 0;

    virtual bool hasAttributeNS(const stringT& namespaceURI, const stringT& localName) const = 0;
}; // class Element_impl

} // namespace DOM

#endif
// end of file
