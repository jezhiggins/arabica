#ifndef STEP_TEST_H
#define STEP_TEST_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.h>

template<class string_type, class string_adaptor>
class StepTest : public TestCase
{
  typedef string_adaptor SA;

  DOM::DOMImplementation<string_type> factory_;
  DOM::Document<string_type> document_;

  DOM::Element<string_type> root_;

  DOM::Element<string_type> element1_;
  DOM::Element<string_type> element2_;
  DOM::Element<string_type> element3_;

  DOM::Attr<string_type> attr_;

public:
  StepTest(const std::string& name) : TestCase(name)
  {
  } // StepTest

  void setUp()
  {
    factory_ = SimpleDOM::DOMImplementation<string_type>::getDOMImplementation();
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
    using namespace Arabica::XPath;
    XPathExpressionPtr<string_type> step(new impl::TestStepExpression<string_type, string_adaptor>(CHILD, new impl::AnyNodeTest<string_type>()));

    XPathValuePtr<string_type> value = step->evaluate(root_);
    const NodeSet<string_type>& set = value->asNodeSet();

    assertEquals(set.size(), 3);
    assertTrue(set[0] == element1_);
    assertTrue(set[1] == element2_);
    assertTrue(set[2] == element3_);
  } // test1

  void test2()
  {
    using namespace Arabica::XPath;
    XPathExpressionPtr<string_type> step(new impl::TestStepExpression<string_type, string_adaptor>(ATTRIBUTE, new impl::AnyNodeTest<string_type>()));

    NodeSet<string_type> set = step->evaluateAsNodeSet(element2_);

    assertEquals(4, set.size());
    DOM::Attr<string_type> attr = static_cast<DOM::Attr<string_type> >(set[0]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("one"));
    attr = static_cast<DOM::Attr<string_type> >(set[1]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("two"));
    attr = static_cast<DOM::Attr<string_type> >(set[2]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("three"));
    attr = static_cast<DOM::Attr<string_type> >(set[3]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("four"));
  } // test2

  void test3()
  {
    using namespace Arabica::XPath;
    XPathExpressionPtr<string_type> step(new impl::TestStepExpression<string_type, 
      string_adaptor>(CHILD, new impl::NameNodeTest<string_type, string_adaptor>(SA::construct_from_utf8("child2"))));

    XPathValuePtr<string_type> value = step->evaluate(root_);
    const NodeSet<string_type>& set = value->asNodeSet();

    assertEquals(1, set.size());
    assertTrue(set[0] == element2_);
  } // test3
}; // class StepTest

template<class string_type, class string_adaptor>
TestSuite* StepTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<StepTest<string_type, string_adaptor> >("test1", &StepTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<StepTest<string_type, string_adaptor> >("test2", &StepTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<StepTest<string_type, string_adaptor> >("test3", &StepTest<string_type, string_adaptor>::test3));

  return suiteOfTests;
} // StepTest_suite

#endif
