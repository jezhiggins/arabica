#ifndef test_SAX_H
#define test_SAX_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"
#include <sstream>
#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

template<class string_type, class string_adaptor>
class SAX2DOMTest : public TestCase 
{
  typedef string_adaptor SA;

  public: 
    SAX2DOMTest(std::string name) :
        TestCase(name) 
    {
    } // SAX2DOMTest
    
    void setUp() 
    {
    } // setUp

    Arabica::DOM::Document<string_type, string_adaptor> parse(string_type str)
    {
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
      Arabica::DOM::Element<string_type, string_adaptor> d;
      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // test1

    void test2()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<root/>"));
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.getDocumentElement();
      assert(elem.getParentNode() == d);
      assert(elem.getOwnerDocument() == d);
    } // test2

    void test3()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<root attr=\"poop\"/>"));
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.getDocumentElement();
      assert(elem.hasAttributes() == true);
      assert(elem.getAttribute(SA::construct_from_utf8("attr")) == SA::construct_from_utf8("poop"));
    } // test3

    void test4()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<root><child attr=\"poop\"/></root>"));
      Arabica::DOM::Element<string_type, string_adaptor> elem = Arabica::DOM::Element<string_type, string_adaptor>(d.getDocumentElement().getFirstChild());
      assert(SA::construct_from_utf8("child") == elem.getNodeName());
      assertEquals(true, elem.hasAttributes());
      assert(SA::construct_from_utf8("poop") == elem.getAttribute(SA::construct_from_utf8("attr")));
    } // test4

    void test5()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<stuff:elem attr='something' xmlns:stuff='http://example.com/stuff'/>"));
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.getDocumentElement();
      assertEquals(true, elem.hasNamespaceURI());
      assert(SA::construct_from_utf8("http://example.com/stuff") == elem.getNamespaceURI());

      Arabica::DOM::Attr<string_type, string_adaptor> attr = elem.getAttributeNode(SA::construct_from_utf8("attr"));
      assertEquals(false, attr.hasNamespaceURI());
    } // test5

    void test6()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<stuff:elem stuff:attr='something' xmlns:stuff='http://example.com/stuff'/>"));
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.getDocumentElement();
      assertEquals(true, elem.hasNamespaceURI());
      assert(SA::construct_from_utf8("http://example.com/stuff") == elem.getNamespaceURI());

      Arabica::DOM::Attr<string_type, string_adaptor> attr = elem.getAttributeNodeNS(SA::construct_from_utf8("http://example.com/stuff"), SA::construct_from_utf8("attr"));
      assertEquals(true, attr.hasNamespaceURI());
      assert(SA::construct_from_utf8("http://example.com/stuff") == attr.getNamespaceURI());
    } // test6

    void test7()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<elem stuff:attr='something' xmlns:stuff='http://example.com/stuff'/>"));
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.getDocumentElement();
      assertEquals(false, elem.hasNamespaceURI());

      Arabica::DOM::Attr<string_type, string_adaptor> attr = elem.getAttributeNodeNS(SA::construct_from_utf8("http://example.com/stuff"), SA::construct_from_utf8("attr"));
      assertEquals(true, attr.hasNamespaceURI());
      assert(SA::construct_from_utf8("http://example.com/stuff") == attr.getNamespaceURI());
    } // test7

    void test8()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<root attr=\"poop\"><child/></root>"));
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.getDocumentElement();

      Arabica::DOM::Element<string_type, string_adaptor> e2 = Arabica::DOM::Element<string_type, string_adaptor>(elem.cloneNode(true));
      assert(e2.getOwnerDocument() == d);
      assert(e2.getParentNode() == 0);
      assert(e2.hasAttributes() == true);
      assert(e2.getAttribute(SA::construct_from_utf8("attr")) == SA::construct_from_utf8("poop"));
      assert(e2.getFirstChild().getNodeName() == SA::construct_from_utf8("child"));
    } // test8

    void test9()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<elem attr='something' xmlns:stuff='http://example.com/stuff'/>"));
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.getDocumentElement();
      assertEquals(false, elem.hasNamespaceURI());

      Arabica::DOM::Attr<string_type, string_adaptor> attr = elem.getAttributeNode(SA::construct_from_utf8("attr"));
      assertEquals(false, attr.hasNamespaceURI());
    } // test9

    void test10()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = parse(SA::construct_from_utf8("<elem stuff:attr='something' poop:attr='fail' xmlns:stuff='http://example.com/stuff'/>"));
      assert(d == 0);
    } // test10

    void test11()
    {
      Arabica::SAX2DOM::Parser<string_type, string_adaptor> parser;
      assert(parser.getFeature(SA::construct_from_utf8("http://xml.org/sax/features/validation")) == false);
      parser.setFeature(SA::construct_from_utf8("http://xml.org/sax/features/validation"), true);
      assert(parser.getFeature(SA::construct_from_utf8("http://xml.org/sax/features/validation")) == true);
      parser.setFeature(SA::construct_from_utf8("http://xml.org/sax/features/validation"), false);
      assert(parser.getFeature(SA::construct_from_utf8("http://xml.org/sax/features/validation")) == false);

      parser.parse(SA::construct_from_utf8("<root attr=\"poop\"><child/></root>"));
    } // test11

    void test12()
    {
      Arabica::SAX2DOM::Parser<string_type, string_adaptor> parser;
      try
      {
        parser.getFeature(SA::construct_from_utf8("made up name"));
        assert(false);
      }
      catch(const Arabica::SAX::SAXNotRecognizedException&)
      {
      } 
    } // test12
};

template<class string_type, class string_adaptor>
TestSuite* SAX2DOMTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test1", &SAX2DOMTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test2", &SAX2DOMTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test3", &SAX2DOMTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test4", &SAX2DOMTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test5", &SAX2DOMTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test6", &SAX2DOMTest<string_type, string_adaptor>::test6));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test7", &SAX2DOMTest<string_type, string_adaptor>::test7));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test8", &SAX2DOMTest<string_type, string_adaptor>::test8));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test9", &SAX2DOMTest<string_type, string_adaptor>::test9));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test10", &SAX2DOMTest<string_type, string_adaptor>::test10));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test11", &SAX2DOMTest<string_type, string_adaptor>::test11));
  suiteOfTests->addTest(new TestCaller<SAX2DOMTest<string_type, string_adaptor> >("test12", &SAX2DOMTest<string_type, string_adaptor>::test12));
  return suiteOfTests;
} // SAX2DOMTest_suite

#endif

