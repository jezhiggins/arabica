#ifndef ARABICA_XPATH_EXECUTION_CONTEXT_HPP
#define ARABICA_XPATH_EXECUTION_CONTEXT_HPP

#include "xpath_variable_resolver.hpp"
#include "xpath_resolver_holder.hpp"

namespace Arabica
{
namespace XPath
{
  
class ExecutionContext
{
public:
  ExecutionContext() : 
      position_(-1), 
      last_(-1)
  { 
  } // ExecutionContext

  ExecutionContext(size_t last, const ExecutionContext& parent) : 
      position_(-1), 
      last_(last),
      variableResolver_(parent.variableResolver_)
  { 
  } // ExecutionContext

  size_t position() const { return position_; }
  size_t last() const { return last_; }

  void setPosition(unsigned int pos) { position_ = pos; }

  const VariableResolver& variableResolver() const { return variableResolver_.get(); }
  void setVariableResolver(const VariableResolver& resolver) { variableResolver_.set(resolver); }
  void setVariableResolver(VariableResolverPtr& resolver) { variableResolver_.set(resolver); }

private:
  size_t position_;
  size_t last_;
  ResolverHolder<const VariableResolver> variableResolver_;

  ExecutionContext(const ExecutionContext&);
  ExecutionContext& operator=(const ExecutionContext&);
  bool operator==(const ExecutionContext&) const;
}; // class ExecutionContext

} // namespace XPath
} // namespace Arabica

#endif
