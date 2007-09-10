#ifndef utils_normalize_whitespace_test_hpp
#define utils_normalize_whitespace_test_hpp

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <text/normalize_whitespace.hpp>

template<class string_type, class string_adaptor>
class NormalizeWhitespaceTest : public TestCase 
{
  typedef string_adaptor SA;

  public: 
    NormalizeWhitespaceTest(std::string name) :
        TestCase(name) 
    {
    } 
    
    void testNormalize1()
    {
      string_type s = SA::construct_from_utf8("hello");
      string_type n = normalize(s);
      assertTrue(SA::construct_from_utf8("hello") == n);
    } 
    
    void testNormalize2()
    {
      string_type s = SA::construct_from_utf8("hello   ");
      string_type n = normalize(s);
      assertTrue(SA::construct_from_utf8("hello") == n);
    } 
    
    void testNormalize3()
    {
      string_type s = SA::construct_from_utf8("    hello");
      string_type n = normalize(s);
      assertTrue(SA::construct_from_utf8("hello") == n);
    } 
    
    void testNormalize4()
    {
      string_type s = SA::construct_from_utf8("    hello      ");
      string_type n = normalize(s);
      assertTrue(SA::construct_from_utf8("hello") == n);
    } 

    void testNormalize5()
    {
      string_type s = SA::construct_from_utf8("    hello world     ");
      string_type n = normalize(s);
      assertTrue(SA::construct_from_utf8("hello world") == n);
    } 

    void testNormalize6()
    {
      string_type s = SA::construct_from_utf8("\t\t\thello\tworld\t\t\t\t\t");
      string_type n = normalize(s);
      assertTrue(SA::construct_from_utf8("hello world") == n);
    } 

    void testNormalize7()
    {
      string_type s = SA::construct_from_utf8("\r\n    h e  l   l    o \t\r\n w    \t   o \t r   l d     ");
      string_type n = normalize(s);
      assertTrue(SA::construct_from_utf8("h e l l o w o r l d") == n);
    } 

private:
   string_type normalize(const string_type& s)
   {
     return Arabica::text::normalize_whitespace<string_type, string_adaptor>(s);
   } // normalize
};

template<class string_type, class string_adaptor>
TestSuite* NormalizeWhitespaceTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<NormalizeWhitespaceTest<string_type, string_adaptor> >("testNormalize1", &NormalizeWhitespaceTest<string_type, string_adaptor>::testNormalize1));
  suiteOfTests->addTest(new TestCaller<NormalizeWhitespaceTest<string_type, string_adaptor> >("testNormalize2", &NormalizeWhitespaceTest<string_type, string_adaptor>::testNormalize2));
  suiteOfTests->addTest(new TestCaller<NormalizeWhitespaceTest<string_type, string_adaptor> >("testNormalize3", &NormalizeWhitespaceTest<string_type, string_adaptor>::testNormalize3));
  suiteOfTests->addTest(new TestCaller<NormalizeWhitespaceTest<string_type, string_adaptor> >("testNormalize4", &NormalizeWhitespaceTest<string_type, string_adaptor>::testNormalize4));
  suiteOfTests->addTest(new TestCaller<NormalizeWhitespaceTest<string_type, string_adaptor> >("testNormalize5", &NormalizeWhitespaceTest<string_type, string_adaptor>::testNormalize5));
  suiteOfTests->addTest(new TestCaller<NormalizeWhitespaceTest<string_type, string_adaptor> >("testNormalize6", &NormalizeWhitespaceTest<string_type, string_adaptor>::testNormalize6));
  suiteOfTests->addTest(new TestCaller<NormalizeWhitespaceTest<string_type, string_adaptor> >("testNormalize7", &NormalizeWhitespaceTest<string_type, string_adaptor>::testNormalize7));

  return suiteOfTests;
} // NormalizeWhitespaceTest_suite

#endif

