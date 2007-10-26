#ifndef ARABICA_XSLT_VARIABLE_STACK_HPP
#define ARABICA_XSLT_VARIABLE_STACK_HPP

#include <XPath/XPath.hpp>
#include <map>
#include <vector>

namespace Arabica
{
namespace XSLT
{

class Variable_instance;
typedef boost::shared_ptr<const Variable_instance> Variable_instance_ptr;
typedef std::map<std::string, Variable_instance_ptr> Scope;

class Variable_instance
{
public:
  Variable_instance() { }
  virtual ~Variable_instance() { }
  
  virtual const std::string& namespace_uri() const = 0;
  virtual const std::string& name() const = 0;
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

	void popScope()
	{
    params_.pop_back();
		stack_.pop_back();
	} // popScope

  void topLevelParam(Variable_instance_ptr param)
  {
    params_.front()[clarkName(param)] = param;
  } // topLevelParam

  std::string passParam(Variable_instance_ptr param)
  {
    std::string clark_name = clarkName(param);
    params_.back()[clark_name] = param;
    return clark_name;
  } // passParam

  void unpassParam(const std::string& name)
  {
    params_.back().erase(name);
  } // unpassParam

  void declareParam(Variable_instance_ptr param)
  {
    ScopeStack::reverse_iterator p = params_.rbegin()+1;    
		Scope::iterator i = p->find(clarkName(param));
		if(i == p->end())
      declareVariable(param);
    else
      declareVariable(i->second);
  } // declareParam

	void declareVariable(Variable_instance_ptr var)
	{
		stack_.back()[clarkName(var)] = var;
	} // declareVariable

  void freezeTopLevel()
  {
    const Scope& top = stack_.front();
    for(Scope::const_iterator v = top.begin(), ve = top.end(); v != ve; ++v)
      v->second->injectGlobalScope(top);
  } // freezeTopLevel

  void injectGlobalScope(const Scope& scope)
  {
    stack_.front() = scope;
  } // injectGlobalScope

  virtual Arabica::XPath::XPathValue<std::string> resolveVariable(const std::string& namespace_uri,
                                                                  const std::string& name) const
  {
    std::string clarkName = "{" + namespace_uri + "}" + name;
		Arabica::XPath::XPathValue<std::string> val = lookup(stack_.back(), clarkName);
		if(val != 0)
			return val;

		val = lookup(stack_.front(), clarkName); // try our "global" scope
		if(val == 0)
			throw Arabica::XPath::UnboundVariableException(clarkName);

		return val;
  } // resolveVariable

private:
	typedef std::vector<Scope> ScopeStack;

  std::string clarkName(Variable_instance_ptr var)
  {
    return "{" + var->namespace_uri() + "}" + var->name();
  } // clarkName

	Arabica::XPath::XPathValue<std::string> lookup(const Scope& scope, const std::string& name) const
	{
		Scope::const_iterator i = scope.find(name);
		if(i == scope.end())
			return Arabica::XPath::XPathValue<std::string>(0);

		return i->second->value();
	} // lookup

	ScopeStack stack_;
  ScopeStack params_;
}; // class VariableStack

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_VARIABLE_STACK_HPP

