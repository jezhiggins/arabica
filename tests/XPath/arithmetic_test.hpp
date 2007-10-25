#ifndef XPATHIC_ARITHMETIC_TEST_H
#define XPATHIC_ARITHMETIC_TEST_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>

template<class string_type, class string_adaptor>
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
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(1);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(2);

    XPathExpression<string_type, string_adaptor> add(new impl::PlusOperator<string_type, string_adaptor>(p1, p2));

    add.evaluate(dummy_);
    assertEquals(3.0, add.evaluateAsNumber(dummy_), 0.0);
  } // test1

  void test2()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(1);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(2);

    XPathExpression<string_type, string_adaptor> minus(new impl::MinusOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(-1.0, minus.evaluateAsNumber(dummy_), 0.0);
  } // test2

  void test3()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(3);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(2);

    XPathExpression<string_type, string_adaptor> mult(new impl::MultiplyOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(6, mult.evaluateAsNumber(dummy_), 0.0);
  } // test3

  void test4()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* mult = new impl::MultiplyOperator<string_type, string_adaptor>(new NumericValue<string_type, string_adaptor>(4), new NumericValue<string_type, string_adaptor>(2));

    XPathExpression<string_type, string_adaptor> minus(new impl::MinusOperator<string_type, string_adaptor>(mult, new NumericValue<string_type, string_adaptor>(2)));

    assertEquals(8, mult->evaluateAsNumber(dummy_), 0.0);
    assertEquals(6, minus.evaluateAsNumber(dummy_), 0.0);
  } // test4

  void test5()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(12);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(2);

    XPathExpression<string_type, string_adaptor> div(new impl::DivideOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(6, div.evaluateAsNumber(dummy_), 0.0);
  } // test5

  void test6()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(12);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(2);

    XPathExpression<string_type, string_adaptor> mod(new impl::ModOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(0, mod.evaluateAsNumber(dummy_), 0.0);
  } // test6

  void test7()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(11);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(2);

    XPathExpression<string_type, string_adaptor> div(new impl::DivideOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(5.5, div.evaluateAsNumber(dummy_), 0.0);
  } // test7

  void test8()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(11);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(4);

    XPathExpression<string_type, string_adaptor> mod(new impl::ModOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(3, mod.evaluateAsNumber(dummy_), 0.0);
  } // test8

  void test9()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(5);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(2);

    XPathExpression<string_type, string_adaptor> mod(new impl::ModOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(1.0, mod.evaluateAsNumber(dummy_), 0.0);
  } // test9

  void test10()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(5);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(-2);

    XPathExpression<string_type, string_adaptor> mod(new impl::ModOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(1.00, mod.evaluateAsNumber(dummy_), 0.0);
  } // test10

  void test11()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(-5);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(2);

    XPathExpression<string_type, string_adaptor> mod(new impl::ModOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(-1.0, mod.evaluateAsNumber(dummy_), 0.0);
  } // test11

  void test12()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(-5);
    XPathExpression_impl<string_type, string_adaptor>* p2 = new NumericValue<string_type, string_adaptor>(-2);

    XPathExpression<string_type, string_adaptor> mod(new impl::ModOperator<string_type, string_adaptor>(p1, p2));

    assertEquals(-1.0, mod.evaluateAsNumber(dummy_), 0.0);
  } // test12

  void test13()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(5);
    XPathExpression<string_type, string_adaptor> p2(new impl::UnaryNegative<string_type, string_adaptor>(p1));

    assertEquals(-5.0, p2.evaluateAsNumber(dummy_), 0.0);
  } // test13

  void test14()
  {
    using namespace Arabica::XPath;
    XPathExpression_impl<string_type, string_adaptor>* p1 = new NumericValue<string_type, string_adaptor>(-5);
    XPathExpression<string_type, string_adaptor> p2(new impl::UnaryNegative<string_type, string_adaptor>(p1));

    assertEquals(5.0, p2.evaluateAsNumber(dummy_), 0.0);
  } // test14

private:
  Arabica::DOM::Node<string_type, string_adaptor> dummy_;
}; // ArithmeticTest

template<class string_type, class string_adaptor>
TestSuite* ArithmeticTest_suite()
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test1", &ArithmeticTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test2", &ArithmeticTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test3", &ArithmeticTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test4", &ArithmeticTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test5", &ArithmeticTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test6", &ArithmeticTest<string_type, string_adaptor>::test6));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test7", &ArithmeticTest<string_type, string_adaptor>::test7));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test8", &ArithmeticTest<string_type, string_adaptor>::test8));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test9", &ArithmeticTest<string_type, string_adaptor>::test9));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test10", &ArithmeticTest<string_type, string_adaptor>::test10));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test11", &ArithmeticTest<string_type, string_adaptor>::test11));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test12", &ArithmeticTest<string_type, string_adaptor>::test12));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test13", &ArithmeticTest<string_type, string_adaptor>::test13));
  suiteOfTests->addTest(new TestCaller<ArithmeticTest<string_type, string_adaptor> >("test14", &ArithmeticTest<string_type, string_adaptor>::test14));

  return suiteOfTests;
} // ArithmeticTest_suite

#endif

