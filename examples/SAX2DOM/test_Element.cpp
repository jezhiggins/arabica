#ifdef _MSC_VER 
#pragma warning(disable: 4786 4250 4503)
#endif
#include "CppUnit/framework/TestCase.h"
#include "CppUnit/framework/TestSuite.h"
#include "CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class ElementTest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    ElementTest(std::string name) :
        TestCase(name) 
    {
    } // ElementTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

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
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Element<std::string> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      DOM::Element<std::string> child = d.createElement("child");
      elem.appendChild(child);
    } // test2

    void test3()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Element<std::string> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      DOM::Attr<std::string> attr = d.createAttribute("attr");
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
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Element<std::string> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      DOM::Attr<std::string> attr = d.createAttribute("attr");
      elem.setAttributeNode(attr);
      assert(elem.getAttributeNode("attr") == attr);
      assert(elem.removeAttributeNode(attr) == attr);
    } // test4

    void test5()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Element<std::string> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);
      d.appendChild(elem);

      assert(elem.hasAttributes() == false);
      assert(elem.hasAttribute("attr") == false);
      elem.setAttribute("attr", "poop");
      assert(elem.hasAttributes() == true);
      assert(elem.hasAttribute("attr") == true);

      DOM::Node<std::string> n = elem.getAttributeNode("attr");
      assert(n.getNodeValue() == "poop");
      assert(elem.setAttributeNode(d.createAttribute("attr")) == n);
    } // test5

    void test6()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Element<std::string> elem = d.createElement("root");
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
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Element<std::string> elem = d.createElement("root");
      elem.setAttribute("attr", "poop");
      elem.appendChild(d.createElement("child"));

      DOM::Element<std::string> e2 = DOM::Element<std::string>(elem.cloneNode(false));
      assert(e2.getOwnerDocument() == d);
      assert(e2.getParentNode() == 0);
      assert(e2.hasAttributes() == true);
      assert(e2.getAttribute("attr") == "poop");
      assert(e2.getFirstChild() == 0);
    } // test7

    void test8()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Element<std::string> elem = d.createElement("root");
      elem.setAttribute("attr", "poop");
      elem.appendChild(d.createElement("child"));

      DOM::Element<std::string> e2 = DOM::Element<std::string>(elem.cloneNode(true));
      assert(e2.getOwnerDocument() == d);
      assert(e2.getParentNode() == 0);
      assert(e2.hasAttributes() == true);
      assert(e2.getAttribute("attr") == "poop");
      assert(e2.getFirstChild().getNodeName() == "child");
    } // test7
};

TestSuite* ElementTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<ElementTest>("test1", &ElementTest::test1));
    suiteOfTests->addTest(new TestCaller<ElementTest>("test2", &ElementTest::test2));
    suiteOfTests->addTest(new TestCaller<ElementTest>("test3", &ElementTest::test3));
    suiteOfTests->addTest(new TestCaller<ElementTest>("test4", &ElementTest::test4));
    suiteOfTests->addTest(new TestCaller<ElementTest>("test5", &ElementTest::test5));
    suiteOfTests->addTest(new TestCaller<ElementTest>("test6", &ElementTest::test6));
    suiteOfTests->addTest(new TestCaller<ElementTest>("test7", &ElementTest::test7));
    suiteOfTests->addTest(new TestCaller<ElementTest>("test8", &ElementTest::test8));
    return suiteOfTests;
} // MathTest_suite

