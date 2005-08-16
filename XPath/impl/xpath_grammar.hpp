#ifndef ARABICA_XPATHIC_XPATH_GRAMMER_HPP
#define ARABICA_XPATHIC_XPATH_GRAMMER_HPP

#define BOOST_SPIRIT_THREADSAFE
#include <boost/spirit/core.hpp>
#include <boost/spirit/phoenix/primitives.hpp>
#include <boost/spirit/symbols/symbols.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include "xpath_ast_ids.hpp"

namespace Arabica
{
namespace XPath
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
    NodeTest = S >>(ProcessingInstruction >> S >> discard_node_d[ch_p('(')] >> S >> Literal >> S >> discard_node_d[ch_p(')')]
                | NodeType >> S >> discard_node_d[ch_p('(')] >> S >> discard_node_d[ch_p(')')]
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
                    | inner_node_d[ch_p('(') >> S >> Expr >> S >> ch_p(')')]
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
    MultiplicativeExpr = UnaryExpr >> *(token_node_d[(MultiplyOperator | DivOperator | ModOperator)] >> UnaryExpr);
    UnaryExpr = discard_node_d[S] >> *(UnaryMinusOperator) >> UnionExpr;

    // [28] ExprToken not actually used

    //[29], [30], [31], 
    Literal	= inner_node_d[ch_p('\"') >> token_node_d[*~ch_p('\"')] >> '\"'] 
            | inner_node_d[ch_p('\'') >> token_node_d[*~ch_p('\'')] >> '\''];	
    Number = token_node_d[ch_p('.') >> Digits | Digits >> !('.' >> *Digits)];
    Digits = token_node_d[+digit_p];
    // [32] Operator not actually used
    // [33] OperatorName not actually used
    // [34], [35], [36], [37], [38], [39]
    MultiplyOperator = ch_p('*');
    FunctionName = QName - NodeType;
    VariableReference	=	token_node_d[ch_p('$') >> QName];
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

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::QName_id> > QName;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Prefix_id> > Prefix;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::LocalPart_id> > LocalPart;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::NCName_id> > NCName;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::NCNameChar_id> > NCNameChar;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AxisName_id> > AxisName;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::NodeType_id> > NodeType;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::LocationPath_id> > LocationPath; 
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AbsoluteLocationPath_id> > AbsoluteLocationPath;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::RelativeLocationPath_id> > RelativeLocationPath;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Step_id> > Step;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AxisSpecifier_id> > AxisSpecifier;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::NodeTest_id> > NodeTest;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Predicate_id> > Predicate;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::PredicateExpr_id> > PredicateExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AbbreviatedAbsoluteLocationPath_id> > AbbreviatedAbsoluteLocationPath;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AbbreviatedStep_id> > AbbreviatedStep;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AbbreviatedAxisSpecifier_id> > AbbreviatedAxisSpecifier;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Expr_id> > Expr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::PrimaryExpr_id> > PrimaryExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::FunctionCall_id> > FunctionCall;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Argument_id> > Argument;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::UnionExpr_id> > UnionExpr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::PathExpr_id> > PathExpr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::FilterExpr_id> > FilterExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::OrExpr_id> > OrExpr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AndExpr_id> > AndExpr;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::EqualityExpr_id> > EqualityExpr;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::RelationalExpr_id> > RelationalExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AdditiveExpr_id> > AdditiveExpr;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::MultiplicativeExpr_id> > MultiplicativeExpr;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::UnaryExpr_id> > UnaryExpr;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Literal_id> > Literal;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Number_id> > Number;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Digits_id> > Digits;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::MultiplyOperator_id> > MultiplyOperator;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::FunctionName_id> > FunctionName;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::VariableReference_id> > VariableReference;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::NameTest_id> > NameTest;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::S_id> > S; // ExprWhitespace

  // bonus bits
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Slash_id> > Slash;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::SlashSlash_id> > SlashSlash;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AncestorOrSelf_id> > AncestorOrSelf;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Ancestor_id> > Ancestor;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Attribute_id> > Attribute;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Child_id> > Child;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::DescendantOrSelf_id> > DescendantOrSelf;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Descendant_id> > Descendant;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::FollowingSibling_id> > FollowingSibling;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Following_id> > Following;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Namespace_id> > Namespace;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Parent_id> > Parent;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::PrecedingSibling_id> > PrecedingSibling;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Preceding_id> > Preceding;
	boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Self_id> > Self;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Comment_id> > Comment;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Text_id> > Text;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::ProcessingInstruction_id> > ProcessingInstruction;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Node_id> > Node;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AnyName_id> > AnyName;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::SelfSelect_id> > SelfSelect;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::ParentSelect_id> > ParentSelect;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::LeftSquare_id> > LeftSquare;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::RightSquare_id> > RightSquare;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::LeftBracket_id> > LeftBracket;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::RightBracket_id> > RightBracket;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::PlusOperator_id> > PlusOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::MinusOperator_id> > MinusOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::ModOperator_id> > ModOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::DivOperator_id> > DivOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::EqualsOperator_id> > EqualsOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::NotEqualsOperator_id> > NotEqualsOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::LessThanOperator_id> > LessThanOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::LessThanEqualsOperator_id> > LessThanEqualsOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::GreaterThanOperator_id> > GreaterThanOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::GreaterThanEqualsOperator_id> > GreaterThanEqualsOperator;

  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::OrOperator_id> > OrOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::AndOperator_id> > AndOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::UnionOperator_id> > UnionOperator;
  boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::UnaryMinusOperator_id> > UnaryMinusOperator;
}; // xpath_grammar_definition


struct xpath_grammar : public boost::spirit::grammar<xpath_grammar>
{
  template<typename ScannerT>
  struct definition : public xpath_grammar_definition<ScannerT>
  {
    definition(xpath_grammar const& /* self */)
    {
    } // definition

    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::LocationPath_id> > const&
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

    boost::spirit::rule<ScannerT, boost::spirit::parser_tag<impl::Expr_id> > const&
    start() const
    {
      return xpath_grammar_definition<ScannerT>::Expr;
    } // start 
  }; // definition<ScannerT>
}; // xpath_grammar

} // namespace XPath
} // namespace Arabica

#endif
