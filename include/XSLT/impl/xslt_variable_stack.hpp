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

class Variable_instance;
typedef boost::shared_ptr<Variable_instance> Variable_instance_ptr;
typedef std::map<std::string, Variable_instance_ptr> Scope;

class Variable_instance
{
public:
  Variable_instance() { }
  virtual ~Variable_instance() { }
  
  virtual const std::string& name() const = 0;
  virtual const Precedence& precedence() const = 0;
  virtual Arabica::XPath::XPathValue<std::string> value() const = 0;

  virtual void injectGlobalScope(const Scope& scope) const = 0;

private:
  Variable_instance(const Variable_instance&);
  Variable_instance& operator=(const Variable_instance&);
  bool operator==(const Variable_instance&) const;
}; // Variable_instance

class VariableStack : public Arabica::XPath::VariableResolver<std::string>
{
public:
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

  std::string passParam(Variable_instance_ptr param)
  {
    std::string name = param->name();
    Scope& params = params_.back();

    if(params.find(name) != params.end())
      throw std::runtime_error("Duplicate parameter name in xsl:with-param - " + name);
    params[name] = param;
    return name;
  } // passParam

  void unpassParam(const std::string& name)
  {
    params_.back().erase(name);
  } // unpassParam

  bool findPassedParam(const std::string& name)
  {
    ScopeStack::reverse_iterator p = params_.rbegin()+1;    
    Scope::iterator i = p->find(name);
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
    std::string name = var->name();
    Scope& stack = stack_.back();
    
    if(stack.find(name) != stack.end())
    {
      const Precedence& current_p = stack[name]->precedence();
      if(var->precedence() == current_p)
        throw std::runtime_error("Duplicate variable name : " + name);
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
    for(Scope::const_iterator v = top.begin(), ve = top.end(); v != ve; ++v)
      v->second->injectGlobalScope(top);
    for(Scope::const_iterator v = top.begin(), ve = top.end(); v != ve; ++v)
      lookup(top, v->first);
  } // freezeTopLevel
  
  void injectGlobalScope(const Scope& scope)
  {
    stack_.front() = scope;
  } // injectGlobalScope
  
  virtual Arabica::XPath::XPathValue<std::string> resolveVariable(const std::string& namespace_uri,
                                                                  const std::string& name) const
  {
    std::string clarkName = namespace_uri.empty() ? name : "{" + namespace_uri + "}" + name;
    if(std::find(resolutionStack_.begin(), resolutionStack_.end(), clarkName) != resolutionStack_.end())
      throw std::runtime_error("Circular dependency: " + clarkName + " refers to itself directly or indirectly.");

    resolutionStack_.push_back(clarkName);
    Arabica::XPath::XPathValue<std::string> val = lookup(stack_.back(), clarkName);
    resolutionStack_.pop_back();
    
    if(val != 0)
      return val;
    
    val = lookup(stack_.front(), clarkName); // try our "global" scope
    if(val == 0)
      throw Arabica::XPath::UnboundVariableException(clarkName);
    
    return val;
  } // resolveVariable
  
private:
  typedef std::vector<Scope> ScopeStack;
  
  Arabica::XPath::XPathValue<std::string> lookup(const Scope& scope, const std::string& name) const
  {
    Scope::const_iterator i = scope.find(name);
    if(i == scope.end())
      return Arabica::XPath::XPathValue<std::string>(0);
    
    return i->second->value();
  } // lookup
  
  ScopeStack stack_;
  ScopeStack params_;
  mutable std::vector<std::string> resolutionStack_;
}; // class VariableStack

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_VARIABLE_STACK_HPP

