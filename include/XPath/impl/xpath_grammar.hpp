#ifndef ARABICA_XPATHIC_XPATH_GRAMMER_HPP
#define ARABICA_XPATHIC_XPATH_GRAMMER_HPP

#ifndef BOOST_SPIRIT_THREADSAFE
#define BOOST_SPIRIT_THREADSAFE
#endif

#include <boost/version.hpp>

#if BOOST_VERSION >= 103800
#define BOOST_SPIRIT_USE_OLD_NAMESPACE 1
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_chset.hpp>
#include <boost/spirit/include/classic_symbols.hpp>
#else
#include <boost/spirit/core.hpp>
#include <boost/spirit/symbols/symbols.hpp>
#include <boost/spirit/utility/chset.hpp>
#endif

#include "xpath_ast_ids.hpp"

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<typename ScannerT>
struct xpath_grammar_definition
{
  xpath_grammar_definition()
  {
    using namespace boost::spirit;

    // [1]
    LocationPath = AbsoluteLocationPath | RelativeLocationPath;
    // [2]
    AbsoluteLocationPath = AbbreviatedAbsoluteLocationPath
                            | (Slash >> !RelativeLocationPath);
    // [3]
    RelativeLocationPath = Step >> *((SlashSlash | discard_node_d[Slash]) >> Step);

    // [4], [5]
    Step = AxisSpecifier >> NodeTest >> *Predicate | AbbreviatedStep;
    AxisSpecifier = S >> ( AxisName >> S >> "::" | AbbreviatedAxisSpecifier ) >> S;

    // [6]
    AxisName = AncestorOrSelf
			          | Ancestor
			          | Attribute
                | Child
			          | DescendantOrSelf
			          | Descendant
			          | FollowingSibling
			          | Following
			          | Namespace
			          | Parent
			          | PrecedingSibling
			          | Preceding
			          | Self;

    // [7]
    NodeTest = S >>(ProcessingInstruction >> S >> discard_node_d[LeftBracket] >> S >> Literal >> S >> discard_node_d[RightBracket]
                | NodeType >> S >> discard_node_d[LeftBracket] >> S >> discard_node_d[RightBracket]
                | NameTest )
                  >> S;

    // [8], [9]
    Predicate = S >> LeftSquare >> PredicateExpr >> RightSquare >> S;
    PredicateExpr = Expr;

    // [10]
    AbbreviatedAbsoluteLocationPath = SlashSlash >> RelativeLocationPath;
    // [11] AbbreviatedRelativeLocationPath eliminated
    // [12], [13]
    AbbreviatedStep = ParentSelect | SelfSelect;
    AbbreviatedAxisSpecifier = !ch_p('@');

    // [14], [15]
    Expr = OrExpr;
    PrimaryExpr = discard_node_d[S] >>
                  (VariableReference
                    | Number
                    | FunctionCall
                    | discard_node_d[LeftBracket] >> S >> Expr >> S >> discard_node_d[RightBracket]
                    | Literal) >>
                  discard_node_d[S];

    // [16], [17]
    FunctionCall = FunctionName >> S >> LeftBracket >> !(Argument >> *(discard_node_d[ch_p(',')] >> S >> Argument)) >> S >> RightBracket >> S;
    Argument = Expr;

    // [18], [19], [20]
    // UnionExpr ::= PathExpr	| UnionExpr '|' PathExpr
    UnionExpr = PathExpr >> *(UnionOperator >> PathExpr);
    /*
      LocationPath
		| FilterExpr
		| FilterExpr '/' RelativeLocationPath
		| FilterExpr '//' RelativeLocationPath	*/
    PathExpr = discard_node_d[S] >>
                (FilterExpr >> !((SlashSlash | Slash) >> RelativeLocationPath)
                | LocationPath) >>
                discard_node_d[S];
    // FilterExpr ::=  PrimaryExpr | FilterExpr Predicate
    FilterExpr = PrimaryExpr >> *Predicate;

    // [21], [22], [23], [24]
    OrExpr = AndExpr >> *(OrOperator >> AndExpr);
    AndExpr = EqualityExpr >> *(AndOperator >> EqualityExpr);
    EqualityExpr = RelationalExpr >> *((EqualsOperator | NotEqualsOperator) >> RelationalExpr);
    RelationalExpr = AdditiveExpr >> *((LessThanEqualsOperator | GreaterThanEqualsOperator | LessThanOperator |GreaterThanOperator) >> AdditiveExpr);

    // [25], [26], [27]
    AdditiveExpr = MultiplicativeExpr >> *((PlusOperator | MinusOperator) >> MultiplicativeExpr);
    MultiplicativeExpr = UnaryExpr >> *((MultiplyOperator | DivOperator | ModOperator) >> UnaryExpr);
    UnaryExpr = discard_node_d[S] >> *(UnaryMinusOperator) >> UnionExpr;

    // [28] ExprToken not actually used

    //[29], [30], [31],
    Literal	= discard_node_d[ch_p('\"')] >> token_node_d[*~ch_p('\"')] >> discard_node_d[ch_p('\"')]
            | discard_node_d[ch_p('\'')] >> token_node_d[*~ch_p('\'')] >> discard_node_d[ch_p('\'')];
    Number = token_node_d[ch_p('.') >> Digits | Digits >> !('.' >> *Digits)];
    Digits = token_node_d[+digit_p];
    // [32] Operator not actually used
    // [33] OperatorName not actually used
    // [34], [35], [36], [37], [38], [39]
    MultiplyOperator = ch_p('*');
    FunctionName = QName - NodeType;
    VariableReference	=	ch_p('$') >> QName;
    NameTest = AnyName
			        | NCName >> discard_node_d[ch_p(':')] >> AnyName
			        | QName;
    NodeType = Comment
			          | Text
			          | ProcessingInstruction
			          | Node;

    // These aren't correct to spec yet :)
    S = *space_p;
    QName = !(Prefix >> discard_node_d[ch_p(':')]) >> LocalPart;
    Prefix = NCName;
    LocalPart = NCName;
    NCName = token_node_d[(alpha_p | '_') >> *NCNameChar];
    NCNameChar = alpha_p | digit_p | '.' | '-' | '_';

    // things not defined in the spec, but which are just kind of handy :)
    Slash = ch_p('/');
    SlashSlash = str_p("//");

    AncestorOrSelf = str_p("ancestor-or-self");
		Ancestor = str_p("ancestor");
		Attribute = str_p("attribute");
    Child = str_p("child");
		DescendantOrSelf = str_p("descendant-or-self");
    Descendant = str_p("descendant");
		FollowingSibling = str_p("following-sibling");
		Following = str_p("following");
		Namespace = str_p("namespace");
		Parent = str_p("parent");
		PrecedingSibling = str_p("preceding-sibling");
		Preceding = str_p("preceding");
		Self = str_p("self");

    Comment = str_p("comment");
    Text = str_p("text");
    ProcessingInstruction = str_p("processing-instruction");
    Node = str_p("node");
    AnyName = ch_p('*');

    SelfSelect = ch_p('.');
    ParentSelect = str_p("..");

    LeftSquare = ch_p('[');
    RightSquare = ch_p(']');

    LeftBracket = ch_p('(');
    RightBracket = ch_p(')');

    PlusOperator = ch_p('+');
    MinusOperator = ch_p('-');
    ModOperator = str_p("mod");
    DivOperator = str_p("div");
    EqualsOperator = ch_p('=');
    NotEqualsOperator = str_p("!=");
    LessThanOperator = ch_p('<');
    LessThanEqualsOperator = str_p("<=");
    GreaterThanOperator = ch_p('>');
    GreaterThanEqualsOperator = str_p(">=");

    OrOperator = str_p("or");
    AndOperator = str_p("and");
    UnionOperator = ch_p('|');
    UnaryMinusOperator = ch_p('-');
  } // xpath_grammar_definition

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<QName_id> > QName;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Prefix_id> > Prefix;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LocalPart_id> > LocalPart;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<NCName_id> > NCName;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<NCNameChar_id> > NCNameChar;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AxisName_id> > AxisName;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<NodeType_id> > NodeType;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LocationPath_id> > LocationPath;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AbsoluteLocationPath_id> > AbsoluteLocationPath;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<RelativeLocationPath_id> > RelativeLocationPath;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Step_id> > Step;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AxisSpecifier_id> > AxisSpecifier;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<NodeTest_id> > NodeTest;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Predicate_id> > Predicate;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<PredicateExpr_id> > PredicateExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AbbreviatedAbsoluteLocationPath_id> > AbbreviatedAbsoluteLocationPath;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AbbreviatedStep_id> > AbbreviatedStep;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AbbreviatedAxisSpecifier_id> > AbbreviatedAxisSpecifier;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Expr_id> > Expr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<PrimaryExpr_id> > PrimaryExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<FunctionCall_id> > FunctionCall;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Argument_id> > Argument;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<UnionExpr_id> > UnionExpr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<PathExpr_id> > PathExpr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<FilterExpr_id> > FilterExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<OrExpr_id> > OrExpr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AndExpr_id> > AndExpr;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<EqualityExpr_id> > EqualityExpr;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<RelationalExpr_id> > RelationalExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AdditiveExpr_id> > AdditiveExpr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<MultiplicativeExpr_id> > MultiplicativeExpr;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<UnaryExpr_id> > UnaryExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Literal_id> > Literal;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Number_id> > Number;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Digits_id> > Digits;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<MultiplyOperator_id> > MultiplyOperator;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<FunctionName_id> > FunctionName;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<VariableReference_id> > VariableReference;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<NameTest_id> > NameTest;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<S_id> > S; // ExprWhitespace

  // bonus bits
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Slash_id> > Slash;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<SlashSlash_id> > SlashSlash;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AncestorOrSelf_id> > AncestorOrSelf;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Ancestor_id> > Ancestor;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Attribute_id> > Attribute;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Child_id> > Child;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<DescendantOrSelf_id> > DescendantOrSelf;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Descendant_id> > Descendant;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<FollowingSibling_id> > FollowingSibling;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Following_id> > Following;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Namespace_id> > Namespace;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Parent_id> > Parent;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<PrecedingSibling_id> > PrecedingSibling;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Preceding_id> > Preceding;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Self_id> > Self;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Comment_id> > Comment;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Text_id> > Text;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<ProcessingInstruction_id> > ProcessingInstruction;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Node_id> > Node;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AnyName_id> > AnyName;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<SelfSelect_id> > SelfSelect;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<ParentSelect_id> > ParentSelect;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LeftSquare_id> > LeftSquare;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<RightSquare_id> > RightSquare;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LeftBracket_id> > LeftBracket;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<RightBracket_id> > RightBracket;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<PlusOperator_id> > PlusOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<MinusOperator_id> > MinusOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<ModOperator_id> > ModOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<DivOperator_id> > DivOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<EqualsOperator_id> > EqualsOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<NotEqualsOperator_id> > NotEqualsOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LessThanOperator_id> > LessThanOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LessThanEqualsOperator_id> > LessThanEqualsOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<GreaterThanOperator_id> > GreaterThanOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<GreaterThanEqualsOperator_id> > GreaterThanEqualsOperator;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<OrOperator_id> > OrOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AndOperator_id> > AndOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<UnionOperator_id> > UnionOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<UnaryMinusOperator_id> > UnaryMinusOperator;
}; // xpath_grammar_definition


struct xpath_grammar : public boost::spirit::grammar<xpath_grammar>
{
  template<typename ScannerT>
  struct definition : public xpath_grammar_definition<ScannerT>
  {
    definition(xpath_grammar const& /* self */)
    {
    } // definition

    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LocationPath_id> > const&
    start() const
    {
      return xpath_grammar_definition<ScannerT>::LocationPath;
    } // start
  }; // definition<ScannerT>
}; // xpath_grammar

struct xpath_grammar_expr : public boost::spirit::grammar<xpath_grammar_expr>
{
  template<typename ScannerT>
  struct definition : public xpath_grammar_definition<ScannerT>
  {
    definition(xpath_grammar_expr const& /* self */)
    {
    } // definition

    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Expr_id> > const&
    start() const
    {
      return xpath_grammar_definition<ScannerT>::Expr;
    } // start
  }; // definition<ScannerT>
}; // xpath_grammar_expr

struct xpath_grammar_match : public boost::spirit::grammar<xpath_grammar_match>
{
  template<typename ScannerT>
  struct definition : public xpath_grammar_definition<ScannerT>
  {
    definition(xpath_grammar_match const& /* self */)
    {
      using namespace boost::spirit;
      typedef xpath_grammar_definition<ScannerT> base;

      // [1] Pattern ::= LocationPathPattern | Pattern '|' LocationPathPattern
      Pattern = discard_node_d[base::S] >> LocationPathPattern >> discard_node_d[base::S] >> *(base::UnionOperator >> discard_node_d[base::S] >> LocationPathPattern >> discard_node_d[base::S]);

      // [2] LocationPathPattern ::= '/' RelativePathPattern?
		  //                       | IdKeyPattern (('/' | '//') RelativePathPattern)?
		  //                       | '//'? RelativePathPattern
      LocationPathPattern = IdKeyPattern >> !((base::SlashSlash | base::Slash) >> RelativePathPattern) |
                            !base::SlashSlash >> RelativePathPattern |
                            base::Slash >> !RelativePathPattern;


      // [3] IdKeyPattern ::= 'id' '(' Literal ')' | 'key' '(' Literal ',' Literal ')'
      IdKeyPattern = (str_p("id") >> base::LeftBracket >> discard_node_d[base::S] >> base::Literal >> discard_node_d[base::S] >> base::RightBracket) |
                     (str_p("key") >> base::LeftBracket >> discard_node_d[base::S] >> base::Literal >> discard_node_d[base::S] >> discard_node_d[ch_p(',')] >>discard_node_d[base::S] >>  base::Literal >> discard_node_d[base::S] >> base::RightBracket);

      // [4] RelativePathPattern ::= StepPattern
	    //                            | RelativePathPattern '/' StepPattern
	    //                            | RelativePathPattern '//' StepPattern
      RelativePathPattern = StepPattern >> *((base::SlashSlash | base::Slash) >> StepPattern);

      // [5] StepPattern ::= ChildOrAttributeAxisSpecifier NodeTest Predicate*
      StepPattern = ChildOrAttributeAxisSpecifier >> (NodeMatchPattern|base::NodeTest) >> *base::Predicate;

      // [6] ChildOrAttributeAxisSpecifier ::= AbbreviatedAxisSpecifier | ('child' | 'attribute') '::'
      ChildOrAttributeAxisSpecifier = ((base::Child | base::Attribute) >> discard_node_d[str_p("::")]) | base::AbbreviatedAxisSpecifier;

      NodeMatchPattern = str_p("node()");
    } // definition

    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Pattern_id> > const&
    start() const
    {
      return Pattern;
    } // start

    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<Pattern_id> > Pattern;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LocationPathPattern_id> > LocationPathPattern;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<IdKeyPattern_id> > IdKeyPattern;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<RelativePathPattern_id> > RelativePathPattern;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<StepPattern_id> > StepPattern;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<ChildOrAttributeAxisSpecifier_id> > ChildOrAttributeAxisSpecifier;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<NodeMatchPattern_id> > NodeMatchPattern;
  }; // definition<ScannerT>
}; // xpath_grammar_match

struct xpath_grammar_attribute_value : public boost::spirit::grammar<xpath_grammar_attribute_value>
{
  template<typename ScannerT>
  struct definition : public xpath_grammar_definition<ScannerT>
  {
    definition(xpath_grammar_attribute_value const& /* self */)
    {
      using namespace boost::spirit;
      typedef xpath_grammar_definition<ScannerT> base;

      AttributeValueTemplate = (DoubleLeftCurly | DoubleRightCurly | EmbeddedExpr | AttrLiteral) >>
                               *(DoubleLeftCurly | DoubleRightCurly | EmbeddedExpr | AttrLiteral);
      DoubleLeftCurly = str_p("{{");
      DoubleRightCurly = str_p("}}");
      LeftCurly = ch_p('{');
      RightCurly = ch_p('}');
      EmbeddedExpr = LeftCurly >> base::Expr >> RightCurly;
      chset<> brackets("{}");
      AttrLiteral = token_node_d[~brackets >> *~brackets];
    } // definition

    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AttributeValueTemplate_id> > const&
    start() const
    {
      return AttributeValueTemplate;
    } // start

    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AttributeValueTemplate_id> > AttributeValueTemplate;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<DoubleLeftCurly_id> > DoubleLeftCurly;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<DoubleRightCurly_id> > DoubleRightCurly;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<LeftCurly_id> > LeftCurly;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<RightCurly_id> > RightCurly;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<EmbeddedExpr_id> > EmbeddedExpr;
    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<AttrLiteral_id> > AttrLiteral;
  }; // definition
}; // xpath_grammar_attribute_value

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
