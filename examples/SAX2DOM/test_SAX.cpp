#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include "CppUnit/framework/TestCase.h"
#include "CppUnit/framework/TestSuite.h"
#include "CppUnit/framework/TestCaller.h"
#include <sstream>
#include <DOM/SAX2DOM/SAX2DOM.h>

class SAXTest : public TestCase 
{
  public: 
    SAXTest(std::string name) :
        TestCase(name) 
    {
    } // SAXTest
    
    void setUp() 
    {
    } // setUp

    DOM::Document<std::string> parse(std::string str)
    {
      std::stringstream ss;
      ss << str;

      SAX::InputSource is(ss);
      SAX2DOM::Parser<std::string> parser;
      parser.parse(is);       
      return parser.getDocument();
    } // parse

    void test1() 
    {
      DOM::Element<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // test1

    void test2()
    {
      DOM::Document<std::string> d = parse("<root/>");
      DOM::Element<std::string> elem = d.getDocumentElement();
      assert(elem.getParentNode() == d);
      assert(elem.getOwnerDocument() == d);
    } // test2

    void test3()
    {
      DOM::Document<std::string> d = parse("<root attr=\"poop\"/>");
      DOM::Element<std::string> elem = d.getDocumentElement();
      assert(elem.hasAttributes() == true);
      assert(elem.getAttribute("attr") == "poop");
    } // test3

    void test4()
    {
      DOM::Document<std::string> d = parse("<root><child attr=\"poop\"/></root>");
      DOM::Element<std::string> elem = DOM::Element<std::string>(d.getDocumentElement().getFirstChild());
      assertEquals("child", elem.getNodeName());
      assertEquals(true, elem.hasAttributes());
      assertEquals("poop", elem.getAttribute("attr"));
    } // test4

    void test5()
    {
      DOM::Document<std::string> d = parse("<stuff:elem attr='something' xmlns:stuff='http://example.com/stuff'/>");
      DOM::Element<std::string> elem = d.getDocumentElement();
      assertEquals(true, elem.hasNamespaceURI());
      assertEquals("http://example.com/stuff", elem.getNamespaceURI());

      DOM::Attr<std::string> attr = elem.getAttributeNode("attr");
      assertEquals(false, attr.hasNamespaceURI());
    } // test5

    void test6()
    {
      DOM::Document<std::string> d = parse("<stuff:elem stuff:attr='something' xmlns:stuff='http://example.com/stuff'/>");
      DOM::Element<std::string> elem = d.getDocumentElement();
      assertEquals(true, elem.hasNamespaceURI());
      assertEquals("http://example.com/stuff", elem.getNamespaceURI());

      DOM::Attr<std::string> attr = elem.getAttributeNodeNS("http://example.com/stuff", "attr");
      assertEquals(true, attr.hasNamespaceURI());
      assertEquals("http://example.com/stuff", attr.getNamespaceURI());
    } // test6

    void test7()
    {
      DOM::Document<std::string> d = parse("<elem stuff:attr='something' xmlns:stuff='http://example.com/stuff'/>");
      DOM::Element<std::string> elem = d.getDocumentElement();
      assertEquals(false, elem.hasNamespaceURI());

      DOM::Attr<std::string> attr = elem.getAttributeNodeNS("http://example.com/stuff", "attr");
      assertEquals(true, attr.hasNamespaceURI());
      assertEquals("http://example.com/stuff", attr.getNamespaceURI());
    } // test7

    void test8()
    {
      DOM::Document<std::string> d = parse("<root attr=\"poop\"><child/></root>");
      DOM::Element<std::string> elem = d.getDocumentElement();

      DOM::Element<std::string> e2 = DOM::Element<std::string>(elem.cloneNode(true));
      assert(e2.getOwnerDocument() == d);
      assert(e2.getParentNode() == 0);
      assert(e2.hasAttributes() == true);
      assert(e2.getAttribute("attr") == "poop");
      assert(e2.getFirstChild().getNodeName() == "child");
    } // test8

    void test9()
    {
      DOM::Document<std::string> d = parse("<elem attr='something' xmlns:stuff='http://example.com/stuff'/>");
      DOM::Element<std::string> elem = d.getDocumentElement();
      assertEquals(false, elem.hasNamespaceURI());

      DOM::Attr<std::string> attr = elem.getAttributeNode("attr");
      assertEquals(false, attr.hasNamespaceURI());
    } // test9

    void test10()
    {
      DOM::Document<std::string> d = parse("<elem stuff:attr='something' poop:attr='fail' xmlns:stuff='http://example.com/stuff'/>");
      assert(d == 0);
    } // test10
};

TestSuite* SAXTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<SAXTest>("test1", &SAXTest::test1));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test2", &SAXTest::test2));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test3", &SAXTest::test3));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test4", &SAXTest::test4));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test5", &SAXTest::test5));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test6", &SAXTest::test6));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test7", &SAXTest::test7));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test8", &SAXTest::test8));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test9", &SAXTest::test9));
    suiteOfTests->addTest(new TestCaller<SAXTest>("test10", &SAXTest::test10));
    return suiteOfTests;
} // MathTest_suite

