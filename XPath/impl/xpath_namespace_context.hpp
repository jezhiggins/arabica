#ifndef ARABICA_XPATH_NAMESPACE_CONTEXT_HPP
#define ARABICA_XPATH_NAMESPACE_CONTEXT_HPP

#include <string>
#include <map>
#include <stdexcept>

namespace Arabica
{

namespace XPath
{

class UnboundNamespacePrefixException : public std::runtime_error
{
public:
  UnboundNamespacePrefixException(const std::string& thing) : std::runtime_error("The prefix '" + thing + "' is not bound to a namespace URI") { }
}; // class UnboundNamespacePrefixException

class NamespaceContext
{
  public:
    NamespaceContext() { } 
    virtual ~NamespaceContext() { };

    virtual std::string namespaceURI(const std::string& prefix) const = 0;

    virtual NamespaceContext* clone() const = 0;

  private:
    NamespaceContext(const NamespaceContext&);
    NamespaceContext& operator=(const NamespaceContext&);
    bool operator==(const NamespaceContext&) const;
}; // class NamespaceContext 

typedef boost::shared_ptr<NamespaceContext> NamespaceContextPtr;

class NullNamespaceContext : public NamespaceContext
{  
  public:
    virtual std::string namespaceURI(const std::string& prefix) const { throw UnboundNamespacePrefixException(prefix); }
    virtual NamespaceContext* clone() const { return new NullNamespaceContext; }
}; // class NullNamespaceContext

class StandardNamespaceContext : public NamespaceContext
{
  public:
    StandardNamespaceContext() { }
    ~StandardNamespaceContext() { }

    virtual std::string namespaceURI(const std::string& prefix) const
    {
      NSMap::const_iterator n = map_.find(prefix);
      if(n == map_.end())
        throw UnboundNamespacePrefixException(prefix);
      return (*n).second;
    } // namespaceURI

    void addNamespaceDeclaration(const std::string& namespaceURI, const std::string& prefix)
    {
      map_[prefix] = namespaceURI;
    } // addNamespaceDeclaration

    virtual StandardNamespaceContext* clone() const { return new StandardNamespaceContext(*this); }

  private:
    StandardNamespaceContext(const StandardNamespaceContext& rhs) : map_(rhs.map_) { }

    typedef std::map<std::string, std::string> NSMap;
    NSMap map_;
}; // class StandardNamespaceContext

} // namespace XPath

} // namespace Arabica
#endif
