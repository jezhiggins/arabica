#ifndef XPATHIC_RELATIONAL_TEST_H
#define XPATHIC_RELATIONAL_TEST_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>

template<class string_type, class string_adaptor>
class RelationalTest : public TestCase
{
public:
  RelationalTest(const std::string& name) : TestCase(name)
  {
  } // RelationalTest

  void setUp()
  {
  } // setUp

  void test1()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> equals1(new impl::EqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(1), new NumericValue<string_type, string_adaptor>(1)));
    XPathExpression<string_type, string_adaptor> equals2(new impl::EqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(1), new NumericValue<string_type, string_adaptor>(1)));

    assertEquals(true, equals1.evaluateAsBool(dummy_));
    assertEquals(true, equals2.evaluateAsBool(dummy_));
  } // test1

  void test2()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> equals1(new impl::EqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(1), new NumericValue<string_type, string_adaptor>(2)));
    XPathExpression<string_type, string_adaptor> equals2(new impl::EqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(2), new NumericValue<string_type, string_adaptor>(1)));

    assertEquals(false, equals1.evaluateAsBool(dummy_));
    assertEquals(false, equals2.evaluateAsBool(dummy_));
  } // test2

  void test3()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> equals1(new impl::EqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(1), new NumericValue<string_type, string_adaptor>(1)));

    assertEquals(true, equals1.evaluateAsBool(dummy_));
  } // test3

  void test4()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new StringValue<string_type, string_adaptor>("charlie");
    XPathExpression_impl<string_type, string_adaptor>* p2 = new StringValue<string_type, string_adaptor>("charlie");

    XPathExpression<string_type, string_adaptor> equals1(new impl::EqualsOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(true, equals1.evaluateAsBool(dummy_));
  } // test4

  void test5()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new StringValue<string_type, string_adaptor>("trousers");
    XPathExpression_impl<string_type, string_adaptor>* p2 = new StringValue<string_type, string_adaptor>("charlie");

    XPathExpression<string_type, string_adaptor> equals1(new impl::EqualsOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(false, equals1.evaluateAsBool(dummy_));
  } // test5

  void test6()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> equals1(new impl::EqualsOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(true)));
    XPathExpression<string_type, string_adaptor> equals2(new impl::EqualsOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(false)));

    assertEquals(true, equals1.evaluateAsBool(dummy_));
    assertEquals(true, equals2.evaluateAsBool(dummy_));
  } // test6

  void test7()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> equals1(new impl::EqualsOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(false)));
    XPathExpression<string_type, string_adaptor> equals2(new impl::EqualsOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(true)));

    assertEquals(false, equals1.evaluateAsBool(dummy_));
    assertEquals(false, equals2.evaluateAsBool(dummy_));
  } // test7

  void testLessThan1()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> lessThan1(new impl::LessThanOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(true)));
    XPathExpression<string_type, string_adaptor> lessThan2(new impl::LessThanOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(false)));
    XPathExpression<string_type, string_adaptor> lessThan3(new impl::LessThanOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(false)));
    XPathExpression<string_type, string_adaptor> lessThan4(new impl::LessThanOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(true)));

    assertEquals(false, lessThan1.evaluateAsBool(dummy_));
    assertEquals(false, lessThan2.evaluateAsBool(dummy_));
    assertEquals(false, lessThan3.evaluateAsBool(dummy_));
    assertEquals(true, lessThan4.evaluateAsBool(dummy_));
  } // testLessThan1

  void testLessThan2()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> lessThan1(new impl::LessThanOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(1.0), new NumericValue<string_type, string_adaptor>(1.0)));
    XPathExpression<string_type, string_adaptor> lessThan2(new impl::LessThanOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(3.0), new NumericValue<string_type, string_adaptor>(2.0)));
    XPathExpression<string_type, string_adaptor> lessThan3(new impl::LessThanOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(2.0), new NumericValue<string_type, string_adaptor>(3.0)));
    XPathExpression<string_type, string_adaptor> lessThan4(new impl::LessThanOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(-1), new NumericValue<string_type, string_adaptor>(1)));

    assertEquals(false, lessThan1.evaluateAsBool(dummy_));
    assertEquals(false, lessThan2.evaluateAsBool(dummy_));
    assertEquals(true, lessThan3.evaluateAsBool(dummy_));
    assertEquals(true, lessThan4.evaluateAsBool(dummy_));
  } // testLessThan2

  void testLessThan3()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> lessThan1(new impl::LessThanOperator<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>("1.0"), new StringValue<string_type, string_adaptor>("1.0")));
    XPathExpression<string_type, string_adaptor> lessThan2(new impl::LessThanOperator<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>("3.0"), new StringValue<string_type, string_adaptor>("2.0")));
    XPathExpression<string_type, string_adaptor> lessThan3(new impl::LessThanOperator<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>("2.0"), new StringValue<string_type, string_adaptor>("3.0")));
    XPathExpression<string_type, string_adaptor> lessThan4(new impl::LessThanOperator<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>("-1"), new StringValue<string_type, string_adaptor>("1")));

    assertEquals(false, lessThan1.evaluateAsBool(dummy_));
    assertEquals(false, lessThan2.evaluateAsBool(dummy_));
    assertEquals(true, lessThan3.evaluateAsBool(dummy_));
    assertEquals(true, lessThan4.evaluateAsBool(dummy_));
  } // testLessThan3

  void testLessThanEquals1()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> lessThanEquals1(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(true)));
    XPathExpression<string_type, string_adaptor> lessThanEquals2(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(false)));
    XPathExpression<string_type, string_adaptor> lessThanEquals3(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(true), new BoolValue<string_type, string_adaptor>(false)));
    XPathExpression<string_type, string_adaptor> lessThanEquals4(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new BoolValue<string_type, string_adaptor>(false), new BoolValue<string_type, string_adaptor>(true)));

    assertEquals(true, lessThanEquals1.evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals2.evaluateAsBool(dummy_));
    assertEquals(false, lessThanEquals3.evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals4.evaluateAsBool(dummy_));
  } // testLessThanEquals1

  void testLessThanEquals2()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> lessThanEquals1(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(1.0), new NumericValue<string_type, string_adaptor>(1.0)));
    XPathExpression<string_type, string_adaptor> lessThanEquals2(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(3.0), new NumericValue<string_type, string_adaptor>(2.0)));
    XPathExpression<string_type, string_adaptor> lessThanEquals3(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(2.0), new NumericValue<string_type, string_adaptor>(3.0)));
    XPathExpression<string_type, string_adaptor> lessThanEquals4(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(-1), new NumericValue<string_type, string_adaptor>(1)));

    assertEquals(true, lessThanEquals1.evaluateAsBool(dummy_));
    assertEquals(false, lessThanEquals2.evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals3.evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals4.evaluateAsBool(dummy_));
  } // testLessThanEquals2

  void testLessThanEquals3()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> lessThanEquals1(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>("1.0"), new StringValue<string_type, string_adaptor>("1.0")));
    XPathExpression<string_type, string_adaptor> lessThanEquals2(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>("3.0"), new StringValue<string_type, string_adaptor>("2.0")));
    XPathExpression<string_type, string_adaptor> lessThanEquals3(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>("2.0"), new StringValue<string_type, string_adaptor>("3.0")));
    XPathExpression<string_type, string_adaptor> lessThanEquals4(new impl::LessThanEqualsOperator<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>("-1"), new StringValue<string_type, string_adaptor>("1")));

    assertEquals(true, lessThanEquals1.evaluateAsBool(dummy_));
    assertEquals(false, lessThanEquals2.evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals3.evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals4.evaluateAsBool(dummy_));
  } // testLessThanEquals3

private:
  Arabica::DOM::Node<string_type, string_adaptor> dummy_;
}; // class RelationalTest

template<class string_type, class string_adaptor>
TestSuite* RelationalTest_suite()
{
  TestSuite* tests = new TestSuite;

  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("test1", &RelationalTest<string_type, string_adaptor>::test1));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("test2", &RelationalTest<string_type, string_adaptor>::test2));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("test3", &RelationalTest<string_type, string_adaptor>::test3));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("test4", &RelationalTest<string_type, string_adaptor>::test4));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("test5", &RelationalTest<string_type, string_adaptor>::test5));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("test6", &RelationalTest<string_type, string_adaptor>::test6));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("test7", &RelationalTest<string_type, string_adaptor>::test7));

  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("testLessThan1", &RelationalTest<string_type, string_adaptor>::testLessThan1));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("testLessThan2", &RelationalTest<string_type, string_adaptor>::testLessThan2));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("testLessThan3", &RelationalTest<string_type, string_adaptor>::testLessThan3));

  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("testLessThanEquals1", &RelationalTest<string_type, string_adaptor>::testLessThanEquals1));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("testLessThanEquals2", &RelationalTest<string_type, string_adaptor>::testLessThanEquals2));
  tests->addTest(new TestCaller<RelationalTest<string_type, string_adaptor> >("testLessThanEquals3", &RelationalTest<string_type, string_adaptor>::testLessThanEquals3));

  return tests;
} // RelationalTest_suite

#endif
