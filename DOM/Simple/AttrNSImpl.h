#ifndef JEZUK_SimpleDOM_ATTRNSIMPL_H
#define JEZUK_SimpleDOM_ATTRNSIMPL_H

#include <DOM/Simple/AttrImpl.h>
#include <DOM/Simple/Helpers.h>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class AttrNSImpl : public AttrImpl<stringT, string_adaptorT>
{
    typedef typename string_adaptorT::size_type size_type;
    typedef AttrImpl<stringT, string_adaptorT> AttrT;
	
  public:
    AttrNSImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc,
               const stringT& namespaceURI,
               bool hasNamespaceURI,
               const stringT& qualifiedName) : 
        AttrImpl<stringT, string_adaptorT>(ownerDoc, qualifiedName),
        hasNamespaceURI_(false)
    { 
      string_adaptorT SA;
      bool hasPrefix = false;
      stringT prefix;
      size_type index = string_adaptorT::find(qualifiedName, SA.makeStringT(":"));

      if(index == string_adaptorT::npos) 
      {	//qualifiedName contains no ':'
	      localName_ = qualifiedName;
        if(localName_ == SA.makeStringT("xmlns"))
        {
          hasPrefix = true;
          prefix = localName_;
        } // 
      } 
      else 
      {	
        hasPrefix = true;
        prefix = string_adaptorT::substr(qualifiedName, 0, index);
	      localName_ = string_adaptorT::substr(qualifiedName, index+1);
      }

      std::pair<bool, stringT> mappedURI = 
        checkPrefixAndNamespace<stringT, string_adaptorT>(hasPrefix, prefix, hasNamespaceURI, namespaceURI, DOM::Node<stringT>::ATTRIBUTE_NODE);

      hasNamespaceURI_ = mappedURI.first;
      namespaceURI_ = mappedURI.second;
    } // AttrImpl

    virtual ~AttrNSImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      AttrNSImpl* clone = dynamic_cast<AttrNSImpl*>(AttrT::ownerDoc_->createAttributeNS(namespaceURI_, AttrT::name_));
      AttrT::cloneChildren(clone);
      clone->setSpecified(AttrT::getSpecified());
      return clone;
    } // cloneNode

    virtual stringT getNamespaceURI() const 
    { 
      return namespaceURI_;
    } // getNamespaceURI

    virtual stringT getPrefix() const 
    { 
      string_adaptorT SA;
      size_type index = string_adaptorT::find(AttrT::name_, SA.makeStringT(":"));
      return (index != string_adaptorT::npos) ? string_adaptorT::substr(AttrT::name_, 0, index) : stringT();
    } // getPrefix
    
    virtual void setPrefix(const stringT& prefix) 
    {
      if(hasNamespaceURI_ == false) 
        throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);

      if(string_adaptorT::empty(prefix)) 
      {
        AttrT::name_ = localName_;
        return;
      } // empty prefix

      checkPrefixAndNamespace<stringT, string_adaptorT>(true, prefix, true, namespaceURI_, DOM::Node<stringT>::ATTRIBUTE_NODE);

      AttrT::name_ = prefix;
      string_adaptorT::append(AttrT::name_, string_adaptorT().makeStringT(":"));
      string_adaptorT::append(AttrT::name_, localName_);
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
      return (string_adaptorT::find(AttrT::name_, string_adaptorT().makeStringT(":")) != string_adaptorT::npos);
    } // hasPrefix

  private:
    stringT namespaceURI_;
    stringT localName_;
    bool hasNamespaceURI_;
}; // class AttrNSImpl


} // namespace SAX2DOM

#endif

