#ifndef JEZUK_SimpleDOM_HELPERSH
#define JEZUK_SimpleDOM_HELPERSH

#include <DOM/Node.hpp>
#include <utility>

namespace Arabica
{
namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
std::pair<bool, stringT> checkPrefixAndNamespace(bool hasPrefix, 
                                                const stringT& prefix, 
                                                bool hasNamespaceURI, 
                                                const stringT& namespaceURI, 
                                                typename DOM::Node_base::Type nodeType)
{
  const stringT xml = string_adaptorT::construct_from_utf8("xml");
  const stringT xmlURI = string_adaptorT::construct_from_utf8("http://www.w3.org/XML/1998/namespace");
  const stringT xmlns = string_adaptorT::construct_from_utf8("xmlns");
  const stringT xmlnsURI = string_adaptorT::construct_from_utf8("http://www.w3.org/2000/xmlns/");

  if(!hasPrefix)
    return std::make_pair(hasNamespaceURI, namespaceURI);

  if(string_adaptorT::find(prefix, string_adaptorT::construct_from_utf8(":")) != string_adaptorT::npos())
    throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);

  if(prefix == xml) 
  {
    if(namespaceURI == xmlURI)
      return std::make_pair(true, namespaceURI);
    throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);
  } // if(prefix == xml)
  
  if(nodeType == DOM::Node_base::ATTRIBUTE_NODE && prefix == xmlns) 
  {
    // DOM mandates xmlns: be bound to a namespace URI, XML Namespace rec
    // says not - allow for both here
    if((namespaceURI == xmlnsURI) || (string_adaptorT::empty(namespaceURI)))
      return std::make_pair(true, xmlnsURI);
    throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);
  } // if(nodeType == DOM::Node<stringT>::ATTRIBUTE_NODE && prefix == xmlns) 
  
  if(hasNamespaceURI == false || string_adaptorT::empty(namespaceURI)) 
    throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);

  return std::make_pair(true, namespaceURI);
} // checkPrefixAndNamespace

} // namespace SimpleDOM
} // namespace Arabica

#endif

