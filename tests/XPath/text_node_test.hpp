#ifndef TEXT_NODE_TEST_HPP
#define TEXT_NODE_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class TextNodeTest : public TestCase
{
  typedef string_adaptor SA;

  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory_;
  Arabica::DOM::Document<string_type, string_adaptor> document_;

  Arabica::DOM::Element<string_type, string_adaptor> root_;

  Arabica::DOM::Text<string_type, string_adaptor> text1_;
  Arabica::DOM::Text<string_type, string_adaptor> text2_;
  Arabica::DOM::Text<string_type, string_adaptor> text3_;

  Arabica::XPath::XPath<string_type, string_adaptor> parser_;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression_t;
  typedef Arabica::XPath::XPathValue<string_type, string_adaptor> XPathValue_t;
  typedef Arabica::DOM::Node<string_type, string_adaptor> Node_t;


public:
  TextNodeTest(const std::string& name) : TestCase(name)
  {
  } // TextNodeTest

  void setUp()
  {
    factory_ = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    document_ = factory_.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8("root"), 0);
    root_ = document_.getDocumentElement();

    text1_ = document_.createTextNode(SA::construct_from_utf8("one"));
    text2_ = document_.createTextNode(SA::construct_from_utf8("two"));
    text3_ = document_.createTextNode(SA::construct_from_utf8("three"));

    root_.appendChild(text1_);
    root_.appendChild(text2_);
    root_.appendChild(text3_);
  } // setUp

  void test1()
  {
    Node_t node = parser_.evaluate(SA::construct_from_utf8("/root"), document_).asNodeSet()[0];
    assertTrue(node == root_);
  } // test1

  void testTextTest()
  {
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()"), document_);
    assertEquals(1, nodes.asNodeSet().size());
  } // test2

  void testTextValue()
  {
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root/text()"), document_).asString();
    assertEquals("onetwothree", SA::asStdString(value));
  } // testTextValue

  void test4()
  {
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root/node()"), document_).asString();
    assertEquals("onetwothree", SA::asStdString(value));
  } // test4

  void test5()
  {
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root"), document_).asString();
    assertEquals("onetwothree", SA::asStdString(value));
  } // test5

  void testNodeTest()
  {
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/node()"), document_);
    assertEquals(1, nodes.asNodeSet().size());
  } // testNodeTest

  void testDescendantOrSelf()
  {
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("//text()"), document_);
    assertEquals(1, nodes.asNodeSet().size());
  } // testDescendantOrSelf

  void testDescendant()
  {
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/descendant::text()"), document_);
    assertEquals(1, nodes.asNodeSet().size());
  } // testDescendant

  void testFollowingSibling1()
  {
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()/following-sibling::node()"), document_);
    assertEquals(0, nodes.asNodeSet().size());
  } // testFollowingSibling1

  void testFollowing1()
  {
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()/following::node()"), document_);
    assertEquals(0, nodes.asNodeSet().size());
  } // testFollowing1

  // FOLLOWING_SIBLING
  // FOLLOWING
  // PRECEDING
  // PRECEDING_SIBLING
}; // class TextNodeTest

template<class string_type, class string_adaptor>
TestSuite* TextNodeTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("test1", &TextNodeTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextTest", &TextNodeTest<string_type, string_adaptor>::testTextTest));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextValue", &TextNodeTest<string_type, string_adaptor>::testTextValue));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("test4", &TextNodeTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("test5", &TextNodeTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testNodeTest", &TextNodeTest<string_type, string_adaptor>::testNodeTest));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testDescendantOrSelf", &TextNodeTest<string_type, string_adaptor>::testDescendantOrSelf));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testDescendant", &TextNodeTest<string_type, string_adaptor>::testDescendant));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testFollowingSibling1", &TextNodeTest<string_type, string_adaptor>::testFollowingSibling1));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testFollowing1", &TextNodeTest<string_type, string_adaptor>::testFollowing1));

  return suiteOfTests;
} // TextNodeTest

#endif
