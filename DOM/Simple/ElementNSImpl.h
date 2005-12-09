#ifndef JEZUK_SimpleDOM_ELEMENTNSIMPL_H
#define JEZUK_SimpleDOM_ELEMENTNSIMPL_H

#include <DOM/Simple/ElementImpl.h>
#include <DOM/Simple/Helpers.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class ElementNSImpl : public ElementImpl<stringT, string_adaptorT>
{
    typedef typename string_adaptorT::size_type size_type;
    typedef ElementImpl<stringT, string_adaptorT> ElementImplT;
  public:
    ElementNSImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc,
                const stringT& namespaceURI,
                bool hasNamespaceURI,
                const stringT& qualifiedName) : 
        ElementImpl<stringT, string_adaptorT>(ownerDoc, qualifiedName),
        hasNamespaceURI_(false)
    { 
      bool hasPrefix = false;
      stringT prefix;
      size_type index = string_adaptorT::find(qualifiedName, string_adaptorT::construct_from_utf8(":"));

      if(index == string_adaptorT::npos) 
      { //qualifiedName contains no ':'
        localName_ = ElementImplT::ownerDoc_->stringPool(qualifiedName);
      } 
      else 
      {	
        hasPrefix = true;
        prefix = string_adaptorT::substr(qualifiedName, 0, index);
        localName_ = ElementImplT::ownerDoc_->stringPool(string_adaptorT::substr(qualifiedName, index+1));
      }

      std::pair<bool, stringT> mappedURI = 
        checkPrefixAndNamespace<stringT, string_adaptorT>(hasPrefix, prefix, hasNamespaceURI, namespaceURI, DOM::Node<stringT>::ELEMENT_NODE);

      hasNamespaceURI_ = mappedURI.first;
      namespaceURI_ = ElementImplT::ownerDoc_->stringPool(mappedURI.second);
    } // ElementImpl

    virtual ~ElementNSImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      ElementNSImpl* clone =  dynamic_cast<ElementNSImpl*>(ElementImplT::ownerDoc_->createElementNS(*namespaceURI_, ElementImplT::getNodeName()));
      ElementImplT::cloneChildren(clone, deep);
      return clone;
    } // cloneNode

    virtual stringT getNamespaceURI() const 
    { 
      return *namespaceURI_;
    } // getNamespaceURI

    virtual stringT getPrefix() const 
    { 
      size_type index = string_adaptorT::find(ElementImplT::getNodeName(), string_adaptorT::construct_from_utf8(":"));
      return (index != string_adaptorT::npos) ? string_adaptorT::substr(ElementImplT::getNodeName(), 0, index) : stringT();
    } // getPrefix
    
    virtual void setPrefix(const stringT& prefix) 
    {
      ElementImplT::throwIfReadOnly();

      if(hasNamespaceURI_ == false) 
        throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);

      if(string_adaptorT::empty(prefix)) 
      {
        ElementImplT::tagName_ = localName_;
        return;
      } // empty prefix

      checkPrefixAndNamespace<stringT, string_adaptorT>(true, prefix, true, *namespaceURI_, DOM::Node<stringT>::ELEMENT_NODE);

      stringT newTagName = prefix;
      string_adaptorT::append(newTagName, string_adaptorT::construct_from_utf8(":"));
      string_adaptorT::append(newTagName, *localName_);

      ElementImplT::tagName_ = ElementImplT::ownerDoc_->stringPool(newTagName);
    } // setPrefix

    virtual stringT getLocalName() const 
    { 
      return *localName_;
    } // getLocalName

    // additional three methods - since C++ std::string (and by implication
    // stringT) don't differenciate between a null string and an empty string,
    // but the DOM recommendation does, I have to introduce these three methods 
    // to disambiguate.  If they return false, the corresponding attribute should be
    // considered null.  If they return true, the attribute has been set EVEN IF 
    // it has been set to the empty string
    virtual bool hasNamespaceURI() const 
    { 
      return hasNamespaceURI_;
    } // hasNamespaceURI

    virtual bool hasPrefix() const 
    { 
      return (string_adaptorT::find(ElementImplT::getNodeName(), string_adaptorT::construct_from_utf8(":")) != string_adaptorT::npos);
    } // hasPrefix

  private:
    stringT const* namespaceURI_;
    stringT const* localName_;
    bool hasNamespaceURI_;
}; // class ElementImpl


} // namespace SAX2DOM

#endif

