#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class CDATATest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    CDATATest(std::string name) :
        TestCase(name) 
    {
    } // CDATATest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::CDATASection<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::CDATASection<std::string> t = d.createCDATASection("some data");

      assert(t.getData() == "some data");
      assert(t.getNodeName() == "#cdata-section");
      assert(t.getNodeValue() == t.getData());

      t.setData("newData");
      assert(t.getData() == "newData");
    } // testCreate

    void testConversion()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::CDATASection<std::string> t = d.createCDATASection("some data");

      DOM::Node<std::string> n;

      assert(n != t);

      n = t;
      assert(n == t);

      DOM::CDATASection<std::string> t2;

      assert(n != t2);

      t2 = DOM::CDATASection<std::string>(n);
      assert(t == t2);
      assert(n == t2);

      DOM::CDATASection<std::string> t3;
      t3 = t2;
      assert(t3 == t2);
      assert(t3 == t);

      DOM::Comment<std::string> c = d.createComment("woo");
      try {
        t = DOM::CDATASection<std::string>(c);
        assertImplementation(false, "converted comment to text");
      } 
      catch(const std::bad_cast& ex) {
        assertEquals(ex.what(), "Cannot convert Node to CDATA section");
      }
    } // testConverstion

    void testConversionToText()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::CDATASection<std::string> cd = d.createCDATASection("some data");

      DOM::Text<std::string> t;
      assert(t == 0);
      assert(cd != t);
      t = cd;
      assert(cd == t);

      DOM::CDATASection<std::string> cd2;
      assert(cd2 == 0);
      cd2 = DOM::CDATASection<std::string>(t);
      assert(cd2 == t);
      assert(t == cd2);
      assert(cd == cd2);
      assert(cd2 == cd);

      t = d.createTextNode("boom");
      try {
        cd = DOM::CDATASection<std::string>(t);
        assertImplementation(false, "converted text to CDATA");
      } 
      catch(const std::bad_cast& ex) {
        assertEquals(ex.what(), "Cannot convert Node to CDATA section");
      }
    } // testConversionToTest

    void testEverythingElse()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::CDATASection<std::string> t = d.createCDATASection("some data");

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
    } // 
};

TestSuite* CDATATest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<CDATATest>("testNull", &CDATATest::testNull));
    suiteOfTests->addTest(new TestCaller<CDATATest>("testCreate", &CDATATest::testCreate));
    suiteOfTests->addTest(new TestCaller<CDATATest>("testConversion", &CDATATest::testConversion));
    suiteOfTests->addTest(new TestCaller<CDATATest>("testConversionToText", &CDATATest::testConversionToText));
    suiteOfTests->addTest(new TestCaller<CDATATest>("testEverythingElse", &CDATATest::testEverythingElse));
    return suiteOfTests;
} // CDATATest_suite

