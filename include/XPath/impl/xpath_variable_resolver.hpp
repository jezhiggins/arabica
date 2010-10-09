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

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class VariableResolver
{
public:
  virtual ~VariableResolver() { }

  virtual XPathValue<string_type, string_adaptor> resolveVariable(const string_type& namespace_uri_,
                                                                  const string_type& name) const = 0; 
}; // class VariableResolver

template<class string_type, class string_adaptor>
class VariableResolverPtr : public boost::shared_ptr<VariableResolver<string_type, string_adaptor> >
{
public:
  explicit VariableResolverPtr(VariableResolver<string_type, string_adaptor>* vr) : 
      boost::shared_ptr<VariableResolver<string_type, string_adaptor> >(vr) 
  { 
  } // VariableResolverPtr
}; // class VariableResolverPtr

template<class string_type, class string_adaptor>
class NullVariableResolver : public VariableResolver<string_type, string_adaptor>
{
public:
  virtual XPathValue<string_type, string_adaptor> resolveVariable(const string_type& namespace_uri,
                                                     const string_type& name) const
  {
    string_type error;
    if(!string_adaptor::empty(namespace_uri))
    {
      string_adaptor::append(error, string_adaptor::construct_from_utf8("{"));
      string_adaptor::append(error, namespace_uri);
      string_adaptor::append(error, string_adaptor::construct_from_utf8("}"));
    } // if ...
    string_adaptor::append(error, name);
    throw UnboundVariableException(string_adaptor().asStdString(error));
  } // resolveVariable
}; // NullVariableResolver

} // namespace XPath
} // namespace Arabica

#endif
