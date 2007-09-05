#ifndef ARABICA_TEST_WHITESPACE_STRIPPER_HPP
#define ARABICA_TEST_WHITESPACE_STRIPPER_HPP

#include <memory>
#include <sstream>
#include <iostream>

#include <SAX/XMLReader.hpp>
#include <SAX/InputSource.hpp>
#include <SAX/filter/WhitespaceStripperFilter.hpp>
#include <SAX/filter/PYXWriter.hpp>

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

template<class string_type, class string_adaptor>
class WhitespaceStripperTest : public TestCase 
{
  typedef string_adaptor SA;

  public: 
    WhitespaceStripperTest(std::string name) :
        TestCase(name) 
    {
    } // WhitespaceStripperTest
    
    void setUp() 
    {
    } // setUp

    void testNoStrip() 
    {
      std::ostringstream o;
      Arabica::SAX::XMLReader<std::string> parser;
      Arabica::SAX::PYXWriter<std::string> writer(o, parser);
      writer.parse(*source("<test><p>  Woo baby   hooray    </p></test>"));
      assertEquals("(test\n(p\n-  Woo baby   hooray    \n)p\n)test\n", o.str());
    } // testNoStrip

    void testStripLeading() 
    {
      std::ostringstream o;
      Arabica::SAX::XMLReader<std::string> parser;
      Arabica::SAX::WhitespaceStripper<std::string> stripper(parser);
      Arabica::SAX::PYXWriter<std::string> writer(o, stripper);
      writer.parse(*source("<test><p>Woo</p></test>"));
      assertEquals("(test\n(p\n-Woo\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p> Woo</p></test>"));
      assertEquals("(test\n(p\n-Woo\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p>      Woo</p></test>"));
      assertEquals("(test\n(p\n-Woo\n)p\n)test\n", o.str());
    } // testStripLeading

    void testStripTrailing() 
    {
      std::ostringstream o;
      Arabica::SAX::XMLReader<std::string> parser;
      Arabica::SAX::WhitespaceStripper<std::string> stripper(parser);
      Arabica::SAX::PYXWriter<std::string> writer(o, stripper);
      writer.parse(*source("<test><p>Woo</p></test>"));
      assertEquals("(test\n(p\n-Woo\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p>Woo </p></test>"));
      assertEquals("(test\n(p\n-Woo\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p>Woo     </p></test>"));
      assertEquals("(test\n(p\n-Woo\n)p\n)test\n", o.str());
    } // testStripTrailing

    void testStripMid() 
    {
      std::ostringstream o;
      Arabica::SAX::XMLReader<std::string> parser;
      Arabica::SAX::WhitespaceStripper<std::string> stripper(parser);
      Arabica::SAX::PYXWriter<std::string> writer(o, stripper);
      writer.parse(*source("<test><p>Woo yea</p></test>"));
      assertEquals("(test\n(p\n-Woo yea\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p>Woo  yea</p></test>"));
      assertEquals("(test\n(p\n-Woo yea\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p>Woo     yea</p></test>"));
      assertEquals("(test\n(p\n-Woo yea\n)p\n)test\n", o.str());
    } // testStripMid

    void testStripMid2() 
    {
      std::ostringstream o;
      Arabica::SAX::XMLReader<std::string> parser;
      Arabica::SAX::WhitespaceStripper<std::string> stripper(parser);
      Arabica::SAX::PYXWriter<std::string> writer(o, stripper);
      writer.parse(*source("<test><p>Woo yea man</p></test>"));
      assertEquals("(test\n(p\n-Woo yea man\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p>Woo yea  man</p></test>"));
      assertEquals("(test\n(p\n-Woo yea man\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p>Woo     yea man</p></test>"));
      assertEquals("(test\n(p\n-Woo yea man\n)p\n)test\n", o.str());
      
      o.str("");
      writer.parse(*source("<test><p>Woo     yea    man</p></test>"));
      assertEquals("(test\n(p\n-Woo yea man\n)p\n)test\n", o.str());
    } // testStripMid2

    void testStrip() 
    {
      std::ostringstream o;
      Arabica::SAX::XMLReader<std::string> parser;
      Arabica::SAX::WhitespaceStripper<std::string> stripper(parser);
      Arabica::SAX::PYXWriter<std::string> writer(o, stripper);
      writer.parse(*source("<test><p>  Woo baby   hooray    </p><!-- yo mama --></test>"));
      assertEquals("(test\n(p\n-Woo baby hooray\n)p\n)test\n", o.str());
    } // testStrip

  private:
    std::auto_ptr<Arabica::SAX::InputSource<std::string> > source(const std::string& str)
    {
      std::auto_ptr<std::iostream> ss(new std::stringstream());
      (*ss) << str;
      return std::auto_ptr<Arabica::SAX::InputSource<std::string> >(new Arabica::SAX::InputSource<std::string>(ss));
    } // source
}; // WhitespaceStripperTest

template<class string_type, class string_adaptor>
TestSuite* WhitespaceStripper_test_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<WhitespaceStripperTest<string_type, string_adaptor> >("testNoStrip", &WhitespaceStripperTest<string_type, string_adaptor>::testNoStrip));
  suiteOfTests->addTest(new TestCaller<WhitespaceStripperTest<string_type, string_adaptor> >("testStripLeading", &WhitespaceStripperTest<string_type, string_adaptor>::testStripLeading));
  suiteOfTests->addTest(new TestCaller<WhitespaceStripperTest<string_type, string_adaptor> >("testStripTrailing", &WhitespaceStripperTest<string_type, string_adaptor>::testStripTrailing));
  suiteOfTests->addTest(new TestCaller<WhitespaceStripperTest<string_type, string_adaptor> >("testStripMid", &WhitespaceStripperTest<string_type, string_adaptor>::testStripMid));
  suiteOfTests->addTest(new TestCaller<WhitespaceStripperTest<string_type, string_adaptor> >("testStripMid2", &WhitespaceStripperTest<string_type, string_adaptor>::testStripMid2));
  suiteOfTests->addTest(new TestCaller<WhitespaceStripperTest<string_type, string_adaptor> >("testStrip", &WhitespaceStripperTest<string_type, string_adaptor>::testStrip));

  return suiteOfTests;
} // WhitespaceStripperTest_suite

#endif

