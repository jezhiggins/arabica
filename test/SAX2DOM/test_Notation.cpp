
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/SAX2DOM/SAX2DOM.h>

class NotationTest : public TestCase 
{
 SAX2DOM::DOMFactory factory;

  public: 
    NotationTest(std::string name) :
        TestCase(name) 
    {
    } // NotationTest
    
    void setUp() 
    {
    } // setUp

    void testNull() 
    {
      DOM::Notation<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      DOM::Document<std::string> d = factory.newDocument();
      DOM::Notation<std::string> p = d.createNotation("target", "data");

      assert(p.getTarget() == "target");
      assert(p.getData() == "data");
      assert(p.getNodeName() == p.getTarget());
      assert(p.getNodeValue() == p.getData());

      p.setData("newData");
      assert(p.getData() == "newData");
    } // testCreate

    void testConversion()
    {
      DOM::Document<std::string> d = factory.newDocument();
      DOM::Notation<std::string> pi = d.createNotation("target", "data");

      DOM::Node<std::string> n;

      assert(n != pi);

      n = pi;

      assert(n == pi);

      DOM::Notation<std::string> pi2;

      assert(n != pi2);
      pi2 = static_cast<DOM::Notation<std::string> >(n);
      assert(pi == pi2);
      assert(n == pi2);
    } // testConverstion

    void testEverythingElse()
    {
      DOM::Document<std::string> d = factory.newDocument();
      DOM::Notation<std::string> pi = d.createNotation("target", "data");

      assert(pi.getNodeType() == DOM::Node<std::string>::PROCESSING_INSTRUCTION_NODE);
      assert(pi.hasAttributes() == false);
      assert(pi.getAttributes() == 0);
      assert(pi.getChildNodes() == 0);
      assert(pi.getFirstChild() == 0);

      try
      {
        pi.appendChild(DOM::Node<std::string>());
      } 
      catch(const DOM::DOMException&)
      {
      } 

      assert(pi.getFirstChild() == 0);

      assert(pi.getOwnerDocument() == d);
      assert(pi.getParentNode() == 0);

      d.appendChild(pi);
      assert(pi.getOwnerDocument() == d);
      assert(pi.getParentNode() == d);
      assert(d.getFirstChild() == pi);
    } // 
};

TestSuite* NotationTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<NotationTest>("testNull", NotationTest::testNull));
    suiteOfTests->addTest(new TestCaller<NotationTest>("testCreate", NotationTest::testCreate));
    suiteOfTests->addTest(new TestCaller<NotationTest>("testConversion", NotationTest::testConversion));
    suiteOfTests->addTest(new TestCaller<NotationTest>("testEverythingElse", NotationTest::testEverythingElse));
    return suiteOfTests;
} // MathTest_suite

