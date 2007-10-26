#ifndef ARABICA_XPATHIC_XPATH_AST_IDS_HPP
#define ARABICA_XPATHIC_XPATH_AST_IDS_HPP

namespace Arabica
{
namespace XPath
{
namespace impl
{

enum 
{
  LocationPath_id = 1,
  AbsoluteLocationPath_id,
  RelativeLocationPath_id,
  Step_id,
  AxisSpecifier_id,
  NodeTest_id,
  Predicate_id,
  PredicateExpr_id,
  AbbreviatedAbsoluteLocationPath_id,
  AbbreviatedStep_id,
  AbbreviatedAxisSpecifier_id,
  Expr_id,
  PrimaryExpr_id,
  FunctionCall_id,
  Argument_id,
  UnionExpr_id,
  PathExpr_id,
  FilterExpr_id,
  OrExpr_id,
  AndExpr_id,
  EqualityExpr_id,
  RelationalExpr_id,
  AdditiveExpr_id,
  MultiplicativeExpr_id,
  UnaryExpr_id,
  Literal_id,
  Number_id,
  Digits_id,
  MultiplyOperator_id,
  FunctionName_id,
  VariableReference_id,
  NameTest_id,
  S_id,
  NodeType_id,
  AxisName_id,

  QName_id,
  Prefix_id,
  LocalPart_id,
  NCName_id,
  NCNameChar_id,

  Slash_id,
  SlashSlash_id,

  AncestorOrSelf_id,
	Ancestor_id,
	Attribute_id,
  Child_id,
	DescendantOrSelf_id,
  Descendant_id,
	FollowingSibling_id,
	Following_id,
	Namespace_id,
	Parent_id,
	PrecedingSibling_id,
	Preceding_id,
	Self_id,

  Comment_id,
  Text_id,
  ProcessingInstruction_id,
  Node_id,
  AnyName_id,

  SelfSelect_id,
  ParentSelect_id,

  LeftSquare_id,
  RightSquare_id,

  LeftBracket_id,
  RightBracket_id,

  PlusOperator_id,
  MinusOperator_id,
  ModOperator_id,
  DivOperator_id,
  EqualsOperator_id,
  NotEqualsOperator_id,
  LessThanOperator_id,
  LessThanEqualsOperator_id,
  GreaterThanOperator_id,
  GreaterThanEqualsOperator_id,

  OrOperator_id,
  AndOperator_id,
  UnionOperator_id,
  UnaryMinusOperator_id,

  Pattern_id,
  LocationPathPattern_id,
  IdKeyPattern_id,
  RelativePathPattern_id,
  StepPattern_id,
  ChildOrAttributeAxisSpecifier_id,
  NodeMatchPattern_id,

  AttributeValueTemplate_id,
  DoubleLeftCurly_id,
  DoubleRightCurly_id,
  LeftCurly_id,
  RightCurly_id,
  EmbeddedExpr_id,
  AttrLiteral_id
};

} // namespace impl

} // namespace XPath

} // namespace Arabica

#endif
