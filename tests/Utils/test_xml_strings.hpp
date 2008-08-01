#ifndef UTILS_XML_STRINGS_HPP
#define UTILS_XML_STRINGS_HPP

#include <XML/strings.hpp>

using namespace Arabica::XML;

class NCNameTest : public TestCase
{
public:
  NCNameTest(std::string name) : 
    TestCase(name)
  {
  } // NCNameTest
  
  void test1()
  {
    assertTrue(is_ncname("woo"));
  } // test1
  
  void test2()
  {
    assertTrue(is_ncname("WOO"));
  } // test2
  
  void test3()
  {
    assertFalse(is_ncname("???"));
  } // test3
  
  void test4()
  {
    assertTrue(is_ncname("a_b"));
  } // test4

  void test5()
  {
    assertFalse(is_ncname("a:b"));
  } // test5

  void test6()
  {
    assertFalse(is_ncname("xsl:foo"));
  } // test6
}; // class NCNameTest

TestSuite* NCNameTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<NCNameTest>("test1", &NCNameTest::test1));
  suiteOfTests->addTest(new TestCaller<NCNameTest>("test2", &NCNameTest::test2));
  suiteOfTests->addTest(new TestCaller<NCNameTest>("test3", &NCNameTest::test3));
  suiteOfTests->addTest(new TestCaller<NCNameTest>("test4", &NCNameTest::test4));
  suiteOfTests->addTest(new TestCaller<NCNameTest>("test5", &NCNameTest::test5));
  suiteOfTests->addTest(new TestCaller<NCNameTest>("test6", &NCNameTest::test6));

  return suiteOfTests;
} // NCNameTest_suite

class QNameTest : public TestCase
{
public:
  QNameTest(std::string name) : 
    TestCase(name)
  {
  } // QNameTest
  
  void test1()
  {
    assertTrue(is_qname("woo"));
  } // test1
  
  void test2()
  {
    assertTrue(is_qname("WOO"));
  } // test2
  
  void test3()
  {
    assertFalse(is_qname("???"));
  } // test3
  
  void test4()
  {
    assertTrue(is_qname("a_b"));
  } // test4

  void test5()
  {
    assertTrue(is_qname("a:b"));
  } // test5

  void test6()
  {
    assertTrue(is_qname("xsl:foo"));
  } // test6

  void test7()
  {
    assertFalse(is_qname(":foo"));
  } // test7

  void test8()
  {
    assertFalse(is_qname("foo:"));
  } // test7

  void test9()
  {
    assertFalse(is_qname("xsl::foo"));
  } // test7

  void test10()
  {
    assertFalse(is_qname("xsl:foo:"));
  } // test7

  void test11()
  {
    assertFalse(is_qname("$rr"));
  } // test11

  void test12()
  {
    assertFalse(is_qname("root/child"));
  } // test12
}; // class QNameTest

TestSuite* QNameTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<QNameTest>("test1", &QNameTest::test1));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test2", &QNameTest::test2));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test3", &QNameTest::test3));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test4", &QNameTest::test4));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test5", &QNameTest::test5));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test6", &QNameTest::test6));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test7", &QNameTest::test7));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test8", &QNameTest::test8));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test9", &QNameTest::test9));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test10", &QNameTest::test10));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test11", &QNameTest::test11));
  suiteOfTests->addTest(new TestCaller<QNameTest>("test12", &QNameTest::test12));

  return suiteOfTests;
} // QNameTest_suite

TestSuite* XMLStringTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(NCNameTest_suite());
  suiteOfTests->addTest(QNameTest_suite());

  return suiteOfTests;
} // XMLStringTest_suite

#endif
