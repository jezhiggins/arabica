#ifndef STEP_TEST_H
#define STEP_TEST_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class StepTest : public TestCase
{
  typedef string_adaptor SA;

  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory_;
  Arabica::DOM::Document<string_type, string_adaptor> document_;

  Arabica::DOM::Element<string_type, string_adaptor> root_;

  Arabica::DOM::Element<string_type, string_adaptor> element1_;
  Arabica::DOM::Element<string_type, string_adaptor> element2_;
  Arabica::DOM::Element<string_type, string_adaptor> element3_;

  Arabica::DOM::Attr<string_type, string_adaptor> attr_;

public:
  StepTest(const std::string& name) : TestCase(name)
  {
  } // StepTest

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

    attr_ = element1_.getAttributeNode(SA::construct_from_utf8("one"));

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);
  } // setUp

  void test1()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> step(new impl::TestStepExpression<string_type, string_adaptor>(CHILD, new impl::AnyNodeTest<string_type, string_adaptor>()));

    XPathValue<string_type, string_adaptor> value = step.evaluate(root_);
    const NodeSet<string_type, string_adaptor>& set = value.asNodeSet();

    assertEquals(set.size(), 3);
    assertTrue(set[0] == element1_);
    assertTrue(set[1] == element2_);
    assertTrue(set[2] == element3_);
  } // test1

  void test2()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> step(new impl::TestStepExpression<string_type, string_adaptor>(ATTRIBUTE, new impl::AnyNodeTest<string_type, string_adaptor>()));

    NodeSet<string_type, string_adaptor> set = step.evaluateAsNodeSet(element2_);

    assertEquals(4, set.size());
    Arabica::DOM::Attr<string_type, string_adaptor> attr = static_cast<Arabica::DOM::Attr<string_type, string_adaptor> >(set[0]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("one"));
    attr = static_cast<Arabica::DOM::Attr<string_type, string_adaptor> >(set[1]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("two"));
    attr = static_cast<Arabica::DOM::Attr<string_type, string_adaptor> >(set[2]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("three"));
    attr = static_cast<Arabica::DOM::Attr<string_type, string_adaptor> >(set[3]);
    assertTrue(attr.getNodeName() == SA::construct_from_utf8("four"));
  } // test2

  void test3()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> step(new impl::TestStepExpression<string_type, 
      string_adaptor>(CHILD, new impl::NameNodeTest<string_type, string_adaptor>(SA::construct_from_utf8("child2"))));

    XPathValue<string_type, string_adaptor> value = step.evaluate(root_);
    const NodeSet<string_type, string_adaptor>& set = value.asNodeSet();

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
