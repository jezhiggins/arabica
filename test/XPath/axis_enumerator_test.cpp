#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.h>

using namespace Arabica::XPath;

class AxisEnumeratorTest : public TestCase
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
  AxisEnumeratorTest(const std::string& name) : TestCase(name)
  {
  } // AxisEnumeratorTest

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
  } // setup

  void childTest1()
  {
    DOM::DocumentFragment<std::string> node;

    AxisEnumerator e(node, CHILD);
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // test1

  void childTest2()
  {
    DOM::Node<std::string> node;

    AxisEnumerator e(node, CHILD);
    assertTrue(*e == 0);
  } // test2

  void childTest3()
  {
    AxisEnumerator e(root_, CHILD);

    assertTrue(element1_ == *e);
    assertEquals("child1", e->getNodeName());
    ++e;
    assertTrue(element2_ == *e);
    assertEquals("child2", e->getNodeName());
    ++e;
    assertTrue(element3_ == *e);
    assertEquals("child3", e->getNodeName());
    ++e;
    assertTrue(DOM::Node<std::string>() == *e);
    assertTrue(*e == 0);
  } // test3

  void childTest4()
  {
    AxisEnumerator e(document_, CHILD);

    assertTrue(root_ == *e);
    ++e;
    assertTrue(*e == 0);
  } // childTest4

  void attributeTest1()
  {
    DOM::DocumentFragment<std::string> node;

    AxisEnumerator e(node, ATTRIBUTE);
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // attributeTest1

  void attributeTest2()
  {
    DOM::Node<std::string> node;

    AxisEnumerator e(node, ATTRIBUTE);
    assertTrue(*e == 0);
  } // attributeTest2

  void attributeTest3()
  {
    AxisEnumerator e(element1_, ATTRIBUTE);
    assertEquals("one", e->getNodeName());
    assertEquals("1", e->getNodeValue());
    ++e;
    assertTrue(*e == 0);
  } // attributeTest3

  void attributeTest4()
  {
    int count = 0;
    AxisEnumerator e(element2_, ATTRIBUTE);
    while(*e++ != 0)
      ++count;
    assertEquals(4, count);
  } // attributeTest4

  void attributeTest5()
  {
    element2_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:poop", "poop-uri");

    int count = 0;
    AxisEnumerator e(element2_, ATTRIBUTE);
    while(*e++ != 0)
      ++count;
    assertEquals(4, count);
  } // attributeTest5

  void attributeTest6()
  {
    element2_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:poop", "poop-uri");
    element2_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:qooq", "qooq-uri");

    int count = 0;
    AxisEnumerator e(element2_, ATTRIBUTE);
    while(*e++ != 0)
      ++count;
    assertEquals(4, count);
  } // attributeTest6

  void followingSiblingTest1()
  {
    DOM::Node<std::string> node;
    AxisEnumerator e(node, FOLLOWING_SIBLING);
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // followingSiblingTest1

  void followingSiblingTest2()
  {
    AxisEnumerator e(document_, FOLLOWING_SIBLING);
    assertTrue(*e == 0);
  } // followingSiblingTest2

  void followingSiblingTest3()
  {
    AxisEnumerator e(element1_, FOLLOWING_SIBLING);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingSiblingTest3

  void followingSiblingTest4()
  {
    AxisEnumerator e(element2_, FOLLOWING_SIBLING);
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingSiblingTest4

  void followingSiblingTest5()
  {
    AxisEnumerator e(element3_, FOLLOWING_SIBLING);
    assertTrue(*e == 0);
  } // followingSiblingTest5

  void followingSiblingTest6()
  {
    AxisEnumerator e(attr_, FOLLOWING_SIBLING);
    assertTrue(*e == 0);
  } // followingSiblingTest6

  void precedingSiblingTest1()
  {
    DOM::Node<std::string> node;
    AxisEnumerator e(node, PRECEDING_SIBLING);
    assertTrue(*e == 0);
    assertTrue(e.reverse());
  } // precedingSiblingTest1

  void precedingSiblingTest2()
  {
    AxisEnumerator e(document_, PRECEDING_SIBLING);
    assertTrue(*e == 0);
  } // precedingSiblingTest2

  void precedingSiblingTest3()
  {
    AxisEnumerator e(element3_, PRECEDING_SIBLING);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingSiblingTest3

  void precedingSiblingTest4()
  {
    AxisEnumerator e(element2_, PRECEDING_SIBLING);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingSiblingTest4

  void precedingSiblingTest5()
  {
    AxisEnumerator e(element1_, PRECEDING_SIBLING);
    assertTrue(*e == 0);
  } // precedingSiblingTest5

  void precedingSiblingTest6()
  {
    AxisEnumerator e(attr_, PRECEDING_SIBLING);
    assertTrue(*e == 0);
  } // precedingSiblingTest6

  void selfTest1()
  {
    AxisEnumerator e(document_, SELF);
    assertTrue(document_ == *e);
    ++e;
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // selfTest1

  void selfTest2()
  {
    AxisEnumerator e(root_, SELF);
    assertTrue(root_ == *e);
    ++e;
    assertTrue(*e == 0);
  } // selfTest2

  void selfTest3()
  {
    DOM::Node<std::string> node;
    AxisEnumerator e(node, SELF);
    assertTrue(*e == 0);
  } // selfTest3

  void parentTest1()
  {
    AxisEnumerator e(document_, PARENT);
    assertTrue(*e == 0);
    assertTrue(e.reverse());
  } // parentTest1

  void parentTest2()
  {
    AxisEnumerator e(root_, PARENT);
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // parentTest2

  void parentTest3()
  {
    AxisEnumerator e(element2_, PARENT);
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == 0);
  } // parentTest3

  void parentTest4()
  {
    AxisEnumerator e(attr_, PARENT);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // parentTest4

  void ancestorTest1()
  {
    AxisEnumerator e(document_, ANCESTOR);
    assertTrue(*e == 0);
    assertTrue(e.reverse());
  } // ancestorTest1

  void ancestorTest2()
  {
    AxisEnumerator e(root_, ANCESTOR);
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorTest2

  void ancestorTest3()
  {
    AxisEnumerator e(element2_, ANCESTOR);
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorTest3

  void ancestorTest4()
  {
    AxisEnumerator e(attr_, ANCESTOR);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorTest4

  void ancestorOrSelfTest1()
  {
    AxisEnumerator e(document_, ANCESTOR_OR_SELF);
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
    assertTrue(e.reverse());
  } // ancestorOrSelfTest1

  void ancestorOrSelfTest2()
  {
    AxisEnumerator e(root_, ANCESTOR_OR_SELF);
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorOrSelfTest2

  void ancestorOrSelfTest3()
  {
    AxisEnumerator e(element2_, ANCESTOR_OR_SELF);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorOrSelfTest3

  void ancestorOrSelfTest4()
  {
    AxisEnumerator e(attr_, ANCESTOR_OR_SELF);
    assertTrue(*e == attr_);
    ++e;
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorOrSelfTest4

  void descendantTest1()
  {
    AxisEnumerator e(root_, DESCENDANT);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // descendantTest1

  void descendantTest2()
  {
    AxisEnumerator e(element1_, DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest2

  void descendantTest3()
  {
    AxisEnumerator e(element2_, DESCENDANT);
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == 0);
  } // descendantTest3

  void descendantTest4()
  {
    AxisEnumerator e(comment_, DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest4

  void descendantTest5()
  {
    AxisEnumerator e(processingInstruction_, DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest5

  void descendantTest6()
  {
    AxisEnumerator e(text_, DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest6

  void descendantTest7()
  {
    AxisEnumerator e(attr_, DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest7

  void descendantOrSelfTest1()
  {
    AxisEnumerator e(root_, DESCENDANT_OR_SELF);
    assertTrue(e.forward());
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest1

  void descendantOrSelfTest2()
  {
    AxisEnumerator e(element1_, DESCENDANT_OR_SELF);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest2

  void descendantOrSelfTest3()
  {
    AxisEnumerator e(element2_, DESCENDANT_OR_SELF);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest3

  void descendantOrSelfTest4()
  {
    AxisEnumerator e(comment_, DESCENDANT_OR_SELF);
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest4

  void descendantOrSelfTest5()
  {
    AxisEnumerator e(processingInstruction_, DESCENDANT_OR_SELF);
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest5

  void descendantOrSelfTest6()
  {
    AxisEnumerator e(text_, DESCENDANT_OR_SELF);
    assertTrue(*e == text_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest6

  void descendantOrSelfTest7()
  {
    AxisEnumerator e(attr_, DESCENDANT_OR_SELF);
    assertTrue(*e == attr_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest7

  void followingTest1()
  {
    AxisEnumerator e(root_, FOLLOWING);
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // followingTest1

  void followingTest2()
  {
    AxisEnumerator e(element1_, FOLLOWING);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest2

  void followingTest3()
  {
    AxisEnumerator e(element2_, FOLLOWING);
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest3

  void followingTest4()
  {
    AxisEnumerator e(comment_, FOLLOWING);
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest4

  void followingTest5()
  {
    AxisEnumerator e(processingInstruction_, FOLLOWING);
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest5

  void followingTest6()
  {
    AxisEnumerator e(text_, FOLLOWING);
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest6

  void followingTest7()
  {
    AxisEnumerator e(attr_, FOLLOWING);
    assertTrue(*e == 0);
  } // followingTest7

  void precedingTest1()
  {
    AxisEnumerator e(root_, PRECEDING);
    assertTrue(*e == 0);
  } // precedingTest1

  void precedingTest2()
  {
    AxisEnumerator e(element1_, PRECEDING);
    assertTrue(*e == 0);
  } // precedingTest2

  void precedingTest3()
  {
    AxisEnumerator e(element2_, PRECEDING);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingTest3

  void precedingTest4() 
  {
    AxisEnumerator e(comment_, PRECEDING);
    assertTrue(e.reverse());
    ++e; // spinkle
    assertTrue(*e == text_);
    ++e;
    assertTrue(*e == element1_);
    ++e; 
    assertTrue(*e == 0);
  } // precedingTest4();

  void precedingTest5()
  {
    AxisEnumerator e(processingInstruction_, PRECEDING);
    assertTrue(*e == comment_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == text_);
    ++e;
    assertTrue(*e == element1_);
    ++e; 
    assertTrue(*e == 0);
  } // precedingTest5

  void precedingTest6()
  {
    AxisEnumerator e(text_, PRECEDING);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingTest6

  void precedingTest7()
  {
    AxisEnumerator e(element3_, PRECEDING);
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == comment_);
    ++e;
    ++e; // spinkle;
    assertTrue(*e == text_);
    ++e;
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingTest7

  void namespaceNodeTest1()
  {
    DOM::Node<std::string> node(new NamespaceNodeImpl<std::string>("p", "test-uri"));
    DOM::Node<std::string> node2;

    node2 = node;
  } // namespaceNodeTest1

  void namespaceNodeTest2()
  {
    DOM::Node<std::string> node;
    {
      DOM::Node<std::string> node2(new NamespaceNodeImpl<std::string>("p", "test-uri"));
      node = node2;
    }
  } // namespaceNodeTest2

  void namespaceNodeTest3()
  {
    DOM::Node<std::string> node;
    {
      DOM::Node<std::string> node2(new NamespaceNodeImpl<std::string>("p", "test-uri"));
      node = node2;
    }
    node = 0;
  } // namespaceNodeTest3

  void namespaceNodeTest4()
  {
    DOM::Node<std::string> node(new NamespaceNodeImpl<std::string>("p", "test-uri"));
    assertValuesEqual("p", node.getLocalName());
    assertValuesEqual("test-uri", node.getNodeValue());
    assertValuesEqual("", node.getNamespaceURI());
    assertValuesEqual("p", node.getNodeName());
  } // namespaceNodeTest4

  void namespaceAxisTest1()
  {
    AxisEnumerator e(root_, NAMESPACE);
    assertTrue(*e == 0);
  } // namespaceAxisTest1()

  void namespaceAxisTest2()
  {
    root_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:poop", "urn:test");
    AxisEnumerator e(root_, NAMESPACE);
    assertTrue(*e != 0);
    DOM::Node<std::string> ns = *e;
    assertValuesEqual("poop", ns.getLocalName());
    assertValuesEqual("urn:test", ns.getNodeValue());
    ++e;
    assertTrue(*e == 0);
  } // namespaceAxisTest2

  void namespaceAxisTest3()
  {
    root_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:poop", "urn:test");
    element2_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:test", "urn:another-test");
    AxisEnumerator e(element2_, NAMESPACE);
    assertTrue(*e != 0);
    ++e;
    assertTrue(*e != 0);
    ++e;
    assertTrue(*e == 0);
  } // namespaceAxisTest3

}; // AxisEnumeratorTest

TestSuite* AncestorTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("ancestorTest1", &AxisEnumeratorTest::ancestorTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("ancestorTest2", &AxisEnumeratorTest::ancestorTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("ancestorTest3", &AxisEnumeratorTest::ancestorTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("ancestorTest4", &AxisEnumeratorTest::ancestorTest4));

  return suiteOfTests;
} // AncestorTest_suite

TestSuite* AncestorOrSelfTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("ancestorOrSelfTest1", &AxisEnumeratorTest::ancestorOrSelfTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("ancestorOrSelfTest2", &AxisEnumeratorTest::ancestorOrSelfTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("ancestorOrSelfTest3", &AxisEnumeratorTest::ancestorOrSelfTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("ancestorOrSelfTest4", &AxisEnumeratorTest::ancestorOrSelfTest4));

  return suiteOfTests;
} // AncestorOrSelfTest_suite

TestSuite* ChildTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("childTest1", &AxisEnumeratorTest::childTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("childTest2", &AxisEnumeratorTest::childTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("childTest3", &AxisEnumeratorTest::childTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("childTest4", &AxisEnumeratorTest::childTest4));

  return suiteOfTests;
} // ChildTest_suite

TestSuite* AttributeTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("attributeTest1", &AxisEnumeratorTest::attributeTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("attributeTest2", &AxisEnumeratorTest::attributeTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("attributeTest3", &AxisEnumeratorTest::attributeTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("attributeTest4", &AxisEnumeratorTest::attributeTest4));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("attributeTest5", &AxisEnumeratorTest::attributeTest5));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("attributeTest6", &AxisEnumeratorTest::attributeTest6));

  return suiteOfTests;
} // AttributeTest_suite

TestSuite* FollowingSibling_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingSiblingTest1", &AxisEnumeratorTest::followingSiblingTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingSiblingTest2", &AxisEnumeratorTest::followingSiblingTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingSiblingTest3", &AxisEnumeratorTest::followingSiblingTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingSiblingTest4", &AxisEnumeratorTest::followingSiblingTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingSiblingTest5", &AxisEnumeratorTest::followingSiblingTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingSiblingTest6", &AxisEnumeratorTest::followingSiblingTest6));

  return suite;
} // FollowingSibling_suite

TestSuite* PrecedingSibling_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingSiblingTest1", &AxisEnumeratorTest::precedingSiblingTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingSiblingTest2", &AxisEnumeratorTest::precedingSiblingTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingSiblingTest3", &AxisEnumeratorTest::precedingSiblingTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingSiblingTest4", &AxisEnumeratorTest::precedingSiblingTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingSiblingTest5", &AxisEnumeratorTest::precedingSiblingTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingSiblingTest6", &AxisEnumeratorTest::precedingSiblingTest6));

  return suite;
} // PrecedingSibling_suite

TestSuite* SelfTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("selfTest1", &AxisEnumeratorTest::selfTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("selfTest2", &AxisEnumeratorTest::selfTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("selfTest3", &AxisEnumeratorTest::selfTest3));

  return suiteOfTests;
} // SelfTest_suite

TestSuite* ParentTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("parentTest1", &AxisEnumeratorTest::parentTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("parentTest2", &AxisEnumeratorTest::parentTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("parentTest3", &AxisEnumeratorTest::parentTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest>("parentTest4", &AxisEnumeratorTest::parentTest4));

  return suiteOfTests;
} // ParentTest_suite

TestSuite* DescendantTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantTest1", &AxisEnumeratorTest::descendantTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantTest2", &AxisEnumeratorTest::descendantTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantTest3", &AxisEnumeratorTest::descendantTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantTest4", &AxisEnumeratorTest::descendantTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantTest5", &AxisEnumeratorTest::descendantTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantTest6", &AxisEnumeratorTest::descendantTest6));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantTest7", &AxisEnumeratorTest::descendantTest7));

  return suite;
} // DescendantTest_suite

TestSuite* DescendantOrSelfTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantOrSelfTest1", &AxisEnumeratorTest::descendantOrSelfTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantOrSelfTest2", &AxisEnumeratorTest::descendantOrSelfTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantOrSelfTest3", &AxisEnumeratorTest::descendantOrSelfTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantOrSelfTest4", &AxisEnumeratorTest::descendantOrSelfTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantOrSelfTest5", &AxisEnumeratorTest::descendantOrSelfTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantOrSelfTest6", &AxisEnumeratorTest::descendantOrSelfTest6));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("descendantOrSelfTest7", &AxisEnumeratorTest::descendantOrSelfTest7));

  return suite;
} // DescendantOrSelfTest_suite

TestSuite* FollowingTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingTest1", &AxisEnumeratorTest::followingTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingTest2", &AxisEnumeratorTest::followingTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingTest3", &AxisEnumeratorTest::followingTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingTest4", &AxisEnumeratorTest::followingTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingTest5", &AxisEnumeratorTest::followingTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingTest6", &AxisEnumeratorTest::followingTest6));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("followingTest7", &AxisEnumeratorTest::followingTest7));

  return suite;
} // FollowingTest_suite

TestSuite* PrecedingTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingTest1", &AxisEnumeratorTest::precedingTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingTest2", &AxisEnumeratorTest::precedingTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingTest3", &AxisEnumeratorTest::precedingTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingTest4", &AxisEnumeratorTest::precedingTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingTest5", &AxisEnumeratorTest::precedingTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingTest6", &AxisEnumeratorTest::precedingTest6));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("precedingTest7", &AxisEnumeratorTest::precedingTest7));

  return suite;
} // PrecedingTest_suite

TestSuite* NamespaceNodeTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest>("namespaceNodeTest1", &AxisEnumeratorTest::namespaceNodeTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("namespaceNodeTest2", &AxisEnumeratorTest::namespaceNodeTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("namespaceNodeTest3", &AxisEnumeratorTest::namespaceNodeTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("namespaceNodeTest4", &AxisEnumeratorTest::namespaceNodeTest4));

  return suite;
} // NamespaceNodeTest_suite

TestSuite* NamespaceAxisTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest>("namespaceAxisTest1", &AxisEnumeratorTest::namespaceAxisTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("namespaceAxisTest2", &AxisEnumeratorTest::namespaceAxisTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest>("namespaceAxisTest3", &AxisEnumeratorTest::namespaceAxisTest3));

  return suite;
} // NamespaceAxisTest_suite

TestSuite* AxisEnumeratorTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(AncestorTest_suite());
  suiteOfTests->addTest(AncestorOrSelfTest_suite());
  suiteOfTests->addTest(AttributeTest_suite());
  suiteOfTests->addTest(ChildTest_suite());
  suiteOfTests->addTest(FollowingSibling_suite());
  suiteOfTests->addTest(PrecedingSibling_suite());
  suiteOfTests->addTest(SelfTest_suite());
  suiteOfTests->addTest(ParentTest_suite());
  suiteOfTests->addTest(DescendantTest_suite());
  suiteOfTests->addTest(DescendantOrSelfTest_suite());
  suiteOfTests->addTest(FollowingTest_suite());
  suiteOfTests->addTest(PrecedingTest_suite());
  suiteOfTests->addTest(NamespaceNodeTest_suite());
  suiteOfTests->addTest(NamespaceAxisTest_suite());

  return suiteOfTests;
} // AxisEnumeratorTest_suite

