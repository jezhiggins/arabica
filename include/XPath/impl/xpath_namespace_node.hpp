#ifndef ARABICA_XPATHIC_XPATH_NAMESPACE_NODE_HPP
#define ARABICA_XPATHIC_XPATH_NAMESPACE_NODE_HPP

#ifdef _MSC_VER
#pragma warning(disable: 4250)
#endif

#include <DOM/Simple/DocumentImpl.hpp>
#include <DOM/Simple/NodeImpl.hpp>
#include <Utils/StringAdaptor.hpp>

namespace Arabica
{
namespace XPath
{

const DOM::Node_base::Type NAMESPACE_NODE_TYPE = static_cast<DOM::Node_base::Type>(DOM::Node_base::MAX_TYPE + 27);  // 27 is a random choice

namespace impl
{

template<class stringT, class string_adaptorT = Arabica::default_string_adaptor<stringT> >
class NamespaceNodeImpl : public Arabica::SimpleDOM::ChildlessNodeImpl<stringT, string_adaptorT>
{
    typedef Arabica::SimpleDOM::ChildlessNodeImpl<stringT, string_adaptorT> NodeT;
  public:
    NamespaceNodeImpl(stringT localname,
                      stringT value) : 
        Arabica::SimpleDOM::ChildlessNodeImpl<stringT, string_adaptorT>(0),
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

    virtual const stringT& getNodeName() const
    {
      return localname_;
    } // getNodeName

    virtual const stringT& getNodeValue() const
    {
      return value_;
    } // getNodeValue

    virtual const stringT& getNamespaceURI() const 
    { 
      return empty_;
    } // getNamespaceURI()

    virtual const stringT& getPrefix() const
    {
      return empty_;
    } // getPrefix

    virtual const stringT& getLocalName() const 
    {
      return localname_;
    } // getLocalName

    virtual DOM::Node_impl<stringT, string_adaptorT>* cloneNode(bool deep) const
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
    const stringT empty_;
    unsigned int ref_;
}; // class NamespaceNodeImpl

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
