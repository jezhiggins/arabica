#ifndef JEZUK_SimpleDOM_ELEMENTNSIMPL_H
#define JEZUK_SimpleDOM_ELEMENTNSIMPL_H

#include <DOM/Simple/ElementImpl.h>
#include <DOM/Simple/Helpers.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class ElementNSImpl : public ElementImpl<stringT, string_adaptorT>
{
    typedef typename stringT::size_type size_type;
    typedef ElementImpl<stringT, string_adaptorT> ElementImplT;
  public:
    ElementNSImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc,
                const stringT& namespaceURI,
                bool hasNamespaceURI,
                const stringT& qualifiedName) : 
        ElementImpl<stringT, string_adaptorT>(ownerDoc, qualifiedName),
        hasNamespaceURI_(false)
    { 
      string_adaptorT SA;
      bool hasPrefix = false;
      stringT prefix;
      size_type index = qualifiedName.find(SA.makeStringT(":"));

      if(index == stringT::npos) 
      { //qualifiedName contains no ':'
        localName_ = qualifiedName;
      } 
      else 
      {	
        hasPrefix = true;
        prefix = qualifiedName.substr(0, index);
        localName_ = qualifiedName.substr(index+1);
      }

      std::pair<bool, stringT> mappedURI = 
        checkPrefixAndNamespace<stringT, string_adaptorT>(hasPrefix, prefix, hasNamespaceURI, namespaceURI, DOM::Node<stringT>::ELEMENT_NODE);

      hasNamespaceURI_ = mappedURI.first;
      namespaceURI_ = mappedURI.second;
    } // ElementImpl

    virtual ~ElementNSImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      ElementNSImpl* clone =  dynamic_cast<ElementNSImpl*>(ElementImplT::ownerDoc_->createElementNS(namespaceURI_, ElementImplT::tagName_));
      ElementImplT::cloneChildren(clone, deep);
      return clone;
    } // cloneNode

    virtual stringT getNamespaceURI() const 
    { 
      return namespaceURI_;
    } // getNamespaceURI

    virtual stringT getPrefix() const 
    { 
      string_adaptorT SA;
      size_type index = ElementImplT::tagName_.find(SA.makeStringT(":"));
      return (index != stringT::npos) ? ElementImplT::tagName_.substr(0, index) : stringT();
    } // getPrefix
    
    virtual void setPrefix(const stringT& prefix) 
    {
      ElementImplT::throwIfReadOnly();

      if(hasNamespaceURI_ == false) 
        throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);

      if(prefix.empty()) 
      {
        ElementImplT::tagName_ = localName_;
        return;
      } // empty prefix

      checkPrefixAndNamespace<stringT, string_adaptorT>(true, prefix, true, namespaceURI_, DOM::Node<stringT>::ELEMENT_NODE);

      string_adaptorT SA;
      ElementImplT::tagName_ = prefix + SA.makeStringT(":") + localName_; 
    } // setPrefix

    virtual stringT getLocalName() const 
    { 
      return localName_;
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
      string_adaptorT SA;
      return (ElementImplT::tagName_.find(SA.makeStringT(":")) != stringT::npos);
    } // hasPrefix

  private:
    stringT namespaceURI_;
    stringT localName_;
    bool hasNamespaceURI_;
}; // class ElementImpl


} // namespace SAX2DOM

#endif

