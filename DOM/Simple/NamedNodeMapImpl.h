#ifndef JEZUK_SimpleDOM_NAMEDNODEMAPIMPL_H
#define JEZUK_SimpleDOM_NAMEDNODEMAPIMPL_H

#include <DOM/Simple/NodeImpl.h>
#include <DOM/NamedNodeMap.h>
#include <deque>
#include <algorithm>
#include <functional>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class nameIs : public std::unary_function<NodeImpl<stringT, string_adaptorT>*, bool>
{
  public:
    nameIs(const stringT& name) : name_(name) { }
    bool operator()(const NodeImpl<stringT, string_adaptorT>* node) const
    {
      return (node->getNodeName() == name_);
    } // operator()

  private:
    stringT name_;
}; // class nameIs

template<class stringT, class string_adaptorT>
class namespaceAndNameIs : public std::unary_function<NodeImpl<stringT, string_adaptorT>*, bool>
{
  public:
    namespaceAndNameIs(const stringT& namespaceURI, const stringT& localName) : 
      namespaceURI_(namespaceURI),
      localName_(localName) { }

    bool operator()(const NodeImpl<stringT, string_adaptorT>* node) const
    {
      if(namespaceURI_.empty())
      {
        if((node->hasNamespaceURI() == false) &&
           ((node->getLocalName() == localName_) ||
            (node->getLocalName().empty() && node->getNodeName() == localName_)
           )
          )
          return true;
      } // if(namespaceURI_.empty())

      if((node->getNamespaceURI() == namespaceURI_) && (node->getLocalName() == localName_))
        return true;

      return false;
    } // operator()

  private:
    stringT namespaceURI_;
    stringT localName_;
}; // class namespaceAndNameIs

template<class stringT, class string_adaptorT>
class NamedNodeMapImpl : public DOM::NamedNodeMap_impl<stringT>
{
  public:
    NamedNodeMapImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc) : 
        DOM::NamedNodeMap_impl<stringT>(),
				nodes_(),
        readOnly_(false),
        ownerDoc_(ownerDoc)
    { 
    } // NamedNodeMapImpl

    virtual ~NamedNodeMapImpl() 
    { 
      for(typename NodeListT::iterator i = nodes_.begin(); i != nodes_.end(); ++i)
        delete (*i);
    } // ~NodeImpl

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef()
    {
      if(ownerDoc_)
        ownerDoc_->addRef();
    } // addRef
    virtual void releaseRef() 
    {
      if(ownerDoc_)
        ownerDoc_->releaseRef();
    } // releaseRef
    virtual void setOwnerDoc(DocumentImpl<stringT, string_adaptorT>* ownerDoc)
    {
      ownerDoc_ = ownerDoc;
      for(typename NodeListT::iterator i = nodes_.begin(); i != nodes_.end(); ++i)
        (*i)->setOwnerDoc(ownerDoc);
    } // setOwnerDoc

    ///////////////////////////////////////////////////
    // DOM::NamedNodeMap methods
    virtual DOM::Node_impl<stringT>* getNamedItem(const stringT& name) const
    {
      return getNode(const_cast<NamedNodeMapImpl<stringT, string_adaptorT>*>(this)->findByName(name));
    } // getNamedItem

    virtual DOM::Node_impl<stringT>* setNamedItem(DOM::Node_impl<stringT>* arg)
    {
      throwIfReadOnly();
      return setNode(findByName(arg->getNodeName()), dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(arg));
    } // setNamedItem

    virtual DOM::Node_impl<stringT>* removeNamedItem(const stringT& name)
    {
      throwIfReadOnly();
      return removeNode(findByName(name));
    } // removedNamedItem

    virtual DOM::Node_impl<stringT>* item(unsigned int index) const
    {
      return do_item(index);
    } // item

    virtual unsigned int getLength() const
    {
      return nodes_.size();
    } // getLength

    virtual DOM::Node_impl<stringT>* getNamedItemNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return getNode(const_cast<NamedNodeMapImpl<stringT, string_adaptorT>*>(this)->findByNamespaceAndName(namespaceURI, localName));
    } // getNamedItemNS

    virtual DOM::Node_impl<stringT>* setNamedItemNS(DOM::Node_impl<stringT>* arg)
    {
      throwIfReadOnly();
      return setNode(findByNamespaceAndName(arg->getNamespaceURI(), arg->getLocalName()), dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(arg));
    } // setNamedItemNS

    virtual DOM::Node_impl<stringT>* removeNamedItemNS(const stringT& namespaceURI, const stringT& localName)
    {
      throwIfReadOnly();
      return removeNode(findByNamespaceAndName(namespaceURI, localName));
    } // removeNamedItemNS

    ///////////////////////////////////////////////////////
    // extensions
    void setReadOnly(bool readOnly)
    {
      readOnly_ = readOnly;
    } // setReadOnly

    NodeImpl<stringT, string_adaptorT>* do_item(unsigned int index) const
    {
      if(index >= nodes_.size())
        return 0;

      return nodes_[index];
    } // item

  private:
    void throwIfReadOnly() const
    {
      if(readOnly_)
        throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);
    } // throwIfReadOnly

    typedef std::deque<NodeImpl<stringT, string_adaptorT>*> NodeListT;

    NodeImpl<stringT, string_adaptorT>* getNode(typename NodeListT::const_iterator n) const
    {
      if(n == nodes_.end())
        return 0;
      return *n;
    } // getNode

    NodeImpl<stringT, string_adaptorT>* setNode(typename NodeListT::iterator n, NodeImpl<stringT, string_adaptorT>* arg)
    {
      if(n == nodes_.end())
      {
        nodes_.push_back(arg);
        return 0;
      } // if(n == nodes_.end())

      NodeImpl<stringT, string_adaptorT>* removedNode = *n;
      *n = arg;
      ownerDoc_->orphaned(removedNode);
      return removedNode;
    } // setNode

    NodeImpl<stringT, string_adaptorT>* removeNode(typename NodeListT::iterator n)
    {
      if(n == nodes_.end())
        return 0;
      NodeImpl<stringT, string_adaptorT>* removedNode = *n;
      nodes_.erase(n);
      ownerDoc_->orphaned(removedNode);
      return removedNode;
    } // removeNode

    typename NodeListT::iterator findByName(const stringT& name) 
    {
      return std::find_if(nodes_.begin(), nodes_.end(), nameIs<stringT, string_adaptorT>(name));
    } // findByName

    typename NodeListT::iterator findByNamespaceAndName(const stringT& namespaceURI, const stringT& localName) 
    {
      return std::find_if(nodes_.begin(), nodes_.end(), namespaceAndNameIs<stringT, string_adaptorT>(namespaceURI, localName));
    } // findByName

    NodeListT nodes_;
    bool readOnly_;

  protected:
    DocumentImpl<stringT, string_adaptorT>* ownerDoc_;
}; // class NamedNodeMapImpl

} // namespace SAX2DOM

#endif

