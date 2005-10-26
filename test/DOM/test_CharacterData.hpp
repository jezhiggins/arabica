#ifndef ARABICA_TEST_SAX2DOM_CHARACTER_DATA_HPP
#define ARABICA_TEST_SAX2DOM_CHARACTER_DATA_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

template<class string_type, class string_adaptor>
class CharacterDataTest : public TestCase 
{
  DOM::DOMImplementation<string_type> factory;

  public: 
    CharacterDataTest(std::string name) :
        TestCase(name) 
    {
    } // CharacterDataTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<string_type>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::CharacterData<string_type> d;
      DOM::Node<string_type> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreateText()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::CharacterData<string_type> t = d.createTextNode("some data");

      assert(t.getData() == "some data");
      assert(t.getNodeName() == "#text");
      assert(t.getNodeValue() == t.getData());

      t.setData("newData");
      assert(t.getData() == "newData");

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
    } // testCreateText

    void testCreateCDATA()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::CharacterData<string_type> t = d.createCDATASection("some data");

      assert(t.getData() == "some data");
      assert(t.getNodeName() == "#cdata-section");
      assert(t.getNodeValue() == t.getData());

      t.setData("newData");
      assert(t.getData() == "newData");

      assert(t.getNodeType() == DOM::Node<string_type>::CDATA_SECTION_NODE);
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
    } // testCreateCDATA

    void testDownCasts()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::CDATASection<string_type> cd = d.createCDATASection("some data");

      DOM::Text<string_type> t = cd;
      DOM::CharacterData<string_type> c = t;

      DOM::Node<string_type> n = c;

      assert(c == cd);
      assert(c == t);
      assert(c == n);
      assert(n == c);
      assert(n == cd);
    } // testDownCasts

    void testTextUpCasts()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Node<string_type> n = d.createTextNode("some data");

      DOM::CharacterData<string_type> c = DOM::CharacterData<string_type>(n);
      DOM::Text<string_type> t = DOM::Text<string_type>(c);

      assert(c == t);
      assert(c == n);
      assert(n == c);
    } // testTextUpCasts

    void testCDATAUpCasts()
    {
      DOM::Document<string_type> d = factory.createDocument("","", 0);
      DOM::Node<string_type> n = d.createCDATASection("some data");

      DOM::CharacterData<string_type> c = DOM::CharacterData<string_type>(n);
      DOM::Text<string_type> t = DOM::Text<string_type>(c);
      DOM::CDATASection<string_type> cd = DOM::CDATASection<string_type>(c);

      assert(c == cd);
      assert(c == t);
      assert(c == n);
      assert(n == c);
      assert(n == cd);
    } // testCDATAUpCasts
};

template<class string_type, class string_adaptor>
TestSuite* CharacterDataTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<CharacterDataTest<string_type, string_adaptor> >("testNull", &CharacterDataTest<string_type, string_adaptor>::testNull));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest<string_type, string_adaptor> >("testCreateText", &CharacterDataTest<string_type, string_adaptor>::testCreateText));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest<string_type, string_adaptor> >("testCreateCDATA", &CharacterDataTest<string_type, string_adaptor>::testCreateCDATA));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest<string_type, string_adaptor> >("testDownCasts", &CharacterDataTest<string_type, string_adaptor>::testDownCasts));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest<string_type, string_adaptor> >("testTextUpCasts", &CharacterDataTest<string_type, string_adaptor>::testTextUpCasts));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest<string_type, string_adaptor> >("testCDATAUpCasts", &CharacterDataTest<string_type, string_adaptor>::testCDATAUpCasts));
    return suiteOfTests;
} // CharacterDataTest_suite

#endif