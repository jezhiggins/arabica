#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class AttrTest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    AttrTest(std::string name) :
        TestCase(name) 
    {
    } // AttrTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void test1() 
    {
      DOM::Attr<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // test1

    void test2()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttribute("attr");
      assert(attr.getName() == "attr");
      assert(attr.getNodeName() == "attr");
      assert(attr.getLocalName() == "");
      assert(attr.getNamespaceURI() == "");
      assert(attr.getPrefix() == "");
      assert(attr.hasNamespaceURI() == false);
      assert(attr.hasPrefix() == false);
    } // test2

    void test3()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttributeNS("http://attr", "attr:value");
      assert(attr.getName() == "attr:value");
      assert(attr.getValue() == "");
      assert(attr.getNodeName() == "attr:value");
      assert(attr.getNodeValue() == "");
      assert(attr.getLocalName() == "value");
      assert(attr.getNamespaceURI() == "http://attr");
      assert(attr.getPrefix() == "attr");
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == true);
    } // test3

    void test4()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttributeNS("http://attr", "attr");
      assert(attr.getName() == "attr");
      assert(attr.getValue() == "");
      assert(attr.getNodeName() == "attr");
      assert(attr.getNodeValue() == "");
      assert(attr.getLocalName() == "attr");
      assert(attr.getNamespaceURI() == "http://attr");
      assert(attr.getPrefix() == "");
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == false);
    } // test4

    void test5()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttributeNS("http://attr", "attr:value");

      attr.setPrefix("monkey");
      assert(attr.getName() == "monkey:value");
      assert(attr.getValue() == "");
      assert(attr.getNodeName() == "monkey:value");
      assert(attr.getNodeValue() == "");
      assert(attr.getLocalName() == "value");
      assert(attr.getNamespaceURI() == "http://attr");
      assert(attr.getPrefix() == "monkey");
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == true);
    } // test5

    void test6()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttributeNS("http://attr", "value");

      attr.setPrefix("monkey");
      assert(attr.getName() == "monkey:value");
      assert(attr.getValue() == "");
      assert(attr.getNodeName() == "monkey:value");
      assert(attr.getNodeValue() == "");
      assert(attr.getLocalName() == "value");
      assert(attr.getNamespaceURI() == "http://attr");
      assert(attr.getPrefix() == "monkey");
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == true);
    } // test6

    void test7()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns");

      assert(attr.getName() == "xmlns");
      assert(attr.getValue() == "");
      assert(attr.getNodeName() == "xmlns");
      assert(attr.getNodeValue() == "");
      assert(attr.getLocalName() == "xmlns");
      assert(attr.getNamespaceURI() == "http://www.w3.org/2000/xmlns/");
      assert(attr.getPrefix() == "");
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == false);
    } // test7

    void test8()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr;
      
      try {
        attr = d.createAttributeNS("ppopopop", "xmlns");
      }
      catch(const DOM::DOMException&) { }

      assert(attr == 0);
    } // test8

    void test9()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr;
      
      try {
        attr = d.createAttributeNS("ahuafh", "xmlns:billy");
      }
      catch(const DOM::DOMException&) { }

      assert(attr == 0);
    } // test9

    void test10()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttributeNS("http://www.w3.org/2000/xmlns/", "nothing:much");

      try {
        attr.setPrefix("xmlns");
      }
      catch(const DOM::DOMException&) { }

      assert(attr.getPrefix() == "xmlns");
    } // test10

    void test11()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttributeNS("charles", "nothing:much");

      try {
        attr.setPrefix("xmlns");
      }
      catch(const DOM::DOMException&) { }

      assert(attr.getPrefix() == "nothing");
    } // test11

    void test12()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr = d.createAttributeNS("", "much");

      try {
        attr.setPrefix("charles");
      }
      catch(const DOM::DOMException&) { }

      assert(attr.hasPrefix() == false);
    } // test12

    void test13()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Attr<std::string> attr;
      
      try {
        attr = d.createAttributeNS("", "trouser:pants");
      }
      catch(const DOM::DOMException&) { }

      assert(attr == 0);
    } // test13

};

TestSuite* AttrTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<AttrTest>("test3", &AttrTest::test3));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test4", &AttrTest::test4));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test5", &AttrTest::test5));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test6", &AttrTest::test6));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test7", &AttrTest::test7));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test8", &AttrTest::test8));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test9", &AttrTest::test9));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test10", &AttrTest::test10));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test11", &AttrTest::test11));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test12", &AttrTest::test12));
  suiteOfTests->addTest(new TestCaller<AttrTest>("test13", &AttrTest::test13));
  return suiteOfTests;
} // MathTest_suite

