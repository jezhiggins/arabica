#ifndef JEZUK_SimpleDOM_NAMEDNODEMAPIMPL_H
#define JEZUK_SimpleDOM_NAMEDNODEMAPIMPL_H

#include <DOM/Simple/NodeImpl.hpp>
#include <DOM/NamedNodeMap.hpp>
#include <deque>
#include <algorithm>
#include <functional>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
class nameIs : public std::unary_function<Arabica::SimpleDOM::NodeImpl<stringT, string_adaptorT>*, bool>
{
  public:
    nameIs(const stringT& name) : name_(name) { }
    bool operator()(const Arabica::SimpleDOM::NodeImpl<stringT, string_adaptorT>* node) const
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
      if(string_adaptorT::empty(namespaceURI_))
      {
        if((node->hasNamespaceURI() == false) &&
           ((node->getLocalName() == localName_) ||
            (string_adaptorT::empty(node->getLocalName()) && node->getNodeName() == localName_)
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
class NamedNodeMapImpl : public DOM::NamedNodeMap_impl<stringT, string_adaptorT>
{
  public:
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef NodeImpl<stringT, string_adaptorT> NodeImplT;
    typedef NamedNodeMapImpl<stringT, string_adaptorT> NamedNodeMapImplT;
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;

    NamedNodeMapImpl(DocumentImplT* ownerDoc) : 
        DOM::NamedNodeMap_impl<stringT, string_adaptorT>(),
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
    virtual void setOwnerDoc(DocumentImplT* ownerDoc)
    {
      ownerDoc_ = ownerDoc;
      for(typename NodeListT::iterator i = nodes_.begin(); i != nodes_.end(); ++i)
        (*i)->setOwnerDoc(ownerDoc);
    } // setOwnerDoc

    ///////////////////////////////////////////////////
    // DOM::NamedNodeMap methods
    virtual DOMNode_implT* getNamedItem(const stringT& name) const
    {
      return getNode(const_cast<NamedNodeMapImplT*>(this)->findByName(name));
    } // getNamedItem

    virtual DOMNode_implT* setNamedItem(DOMNode_implT* arg)
    {
      throwIfReadOnly();
      return setNode(findByName(arg->getNodeName()), dynamic_cast<NodeImplT*>(arg));
    } // setNamedItem

    virtual DOMNode_implT* removeNamedItem(const stringT& name)
    {
      throwIfReadOnly();
      return removeNode(findByName(name));
    } // removedNamedItem

    virtual DOMNode_implT* item(unsigned int index) const
    {
      return do_item(index);
    } // item

    virtual unsigned int getLength() const
    {
      return static_cast<unsigned int>(nodes_.size());
    } // getLength

    virtual DOMNode_implT* getNamedItemNS(const stringT& namespaceURI, const stringT& localName) const
    {
      return getNode(const_cast<NamedNodeMapImplT*>(this)->findByNamespaceAndName(namespaceURI, localName));
    } // getNamedItemNS

    virtual DOMNode_implT* setNamedItemNS(DOMNode_implT* arg)
    {
      throwIfReadOnly();
      return setNode(findByNamespaceAndName(arg->getNamespaceURI(), arg->getLocalName()), dynamic_cast<NodeImplT*>(arg));
    } // setNamedItemNS

    virtual DOMNode_implT* removeNamedItemNS(const stringT& namespaceURI, const stringT& localName)
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

    NodeImplT* do_item(unsigned int index) const
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

    typedef std::deque<NodeImplT*> NodeListT;

    NodeImplT* getNode(typename NodeListT::const_iterator n) const
    {
      if(n == nodes_.end())
        return 0;
      return *n;
    } // getNode

    NodeImplT* setNode(typename NodeListT::iterator n, NodeImplT* arg)
    {
      if(ownerDoc_)
        ownerDoc_->adopted(arg);
      if(n == nodes_.end())
      {
        nodes_.push_back(arg);
        return 0;
      } // if(n == nodes_.end())

      NodeImplT* removedNode = *n;
      *n = arg;
      ownerDoc_->orphaned(removedNode);
      return removedNode;
    } // setNode

    NodeImplT* removeNode(typename NodeListT::iterator n)
    {
      if(n == nodes_.end())
        return 0;
      NodeImplT* removedNode = *n;
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
    DocumentImplT* ownerDoc_;
}; // class NamedNodeMapImpl

} // namespace SAX2DOM
} // namespace Arabica

#endif

