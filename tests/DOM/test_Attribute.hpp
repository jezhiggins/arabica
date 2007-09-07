#ifndef test_Attr_H
#define test_Attr_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class AttrTest : public TestCase 
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  typedef string_adaptor SA;

  public: 
    AttrTest(std::string name) :
        TestCase(name) 
    {
    } // AttrTest
    
    void setUp() 
    {
      factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

    void test1() 
    {
      Arabica::DOM::Attr<string_type, string_adaptor> d;
      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // test1

    void test2()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttribute(SA::construct_from_utf8("attr"));
      assert(attr.getName() == SA::construct_from_utf8("attr"));
      assert(attr.getNodeName() == SA::construct_from_utf8("attr"));
      assert(attr.getLocalName() == SA::construct_from_utf8(""));
      assert(attr.getNamespaceURI() == SA::construct_from_utf8(""));
      assert(attr.getPrefix() == SA::construct_from_utf8(""));
      assert(attr.hasNamespaceURI() == false);
      assert(attr.hasPrefix() == false);
    } // test2

    void test3()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8("http://attr"), SA::construct_from_utf8("attr:value"));
      assert(attr.getName() == SA::construct_from_utf8("attr:value"));
      assert(attr.getValue() == SA::construct_from_utf8(""));
      assert(attr.getNodeName() == SA::construct_from_utf8("attr:value"));
      assert(attr.getNodeValue() == SA::construct_from_utf8(""));
      assert(attr.getLocalName() == SA::construct_from_utf8("value"));
      assert(attr.getNamespaceURI() == SA::construct_from_utf8("http://attr"));
      assert(attr.getPrefix() == SA::construct_from_utf8("attr"));
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == true);
    } // test3

    void test4()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8("http://attr"), SA::construct_from_utf8("attr"));
      assert(attr.getName() == SA::construct_from_utf8("attr"));
      assert(attr.getValue() == SA::construct_from_utf8(""));
      assert(attr.getNodeName() == SA::construct_from_utf8("attr"));
      assert(attr.getNodeValue() == SA::construct_from_utf8(""));
      assert(attr.getLocalName() == SA::construct_from_utf8("attr"));
      assert(attr.getNamespaceURI() == SA::construct_from_utf8("http://attr"));
      assert(attr.getPrefix() == SA::construct_from_utf8(""));
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == false);
    } // test4

    void test5()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8("http://attr"), SA::construct_from_utf8("attr:value"));

      attr.setPrefix(SA::construct_from_utf8("monkey"));
      assert(attr.getName() == SA::construct_from_utf8("monkey:value"));
      assert(attr.getValue() == SA::construct_from_utf8(""));
      assert(attr.getNodeName() == SA::construct_from_utf8("monkey:value"));
      assert(attr.getNodeValue() == SA::construct_from_utf8(""));
      assert(attr.getLocalName() == SA::construct_from_utf8("value"));
      assert(attr.getNamespaceURI() == SA::construct_from_utf8("http://attr"));
      assert(attr.getPrefix() == SA::construct_from_utf8("monkey"));
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == true);
    } // test5

    void test6()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8("http://attr"), SA::construct_from_utf8("value"));

      attr.setPrefix(SA::construct_from_utf8("monkey"));
      assert(attr.getName() == SA::construct_from_utf8("monkey:value"));
      assert(attr.getValue() == SA::construct_from_utf8(""));
      assert(attr.getNodeName() == SA::construct_from_utf8("monkey:value"));
      assert(attr.getNodeValue() == SA::construct_from_utf8(""));
      assert(attr.getLocalName() == SA::construct_from_utf8("value"));
      assert(attr.getNamespaceURI() == SA::construct_from_utf8("http://attr"));
      assert(attr.getPrefix() == SA::construct_from_utf8("monkey"));
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == true);
    } // test6

    void test7()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8("http://www.w3.org/2000/xmlns/"), SA::construct_from_utf8("xmlns"));

      assert(attr.getName() == SA::construct_from_utf8("xmlns"));
      assert(attr.getValue() == SA::construct_from_utf8(""));
      assert(attr.getNodeName() == SA::construct_from_utf8("xmlns"));
      assert(attr.getNodeValue() == SA::construct_from_utf8(""));
      assert(attr.getLocalName() == SA::construct_from_utf8("xmlns"));
      assert(attr.getNamespaceURI() == SA::construct_from_utf8("http://www.w3.org/2000/xmlns/"));
      assert(attr.getPrefix() == SA::construct_from_utf8(""));
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == false);
    } // test7

    void test8()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr;
      
      try {
        attr = d.createAttributeNS(SA::construct_from_utf8("ppopopop"), SA::construct_from_utf8("xmlns"));
      }
      catch(const Arabica::DOM::DOMException&) { }

      assert(attr == 0);
    } // test8

    void test9()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr;
      
      try {
        attr = d.createAttributeNS(SA::construct_from_utf8("ahuafh"), SA::construct_from_utf8("xmlns:billy"));
      }
      catch(const Arabica::DOM::DOMException&) { }

      assert(attr == 0);
    } // test9

    void test10()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8("http://www.w3.org/2000/xmlns/"), SA::construct_from_utf8("nothing:much"));

      try {
        attr.setPrefix(SA::construct_from_utf8("xmlns"));
      }
      catch(const Arabica::DOM::DOMException&) { }

      assert(attr.getPrefix() == SA::construct_from_utf8("xmlns"));
    } // test10

    void test11()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8("charles"), SA::construct_from_utf8("nothing:much"));

      try {
        attr.setPrefix(SA::construct_from_utf8("xmlns"));
      }
      catch(const Arabica::DOM::DOMException&) { }

      assert(attr.getPrefix() == SA::construct_from_utf8("nothing"));
    } // test11

    void test12()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8(""), SA::construct_from_utf8("much"));

      try {
        attr.setPrefix(SA::construct_from_utf8("charles"));
      }
      catch(const Arabica::DOM::DOMException&) { }

      assert(attr.hasPrefix() == false);
    } // test12

    void test13()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr;
      
      try {
        attr = d.createAttributeNS(SA::construct_from_utf8(""), SA::construct_from_utf8("trouser:pants"));
      }
      catch(const Arabica::DOM::DOMException&) { }

      assert(attr == 0);
    } // test13

    void test14()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttributeNS(SA::construct_from_utf8("http://www.w3.org/2000/xmlns/"), SA::construct_from_utf8("xmlns"));

      assert(attr.getName() == SA::construct_from_utf8("xmlns"));
      assert(attr.getValue() == SA::construct_from_utf8(""));
      assert(attr.getNodeName() == SA::construct_from_utf8("xmlns"));
      assert(attr.getNodeValue() == SA::construct_from_utf8(""));
      assert(attr.getLocalName() == SA::construct_from_utf8("xmlns"));
      assert(attr.getNamespaceURI() == SA::construct_from_utf8("http://www.w3.org/2000/xmlns/"));
      assert(attr.getPrefix() == SA::construct_from_utf8(""));
      assert(attr.hasNamespaceURI() == true);
      assert(attr.hasPrefix() == false);

      string_type norb = SA::construct_from_utf8("norb");
      attr.setValue(norb);
      assert(attr.getValue() == norb);
      assert(attr.getNodeValue() == norb);

      string_type porg = SA::construct_from_utf8("porg");
      attr.setNodeValue(porg);
      assert(attr.getValue() == porg);
      assert(attr.getNodeValue() == porg);
    } // test14

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
  suiteOfTests->addTest(new TestCaller<AttrTest<string_type, string_adaptor> >("test14", &AttrTest<string_type, string_adaptor>::test14));
  return suiteOfTests;
} // AttrTest_suite


#endif

