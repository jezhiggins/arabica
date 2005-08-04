#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.h>

using namespace Arabica::XPath;

class NodeTestTest : public TestCase
{
  DOM::DOMImplementation<std::string> factory_;
  DOM::Document<std::string> document_;

  DOM::Element<std::string> root_;

  DOM::Element<std::string> element1_;
  DOM::Element<std::string> element2_;
  DOM::Element<std::string> element3_;

  DOM::Attr<std::string> attr_;

  DOM::Text<std::string> text_;

  DOM::Comment<std::string> comment_;

  DOM::ProcessingInstruction<std::string> processingInstruction_;

public:
  NodeTestTest(const std::string& name) : TestCase(name)
  {
  } // NodeTestTest

  void setUp()
  {
    factory_ = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    document_ = factory_.createDocument("", "root", 0);
    root_ = document_.getDocumentElement();

    element1_ = document_.createElement("child1");
    element2_ = document_.createElement("child2");
    element3_ = document_.createElement("child3");

    element1_.setAttribute("one", "1");

    element2_.setAttribute("one", "1");
    element2_.setAttribute("two", "1");
    element2_.setAttribute("three", "1");
    element2_.setAttribute("four", "1");

    text_ = document_.createTextNode("data");
    comment_ = document_.createComment("comment");
    processingInstruction_ = document_.createProcessingInstruction("target", "data");
    element2_.appendChild(text_);
    element2_.appendChild(document_.createElement("spinkle"));
    element2_.appendChild(comment_);
    element2_.appendChild(processingInstruction_);

    attr_ = element1_.getAttributeNode("one");

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);
  } // setUp

  void test1()
  {
    AnyNodeTest test;

    assertTrue(test(element1_));
    assertTrue(test(element2_));
    assertTrue(test(root_));
    assertTrue(test(attr_));
    assertTrue(test(document_));
    assertTrue(test(text_));
    assertTrue(test(comment_));
    assertTrue(test(processingInstruction_));
  } // test1

  void test2()
  {
    NameNodeTest test("child1");

    assertTrue(test(element1_));
    assertTrue(!test(element2_));
    assertTrue(!test(root_));
    assertTrue(!test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(!test(comment_));
    assertTrue(!test(processingInstruction_));
  } // test2

  void test3()
  {
    NameNodeTest test("one");

    assertTrue(!test(element1_));
    assertTrue(!test(element2_));
    assertTrue(!test(root_));
    assertTrue(test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(!test(comment_));
    assertTrue(!test(processingInstruction_));
  } // test3

  void test4()
  {
    TextNodeTest test;

    assertTrue(!test(element1_));
    assertTrue(!test(root_));
    assertTrue(!test(attr_));
    assertTrue(!test(document_));
    assertTrue(test(text_));
    assertTrue(!test(comment_));
    assertTrue(!test(processingInstruction_));
  } // test4

  void test5()
  {
    CommentNodeTest test;

    assertTrue(!test(element1_));
    assertTrue(!test(root_));
    assertTrue(!test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(test(comment_));
    assertTrue(!test(processingInstruction_));
  } // test5

  void test6()
  {
    ProcessingInstructionNodeTest test;

    assertTrue(!test(element1_));
    assertTrue(!test(root_));
    assertTrue(!test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(!test(comment_));
    assertTrue(test(processingInstruction_));
  } // test6

  void test7()
  {
    ProcessingInstructionNodeTest test("fruity");

    assertTrue(!test(element1_));
    assertTrue(!test(root_));
    assertTrue(!test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(!test(comment_));
    assertTrue(!test(processingInstruction_));
  } // test7

  void test8()
  {
    ProcessingInstructionNodeTest test("target");

    assertTrue(!test(element1_));
    assertTrue(!test(root_));
    assertTrue(!test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(!test(comment_));
    assertTrue(test(processingInstruction_));
  } // test8

  void test9()
  {
    StarNodeTest test;

    AxisEnumerator e(element2_, CHILD);
    assertTrue(!test(*e));
    ++e;
    assertTrue(test(*e));
    ++e;
    assertTrue(!test(*e));
    ++e;
    assertTrue(!test(*e));
  } // test9

  void test10()
  {
    QNameNodeTest test("http://example.com/test", "one");

    assertTrue(!test(element1_));
    assertTrue(!test(element2_));
    assertTrue(!test(root_));
    assertTrue(!test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(!test(comment_));
    assertTrue(!test(processingInstruction_));
  } // test10

  void test11()
  {
    QNameNodeTest test("http://example.com/test", "one");

    DOM::Element<std::string> e1_ = document_.createElementNS("http://example.com/test", "ns:one");
    DOM::Element<std::string> e2_ = document_.createElementNS("http://example.com/test", "ttt:one");
    DOM::Element<std::string> e3_ = document_.createElementNS("http://example.com/test", "ns:two");
    DOM::Element<std::string> e4_ = document_.createElementNS("http://example.com/test", "ttt:two");
    DOM::Element<std::string> e5_ = document_.createElementNS("http://example.com/ssss", "ns:one");
    DOM::Element<std::string> e6_ = document_.createElementNS("http://example.com/eeee", "ttt:one");

    assertTrue(test(e1_));
    assertTrue(test(e2_));
    assertTrue(!test(e3_));
    assertTrue(!test(e4_));
    assertTrue(!test(e5_));
    assertTrue(!test(e6_));
  } // test11

  void test12()
  {
    QStarNodeTest test("http://example.com/test");

    DOM::Element<std::string> e1_ = document_.createElementNS("http://example.com/test", "ns:one");
    DOM::Element<std::string> e2_ = document_.createElementNS("http://example.com/test", "ttt:one");
    DOM::Element<std::string> e3_ = document_.createElementNS("http://example.com/test", "ns:two");
    DOM::Element<std::string> e4_ = document_.createElementNS("http://example.com/test", "ttt:two");
    DOM::Element<std::string> e5_ = document_.createElementNS("http://example.com/ssss", "ns:one");
    DOM::Element<std::string> e6_ = document_.createElementNS("http://example.com/eeee", "ttt:one");

    assertTrue(test(e1_));
    assertTrue(test(e2_));
    assertTrue(test(e3_));
    assertTrue(test(e4_));
    assertTrue(!test(e5_));
    assertTrue(!test(e6_));
  } // test12
}; // class NodeTestTest

TestSuite* NodeTestTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test1", &NodeTestTest::test1));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test2", &NodeTestTest::test2));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test3", &NodeTestTest::test3));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test4", &NodeTestTest::test4));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test5", &NodeTestTest::test5));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test6", &NodeTestTest::test6));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test7", &NodeTestTest::test7));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test8", &NodeTestTest::test8));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test9", &NodeTestTest::test9));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test10", &NodeTestTest::test10));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test11", &NodeTestTest::test11));
  suiteOfTests->addTest(new TestCaller<NodeTestTest>("test12", &NodeTestTest::test12));

  return suiteOfTests;
} // NodeTestTest_suite

  