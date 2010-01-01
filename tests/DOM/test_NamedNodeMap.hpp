#ifndef test_NAMEDNODEMAP_H
#define test_NAMEDNODEMAP_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"
#include <sstream>
#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

template<class string_type, class string_adaptor>
class NamedNodeMapTest : public TestCase 
{
  typedef string_adaptor SA;

  typedef Arabica::DOM::Element<string_type, string_adaptor> Element;
  typedef Arabica::DOM::Node<string_type, string_adaptor> Node;
  typedef Arabica::DOM::NamedNodeMap<string_type, string_adaptor> NamedNodeMap;

  public: 
    NamedNodeMapTest(std::string name) :
        TestCase(name) 
    {
    } // NamedNodeMapTest
    
    void setUp() 
    {
    } // setUp

    string_type s(const char* ss)
    {
      return SA::construct_from_utf8(ss);
    } // s

    Arabica::DOM::Document<string_type, string_adaptor> parse(const char* xml)
    {
      string_type str = s(xml);
      std::stringstream ss;
      ss << SA::asStdString(str);

      Arabica::SAX::InputSource<string_type, string_adaptor> is(ss);
      Arabica::SAX::CatchErrorHandler<string_type, string_adaptor> eh;
      Arabica::SAX2DOM::Parser<string_type, string_adaptor> parser;
      parser.setErrorHandler(eh);
      parser.parse(is);       

      //if(eh.errorsReported())
      //  throw std::runtime_error(eh.errors());

      return parser.getDocument();
    } // parse

    void test1()
    {
      Element d = parse("<root/>").getDocumentElement();
      NamedNodeMap nm = d.getAttributes();
      assertEquals(0, nm.getLength());
    } // test1

    void test2()
    {
      Element d = parse("<root a='one'/>").getDocumentElement();
      NamedNodeMap nm = d.getAttributes();
      assertEquals(1, nm.getLength());
      assert(s("one") == nm.item(0).getNodeValue());
      assert(s("one") == nm.getNamedItem(s("a")).getNodeValue());
      assert(s("one") == nm.getNamedItemNS(s(""), s("a")).getNodeValue());
    } // test2

    void test3()
    {
      Element d = parse("<root xmlns:a='urn:a' a:a='one'/>").getDocumentElement();
      NamedNodeMap nm = d.getAttributes();
      assertEquals(2, nm.getLength());
      assert(0 == nm.getNamedItem(s("a")));
      assert(s("one") == nm.getNamedItemNS(s("urn:a"), s("a")).getNodeValue());
    } // test3

    void test4()
    {
      Element d = parse("<root a='one'/>").getDocumentElement();
      NamedNodeMap nm = d.getAttributes();
      assertEquals(1, nm.getLength());
      Node a = nm.removeNamedItem(s("a"));
      assertEquals(0, nm.getLength());
      nm.setNamedItem(a);
      assertEquals(1, nm.getLength());
    } // test4

    void test5()
    {
      Element d = parse("<root xmlns:a='urn:a' a:a='one'/>").getDocumentElement();
      NamedNodeMap nm = d.getAttributes();
      assertEquals(2, nm.getLength());
      Node a = nm.removeNamedItemNS(s("urn:a"), s("a"));
      assertEquals(1, nm.getLength());
      nm.setNamedItemNS(a);
      assertEquals(2, nm.getLength());
    } // test5

};

template<class string_type, class string_adaptor>
TestSuite* NamedNodeMapTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<NamedNodeMapTest<string_type, string_adaptor> >("test1", &NamedNodeMapTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<NamedNodeMapTest<string_type, string_adaptor> >("test2", &NamedNodeMapTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<NamedNodeMapTest<string_type, string_adaptor> >("test3", &NamedNodeMapTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<NamedNodeMapTest<string_type, string_adaptor> >("test4", &NamedNodeMapTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<NamedNodeMapTest<string_type, string_adaptor> >("test5", &NamedNodeMapTest<string_type, string_adaptor>::test5));
  return suiteOfTests;
} // NamedNodeMapTest_suite

#endif

