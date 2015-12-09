#ifndef JEZUK_DOM_SimpleDOM_NODE_H
#define JEZUK_DOM_SimpleDOM_NODE_H

////////////////////////////
// C++ DOM definition
////////////////////////////

#include <DOM/Node.hpp>
#include <DOM/Events/Event.hpp>
#include <DOM/Events/EventListener.hpp>
#include <DOM/DOMException.hpp>
#include <XML/XMLCharacterClasses.hpp>
#include <deque>
#include <algorithm>
#include <map>

namespace Arabica
{
namespace SimpleDOM
{

////////////////////////////////////////////////////////////////////
template<class stringT, class string_adaptorT> class DocumentImpl;

template<class stringT, class string_adaptorT>
class NodeImpl : virtual public DOM::Node_impl<stringT, string_adaptorT>
{
  public:
    typedef NodeImpl<stringT, string_adaptorT> NodeImplT;
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::Text_impl<stringT, string_adaptorT> DOMText_implT;
    typedef DOM::Document_impl<stringT, string_adaptorT> DOMDocument_implT;
    typedef DOM::NamedNodeMap_impl<stringT, string_adaptorT> DOMNamedNodeMap_implT;
    typedef DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;

    NodeImpl(DocumentImplT* ownerDoc) :
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
    virtual const stringT& getNodeName() const = 0;

    virtual const stringT& getNodeValue() const { return ownerDoc_->empty_string(); }
    virtual void setNodeValue(const stringT& /*nodeValue*/) { }

    virtual DOM::Node_base::Type getNodeType() const = 0;

    virtual DOMNode_implT* getParentNode() const { return parentNode_; }

    virtual DOMNodeList_implT* getChildNodes() const = 0;

    virtual DOMNode_implT* getFirstChild() const = 0;
    virtual DOMNode_implT* getLastChild() const = 0;

    virtual DOMNode_implT* getPreviousSibling() const { return prevSibling_; }
    virtual DOMNode_implT* getNextSibling() const { return nextSibling_; }

    virtual DOMNamedNodeMap_implT* getAttributes() const { return 0; }

    virtual DOMDocument_implT* getOwnerDocument() const { return ownerDoc_; }

    virtual DOMNode_implT* insertBefore(DOMNode_implT* newChild, DOMNode_implT* refChild) = 0;
    virtual DOMNode_implT* replaceChild(DOMNode_implT*  newChild, DOMNode_implT* oldChild) = 0;
    virtual DOMNode_implT* removeChild(DOMNode_implT*  oldChild) = 0;
    virtual DOMNode_implT* appendChild(DOMNode_implT*  newChild) = 0;
    virtual void purgeChild(DOMNode_implT* oldChild) = 0;

    virtual bool hasChildNodes() const = 0;

    virtual DOMNode_implT* cloneNode(bool deep) const = 0;

    virtual void normalize()
    {
      DOMNode_implT*child = getFirstChild();
      while(child != 0)
      {
        DOMNode_implT*next = child->getNextSibling();

        if(child->getNodeType() == DOM::Node_base::TEXT_NODE)
        {
          DOMText_implT* textNode = dynamic_cast<DOMText_implT*>(child);
          while((next != 0) &&
                (next->getNodeType() == DOM::Node_base::TEXT_NODE))
          {
            textNode->appendData(next->getNodeValue());
            removeChild(next);
            next = textNode->getNextSibling();
          } // while
          if(string_adaptorT::empty(textNode->getData()))
            removeChild(textNode);
        }
        else
          child->normalize();

        child = next;
      } // while

      DOMNamedNodeMap_implT* attrs = getAttributes();
      if(attrs)
        for(unsigned int i = 0; i < attrs->getLength(); ++i)
          attrs->item(i)->normalize();
    } // normalize

    virtual bool isSupported(const stringT& /*feature*/, const stringT& /*version*/) const
    {
      return false;
    } // isSupported

    virtual const stringT& getNamespaceURI() const { return ownerDoc_->empty_string(); }
    virtual const stringT& getPrefix() const { return ownerDoc_->empty_string(); }
    virtual void setPrefix(const stringT& /*prefix*/) { }
    virtual const stringT& getLocalName() const { return ownerDoc_->empty_string(); }

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
    void setParentNode(NodeImplT* parent)
    {
      if(!parent && parentNode_ && ownerDoc_)
        ownerDoc_->orphaned(this);
      if(!parentNode_ && parent && ownerDoc_)
        ownerDoc_->adopted(this);
      parentNode_ = parent;
    } // setParentNode

    NodeImplT* getFirst() { return dynamic_cast<NodeImplT*>(getFirstChild()); }

    NodeImplT* getPrev() { return prevSibling_; }

    void setPrev(NodeImplT* prevSibling)
    {
      prevSibling_ = prevSibling;
    } // setPreviousSibling

    NodeImplT* getNext() { return nextSibling_; }

    void setNext(NodeImplT* nextSibling)
    {
      nextSibling_ = nextSibling;
    } // setNextSibling

    DocumentImplT* getOwnerDoc() const { return ownerDoc_; }

    virtual void setOwnerDoc(DocumentImplT* ownerDoc)
    {
      ownerDoc_ = ownerDoc;
      for(NodeImplT*child = getFirst(); child != 0; child = child->getNext())
        child->setOwnerDoc(ownerDoc);
    } // setOwnerDocument

    bool getReadOnly() const { return readOnly_; }

    virtual void setReadOnly(bool /*readOnly*/)
    {
      // Should be readOnly_ = readOnly; ?
      readOnly_ = true;
      for(NodeImplT* child = getFirst(); child != 0; child = child->getNext())
        child->setReadOnly(readOnly_);
      DOMNamedNodeMap_implT* attrs = getAttributes();
      if(attrs)
        for(unsigned int i = 0; i < attrs->getLength(); ++i)
          (dynamic_cast<NodeImplT*>(attrs->item(i)))->setReadOnly(readOnly_);
    } // setReadOnly

    void throwIfReadOnly() const
    {
      if(readOnly_)
        throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR);
    } // throwIfReadOnly


  protected:
    void checkName(const stringT& str) const
    {
      if(string_adaptorT::length(str) == 0)
	throw DOM::DOMException(DOM::DOMException::INVALID_CHARACTER_ERR);
      typedef typename string_adaptorT::const_iterator const_iterator;
      const_iterator i = string_adaptorT::begin(str);
      const_iterator ie = string_adaptorT::end(str);
      for( ; i != ie; ++i)
	if(!XML::is_name_char(*i))
	  throw DOM::DOMException(DOM::DOMException::INVALID_CHARACTER_ERR);
    } // checkName

    void checkChars(const stringT& str) const
    {
      typedef typename string_adaptorT::const_iterator const_iterator;
      const_iterator i = string_adaptorT::begin(str);
      const_iterator ie = string_adaptorT::end(str);
      for( ; i != ie; ++i)
	if(!XML::is_char(*i))
	  throw DOM::DOMException(DOM::DOMException::INVALID_CHARACTER_ERR);
    } // checkChars

    NodeImplT* parentNode_;
    DocumentImplT* ownerDoc_;
    NodeImplT* prevSibling_;
    NodeImplT* nextSibling_;
    bool readOnly_;
}; // class NodeImpl

template<class stringT, class string_adaptorT>
class ChildlessNodeImpl : public NodeImpl<stringT, string_adaptorT>
{
  public:
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;

    ChildlessNodeImpl(DocumentImplT* ownerDoc) :
      NodeImpl<stringT, string_adaptorT>(ownerDoc)
    {
    } // ChildlessNodeImpl

    ///////////////////////////////////////////////////////
    // Node methods
    virtual DOMNodeList_implT* getChildNodes() const { return 0; }

    virtual DOMNode_implT* getFirstChild() const { return 0; }
    virtual DOMNode_implT* getLastChild() const { return 0; }

    virtual DOMNode_implT* insertBefore(DOMNode_implT* /*newChild*/, DOMNode_implT* /*refChild*/)
    {
      throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // insertBefore

    virtual DOMNode_implT* replaceChild(DOMNode_implT* /*newChild*/, DOMNode_implT* /*oldChild*/)
    {
      throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // insertBefore

    virtual DOMNode_implT* removeChild(DOMNode_implT* /*oldChild*/)
    {
      throw DOM::DOMException(DOM::DOMException::NOT_FOUND_ERR);
    } // removeChild

    virtual DOMNode_implT* appendChild(DOMNode_implT* /*newChild*/)
    {
      throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // appendChild

    virtual void purgeChild(DOMNode_implT* /*oldChild*/)
    {
      throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);
    } // purgeChild

    virtual bool hasChildNodes() const { return false; }
}; // class ChildlessNodeImpl

template<class stringT, class string_adaptorT>
class NodeImplWithChildren : public NodeImpl<stringT, string_adaptorT>,
                             public DOM::NodeList_impl<stringT, string_adaptorT>
{
  public:
    typedef NodeImpl<stringT, string_adaptorT> NodeImplT;
    typedef DocumentImpl<stringT, string_adaptorT> DocumentImplT;
    typedef DOM::Node_impl<stringT, string_adaptorT> DOMNode_implT;
    typedef DOM::NodeList_impl<stringT, string_adaptorT> DOMNodeList_implT;

    NodeImplWithChildren(DocumentImplT* ownerDoc) :
      NodeImplT(ownerDoc)
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
      NodeImplT::addRef();
    } // addRef
    virtual void releaseRef()
    {
      NodeImplT::releaseRef();
    } // releaseRef

    ///////////////////////////////////////////////////////
    // Node methods
    virtual DOMNodeList_implT* getChildNodes() const
    {
      return const_cast<DOMNodeList_implT*>(static_cast<const DOMNodeList_implT*>(this));
    } // getChildNodes

    virtual DOMNode_implT* getFirstChild() const
    {
      if(nodes_.size())
        return nodes_[0];
      return 0;
    } // getFirstChild

    virtual DOMNode_implT* getLastChild() const
    {
      if(nodes_.size())
        return *nodes_.rbegin();
      return 0;
    } // getLastChild

    virtual DOMNode_implT* insertBefore(DOMNode_implT* newChild, DOMNode_implT* refChild)
    {
      return do_insertBefore(dynamic_cast<NodeImplT*>(newChild),
                             dynamic_cast<NodeImplT*>(refChild));
    } // insertBefore

    virtual DOMNode_implT* replaceChild(DOMNode_implT* newChild, DOMNode_implT* oldChild)
    {
      return do_replaceChild(dynamic_cast<NodeImplT*>(newChild),
                             dynamic_cast<NodeImplT*>(oldChild));
    } // replaceChild

    virtual DOMNode_implT* removeChild(DOMNode_implT* oldChild)
    {
      return do_removeChild(dynamic_cast<NodeImplT*>(oldChild));
    } // removeChild

    virtual DOMNode_implT* appendChild(DOMNode_implT* newChild)
    {
      return do_appendChild(dynamic_cast<NodeImplT*>(newChild));
    } // appendChild

    virtual void purgeChild(DOMNode_implT* oldChild)
    {
      do_purgeChild(dynamic_cast<NodeImplT*>(oldChild));
    } // purgeChild

    virtual bool hasChildNodes() const
    {
      return nodes_.size() != 0;
    } // hasChildNodes

    ///////////////////////////////////////////////////////
    // NodeList methods
    virtual DOMNode_implT* item(unsigned int index) const
    {
      if(index >= nodes_.size())
        return 0;

      return nodes_[index];
    } // item

    virtual unsigned int getLength() const
    {
      return static_cast<unsigned int>(nodes_.size());
    } // getLength

    /////////////////////////////////////////////////////////////
    // implementation
  protected:
    NodeImplT* do_insertBefore(NodeImplT* newChild, NodeImplT* refChild)
    {
      NodeImplT::throwIfReadOnly();

      if(newChild->getNodeType() == DOM::Node_base::DOCUMENT_FRAGMENT_NODE)
      {
        for(NodeImplT* child = newChild->getFirst(); child != 0; child = newChild->getFirst())
          insertBefore(newChild->removeChild(child), refChild);
        return newChild;
      } // if ...

      checkCanAdd(newChild);
      removeIfRequired(newChild);
      if(refChild)
      {
        nodes_.insert(findChild(refChild), newChild);

        NodeImplT* prev = refChild->getPrev();
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

    NodeImplT* do_replaceChild(NodeImplT* newChild, NodeImplT* oldChild)
    {
      NodeImplT::throwIfReadOnly();

      if(newChild->getNodeType() == DOM::Node_base::DOCUMENT_FRAGMENT_NODE)
      {
        // not exception safe - but the it's not specified to be :(
        DOMNode_implT* lc = newChild->getLastChild();
        replaceChild(newChild->removeChild(lc), oldChild);
        insertBefore(newChild, lc);
        return oldChild;
      } // if ...

      checkCanAdd(newChild);
      removeIfRequired(newChild);
      typename std::deque<NodeImplT*>::iterator result = findChild(oldChild);
      *result = newChild;
      newChild->setParentNode(this);

      NodeImplT* prev = oldChild->getPrev();
      NodeImplT* next = oldChild->getNext();
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

    NodeImplT* do_removeChild(NodeImplT* oldChild)
    {
      NodeImplT::throwIfReadOnly();

      nodes_.erase(findChild(oldChild));

      NodeImplT* prev = oldChild->getPrev();
      NodeImplT* next = oldChild->getNext();
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

    NodeImplT* do_appendChild(NodeImplT* newChild)
    {
      return do_insertBefore(newChild, 0);
    } // appendChild

    void do_purgeChild(NodeImplT* oldChild)
    {
      oldChild = do_removeChild(oldChild);
      NodeImplT::ownerDoc_->purge(oldChild);
    } // do_purgeChild

  private:
    typedef std::deque<NodeImplT*> NodeListT;

    typename NodeListT::iterator findChild(NodeImplT* refChild)
    {
      typename NodeListT::iterator result = std::find(nodes_.begin(), nodes_.end(), refChild);
      if(result == nodes_.end())
        throw DOM::DOMException(DOM::DOMException::NOT_FOUND_ERR);
      return result;
    } // findChild

    void removeIfRequired(NodeImplT* newNode) const
    {
      if(newNode->getParentNode() != 0)
        newNode->getParentNode()->removeChild(newNode);
    } // removeIfRequired

    void checkCanAdd(NodeImplT* child)
    {
      DocumentImplT* childDoc = child->getOwnerDoc();
      if(childDoc == 0)
      {
        child->setOwnerDoc(NodeImplT::getOwnerDoc());
        return;
      } //

      if(child->getNodeType() == DOM::Node_base::DOCUMENT_NODE)
      {
        if(childDoc != dynamic_cast<DocumentImplT*>(this))
          throw DOM::DOMException(DOM::DOMException::WRONG_DOCUMENT_ERR);
        return;
      } // if(parent is a Document)

      if(NodeImplT::getOwnerDocument() && childDoc != NodeImplT::getOwnerDocument())
        throw DOM::DOMException(DOM::DOMException::WRONG_DOCUMENT_ERR);

      for(DOMNode_implT* n = this; n != 0; n = n->getParentNode())
	if(n == child)
	  throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR);

      checkChildType(child);
    } // checkCanAdd

    virtual void checkChildType(DOMNode_implT* child) = 0;

    void markChanged()
    {
      if(NodeImplT::ownerDoc_)
        NodeImplT::ownerDoc_->markChanged();
    } // markChanged

    NodeListT nodes_;
}; // class NodeImplWithChildren

} // namespace DOM
} // namespace Arabica

#endif // JEZUK_DOM_NODE_H
// end of file
