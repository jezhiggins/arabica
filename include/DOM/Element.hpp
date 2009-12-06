#ifndef JEZUK_DOM_ELEMENT_H
#define JEZUK_DOM_ELEMENT_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////

#include <DOM/Node.hpp>
#include <DOM/Attr.hpp>
#include <DOM/NamedNodeMap.hpp>

namespace Arabica
{
namespace DOM
{

template<class stringT, class string_adaptorT> class Attr;
template<class stringT, class string_adaptorT> class NodeList;
template<class stringT, class string_adaptorT> class Element_impl;

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> > 
class Element : public Node<stringT, string_adaptorT>
{
    typedef Element_impl<stringT, string_adaptorT> Element_implT;
  public:
    typedef Node<stringT, string_adaptorT> NodeT;
    typedef NodeList<stringT, string_adaptorT> NodeListT;
    typedef Attr<stringT, string_adaptorT> AttrT;

    Element() : NodeT() { }
    explicit Element(Element_implT* impl) : NodeT(impl) { }
    Element(const Element& rhs) : NodeT(rhs) { }
    explicit Element(const NodeT& rhs) : NodeT(rhs)  
    {
      if(rhs.getNodeType() != NodeT::ELEMENT_NODE)
        throw std::bad_cast();
    } // Element

    const stringT& getTagName() const { return eImpl()->getTagName(); }

    const stringT& getAttribute(const stringT& name) const { return eImpl()->getAttribute(name); }
    void setAttribute(const stringT& name, const stringT& value) { eImpl()->setAttribute(name, value); } 
    void removeAttribute(const stringT& name) { eImpl()->removeAttribute(name); }

    AttrT getAttributeNode(const stringT& name) const { return AttrT(eImpl()->getAttributeNode(name)); }
    AttrT setAttributeNode(const AttrT& newAttr) { return AttrT(eImpl()->setAttributeNode(newAttr.attrImpl())); }
    AttrT removeAttributeNode(const AttrT& oldAttr) { return AttrT(eImpl()->removeAttributeNode(oldAttr.attrImpl())); }

    NodeListT getElementsByTagName(const stringT& tagName) const { return NodeListT(eImpl()->getElementsByTagName(tagName)); }

    stringT getAttributeNS(const stringT& namespaceURI, const stringT& localName) const  { return eImpl()->getAttributeNS(namespaceURI, localName); }
    void setAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName, const stringT& value) { eImpl()->setAttributeNS(namespaceURI, qualifiedName, value); }
    void removeAttributeNS(const stringT& namespaceURI, const stringT& localName) { return eImpl()->removeAttributeNS(namespaceURI, localName); }

    AttrT getAttributeNodeNS(const stringT& namespaceURI, const stringT& localName) const { return AttrT(eImpl()->getAttributeNodeNS(namespaceURI, localName)); }
    AttrT setAttributeNodeNS(const AttrT& newAttr) { return AttrT(eImpl()->setAttributeNodeNS(newAttr.attrImpl())); } 

    NodeListT getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const { return NodeListT(eImpl()->getElementsByTagNameNS(namespaceURI, localName)); }

    bool hasAttribute(const stringT& name) const { return eImpl()->hasAttribute(name); }

    bool hasAttributeNS(const stringT& namespaceURI, const stringT& localName) const { return eImpl()->hasAttributeNS(namespaceURI, localName); } 

  private:
    Element_implT* eImpl() const { return dynamic_cast<Element_implT*>(*NodeT::impl_); }
}; // class Element

///////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT>
class Element_impl : virtual public Node_impl<stringT, string_adaptorT>
{
  public:
    typedef NodeList_impl<stringT, string_adaptorT> NodeList_implT;
    typedef Attr_impl<stringT, string_adaptorT> Attr_implT;

    virtual ~Element_impl () { }

    ////////////////////////////////////////////////////////
    // DOM::Element 
    virtual const stringT& getTagName() const = 0;

    virtual const stringT& getAttribute(const stringT& name) const = 0;
    virtual void setAttribute(const stringT& name, const stringT& value) = 0;
    virtual void removeAttribute(const stringT& name) = 0;

    virtual Attr_implT* getAttributeNode(const stringT& name) const = 0;
    virtual Attr_implT* setAttributeNode(Attr_implT* newAttr) = 0;
    virtual Attr_implT* removeAttributeNode(Attr_implT* oldAttr) = 0;

    virtual NodeList_implT* getElementsByTagName(const stringT& tagName) const = 0;

    virtual stringT getAttributeNS(const stringT& namespaceURI, const stringT& localName) const = 0;
    virtual void setAttributeNS(const stringT& namespaceURI, const stringT& qualifiedName, const stringT& value) = 0;
    virtual void removeAttributeNS(const stringT& namespaceURI, const stringT& localName) = 0;

    virtual Attr_implT* getAttributeNodeNS(const stringT& namespaceURI, const stringT& localName) const = 0;
    virtual Attr_implT* setAttributeNodeNS(Attr_implT* newAttr) = 0;

    virtual NodeList_implT* getElementsByTagNameNS(const stringT& namespaceURI, const stringT& localName) const = 0;

    virtual bool hasAttribute(const stringT& name) const = 0;

    virtual bool hasAttributeNS(const stringT& namespaceURI, const stringT& localName) const = 0;
}; // class Element_impl

} // namespace DOM
} // namespace Arabica
#endif
// end of file
