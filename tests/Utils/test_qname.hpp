#ifndef UTILS_QNAME_HPP
#define UTILS_QNAME_HPP

#include <XML/QName.hpp>

using namespace Arabica::XML;

class QualifiedNameTest : public TestCase
{
public:
  QualifiedNameTest(const std::string& name) :
    TestCase(name)
  {
  } // QualifiedNameTest

  void testNcNameEquality()
  {
    QualifiedName q1("foo");
    QualifiedName q2("foo");
    
    assertTrue(q1 == q2);
    assertTrue(!(q1 != q2));
  } // testNcNameEquality

  void testNcNameCopy()
  {
    QualifiedName q1("foo");
    QualifiedName q2(q1);
    
    assertTrue(q1 == q2);
    assertTrue(!(q1 != q2));
  } // testNcNameCopy

  void testNcNameAssignment()
  {
    QualifiedName q1("foo");
    QualifiedName q2("bar");
    
    assertFalse(q1 == q2);

    q2 = q1;

    assertTrue(q1 == q2);
  } // testNcNameAssignment

  void testNcClarkName()
  {
    QualifiedName q("bar");

    assertEquals("bar", q.clarkName());
  } // testNcClarkName

  void testEquality()
  {
    QualifiedName q1("foo", "bar", "http://test/");
    QualifiedName q2("foo", "bar", "http://test/");

    assertTrue(q1 == q2);
    assertTrue(!(q1 != q2));

    // prefix is not significant
    QualifiedName q3("baz", "bar", "http://test/");
    assertTrue(q1 == q3);
    assertTrue(!(q1 != q3));
  } // testEquality

  void testCopy()
  {
    QualifiedName q1("foo", "bar", "http://test/");
    QualifiedName q2(q1);

    assertTrue(q1 == q2);
  } // testCopy

  void testAssignment()
  {
    QualifiedName q1("foo", "bar", "http://test/");
    QualifiedName q2("foo", "parp", "http://tst/");

    assertTrue(q1 != q2);

    q2 = q1;

    assertTrue(q1 == q2);
  } // testAssignment

  void testClarkName()
  {
    QualifiedName q("foo", "bar", "http://test/");
    assertEquals("{http://test/}bar", q.clarkName());
  } // testClarkName

  void testPrefix()
  {
    QualifiedName q("", "bar", "http://test/");
    assertFalse(q.has_prefix());
    assertEquals("bar", q.localName());
    assertEquals("http://test/", q.namespaceUri());
    
    q.set_prefix("t");
    assertTrue(q.has_prefix());
    assertEquals("t", q.prefix());
  } // testPrefix
}; // class QualifiedNameTest

TestSuite* QualifiedNameTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testNcNameEquality", &QualifiedNameTest::testNcNameEquality));
  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testNcNameCopy", &QualifiedNameTest::testNcNameCopy));
  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testNcNameAssignment", &QualifiedNameTest::testNcNameAssignment));
  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testNcClarkName", &QualifiedNameTest::testNcClarkName));
  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testEquality", &QualifiedNameTest::testEquality));
  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testCopy", &QualifiedNameTest::testCopy));
  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testAssignment", &QualifiedNameTest::testAssignment));
  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testClarkName", &QualifiedNameTest::testClarkName));
  suiteOfTests->addTest(new TestCaller<QualifiedNameTest>("testPrefix", &QualifiedNameTest::testPrefix));

  return suiteOfTests;
} // QualifiedNameTest_suite
#endif
