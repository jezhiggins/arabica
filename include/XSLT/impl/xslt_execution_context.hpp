#ifndef ARABICA_XSLT_EXECUTION_CONTEXT_HPP
#define ARABICA_XSLT_EXECUTION_CONTEXT_HPP

#include <ostream>
#include "xslt_sink.hpp"
#include "xslt_variable_stack.hpp"

namespace Arabica
{
namespace XSLT
{

class Stylesheet;
class ExecutionContext;

class Variable_declaration
{
protected:
  Variable_declaration() { }

public:
  virtual const std::string& namespace_uri() const = 0;
  virtual const std::string& name() const = 0;
  virtual Arabica::XPath::XPathValue<std::string> value(const DOM::Node<std::string>& node, 
                                                        ExecutionContext& context,
                                                        DOMSink& sink) const = 0;

private:
  Variable_declaration(const Variable_declaration&);
  Variable_declaration& operator=(const Variable_declaration&);
  bool operator==(const Variable_declaration&) const;
}; // class Variable_declaration

class ExecutionContext
{
public:
  ExecutionContext(const Stylesheet& stylesheet,
                   Sink& output,
                   std::ostream& error_output) :
      stylesheet_(stylesheet),
      sink_(output.asOutput()),
      message_sink_(error_output),
      to_msg_(false)
  {
		xpathContext_.setVariableResolver(stack_);
  } // ExecutionContext

  ExecutionContext(Sink& output,
                   ExecutionContext& rhs) :
    stylesheet_(rhs.stylesheet_),
    stack_(rhs.stack_),
    sink_(output.asOutput()),
    message_sink_(rhs.message_sink_),
    to_msg_(false)
  {
		xpathContext_.setVariableResolver(stack_);
    xpathContext_.setCurrentNode(rhs.xpathContext().currentNode());
    xpathContext_.setPosition(rhs.xpathContext().position());
    xpathContext_.setLast(rhs.xpathContext().last());
  } // ExecutionContext

  const Stylesheet& stylesheet() const { return stylesheet_; }

  Output& sink() 
  { 
    return !to_msg_ ? sink_ : message_sink_.asOutput();
  } // sink
  void redirectToMessageSink(bool redirect) { to_msg_ = redirect; }

  const Arabica::XPath::ExecutionContext<std::string>& xpathContext() const { return xpathContext_; }

  void topLevelParam(const DOM::Node<std::string>& node, const Variable_declaration& param);
  void passParam(const DOM::Node<std::string>& node, const Variable_declaration& param);
  void declareParam(const DOM::Node<std::string>& node, const Variable_declaration& param); 
  void declareVariable(const DOM::Node<std::string>& node, const Variable_declaration& variable); 
  void freezeTopLevel();
  void injectGlobalScope(const Scope& scope);

  void setPosition(const DOM::Node<std::string>& current, size_t pos) { setPosition(current, static_cast<int>(pos)); }
  void setPosition(const DOM::Node<std::string>& current, int pos) 
  {
    xpathContext_.setCurrentNode(current);
    xpathContext_.setPosition(pos);
  } // setPosition

  int setLast(int last)
  {
    int old = xpathContext_.last();
    xpathContext_.setLast(last);
    return old;
  } // setLast

private:
  void pushStackFrame() { stack_.pushScope(); }
  void popStackFrame() { stack_.popScope(); }

private:
  const Stylesheet& stylesheet_;
  VariableStack stack_;
  Arabica::XPath::ExecutionContext<std::string> xpathContext_;
  Output& sink_;
  StreamSink message_sink_;
  bool to_msg_;

  friend class StackFrame;
}; // class ExecutionContext

///////////////////////////
class VariableClosure : public Variable_instance
{
public:
  static Variable_instance_ptr create(const Variable_declaration& var, const DOM::Node<std::string>& node, ExecutionContext& context)
  {
    return Variable_instance_ptr(new VariableClosure(var, node, context));
  } // create

  virtual const std::string& namespace_uri() const { return var_.namespace_uri(); }
  virtual const std::string& name() const { return var_.name(); }

  virtual Arabica::XPath::XPathValue<std::string> value() const 
  {
    if(!value_)
      value_ = var_.value(node_, context_, sink_);
    return value_;
  } // value

  virtual void injectGlobalScope(const Scope& scope) const
  {
    context_.injectGlobalScope(scope);
  } // globalScope

private:
  VariableClosure(const Variable_declaration& var, 
                  const DOM::Node<std::string>& node, 
                  ExecutionContext& context) :
      var_(var),
      sink_(),
      node_(node),
      context_(sink_, context)
  {
  } // VariableClosure

  const Variable_declaration& var_;
  mutable DOMSink sink_;
  const DOM::Node<std::string> node_;
  mutable ExecutionContext context_;
  mutable Arabica::XPath::XPathValuePtr<std::string> value_;

  VariableClosure();
  VariableClosure(const VariableClosure&);
  VariableClosure& operator=(const VariableClosure&);
  const VariableClosure& operator==(const VariableClosure&) const;
}; // class VariableClosure

///////////////////////////
void ExecutionContext::topLevelParam(const DOM::Node<std::string>& node, const Variable_declaration& param)
{
  stack_.topLevelParam(VariableClosure::create(param, node, *this));
} // passParam

void ExecutionContext::passParam(const DOM::Node<std::string>& node, const Variable_declaration& param)
{
  stack_.passParam(VariableClosure::create(param, node, *this));
} // passParam

void ExecutionContext::declareParam(const DOM::Node<std::string>& node, const Variable_declaration& param) 
{
  stack_.declareParam(VariableClosure::create(param, node, *this)); 
} // declareParam

void ExecutionContext::declareVariable(const DOM::Node<std::string>& node, const Variable_declaration& variable) 
{ 
  stack_.declareVariable(VariableClosure::create(variable, node, *this)); 
} // declareVariable

void ExecutionContext::freezeTopLevel()
{
  stack_.freezeTopLevel();
} // freezeTopLevel

void ExecutionContext::injectGlobalScope(const Scope& scope) 
{
  stack_.injectGlobalScope(scope);
} // injectGlobalScope

///////////////////////////
class StackFrame
{
public:
  StackFrame(ExecutionContext& context) : context_(context) { context_.pushStackFrame(); }
  ~StackFrame() { context_.popStackFrame(); }

private:
  ExecutionContext& context_;
  
  StackFrame(const StackFrame&);
  StackFrame& operator=(const StackFrame&);
  bool operator==(const StackFrame&) const;
}; // class StackFrame

///////////////////////////
class LastFrame
{
public:
  LastFrame(ExecutionContext& context, int last) : context_(context) 
  { 
    oldLast_ = context_.setLast(last);
  } // LastFrame

  LastFrame(ExecutionContext& context, size_t last) : context_(context) 
  { 
    oldLast_ = context_.setLast(static_cast<int>(last));
  } // LastFrame

  ~LastFrame()
  {
    context_.setLast(oldLast_);
  } // ~LastFrame

private:
  ExecutionContext& context_;
  int oldLast_;

  LastFrame(const LastFrame&);
  LastFrame& operator=(const LastFrame&);
  bool operator==(const LastFrame&) const;
}; // class LastFrame

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_EXECUTION_CONTEXT_HPP

