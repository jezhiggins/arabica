#ifndef ARABICA_XPATHIC_XPATH_PARSER_HPP
#define ARABICA_XPATHIC_XPATH_PARSER_HPP

#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/ast.hpp>
#include <string>
#include <stdexcept>
#include <map>
#include "xpath_object.hpp"
#include "xpath_expression.hpp"
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

namespace impl 
{
  template<class string_type, class string_adaptor> class CompilationContext;

  template<class string_type, class string_adaptor> class StepExpression;

  template<class string_type, class string_adaptor>
  class StepList : public std::vector<impl::StepExpression<string_type, string_adaptor>*> { };
} // namespace impl

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XPath 
{
public:
  XPath()
  {
    resetNamespaceContext();
    resetVariableResolver();
    resetFunctionResolver();
  } // XPath

  ~XPath()
  {
  } // ~XPath

  XPathExpressionPtr<string_type, string_adaptor> compile(const string_type& xpath) const
  {
    return do_compile(xpath, &XPath::parse_xpath);
  } // compile

  XPathExpressionPtr<string_type, string_adaptor> compile_expr(const string_type& xpath) const
  {
    return do_compile(xpath, &XPath::parse_xpath_expr);
  } // compile

  XPathValuePtr<string_type> evaluate(const string_type& xpath, const DOM::Node<string_type>& context) const
  {
    ExecutionContext<string_type, string_adaptor> executionContext;
    executionContext.setVariableResolver(getVariableResolver());
    return compile(xpath)->evaluate(context, executionContext);
  } // evaluate

  XPathValuePtr<string_type> evaluate_expr(const string_type& xpath, const DOM::Node<string_type>& context) const
  {
    ExecutionContext<string_type, string_adaptor> executionContext;
    executionContext.setVariableResolver(getVariableResolver());
    return compile_expr(xpath)->evaluate(context, executionContext);
  } // evaluate_expr

  void setNamespaceContext(const NamespaceContext<string_type, string_adaptor>& namespaceContext) { namespaceContext_.set(namespaceContext); }
  void setNamespaceContext(NamespaceContextPtr<string_type, string_adaptor> namespaceContext) { namespaceContext_.set(namespaceContext); }
  const NamespaceContext<string_type, string_adaptor>& getNamespaceContext() const { return namespaceContext_.get(); }
  void resetNamespaceContext() { namespaceContext_.set(NamespaceContextPtr<string_type, string_adaptor>(new NullNamespaceContext<string_type, string_adaptor>())); }

  void setVariableResolver(const VariableResolver<string_type, string_adaptor>& variableResolver) { variableResolver_.set(variableResolver); }
  void setVariableResolver(VariableResolverPtr<string_type, string_adaptor> variableResolver) { variableResolver_.set(variableResolver); }
  const VariableResolver<string_type, string_adaptor>& getVariableResolver() const { return variableResolver_.get(); }
  void resetVariableResolver() { variableResolver_.set(VariableResolverPtr<string_type, string_adaptor>(new NullVariableResolver<string_type, string_adaptor>())); }

  void setFunctionResolver(const FunctionResolver<string_type, string_adaptor>& functionResolver) { functionResolver_.set(functionResolver); }
  void setFunctionResolver(FunctionResolverPtr<string_type, string_adaptor> functionResolver) { functionResolver_.set(functionResolver); }
  const FunctionResolver<string_type, string_adaptor>& getFunctionResolver() const { return functionResolver_.get(); }
  void resetFunctionResolver() { functionResolver_.set(FunctionResolverPtr<string_type, string_adaptor>(new NullFunctionResolver<string_type, string_adaptor>())); }

private:
  XPathExpressionPtr<string_type, string_adaptor> do_compile(const string_type& xpath, 
                                                             typename impl::types<string_adaptor>::tree_info_t(XPath::*fn)(const string_type& str) const) const
  {
    typename impl::types<string_adaptor>::tree_info_t ast;
    try {
      ast = (this->*fn)(xpath);
      if(!ast.full)
        throw SyntaxException(string_adaptor().asStdString(xpath));

      impl::CompilationContext<string_type, string_adaptor> context(*this, getNamespaceContext(), getFunctionResolver());
      return XPathExpressionPtr<string_type, string_adaptor>(compile_expression(ast.trees.begin(), context));
    } // try
    catch(std::exception& ex) 
    {
      throw ex;
    } // catch
    catch(...) 
    {
      throw SyntaxException(string_adaptor().asStdString(xpath));
    } // catch
  } // do_compile

  typename impl::types<string_adaptor>::tree_info_t parse_xpath(const string_type& str) const
  {
    typename impl::types<string_adaptor>::str_iter_t first = string_adaptor::begin(str), last = string_adaptor::end(str);
    return ast_parse(first, last, xpathg_);
  } // parse_xpath

  typename impl::types<string_adaptor>::tree_info_t parse_xpath_expr(const string_type& str) const
  {
    typename impl::types<string_adaptor>::str_iter_t first = string_adaptor::begin(str), last = string_adaptor::end(str);
    return ast_parse(first, last, xpathge_);
  } // parse_xpath

  impl::xpath_grammar xpathg_;
  impl::xpath_grammar_expr xpathge_;

  impl::ResolverHolder<const NamespaceContext<string_type, string_adaptor> > namespaceContext_;
  impl::ResolverHolder<const VariableResolver<string_type, string_adaptor> > variableResolver_;
  impl::ResolverHolder<const FunctionResolver<string_type, string_adaptor> > functionResolver_;

  /////////////////////////////////////////////////////////////////////////////////
public:
  static XPathExpression<string_type, string_adaptor>* compile_expression(typename impl::types<string_adaptor>::node_iter_t const& i, 
                                                          impl::CompilationContext<string_type, string_adaptor>& context)
  {
    long id = impl::getNodeId<string_adaptor>(i);

    if(XPath::factory().find(id) == XPath::factory().end())
    {
      //XPath::dump(i, 0);
      throw UnsupportedException(string_adaptor().asStdString(XPath::names()[id]));
    }
  
    return XPath::factory()[id](i, context);
  } // compile_expression

private:
  static XPathExpression<string_type, string_adaptor>* createAbsoluteLocationPath(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createRelativeLocationPath(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createSingleStepRelativeLocationPath(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createExpression(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createFunction(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createBinaryExpression(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createLiteral(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createNumber(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createVariable(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createSingleStepAbsoluteLocationPath(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createUnaryExpression(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static XPathExpression<string_type, string_adaptor>* createUnaryNegativeExpr(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);

  static impl::StepList<string_type, string_adaptor> createStepList(typename impl::types<string_adaptor>::node_iter_t const& from, typename impl::types<string_adaptor>::node_iter_t const& to, impl::CompilationContext<string_type, string_adaptor>& context);

  typedef XPathExpression<string_type, string_adaptor>* (*compileFn)(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context);
  static std::map<int, compileFn>& factory()
  {
    static std::map<int, compileFn> f = init_createFunctions();
    return f;
  } // factory

  static std::map<int, string_type>& names()
  {
    static std::map<int, string_type> n = init_debugNames();
    return n;
  } // names

  static const std::map<int, compileFn> init_createFunctions()
  {
    std::map<int, compileFn> factory;

    factory[impl::AbsoluteLocationPath_id] = createAbsoluteLocationPath;
    factory[impl::RelativeLocationPath_id] = createRelativeLocationPath;
    factory[impl::AbbreviatedAbsoluteLocationPath_id] = createAbsoluteLocationPath;
    factory[impl::Step_id] = createRelativeLocationPath;
    factory[impl::PathExpr_id] = createRelativeLocationPath;
    factory[impl::FilterExpr_id] = createRelativeLocationPath;

    factory[impl::PrimaryExpr_id] = createExpression;

    factory[impl::FunctionCall_id] = createFunction;

    factory[impl::AdditiveExpr_id] = createBinaryExpression;
    factory[impl::MultiplicativeExpr_id] = createBinaryExpression;
    factory[impl::EqualityExpr_id] = createBinaryExpression;
    factory[impl::RelationalExpr_id] = createBinaryExpression;
    factory[impl::OrExpr_id] = createBinaryExpression;
    factory[impl::AndExpr_id] = createBinaryExpression;
    factory[impl::UnionExpr_id] = createBinaryExpression;

    factory[impl::Literal_id] = createLiteral;
    factory[impl::Number_id] = createNumber;
    factory[impl::Digits_id] = createNumber;

    factory[impl::VariableReference_id] = createVariable;

    factory[impl::NodeTest_id] = createSingleStepRelativeLocationPath;
    factory[impl::QName_id] = createSingleStepRelativeLocationPath;
    factory[impl::NCName_id] = createSingleStepRelativeLocationPath;
    factory[impl::AnyName_id] = createSingleStepRelativeLocationPath;
    factory[impl::Text_id] = createSingleStepRelativeLocationPath;
    factory[impl::Comment_id] = createSingleStepRelativeLocationPath;
    factory[impl::ProcessingInstruction_id] = createSingleStepRelativeLocationPath;
    factory[impl::Slash_id] = createSingleStepAbsoluteLocationPath;

    factory[impl::SelfSelect_id] = createSingleStepRelativeLocationPath;
    factory[impl::ParentSelect_id] = createSingleStepRelativeLocationPath;

    factory[impl::UnaryExpr_id] = createUnaryExpression;
    factory[impl::UnaryMinusOperator_id] = createUnaryNegativeExpr;

    return factory;
  } // init_createFunctions

  static const std::map<int, string_type> init_debugNames()
  {
    std::map<int, string_type> names;
    typedef string_adaptor SA;

    names[impl::LocationPath_id] = SA::construct_from_utf8("LocationPath");
    names[impl::AbsoluteLocationPath_id] = SA::construct_from_utf8("AbsoluteLocationPath");
    names[impl::RelativeLocationPath_id] = SA::construct_from_utf8("RelativeLocationPath");
    names[impl::Step_id] = SA::construct_from_utf8("Step");
    names[impl::AxisSpecifier_id] = SA::construct_from_utf8("AxisSpecifier");
    names[impl::NodeTest_id] = SA::construct_from_utf8("NodeTest");
    names[impl::Predicate_id] = SA::construct_from_utf8("Predicate");
    names[impl::PredicateExpr_id] = SA::construct_from_utf8("PredicateExpr");
    names[impl::AbbreviatedAbsoluteLocationPath_id] = SA::construct_from_utf8("AbbreviatedAbsoluteLocationPath");
    names[impl::AbbreviatedStep_id] = SA::construct_from_utf8("AbbreviatedStep");
    names[impl::AbbreviatedAxisSpecifier_id] = SA::construct_from_utf8("AbbreviatedAxisSpecifier");
    names[impl::Expr_id] = SA::construct_from_utf8("Expr");
    names[impl::PrimaryExpr_id] = SA::construct_from_utf8("PrimaryExpr");
    names[impl::FunctionCall_id] = SA::construct_from_utf8("FunctionCall");
    names[impl::Argument_id] = SA::construct_from_utf8("Argument");
    names[impl::UnionExpr_id] = SA::construct_from_utf8("UnionExpr");
    names[impl::PathExpr_id] = SA::construct_from_utf8("PathExpr");
    names[impl::FilterExpr_id] = SA::construct_from_utf8("FilterExpr");
    names[impl::OrExpr_id] = SA::construct_from_utf8("OrExpr");
    names[impl::AndExpr_id] = SA::construct_from_utf8("AndExpr");
    names[impl::EqualityExpr_id] = SA::construct_from_utf8("EqualityExpr");
    names[impl::RelationalExpr_id] = SA::construct_from_utf8("RelationalExpr");
    names[impl::AdditiveExpr_id] = SA::construct_from_utf8("AdditiveExpr");
    names[impl::MultiplicativeExpr_id] = SA::construct_from_utf8("MultiplicativeExpr");
    names[impl::UnaryExpr_id] = SA::construct_from_utf8("UnaryExpr");
    names[impl::Literal_id] = SA::construct_from_utf8("Literal");
    names[impl::Number_id] = SA::construct_from_utf8("Number");
    names[impl::Digits_id] = SA::construct_from_utf8("Digits");
    names[impl::MultiplyOperator_id] = SA::construct_from_utf8("MultiplyOperator");
    names[impl::FunctionName_id] = SA::construct_from_utf8("FunctionName");
    names[impl::VariableReference_id] = SA::construct_from_utf8("VariableReference");
    names[impl::NameTest_id] = SA::construct_from_utf8("NameTest");
    names[impl::S_id] = SA::construct_from_utf8("S");
    names[impl::NodeType_id] = SA::construct_from_utf8("NodeType");
    names[impl::AxisName_id] = SA::construct_from_utf8("AxisName");

    names[impl::QName_id] = SA::construct_from_utf8("QName");
    names[impl::Prefix_id] = SA::construct_from_utf8("Prefix");
    names[impl::LocalPart_id] = SA::construct_from_utf8("LocalPart");
    names[impl::NCName_id] = SA::construct_from_utf8("NCName");
    names[impl::NCNameChar_id] = SA::construct_from_utf8("NCNameChar");

    names[impl::Slash_id] = SA::construct_from_utf8("/");
    names[impl::SlashSlash_id] = SA::construct_from_utf8("//");

    names[impl::AncestorOrSelf_id] = SA::construct_from_utf8("ancestor-or-self::");
    names[impl::Ancestor_id] = SA::construct_from_utf8("ancestor::");
    names[impl::Attribute_id] = SA::construct_from_utf8("attribute::");
    names[impl::Child_id] = SA::construct_from_utf8("child::");
    names[impl::DescendantOrSelf_id] = SA::construct_from_utf8("descendant-or-self::");
    names[impl::Descendant_id] = SA::construct_from_utf8("descendant::");
    names[impl::FollowingSibling_id] = SA::construct_from_utf8("following-sibling::");
    names[impl::Following_id] = SA::construct_from_utf8("following::");
    names[impl::Namespace_id] = SA::construct_from_utf8("namespace::");
    names[impl::Parent_id] = SA::construct_from_utf8("parent::");
    names[impl::PrecedingSibling_id] = SA::construct_from_utf8("preceding-sibling::");
    names[impl::Preceding_id] = SA::construct_from_utf8("preceding::");
    names[impl::Self_id] = SA::construct_from_utf8("self::");

    names[impl::Comment_id] = SA::construct_from_utf8("comment()");
    names[impl::Text_id] = SA::construct_from_utf8("text()");
    names[impl::ProcessingInstruction_id] = SA::construct_from_utf8("processing-instruction()");
    names[impl::Node_id] = SA::construct_from_utf8("node()");
    names[impl::AnyName_id] = SA::construct_from_utf8("AnyName");

    names[impl::SelfSelect_id] = SA::construct_from_utf8("SelfSelect");
    names[impl::ParentSelect_id] = SA::construct_from_utf8("ParentSelect");

    names[impl::LeftSquare_id] = SA::construct_from_utf8("[");
    names[impl::RightSquare_id] = SA::construct_from_utf8("]");

    names[impl::LeftBracket_id] = SA::construct_from_utf8("(");
    names[impl::RightBracket_id] = SA::construct_from_utf8(")");

    names[impl::PlusOperator_id] = SA::construct_from_utf8("+");
    names[impl::MinusOperator_id] = SA::construct_from_utf8("-");
    names[impl::ModOperator_id] = SA::construct_from_utf8("mod");
    names[impl::DivOperator_id] = SA::construct_from_utf8("div");
    names[impl::EqualsOperator_id] = SA::construct_from_utf8("=");
    names[impl::NotEqualsOperator_id] = SA::construct_from_utf8("!=");
    names[impl::LessThanOperator_id] = SA::construct_from_utf8("<");
    names[impl::LessThanEqualsOperator_id] = SA::construct_from_utf8("<=");
    names[impl::GreaterThanOperator_id] = SA::construct_from_utf8(">");
    names[impl::GreaterThanEqualsOperator_id] = SA::construct_from_utf8(">=");

    names[impl::OrOperator_id] = SA::construct_from_utf8("or");
    names[impl::AndOperator_id] = SA::construct_from_utf8("and");
    names[impl::UnionOperator_id] = SA::construct_from_utf8("union");
    names[impl::UnaryMinusOperator_id] = SA::construct_from_utf8("minus");

    return names;
  } // init_debugNames
  
  /*
  static void dump(typename impl::types<string_adaptor>::node_iter_t const& i, int depth)
  {
    long id = static_cast<long>(i->value.id().to_long());

    for(int d = 0; d < depth; ++d)
      std::cerr << ' ';
    std::cerr << names()[id] << " - " << std::string(i->value.begin(), i->value.end()) << std::endl;

    for(typename impl::types<string_adaptor>::node_iter_t c = i->children.begin(); c != i->children.end(); ++c)
      dump(c, depth+2);
  } // dump
  */

  XPath(const XPath&);
  XPath& operator=(const XPath&);
  bool operator==(const XPath&) const;
}; // class XPath

} // namespace XPath

} // namespace Arabica

#include <boost/lexical_cast.hpp>
#include "xpath_value.hpp"
#include "xpath_arithmetic.hpp"
#include "xpath_relational.hpp"
#include "xpath_logical.hpp"
#include "xpath_step.hpp"
#include "xpath_compile_context.hpp"
#include "xpath_variable.hpp"
#include "xpath_function_holder.hpp"
#include "xpath_union.hpp"

namespace Arabica
{

namespace XPath
{

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createAbsoluteLocationPath(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  return new impl::AbsoluteLocationPath<string_type, string_adaptor>(createStepList(i->children.begin(), i->children.end(), context));
} // createAbsoluteLocationPath

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createRelativeLocationPath(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  return new impl::RelativeLocationPath<string_type, string_adaptor>(createStepList(i->children.begin(), i->children.end(), context));
} // createRelativeLocationPath

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createSingleStepRelativeLocationPath(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  typename impl::types<string_adaptor>::node_iter_t n = i;
  return new impl::RelativeLocationPath<string_type, string_adaptor>(impl::StepFactory<string_type, string_adaptor>::createStep(n, context));
} // createSingleStepRelativeLocationPath

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createExpression(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  typename impl::types<string_adaptor>::node_iter_t c = i->children.begin();
  impl::skipWhitespace<string_adaptor>(c);
  return XPath<string_type, string_adaptor>::compile_expression(c, context);
} // createExpression

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createFunction(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  typename impl::types<string_adaptor>::node_iter_t c = i->children.begin();
  string_type name = string_adaptor::construct(c->value.begin(), c->value.end());
  ++c;
  impl::skipWhitespace<string_adaptor>(c);
  assert(impl::getNodeId<string_adaptor>(c) == impl::LeftBracket_id);
  ++c;
  impl::skipWhitespace<string_adaptor>(c);

  std::vector<XPathExpressionPtr<string_type, string_adaptor> > args;
  while(impl::getNodeId<string_adaptor>(c) != impl::RightBracket_id)
  {
    XPathExpressionPtr<string_type, string_adaptor> arg(XPath<string_type, string_adaptor>::compile_expression(c++, context));
    args.push_back(arg);

    impl::skipWhitespace<string_adaptor>(c);
  } // while ...
  // maybe trailing whitespace ...

  return impl::FunctionHolder<string_type, string_adaptor>::createFunction(name, args, context);
} // createFunction

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createBinaryExpression(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  typename impl::types<string_adaptor>::node_iter_t c = i->children.begin();
  XPathExpression<string_type, string_adaptor>* p1 = XPath<string_type, string_adaptor>::compile_expression(c, context);
  ++c;

  do
  {
    long op = impl::getNodeId<string_adaptor>(c);
    ++c;
    XPathExpression<string_type, string_adaptor>* p2 = XPath<string_type, string_adaptor>::compile_expression(c, context);

    switch(op)
    {
      case impl::PlusOperator_id:
        p1 = new impl::PlusOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::MinusOperator_id:
        p1 = new impl::MinusOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::MultiplyOperator_id:
        p1 = new impl::MultiplyOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::DivOperator_id:
        p1 = new impl::DivideOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::ModOperator_id:
        p1 = new impl::ModOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::EqualsOperator_id:
        p1 = new impl::EqualsOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::NotEqualsOperator_id:
        p1 = new impl::NotEqualsOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::LessThanOperator_id:
        p1 = new impl::LessThanOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::LessThanEqualsOperator_id:
        p1 = new impl::LessThanEqualsOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::GreaterThanOperator_id:
        p1 = new impl::GreaterThanOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::GreaterThanEqualsOperator_id:
        p1 = new impl::GreaterThanEqualsOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::OrOperator_id:
        p1 = new impl::OrOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::AndOperator_id:
        p1 = new impl::AndOperator<string_type, string_adaptor>(p1, p2);
        break;
      case impl::UnionOperator_id:
        p1 = new impl::UnionExpression<string_type, string_adaptor>(p1, p2);
        break;
      default:
        throw UnsupportedException(boost::lexical_cast<std::string>(op));
    } // switch
  } 
  while(++c != i->children.end());

  return p1;
} // createBinaryExpression

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createLiteral(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  string_type str = string_adaptor::construct(i->value.begin(), i->value.end());
  return new StringValue<string_type, string_adaptor>(str);
} // createLiteral

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createNumber(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  string_type str = string_adaptor::construct(i->value.begin(), i->value.end());
  return new NumericValue<string_type, string_adaptor>(boost::lexical_cast<double>(str));
} // createNumber

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createVariable(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  string_type str = string_adaptor::construct(i->value.begin()+1, i->value.end());
  return new Variable<string_type, string_adaptor>(str); 
} // createVariable

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createSingleStepAbsoluteLocationPath(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  typename impl::types<string_adaptor>::node_iter_t n = i;
  return new impl::AbsoluteLocationPath<string_type, string_adaptor>(impl::StepFactory<string_type, string_adaptor>::createStep(n, context));
} // createSingleStepAbsoluteLocationPath

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createUnaryExpression(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  return XPath<string_type, string_adaptor>::compile_expression(i->children.begin(), context);
} // createUnaryExpression

template<class string_type, class string_adaptor>
XPathExpression<string_type, string_adaptor>* XPath<string_type, string_adaptor>::createUnaryNegativeExpr(typename impl::types<string_adaptor>::node_iter_t const& i, impl::CompilationContext<string_type, string_adaptor>& context)
{
  return new impl::UnaryNegative<string_type, string_adaptor>(XPath<string_type, string_adaptor>::compile_expression(i+1, context));
} // createUnaryNegativeExpr

template<class string_type, class string_adaptor>
impl::StepList<string_type, string_adaptor> XPath<string_type, string_adaptor>::createStepList(typename impl::types<string_adaptor>::node_iter_t const& from, 
                                                            typename impl::types<string_adaptor>::node_iter_t const& to, 
                                                            impl::CompilationContext<string_type, string_adaptor>& context)
{
  impl::StepList<string_type, string_adaptor> steps;

  typename impl::types<string_adaptor>::node_iter_t c = from;
  typename impl::types<string_adaptor>::node_iter_t end = to;

  while(c != end)
    switch(impl::getNodeId<string_adaptor>(c))
    {
      case impl::S_id:
      case impl::Slash_id:
        ++c; // just drop it
        break;
      case impl::RelativeLocationPath_id:
        // might get here when handling an absolute path
        end = c->children.end();
        c = c->children.begin();
        break;
      case impl::Step_id:
        {
          typename impl::types<string_adaptor>::node_iter_t step = c->children.begin();
          steps.push_back(impl::StepFactory<string_type, string_adaptor>::createStep(step, c->children.end(), context));
          ++c;
        }
        break;
      default:
        steps.push_back(impl::StepFactory<string_type, string_adaptor>::createStep(c, end, context));
    } // switch(impl::getNodeId(c))

  return steps;
} // createStepList

} // namespace XPath
} // namespace Arabica

#endif
