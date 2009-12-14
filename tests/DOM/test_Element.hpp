#ifndef test_Element_H
#define test_Element_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class ElementTest : public TestCase 
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  typedef string_adaptor SA;

  public: 
    ElementTest(std::string name) :
        TestCase(name) 
    {
    } // ElementTest
    
    void setUp() 
    {
      factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

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
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.createElement(SA::construct_from_utf8("root"));
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      Arabica::DOM::Element<string_type, string_adaptor> child = d.createElement(SA::construct_from_utf8("child"));
      elem.appendChild(child);
    } // test2

    void test3()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.createElement(SA::construct_from_utf8("root"));
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttribute(SA::construct_from_utf8("attr"));
      attr.setNodeValue(SA::construct_from_utf8("trousers"));
      try
      {
        elem.appendChild(attr);
      }
      catch(const Arabica::DOM::DOMException&) { }
      assert(elem.getFirstChild() == 0);
    } // test3

    void test4()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.createElement(SA::construct_from_utf8("root"));
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      Arabica::DOM::Attr<string_type, string_adaptor> attr = d.createAttribute(SA::construct_from_utf8("attr"));
      elem.setAttributeNode(attr);
      assert(elem.getAttributeNode(SA::construct_from_utf8("attr")) == attr);
      assert(elem.removeAttributeNode(attr) == attr);

      Arabica::DOM::Attr<string_type, string_adaptor> attrNS = d.createAttributeNS(SA::construct_from_utf8("ns"), SA::construct_from_utf8("attr"));
      elem.setAttributeNodeNS(attrNS);
      assert(elem.getAttributeNodeNS(SA::construct_from_utf8("ns"), SA::construct_from_utf8("attr")) == attrNS);
      assert(elem.removeAttributeNode(attrNS) == attrNS);
    } // test4

    void test5()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.createElement(SA::construct_from_utf8("root"));
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      assert(elem.hasAttributes() == false);
      assert(elem.hasAttribute(SA::construct_from_utf8("attr")) == false);
      elem.setAttribute(SA::construct_from_utf8("attr"), SA::construct_from_utf8("poop"));
      assert(elem.hasAttributes() == true);
      assert(elem.hasAttribute(SA::construct_from_utf8("attr")) == true);

      Arabica::DOM::Node<string_type, string_adaptor> n = elem.getAttributeNode(SA::construct_from_utf8("attr"));
      assert(n.getNodeValue() == SA::construct_from_utf8("poop"));
      assert(elem.setAttributeNode(d.createAttribute(SA::construct_from_utf8("attr"))) == n);
    } // test5

    void test6()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.createElement(SA::construct_from_utf8("root"));
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      assert(elem.hasAttributes() == false);
      assert(elem.hasAttribute(SA::construct_from_utf8("attr")) == false);
      elem.setAttribute(SA::construct_from_utf8("attr"), SA::construct_from_utf8("poop"));
      assert(elem.hasAttributes() == true);
      assert(elem.hasAttribute(SA::construct_from_utf8("attr")) == true);
      elem.removeAttribute(SA::construct_from_utf8("attr"));
      assert(elem.hasAttributes() == false);
      assert(elem.hasAttribute(SA::construct_from_utf8("attr")) == false);
    } // test6

    void test7()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.createElement(SA::construct_from_utf8("root"));
      elem.setAttribute(SA::construct_from_utf8("attr"), SA::construct_from_utf8("poop"));
      elem.appendChild(d.createElement(SA::construct_from_utf8("child")));

      Arabica::DOM::Element<string_type, string_adaptor> e2 = Arabica::DOM::Element<string_type, string_adaptor>(elem.cloneNode(false));
      assert(e2.getOwnerDocument() == d);
      assert(e2.getParentNode() == 0);
      assert(e2.hasAttributes() == true);
      assert(e2.getAttribute(SA::construct_from_utf8("attr")) == SA::construct_from_utf8("poop"));
      assert(e2.getFirstChild() == 0);
    } // test7

    void test8()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Element<string_type, string_adaptor> elem = d.createElement(SA::construct_from_utf8("root"));
      elem.setAttribute(SA::construct_from_utf8("attr"), SA::construct_from_utf8("poop"));
      elem.appendChild(d.createElement(SA::construct_from_utf8("child")));

      Arabica::DOM::Element<string_type, string_adaptor> e2 = Arabica::DOM::Element<string_type, string_adaptor>(elem.cloneNode(true));
      assert(e2.getOwnerDocument() == d);
      assert(e2.getParentNode() == 0);
      assert(e2.hasAttributes() == true);
      assert(e2.getAttribute(SA::construct_from_utf8("attr")) == SA::construct_from_utf8("poop"));
      assert(e2.getFirstChild().getNodeName() == SA::construct_from_utf8("child"));
    } // test
};

template<class string_type, class string_adaptor>
TestSuite* ElementTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<ElementTest<string_type, string_adaptor> >("test1", &ElementTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<ElementTest<string_type, string_adaptor> >("test2", &ElementTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<ElementTest<string_type, string_adaptor> >("test3", &ElementTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<ElementTest<string_type, string_adaptor> >("test4", &ElementTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<ElementTest<string_type, string_adaptor> >("test5", &ElementTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<ElementTest<string_type, string_adaptor> >("test6", &ElementTest<string_type, string_adaptor>::test6));
  suiteOfTests->addTest(new TestCaller<ElementTest<string_type, string_adaptor> >("test7", &ElementTest<string_type, string_adaptor>::test7));
  suiteOfTests->addTest(new TestCaller<ElementTest<string_type, string_adaptor> >("test8", &ElementTest<string_type, string_adaptor>::test8));
  return suiteOfTests;
} // ElementTest_suite

#endif

