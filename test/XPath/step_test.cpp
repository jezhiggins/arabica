#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4267 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include "step_test.hpp"
#include <DOM/Simple/DOMImplementation.h>

using namespace Arabica::XPath;

class StepTest : public TestCase
{
  DOM::DOMImplementation<std::string> factory_;
  DOM::Document<std::string> document_;

  DOM::Element<std::string> root_;

  DOM::Element<std::string> element1_;
  DOM::Element<std::string> element2_;
  DOM::Element<std::string> element3_;

  DOM::Attr<std::string> attr_;

public:
  StepTest(const std::string& name) : TestCase(name)
  {
  } // StepTest

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

    attr_ = element1_.getAttributeNode("one");

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);
  } // setUp

  void test1()
  {
    XPathExpressionPtr<std::string> step(new TestStepExpression(CHILD, new AnyNodeTest<std::string>()));

    XPathValuePtr<std::string> value = step->evaluate(root_);
    const NodeSet<std::string>& set = value->asNodeSet();

    assertEquals(set.size(), 3);
    assertTrue(set[0] == element1_);
    assertTrue(set[1] == element2_);
    assertTrue(set[2] == element3_);
  } // test1

  void test2()
  {
    XPathExpressionPtr<std::string> step(new TestStepExpression(ATTRIBUTE, new AnyNodeTest<std::string>()));

    NodeSet<std::string> set = step->evaluateAsNodeSet(element2_);

    assertEquals(4, set.size());
    DOM::Attr<std::string> attr = static_cast<DOM::Attr<std::string> >(set[0]);
    assertEquals(attr.getNodeName(), "one");
    attr = static_cast<DOM::Attr<std::string> >(set[1]);
    assertEquals(attr.getNodeName(), "two");
    attr = static_cast<DOM::Attr<std::string> >(set[2]);
    assertEquals(attr.getNodeName(), "three");
    attr = static_cast<DOM::Attr<std::string> >(set[3]);
    assertEquals(attr.getNodeName(), "four");
  } // test2

  void test3()
  {
    XPathExpressionPtr<std::string> step(new TestStepExpression(CHILD, new NameNodeTest<std::string>("child2")));

    XPathValuePtr<std::string> value = step->evaluate(root_);
    const NodeSet<std::string>& set = value->asNodeSet();

    assertEquals(1, set.size());
    assertTrue(set[0] == element2_);
  } // test3
}; // class StepTest

TestSuite* StepTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<StepTest>("test1", &StepTest::test1));
  suiteOfTests->addTest(new TestCaller<StepTest>("test2", &StepTest::test2));
  suiteOfTests->addTest(new TestCaller<StepTest>("test3", &StepTest::test3));

  return suiteOfTests;
} // StepTest_suite
