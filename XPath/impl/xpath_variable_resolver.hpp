#ifndef ARABICA_XPATH_VARIABLE_RESOLVER_HPP
#define ARABICA_XPATH_VARIABLE_RESOLVER_HPP

#include <stdexcept>
#include "xpath_object.hpp"

namespace Arabica
{
namespace XPath
{

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

class VariableResolverPtr : public boost::shared_ptr<VariableResolver>
{
public:
  explicit VariableResolverPtr(VariableResolver* vr) : boost::shared_ptr<VariableResolver>(vr) { }
}; // class VariableResolverPtr

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
