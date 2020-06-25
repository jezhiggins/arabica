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

    void expect(char const* expected, std::basic_ostringstream<typename string_adaptor::value_type>& result) {
        assertEquals(
            expected,
            string_adaptor::asStdString(string_adaptor::construct(result.str().c_str()))
        );
    }

    void testNoStrip() 
    {
      std::basic_ostringstream<typename string_adaptor::value_type> o;
      Arabica::SAX::XMLReader<string_type, string_adaptor> parser;
      Arabica::SAX::PYXWriter<string_type, string_adaptor> writer(o, parser);
      writer.parse(*source("<test><p>  Woo baby   hooray    </p></test>"));
      expect("(test\n(p\n-  Woo baby   hooray    \n)p\n)test\n", o);
    } // testNoStrip

    void testStripLeading()
    {
      std::basic_ostringstream<typename string_adaptor::value_type> o;
      Arabica::SAX::XMLReader<string_type, string_adaptor> parser;
      Arabica::SAX::WhitespaceStripper<string_type, string_adaptor> stripper(parser);
      Arabica::SAX::PYXWriter<string_type, string_adaptor> writer(o, stripper);
      writer.parse(*source("<test><p>Woo</p></test>"));
      expect("(test\n(p\n-Woo\n)p\n)test\n", o);
      
      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p> Woo</p></test>"));
      expect("(test\n(p\n-Woo\n)p\n)test\n", o);
      
      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p>      Woo</p></test>"));
      expect("(test\n(p\n-Woo\n)p\n)test\n", o);
    } // testStripLeading

    void testStripTrailing()
    {
      std::basic_ostringstream<typename string_adaptor::value_type> o;
      Arabica::SAX::XMLReader<string_type, string_adaptor> parser;
      Arabica::SAX::WhitespaceStripper<string_type, string_adaptor> stripper(parser);
      Arabica::SAX::PYXWriter<string_type, string_adaptor> writer(o, stripper);
      writer.parse(*source("<test><p>Woo</p></test>"));
      expect("(test\n(p\n-Woo\n)p\n)test\n", o);
      
      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p>Woo </p></test>"));
      expect("(test\n(p\n-Woo\n)p\n)test\n", o);
      
      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p>Woo     </p></test>"));
      expect("(test\n(p\n-Woo\n)p\n)test\n", o);
    } // testStripTrailing

    void testStripMid() 
    {
      std::basic_ostringstream<typename string_adaptor::value_type> o;
      Arabica::SAX::XMLReader<string_type, string_adaptor> parser;
      Arabica::SAX::WhitespaceStripper<string_type, string_adaptor> stripper(parser);
      Arabica::SAX::PYXWriter<string_type, string_adaptor> writer(o, stripper);
      writer.parse(*source("<test><p>Woo yea</p></test>"));
      expect("(test\n(p\n-Woo yea\n)p\n)test\n", o);
      
      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p>Woo  yea</p></test>"));
      expect("(test\n(p\n-Woo yea\n)p\n)test\n", o);
      
      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p>Woo     yea</p></test>"));
      expect("(test\n(p\n-Woo yea\n)p\n)test\n", o);
    } // testStripMid

    void testStripMid2() 
    {
      std::basic_ostringstream<typename string_adaptor::value_type> o;
      Arabica::SAX::XMLReader<string_type, string_adaptor> parser;
      Arabica::SAX::WhitespaceStripper<string_type, string_adaptor> stripper(parser);
      Arabica::SAX::PYXWriter<string_type, string_adaptor> writer(o, stripper);
      writer.parse(*source("<test><p>Woo yea man</p></test>"));
      expect("(test\n(p\n-Woo yea man\n)p\n)test\n", o);

      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p>Woo yea  man</p></test>"));
      expect("(test\n(p\n-Woo yea man\n)p\n)test\n", o);

      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p>Woo     yea man</p></test>"));
      expect("(test\n(p\n-Woo yea man\n)p\n)test\n", o);

      o.str(string_adaptor::empty_string());
      writer.parse(*source("<test><p>Woo     yea    man</p></test>"));
      expect("(test\n(p\n-Woo yea man\n)p\n)test\n", o);
    } // testStripMid2

    void testStrip() 
    {
      std::basic_ostringstream<typename string_adaptor::value_type> o;
      Arabica::SAX::XMLReader<string_type, string_adaptor> parser;
      Arabica::SAX::WhitespaceStripper<string_type, string_adaptor> stripper(parser);
      Arabica::SAX::PYXWriter<string_type, string_adaptor> writer(o, stripper);
      writer.parse(*source("<test><p>  Woo baby   hooray    </p><!-- yo mama --></test>"));
      expect("(test\n(p\n-Woo baby hooray\n)p\n)test\n", o);
    } // testStrip

  private:
    std::unique_ptr<Arabica::SAX::InputSource<string_type, string_adaptor> > source(const std::string& str)
    {
      std::unique_ptr<std::iostream> ss(new std::stringstream());
      (*ss) << str;
      return std::make_unique<Arabica::SAX::InputSource<string_type, string_adaptor>>(std::move(ss));
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

