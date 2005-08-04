#ifndef ARABICA_XPATHIC_XPATH_NAMESPACE_NODE_HPP
#define ARABICA_XPATHIC_XPATH_NAMESPACE_NODE_HPP

#pragma warning(disable: 4250)

#include <DOM/Simple/DocumentImpl.h>
#include <DOM/Simple/NodeImpl.h>
#include <SAX/helpers/StringAdaptor.h>

namespace Arabica
{
namespace XPath
{

const DOM::Node_base::Type NAMESPACE_NODE_TYPE = static_cast<DOM::Node_base::Type>(DOM::Node_base::MAX_TYPE + 27);  // 27 is a random choice

template<class stringT, class string_adaptorT = SAX::default_string_adaptor<stringT> >
class NamespaceNodeImpl : public SimpleDOM::ChildlessNodeImpl<stringT, string_adaptorT>
{
    typedef SimpleDOM::ChildlessNodeImpl<stringT, string_adaptorT> NodeT;
  public:
    NamespaceNodeImpl(stringT localname,
                      stringT value) : 
        SimpleDOM::ChildlessNodeImpl<stringT, string_adaptorT>(0),
        localname_(localname),
        value_(value),
        ref_(0)
    { 
      this->setReadOnly(true);
    } // NamespaceNodeImpl

    virtual ~NamespaceNodeImpl() { }

    ///////////////////////////////////////////////////////
    // DOM::Node methods
    virtual DOM::Node_base::Type getNodeType() const
    {
      return NAMESPACE_NODE_TYPE;
    } // getNodeType

    virtual stringT getNodeName() const
    {
      return localname_;
    } // getNodeName

    virtual stringT getNodeValue() const
    {
      return value_;
    } // getNodeValue

    virtual stringT getLocalName() const 
    {
      return localname_;
    } // getNodeName

    virtual DOM::Node_impl<stringT>* cloneNode(bool deep) const
    {
      return new NamespaceNodeImpl<stringT, string_adaptorT>(localname_, value_);
    } // cloneNode

    // not part of the document, so need to manage our own lifetime
    virtual void addRef()
    {
      ++ref_;
    } // addRef

    virtual void releaseRef() 
    {
      if(!(--ref_))
        delete this;
    } // releaseRef

private:
    stringT localname_;
    stringT value_;
    unsigned int ref_;
}; // class NamespaceNodeImpl

} // namespace XPath
} // namespace Arabica

#endif
