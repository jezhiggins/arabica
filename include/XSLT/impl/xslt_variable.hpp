#ifndef ARABICA_XSLT_VARIABLE_HPP
#define ARABICA_XSLT_VARIABLE_HPP

#include "xslt_variable_impl.hpp"

namespace Arabica
{
namespace XSLT
{

class Variable : public Variable_impl
{
public:
  Variable(const std::string& name, 
           const Arabica::XPath::XPathExpressionPtr<std::string>& select,
           const Precedence precedence) :
      Variable_impl(name, select, precedence)
  {
  } // Variable

  virtual ~Variable() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const 
  {
    context.declareVariable(node, *this);
  } // declare
}; // Variable

class GlobalVariable : public Variable_impl
{
public:
  GlobalVariable(const std::string& name,
           const Arabica::XPath::XPathExpressionPtr<std::string>& select,
           const Precedence precedence) :
      Variable_impl(name, select, precedence)
  {
  } // Variable

  virtual ~GlobalVariable() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const 
  {
    context.declareVariable(node, *this);
  } // declare
}; // class GlobalVariable          

} // namespace XSLT
} // namespace Arabica
#endif

