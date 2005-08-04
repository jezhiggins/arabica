#ifndef ARABICA_XPATH_VARIABLE_RESOLVER_HPP
#define ARABICA_XPATH_VARIABLE_RESOLVER_HPP

#include <boost/shared_ptr.hpp>

namespace Arabica
{
namespace XPath
{

class XPathValue;
typedef boost::shared_ptr<const XPathValue> XPathValuePtr;

class UnboundVariableException : public std::runtime_error
{
public:
  UnboundVariableException(const std::string& thing) : std::runtime_error("The variable '" + thing + "' is undefined.") { }
}; // class UnboundVariableException

class VariableResolver
{
public:
  virtual ~VariableResolver() { }

  virtual XPathValuePtr resolveVariable(const std::string& name) const = 0; 
}; // class VariableResolver

typedef boost::shared_ptr<VariableResolver> VariableResolverPtr;

class NullVariableResolver : public VariableResolver
{
public:
  virtual XPathValuePtr resolveVariable(const std::string& name) const
  {
    throw UnboundVariableException(name);
  } // resolveVariable
}; // NullVariableResolver

} // namespace XPath
} // namespace Arabica

#endif
