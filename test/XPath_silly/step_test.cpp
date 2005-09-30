#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4267 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include "step_test.hpp"
#include <DOM/Simple/DOMImplementation.h>
#include "../silly_string/silly_string.hpp"

using namespace Arabica::XPath;
template<> class Arabica::default_string_adaptor<silly_string> : public silly_string_adaptor { };

class StepTest : public TestCase
{
  typedef silly_string_adaptor SA;

  DOM::DOMImplementation<silly_string> factory_;
  DOM::Document<silly_string> document_;

  DOM::Element<silly_string> root_;

  DOM::Element<silly_string> element1_;
  DOM::Element<silly_string> element2_;
  DOM::Element<silly_string> element3_;

  DOM::Attr<silly_string> attr_;

public:
  StepTest(const std::string& name) : TestCase(name)
  {
  } // StepTest

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

    attr_ = element1_.getAttributeNode(SA::construct_from_utf8("one"));

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);
  } // setUp

  void test1()
  {
    XPathExpressionPtr<silly_string> step(new impl::TestStepExpression<silly_string, Arabica::default_string_adaptor<silly_string> >(CHILD, new impl::AnyNodeTest<silly_string>()));

    XPathValuePtr<silly_string> value = step->evaluate(root_);
    const NodeSet<silly_string>& set = value->asNodeSet();

    assertEquals(set.size(), 3);
    assertTrue(set[0] == element1_);
    assertTrue(set[1] == element2_);
    assertTrue(set[2] == element3_);
  } // test1

  void test2()
  {
    XPathExpressionPtr<silly_string> step(new impl::TestStepExpression<silly_string, Arabica::default_string_adaptor<silly_string> >(ATTRIBUTE, new impl::AnyNodeTest<silly_string>()));

    NodeSet<silly_string> set = step->evaluateAsNodeSet(element2_);

    assertEquals(4, set.size());
    DOM::Attr<silly_string> attr = static_cast<DOM::Attr<silly_string> >(set[0]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("one"));
    attr = static_cast<DOM::Attr<silly_string> >(set[1]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("two"));
    attr = static_cast<DOM::Attr<silly_string> >(set[2]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("three"));
    attr = static_cast<DOM::Attr<silly_string> >(set[3]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("four"));
  } // test2

  void test3()
  {
    XPathExpressionPtr<silly_string> step(new impl::TestStepExpression<silly_string, 
      Arabica::default_string_adaptor<silly_string> >(CHILD, new impl::NameNodeTest<silly_string, Arabica::default_string_adaptor<silly_string> >(SA::construct_from_utf8("child2"))));

    XPathValuePtr<silly_string> value = step->evaluate(root_);
    const NodeSet<silly_string>& set = value->asNodeSet();

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
