#ifndef ARABICA_XPATH_NAMESPACE_CONTEXT_HPP
#define ARABICA_XPATH_NAMESPACE_CONTEXT_HPP

#include <string>
#include <map>
#include <stdexcept>
#include <boost/shared_ptr.hpp>

namespace Arabica
{

namespace XPath
{

class UnboundNamespacePrefixException : public std::runtime_error
{
public:
  UnboundNamespacePrefixException(const std::string& thing) : std::runtime_error("The prefix '" + thing + "' is not bound to a namespace URI") { }
}; // class UnboundNamespacePrefixException

template<class string_type, class string_adaptor>
class NamespaceContext
{
  public:
    NamespaceContext() { } 
    virtual ~NamespaceContext() { };

    virtual string_type namespaceURI(const string_type& prefix) const = 0;

  private:
    NamespaceContext(const NamespaceContext&);
    NamespaceContext& operator=(const NamespaceContext&);
    bool operator==(const NamespaceContext&) const;
}; // class NamespaceContext 

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NamespaceContextPtr : public boost::shared_ptr<NamespaceContext<string_type, string_adaptor> > 
{
public:
  explicit NamespaceContextPtr(NamespaceContext<string_type, string_adaptor> * nc) : 
          boost::shared_ptr<NamespaceContext<string_type, string_adaptor> >(nc) 
  { 
  } // NamespaceContextPtr
}; // class NamespaceContextPtr

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NullNamespaceContext : public NamespaceContext<string_type, string_adaptor>
{  
  public:
    virtual string_type namespaceURI(const string_type& prefix) const 
    { 
      throw UnboundNamespacePrefixException(string_adaptor().asStdString(prefix)); 
    } // namespaceURI
}; // class NullNamespaceContext

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class StandardNamespaceContext : public NamespaceContext<string_type, string_adaptor>
{
  public:
    StandardNamespaceContext() { }
    ~StandardNamespaceContext() { }

    virtual string_type namespaceURI(const string_type& prefix) const
    {
      typename NSMap::const_iterator n = map_.find(prefix);
      if(n == map_.end())
        throw UnboundNamespacePrefixException(string_adaptor().asStdString(prefix)); 
      return (*n).second;
    } // namespaceURI

    void addNamespaceDeclaration(const string_type& namespaceURI, const string_type& prefix)
    {
      map_[prefix] = namespaceURI;
    } // addNamespaceDeclaration

  private:
    StandardNamespaceContext(const StandardNamespaceContext& rhs) : map_(rhs.map_) { }

    typedef std::map<string_type, string_type> NSMap;
    NSMap map_;
}; // class StandardNamespaceContext

} // namespace XPath

} // namespace Arabica
#endif
