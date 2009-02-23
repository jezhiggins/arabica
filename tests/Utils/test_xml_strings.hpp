#ifndef UTILS_XML_STRINGS_HPP
#define UTILS_XML_STRINGS_HPP

#include <XML/strings.hpp>

using namespace Arabica::XML;

template<class string_type, class string_adaptor>
class NCNameTest : public TestCase
{
  typedef string_adaptor SA;

public:
  NCNameTest(std::string name) : 
    TestCase(name)
  {
  } // NCNameTest
  
  void test1()
  {
    assertTrue(is_ncname<SA>(SA::construct_from_utf8("woo")));
  } // test1
  
  void test2()
  {
    assertTrue(is_ncname<SA>(SA::construct_from_utf8("WOO")));
  } // test2
  
  void test3()
  {
    assertFalse(is_ncname<SA>(SA::construct_from_utf8("???")));
  } // test3
  
  void test4()
  {
    assertTrue(is_ncname<SA>(SA::construct_from_utf8("a_b")));
  } // test4

  void test5()
  {
    assertFalse(is_ncname<SA>(SA::construct_from_utf8("a:b")));
  } // test5

  void test6()
  {
    assertFalse(is_ncname<SA>(SA::construct_from_utf8("xsl:foo")));
  } // test6
}; // class NCNameTest

template<class string_type, class string_adaptor>
TestSuite* NCNameTest_suite()
{
  typedef NCNameTest<string_type, string_adaptor> NCNT;

  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<NCNT>("test1", &NCNT::test1));
  suiteOfTests->addTest(new TestCaller<NCNT>("test2", &NCNT::test2));
  suiteOfTests->addTest(new TestCaller<NCNT>("test3", &NCNT::test3));
  suiteOfTests->addTest(new TestCaller<NCNT>("test4", &NCNT::test4));
  suiteOfTests->addTest(new TestCaller<NCNT>("test5", &NCNT::test5));
  suiteOfTests->addTest(new TestCaller<NCNT>("test6", &NCNT::test6));

  return suiteOfTests;
} // NCNT_suite

template<typename string_type, typename string_adaptor>
class QNameTest : public TestCase
{
  typedef string_adaptor SA;

public:
  QNameTest(std::string name) : 
    TestCase(name)
  {
  } // QNameTest
  
  void test1()
  {
    assertTrue(is_qname<SA>(SA::construct_from_utf8("woo")));
  } // test1
  
  void test2()
  {
    assertTrue(is_qname<SA>(SA::construct_from_utf8("WOO")));
  } // test2
  
  void test3()
  {
    assertFalse(is_qname<SA>(SA::construct_from_utf8("???")));
  } // test3
  
  void test4()
  {
    assertTrue(is_qname<SA>(SA::construct_from_utf8("a_b")));
  } // test4

  void test5()
  {
    assertTrue(is_qname<SA>(SA::construct_from_utf8("a:b")));
  } // test5

  void test6()
  {
    assertTrue(is_qname<SA>(SA::construct_from_utf8("xsl:foo")));
  } // test6

  void test7()
  {
    assertFalse(is_qname<SA>(SA::construct_from_utf8(":foo")));
  } // test7

  void test8()
  {
    assertFalse(is_qname<SA>(SA::construct_from_utf8("foo:")));
  } // test7

  void test9()
  {
    assertFalse(is_qname<SA>(SA::construct_from_utf8("xsl::foo")));
  } // test7

  void test10()
  {
    assertFalse(is_qname<SA>(SA::construct_from_utf8("xsl:foo:")));
  } // test7

  void test11()
  {
    assertFalse(is_qname<SA>(SA::construct_from_utf8("$rr")));
  } // test11

  void test12()
  {
    assertFalse(is_qname<SA>(SA::construct_from_utf8("root/child")));
  } // test12
}; // class QNameTest

template<typename string_type, typename string_adaptor>
TestSuite* QNameTest_suite()
{
  typedef QNameTest<string_type, string_adaptor> QNT;

  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<QNT>("test1", &QNT::test1));
  suiteOfTests->addTest(new TestCaller<QNT>("test2", &QNT::test2));
  suiteOfTests->addTest(new TestCaller<QNT>("test3", &QNT::test3));
  suiteOfTests->addTest(new TestCaller<QNT>("test4", &QNT::test4));
  suiteOfTests->addTest(new TestCaller<QNT>("test5", &QNT::test5));
  suiteOfTests->addTest(new TestCaller<QNT>("test6", &QNT::test6));
  suiteOfTests->addTest(new TestCaller<QNT>("test7", &QNT::test7));
  suiteOfTests->addTest(new TestCaller<QNT>("test8", &QNT::test8));
  suiteOfTests->addTest(new TestCaller<QNT>("test9", &QNT::test9));
  suiteOfTests->addTest(new TestCaller<QNT>("test10", &QNT::test10));
  suiteOfTests->addTest(new TestCaller<QNT>("test11", &QNT::test11));
  suiteOfTests->addTest(new TestCaller<QNT>("test12", &QNT::test12));

  return suiteOfTests;
} // QNameTest_suite

template<typename string_type, typename string_adaptor>
TestSuite* XMLStringTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(NCNameTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(QNameTest_suite<string_type, string_adaptor>());

  return suiteOfTests;
} // XMLStringTest_suite

#endif
