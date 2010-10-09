#ifndef ARABICA_XPATH_VARIABLE_COMPILE_TIME_RESOLVER_HPP
#define ARABICA_XPATH_VARIABLE_COMPILE_TIME_RESOLVER_HPP

#include "xpath_variable.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class VariableCompileTimeResolver
{
public:
  virtual ~VariableCompileTimeResolver() { }

  virtual XPathExpression_impl<string_type, string_adaptor>* compileVariable(const string_type& namespace_uri, 
		                                                             const string_type& name) const = 0;
}; // class VariableCompileTimeResolver

template<class string_type, class string_adaptor>
class VariableCompileTimeResolverPtr : public boost::shared_ptr<VariableCompileTimeResolver<string_type, string_adaptor> >
{
public:
  explicit VariableCompileTimeResolverPtr(VariableCompileTimeResolver<string_type, string_adaptor>* vr) : 
      boost::shared_ptr<VariableCompileTimeResolver<string_type, string_adaptor> >(vr) 
  { 
  } // VariableCompileTimeResolverPtr
}; // class VariableCompileTimeResolverPtr

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class DefaultVariableCompileTimeResolver : public VariableCompileTimeResolver<string_type, string_adaptor>
{
public:
  virtual XPathExpression_impl<string_type, string_adaptor>* compileVariable(const string_type& namespace_uri,
									     const string_type& name) const
  {
    return new Variable<string_type, string_adaptor>(namespace_uri, name);
  } // compileVariable
}; // DefaultVariableCompileTimeResolver

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NullVariableCompileTimeResolver : public VariableCompileTimeResolver<string_type, string_adaptor>
{
public:
  virtual XPathExpression_impl<string_type, string_adaptor>* compileVariable(const string_type& namespace_uri, 
									     const string_type& name) const
  {
    return 0;
  } // compileVariable
}; // class NullVariableCompileTimeResolver


} // namespace XPath
} // namespace Arabica

#endif
