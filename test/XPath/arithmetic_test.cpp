#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>

using namespace Arabica::XPath;

class ArithmeticTest : public TestCase
{
public:
  ArithmeticTest(const std::string& name) : TestCase(name)
  {
  } // ArithmeticTest

  void setUp()
  {
  } // setUp

  void test1()
  {
    XPathExpression* p1 = new NumericValue(1);
    XPathExpression* p2 = new NumericValue(2);

    XPathExpressionPtr add(new PlusOperator(p1, p2));
    assertEquals(1, add.use_count());

    add->evaluate(dummy_);

    assertEquals(3.0, add->evaluateAsNumber(dummy_), 0.0);

    assertEquals(1, add.use_count());
  } // test1

  void test2()
  {
    XPathExpression* p1 = new NumericValue(1);
    XPathExpression* p2 = new NumericValue(2);

    XPathExpressionPtr minus(new MinusOperator(p1, p2));

    assertEquals(-1.0, minus->evaluateAsNumber(dummy_), 0.0);
  } // test2

  void test3()
  {
    XPathExpression* p1 = new NumericValue(3);
    XPathExpression* p2 = new NumericValue(2);

    XPathExpressionPtr mult(new MultiplyOperator(p1, p2));

    assertEquals(6, mult->evaluateAsNumber(dummy_), 0.0);
  } // test3

  void test4()
  {
    XPathExpression* mult = new MultiplyOperator(new NumericValue(4), new NumericValue(2));

    XPathExpressionPtr minus(new MinusOperator(mult, new NumericValue(2)));

    assertEquals(8, mult->evaluateAsNumber(dummy_), 0.0);
    assertEquals(6, minus->evaluateAsNumber(dummy_), 0.0);
  } // test4

  void test5()
  {
    XPathExpression* p1 = new NumericValue(12);
    XPathExpression* p2 = new NumericValue(2);

    XPathExpressionPtr div(new DivideOperator(p1, p2));

    assertEquals(6, div->evaluateAsNumber(dummy_), 0.0);
  } // test5

  void test6()
  {
    XPathExpression* p1 = new NumericValue(12);
    XPathExpression* p2 = new NumericValue(2);

    XPathExpressionPtr mod(new ModOperator(p1, p2));

    assertEquals(0, mod->evaluateAsNumber(dummy_), 0.0);
  } // test6

  void test7()
  {
    XPathExpression* p1 = new NumericValue(11);
    XPathExpression* p2 = new NumericValue(2);

    XPathExpressionPtr div(new DivideOperator(p1, p2));

    assertEquals(5.5, div->evaluateAsNumber(dummy_), 0.0);
  } // test7

  void test8()
  {
    XPathExpression* p1 = new NumericValue(11);
    XPathExpression* p2 = new NumericValue(4);

    XPathExpressionPtr mod(new ModOperator(p1, p2));

    assertEquals(3, mod->evaluateAsNumber(dummy_), 0.0);
  } // test8

  void test9()
  {
    XPathExpression* p1 = new NumericValue(5);
    XPathExpression* p2 = new NumericValue(2);

    XPathExpressionPtr mod(new ModOperator(p1, p2));

    assertEquals(1.0, mod->evaluateAsNumber(dummy_), 0.0);
  } // test9

  void test10()
  {
    XPathExpression* p1 = new NumericValue(5);
    XPathExpression* p2 = new NumericValue(-2);

    XPathExpressionPtr mod(new ModOperator(p1, p2));

    assertEquals(1.00, mod->evaluateAsNumber(dummy_), 0.0);
  } // test10

  void test11()
  {
    XPathExpression* p1 = new NumericValue(-5);
    XPathExpression* p2 = new NumericValue(2);

    XPathExpressionPtr mod(new ModOperator(p1, p2));

    assertEquals(-1.0, mod->evaluateAsNumber(dummy_), 0.0);
  } // test11

  void test12()
  {
    XPathExpression* p1 = new NumericValue(-5);
    XPathExpression* p2 = new NumericValue(-2);

    XPathExpressionPtr mod(new ModOperator(p1, p2));

    assertEquals(-1.0, mod->evaluateAsNumber(dummy_), 0.0);
  } // test12

  void test13()
  {
    XPathExpression* p1 = new NumericValue(5);
    XPathExpressionPtr p2(new UnaryNegative(p1));

    assertEquals(-5.0, p2->evaluateAsNumber(dummy_), 0.0);
  } // test13

  void test14()
  {
    XPathExpression* p1 = new NumericValue(-5);
    XPathExpressionPtr p2(new UnaryNegative(p1));

    assertEquals(5.0, p2->evaluateAsNumber(dummy_), 0.0);
  } // test14

private:
  DOM::Node<std::string> dummy_;
}; // ArithmeticTest

TestSuite* ArithmeticTest_suite()
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test1", &ArithmeticTest::test1));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test2", &ArithmeticTest::test2));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test3", &ArithmeticTest::test3));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test4", &ArithmeticTest::test4));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test5", &ArithmeticTest::test5));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test6", &ArithmeticTest::test6));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test7", &ArithmeticTest::test7));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test8", &ArithmeticTest::test8));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test9", &ArithmeticTest::test9));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test10", &ArithmeticTest::test10));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test11", &ArithmeticTest::test11));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test12", &ArithmeticTest::test12));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test13", &ArithmeticTest::test13));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest>("test14", &ArithmeticTest::test14));

  return suiteOfTests;
} // ArithmeticTest_suite
