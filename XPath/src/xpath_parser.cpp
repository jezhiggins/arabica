#ifdef _MSC_VER
#pragma warning(disable:4224 4180 4244)
#endif 

#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>
#include <XPath/impl/xpath_parser.hpp>
#include <XPath/impl/xpath_value.hpp>
#include <XPath/impl/xpath_arithmetic.hpp>
#include <XPath/impl/xpath_relational.hpp>
#include <XPath/impl/xpath_logical.hpp>
#include <XPath/impl/xpath_step.hpp>
#include <XPath/impl/xpath_compile_context.hpp>
#include <XPath/impl/xpath_variable.hpp>
#include <XPath/impl/xpath_function_holder.hpp>
#include <XPath/impl/xpath_union.hpp>

using namespace Arabica::XPath;

long Arabica::XPath::getNodeId(node_iter_t const& node)
{
  return static_cast<long>(node->value.id().to_long());
} // getNodeId

node_iter_t& Arabica::XPath::skipWhitespace(node_iter_t& node)
{
  while(getNodeId(node) == impl::S_id)
    ++node;
  return node;
} // skipWhitespace

XPath::XPath()
{
  resetNamespaceContext();
  resetVariableResolver();
  resetFunctionResolver();
} // XPath

XPath::~XPath()
{
} // ~XPath

std::map<int, std::string> XPath::names_ = debugNames();
std::map<int, XPath::compileFn> XPath::factory_ = createFunctions();

void XPath::dump(node_iter_t const& i, int depth)
{
  long id = static_cast<long>(i->value.id().to_long());

  for(int d = 0; d < depth; ++d)
    std::cout << ' ';
  std::cout << names_[id] << " - " << std::string(i->value.begin(), i->value.end()) << std::endl;

  for(node_iter_t c = i->children.begin(); c != i->children.end(); ++c)
    dump(c, depth+2);
} // dump

XPathExpression<std::string>* createExpression(node_iter_t const& i, CompilationContext& context)
{
  node_iter_t c = i->children.begin();
  skipWhitespace(c);
  return compile_expression(c, context);
} // createExpression

XPathExpression<std::string>* createFunction(node_iter_t const& i, CompilationContext& context)
{
//  dump(i);
  node_iter_t c = i->children.begin();
  std::string name(c->value.begin(), c->value.end());
  ++c;
  skipWhitespace(c);
  assert(getNodeId(c) == impl::LeftBracket_id);
  ++c;
  skipWhitespace(c);

  std::vector<XPathExpressionPtr<std::string> > args;
  while(getNodeId(c) != impl::RightBracket_id)
  {
    XPathExpressionPtr<std::string> arg(compile_expression(c++, context));
    args.push_back(arg);

    skipWhitespace(c);
  } // while ...
  // maybe trailing whitespace ...

  return FunctionHolder::createFunction(name, args, context);
} // createFunction

XPathExpression<std::string>* createNumber(node_iter_t const& i, CompilationContext& context)
{
  return new NumericValue(boost::lexical_cast<double>(std::string(i->value.begin(), i->value.end())));
} // createNumber

XPathExpression<std::string>* createVariable(node_iter_t const& i, CompilationContext& context)
{
  return new Variable(std::string(i->value.begin()+1, i->value.end())); // skip $
} // createVariable

XPathExpression<std::string>* createLiteral(node_iter_t const& i, CompilationContext& context)
{
  std::string str(i->value.begin(), i->value.end());
  return new StringValue(str);
} // createLiteral

XPathExpression<std::string>* createBinaryExpression(node_iter_t const& i, CompilationContext& context)
{
  node_iter_t c = i->children.begin();
  XPathExpression<std::string>* p1 = compile_expression(c, context);
  ++c;

  do
  {
    long op = getNodeId(c);
    ++c;
    XPathExpression<std::string>* p2 = compile_expression(c, context);

    switch(op)
    {
      case impl::PlusOperator_id:
        p1 = new PlusOperator<std::string>(p1, p2);
        break;
      case impl::MinusOperator_id:
        p1 = new MinusOperator<std::string>(p1, p2);
        break;
      case impl::MultiplyOperator_id:
        p1 = new MultiplyOperator<std::string>(p1, p2);
        break;
      case impl::DivOperator_id:
        p1 = new DivideOperator<std::string>(p1, p2);
        break;
      case impl::ModOperator_id:
        p1 = new ModOperator<std::string>(p1, p2);
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
        throw UnsupportedException(boost::lexical_cast<std::string>(op));
    } // switch
  } 
  while(++c != i->children.end());

  return p1;
} // createBinaryExpression

RelativeLocationPath::StepList createStepList(node_iter_t const& from, node_iter_t const& to, CompilationContext& context)
{
  RelativeLocationPath::StepList steps;

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

XPathExpression<std::string>* createAbsoluteLocationPath(node_iter_t const& i, CompilationContext& context)
{
  return new AbsoluteLocationPath(createStepList(i->children.begin(), i->children.end(), context));
} // createAbsoluteLocationPath

XPathExpression<std::string>* createRelativeLocationPath(node_iter_t const& i, CompilationContext& context)
{
  return new RelativeLocationPath(createStepList(i->children.begin(), i->children.end(), context));
} // createRelativeLocationPath

XPathExpression<std::string>* createSingleStepRelativeLocationPath(node_iter_t const& i, CompilationContext& context)
{
  node_iter_t n = i;
  return new RelativeLocationPath(StepFactory::createStep(n, context));
} // createSingleStepRelativeLocationPath

XPathExpression<std::string>* createSingleStepAbsoluteLocationPath(node_iter_t const& i, CompilationContext& context)
{
  node_iter_t n = i;
  return new AbsoluteLocationPath(StepFactory::createStep(n, context));
} // createSingleStepAbsoluteLocationPath

XPathExpression<std::string>* createUnaryExpression(node_iter_t const& i, CompilationContext& context)
{
  return compile_expression(i->children.begin(), context);
} // createUnaryExpression

XPathExpression<std::string>* createUnaryNegativeExpr(node_iter_t const& i, CompilationContext& context)
{
  return new UnaryNegative<std::string>(compile_expression(i+1, context));
} // createUnaryNegativeExpr

XPathExpressionPtr<std::string> XPath::compile(const std::string& xpath) const
{
  return do_compile(xpath, &XPath::parse_xpath);
} // compile

XPathExpressionPtr<std::string> XPath::compile_expr(const std::string& xpath) const
{
  return do_compile(xpath, &XPath::parse_xpath_expr);
} // compile_expr

XPathExpressionPtr<std::string> XPath::do_compile(const std::string& xpath, tree_info_t(XPath::*fn)(const std::string& str) const) const
{
  debugNames();
  createFunctions();
  tree_info_t ast;
  try {
    ast = (this->*fn)(xpath);
    if(!ast.full)
      throw SyntaxException(xpath);

    CompilationContext context(*this, getNamespaceContext(), getFunctionResolver());
    return XPathExpressionPtr<std::string>(compile_expression(ast.trees.begin(), context));
  } // try
  catch(std::exception& ex) 
  {
    //dump(ast.trees.begin());
    std::cerr << "\n\t'" << xpath << "' threw " << ex.what() << '\n' << std::endl;
    throw SyntaxException(xpath);
  }
  catch(...) 
  {
    std::cerr << "\n\t'" << xpath << "' threw something\n" << std::endl;
    throw SyntaxException(xpath);
  }
} // compile

tree_info_t XPath::parse_xpath(const std::string& str) const
{
  str_iter_t first = str.begin();
  str_iter_t last = str.end();

  return ast_parse(first, last, xpathg_);
} // parse_xpath

tree_info_t XPath::parse_xpath_expr(const std::string& str) const
{
  str_iter_t first = str.begin();
  str_iter_t last = str.end();

  xpath_grammar_expr xpathg;
  return ast_parse(first, last, xpathg);
} // parse_xpath_expr

XPathValuePtr<std::string> XPath::evaluate(const std::string& xpath, const DOM::Node<std::string>& context) const
{
  ExecutionContext executionContext;
  executionContext.setVariableResolver(getVariableResolver());

  return compile(xpath)->evaluate(context, executionContext);
} // evaluate

XPathValuePtr<std::string> XPath::evaluate_expr(const std::string& xpath, const DOM::Node<std::string>& context) const
{
  ExecutionContext executionContext;
  executionContext.setVariableResolver(getVariableResolver());

  return compile_expr(xpath)->evaluate(context, executionContext);
} // evaluate_expr

XPathExpression<std::string>* Arabica::XPath::compile_expression(node_iter_t const& i, CompilationContext& context)
{
  //dump(i);

  long id = getNodeId(i);

  if(XPath::factory_.find(id) == XPath::factory_.end())
  {
  //return XPathExpressionPtr<std::string>();
    XPath::dump(i, 0);
    throw UnsupportedException(XPath::names_[id]);
  }
  
  return XPath::factory_[id](i, context);
} // compile_expression

const std::map<int, XPath::compileFn> XPath::createFunctions()
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
} // createFunctions

const std::map<int, std::string> XPath::debugNames()
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
} // debugNames

// end 
