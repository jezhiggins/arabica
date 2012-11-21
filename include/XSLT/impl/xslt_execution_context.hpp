#ifndef ARABICA_XSLT_EXECUTION_CONTEXT_HPP
#define ARABICA_XSLT_EXECUTION_CONTEXT_HPP

#include <ostream>
#include "xslt_sink.hpp"
#include "xslt_variable_stack.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor> class CompiledStylesheet;
template<class string_type, class string_adaptor> class ExecutionContext;
template<class string_type, class string_adaptor> class StackFrame;
template<class string_type, class string_adaptor> class ChainStackFrame;

template<class string_type, class string_adaptor>
class Variable_declaration
{
protected:
  Variable_declaration() { }

public:
  virtual const string_type& name() const = 0;
  virtual Arabica::XPath::XPathValue<string_type, string_adaptor> value(const DOM::Node<string_type, string_adaptor>& node, 
                                                        ExecutionContext<string_type, string_adaptor>& context,
                                                        DOMSink<string_type, string_adaptor>& sink) const = 0;
  virtual const Precedence& precedence() const = 0;

private:
  Variable_declaration(const Variable_declaration&);
  Variable_declaration& operator=(const Variable_declaration&);
  bool operator==(const Variable_declaration&) const;
}; // class Variable_declaration

template<class string_type, class string_adaptor>
class ExecutionContext
{
public:
  ExecutionContext(const CompiledStylesheet<string_type, string_adaptor>& stylesheet,
                   Sink<string_type, string_adaptor>& output,
                   std::basic_ostream<typename string_adaptor::value_type>& error_output) :
      stylesheet_(stylesheet),
      sink_(output.asOutput()),
      message_sink_(error_output),
      to_msg_(0)
  {
		xpathContext_.setVariableResolver(stack_);
    sink_.set_warning_sink(message_sink_.asOutput());
    message_sink_.asOutput().set_warning_sink(message_sink_.asOutput());
  } // ExecutionContext

  ExecutionContext(Sink<string_type, string_adaptor>& output, 
                   ExecutionContext<string_type, string_adaptor>& rhs) :
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

  const CompiledStylesheet<string_type, string_adaptor>& stylesheet() const { return stylesheet_; }

  Output<string_type, string_adaptor>& sink() 
  { 
    return !to_msg_ ? sink_ : message_sink_.asOutput();
  } // sink
  void redirectToMessageSink() { ++to_msg_; }
  void revertFromMessageSink() { --to_msg_; }

  const Arabica::XPath::ExecutionContext<string_type, string_adaptor>& xpathContext() const { return xpathContext_; }

  void topLevelParam(const DOM::Node<string_type, string_adaptor>& node, const Variable_declaration<string_type, string_adaptor>& param);
  string_type passParam(const DOM::Node<string_type, string_adaptor>& node, const Variable_declaration<string_type, string_adaptor>& param);
  void unpassParam(const string_type& name);
  void declareParam(const DOM::Node<string_type, string_adaptor>& node, const Variable_declaration<string_type, string_adaptor>& param); 
  void declareVariable(const DOM::Node<string_type, string_adaptor>& node, const Variable_declaration<string_type, string_adaptor>& variable); 
  void freezeTopLevel();
  void injectGlobalScope(const typename ScopeType<string_type, string_adaptor>::Scope& scope);

  void setPosition(const DOM::Node<string_type, string_adaptor>& current, size_t pos) { setPosition(current, static_cast<int>(pos)); }
  void setPosition(const DOM::Node<string_type, string_adaptor>& current, int pos) 
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
  void chainStackFrame() { stack_.chainScope(); }
  void popStackFrame() { stack_.popScope(); }

private:
  const CompiledStylesheet<string_type, string_adaptor>& stylesheet_;
  VariableStack<string_type, string_adaptor> stack_;
  Arabica::XPath::ExecutionContext<string_type, string_adaptor> xpathContext_;
  Output<string_type, string_adaptor>& sink_;
  StreamSink<string_type, string_adaptor> message_sink_;
  int to_msg_;

  friend class StackFrame<string_type, string_adaptor> ;
  friend class ChainStackFrame<string_type, string_adaptor> ;
}; // class ExecutionContext

///////////////////////////
template<class string_type, class string_adaptor>
class VariableClosure : public Variable_instance<string_type, string_adaptor>
{
public:
  typedef typename ScopeType<string_type, string_adaptor>::Variable_instance_ptr Variable_instance_ptr;
  typedef typename ScopeType<string_type, string_adaptor>::Scope Scope;

  static Variable_instance_ptr create(const Variable_declaration<string_type, string_adaptor>& var, 
                                      const DOM::Node<string_type, string_adaptor>& node,
                                      ExecutionContext<string_type, string_adaptor>& context)
  {
    return Variable_instance_ptr(new VariableClosure(var, node, context));
  } // create

  virtual const string_type& name() const { return var_.name(); }
  virtual const Precedence& precedence() const { return var_.precedence(); }

  virtual Arabica::XPath::XPathValue<string_type, string_adaptor> value() const 
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
  VariableClosure(const Variable_declaration<string_type, string_adaptor>& var, 
                  const DOM::Node<string_type, string_adaptor>& node, 
                  ExecutionContext<string_type, string_adaptor>& context) :
      var_(var),
      sink_(),
      node_(node),
      context_(sink_, context)
  {
  } // VariableClosure

  const Variable_declaration<string_type, string_adaptor>& var_;
  mutable DOMSink<string_type, string_adaptor> sink_;
  const DOM::Node<string_type, string_adaptor> node_;
  mutable ExecutionContext<string_type, string_adaptor> context_;
  mutable Arabica::XPath::XPathValue<string_type, string_adaptor> value_;

  VariableClosure();
  VariableClosure(const VariableClosure&);
  VariableClosure& operator=(const VariableClosure&);
  const VariableClosure& operator==(const VariableClosure&) const;
}; // class VariableClosure

///////////////////////////
template<class string_type, class string_adaptor>
void ExecutionContext<string_type, string_adaptor>::topLevelParam(const DOM::Node<string_type, string_adaptor>& node, const Variable_declaration<string_type, string_adaptor>& param)
{
  stack_.topLevelParam(VariableClosure<string_type, string_adaptor>::create(param, node, *this));
} // topLevelParam

template<class string_type, class string_adaptor>
string_type ExecutionContext<string_type, string_adaptor>::passParam(const DOM::Node<string_type, string_adaptor>& node, const Variable_declaration<string_type, string_adaptor>& param)
{
  return stack_.passParam(VariableClosure<string_type, string_adaptor>::create(param, node, *this));
} // passParam

template<class string_type, class string_adaptor>
void ExecutionContext<string_type, string_adaptor>::unpassParam(const string_type& name)
{
  stack_.unpassParam(name);
} // unpassParam

template<class string_type, class string_adaptor>
void ExecutionContext<string_type, string_adaptor>::declareParam(const DOM::Node<string_type, string_adaptor>& node, const Variable_declaration<string_type, string_adaptor>& param) 
{
  if(!stack_.findPassedParam(param.name()))
    stack_.declareParam(VariableClosure<string_type, string_adaptor>::create(param, node, *this)); 
} // declareParam

template<class string_type, class string_adaptor>
void ExecutionContext<string_type, string_adaptor>::declareVariable(const DOM::Node<string_type, string_adaptor>& node, const Variable_declaration<string_type, string_adaptor>& variable) 
{ 
  stack_.declareVariable(VariableClosure<string_type, string_adaptor>::create(variable, node, *this)); 
} // declareVariable

template<class string_type, class string_adaptor>
void ExecutionContext<string_type, string_adaptor>::freezeTopLevel()
{
  stack_.freezeTopLevel();
} // freezeTopLevel

template<class string_type, class string_adaptor>
void ExecutionContext<string_type, string_adaptor>::injectGlobalScope(const typename ScopeType<string_type, string_adaptor>::Scope& scope) 
{
  stack_.injectGlobalScope(scope);
} // injectGlobalScope

///////////////////////////
template<class string_type, class string_adaptor>
class StackFrame
{
public:
  StackFrame(ExecutionContext<string_type, string_adaptor>& context) : context_(context) { context_.pushStackFrame(); }
  ~StackFrame() { context_.popStackFrame(); }

private:
  ExecutionContext<string_type, string_adaptor>& context_;
  
  StackFrame(const StackFrame&);
  StackFrame& operator=(const StackFrame&);
  bool operator==(const StackFrame&) const;
}; // class StackFrame

template<class string_type, class string_adaptor>
class ChainStackFrame
{
public:
  ChainStackFrame(ExecutionContext<string_type, string_adaptor>& context) : context_(context) { context_.chainStackFrame(); }
  ~ChainStackFrame() { context_.popStackFrame(); }

private:
  ExecutionContext<string_type, string_adaptor>& context_;

  ChainStackFrame(const ChainStackFrame&);
  ChainStackFrame& operator=(const ChainStackFrame&);
  bool operator==(const ChainStackFrame&) const;
}; // class ChainStackFrame

///////////////////////////
template<class string_type, class string_adaptor>
class LastFrame
{
public:
  LastFrame(ExecutionContext<string_type, string_adaptor>& context, int last) : context_(context) 
  { 
    oldLast_ = context_.setLast(last);
  } // LastFrame

  LastFrame(ExecutionContext<string_type, string_adaptor>& context, size_t last) : context_(context) 
  { 
    oldLast_ = context_.setLast(static_cast<int>(last));
  } // LastFrame

  ~LastFrame()
  {
    context_.setLast(oldLast_);
  } // ~LastFrame

private:
  ExecutionContext<string_type, string_adaptor>& context_;
  int oldLast_;

  LastFrame(const LastFrame&);
  LastFrame& operator=(const LastFrame&);
  bool operator==(const LastFrame&) const;
}; // class LastFrame

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_EXECUTION_CONTEXT_HPP

