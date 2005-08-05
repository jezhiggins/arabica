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
  while(getNodeId(node) == S_id)
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

XPathExpression* createExpression(node_iter_t const& i, CompilationContext& context)
{
  node_iter_t c = i->children.begin();
  skipWhitespace(c);
  return compile_expression(c, context);
} // createExpression

XPathExpression* createFunction(node_iter_t const& i, CompilationContext& context)
{
//  dump(i);
  node_iter_t c = i->children.begin();
  std::string name(c->value.begin(), c->value.end());
  ++c;
  skipWhitespace(c);
  assert(getNodeId(c) == LeftBracket_id);
  ++c;
  skipWhitespace(c);

  std::vector<XPathExpressionPtr> args;
  while(getNodeId(c) != RightBracket_id)
  {
    XPathExpressionPtr arg(compile_expression(c++, context));
    args.push_back(arg);

    skipWhitespace(c);
  } // while ...
  // maybe trailing whitespace ...

  return FunctionHolder::createFunction(name, args, context);
} // createFunction

XPathExpression* createNumber(node_iter_t const& i, CompilationContext& context)
{
  return new NumericValue(boost::lexical_cast<double>(std::string(i->value.begin(), i->value.end())));
} // createNumber

XPathExpression* createVariable(node_iter_t const& i, CompilationContext& context)
{
  return new Variable(std::string(i->value.begin()+1, i->value.end())); // skip $
} // createVariable

XPathExpression* createLiteral(node_iter_t const& i, CompilationContext& context)
{
  std::string str(i->value.begin(), i->value.end());
  return new StringValue(str);
} // createLiteral

XPathExpression* createBinaryExpression(node_iter_t const& i, CompilationContext& context)
{
  node_iter_t c = i->children.begin();
  XPathExpression* p1 = compile_expression(c, context);
  ++c;

  do
  {
    long op = getNodeId(c);
    ++c;
    XPathExpression* p2 = compile_expression(c, context);

    switch(op)
    {
      case PlusOperator_id:
        p1 = new PlusOperator(p1, p2);
        break;
      case MinusOperator_id:
        p1 = new MinusOperator(p1, p2);
        break;
      case MultiplyOperator_id:
        p1 = new MultiplyOperator(p1, p2);
        break;
      case DivOperator_id:
        p1 = new DivideOperator(p1, p2);
        break;
      case ModOperator_id:
        p1 = new ModOperator(p1, p2);
        break;
      case EqualsOperator_id:
        p1 = new EqualsOperator(p1, p2);
        break;
      case NotEqualsOperator_id:
        p1 = new NotEqualsOperator(p1, p2);
        break;
      case LessThanOperator_id:
        p1 = new LessThanOperator(p1, p2);
        break;
      case LessThanEqualsOperator_id:
        p1 = new LessThanEqualsOperator(p1, p2);
        break;
      case GreaterThanOperator_id:
        p1 = new GreaterThanOperator(p1, p2);
        break;
      case GreaterThanEqualsOperator_id:
        p1 = new GreaterThanEqualsOperator(p1, p2);
        break;
      case OrOperator_id:
        p1 = new OrOperator(p1, p2);
        break;
      case AndOperator_id:
        p1 = new AndOperator(p1, p2);
        break;
      case UnionOperator_id:
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
      case S_id:
      case Slash_id:
        ++c; // just drop it
        break; 
      case RelativeLocationPath_id:
        // might get here when handling an absolute path
        end = c->children.end();
        c = c->children.begin();
        break;
      case Step_id:
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

XPathExpression* createAbsoluteLocationPath(node_iter_t const& i, CompilationContext& context)
{
  return new AbsoluteLocationPath(createStepList(i->children.begin(), i->children.end(), context));
} // createAbsoluteLocationPath

XPathExpression* createRelativeLocationPath(node_iter_t const& i, CompilationContext& context)
{
  return new RelativeLocationPath(createStepList(i->children.begin(), i->children.end(), context));
} // createRelativeLocationPath

XPathExpression* createSingleStepRelativeLocationPath(node_iter_t const& i, CompilationContext& context)
{
  node_iter_t n = i;
  return new RelativeLocationPath(StepFactory::createStep(n, context));
} // createSingleStepRelativeLocationPath

XPathExpression* createSingleStepAbsoluteLocationPath(node_iter_t const& i, CompilationContext& context)
{
  node_iter_t n = i;
  return new AbsoluteLocationPath(StepFactory::createStep(n, context));
} // createSingleStepAbsoluteLocationPath

XPathExpression* createUnaryExpression(node_iter_t const& i, CompilationContext& context)
{
  return compile_expression(i->children.begin(), context);
} // createUnaryExpression

XPathExpression* createUnaryNegativeExpr(node_iter_t const& i, CompilationContext& context)
{
  return new UnaryNegative(compile_expression(i+1, context));
} // createUnaryNegativeExpr

XPathExpressionPtr XPath::compile(const std::string& xpath) const
{
  return do_compile(xpath, &XPath::parse_xpath);
} // compile

XPathExpressionPtr XPath::compile_expr(const std::string& xpath) const
{
  return do_compile(xpath, &XPath::parse_xpath_expr);
} // compile_expr

XPathExpressionPtr XPath::do_compile(const std::string& xpath, tree_info_t(XPath::*fn)(const std::string& str) const) const
{
  debugNames();
  createFunctions();
  tree_info_t ast;
  try {
    ast = (this->*fn)(xpath);
    if(!ast.full)
      throw SyntaxException(xpath);

    CompilationContext context(*this, getNamespaceContext(), getFunctionResolver());
    return XPathExpressionPtr(compile_expression(ast.trees.begin(), context));
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

XPathValuePtr XPath::evaluate(const std::string& xpath, const DOM::Node<std::string>& context) const
{
  ExecutionContext executionContext;
  executionContext.setVariableResolver(getVariableResolver());

  return compile(xpath)->evaluate(context, executionContext);
} // evaluate

XPathValuePtr XPath::evaluate_expr(const std::string& xpath, const DOM::Node<std::string>& context) const
{
  ExecutionContext executionContext;
  executionContext.setVariableResolver(getVariableResolver());

  return compile_expr(xpath)->evaluate(context, executionContext);
} // evaluate_expr

XPathExpression* Arabica::XPath::compile_expression(node_iter_t const& i, CompilationContext& context)
{
  //dump(i);

  long id = getNodeId(i);

  if(XPath::factory_.find(id) == XPath::factory_.end())
  {
  //return XPathExpressionPtr();
    XPath::dump(i, 0);
    throw UnsupportedException(XPath::names_[id]);
  }
  
  return XPath::factory_[id](i, context);
} // compile_expression

const std::map<int, XPath::compileFn> XPath::createFunctions()
{
  std::map<int, XPath::compileFn> factory;

  factory[AbsoluteLocationPath_id] = createAbsoluteLocationPath;
  factory[RelativeLocationPath_id] = createRelativeLocationPath;
  factory[AbbreviatedAbsoluteLocationPath_id] = createAbsoluteLocationPath;
  factory[Step_id] = createRelativeLocationPath;
  factory[PathExpr_id] = createRelativeLocationPath;
  factory[FilterExpr_id] = createRelativeLocationPath;

  factory[PrimaryExpr_id] = createExpression;

  factory[FunctionCall_id] = createFunction;

  factory[AdditiveExpr_id] = createBinaryExpression;
  factory[MultiplicativeExpr_id] = createBinaryExpression;
  factory[EqualityExpr_id] = createBinaryExpression;
  factory[RelationalExpr_id] = createBinaryExpression;
  factory[OrExpr_id] = createBinaryExpression;
  factory[AndExpr_id] = createBinaryExpression;
  factory[UnionExpr_id] = createBinaryExpression;

  factory[Literal_id] = createLiteral;
  factory[Number_id] = createNumber;
  factory[Digits_id] = createNumber;

  factory[VariableReference_id] = createVariable;

  factory[NodeTest_id] = createSingleStepRelativeLocationPath;
  factory[QName_id] = createSingleStepRelativeLocationPath;
  factory[NCName_id] = createSingleStepRelativeLocationPath;
  factory[AnyName_id] = createSingleStepRelativeLocationPath;
  factory[Text_id] = createSingleStepRelativeLocationPath;
  factory[Comment_id] = createSingleStepRelativeLocationPath;
  factory[ProcessingInstruction_id] = createSingleStepRelativeLocationPath;
  factory[Slash_id] = createSingleStepAbsoluteLocationPath;

  factory[SelfSelect_id] = createSingleStepRelativeLocationPath;
  factory[ParentSelect_id] = createSingleStepRelativeLocationPath;

  factory[UnaryExpr_id] = createUnaryExpression;
  factory[UnaryMinusOperator_id] = createUnaryNegativeExpr;

  return factory;
} // createFunctions

const std::map<int, std::string> XPath::debugNames()
{
  std::map<int, std::string> names;
  
  names[LocationPath_id] = "LocationPath";
  names[AbsoluteLocationPath_id] = "AbsoluteLocationPath";
  names[RelativeLocationPath_id] = "RelativeLocationPath";
  names[Step_id] = "Step";
  names[AxisSpecifier_id] = "AxisSpecifier";
  names[NodeTest_id] = "NodeTest";
  names[Predicate_id] = "Predicate";
  names[PredicateExpr_id] = "PredicateExpr";
  names[AbbreviatedAbsoluteLocationPath_id] = "AbbreviatedAbsoluteLocationPath";
  names[AbbreviatedStep_id] = "AbbreviatedStep";
  names[AbbreviatedAxisSpecifier_id] = "AbbreviatedAxisSpecifier";
  names[Expr_id] = "Expr";
  names[PrimaryExpr_id] = "PrimaryExpr";
  names[FunctionCall_id] = "FunctionCall";
  names[Argument_id] = "Argument";
  names[UnionExpr_id] = "UnionExpr";
  names[PathExpr_id] = "PathExpr";
  names[FilterExpr_id] = "FilterExpr";
  names[OrExpr_id] = "OrExpr";
  names[AndExpr_id] = "AndExpr";
  names[EqualityExpr_id] = "EqualityExpr";
  names[RelationalExpr_id] = "RelationalExpr";
  names[AdditiveExpr_id] = "AdditiveExpr";
  names[MultiplicativeExpr_id] = "MultiplicativeExpr";
  names[UnaryExpr_id] = "UnaryExpr";
  names[Literal_id] = "Literal";
  names[Number_id] = "Number";
  names[Digits_id] = "Digits";
  names[MultiplyOperator_id] = "MultiplyOperator";
  names[FunctionName_id] = "FunctionName";
  names[VariableReference_id] = "VariableReference";
  names[NameTest_id] = "NameTest";
  names[S_id] = "S";
  names[NodeType_id] = "NodeType";
  names[AxisName_id] = "AxisName";

  names[QName_id] = "QName";
  names[Prefix_id] = "Prefix";
  names[LocalPart_id] = "LocalPart";
  names[NCName_id] = "NCName";
  names[NCNameChar_id] = "NCNameChar";

  names[Slash_id] = "/";
  names[SlashSlash_id] = "//";

  names[AncestorOrSelf_id] = "ancestor-or-self::";
  names[Ancestor_id] = "ancestor::";
  names[Attribute_id] = "attribute::";
  names[Child_id] = "child::";
  names[DescendantOrSelf_id] = "descendant-or-self::";
  names[Descendant_id] = "descendant::";
  names[FollowingSibling_id] = "following-sibling::";
  names[Following_id] = "following::";
  names[Namespace_id] = "namespace::";
  names[Parent_id] = "parent::";
  names[PrecedingSibling_id] = "preceding-sibling::";
  names[Preceding_id] = "preceding::";
  names[Self_id] = "self::";

  names[Comment_id] = "comment()";
  names[Text_id] = "text()";
  names[ProcessingInstruction_id] = "processing-instruction()";
  names[Node_id] = "node()";
  names[AnyName_id] = "AnyName";

  names[SelfSelect_id] = "SelfSelect";
  names[ParentSelect_id] = "ParentSelect";

  names[LeftSquare_id] = "[";
  names[RightSquare_id] = "]";

  names[LeftBracket_id] = "(";
  names[RightBracket_id] = ")";

  names[PlusOperator_id] = "+";
  names[MinusOperator_id] = "-";
  names[ModOperator_id] = "mod";
  names[DivOperator_id] = "div";
  names[EqualsOperator_id] = "=";
  names[NotEqualsOperator_id] = "!=";
  names[LessThanOperator_id] = "<";
  names[LessThanEqualsOperator_id] = "<=";
  names[GreaterThanOperator_id] = ">";
  names[GreaterThanEqualsOperator_id] = ">=";

  names[OrOperator_id] = "or";
  names[AndOperator_id] = "and";
  names[UnionOperator_id] = "union";
  names[UnaryMinusOperator_id] = "minus";

  return names;
} // debugNames

// end 
