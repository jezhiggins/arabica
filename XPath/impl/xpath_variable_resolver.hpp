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

template<class string_type>
class VariableResolver
{
public:
  virtual ~VariableResolver() { }

  virtual XPathValuePtr<string_type> resolveVariable(const string_type& name) const = 0; 
}; // class VariableResolver

template<class string_type>
class VariableResolverPtr : public boost::shared_ptr<VariableResolver<string_type> >
{
public:
  explicit VariableResolverPtr(VariableResolver<string_type>* vr) : boost::shared_ptr<VariableResolver<string_type> >(vr) { }
}; // class VariableResolverPtr

template<class string_type>
class NullVariableResolver : public VariableResolver<string_type>
{
public:
  virtual XPathValuePtr<string_type> resolveVariable(const string_type& name) const
  {
    throw UnboundVariableException(name);
  } // resolveVariable
}; // NullVariableResolver

} // namespace XPath
} // namespace Arabica

#endif
