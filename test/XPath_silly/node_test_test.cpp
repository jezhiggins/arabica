#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include "../silly_string/silly_string.hpp"
#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.h>

// let's see if this crazy gizmo really works
// and define a default_string_adaptor specialisation
template<> class Arabica::default_string_adaptor<silly_string> : public silly_string_adaptor { };

using namespace Arabica::XPath;

class NodeTestTest : public TestCase
{
  DOM::DOMImplementation<silly_string> factory_;
  DOM::Document<silly_string> document_;

  DOM::Element<silly_string> root_;

  DOM::Element<silly_string> element1_;
  DOM::Element<silly_string> element2_;
  DOM::Element<silly_string> element3_;

  DOM::Attr<silly_string> attr_;

  DOM::Text<silly_string> text_;

  DOM::Comment<silly_string> comment_;

  DOM::ProcessingInstruction<silly_string> processingInstruction_;

  typedef silly_string_adaptor SA;

public:
  NodeTestTest(const std::string& name) : TestCase(name)
  {
  } // NodeTestTest

  void setUp()
  {
    factory_ = SimpleDOM::DOMImplementation<silly_string>::getDOMImplementation();
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
    element2_.appendChild(document_.createElement(SA::construct_from_utf8("spinkle")));
    element2_.appendChild(comment_);
    element2_.appendChild(processingInstruction_);

    attr_ = element1_.getAttributeNode(SA::construct_from_utf8("one"));

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);
  } // setUp

  void test1()
  {
    impl::AnyNodeTest<silly_string> test;

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
    impl::NameNodeTest<silly_string, Arabica::default_string_adaptor<silly_string> > test(SA::construct_from_utf8("child1"));

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
    impl::NameNodeTest<silly_string, Arabica::default_string_adaptor<silly_string> > test(SA::construct_from_utf8("one"));

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
    impl::TextNodeTest<silly_string> test;

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
    impl::CommentNodeTest<silly_string> test;

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
    impl::ProcessingInstructionNodeTest<silly_string, Arabica::default_string_adaptor<silly_string> > test;

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
    impl::ProcessingInstructionNodeTest<silly_string, Arabica::default_string_adaptor<silly_string> > test(SA::construct_from_utf8("fruity"));

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
    impl::ProcessingInstructionNodeTest<silly_string, Arabica::default_string_adaptor<silly_string> > test(SA::construct_from_utf8("target"));

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
    impl::StarNodeTest<silly_string> test;

    AxisEnumerator<silly_string, Arabica::default_string_adaptor<silly_string> > e(element2_, CHILD);
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
    impl::QNameNodeTest<silly_string> test(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("one"));

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
    impl::QNameNodeTest<silly_string> test(SA::construct_from_utf8("http://example.com/test"), 
                                           SA::construct_from_utf8("one"));

    DOM::Element<silly_string> e1_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), 
                                                               SA::construct_from_utf8("ns:one"));
    DOM::Element<silly_string> e2_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), 
                                                               SA::construct_from_utf8("ttt:one"));
    DOM::Element<silly_string> e3_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), 
                                                               SA::construct_from_utf8("ns:two"));
    DOM::Element<silly_string> e4_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), 
                                                               SA::construct_from_utf8("ttt:two"));
    DOM::Element<silly_string> e5_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/ssss"), 
                                                               SA::construct_from_utf8("ns:one"));
    DOM::Element<silly_string> e6_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/eeee"), 
                                                               SA::construct_from_utf8("ttt:one"));

    assertTrue(test(e1_));
    assertTrue(test(e2_));
    assertTrue(!test(e3_));
    assertTrue(!test(e4_));
    assertTrue(!test(e5_));
    assertTrue(!test(e6_));
  } // test11

  void test12()
  {
    impl::QStarNodeTest<silly_string> test(SA::construct_from_utf8("http://example.com/test"));

    DOM::Element<silly_string> e1_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("ns:one"));
    DOM::Element<silly_string> e2_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("ttt:one"));
    DOM::Element<silly_string> e3_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("ns:two"));
    DOM::Element<silly_string> e4_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("ttt:two"));
    DOM::Element<silly_string> e5_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/ssss"), SA::construct_from_utf8("ns:one"));
    DOM::Element<silly_string> e6_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/eeee"), SA::construct_from_utf8("ttt:one"));

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

