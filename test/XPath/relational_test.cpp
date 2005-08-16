#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>

using namespace Arabica::XPath;

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
    XPathExpressionPtr<std::string> equals1(new EqualsOperator(new NumericValue(1), new NumericValue(1)));
    XPathExpressionPtr<std::string> equals2(new EqualsOperator(new NumericValue(1), new NumericValue(1)));

    assertEquals(true, equals1->evaluateAsBool(dummy_));
    assertEquals(true, equals2->evaluateAsBool(dummy_));
  } // test1

  void test2()
  {
    XPathExpressionPtr<std::string> equals1(new EqualsOperator(new NumericValue(1), new NumericValue(2)));
    XPathExpressionPtr<std::string> equals2(new EqualsOperator(new NumericValue(2), new NumericValue(1)));

    assertEquals(false, equals1->evaluateAsBool(dummy_));
    assertEquals(false, equals2->evaluateAsBool(dummy_));
  } // test2

  void test3()
  {
    XPathExpressionPtr<std::string> equals1(new EqualsOperator(new NumericValue(1), new NumericValue(1)));

    assertEquals(true, equals1->evaluateAsBool(dummy_));
  } // test3

  void test4()
  {
    XPathExpression<std::string>* p1 = new StringValue("charlie");
    XPathExpression<std::string>* p2 = new StringValue("charlie");

    XPathExpressionPtr<std::string> equals1(new EqualsOperator(p1, p2));

    assertEquals(true, equals1->evaluateAsBool(dummy_));
  } // test4

  void test5()
  {
    XPathExpression<std::string>* p1 = new StringValue("trousers");
    XPathExpression<std::string>* p2 = new StringValue("charlie");

    XPathExpressionPtr<std::string> equals1(new EqualsOperator(p1, p2));

    assertEquals(false, equals1->evaluateAsBool(dummy_));
  } // test5

  void test6()
  {
    XPathExpressionPtr<std::string> equals1(new EqualsOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));
    XPathExpressionPtr<std::string> equals2(new EqualsOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));

    assertEquals(true, equals1->evaluateAsBool(dummy_));
    assertEquals(true, equals2->evaluateAsBool(dummy_));
  } // test6

  void test7()
  {
    XPathExpressionPtr<std::string> equals1(new EqualsOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    XPathExpressionPtr<std::string> equals2(new EqualsOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));

    assertEquals(false, equals1->evaluateAsBool(dummy_));
    assertEquals(false, equals2->evaluateAsBool(dummy_));
  } // test7

  void testLessThan1()
  {
    XPathExpressionPtr<std::string> lessThan1(new LessThanOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));
    XPathExpressionPtr<std::string> lessThan2(new LessThanOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    XPathExpressionPtr<std::string> lessThan3(new LessThanOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    XPathExpressionPtr<std::string> lessThan4(new LessThanOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));

    assertEquals(false, lessThan1->evaluateAsBool(dummy_));
    assertEquals(false, lessThan2->evaluateAsBool(dummy_));
    assertEquals(false, lessThan3->evaluateAsBool(dummy_));
    assertEquals(true, lessThan4->evaluateAsBool(dummy_));
  } // testLessThan1

  void testLessThan2()
  {
    XPathExpressionPtr<std::string> lessThan1(new LessThanOperator(new NumericValue(1.0), new NumericValue(1.0)));
    XPathExpressionPtr<std::string> lessThan2(new LessThanOperator(new NumericValue(3.0), new NumericValue(2.0)));
    XPathExpressionPtr<std::string> lessThan3(new LessThanOperator(new NumericValue(2.0), new NumericValue(3.0)));
    XPathExpressionPtr<std::string> lessThan4(new LessThanOperator(new NumericValue(-1), new NumericValue(1)));

    assertEquals(false, lessThan1->evaluateAsBool(dummy_));
    assertEquals(false, lessThan2->evaluateAsBool(dummy_));
    assertEquals(true, lessThan3->evaluateAsBool(dummy_));
    assertEquals(true, lessThan4->evaluateAsBool(dummy_));
  } // testLessThan2

  void testLessThan3()
  {
    XPathExpressionPtr<std::string> lessThan1(new LessThanOperator(new StringValue("1.0"), new StringValue("1.0")));
    XPathExpressionPtr<std::string> lessThan2(new LessThanOperator(new StringValue("3.0"), new StringValue("2.0")));
    XPathExpressionPtr<std::string> lessThan3(new LessThanOperator(new StringValue("2.0"), new StringValue("3.0")));
    XPathExpressionPtr<std::string> lessThan4(new LessThanOperator(new StringValue("-1"), new StringValue("1")));

    assertEquals(false, lessThan1->evaluateAsBool(dummy_));
    assertEquals(false, lessThan2->evaluateAsBool(dummy_));
    assertEquals(true, lessThan3->evaluateAsBool(dummy_));
    assertEquals(true, lessThan4->evaluateAsBool(dummy_));
  } // testLessThan3

  void testLessThanEquals1()
  {
    XPathExpressionPtr<std::string> lessThanEquals1(new LessThanEqualsOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));
    XPathExpressionPtr<std::string> lessThanEquals2(new LessThanEqualsOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    XPathExpressionPtr<std::string> lessThanEquals3(new LessThanEqualsOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false)));
    XPathExpressionPtr<std::string> lessThanEquals4(new LessThanEqualsOperator(new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false), new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true)));

    assertEquals(true, lessThanEquals1->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals2->evaluateAsBool(dummy_));
    assertEquals(false, lessThanEquals3->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals4->evaluateAsBool(dummy_));
  } // testLessThanEquals1

  void testLessThanEquals2()
  {
    XPathExpressionPtr<std::string> lessThanEquals1(new LessThanEqualsOperator(new NumericValue(1.0), new NumericValue(1.0)));
    XPathExpressionPtr<std::string> lessThanEquals2(new LessThanEqualsOperator(new NumericValue(3.0), new NumericValue(2.0)));
    XPathExpressionPtr<std::string> lessThanEquals3(new LessThanEqualsOperator(new NumericValue(2.0), new NumericValue(3.0)));
    XPathExpressionPtr<std::string> lessThanEquals4(new LessThanEqualsOperator(new NumericValue(-1), new NumericValue(1)));

    assertEquals(true, lessThanEquals1->evaluateAsBool(dummy_));
    assertEquals(false, lessThanEquals2->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals3->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals4->evaluateAsBool(dummy_));
  } // testLessThanEquals2

  void testLessThanEquals3()
  {
    XPathExpressionPtr<std::string> lessThanEquals1(new LessThanEqualsOperator(new StringValue("1.0"), new StringValue("1.0")));
    XPathExpressionPtr<std::string> lessThanEquals2(new LessThanEqualsOperator(new StringValue("3.0"), new StringValue("2.0")));
    XPathExpressionPtr<std::string> lessThanEquals3(new LessThanEqualsOperator(new StringValue("2.0"), new StringValue("3.0")));
    XPathExpressionPtr<std::string> lessThanEquals4(new LessThanEqualsOperator(new StringValue("-1"), new StringValue("1")));

    assertEquals(true, lessThanEquals1->evaluateAsBool(dummy_));
    assertEquals(false, lessThanEquals2->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals3->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals4->evaluateAsBool(dummy_));
  } // testLessThanEquals3

private:
  DOM::Node<std::string> dummy_;
}; // class RelationalTest

TestSuite* RelationalTest_suite()
{
  TestSuite* tests = new TestSuite;

  tests->addTest(new TestCaller<RelationalTest>("test1", &RelationalTest::test1));
  tests->addTest(new TestCaller<RelationalTest>("test2", &RelationalTest::test2));
  tests->addTest(new TestCaller<RelationalTest>("test3", &RelationalTest::test3));
  tests->addTest(new TestCaller<RelationalTest>("test4", &RelationalTest::test4));
  tests->addTest(new TestCaller<RelationalTest>("test5", &RelationalTest::test5));
  tests->addTest(new TestCaller<RelationalTest>("test6", &RelationalTest::test6));
  tests->addTest(new TestCaller<RelationalTest>("test7", &RelationalTest::test7));

  tests->addTest(new TestCaller<RelationalTest>("testLessThan1", &RelationalTest::testLessThan1));
  tests->addTest(new TestCaller<RelationalTest>("testLessThan2", &RelationalTest::testLessThan2));
  tests->addTest(new TestCaller<RelationalTest>("testLessThan3", &RelationalTest::testLessThan3));

  tests->addTest(new TestCaller<RelationalTest>("testLessThanEquals1", &RelationalTest::testLessThanEquals1));
  tests->addTest(new TestCaller<RelationalTest>("testLessThanEquals2", &RelationalTest::testLessThanEquals2));
  tests->addTest(new TestCaller<RelationalTest>("testLessThanEquals3", &RelationalTest::testLessThanEquals3));

  return tests;
} // RelationalTest_suite
