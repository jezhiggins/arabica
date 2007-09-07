#ifndef NODE_TEST_TEST_H
#define NODE_TEST_TEST_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class NodeTestTest : public TestCase
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory_;
  Arabica::DOM::Document<string_type, string_adaptor> document_;

  Arabica::DOM::Element<string_type, string_adaptor> root_;

  Arabica::DOM::Element<string_type, string_adaptor> element1_;
  Arabica::DOM::Element<string_type, string_adaptor> element2_;
  Arabica::DOM::Element<string_type, string_adaptor> element3_;

  Arabica::DOM::Attr<string_type, string_adaptor> attr_;

  Arabica::DOM::Text<string_type, string_adaptor> text_;

  Arabica::DOM::Comment<string_type, string_adaptor> comment_;

  Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> processingInstruction_;

  typedef string_adaptor SA;

public:
  NodeTestTest(const std::string& name) : TestCase(name)
  {
  } // NodeTestTest

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
    using namespace Arabica::XPath;
    impl::AnyNodeTest<string_type, string_adaptor> test;

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
    using namespace Arabica::XPath;
    impl::NameNodeTest<string_type, string_adaptor> test(SA::construct_from_utf8("child1"));

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
    using namespace Arabica::XPath;
    impl::NameNodeTest<string_type, string_adaptor> test(SA::construct_from_utf8("one"));

    assertTrue(!test(element1_));
    assertTrue(!test(element2_));
    assertTrue(!test(root_));
    assertTrue(!test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(!test(comment_));
    assertTrue(!test(processingInstruction_));
  } // test3

  void test4()
  {
    using namespace Arabica::XPath;
    impl::TextNodeTest<string_type, string_adaptor> test;

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
    using namespace Arabica::XPath;
    impl::CommentNodeTest<string_type, string_adaptor> test;

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
    using namespace Arabica::XPath;
    impl::ProcessingInstructionNodeTest<string_type, string_adaptor> test;

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
    using namespace Arabica::XPath;
    impl::ProcessingInstructionNodeTest<string_type, string_adaptor> test(SA::construct_from_utf8("fruity"));

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
    using namespace Arabica::XPath;
    impl::ProcessingInstructionNodeTest<string_type, string_adaptor> test(SA::construct_from_utf8("target"));

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
    using namespace Arabica::XPath;
    impl::StarNodeTest<string_type, string_adaptor> test;

    AxisEnumerator<string_type, string_adaptor> e(element2_, CHILD);
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
    using namespace Arabica::XPath;
    impl::QNameNodeTest<string_type, string_adaptor> test(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("one"));

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
    using namespace Arabica::XPath;
    impl::QNameNodeTest<string_type, string_adaptor> test(SA::construct_from_utf8("http://example.com/test"), 
                                           SA::construct_from_utf8("one"));

    Arabica::DOM::Element<string_type, string_adaptor> e1_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), 
                                                               SA::construct_from_utf8("ns:one"));
    Arabica::DOM::Element<string_type, string_adaptor> e2_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), 
                                                               SA::construct_from_utf8("ttt:one"));
    Arabica::DOM::Element<string_type, string_adaptor> e3_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), 
                                                               SA::construct_from_utf8("ns:two"));
    Arabica::DOM::Element<string_type, string_adaptor> e4_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), 
                                                               SA::construct_from_utf8("ttt:two"));
    Arabica::DOM::Element<string_type, string_adaptor> e5_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/ssss"), 
                                                               SA::construct_from_utf8("ns:one"));
    Arabica::DOM::Element<string_type, string_adaptor> e6_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/eeee"), 
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
    using namespace Arabica::XPath;
    impl::QStarNodeTest<string_type, string_adaptor> test(SA::construct_from_utf8("http://example.com/test"));

    Arabica::DOM::Element<string_type, string_adaptor> e1_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("ns:one"));
    Arabica::DOM::Element<string_type, string_adaptor> e2_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("ttt:one"));
    Arabica::DOM::Element<string_type, string_adaptor> e3_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("ns:two"));
    Arabica::DOM::Element<string_type, string_adaptor> e4_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/test"), SA::construct_from_utf8("ttt:two"));
    Arabica::DOM::Element<string_type, string_adaptor> e5_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/ssss"), SA::construct_from_utf8("ns:one"));
    Arabica::DOM::Element<string_type, string_adaptor> e6_ = document_.createElementNS(SA::construct_from_utf8("http://example.com/eeee"), SA::construct_from_utf8("ttt:one"));

    assertTrue(test(e1_));
    assertTrue(test(e2_));
    assertTrue(test(e3_));
    assertTrue(test(e4_));
    assertTrue(!test(e5_));
    assertTrue(!test(e6_));
  } // test12

  void test13()
  {
    using namespace Arabica::XPath;
    impl::AttributeNameNodeTest<string_type, string_adaptor> test(SA::construct_from_utf8("one"));

    assertTrue(!test(element1_));
    assertTrue(!test(element2_));
    assertTrue(!test(root_));
    assertTrue(test(attr_));
    assertTrue(!test(document_));
    assertTrue(!test(text_));
    assertTrue(!test(comment_));
    assertTrue(!test(processingInstruction_));
  } // test13

  void test14()
  {
    using namespace Arabica::XPath;
    impl::NodeNodeTest<string_type, string_adaptor> test;

    assertTrue(test(element1_));
    assertTrue(test(element2_));
    assertTrue(test(root_));
    assertTrue(test(attr_));
    assertTrue(!test(document_));
    assertTrue(test(text_));
    assertTrue(test(comment_));
    assertTrue(test(processingInstruction_));
  } // test14
}; // class NodeTestTest

template<class string_type, class string_adaptor>
TestSuite* NodeTestTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test1", &NodeTestTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test2", &NodeTestTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test3", &NodeTestTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test4", &NodeTestTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test5", &NodeTestTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test6", &NodeTestTest<string_type, string_adaptor>::test6));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test7", &NodeTestTest<string_type, string_adaptor>::test7));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test8", &NodeTestTest<string_type, string_adaptor>::test8));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test9", &NodeTestTest<string_type, string_adaptor>::test9));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test10", &NodeTestTest<string_type, string_adaptor>::test10));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test11", &NodeTestTest<string_type, string_adaptor>::test11));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test12", &NodeTestTest<string_type, string_adaptor>::test12));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test13", &NodeTestTest<string_type, string_adaptor>::test13));
  suiteOfTests->addTest(new TestCaller<NodeTestTest<string_type, string_adaptor> >("test14", &NodeTestTest<string_type, string_adaptor>::test14));

  return suiteOfTests;
} // NodeTestTest_suite

#endif
