
#pragma warning(disable: 4786 4250 4503)
#include "CppUnit/framework/TestCase.h"
#include "CppUnit/framework/TestSuite.h"
#include "CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class DocumentFragmentTest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    DocumentFragmentTest(std::string name) :
        TestCase(name) 
    {
    } // DocumentFragmentTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void test1() 
    {
      DOM::DocumentFragment<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // test1

    void test2()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::DocumentFragment<std::string> frag = d.createDocumentFragment();

      frag.appendChild(d.createElement("child"));
      frag.appendChild(d.createElement("child2"));
      frag.appendChild(d.createElement("child3"));

      assert(frag.getChildNodes().getLength() == 3);
    } // test2

    void test3()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::DocumentFragment<std::string> frag = d.createDocumentFragment();
      frag.appendChild(d.createElement("child"));
      frag.appendChild(d.createElement("child2"));
      frag.appendChild(d.createElement("child3"));

      DOM::Element<std::string> elem = d.createElement("root");
      elem.appendChild(frag);
      assert(elem.getChildNodes().getLength() == 3);
      assert(elem.getFirstChild().getNodeName() == "child");
      assert(elem.getLastChild().getNodeName() == "child3");
      assert(frag.getChildNodes().getLength() == 0);
    } // test3

    void test4()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::DocumentFragment<std::string> frag = d.createDocumentFragment();
      frag.appendChild(d.createElement("child"));
      frag.appendChild(d.createElement("child2"));
      frag.appendChild(d.createElement("child3"));

      DOM::Element<std::string> elem = d.createElement("root");
      elem.appendChild(d.createElement("t"));
      assert(elem.getChildNodes().getLength() == 1);

      elem.replaceChild(frag, elem.getFirstChild());
      assert(elem.getChildNodes().getLength() == 3);
      assert(elem.getFirstChild().getNodeName() == "child");
      assert(elem.getLastChild().getNodeName() == "child3");
      assert(frag.getChildNodes().getLength() == 0);
    } // test4

    void test5()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::DocumentFragment<std::string> frag = d.createDocumentFragment();
      frag.appendChild(d.createElement("child"));
      frag.appendChild(d.createElement("child2"));
      frag.appendChild(d.createElement("child3"));

      DOM::Element<std::string> elem = d.createElement("root");
      elem.appendChild(d.createElement("t"));
      assert(elem.getChildNodes().getLength() == 1);

      elem.insertBefore(frag, elem.getFirstChild());
      assert(elem.getChildNodes().getLength() == 4);
      assert(elem.getFirstChild().getNodeName() == "child");
      assert(elem.getLastChild().getNodeName() == "t");
      assert(frag.getChildNodes().getLength() == 0);
    } // test5
};

TestSuite* DocumentFragmentTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<DocumentFragmentTest>("test1", &DocumentFragmentTest::test1));
    suiteOfTests->addTest(new TestCaller<DocumentFragmentTest>("test2", &DocumentFragmentTest::test2));
    suiteOfTests->addTest(new TestCaller<DocumentFragmentTest>("test3", &DocumentFragmentTest::test3));
    suiteOfTests->addTest(new TestCaller<DocumentFragmentTest>("test4", &DocumentFragmentTest::test4));
    suiteOfTests->addTest(new TestCaller<DocumentFragmentTest>("test5", &DocumentFragmentTest::test5));
    return suiteOfTests;
} // MathTest_suite

