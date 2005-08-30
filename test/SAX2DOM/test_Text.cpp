#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class TextTest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    TextTest(std::string name) :
        TestCase(name) 
    {
    } // TextTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::Text<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Text<std::string> t = d.createTextNode("some data");

      assert(t.getData() == "some data");
      assert(t.getNodeName() == "#text");
      assert(t.getNodeValue() == t.getData());

      t.setData("newData");
      assert(t.getData() == "newData");
    } // testCreate

    void testConversion()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Text<std::string> t = d.createTextNode("some data");

      DOM::Node<std::string> n;

      assert(n != t);

      n = t;
      assert(n == t);

      DOM::Text<std::string> t2;

      assert(n != t2);

      t2 = DOM::Text<std::string>(n);
      assert(t == t2);
      assert(n == t2);

      DOM::Text<std::string> t3;
      t3 = t2;
      assert(t3 == t2);
      assert(t3 == t);

      DOM::Comment<std::string> c = d.createComment("woo");
      try {
        t = DOM::Text<std::string>(c);
        assertImplementation(false, "converted comment to text");
      } 
      catch(const std::bad_cast&) {
      }
    } // testConverstion

    void testEverythingElse()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Text<std::string> t = d.createTextNode("some data");

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
    } // 
};

TestSuite* TextTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<TextTest>("testNull", &TextTest::testNull));
    suiteOfTests->addTest(new TestCaller<TextTest>("testCreate", &TextTest::testCreate));
    suiteOfTests->addTest(new TestCaller<TextTest>("testConversion", &TextTest::testConversion));
    suiteOfTests->addTest(new TestCaller<TextTest>("testEverythingElse", &TextTest::testEverythingElse));
    return suiteOfTests;
} // TextTest_suite

