#ifndef ARABICA_XSLT_NAMESPACE_STACK_HPP
#define ARABICA_XSLT_NAMESPACE_STACK_HPP

#include <map>
#include <vector>
 
#include "handler/xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class NamespaceStack 
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
public:
  typedef std::map<string_type, string_type> Scope;

  NamespaceStack() :
    autoNs_(1)
  {
    prefixStack_.push_back(Scope());
    uriStack_.push_back(Scope());
  } // NamespaceStack

  void pushScope()
  {
    prefixStack_.push_back(Scope());
    uriStack_.push_back(Scope());
  } // pushScope

  void popScope()
  {
    prefixStack_.pop_back();
    uriStack_.pop_back();
  } // popScope

  void declareNamespace(const string_type& given_prefix, const string_type& namespaceURI, bool attr = false)
  {
    if(findPrefix(namespaceURI) != EMPTY_STRING)
      return;

    bool remap = (attr && string_adaptor::empty(given_prefix)) || (given_prefix == SC::xmlns);

    string_type prefix = !remap ? given_prefix : autoNamespacePrefix();

    prefixStack_.back()[prefix] = namespaceURI;
    uriStack_.back()[namespaceURI] = prefix;
  } // declareNamespace

  const string_type& findURI(const string_type& prefix) const
  {
    return searchStack(prefixStack_, prefix);
  } // findURI

  const string_type& findPrefix(const string_type& uri) const
  {
    return searchStack(uriStack_, uri);
  } // findPrefix

  typename Scope::const_iterator begin() { return prefixStack_.back().begin(); }
  typename Scope::const_iterator end() { return prefixStack_.back().end(); }

private:
  typedef std::vector<Scope> ScopeStack;

  const string_type& searchStack(const ScopeStack& stack, const string_type& key) const
  {
    for(typename ScopeStack::const_reverse_iterator ss = stack.rbegin(), se = stack.rend(); ss != se; ss++)
    {      
      typename Scope::const_iterator i = ss->find(key);
      if(i != ss->end())
        return i->second;
    }
    return EMPTY_STRING;
  } // searchStack

  string_type autoNamespacePrefix()
  {
    std::basic_ostringstream<typename string_adaptor::value_type> ss;
    ss << SC::auto_ns << autoNs_++;
    return string_adaptor::construct(ss.str());
  } // autoNamespacePrefix

  ScopeStack prefixStack_;
  ScopeStack uriStack_;
  string_type EMPTY_STRING;
  unsigned int autoNs_;
}; // class NamespaceStack

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_NAMESPACE_STACK_HPP

