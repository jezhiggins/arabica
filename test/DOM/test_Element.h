#ifndef test_Element_H
#define test_Element_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

template<class string_type, class string_adaptor>
class ElementTest : public TestCase 
{
  DOM::DOMImplementation<string_type> factory;

  public: 
    ElementTest(std::string name) :
        TestCase(name) 
    {
    } // ElementTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<string_type>::getDOMImplementation();
    } // setUp

    void test1() 
    {
      DOM::Element<string_type> d;
      DOM::Node<string_type> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // test1

    void test2()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Element<string_type> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      DOM::Element<string_type> child = d.createElement("child");
      elem.appendChild(child);
    } // test2

    void test3()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Element<string_type> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      DOM::Attr<string_type> attr = d.createAttribute("attr");
      attr.setNodeValue("trousers");
      try
      {
        elem.appendChild(attr);
      }
      catch(const DOM::DOMException&) { }
      assert(elem.getFirstChild() == 0);
    } // test3

    void test4()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Element<string_type> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      DOM::Attr<string_type> attr = d.createAttribute("attr");
      elem.setAttributeNode(attr);
      assert(elem.getAttributeNode("attr") == attr);
      assert(elem.removeAttributeNode(attr) == attr);
    } // test4

    void test5()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Element<string_type> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      assert(elem.hasAttributes() == false);
      assert(elem.hasAttribute("attr") == false);
      elem.setAttribute("attr", "poop");
      assert(elem.hasAttributes() == true);
      assert(elem.hasAttribute("attr") == true);

      DOM::Node<string_type> n = elem.getAttributeNode("attr");
      assert(n.getNodeValue() == "poop");
      assert(elem.setAttributeNode(d.createAttribute("attr")) == n);
    } // test5

    void test6()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Element<string_type> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      assert(elem.hasAttributes() == false);
      assert(elem.hasAttribute("attr") == false);
      elem.setAttribute("attr", "poop");
      assert(elem.hasAttributes() == true);
      assert(elem.hasAttribute("attr") == true);
      elem.removeAttribute("attr");
      assert(elem.hasAttributes() == false);
      assert(elem.hasAttribute("attr") == false);
    } // test6

    void test7()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Element<string_type> elem = d.createElement("root");
      elem.setAttribute("attr", "poop");
      elem.appendChild(d.createElement("child"));

      DOM::Element<string_type> e2 = DOM::Element<string_type>(elem.cloneNode(false));
      assert(e2.getOwnerDocument() == d);
      assert(e2.getParentNode() == 0);
      assert(e2.hasAttributes() == true);
      assert(e2.getAttribute("attr") == "poop");
      assert(e2.getFirstChild() == 0);
    } // test7

    void test8()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Element<string_type> elem = d.createElement("root");
      elem.setAttribute("attr", "poop");
      elem.appendChild(d.createElement("child"));

      DOM::Element<string_type> e2 = DOM::Element<string_type>(elem.cloneNode(true));
      assert(e2.getOwnerDocument() == d);
      assert(e2.getParentNode() == 0);
      assert(e2.hasAttributes() == true);
      assert(e2.getAttribute("attr") == "poop");
      assert(e2.getFirstChild().getNodeName() == "child");
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

