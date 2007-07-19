#ifndef ARABICA_XSLT_NAMESPACE_STACK_HPP
#define ARABICA_XSLT_NAMESPACE_STACK_HPP

#include <map>
#include <vector>
 
namespace Arabica
{
namespace XSLT
{

class NamespaceStack 
{
public:
  typedef std::map<std::string, std::string> Scope;

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

  void declareNamespace(const std::string& given_prefix, const std::string& namespaceURI, bool attr = false)
  {
    if(findPrefix(namespaceURI) != EMPTY_STRING)
      return;

    bool remap = (attr && given_prefix.empty()) || (given_prefix == "xmlns");

    std::string prefix = !remap ? given_prefix : autoNamespacePrefix();

    prefixStack_.back()[prefix] = namespaceURI;
    uriStack_.back()[namespaceURI] = prefix;
  } // declareNamespace

  const std::string& findURI(const std::string& prefix) const
  {
    return searchStack(prefixStack_, prefix);
  } // findURI

  const std::string& findPrefix(const std::string& uri) const
  {
    return searchStack(uriStack_, uri);
  } // findPrefix

  Scope::const_iterator begin() { return prefixStack_.back().begin(); }
  Scope::const_iterator end() { return prefixStack_.back().end(); }

private:
  typedef std::vector<Scope> ScopeStack;

  const std::string& searchStack(const ScopeStack& stack, const std::string& key) const
  {
    for(ScopeStack::const_reverse_iterator ss = stack.rbegin(), se = stack.rend(); ss != se; ss++)
    {      
      Scope::const_iterator i = ss->find(key);
      if(i != ss->end())
        return i->second;
    }
    return EMPTY_STRING;
  } // searchStack

  std::string autoNamespacePrefix()
  {
    std::ostringstream ss;
    ss << "auto-ns" << autoNs_++;
    return ss.str();
  } // autoNamespacePrefix

  ScopeStack prefixStack_;
  ScopeStack uriStack_;
  std::string EMPTY_STRING;
  unsigned int autoNs_;
}; // class NamespaceStack

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_NAMESPACE_STACK_HPP

