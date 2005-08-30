#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class CharacterDataTest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    CharacterDataTest(std::string name) :
        TestCase(name) 
    {
    } // CharacterDataTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::CharacterData<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreateText()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::CharacterData<std::string> t = d.createTextNode("some data");

      assert(t.getData() == "some data");
      assert(t.getNodeName() == "#text");
      assert(t.getNodeValue() == t.getData());

      t.setData("newData");
      assert(t.getData() == "newData");

      assert(t.getNodeType() == DOM::Node<std::string>::TEXT_NODE);
      assert(t.hasAttributes() == false);
      assert(t.getAttributes() == 0);
      assert(t.getChildNodes() == 0);
      assert(t.getFirstChild() == 0);

      try
      {
        t.appendChild(DOM::Node<std::string>());
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
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::CharacterData<std::string> t = d.createCDATASection("some data");

      assert(t.getData() == "some data");
      assert(t.getNodeName() == "#cdata-section");
      assert(t.getNodeValue() == t.getData());

      t.setData("newData");
      assert(t.getData() == "newData");

      assert(t.getNodeType() == DOM::Node<std::string>::CDATA_SECTION_NODE);
      assert(t.hasAttributes() == false);
      assert(t.getAttributes() == 0);
      assert(t.getChildNodes() == 0);
      assert(t.getFirstChild() == 0);

      try
      {
        t.appendChild(DOM::Node<std::string>());
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
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::CDATASection<std::string> cd = d.createCDATASection("some data");

      DOM::Text<std::string> t = cd;
      DOM::CharacterData<std::string> c = t;

      DOM::Node<std::string> n = c;

      assert(c == cd);
      assert(c == t);
      assert(c == n);
      assert(n == c);
      assert(n == cd);
    } // testDownCasts

    void testTextUpCasts()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Node<std::string> n = d.createTextNode("some data");

      DOM::CharacterData<std::string> c = DOM::CharacterData<std::string>(n);
      DOM::Text<std::string> t = DOM::Text<std::string>(c);

      assert(c == t);
      assert(c == n);
      assert(n == c);
    } // testTextUpCasts

    void testCDATAUpCasts()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Node<std::string> n = d.createCDATASection("some data");

      DOM::CharacterData<std::string> c = DOM::CharacterData<std::string>(n);
      DOM::Text<std::string> t = DOM::Text<std::string>(c);
      DOM::CDATASection<std::string> cd = DOM::CDATASection<std::string>(c);

      assert(c == cd);
      assert(c == t);
      assert(c == n);
      assert(n == c);
      assert(n == cd);
    } // testCDATAUpCasts
};

TestSuite* CharacterDataTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<CharacterDataTest>("testNull", &CharacterDataTest::testNull));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest>("testCreateText", &CharacterDataTest::testCreateText));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest>("testCreateCDATA", &CharacterDataTest::testCreateCDATA));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest>("testDownCasts", &CharacterDataTest::testDownCasts));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest>("testTextUpCasts", &CharacterDataTest::testTextUpCasts));
    suiteOfTests->addTest(new TestCaller<CharacterDataTest>("testCDATAUpCasts", &CharacterDataTest::testCDATAUpCasts));
    return suiteOfTests;
} // CharacterDataTest_suite

