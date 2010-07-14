#ifndef test_Stream_HPP
#define test_Stream_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>
#include <DOM/io/Stream.hpp>

template<class string_type, class string_adaptor>
class StreamTest : public TestCase
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  
  typedef string_adaptor SA;
  typedef Arabica::DOM::Document<string_type, string_adaptor> DocumentT;
  typedef Arabica::DOM::Element<string_type, string_adaptor> ElementT;
  typedef std::basic_ostringstream<typename string_adaptor::value_type> stringstreamT;

public:
  StreamTest(const std::string& name) :
    TestCase(name)
  {
  } // StreamTest

  void setUp() 
  {
    factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
  } // setUp

  string_type s(const char* cs)
  {
    return SA::construct_from_utf8(cs);
  } // s

  void testNoNS()
  {
    DocumentT doc = factory.createDocument(s(""), s("a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElement(s("b"));
    ElementT c = doc.createElement(s("c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assert(stream.str() == "<a><b><c/></b></a>");
  } // testNoNS

}; // class StreamTest

template<class string_type, class string_adaptor>
TestSuite* StreamTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNoNS", &StreamTest<string_type, string_adaptor>::testNoNS));
} // StreamTest_suite

#endif
