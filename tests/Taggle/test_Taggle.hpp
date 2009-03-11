#ifndef ARABICA_TEST_TAGGLE_HPP
#define ARABICA_TEST_TAGGLE_HPP

#include <memory>
#include <sstream>
#include <iostream>

#include <SAX/filter/Writer.hpp>
#include <Taggle/Taggle.hpp>

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

class TaggleTest : public TestCase 
{
  public: 
    TaggleTest(std::string name) :
        TestCase(name) 
    {
    } // TaggleTest
    
    void setUp() 
    {
    } // setUp

    void senseTest() 
    {
      Arabica::SAX::Taggle<std::string> parser;
      std::ostringstream sink;
      Arabica::SAX::Writer<std::string> writer(sink, parser);

      writer.parse(*source("<html><body>woo!<br></body></html>"));
      assertEquals("<?xml version=\"1.0\"?>\n<html>\n  <body>woo!\n    <br clear=\"none\"></br>\n  </body>\n</html>\n", sink.str());
    } // senseTest

  private:
    std::auto_ptr<Arabica::SAX::InputSource<std::string> > source(const std::string& str)
    {
      std::auto_ptr<std::iostream> ss(new std::stringstream());
      (*ss) << str;
      return std::auto_ptr<Arabica::SAX::InputSource<std::string> >(new Arabica::SAX::InputSource<std::string>(ss));
    } // source
}; // TaggleTest

TestSuite* Taggle_test_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<TaggleTest>("senseTest", &TaggleTest::senseTest));

  return suiteOfTests;
} // TaggleTest_suite

#endif

