#ifndef test_DocumentFragment_H
#define test_DocumentFragment_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

template<class string_type, class string_adaptor>
class DocumentFragmentTest : public TestCase 
{
  DOM::DOMImplementation<string_type> factory;

  public: 
    DocumentFragmentTest(std::string name) :
        TestCase(name) 
    {
    } // DocumentFragmentTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<string_type>::getDOMImplementation();
    } // setUp

    void test1() 
    {
      DOM::DocumentFragment<string_type> d;
      DOM::Node<string_type> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // test1

    void test2()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::DocumentFragment<string_type> frag = d.createDocumentFragment();

      frag.appendChild(d.createElement("child"));
      frag.appendChild(d.createElement("child2"));
      frag.appendChild(d.createElement("child3"));

      assert(frag.getChildNodes().getLength() == 3);
    } // test2

    void test3()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::DocumentFragment<string_type> frag = d.createDocumentFragment();
      frag.appendChild(d.createElement("child"));
      frag.appendChild(d.createElement("child2"));
      frag.appendChild(d.createElement("child3"));

      DOM::Element<string_type> elem = d.createElement("root");
      elem.appendChild(frag);
      assert(elem.getChildNodes().getLength() == 3);
      assert(elem.getFirstChild().getNodeName() == "child");
      assert(elem.getLastChild().getNodeName() == "child3");
      assert(frag.getChildNodes().getLength() == 0);
    } // test3

    void test4()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::DocumentFragment<string_type> frag = d.createDocumentFragment();
      frag.appendChild(d.createElement("child"));
      frag.appendChild(d.createElement("child2"));
      frag.appendChild(d.createElement("child3"));

      DOM::Element<string_type> elem = d.createElement("root");
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
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::DocumentFragment<string_type> frag = d.createDocumentFragment();
      frag.appendChild(d.createElement("child"));
      frag.appendChild(d.createElement("child2"));
      frag.appendChild(d.createElement("child3"));

      DOM::Element<string_type> elem = d.createElement("root");
      elem.appendChild(d.createElement("t"));
      assert(elem.getChildNodes().getLength() == 1);

      elem.insertBefore(frag, elem.getFirstChild());
      assert(elem.getChildNodes().getLength() == 4);
      assert(elem.getFirstChild().getNodeName() == "child");
      assert(elem.getLastChild().getNodeName() == "t");
      assert(frag.getChildNodes().getLength() == 0);
    } // test5
};

template<class string_type, class string_adaptor>
TestSuite* DocumentFragmentTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<DocumentFragmentTest<string_type, string_adaptor> >("test1", &DocumentFragmentTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<DocumentFragmentTest<string_type, string_adaptor> >("test2", &DocumentFragmentTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<DocumentFragmentTest<string_type, string_adaptor> >("test3", &DocumentFragmentTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<DocumentFragmentTest<string_type, string_adaptor> >("test4", &DocumentFragmentTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<DocumentFragmentTest<string_type, string_adaptor> >("test5", &DocumentFragmentTest<string_type, string_adaptor>::test5));
  return suiteOfTests;
} // DocumentFragmentTest_suite

#endif

