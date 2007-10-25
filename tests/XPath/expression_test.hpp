#ifndef XPATHIC_EXPRESSION_TEST_HPP
#define XPATHIC_EXPRESSION_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.hpp>


template<class string_type, class string_adaptor>
class ExpressionTest : public TestCase
{
  Arabica::XPath::XPath<string_type, string_adaptor> parser;
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory_;
  Arabica::DOM::Document<string_type, string_adaptor> document_;

  Arabica::DOM::Element<string_type, string_adaptor> root_;

  Arabica::DOM::Element<string_type, string_adaptor> element1_;
  Arabica::DOM::Element<string_type, string_adaptor> element2_;
  Arabica::DOM::Element<string_type, string_adaptor> element3_;
  Arabica::DOM::Element<string_type, string_adaptor> spinkle_;

  Arabica::DOM::Attr<string_type, string_adaptor> attr_;

  Arabica::DOM::Text<string_type, string_adaptor> text_;

  Arabica::DOM::Comment<string_type, string_adaptor> comment_;

  Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> processingInstruction_;

  Arabica::DOM::Document<string_type, string_adaptor> chapters_;

  Arabica::DOM::Document<string_type, string_adaptor> numbers_;

  typedef string_adaptor SA;
public:
  ExpressionTest(std::string name) : TestCase(name)
  {
  } // ExpressionTest

  void setUp()
  {
    factory_ = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    document_ = factory_.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8("root"), 0);
    root_ = document_.getDocumentElement();

    element1_ = document_.createElement(SA::construct_from_utf8("child1"));
    element2_ = document_.createElement(SA::construct_from_utf8("child2"));
    element3_ = document_.createElement(SA::construct_from_utf8("child3"));

    element1_.setAttribute(SA::construct_from_utf8("one"), SA::construct_from_utf8("1"));

    element2_.setAttribute(SA::construct_from_utf8("one"), SA::construct_from_utf8("1"));
    element2_.setAttribute(SA::construct_from_utf8("two"), SA::construct_from_utf8("1"));
    element2_.setAttribute(SA::construct_from_utf8("three"), SA::construct_from_utf8("1"));
    element2_.setAttribute(SA::construct_from_utf8("four"), SA::construct_from_utf8("1"));

    text_ = document_.createTextNode(SA::construct_from_utf8("data"));
    comment_ = document_.createComment(SA::construct_from_utf8("comment"));
    processingInstruction_ = document_.createProcessingInstruction(SA::construct_from_utf8("target"), SA::construct_from_utf8("data"));
    element2_.appendChild(text_);
    spinkle_ = document_.createElement(SA::construct_from_utf8("spinkle"));
    element2_.appendChild(spinkle_);
    element2_.appendChild(comment_);
    element2_.appendChild(processingInstruction_);

    attr_ = element1_.getAttributeNode(SA::construct_from_utf8("one"));

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);

    chapters_ = factory_.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8("document"), 0);
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("one")));
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("two")));
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("three")));
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("four")));
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("five")));

    numbers_ = factory_.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8("doc"), 0);
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("1")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("2")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("3")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("4")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("5")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("6")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("7")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("8")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("9")));
  } // setUp

  void testNode1()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile_expr(SA::construct_from_utf8("node()"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(root_ == result.asNodeSet()[0]);

    result = xpath.evaluate(element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(4, result.asNodeSet().size());
  } // testNode1


}; // class ExpressionTest

template<class string_type, class string_adaptor>
TestSuite* ExpressionTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ExpressionTest<string_type, string_adaptor> >("testNode1", &ExpressionTest<string_type, string_adaptor>::testNode1));
 
  return suiteOfTests;
} // ExpressionTest_suite

#endif

