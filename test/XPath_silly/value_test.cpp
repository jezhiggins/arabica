#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include "value_test.hpp"
#include "../silly_string/silly_string.hpp"

using namespace Arabica::XPath;
template<> class Arabica::default_string_adaptor<silly_string> : public silly_string_adaptor { };

class ValueTest : public TestCase
{
private:
  DOM::Node<silly_string> dummy_;
  typedef silly_string_adaptor SA;

public:
  ValueTest(std::string name) : TestCase(name)
  {
  } // ValueTest

  void setUp()
  {
  } // setUp

  void test1()
  {
    XPathExpressionPtr<silly_string> b(new BoolValue<silly_string, Arabica::default_string_adaptor<silly_string> >(true));
    assertEquals(true, b->evaluateAsBool(dummy_));
    assertEquals(1.0, b->evaluateAsNumber(dummy_), 0.0);
    assertTrue(SA::construct_from_utf8("true") == b->evaluateAsString(dummy_));
  }

  void test2()
  {
    XPathExpressionPtr<silly_string> b2(new BoolValue<silly_string, Arabica::default_string_adaptor<silly_string> >(false));
    assertEquals(false, b2->evaluateAsBool(dummy_));
    assertEquals(0.0, b2->evaluateAsNumber(dummy_), 0.0);
    assertTrue(SA::construct_from_utf8("false") == b2->evaluateAsString(dummy_));
  } // test2

  void test3()
  {
    XPathExpressionPtr<silly_string> n(new NumericValue<silly_string, Arabica::default_string_adaptor<silly_string> >(99.5));
    assertEquals(true, n->evaluateAsBool(dummy_));
    assertEquals(99.5, n->evaluateAsNumber(dummy_), 0.0);
    assertTrue(SA::construct_from_utf8("99.5") == n->evaluateAsString(dummy_));
  }

  void test4()
  {
    XPathExpressionPtr<silly_string> n(new NumericValue<silly_string, Arabica::default_string_adaptor<silly_string> >(0.0));
    assertEquals(false, n->evaluateAsBool(dummy_));
    assertEquals(0, n->evaluateAsNumber(dummy_), 0);
    assertTrue(SA::construct_from_utf8("0") == n->evaluateAsString(dummy_));
  }

  void test5()
  {
    XPathExpressionPtr<silly_string> s(new StringValue<silly_string, Arabica::default_string_adaptor<silly_string> >("hello"));
    assertEquals(true, s->evaluateAsBool(dummy_));
    assertTrue(SA::construct_from_utf8("hello") == s->evaluateAsString(dummy_));
  } // test5

  void test6()
  {
    XPathExpressionPtr<silly_string> s(new StringValue<silly_string, Arabica::default_string_adaptor<silly_string> >(""));
    assertEquals(false, s->evaluateAsBool(dummy_));
  }

  void test7()
  {
    XPathExpressionPtr<silly_string> s(new StringValue<silly_string, Arabica::default_string_adaptor<silly_string> >("100"));
    assertEquals(true, s->evaluateAsBool(dummy_));
    assertEquals(100.0, s->evaluateAsNumber(dummy_), 0.0);
    assertTrue(SA::construct_from_utf8("100") == s->evaluateAsString(dummy_));
  } // test7

  void test8()
  {
    XPathExpressionPtr<silly_string> s(new StringValue<silly_string, Arabica::default_string_adaptor<silly_string> >("0"));
    assertEquals(true, s->evaluateAsBool(dummy_));
    assertEquals(0.0, s->evaluateAsNumber(dummy_), 0.0);
    assertTrue(SA::construct_from_utf8("0") == s->evaluateAsString(dummy_));
  } // test8

  void test9()
  {
    XPathExpressionPtr<silly_string> bt(new BoolValue<silly_string, Arabica::default_string_adaptor<silly_string> >(true));
    XPathExpressionPtr<silly_string> st(new StringValue<silly_string, Arabica::default_string_adaptor<silly_string> >("true"));
    XPathExpressionPtr<silly_string> bf(new BoolValue<silly_string, Arabica::default_string_adaptor<silly_string> >(false));
    XPathExpressionPtr<silly_string> sf(new StringValue<silly_string, Arabica::default_string_adaptor<silly_string> >(""));

    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(bt->evaluate(dummy_), (st->evaluate(dummy_)))));
    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(st->evaluate(dummy_), (bt->evaluate(dummy_)))));

    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(sf->evaluate(dummy_), (bf->evaluate(dummy_)))));
    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(bf->evaluate(dummy_), (sf->evaluate(dummy_)))));

    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(bt->evaluate(dummy_), (bt->evaluate(dummy_)))));
    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(bf->evaluate(dummy_), (bf->evaluate(dummy_)))));
    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(st->evaluate(dummy_), (st->evaluate(dummy_)))));
    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(sf->evaluate(dummy_), (sf->evaluate(dummy_)))));
  } // test9

  void test10()
  {
    XPathExpressionPtr<silly_string> bt(new BoolValue<silly_string, Arabica::default_string_adaptor<silly_string> >(true));
    XPathExpressionPtr<silly_string> nt(new NumericValue<silly_string, Arabica::default_string_adaptor<silly_string> >(1.0));
    XPathExpressionPtr<silly_string> bf(new BoolValue<silly_string, Arabica::default_string_adaptor<silly_string> >(false));
    XPathExpressionPtr<silly_string> nf(new NumericValue<silly_string, Arabica::default_string_adaptor<silly_string> >(0.0));

    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(bt->evaluate(dummy_), (nt->evaluate(dummy_)))));
    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(nt->evaluate(dummy_), (bt->evaluate(dummy_)))));

    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(bf->evaluate(dummy_), (nf->evaluate(dummy_)))));
    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(nf->evaluate(dummy_), (bf->evaluate(dummy_)))));
  } // test10

  void test11()
  {
    XPathExpressionPtr<silly_string> nt(new NumericValue<silly_string, Arabica::default_string_adaptor<silly_string> >(1.0));
    XPathValuePtr<silly_string> ns = nt->evaluate(dummy_);

    assertTrue((impl::areEqual<silly_string, Arabica::default_string_adaptor<silly_string> >(ns, (nt->evaluate(dummy_)))));
  } // test11
}; // ValueTest

TestSuite* ValueTest_suite()
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ValueTest>("test1", &ValueTest::test1));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test2", &ValueTest::test2));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test3", &ValueTest::test3));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test4", &ValueTest::test4));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test5", &ValueTest::test5));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test6", &ValueTest::test6));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test7", &ValueTest::test7));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test8", &ValueTest::test8));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test9", &ValueTest::test9));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test10", &ValueTest::test10));
  suiteOfTests->addTest(new TestCaller<ValueTest>("test11", &ValueTest::test11));

  return suiteOfTests;
} // ValueTest_suite
