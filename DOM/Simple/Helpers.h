#ifndef JEZUK_SimpleDOM_HELPERSH
#define JEZUK_SimpleDOM_HELPERSH

#include <DOM/Node.h>
#include <utility>

namespace SimpleDOM
{

template<class stringT, class string_adaptorT>
std::pair<bool, stringT> checkPrefixAndNamespace(bool hasPrefix, 
                                                const stringT& prefix, 
                                                bool hasNamespaceURI, 
                                                const stringT& namespaceURI, 
                                                typename DOM::Node<stringT>::Type nodeType)
{
  string_adaptorT SA;
  const stringT xml = SA.makeStringT("xml");
  const stringT xmlURI = SA.makeStringT("http://www.w3.org/XML/1998/namespace");
  const stringT xmlns = SA.makeStringT("xmlns");
  const stringT xmlnsURI = SA.makeStringT("http://www.w3.org/2000/xmlns/");

  if(!hasPrefix)
    return std::make_pair(hasNamespaceURI, namespaceURI);

  if(prefix.find(SA.makeStringT(":")) != stringT::npos)
    throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);

  if(prefix == xml) 
  {
    if(namespaceURI == xmlURI)
      return std::make_pair(true, namespaceURI);
    throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);
  } // if(prefix == xml)
  
  if(nodeType == DOM::Node<stringT>::ATTRIBUTE_NODE && prefix == xmlns) 
  {
    if(namespaceURI == xmlnsURI)
      return std::make_pair(true, namespaceURI);
    throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);
  } // if(nodeType == DOM::Node<stringT>::ATTRIBUTE_NODE && prefix == xmlns) 
  
  if(hasNamespaceURI == false || namespaceURI.length() == 0) 
    throw DOM::DOMException(DOM::DOMException::NAMESPACE_ERR);

  return std::make_pair(true, namespaceURI);
} // checkPrefixAndNamespace

} // namespace SimpleDOM

#endif

