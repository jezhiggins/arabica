#ifndef ARABICA_TEST_SAX2DOM_CHARACTER_DATA_HPP
#define ARABICA_TEST_SAX2DOM_CHARACTER_DATA_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class CharacterDataTest : public TestCase 
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  typedef string_adaptor SA;

  public: 
    CharacterDataTest(std::string name) :
        TestCase(name) 
    {
    } // CharacterDataTest
    
    void setUp() 
    {
      factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      Arabica::DOM::CharacterData<string_type, string_adaptor> d;
      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreateText()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::CharacterData<string_type, string_adaptor> t = d.createTextNode(SA::construct_from_utf8("some data"));

      assert(t.getData() == SA::construct_from_utf8("some data"));
      assert(t.getNodeName() == SA::construct_from_utf8("#text"));
      assert(t.getNodeValue() == t.getData());

      t.setData(SA::construct_from_utf8("newData"));
      assert(t.getData() == SA::construct_from_utf8("newData"));

      assert(t.getNodeType() == Arabica::DOM::Node_base::TEXT_NODE);
      assert(t.hasAttributes() == false);
      assert(t.getAttributes() == 0);
      assert(t.getChildNodes() == 0);
      assert(t.getFirstChild() == 0);

      try
      {
        t.appendChild(Arabica::DOM::Node<string_type, string_adaptor>());
      } 
      catch(const Arabica::DOM::DOMException&)
      {
      } 

      assert(t.getFirstChild() == 0);

      assert(t.getOwnerDocument() == d);
      assert(t.getParentNode() == 0);
    } // testCreateText

    void testCreateCDATA()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::CharacterData<string_type, string_adaptor> t = d.createCDATASection(SA::construct_from_utf8("some data"));

      assert(t.getData() == SA::construct_from_utf8("some data"));
      assert(t.getNodeName() == SA::construct_from_utf8("#cdata-section"));
      assert(t.getNodeValue() == t.getData());

      t.setData(SA::construct_from_utf8("newData"));
      assert(t.getData() == SA::construct_from_utf8("newData"));

      assert(t.getNodeType() == Arabica::DOM::Node_base::CDATA_SECTION_NODE);
      assert(t.hasAttributes() == false);
      assert(t.getAttributes() == 0);
      assert(t.getChildNodes() == 0);
      assert(t.getFirstChild() == 0);

      try
      {
        t.appendChild(Arabica::DOM::Node<string_type, string_adaptor>());
      } 
      catch(const Arabica::DOM::DOMException&)
      {
      } 

      assert(t.getFirstChild() == 0);

      assert(t.getOwnerDocument() == d);
      assert(t.getParentNode() == 0);
    } // testCreateCDATA

    void testDownCasts()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::CDATASection<string_type, string_adaptor> cd = d.createCDATASection(SA::construct_from_utf8("some data"));

      Arabica::DOM::Text<string_type, string_adaptor> t = cd;
      Arabica::DOM::CharacterData<string_type, string_adaptor> c = t;

      Arabica::DOM::Node<string_type, string_adaptor> n = c;

      assert(c == cd);
      assert(c == t);
      assert(c == n);
      assert(n == c);
      assert(n == cd);
    } // testDownCasts

    void testTextUpCasts()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Node<string_type, string_adaptor> n = d.createTextNode(SA::construct_from_utf8("some data"));

      Arabica::DOM::CharacterData<string_type, string_adaptor> c = Arabica::DOM::CharacterData<string_type, string_adaptor>(n);
      Arabica::DOM::Text<string_type, string_adaptor> t = Arabica::DOM::Text<string_type, string_adaptor>(c);

      assert(c == t);
      assert(c == n);
      assert(n == c);
    } // testTextUpCasts

    void testCDATAUpCasts()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Node<string_type, string_adaptor> n = d.createCDATASection(SA::construct_from_utf8("some data"));

      Arabica::DOM::CharacterData<string_type, string_adaptor> c = Arabica::DOM::CharacterData<string_type, string_adaptor>(n);
      Arabica::DOM::Text<string_type, string_adaptor> t = Arabica::DOM::Text<string_type, string_adaptor>(c);
      Arabica::DOM::CDATASection<string_type, string_adaptor> cd = Arabica::DOM::CDATASection<string_type, string_adaptor>(c);

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

