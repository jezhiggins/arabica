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

  void assertEquals(string_type expected, 
                    string_type actual,
                    long lineNumber)
  { 
    if (expected != actual) 
      assertImplementation (false, notEqualsMessage(SA::asStdString(expected), SA::asStdString(actual)), lineNumber, "test_Stream.hpp"); 
  }


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

#ifndef ARABICA_NO_WCHAR_T
  string_type s(const wchar_t* cs)
  {
    return SA::construct_from_utf16(cs);
  } // s
#endif

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
    assertEquals(s("<a><b><c/></b></a>"), s(stream.str().c_str()), __LINE__);
  } // testNoNS

  void testNSNoPrefix()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("b"));
    ElementT c = doc.createElementNS(s("urn:test"), s("c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<a xmlns=\"urn:test\"><b><c/></b></a>"), s(stream.str().c_str()), __LINE__);
  } // testNSNoPrefix

  void testNSPrefix()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("t:a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("t:b"));
    ElementT c = doc.createElementNS(s("urn:test"), s("t:c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<t:a xmlns:t=\"urn:test\"><t:b><t:c/></t:b></t:a>"), s(stream.str().c_str()), __LINE__);
  } // testNSPrefix

  void testNSMixed()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("t:a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("b"));
    ElementT c = doc.createElementNS(s("urn:test"), s("s:c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<t:a xmlns:t=\"urn:test\"><t:b><t:c/></t:b></t:a>"), s(stream.str().c_str()), __LINE__);
  } // testNSMixed

  void testNSPrefixAttr()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("t:a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("t:b"));
    b.setAttribute(s("x"), s("y"));
    ElementT c = doc.createElementNS(s("urn:test"), s("t:c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<t:a xmlns:t=\"urn:test\"><t:b x=\"y\"><t:c/></t:b></t:a>"), s(stream.str().c_str()), __LINE__);
  } // testNSPrefixAttr

  void testNSPrefixAttrNS()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("t:a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("t:b"));
    b.setAttributeNS(s("urn:case"), s("c:x"), s("y"));
    ElementT c = doc.createElementNS(s("urn:test"), s("t:c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<t:a xmlns:t=\"urn:test\"><t:b c:x=\"y\" xmlns:c=\"urn:case\"><t:c/></t:b></t:a>"), s(stream.str().c_str()), __LINE__);
  } // testNSPrefixAttrNS

  void testNSPrefixAttrNS2()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("t:a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("t:b"));
    b.setAttributeNS(s("urn:case"), s("x"), s("y"));
    ElementT c = doc.createElementNS(s("urn:test"), s("t:c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<t:a xmlns:t=\"urn:test\"><t:b a0:x=\"y\" xmlns:a0=\"urn:case\"><t:c/></t:b></t:a>"), s(stream.str().c_str()), __LINE__);
  } // testNSPrefixAttrNS2

  void testNSPrefixAttrNS3()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("b"));
    b.setAttributeNS(s("urn:case"), s("x"), s("y"));
    ElementT c = doc.createElementNS(s("urn:test"), s("c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<a xmlns=\"urn:test\"><b a0:x=\"y\" xmlns:a0=\"urn:case\"><c/></b></a>"), s(stream.str().c_str()), __LINE__);
  } // testNSPrefixAttrNS3

  void testNSPrefixAttrNS4()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("b"));
    b.setAttributeNS(s("urn:case"), s("x"), s("y"));
    b.setAttributeNS(s("urn:box"), s("z"), s("y"));
    ElementT c = doc.createElementNS(s("urn:test"), s("c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<a xmlns=\"urn:test\"><b a0:x=\"y\" a1:z=\"y\" xmlns:a1=\"urn:box\" xmlns:a0=\"urn:case\"><c/></b></a>"), s(stream.str().c_str()), __LINE__);
  } // testNSPrefixAttrNS4

  void testNSPrefixAttrNS5()
  {
    DocumentT doc = factory.createDocument(s("urn:test"), s("a"), 0);
    ElementT a = doc.getDocumentElement();
    ElementT b = doc.createElementNS(s("urn:test"), s("b"));
    b.setAttributeNS(s("urn:case"), s("x"), s("y"));
    b.setAttributeNS(s("urn:box"), s("x"), s("y"));
    ElementT c = doc.createElementNS(s("urn:test"), s("c"));

    a.appendChild(b);
    b.appendChild(c);

    stringstreamT stream;
    stream << a;
    assertEquals(s("<a xmlns=\"urn:test\"><b a0:x=\"y\" a1:x=\"y\" xmlns:a0=\"urn:box\" xmlns:a1=\"urn:case\"><c/></b></a>"), s(stream.str().c_str()), __LINE__);
  } // testNSPrefixAttrNS5
}; // class StreamTest

template<class string_type, class string_adaptor>
TestSuite* StreamTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNoNS", &StreamTest<string_type, string_adaptor>::testNoNS));
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSNoPrefix", &StreamTest<string_type, string_adaptor>::testNSNoPrefix));
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSPrefix", &StreamTest<string_type, string_adaptor>::testNSPrefix));
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSMixed", &StreamTest<string_type, string_adaptor>::testNSMixed));
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSPrefixAttr", &StreamTest<string_type, string_adaptor>::testNSPrefixAttr));
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSPrefixAttrNS", &StreamTest<string_type, string_adaptor>::testNSPrefixAttrNS));
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSPrefixAttrNS2", &StreamTest<string_type, string_adaptor>::testNSPrefixAttrNS2));
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSPrefixAttrNS3", &StreamTest<string_type, string_adaptor>::testNSPrefixAttrNS3));
  //  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSPrefixAttrNS4", &StreamTest<string_type, string_adaptor>::testNSPrefixAttrNS4));
  suiteOfTests->addTest(new TestCaller<StreamTest<string_type, string_adaptor> >("testNSPrefixAttrNS5", &StreamTest<string_type, string_adaptor>::testNSPrefixAttrNS5));
  return suiteOfTests;
} // StreamTest_suite

#endif
