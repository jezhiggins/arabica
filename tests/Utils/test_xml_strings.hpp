#ifndef UTILS_XML_STRINGS_HPP
#define UTILS_XML_STRINGS_HPP

#include <XML/strings.hpp>

using namespace Arabica::XML;

class XMLStringTest : public TestCase
{
public:
  XMLStringTest(std::string name) : 
    TestCase(name)
  {
  } // XMLStringTest
  
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
    assertTrue("a:b");
  } // test4

  void test5()
  {
    assertFalse(":b");
  } // test5

}; // class XMLStringTest

TestSuite* XMLStringTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<XMLStringTest>("test1", &XMLStringTest::test1));
  suiteOfTests->addTest(new TestCaller<XMLStringTest>("test2", &XMLStringTest::test2));
  suiteOfTests->addTest(new TestCaller<XMLStringTest>("test3", &XMLStringTest::test3));
  suiteOfTests->addTest(new TestCaller<XMLStringTest>("test4", &XMLStringTest::test4));
  suiteOfTests->addTest(new TestCaller<XMLStringTest>("test5", &XMLStringTest::test5));

  return suiteOfTests;
} // XMLStringTest_suite

#endif
