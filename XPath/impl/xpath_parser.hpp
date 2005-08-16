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

template<class string_type> class CompilationContext;

class StepExpression;
typedef std::vector<StepExpression*> StepList;

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

  XPathExpressionPtr<string_type> compile(const string_type& xpath) const
  {
    return do_compile(xpath, &XPath::parse_xpath);
  } // compile

  XPathExpressionPtr<string_type> compile_expr(const string_type& xpath) const
  {
    return do_compile(xpath, &XPath::parse_xpath_expr);
  } // compile

  XPathValuePtr<string_type> evaluate(const string_type& xpath, const DOM::Node<string_type>& context) const
  {
    ExecutionContext executionContext;
    executionContext.setVariableResolver(getVariableResolver());
    return compile(xpath)->evaluate(context, executionContext);
  } // evaluate

  XPathValuePtr<string_type> evaluate_expr(const string_type& xpath, const DOM::Node<string_type>& context) const
  {
    ExecutionContext executionContext;
    executionContext.setVariableResolver(getVariableResolver());
    return compile_expr(xpath)->evaluate(context, executionContext);
  } // evaluate_expr

  void setNamespaceContext(const NamespaceContext& namespaceContext) { namespaceContext_.set(namespaceContext); }
  void setNamespaceContext(NamespaceContextPtr namespaceContext) { namespaceContext_.set(namespaceContext); }
  const NamespaceContext& getNamespaceContext() const { return namespaceContext_.get(); }
  void resetNamespaceContext() { namespaceContext_.set(NamespaceContextPtr(new NullNamespaceContext())); }

  void setVariableResolver(const VariableResolver<string_type>& variableResolver) { variableResolver_.set(variableResolver); }
  void setVariableResolver(VariableResolverPtr<string_type> variableResolver) { variableResolver_.set(variableResolver); }
  const VariableResolver<string_type>& getVariableResolver() const { return variableResolver_.get(); }
  void resetVariableResolver() { variableResolver_.set(VariableResolverPtr<string_type>(new NullVariableResolver<string_type>())); }

  void setFunctionResolver(const FunctionResolver& functionResolver) { functionResolver_.set(functionResolver); }
  void setFunctionResolver(FunctionResolverPtr functionResolver) { functionResolver_.set(functionResolver); }
  const FunctionResolver& getFunctionResolver() const { return functionResolver_.get(); }
  void resetFunctionResolver() { functionResolver_.set(FunctionResolverPtr(new NullFunctionResolver())); }

private:
  XPathExpressionPtr<string_type> do_compile(const string_type& xpath, 
                                             tree_info_t(XPath::*fn)(const string_type& str) const) const
  {
    tree_info_t ast;
    try {
      ast = (this->*fn)(xpath);
      if(!ast.full)
        throw SyntaxException(xpath);

      CompilationContext<string_type> context(*this, getNamespaceContext(), getFunctionResolver());
      return XPathExpressionPtr<std::string>(compile_expression(ast.trees.begin(), context));
    } // try
    catch(std::exception& ex) 
    {
      throw ex;
    } // catch
    catch(...) 
    {
      throw SyntaxException(xpath);
    } // catch
  } // do_compile

  tree_info_t parse_xpath(const string_type& str) const
  {
    str_iter_t first = str.begin(), last = str.end();
    return ast_parse(first, last, xpathg_);
  } // parse_xpath

  tree_info_t parse_xpath_expr(const string_type& str) const
  {
    str_iter_t first = str.begin(), last = str.end();
    return ast_parse(first, last, xpathge_);
  } // parse_xpath

  xpath_grammar xpathg_;
  xpath_grammar_expr xpathge_;

  ResolverHolder<const NamespaceContext> namespaceContext_;
  ResolverHolder<const VariableResolver<string_type> > variableResolver_;
  ResolverHolder<const FunctionResolver> functionResolver_;

  /////////////////////////////////////////////////////////////////////////////////
public:
  static XPathExpression<string_type>* compile_expression(node_iter_t const& i, 
                                                          CompilationContext<string_type>& context)
  {
    long id = getNodeId(i);

    if(XPath::factory().find(id) == XPath::factory().end())
    {
      XPath::dump(i, 0);
      throw UnsupportedException(XPath::names()[id]);
    }
  
    return XPath::factory()[id](i, context);
  } // compile_expression

private:
  static XPathExpression<string_type>* createAbsoluteLocationPath(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createRelativeLocationPath(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createSingleStepRelativeLocationPath(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createExpression(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createFunction(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createBinaryExpression(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createLiteral(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createNumber(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createVariable(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createSingleStepAbsoluteLocationPath(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createUnaryExpression(node_iter_t const& i, CompilationContext<string_type>& context);
  static XPathExpression<string_type>* createUnaryNegativeExpr(node_iter_t const& i, CompilationContext<string_type>& context);

  static StepList createStepList(node_iter_t const& from, node_iter_t const& to, CompilationContext<string_type>& context);

  typedef XPathExpression<string_type>* (*compileFn)(node_iter_t const& i, CompilationContext<string_type>& context);
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
    std::map<int, XPath::compileFn> factory;

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
    std::map<int, std::string> names;
    
    names[impl::LocationPath_id] = "LocationPath";
    names[impl::AbsoluteLocationPath_id] = "AbsoluteLocationPath";
    names[impl::RelativeLocationPath_id] = "RelativeLocationPath";
    names[impl::Step_id] = "Step";
    names[impl::AxisSpecifier_id] = "AxisSpecifier";
    names[impl::NodeTest_id] = "NodeTest";
    names[impl::Predicate_id] = "Predicate";
    names[impl::PredicateExpr_id] = "PredicateExpr";
    names[impl::AbbreviatedAbsoluteLocationPath_id] = "AbbreviatedAbsoluteLocationPath";
    names[impl::AbbreviatedStep_id] = "AbbreviatedStep";
    names[impl::AbbreviatedAxisSpecifier_id] = "AbbreviatedAxisSpecifier";
    names[impl::Expr_id] = "Expr";
    names[impl::PrimaryExpr_id] = "PrimaryExpr";
    names[impl::FunctionCall_id] = "FunctionCall";
    names[impl::Argument_id] = "Argument";
    names[impl::UnionExpr_id] = "UnionExpr";
    names[impl::PathExpr_id] = "PathExpr";
    names[impl::FilterExpr_id] = "FilterExpr";
    names[impl::OrExpr_id] = "OrExpr";
    names[impl::AndExpr_id] = "AndExpr";
    names[impl::EqualityExpr_id] = "EqualityExpr";
    names[impl::RelationalExpr_id] = "RelationalExpr";
    names[impl::AdditiveExpr_id] = "AdditiveExpr";
    names[impl::MultiplicativeExpr_id] = "MultiplicativeExpr";
    names[impl::UnaryExpr_id] = "UnaryExpr";
    names[impl::Literal_id] = "Literal";
    names[impl::Number_id] = "Number";
    names[impl::Digits_id] = "Digits";
    names[impl::MultiplyOperator_id] = "MultiplyOperator";
    names[impl::FunctionName_id] = "FunctionName";
    names[impl::VariableReference_id] = "VariableReference";
    names[impl::NameTest_id] = "NameTest";
    names[impl::S_id] = "S";
    names[impl::NodeType_id] = "NodeType";
    names[impl::AxisName_id] = "AxisName";

    names[impl::QName_id] = "QName";
    names[impl::Prefix_id] = "Prefix";
    names[impl::LocalPart_id] = "LocalPart";
    names[impl::NCName_id] = "NCName";
    names[impl::NCNameChar_id] = "NCNameChar";

    names[impl::Slash_id] = "/";
    names[impl::SlashSlash_id] = "//";

    names[impl::AncestorOrSelf_id] = "ancestor-or-self::";
    names[impl::Ancestor_id] = "ancestor::";
    names[impl::Attribute_id] = "attribute::";
    names[impl::Child_id] = "child::";
    names[impl::DescendantOrSelf_id] = "descendant-or-self::";
    names[impl::Descendant_id] = "descendant::";
    names[impl::FollowingSibling_id] = "following-sibling::";
    names[impl::Following_id] = "following::";
    names[impl::Namespace_id] = "namespace::";
    names[impl::Parent_id] = "parent::";
    names[impl::PrecedingSibling_id] = "preceding-sibling::";
    names[impl::Preceding_id] = "preceding::";
    names[impl::Self_id] = "self::";

    names[impl::Comment_id] = "comment()";
    names[impl::Text_id] = "text()";
    names[impl::ProcessingInstruction_id] = "processing-instruction()";
    names[impl::Node_id] = "node()";
    names[impl::AnyName_id] = "AnyName";

    names[impl::SelfSelect_id] = "SelfSelect";
    names[impl::ParentSelect_id] = "ParentSelect";

    names[impl::LeftSquare_id] = "[";
    names[impl::RightSquare_id] = "]";

    names[impl::LeftBracket_id] = "(";
    names[impl::RightBracket_id] = ")";

    names[impl::PlusOperator_id] = "+";
    names[impl::MinusOperator_id] = "-";
    names[impl::ModOperator_id] = "mod";
    names[impl::DivOperator_id] = "div";
    names[impl::EqualsOperator_id] = "=";
    names[impl::NotEqualsOperator_id] = "!=";
    names[impl::LessThanOperator_id] = "<";
    names[impl::LessThanEqualsOperator_id] = "<=";
    names[impl::GreaterThanOperator_id] = ">";
    names[impl::GreaterThanEqualsOperator_id] = ">=";

    names[impl::OrOperator_id] = "or";
    names[impl::AndOperator_id] = "and";
    names[impl::UnionOperator_id] = "union";
    names[impl::UnaryMinusOperator_id] = "minus";

    return names;
  } // init_debugNames
  
  static void dump(node_iter_t const& i, int depth)
  {
    long id = static_cast<long>(i->value.id().to_long());

    for(int d = 0; d < depth; ++d)
      std::cerr << ' ';
    std::cerr << names()[id] << " - " << std::string(i->value.begin(), i->value.end()) << std::endl;

    for(node_iter_t c = i->children.begin(); c != i->children.end(); ++c)
      dump(c, depth+2);
  } // dump

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
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createAbsoluteLocationPath(node_iter_t const& i, CompilationContext<string_type>& context)
{
  return new AbsoluteLocationPath(createStepList(i->children.begin(), i->children.end(), context));
} // createAbsoluteLocationPath

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createRelativeLocationPath(node_iter_t const& i, CompilationContext<string_type>& context)
{
  return new RelativeLocationPath(createStepList(i->children.begin(), i->children.end(), context));
} // createRelativeLocationPath

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createSingleStepRelativeLocationPath(node_iter_t const& i, CompilationContext<string_type>& context)
{
  node_iter_t n = i;
  return new RelativeLocationPath(StepFactory::createStep(n, context));
} // createSingleStepRelativeLocationPath

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createExpression(node_iter_t const& i, CompilationContext<string_type>& context)
{
  node_iter_t c = i->children.begin();
  skipWhitespace(c);
  return XPath<string_type, string_adaptor>::compile_expression(c, context);
} // createExpression

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createFunction(node_iter_t const& i, CompilationContext<string_type>& context)
{
  node_iter_t c = i->children.begin();
  string_type name(c->value.begin(), c->value.end());
  ++c;
  skipWhitespace(c);
  assert(getNodeId(c) == impl::LeftBracket_id);
  ++c;
  skipWhitespace(c);

  std::vector<XPathExpressionPtr<string_type> > args;
  while(getNodeId(c) != impl::RightBracket_id)
  {
    XPathExpressionPtr<string_type> arg(XPath<string_type, string_adaptor>::compile_expression(c++, context));
    args.push_back(arg);

    skipWhitespace(c);
  } // while ...
  // maybe trailing whitespace ...

  return FunctionHolder::createFunction(name, args, context);
} // createFunction

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createBinaryExpression(node_iter_t const& i, CompilationContext<string_type>& context)
{
  node_iter_t c = i->children.begin();
  XPathExpression<string_type>* p1 = XPath<string_type, string_adaptor>::compile_expression(c, context);
  ++c;

  do
  {
    long op = getNodeId(c);
    ++c;
    XPathExpression<string_type>* p2 = XPath<string_type, string_adaptor>::compile_expression(c, context);

    switch(op)
    {
      case impl::PlusOperator_id:
        p1 = new PlusOperator<string_type>(p1, p2);
        break;
      case impl::MinusOperator_id:
        p1 = new MinusOperator<string_type>(p1, p2);
        break;
      case impl::MultiplyOperator_id:
        p1 = new MultiplyOperator<string_type>(p1, p2);
        break;
      case impl::DivOperator_id:
        p1 = new DivideOperator<string_type>(p1, p2);
        break;
      case impl::ModOperator_id:
        p1 = new ModOperator<string_type>(p1, p2);
        break;
      case impl::EqualsOperator_id:
        p1 = new EqualsOperator(p1, p2);
        break;
      case impl::NotEqualsOperator_id:
        p1 = new NotEqualsOperator(p1, p2);
        break;
      case impl::LessThanOperator_id:
        p1 = new LessThanOperator(p1, p2);
        break;
      case impl::LessThanEqualsOperator_id:
        p1 = new LessThanEqualsOperator(p1, p2);
        break;
      case impl::GreaterThanOperator_id:
        p1 = new GreaterThanOperator(p1, p2);
        break;
      case impl::GreaterThanEqualsOperator_id:
        p1 = new GreaterThanEqualsOperator(p1, p2);
        break;
      case impl::OrOperator_id:
        p1 = new OrOperator(p1, p2);
        break;
      case impl::AndOperator_id:
        p1 = new AndOperator(p1, p2);
        break;
      case impl::UnionOperator_id:
        p1 = new UnionExpression(p1, p2);
        break;
      default:
        throw UnsupportedException(boost::lexical_cast<string_type>(op));
    } // switch
  } 
  while(++c != i->children.end());

  return p1;
} // createBinaryExpression

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createLiteral(node_iter_t const& i, CompilationContext<string_type>& context)
{
  string_type str(i->value.begin(), i->value.end());
  return new StringValue(str);
} // createLiteral

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createNumber(node_iter_t const& i, CompilationContext<string_type>& context)
{
  return new NumericValue(boost::lexical_cast<double>(string_type(i->value.begin(), i->value.end())));
} // createNumber

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createVariable(node_iter_t const& i, CompilationContext<string_type>& context)
{
  return new Variable(string_type(i->value.begin()+1, i->value.end())); // skip $
} // createVariable

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createSingleStepAbsoluteLocationPath(node_iter_t const& i, CompilationContext<string_type>& context)
{
  node_iter_t n = i;
  return new AbsoluteLocationPath(StepFactory::createStep(n, context));
} // createSingleStepAbsoluteLocationPath

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createUnaryExpression(node_iter_t const& i, CompilationContext<string_type>& context)
{
  return XPath<string_type, string_adaptor>::compile_expression(i->children.begin(), context);
} // createUnaryExpression

template<class string_type, class string_adaptor>
XPathExpression<string_type>* XPath<string_type, string_adaptor>::createUnaryNegativeExpr(node_iter_t const& i, CompilationContext<string_type>& context)
{
  return new UnaryNegative<string_type>(XPath<string_type, string_adaptor>::compile_expression(i+1, context));
} // createUnaryNegativeExpr

template<class string_type, class string_adaptor>
StepList XPath<string_type, string_adaptor>::createStepList(node_iter_t const& from, 
                                                            node_iter_t const& to, 
                                                            CompilationContext<string_type>& context)
{
  StepList steps;

  node_iter_t c = from;
  node_iter_t end = to;

  while(c != end)
    switch(getNodeId(c))
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
          node_iter_t step = c->children.begin();
          steps.push_back(StepFactory::createStep(step, c->children.end(), context));
          ++c;
        }
        break;
      default:
        steps.push_back(StepFactory::createStep(c, end, context));
    } // switch(getNodeId(c))

  return steps;
} // createStepList

} // namespace XPath

} // namespace Arabica

#endif
