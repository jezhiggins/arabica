#ifndef UTILS_QNAME_HPP
#define UTILS_QNAME_HPP

#include <XML/QName.hpp>
#include <iostream>
using namespace Arabica::XML;

template<class string_type, class string_adaptor>
class QualifiedNameTest : public TestCase
{
  typedef string_adaptor SA;
  typedef QualifiedName<string_type, string_adaptor> QN;
  typedef QualifiedNameTest<string_type, string_adaptor> QNT;
public:
  QualifiedNameTest(const std::string& name) :
    TestCase(name)
  {
  } // QualifiedNameTest

  void testNcNameEquality()
  {
    QN q1(SA::construct_from_utf8("foo"), SA::empty_string());
    QN q2(SA::construct_from_utf8("foo"), SA::empty_string());
    
    assertTrue(q1 == q2);
    assertTrue(!(q1 != q2));
  } // testNcNameEquality

  void testNcNameCopy()
  {
    QN q1(SA::construct_from_utf8("foo"), SA::empty_string());
    QN q2(q1);
    
    assertTrue(q1 == q2);
    assertTrue(!(q1 != q2));
  } // testNcNameCopy

  void testNcNameAssignment()
  {
    QN q1(SA::construct_from_utf8("foo"), SA::empty_string());
    QN q2(SA::construct_from_utf8("bar"), SA::empty_string());
    
    assertFalse(q1 == q2);

    q2 = q1;

    assertTrue(q1 == q2);
  } // testNcNameAssignment

  void testNcClarkName()
  {
    QN q(SA::construct_from_utf8("bar"), SA::empty_string());

    assertTrue(SA::construct_from_utf8("bar") == q.clarkName());
  } // testNcClarkName

  void testEquality()
  {
    QN q1(SA::construct_from_utf8("foo"), SA::construct_from_utf8("bar"), SA::construct_from_utf8("http://test/"));
    QN q2(SA::construct_from_utf8("foo"), SA::construct_from_utf8("bar"), SA::construct_from_utf8("http://test/"));

    assertTrue(q1 == q2);
    assertTrue(!(q1 != q2));

    // prefix is not significant
    QN q3(SA::construct_from_utf8("baz"), SA::construct_from_utf8("bar"), SA::construct_from_utf8("http://test/"));
    assertTrue(q1 == q3);
    assertTrue(!(q1 != q3));
  } // testEquality

  void testCopy()
  {
    QN q1(SA::construct_from_utf8("foo"), SA::construct_from_utf8("bar"), SA::construct_from_utf8("http://test/"));
    QN q2(q1);

    assertTrue(q1 == q2);
  } // testCopy

  void testAssignment()
  {
    QN q1(SA::construct_from_utf8("foo"), SA::construct_from_utf8("bar"), SA::construct_from_utf8("http://test/"));
    QN q2(SA::construct_from_utf8("foo"), SA::construct_from_utf8("parp"), SA::construct_from_utf8("http://tst/"));

    assertTrue(q1 != q2);

    q2 = q1;

    assertTrue(q1 == q2);
  } // testAssignment

  void testClarkName()
  {
    QN q(SA::construct_from_utf8("foo"), SA::construct_from_utf8("bar"), SA::construct_from_utf8("http://test/"));
    assertTrue(SA::construct_from_utf8("{http://test/}bar") == q.clarkName());
  } // testClarkName

  void testPrefix()
  {
    QN q(SA::construct_from_utf8(""), SA::construct_from_utf8("bar"), SA::construct_from_utf8("http://test/"));
    assertFalse(q.has_prefix());
    assertTrue(SA::construct_from_utf8("bar") == q.localName());
    assertTrue(SA::construct_from_utf8("http://test/") == q.namespaceUri());
    
    q.set_prefix(SA::construct_from_utf8("t"));
    assertTrue(q.has_prefix());
    assertTrue(SA::construct_from_utf8("t") == q.prefix());
  } // testPrefix

  static string_type uri_mapper(const string_type& /* prefix */)
  {
    return SA::construct_from_utf8("http://test/");
  } // uri_mapper

  void testParseBadQName()
  {
    doTestParseBadQName("::::");
    doTestParseBadQName("foo:");
    doTestParseBadQName(":oo");
    doTestParseBadQName("f:ooo:");
    doTestParseBadQName("???");
  } // testParseBadQName

  void doTestParseBadQName(const char* q)
  {
    try {
      QN::parseQName(SA::construct_from_utf8(q), false, QNT::uri_mapper);
      assertFalse("oops - should have thrown here");
    }
    catch(std::runtime_error&) {
      // yay
    } 
  } // testParseBadQName

  void testParseQName()
  {
    QN q = QN::parseQName(SA::construct_from_utf8("hello"), true, QNT::uri_mapper);
    assertTrue(q.localName() == SA::construct_from_utf8("hello"));
    assertFalse(q.has_prefix());
    assertTrue(q.namespaceUri() == SA::empty_string());
    assertTrue(q.rawName() == SA::construct_from_utf8("hello"));

    QN q2 = QN::parseQName(SA::construct_from_utf8("h:hello"), true, QNT::uri_mapper);
    assertTrue(q2.localName() == SA::construct_from_utf8("hello"));    
    assertTrue(q2.prefix() == SA::construct_from_utf8("h"));
    assertTrue(q2.namespaceUri() == SA::construct_from_utf8("http://test/"));
    assertTrue(q2.rawName() == SA::construct_from_utf8("h:hello"));    

    QN q3 = QN::parseQName(SA::construct_from_utf8("hello"), false, QNT::uri_mapper);
    assertTrue(q3.localName() == SA::construct_from_utf8("hello"));
    assertFalse(q3.has_prefix());
    assertTrue(q3.namespaceUri() == SA::construct_from_utf8("http://test/"));
    assertTrue(q3.rawName() == SA::construct_from_utf8("hello"));
  } // testParseQName

  void testParseQName2()
  {
    std::map<string_type, string_type> namespaces;
    namespaces[SA::empty_string()] = SA::construct_from_utf8("http://test/");
    namespaces[SA::construct_from_utf8("h")] = SA::construct_from_utf8("http://test/");

    QN q = QN::parseQName(SA::construct_from_utf8("hello"), true, namespaces);
    assertTrue(q.localName() == SA::construct_from_utf8("hello"));
    assertFalse(q.has_prefix());
    assertTrue(q.namespaceUri() == SA::empty_string());
    assertTrue(q.rawName() == SA::construct_from_utf8("hello"));

    QN q2 = QN::parseQName(SA::construct_from_utf8("h:hello"), true, namespaces);
    assertTrue(q2.localName() == SA::construct_from_utf8("hello"));    
    assertTrue(q2.prefix() == SA::construct_from_utf8("h"));
    assertTrue(q2.namespaceUri() == SA::construct_from_utf8("http://test/"));
    assertTrue(q2.rawName() == SA::construct_from_utf8("h:hello"));    

    QN q3 = QN::parseQName(SA::construct_from_utf8("hello"), false, namespaces);
    assertTrue(q3.localName() == SA::construct_from_utf8("hello"));
    assertFalse(q3.has_prefix());
    assertTrue(q3.namespaceUri() == SA::construct_from_utf8("http://test/"));
    assertTrue(q3.rawName() == SA::construct_from_utf8("hello"));
  } // testParseQName2

}; // class QualifiedNameTest

template<class string_type, class string_adaptor>
TestSuite* QualifiedNameTest_suite()
{
  typedef QualifiedNameTest<string_type, string_adaptor> QNT;

  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<QNT>("testNcNameEquality", &QNT::testNcNameEquality));
  suiteOfTests->addTest(new TestCaller<QNT>("testNcNameCopy", &QNT::testNcNameCopy));
  suiteOfTests->addTest(new TestCaller<QNT>("testNcNameAssignment", &QNT::testNcNameAssignment));
  suiteOfTests->addTest(new TestCaller<QNT>("testNcClarkName", &QNT::testNcClarkName));
  suiteOfTests->addTest(new TestCaller<QNT>("testEquality", &QNT::testEquality));
  suiteOfTests->addTest(new TestCaller<QNT>("testCopy", &QNT::testCopy));
  suiteOfTests->addTest(new TestCaller<QNT>("testAssignment", &QNT::testAssignment));
  suiteOfTests->addTest(new TestCaller<QNT>("testClarkName", &QNT::testClarkName));
  suiteOfTests->addTest(new TestCaller<QNT>("testPrefix", &QNT::testPrefix));
  suiteOfTests->addTest(new TestCaller<QNT>("testParseBadQName", &QNT::testParseBadQName));
  suiteOfTests->addTest(new TestCaller<QNT>("testParseQName", &QNT::testParseQName));
  suiteOfTests->addTest(new TestCaller<QNT>("testParseQName", &QNT::testParseQName2));

  return suiteOfTests;
} // QualifiedNameTest_suite
#endif
