#ifndef ARABICA_XPATH_EXECUTION_CONTEXT_HPP
#define ARABICA_XPATH_EXECUTION_CONTEXT_HPP

#include <Arabica/StringAdaptor.hpp>
#include "xpath_variable_resolver.hpp"
#include "xpath_resolver_holder.hpp"

namespace Arabica
{
namespace XPath
{
 
template<class string_type, class string_adaptor = default_string_adaptor<std::string> >
class ExecutionContext
{
public:
  ExecutionContext() : 
      position_(-1), 
      last_(-1)
  { 
  } // ExecutionContext

  ExecutionContext(size_t last, const ExecutionContext& parent) : 
      current_(parent.current_),
      position_(-1), 
      last_(static_cast<int>(last)),
      variableResolver_(parent.variableResolver_)
  { 
  } // ExecutionContext

  const DOM::Node<string_type, string_adaptor>& currentNode() const { return current_; }
  int position() const { return position_; }
  int last() const { return last_; }

  void setCurrentNode(const DOM::Node<string_type, string_adaptor>& current) { current_ = current; }
  void setPosition(int pos) { position_ = pos; }
  void setLast(int last) { last_ = last; }

  const VariableResolver<string_type, string_adaptor>& variableResolver() const { return variableResolver_.get(); }
  void setVariableResolver(const VariableResolver<string_type, string_adaptor>& resolver) { variableResolver_.set(resolver); }
  void setVariableResolver(VariableResolverPtr<string_type,string_adaptor>& resolver) { variableResolver_.set(resolver); }

private:
  DOM::Node<string_type, string_adaptor> current_;
  int position_;
  int last_;
  impl::ResolverHolder<const VariableResolver<string_type, string_adaptor> > variableResolver_;

  ExecutionContext(const ExecutionContext&);
  ExecutionContext& operator=(const ExecutionContext&);
  bool operator==(const ExecutionContext&) const;
}; // class ExecutionContext

} // namespace XPath
} // namespace Arabica

#endif
