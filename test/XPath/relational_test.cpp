#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224)
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
    XPathExpressionPtr equals1(new EqualsOperator(new NumericValue(1), new NumericValue(1)));
    XPathExpressionPtr equals2(new EqualsOperator(new NumericValue(1), new NumericValue(1)));

    assertEquals(true, equals1->evaluateAsBool(dummy_));
    assertEquals(true, equals2->evaluateAsBool(dummy_));
  } // test1

  void test2()
  {
    XPathExpressionPtr equals1(new EqualsOperator(new NumericValue(1), new NumericValue(2)));
    XPathExpressionPtr equals2(new EqualsOperator(new NumericValue(2), new NumericValue(1)));

    assertEquals(false, equals1->evaluateAsBool(dummy_));
    assertEquals(false, equals2->evaluateAsBool(dummy_));
  } // test2

  void test3()
  {
    XPathExpressionPtr equals1(new EqualsOperator(new NumericValue(1), new NumericValue(1)));

    assertEquals(true, equals1->evaluateAsBool(dummy_));
  } // test3

  void test4()
  {
    XPathExpression* p1 = new StringValue("charlie");
    XPathExpression* p2 = new StringValue("charlie");

    XPathExpressionPtr equals1(new EqualsOperator(p1, p2));

    assertEquals(true, equals1->evaluateAsBool(dummy_));
  } // test4

  void test5()
  {
    XPathExpression* p1 = new StringValue("trousers");
    XPathExpression* p2 = new StringValue("charlie");

    XPathExpressionPtr equals1(new EqualsOperator(p1, p2));

    assertEquals(false, equals1->evaluateAsBool(dummy_));
  } // test5

  void test6()
  {
    XPathExpressionPtr equals1(new EqualsOperator(new BoolValue(true), new BoolValue(true)));
    XPathExpressionPtr equals2(new EqualsOperator(new BoolValue(false), new BoolValue(false)));

    assertEquals(true, equals1->evaluateAsBool(dummy_));
    assertEquals(true, equals2->evaluateAsBool(dummy_));
  } // test6

  void test7()
  {
    XPathExpressionPtr equals1(new EqualsOperator(new BoolValue(true), new BoolValue(false)));
    XPathExpressionPtr equals2(new EqualsOperator(new BoolValue(false), new BoolValue(true)));

    assertEquals(false, equals1->evaluateAsBool(dummy_));
    assertEquals(false, equals2->evaluateAsBool(dummy_));
  } // test7

  void testLessThan1()
  {
    XPathExpressionPtr lessThan1(new LessThanOperator(new BoolValue(true), new BoolValue(true)));
    XPathExpressionPtr lessThan2(new LessThanOperator(new BoolValue(false), new BoolValue(false)));
    XPathExpressionPtr lessThan3(new LessThanOperator(new BoolValue(true), new BoolValue(false)));
    XPathExpressionPtr lessThan4(new LessThanOperator(new BoolValue(false), new BoolValue(true)));

    assertEquals(false, lessThan1->evaluateAsBool(dummy_));
    assertEquals(false, lessThan2->evaluateAsBool(dummy_));
    assertEquals(false, lessThan3->evaluateAsBool(dummy_));
    assertEquals(true, lessThan4->evaluateAsBool(dummy_));
  } // testLessThan1

  void testLessThan2()
  {
    XPathExpressionPtr lessThan1(new LessThanOperator(new NumericValue(1.0), new NumericValue(1.0)));
    XPathExpressionPtr lessThan2(new LessThanOperator(new NumericValue(3.0), new NumericValue(2.0)));
    XPathExpressionPtr lessThan3(new LessThanOperator(new NumericValue(2.0), new NumericValue(3.0)));
    XPathExpressionPtr lessThan4(new LessThanOperator(new NumericValue(-1), new NumericValue(1)));

    assertEquals(false, lessThan1->evaluateAsBool(dummy_));
    assertEquals(false, lessThan2->evaluateAsBool(dummy_));
    assertEquals(true, lessThan3->evaluateAsBool(dummy_));
    assertEquals(true, lessThan4->evaluateAsBool(dummy_));
  } // testLessThan2

  void testLessThan3()
  {
    XPathExpressionPtr lessThan1(new LessThanOperator(new StringValue("1.0"), new StringValue("1.0")));
    XPathExpressionPtr lessThan2(new LessThanOperator(new StringValue("3.0"), new StringValue("2.0")));
    XPathExpressionPtr lessThan3(new LessThanOperator(new StringValue("2.0"), new StringValue("3.0")));
    XPathExpressionPtr lessThan4(new LessThanOperator(new StringValue("-1"), new StringValue("1")));

    assertEquals(false, lessThan1->evaluateAsBool(dummy_));
    assertEquals(false, lessThan2->evaluateAsBool(dummy_));
    assertEquals(true, lessThan3->evaluateAsBool(dummy_));
    assertEquals(true, lessThan4->evaluateAsBool(dummy_));
  } // testLessThan3

  void testLessThanEquals1()
  {
    XPathExpressionPtr lessThanEquals1(new LessThanEqualsOperator(new BoolValue(true), new BoolValue(true)));
    XPathExpressionPtr lessThanEquals2(new LessThanEqualsOperator(new BoolValue(false), new BoolValue(false)));
    XPathExpressionPtr lessThanEquals3(new LessThanEqualsOperator(new BoolValue(true), new BoolValue(false)));
    XPathExpressionPtr lessThanEquals4(new LessThanEqualsOperator(new BoolValue(false), new BoolValue(true)));

    assertEquals(true, lessThanEquals1->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals2->evaluateAsBool(dummy_));
    assertEquals(false, lessThanEquals3->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals4->evaluateAsBool(dummy_));
  } // testLessThanEquals1

  void testLessThanEquals2()
  {
    XPathExpressionPtr lessThanEquals1(new LessThanEqualsOperator(new NumericValue(1.0), new NumericValue(1.0)));
    XPathExpressionPtr lessThanEquals2(new LessThanEqualsOperator(new NumericValue(3.0), new NumericValue(2.0)));
    XPathExpressionPtr lessThanEquals3(new LessThanEqualsOperator(new NumericValue(2.0), new NumericValue(3.0)));
    XPathExpressionPtr lessThanEquals4(new LessThanEqualsOperator(new NumericValue(-1), new NumericValue(1)));

    assertEquals(true, lessThanEquals1->evaluateAsBool(dummy_));
    assertEquals(false, lessThanEquals2->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals3->evaluateAsBool(dummy_));
    assertEquals(true, lessThanEquals4->evaluateAsBool(dummy_));
  } // testLessThanEquals2

  void testLessThanEquals3()
  {
    XPathExpressionPtr lessThanEquals1(new LessThanEqualsOperator(new StringValue("1.0"), new StringValue("1.0")));
    XPathExpressionPtr lessThanEquals2(new LessThanEqualsOperator(new StringValue("3.0"), new StringValue("2.0")));
    XPathExpressionPtr lessThanEquals3(new LessThanEqualsOperator(new StringValue("2.0"), new StringValue("3.0")));
    XPathExpressionPtr lessThanEquals4(new LessThanEqualsOperator(new StringValue("-1"), new StringValue("1")));

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
