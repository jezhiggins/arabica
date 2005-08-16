#ifndef ARABICA_XPATHIC_XPATH_PARSER_HPP
#define ARABICA_XPATHIC_XPATH_PARSER_HPP

#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/ast.hpp>
#include <string>
#include <stdexcept>
#include "xpath_object.hpp"
#include "xpath_ast.hpp"
#include "xpath_grammar.hpp"
#include "xpath_namespace_context.hpp"
#include "xpath_function_resolver.hpp"
#include "xpath_variable_resolver.hpp"
#include "xpath_resolver_holder.hpp"

namespace Arabica
{
namespace XPath
{

class SyntaxException : public std::runtime_error
{
public:
  SyntaxException(const std::string& thing) : std::runtime_error("Bad XPath: " + thing) { }
}; // class SyntaxException

class RuntimeException : public std::runtime_error
{
public:
  RuntimeException(const std::string& thing) : std::runtime_error("Cannot evaluate XPath: " + thing) { }
}; // class RuntimeException

class UnsupportedException : public std::runtime_error
{
public:
  UnsupportedException(const std::string& thing) : std::runtime_error("Sorry, haven't implemented '" + thing + "' yet") { }
}; // class UnsupportedException

class CompilationContext;

class XPath 
{
public:
  XPath();
  ~XPath();

  XPathExpressionPtr compile(const std::string& xpath) const;
  XPathExpressionPtr compile_expr(const std::string& xpath) const;

  XPathValuePtr<std::string> evaluate(const std::string& xpath, const DOM::Node<std::string>& context) const;
  XPathValuePtr<std::string> evaluate_expr(const std::string& xpath, const DOM::Node<std::string>& context) const;

  void setNamespaceContext(const NamespaceContext& namespaceContext) { namespaceContext_.set(namespaceContext); }
  void setNamespaceContext(NamespaceContextPtr namespaceContext) { namespaceContext_.set(namespaceContext); }
  const NamespaceContext& getNamespaceContext() const { return namespaceContext_.get(); }
  void resetNamespaceContext() { namespaceContext_.set(NamespaceContextPtr(new NullNamespaceContext())); }

  void setVariableResolver(const VariableResolver<std::string>& variableResolver) { variableResolver_.set(variableResolver); }
  void setVariableResolver(VariableResolverPtr<std::string> variableResolver) { variableResolver_.set(variableResolver); }
  const VariableResolver<std::string>& getVariableResolver() const { return variableResolver_.get(); }
  void resetVariableResolver() { variableResolver_.set(VariableResolverPtr<std::string>(new NullVariableResolver<std::string>())); }

  void setFunctionResolver(const FunctionResolver& functionResolver) { functionResolver_.set(functionResolver); }
  void setFunctionResolver(FunctionResolverPtr functionResolver) { functionResolver_.set(functionResolver); }
  const FunctionResolver& getFunctionResolver() const { return functionResolver_.get(); }
  void resetFunctionResolver() { functionResolver_.set(FunctionResolverPtr(new NullFunctionResolver())); }

private:
  XPathExpressionPtr do_compile(const std::string& xpath, tree_info_t(XPath::*fn)(const std::string& str) const) const;
  tree_info_t parse_xpath(const std::string& str) const;
  tree_info_t parse_xpath_expr(const std::string& str) const;

  xpath_grammar xpathg_;

  ResolverHolder<const NamespaceContext> namespaceContext_;
  ResolverHolder<const VariableResolver<std::string> > variableResolver_;
  ResolverHolder<const FunctionResolver> functionResolver_;

  typedef XPathExpression* (*compileFn)(node_iter_t const& i, CompilationContext& context);
  static std::map<int, compileFn> factory_;
  static std::map<int, std::string> names_;
  static const std::map<int, compileFn> createFunctions();
  static const std::map<int, std::string> debugNames();
  static void dump(node_iter_t const& i, int depth);

  friend XPathExpression* Arabica::XPath::compile_expression(node_iter_t const& i, CompilationContext& context);


  XPath(const XPath&);
  XPath& operator=(const XPath&);
  bool operator==(const XPath&) const;
}; // class XPath

} // namespace XPath

} // namespace Arabica

#endif
