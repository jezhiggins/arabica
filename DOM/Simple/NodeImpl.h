#ifndef JEZUK_DOM_SimpleDOM_NODE_H
#define JEZUK_DOM_SimpleDOM_NODE_H

////////////////////////////
// C++ DOM definition
//
// $Id$
////////////////////////////
#include <DOM/Node.h>
#include <deque>
#include <algorithm>

//#include <iostream>

namespace SimpleDOM
{

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class DocumentImpl;

template<class stringT, class string_adaptorT>
class NodeImpl : virtual public DOM::Node_impl<stringT>
{
  public:
    NodeImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc) :
      parentNode_(0),
      ownerDoc_(ownerDoc),
      prevSibling_(0),
      nextSibling_(0),
      readOnly_(false)
    {
        //std::cout << std::endl << "born " << this << std::endl;
    } // NodeImpl
    
    virtual ~NodeImpl() 
    { 
        //std::cout << std::endl << "die  " << this << std::endl;
    }

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

    ///////////////////////////////////////////////////////
    // Node methods
    virtual stringT getNodeName() const = 0;

    virtual stringT getNodeValue() const { return stringT(); }
    virtual void setNodeValue(const stringT& nodeValue) { throwIfReadOnly(); }

    virtual DOM::Node_base::Type getNodeType() const = 0;
    
    virtual DOM::Node_impl<stringT>* getParentNode() const { return parentNode_; }

    virtual DOM::NodeList_impl<stringT>* getChildNodes() const = 0;
    
    virtual DOM::Node_impl<stringT>* getFirstChild() const = 0;
    virtual DOM::Node_impl<stringT>* getLastChild() const = 0;

    virtual DOM::Node_impl<stringT>* getPreviousSibling() const { return prevSibling_; }
    virtual DOM::Node_impl<stringT>* getNextSibling() const { return nextSibling_; }

    virtual DOM::NamedNodeMap_impl<stringT>* getAttributes() const { return 0; }

    virtual DOM::Document_impl<stringT>* getOwnerDocument() const { return ownerDoc_; }

    virtual DOM::Node_impl<stringT>* insertBefore(DOM::Node_impl<stringT>* newChild, DOM::Node_impl<stringT>* refChild) = 0;
    virtual DOM::Node_impl<stringT>* replaceChild(DOM::Node_impl<stringT>*  newChild, DOM::Node_impl<stringT>* oldChild) = 0;
    virtual DOM::Node_impl<stringT>* removeChild(DOM::Node_impl<stringT>*  oldChild) = 0;
    virtual DOM::Node_impl<stringT>* appendChild(DOM::Node_impl<stringT>*  newChild) = 0;

    virtual bool hasChildNodes() const = 0;

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const = 0;

    virtual void normalize()
    {
      DOM::Node_impl<stringT>*child = getFirstChild(); 
      while(child != 0)
      {
        DOM::Node_impl<stringT>*next = child->getNextSibling();

        if(child->getNodeType() == DOM::Node<stringT>::TEXT_NODE)
        {
          DOM::Text_impl<stringT>* textNode = dynamic_cast<DOM::Text_impl<stringT>*>(child);
          while((next != 0) && (next->getNodeType() == DOM::Node<stringT>::TEXT_NODE))
          {
            textNode->appendData(next->getNodeValue());
            removeChild(next);
            next = textNode->getNextSibling();
          } // while 
          if(textNode->getData().empty())
            removeChild(textNode);
        } 
        else
          child->normalize();

        child = next;
      } // while 

      DOM::NamedNodeMap_impl<stringT>* attrs = getAttributes();
      if(attrs)
        for(unsigned int i = 0; i < attrs->getLength(); ++i)
          attrs->item(i)->normalize();
    } // normalize

    virtual bool isSupported(const stringT& feature, const stringT& version) const
    {
      return false;
    } // isSupported

    virtual stringT getNamespaceURI() const { return stringT(); }
    virtual stringT getPrefix() const { return stringT(); }
    virtual void setPrefix(const stringT& prefix) { }
    virtual stringT getLocalName() const { return stringT(); }

    // additional methods - since C++ std::string (and by implication
    // stringT) don't differenciate between a null string and an empty string,
    // but the DOM recommendation does, I have to introduce these three methods 
    // to disambiguate.  If they return false, the corresponding attribute should be
    // considered null.  If they return true, the attribute has been set EVEN IF 
    // it has been set to the empty string
    virtual bool hasNamespaceURI() const { return false; } 
    virtual bool hasPrefix() const { return false; }

    virtual bool hasAttributes() const { return false; }

    /////////////////////////////////////////////////////
    // implementation specific method
    void setParentNode(NodeImpl<stringT, string_adaptorT>* parent)
    {
      if(!parent && parentNode_ && ownerDoc_)
        ownerDoc_->orphaned(this);
      if(!parentNode_ && parent && ownerDoc_)
        ownerDoc_->adopted(this);
      parentNode_ = parent;
    } // setParentNode

    NodeImpl<stringT, string_adaptorT>* getFirst() { return dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(getFirstChild()); }

    NodeImpl<stringT, string_adaptorT>* getPrev() { return prevSibling_; }

    void setPrev(NodeImpl<stringT, string_adaptorT>* prevSibling)
    {
      prevSibling_ = prevSibling;
    } // setPreviousSibling

    NodeImpl<stringT, string_adaptorT>* getNext() { return nextSibling_; }

    void setNext(NodeImpl<stringT, string_adaptorT>* nextSibling)
    {
      nextSibling_ = nextSibling;
    } // setNextSibling

    DocumentImpl<stringT, string_adaptorT>* getOwnerDoc() const { return ownerDoc_; }

    virtual void setOwnerDoc(DocumentImpl<stringT, string_adaptorT>* ownerDoc)
    {
      ownerDoc_ = ownerDoc;
      for(NodeImpl<stringT, string_adaptorT>*child = getFirst(); child != 0; child = child->getNext())
        child->setOwnerDoc(ownerDoc);
    } // setOwnerDocument

    bool getReadOnly() const { return readOnly_; }

    virtual void setReadOnly(bool readOnly)
    {
      readOnly_ = true;
      for(NodeImpl<stringT, string_adaptorT>*child = getFirst(); child != 0; child = child->getNext())
        child->setReadOnly(readOnly_);
    } // setReadOnly

    void throwIfReadOnly() const
    {
      if(readOnly_)
        throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);
    } // throwIfReadOnly

  protected:
    NodeImpl<stringT, string_adaptorT>* parentNode_;
    DocumentImpl<stringT, string_adaptorT>* ownerDoc_;
    NodeImpl<stringT, string_adaptorT>* prevSibling_;
    NodeImpl<stringT, string_adaptorT>* nextSibling_;
    bool readOnly_;
}; // class NodeImpl

template<class stringT, class string_adaptorT>
class ChildlessNodeImpl : public NodeImpl<stringT, string_adaptorT>  
{
  public:
    ChildlessNodeImpl(DocumentImpl<stringT, string_adaptorT>* ownerDoc) :
      NodeImpl<stringT, string_adaptorT>(ownerDoc)
    {
    } // ChildlessNodeImpl 

    ///////////////////////////////////////////////////////
    // Node methods
    virtual DOM::NodeList_impl<stringT>* getChildNodes() const { return 0; }
    
    virtual DOM::Node_impl<stringT>* getFirstChild() const { return 0; }
    virtual DOM::Node_impl<stringT>* getLastChild() const { return 0; }

    virtual DOM::Node_impl<stringT>* insertBefore(DOM::Node_impl<stringT>*newChild, DOM::Node_impl<stringT>*refChild)
    {
      throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // insertBefore

    virtual DOM::Node_impl<stringT>* replaceChild(DOM::Node_impl<stringT>*newChild, DOM::Node_impl<stringT>*oldChild)
    {
      throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // insertBefore

    virtual DOM::Node_impl<stringT>* removeChild(DOM::Node_impl<stringT>*oldChild)
    {
      throw DOM::DOMException(DOM::DOMException::NOT_FOUND_ERR);
    } // removeChild

    virtual DOM::Node_impl<stringT>* appendChild(DOM::Node_impl<stringT>*newChild)
    {
      throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // appendChild

    virtual bool hasChildNodes() const { return false; }
}; // class ChildlessNodeImpl

template<class stringT, class string_adaptorT>
class NodeImplWithChildren : public NodeImpl<stringT, string_adaptorT>,
                             public DOM::NodeList_impl<stringT>
{
  public:
    NodeImplWithChildren(DocumentImpl<stringT, string_adaptorT>* ownerDoc) :
      NodeImpl<stringT, string_adaptorT>(ownerDoc)
    {
    } // NodeImplWithChildren

    virtual ~NodeImplWithChildren() 
    { 
      for(typename NodeListT::iterator i = nodes_.begin(); i != nodes_.end(); ++i)
        delete (*i);
    } // ~NodeImpl

    ///////////////////////////////////////////////////////
    // Ref counting
    virtual void addRef()
    {
      NodeImpl<stringT, string_adaptorT>::addRef();
    } // addRef
    virtual void releaseRef() 
    {
      NodeImpl<stringT, string_adaptorT>::releaseRef();
    } // releaseRef

    ///////////////////////////////////////////////////////
    // Node methods
    virtual DOM::NodeList_impl<stringT>* getChildNodes() const 
    { 
      return const_cast<DOM::NodeList_impl<stringT>*>(static_cast<const DOM::NodeList_impl<stringT>*>(this)); 
    } // getChildNodes
    
    virtual DOM::Node_impl<stringT>* getFirstChild() const
    {
      if(nodes_.size())
        return nodes_[0];
      return 0;
    } // getFirstChild

    virtual DOM::Node_impl<stringT>* getLastChild() const
    {
      if(nodes_.size())
        return *nodes_.rbegin();
      return 0;
    } // getLastChild

    virtual DOM::Node_impl<stringT>* insertBefore(DOM::Node_impl<stringT>*newChild, DOM::Node_impl<stringT>*refChild)
    {
      return do_insertBefore(dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(newChild), 
                             dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(refChild));
    } // insertBefore

    virtual DOM::Node_impl<stringT>* replaceChild(DOM::Node_impl<stringT>*newChild, DOM::Node_impl<stringT>*oldChild)
    {
      return do_replaceChild(dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(newChild), 
                             dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(oldChild));
    } // replaceChild

    virtual DOM::Node_impl<stringT>* removeChild(DOM::Node_impl<stringT>* oldChild)
    {
      return do_removeChild(dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(oldChild));
    } // removeChild

    virtual DOM::Node_impl<stringT>* appendChild(DOM::Node_impl<stringT>* newChild)
    {
      return do_appendChild(dynamic_cast<NodeImpl<stringT, string_adaptorT>*>(newChild));
    } // appendChild

    virtual bool hasChildNodes() const 
    {  
      return nodes_.size() != 0;
    } // hasChildNodes

    ///////////////////////////////////////////////////////
    // NodeList methods
    virtual DOM::Node_impl<stringT>* item(unsigned int index) const
    {
      if(index >= nodes_.size())
        return 0;

      return nodes_[index];
    } // item

    virtual unsigned int getLength() const
    {
      return nodes_.size();
    } // getLength

    /////////////////////////////////////////////////////////////
    // implementation
  protected:
    NodeImpl<stringT, string_adaptorT>* do_insertBefore(NodeImpl<stringT, string_adaptorT>* newChild, NodeImpl<stringT, string_adaptorT>* refChild)
    {
      throwIfReadOnly();

      if(newChild->getNodeType() == DOM::Node<stringT>::DOCUMENT_FRAGMENT_NODE)
      {
        for(NodeImpl<stringT, string_adaptorT>* child = newChild->getFirst(); child != 0; child = newChild->getFirst())
          insertBefore(newChild->removeChild(child), refChild);
        return newChild;
      } // if ...

      checkCanAdd(newChild);
      removeIfRequired(newChild);
      if(refChild)
      {
        nodes_.insert(findChild(refChild), newChild);

        NodeImpl<stringT, string_adaptorT>* prev = refChild->getPrev();
        if(prev != 0)
          prev->setNext(newChild);
        newChild->setPrev(prev);
        newChild->setNext(refChild);
        refChild->setPrev(newChild);
      } 
      else 
      {
        if(!nodes_.empty())
        {
          (*nodes_.rbegin())->setNext(newChild);
          newChild->setPrev(*nodes_.rbegin());
        } // 
        nodes_.push_back(newChild);
      }

      newChild->setParentNode(this);

      markChanged();

      return newChild;
    } // insertBefore

    NodeImpl<stringT, string_adaptorT>* do_replaceChild(NodeImpl<stringT, string_adaptorT>* newChild, NodeImpl<stringT, string_adaptorT>* oldChild)
    {
      throwIfReadOnly();

      if(newChild->getNodeType() == DOM::Node<stringT>::DOCUMENT_FRAGMENT_NODE)
      {
        // not exception safe - but the it's not specified to be :(
        DOM::Node_impl<stringT>* lc = newChild->getLastChild();
        replaceChild(newChild->removeChild(lc), oldChild);
        insertBefore(newChild, lc);
        return newChild;
      } // if ...

      checkCanAdd(newChild);
      typename std::deque<NodeImpl<stringT, string_adaptorT>*>::iterator result = findChild(oldChild);
      removeIfRequired(newChild);
      *result = newChild;
      newChild->setParentNode(this);

      NodeImpl<stringT, string_adaptorT>* prev = oldChild->getPrev();
      NodeImpl<stringT, string_adaptorT>* next = oldChild->getNext();
      newChild->setPrev(prev);
      newChild->setNext(next);
      if(prev != 0)
        prev->setNext(newChild);
      if(next != 0)
        next->setPrev(newChild);

      oldChild->setParentNode(0);
      oldChild->setPrev(0);
      oldChild->setNext(0);

      markChanged();

      return oldChild;
    } // replaceChild

    NodeImpl<stringT, string_adaptorT>* do_removeChild(NodeImpl<stringT, string_adaptorT>* oldChild)
    {
      throwIfReadOnly();

      nodes_.erase(findChild(oldChild));

      NodeImpl<stringT, string_adaptorT>* prev = oldChild->getPrev();
      NodeImpl<stringT, string_adaptorT>* next = oldChild->getNext();
      if(prev != 0)
        prev->setNext(next);
      if(next != 0)
        next->setPrev(prev);

      oldChild->setParentNode(0);
      oldChild->setPrev(0);
      oldChild->setNext(0);

      markChanged();

      return oldChild;
    } // removeChild

    NodeImpl<stringT, string_adaptorT>* do_appendChild(NodeImpl<stringT, string_adaptorT>* newChild)
    {
      return do_insertBefore(newChild, 0);
    } // appendChild


  private:
    typedef std::deque<NodeImpl<stringT, string_adaptorT>*> NodeListT;

    typename NodeListT::iterator findChild(NodeImpl<stringT, string_adaptorT>* refChild)
    {
      typename NodeListT::iterator result = std::find(nodes_.begin(), nodes_.end(), refChild);
      if(result == nodes_.end())
        throw DOM::DOMException(DOM::DOMException::NOT_FOUND_ERR);
      return result;
    } // findChild

    void removeIfRequired(NodeImpl<stringT, string_adaptorT>* newNode) const
    {
      if(newNode->getParentNode() != 0)
        newNode->getParentNode()->removeChild(newNode);
    } // removeIfRequired

    void checkCanAdd(NodeImpl<stringT, string_adaptorT>* child)
    {
      DocumentImpl<stringT, string_adaptorT>* childDoc = child->getOwnerDoc();
      if(childDoc == 0)
      {
        child->setOwnerDoc(getOwnerDoc());
        return;
      } // 

      if(getNodeType() == DOM::Node<stringT>::DOCUMENT_NODE) 
      {
        if(childDoc != dynamic_cast<DocumentImpl<stringT, string_adaptorT>*>(this))
          throw DOM::DOMException(DOM::DOMException::WRONG_DOCUMENT_ERR);
        return;
      } // if(parent is a Document)

      if(getOwnerDocument() && childDoc != getOwnerDocument())
        throw DOM::DOMException(DOM::DOMException::WRONG_DOCUMENT_ERR);

      checkChildType(child);
    } // checkCanAdd

    virtual void checkChildType(DOM::Node_impl<stringT>* child) = 0;

    void markChanged()
    {
      if(ownerDoc_)
        ownerDoc_->markChanged();
    } // markChanged

    NodeListT nodes_;
}; // class NodeImplWithChildren

} // namespace DOM

#endif // JEZUK_DOM_NODE_H
// end of file
