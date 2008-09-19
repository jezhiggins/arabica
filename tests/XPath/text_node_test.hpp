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

  void extraSetUp()
  {
    root_.appendChild(document_.createElement(SA::construct_from_utf8("foo")));
    root_.appendChild(document_.createTextNode(SA::construct_from_utf8("four")));
    root_.appendChild(document_.createTextNode(SA::construct_from_utf8("five")));
    root_.appendChild(document_.createElement(SA::construct_from_utf8("boo")));
    root_.appendChild(document_.createTextNode(SA::construct_from_utf8("six")));
    root_.appendChild(document_.createTextNode(SA::construct_from_utf8("seven")));
  } // extraSetUp

  void test1()
  {
    Node_t node = parser_.evaluate(SA::construct_from_utf8("/root"), document_).asNodeSet()[0];
    assertTrue(node == root_);
  } // test1

  void testTextTest()
  {
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()"), document_);
    assertEquals(1, nodes.asNodeSet().size());
  } // testTextTest

  void testTextTest2()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()"), document_);
    assertEquals(3, nodes.asNodeSet().size());
  } // testTextTest2

  void testTextValue()
  {
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root/text()"), document_).asString();
    assertTrue(SA::construct_from_utf8("onetwothree") == value);
  } // testTextValue

  void testTextValue2()
  {
    extraSetUp();
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root/text()"), document_).asString();
    assertTrue(SA::construct_from_utf8("onetwothree") == value);
  } // testTextValue2

  void testTextValue3()
  {
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root/text()[1]"), document_).asString();
    assertTrue(SA::construct_from_utf8("onetwothree") == value);
  } // testTextValue3

  void testTextValue4()
  {
    extraSetUp();
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root/text()[2]"), document_).asString();
    assertTrue(SA::construct_from_utf8("fourfive") == value);
  } // testTextValue4

  void testTextValue5()
  {
    extraSetUp();
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root/text()[3]"), document_).asString();
    assertTrue(SA::construct_from_utf8("sixseven") == value);
  } // testTextValue5

  void test4()
  {
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root/node()"), document_).asString();
    assertTrue(SA::construct_from_utf8("onetwothree") == value);
  } // test4

  void test5()
  {
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root"), document_).asString();
    assertTrue(SA::construct_from_utf8("onetwothree") == value);
  } // test5

  void test5a()
  {
    extraSetUp();
    string_type value = parser_.evaluate(SA::construct_from_utf8("/root"), document_).asString();
    assertTrue(SA::construct_from_utf8("onetwothreefourfivesixseven") == value);
  } // test5a

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

  void testFollowingSibling2()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()/following-sibling::node()"), document_);
    assertEquals(4, nodes.asNodeSet().size());
  } // testFollowingSibling2

  void testFollowingSibling3()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()/following-sibling::text()"), document_);
    assertEquals(2, nodes.asNodeSet().size());
  } // testFollowingSibling3

  void testFollowing1()
  {
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()/following::node()"), document_);
    assertEquals(0, nodes.asNodeSet().size());
  } // testFollowing1

  void testFollowing2()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()/following::node()"), document_);
    assertEquals(4, nodes.asNodeSet().size());
  } // testFollowing2

  void testFollowing3()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/text()/following::text()"), document_);
    assertEquals(2, nodes.asNodeSet().size());
  } // testFollowing3

  void testPreceding1()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/node()[last()]/preceding::node()"), document_);
    assertEquals(4, nodes.asNodeSet().size());
  } // testPreceding1

  void testPreceding2()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/node()[last()]/preceding::text()"), document_);
    assertEquals(2, nodes.asNodeSet().size());
  } // testPreceding2

  void testPreceding3()
  {
    extraSetUp();
    XPathValue_t node = parser_.evaluate(SA::construct_from_utf8("/root/node()[last()]/preceding::text()[1]"), document_);
    assertTrue(SA::construct_from_utf8("fourfive") == node.asString());
  } // testPreceding3

  void testPreceding4()
  {
    extraSetUp();
    XPathValue_t node = parser_.evaluate(SA::construct_from_utf8("/root/node()[last()]/preceding::text()[2]"), document_);
    assertTrue(SA::construct_from_utf8("onetwothree") == node.asString());
  } // testPreceding4

  void testPrecedingSibling1()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/node()[last()]/preceding-sibling::node()"), document_);
    assertEquals(4, nodes.asNodeSet().size());
  } // testPrecedingSibling1

  void testPrecedingSibling2()
  {
    extraSetUp();
    XPathValue_t nodes = parser_.evaluate(SA::construct_from_utf8("/root/node()[last()]/preceding-sibling::text()"), document_);
    assertEquals(2, nodes.asNodeSet().size());
  } // testPrecedingSibling2

  void testPrecedingSibling3()
  {
    extraSetUp();
    XPathValue_t node = parser_.evaluate(SA::construct_from_utf8("/root/node()[last()]/preceding-sibling::text()[1]"), document_);
    assertTrue(SA::construct_from_utf8("fourfive") == node.asString());
  } // testPrecedingSibling3

  void testPrecedingSibling4()
  {
    extraSetUp();
    XPathValue_t node = parser_.evaluate(SA::construct_from_utf8("/root/node()[last()]/preceding-sibling::text()[2]"), document_);
    assertTrue(SA::construct_from_utf8("onetwothree") == node.asString());
  } // testPrecedingSibling4

  // PRECEDING
  // PRECEDING_SIBLING
}; // class TextNodeTest

template<class string_type, class string_adaptor>
TestSuite* TextNodeTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("test1", &TextNodeTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextTest", &TextNodeTest<string_type, string_adaptor>::testTextTest));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextTest2", &TextNodeTest<string_type, string_adaptor>::testTextTest2));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextValue", &TextNodeTest<string_type, string_adaptor>::testTextValue));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextValue2", &TextNodeTest<string_type, string_adaptor>::testTextValue2));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextValue3", &TextNodeTest<string_type, string_adaptor>::testTextValue3));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextValue4", &TextNodeTest<string_type, string_adaptor>::testTextValue4));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testTextValue5", &TextNodeTest<string_type, string_adaptor>::testTextValue5));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("test4", &TextNodeTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("test5", &TextNodeTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("test5a", &TextNodeTest<string_type, string_adaptor>::test5a));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testNodeTest", &TextNodeTest<string_type, string_adaptor>::testNodeTest));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testDescendantOrSelf", &TextNodeTest<string_type, string_adaptor>::testDescendantOrSelf));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testDescendant", &TextNodeTest<string_type, string_adaptor>::testDescendant));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testFollowingSibling1", &TextNodeTest<string_type, string_adaptor>::testFollowingSibling1));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testFollowingSibling2", &TextNodeTest<string_type, string_adaptor>::testFollowingSibling2));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testFollowingSibling3", &TextNodeTest<string_type, string_adaptor>::testFollowingSibling3));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testFollowing1", &TextNodeTest<string_type, string_adaptor>::testFollowing1));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testFollowing2", &TextNodeTest<string_type, string_adaptor>::testFollowing2));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testFollowing3", &TextNodeTest<string_type, string_adaptor>::testFollowing3));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testPreceding1", &TextNodeTest<string_type, string_adaptor>::testPreceding1));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testPreceding2", &TextNodeTest<string_type, string_adaptor>::testPreceding2));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testPreceding3", &TextNodeTest<string_type, string_adaptor>::testPreceding3));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testPreceding4", &TextNodeTest<string_type, string_adaptor>::testPreceding4));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testPrecedingSibling1", &TextNodeTest<string_type, string_adaptor>::testPrecedingSibling1));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testPrecedingSibling2", &TextNodeTest<string_type, string_adaptor>::testPrecedingSibling2));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testPrecedingSibling3", &TextNodeTest<string_type, string_adaptor>::testPrecedingSibling3));
  suiteOfTests->addTest(new TestCaller<TextNodeTest<string_type, string_adaptor> >("testPrecedingSibling4", &TextNodeTest<string_type, string_adaptor>::testPrecedingSibling4));

  return suiteOfTests;
} // TextNodeTest

#endif
