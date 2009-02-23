#ifndef UTILS_QNAME_HPP
#define UTILS_QNAME_HPP

#include <XML/QName.hpp>

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
    QN q1(SA::construct_from_utf8("foo"));
    QN q2(SA::construct_from_utf8("foo"));
    
    assertTrue(q1 == q2);
    assertTrue(!(q1 != q2));
  } // testNcNameEquality

  void testNcNameCopy()
  {
    QN q1(SA::construct_from_utf8("foo"));
    QN q2(q1);
    
    assertTrue(q1 == q2);
    assertTrue(!(q1 != q2));
  } // testNcNameCopy

  void testNcNameAssignment()
  {
    QN q1(SA::construct_from_utf8("foo"));
    QN q2(SA::construct_from_utf8("bar"));
    
    assertFalse(q1 == q2);

    q2 = q1;

    assertTrue(q1 == q2);
  } // testNcNameAssignment

  void testNcClarkName()
  {
    QN q(SA::construct_from_utf8("bar"));

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

  static string_type uri_mapper(const string_type& prefix)
  {
    return SA::construct_from_utf8("http://test/");
  } // uri_mapper

  void testParseBadQName()
  {
    try {
      QN::parseQName(SA::construct_from_utf8("::::"), false, QNT::uri_mapper);
      assertFalse("oops - should have thrown here");
    }
    catch(std::runtime_error&) {
      // yay
    } 
  } // testParseBadQName

  void testParseQName()
  {
    QN q = QN::parseQName(SA::construct_from_utf8("hello"), false, QNT::uri_mapper);
    assertTrue(q.localName() == SA::construct_from_utf8("hello"));

    QN q2 = QN::parseQName(SA::construct_from_utf8("h:hello"), false, QNT::uri_mapper);
    assertTrue(q2.localName() == SA::construct_from_utf8("hello"));    
    assertTrue(q2.prefix() == SA::construct_from_utf8("h"));
    assertTrue(q2.namespaceUri() == SA::construct_from_utf8("http://test/"));
  } // testParseQName

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

  return suiteOfTests;
} // QualifiedNameTest_suite
#endif
