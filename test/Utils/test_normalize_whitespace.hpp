#ifndef utils_normalize_whitespace_test_hpp
#define utils_normalize_whitespace_test_hpp

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <Utils/normalize_whitespace.hpp>

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
      assertEquals("hello", Arabica::string::normalize_whitespace<string_type, string_adaptor>(s));
    } 
    
    void testNormalize2()
    {
      string_type s = SA::construct_from_utf8("hello   ");
      assertEquals("hello", Arabica::string::normalize_whitespace<string_type, string_adaptor>(s));
    } 
    
    void testNormalize3()
    {
      string_type s = SA::construct_from_utf8("    hello");
      assertEquals("hello", Arabica::string::normalize_whitespace<string_type, string_adaptor>(s));
    } 
    
    void testNormalize4()
    {
      string_type s = SA::construct_from_utf8("    hello      ");
      assertEquals("hello", Arabica::string::normalize_whitespace<string_type, string_adaptor>(s));
    } 

    void testNormalize5()
    {
      string_type s = SA::construct_from_utf8("    hello world     ");
      assertEquals("hello world", Arabica::string::normalize_whitespace<string_type, string_adaptor>(s));
    } 

    void testNormalize6()
    {
      string_type s = SA::construct_from_utf8("\t\t\thello\tworld\t\t\t\t\t");
      assertEquals("hello world", Arabica::string::normalize_whitespace<string_type, string_adaptor>(s));
    } 

    void testNormalize7()
    {
      string_type s = SA::construct_from_utf8("\r\n    h e  l   l    o \t\r\n w    \t   o \t r   l d     ");
      assertEquals("h e l l o w o r l d", Arabica::string::normalize_whitespace<string_type, string_adaptor>(s));
    } 
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

