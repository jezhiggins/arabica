#ifndef ARABICA_XPATH_EXECUTION_CONTEXT_HPP
#define ARABICA_XPATH_EXECUTION_CONTEXT_HPP

#include <Utils/StringAdaptor.h>
#include "xpath_variable_resolver.hpp"
#include "xpath_resolver_holder.hpp"

namespace Arabica
{
namespace XPath
{
 
template<class string_type, class string_adaptor>
class ExecutionContext
{
public:
  ExecutionContext() : 
      position_(static_cast<size_t>(-1)), 
      last_(static_cast<size_t>(-1))
  { 
  } // ExecutionContext

  ExecutionContext(size_t last, const ExecutionContext& parent) : 
      position_(static_cast<size_t>(-1)), 
      last_(last),
      variableResolver_(parent.variableResolver_)
  { 
  } // ExecutionContext

  size_t position() const { return position_; }
  size_t last() const { return last_; }

  void setPosition(unsigned int pos) { position_ = pos; }

  const VariableResolver<string_type, string_adaptor>& variableResolver() const { return variableResolver_.get(); }
  void setVariableResolver(const VariableResolver<string_type, string_adaptor>& resolver) { variableResolver_.set(resolver); }
  void setVariableResolver(VariableResolverPtr<string_type,string_adaptor>& resolver) { variableResolver_.set(resolver); }

private:
  size_t position_;
  size_t last_;
  ResolverHolder<const VariableResolver<string_type, string_adaptor> > variableResolver_;

  ExecutionContext(const ExecutionContext&);
  ExecutionContext& operator=(const ExecutionContext&);
  bool operator==(const ExecutionContext&) const;
}; // class ExecutionContext

} // namespace XPath
} // namespace Arabica

#endif
