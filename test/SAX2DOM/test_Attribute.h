#ifndef test_Attr_H
#define test_Attr_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

template<class string_type, class string_adaptor>
class AttrTest : public TestCase 
{
  DOM::DOMImplementation<string_type> factory;

  public: 
    AttrTest(std::string name) :
        TestCase(name) 
    {
    } // AttrTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<string_type>::getDOMImplementation();
    } // setUp

    void test1() 
    {
      DOM::Attr<string_type> d;
      DOM::Node<string_type> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // test1

    void test2()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttribute("attr");
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
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttributeNS("http://attr", "attr:value");
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
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttributeNS("http://attr", "attr");
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
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttributeNS("http://attr", "attr:value");

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
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttributeNS("http://attr", "value");

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
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns");

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
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr;
      
      try {
        attr = d.createAttributeNS("ppopopop", "xmlns");
      }
      catch(const DOM::DOMException&) { }

      assert(attr == 0);
    } // test8

    void test9()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr;
      
      try {
        attr = d.createAttributeNS("ahuafh", "xmlns:billy");
      }
      catch(const DOM::DOMException&) { }

      assert(attr == 0);
    } // test9

    void test10()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttributeNS("http://www.w3.org/2000/xmlns/", "nothing:much");

      try {
        attr.setPrefix("xmlns");
      }
      catch(const DOM::DOMException&) { }

      assert(attr.getPrefix() == "xmlns");
    } // test10

    void test11()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttributeNS("charles", "nothing:much");

      try {
        attr.setPrefix("xmlns");
      }
      catch(const DOM::DOMException&) { }

      assert(attr.getPrefix() == "nothing");
    } // test11

    void test12()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr = d.createAttributeNS("", "much");

      try {
        attr.setPrefix("charles");
      }
      catch(const DOM::DOMException&) { }

      assert(attr.hasPrefix() == false);
    } // test12

    void test13()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Attr<string_type> attr;
      
      try {
        attr = d.createAttributeNS("", "trouser:pants");
      }
      catch(const DOM::DOMException&) { }

      assert(attr == 0);
    } // test13

};

template<class string_type, class string_adaptor>
TestSuite* AttrTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test1", &AttrTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test2", &AttrTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test3", &AttrTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test4", &AttrTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test5", &AttrTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test6", &AttrTest<string_type, string_adaptor>::test6));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test7", &AttrTest<string_type, string_adaptor>::test7));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test8", &AttrTest<string_type, string_adaptor>::test8));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test9", &AttrTest<string_type, string_adaptor>::test9));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test10", &AttrTest<string_type, string_adaptor>::test10));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test11", &AttrTest<string_type, string_adaptor>::test11));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test12", &AttrTest<string_type, string_adaptor>::test12));
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test13", &AttrTest<string_type, string_adaptor>::test13));
  return suiteOfTests;
} // AttrTest_suite


#endif

