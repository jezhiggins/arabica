#ifndef ARABICA_XSLT_VARIABLE_STACK_HPP
#define ARABICA_XSLT_VARIABLE_STACK_HPP

#include <XPath/XPath.hpp>
#include <map>
#include <vector>
#include "xslt_precedence.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor> class Variable_instance;

template<class string_type, class string_adaptor>
struct ScopeType
{
  typedef boost::shared_ptr<Variable_instance<string_type, string_adaptor> > Variable_instance_ptr;
  typedef std::map<string_type, Variable_instance_ptr> Scope;
}; // class Scope

template<class string_type, class string_adaptor>
class Variable_instance
{
public:
  typedef typename ScopeType<string_type, string_adaptor>::Scope Scope;
  Variable_instance() { }
  virtual ~Variable_instance() { }
  
  virtual const string_type& name() const = 0;
  virtual const Precedence& precedence() const = 0;
  virtual Arabica::XPath::XPathValue<string_type, string_adaptor> value() const = 0;

  virtual void injectGlobalScope(const Scope& scope) const = 0;

private:
  Variable_instance(const Variable_instance&);
  Variable_instance& operator=(const Variable_instance&);
  bool operator==(const Variable_instance&) const;
}; // Variable_instance

template<class string_type, class string_adaptor>
class VariableStack : public Arabica::XPath::VariableResolver<string_type, string_adaptor>
{
  typedef typename ScopeType<string_type, string_adaptor>::Scope Scope;
  typedef std::vector<Scope> ScopeStack;
  
public:
  typedef typename ScopeType<string_type, string_adaptor>::Variable_instance_ptr Variable_instance_ptr;
  typedef Arabica::XPath::XPathValue<string_type, string_adaptor> XPathValue;

  VariableStack()
  {
    stack_.push_back(Scope());
    
    params_.push_back(Scope());
    params_.push_back(Scope());
  } // VariableStack
  
  VariableStack(const VariableStack& rhs) :
    stack_(rhs.stack_),
    params_(rhs.params_)
  {
  } // VariableStack

  void pushScope()
  {
    stack_.push_back(Scope());
    params_.push_back(Scope());
  } // pushScope

  void chainScope()
  {
    stack_.push_back(Scope(stack_.back()));
    params_.push_back(Scope(params_.back()));
  } // chainsScope

  void popScope()
  {
    params_.pop_back();
    stack_.pop_back();
  } // popScope
  
  void topLevelParam(Variable_instance_ptr param)
  {
    params_.front()[param->name()] = param;
  } // topLevelParam

  string_type passParam(Variable_instance_ptr param)
  {
    string_type name = param->name();
    Scope& params = params_.back();

    if(params.find(name) != params.end())
      throw std::runtime_error("Duplicate parameter name in xsl:with-param - " + string_adaptor::asStdString(name));
    params[name] = param;
    return name;
  } // passParam

  void unpassParam(const string_type& name)
  {
    params_.back().erase(name);
  } // unpassParam

  bool findPassedParam(const string_type& name)
  {
    typename ScopeStack::reverse_iterator p = params_.rbegin()+1;    
    typename Scope::iterator i = p->find(name);
    if(i == p->end())
      return false;
    declareVariable(i->second);
    return true;
  } // findPassedParam

  void declareParam(Variable_instance_ptr param)
  {
    declareVariable(param);
  } // declareParam

  void declareVariable(Variable_instance_ptr var)
  {
    string_type name = var->name();
    Scope& stack = stack_.back();
    
    if(stack.find(name) != stack.end())
    {
      const Precedence& current_p = stack[name]->precedence();
      if(var->precedence() == current_p)
        throw std::runtime_error("Duplicate variable name : " + string_adaptor::asStdString(name));
      if(current_p.is_descendant(var->precedence()))
        return;
      if(current_p > var->precedence())
        return;
    } // if ...

    if(var->precedence() == Precedence::FrozenPrecedence()) // we're running so resolve immediately
      var->value();

    stack[name] = var;
  } // declareVariable
  
  void freezeTopLevel()
  {
    const Scope& top = stack_.front();
    for(typename Scope::const_iterator v = top.begin(), ve = top.end(); v != ve; ++v)
      v->second->injectGlobalScope(top);
    for(typename Scope::const_iterator v = top.begin(), ve = top.end(); v != ve; ++v)
      lookup(top, v->first);
  } // freezeTopLevel
  
  void injectGlobalScope(const Scope& scope)
  {
    stack_.front() = scope;
  } // injectGlobalScope
  
  virtual XPathValue resolveVariable(const string_type& namespace_uri,
                                     const string_type& name) const
  {
    typedef Arabica::text::Unicode<string_adaptor::value_type> UnicodeT;

    string_type clarkName = namespace_uri.empty() ? name : UnicodeT::LEFT_SQUARE_BRACKET + namespace_uri + UnicodeT::RIGHT_SQUARE_BRACKET + name;
    if(std::find(resolutionStack_.begin(), resolutionStack_.end(), clarkName) != resolutionStack_.end())
      throw std::runtime_error("Circular dependency: " + string_adaptor::asStdString(clarkName) + " refers to itself directly or indirectly.");

    resolutionStack_.push_back(clarkName);
    XPathValue val = lookup(stack_.back(), clarkName);
    resolutionStack_.pop_back();
    
    if(val != 0)
      return val;
    
    val = lookup(stack_.front(), clarkName); // try our "global" scope
    if(val == 0)
      throw Arabica::XPath::UnboundVariableException(string_adaptor::asStdString(clarkName));
    
    return val;
  } // resolveVariable
  
private:
  XPathValue lookup(const Scope& scope, const string_type& name) const
  {
    typename Scope::const_iterator i = scope.find(name);
    if(i == scope.end())
      return XPathValue(0);
    
    return i->second->value();
  } // lookup
  
  ScopeStack stack_;
  ScopeStack params_;
  mutable std::vector<string_type> resolutionStack_;
}; // class VariableStack

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_VARIABLE_STACK_HPP

