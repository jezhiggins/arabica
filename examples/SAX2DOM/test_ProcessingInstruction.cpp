#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include "CppUnit/framework/TestCase.h"
#include "CppUnit/framework/TestSuite.h"
#include "CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class PITest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    PITest(std::string name) :
        TestCase(name) 
    {
    } // PITest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::ProcessingInstruction<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::ProcessingInstruction<std::string> p = d.createProcessingInstruction("target", "data");

      assert(p.getTarget() == "target");
      assert(p.getData() == "data");
      assert(p.getNodeName() == p.getTarget());
      assert(p.getNodeValue() == p.getData());

      p.setData("newData");
      assert(p.getData() == "newData");
    } // testCreate

    void testConversion()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::ProcessingInstruction<std::string> pi = d.createProcessingInstruction("target", "data");

      DOM::Node<std::string> n;

      assert(n != pi);

      n = pi;

      assert(n == pi);

      DOM::ProcessingInstruction<std::string> pi2;

      assert(n != pi2);
      pi2 = static_cast<DOM::ProcessingInstruction<std::string> >(n);
      assert(pi == pi2);
      assert(n == pi2);
    } // testConverstion

    void testEverythingElse()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::ProcessingInstruction<std::string> pi = d.createProcessingInstruction("target", "data");

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

TestSuite* ProcessingInstructionTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<PITest>("testNull", &PITest::testNull));
    suiteOfTests->addTest(new TestCaller<PITest>("testCreate", &PITest::testCreate));
    suiteOfTests->addTest(new TestCaller<PITest>("testConversion", &PITest::testConversion));
    suiteOfTests->addTest(new TestCaller<PITest>("testEverythingElse", &PITest::testEverythingElse));
    return suiteOfTests;
} // MathTest_suite

