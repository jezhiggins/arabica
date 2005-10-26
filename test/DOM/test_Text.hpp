#ifndef ARABICA_TEST_SAX2DOM_TEXT_HPP
#define ARABICA_TEST_SAX2DOM_TEXT_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

template<class string_type, class string_adaptor>
class TextTest : public TestCase 
{
  DOM::DOMImplementation<string_type> factory;

  public: 
    TextTest(std::string name) :
        TestCase(name) 
    {
    } // TextTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<string_type>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::Text<string_type> d;
      DOM::Node<string_type> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Text<string_type> t = d.createTextNode("some data");

      assert(t.getData() == "some data");
      assert(t.getNodeName() == "#text");
      assert(t.getNodeValue() == t.getData());

      t.setData("newData");
      assert(t.getData() == "newData");
    } // testCreate

    void testConversion()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Text<string_type> t = d.createTextNode("some data");

      DOM::Node<string_type> n;

      assert(n != t);

      n = t;
      assert(n == t);

      DOM::Text<string_type> t2;

      assert(n != t2);

      t2 = DOM::Text<string_type>(n);
      assert(t == t2);
      assert(n == t2);

      DOM::Text<string_type> t3;
      t3 = t2;
      assert(t3 == t2);
      assert(t3 == t);

      DOM::Comment<string_type> c = d.createComment("woo");
      try {
        t = DOM::Text<string_type>(c);
        assertImplementation(false, "converted comment to text");
      } 
      catch(const std::bad_cast&) {
      }
    } // testConverstion

    void testEverythingElse()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Text<string_type> t = d.createTextNode("some data");

      assert(t.getNodeType() == DOM::Node<string_type>::TEXT_NODE);
      assert(t.hasAttributes() == false);
      assert(t.getAttributes() == 0);
      assert(t.getChildNodes() == 0);
      assert(t.getFirstChild() == 0);

      try
      {
        t.appendChild(DOM::Node<string_type>());
      } 
      catch(const DOM::DOMException&)
      {
      } 

      assert(t.getFirstChild() == 0);

      assert(t.getOwnerDocument() == d);
      assert(t.getParentNode() == 0);
    } // 
};

template<class string_type, class string_adaptor>
TestSuite* TextTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testNull", &TextTest<string_type, string_adaptor>::testNull));
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testCreate", &TextTest<string_type, string_adaptor>::testCreate));
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testConversion", &TextTest<string_type, string_adaptor>::testConversion));
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testEverythingElse", &TextTest<string_type, string_adaptor>::testEverythingElse));
    return suiteOfTests;
} // TextTest_suite

#endif