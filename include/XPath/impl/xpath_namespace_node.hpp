#ifndef ARABICA_XPATHIC_XPATH_NAMESPACE_NODE_HPP
#define ARABICA_XPATHIC_XPATH_NAMESPACE_NODE_HPP

#ifdef _MSC_VER
#pragma warning(disable: 4250)
#endif

#include <DOM/Simple/DocumentImpl.hpp>
#include <DOM/Simple/NodeImpl.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace XPath
{

const DOM::Node_base::Type NAMESPACE_NODE_TYPE = static_cast<DOM::Node_base::Type>(DOM::Node_base::MAX_TYPE + 27);  // 27 is a random choice

namespace impl
{

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class NamespaceNodeImpl : public DOM::Node_impl<stringT, string_adaptorT>
{
  public:
    typedef DOM::Node<stringT, string_adaptorT> NodeT;
    typedef DOM::Node_impl<stringT, string_adaptorT> NodeImplT;
    typedef DOM::NodeList_impl<stringT, string_adaptorT> NodeListT;
    typedef DOM::NamedNodeMap_impl<stringT, string_adaptorT> NamedNodeMapT;
    typedef DOM::Document_impl<stringT, string_adaptorT> DocumentImplT;

    NamespaceNodeImpl(const NodeT& parentNode,
                      const stringT& localname,
                      const stringT& value) : 
        NodeImplT(),
        parentNode_(parentNode.underlying_impl()),
        localname_(localname),
        value_(value),
        ref_(0)
    { 
    } // NamespaceNodeImpl

    NamespaceNodeImpl(NodeImplT* parentNode,
                      const stringT& localname,
                      const stringT& value) : 
        NodeImplT(),
        parentNode_(parentNode),
        localname_(localname),
        value_(value),
        ref_(0)
    { 
    } // NamespaceNodeImpl

    virtual ~NamespaceNodeImpl() { }

    ////////////////////////////////////////////////////////
    // not fully part of the document, so need to manage our own lifetime
    virtual void addRef()
    {
      parentNode_->addRef();
      ++ref_;
    } // addRef

    virtual void releaseRef() 
    {
      parentNode_->releaseRef();
      if(!(--ref_))
        delete this;
    } // releaseRef

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual const stringT& getNodeName() const { return localname_; }

    virtual const stringT& getNodeValue() const { return value_; }
    virtual void setNodeValue(const stringT&) { oopsReadOnly(); }
    
    virtual DOM::Node_base::Type getNodeType() const { return NAMESPACE_NODE_TYPE; }

    virtual NodeImplT* getParentNode() const { return parentNode_; }

    virtual NodeListT* getChildNodes() const { return 0; }
    
    virtual NodeImplT* getFirstChild() const { return 0; }
    virtual NodeImplT* getLastChild() const { return 0; }

    virtual NodeImplT* getPreviousSibling() const { return 0; }
    virtual NodeImplT* getNextSibling() const { return 0; }

    virtual NamedNodeMapT* getAttributes() const { return 0; }

    virtual DocumentImplT* getOwnerDocument() const { return parentNode_->getOwnerDocument(); }

    virtual NodeImplT* insertBefore(NodeImplT* /* newChild */, NodeImplT* /* refChild */) { throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR); }
    virtual NodeImplT* replaceChild(NodeImplT* /* newChild */, NodeImplT* /* oldChild */) { throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR); }
    virtual NodeImplT* removeChild(NodeImplT*  /* oldChild */) { throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR); }
    virtual NodeImplT* appendChild(NodeImplT*  /* newChild */) { throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR); }
    virtual void purgeChild(NodeImplT* /* oldChild */) { throw DOM::DOMException(DOM::DOMException::HIERARCHY_REQUEST_ERR); }

    virtual bool hasChildNodes() const { return false; }

    virtual NodeImplT* cloneNode(bool /* deep */) const { return new NamespaceNodeImpl<stringT, string_adaptorT>(parentNode_, localname_, value_); } 

    virtual void normalize() { }

    virtual bool isSupported(const stringT& /* feature */, const stringT& /* version */) const { return false; }

    virtual const stringT& getNamespaceURI() const { return empty_; }
    virtual const stringT& getPrefix() const { return empty_; }
    virtual void setPrefix(const stringT&) { oopsReadOnly(); }
    virtual const stringT& getLocalName() const { return localname_; }

    virtual bool hasNamespaceURI() const { return false; }
    virtual bool hasPrefix() const { return false; }

    virtual bool hasAttributes() const { return false; }

  private:
    void oopsReadOnly() const { throw DOM::DOMException(DOM::DOMException::NO_MODIFICATION_ALLOWED_ERR); }

    NodeImplT* parentNode_;
    stringT localname_;
    stringT value_;
    const stringT empty_;
    unsigned int ref_;
}; // class NamespaceNodeImpl

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
