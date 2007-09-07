#ifndef test_PI_H
#define test_PI_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class PITest : public TestCase 
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  typedef string_adaptor SA;

  public: 
    PITest(std::string name) :
        TestCase(name) 
    {
    } // PITest
    
    void setUp() 
    {
      factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> d;
      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> p = d.createProcessingInstruction(SA::construct_from_utf8("target"), SA::construct_from_utf8("data"));

      assert(p.getTarget() == SA::construct_from_utf8("target"));
      assert(p.getData() == SA::construct_from_utf8("data"));
      assert(p.getNodeName() == p.getTarget());
      assert(p.getNodeValue() == p.getData());

      p.setData(SA::construct_from_utf8("newData"));
      assert(p.getData() == SA::construct_from_utf8("newData"));
    } // testCreate

    void testConversion()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""),  0);
      Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> pi = d.createProcessingInstruction(SA::construct_from_utf8("target"), SA::construct_from_utf8("data"));

      Arabica::DOM::Node<string_type, string_adaptor> n;

      assert(n != pi);

      n = pi;

      assert(n == pi);

      Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> pi2;

      assert(n != pi2);
      pi2 = Arabica::DOM::ProcessingInstruction<string_type, string_adaptor>(n);
      assert(pi == pi2);
      assert(n == pi2);
    } // testConverstion

    void testEverythingElse()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> pi = d.createProcessingInstruction(SA::construct_from_utf8("target"), SA::construct_from_utf8("data"));

      assert(pi.getNodeType() == Arabica::DOM::Node_base::PROCESSING_INSTRUCTION_NODE);
      assert(pi.hasAttributes() == false);
      assert(pi.getAttributes() == 0);
      assert(pi.getChildNodes() == 0);
      assert(pi.getFirstChild() == 0);

      try
      {
        pi.appendChild(Arabica::DOM::Node<string_type, string_adaptor>());
      } 
      catch(const Arabica::DOM::DOMException&)
      {
      } 

      assert(pi.getFirstChild() == 0);

      assert(pi.getOwnerDocument() == d);
      assert(pi.getParentNode() == 0);

      d.appendChild(pi);
      assert(pi.getOwnerDocument() == d);
      assert(pi.getParentNode() == d);
      assert(d.getFirstChild() == pi);
    } // testEverythingElse
}; // class PITest

template<class string_type, class string_adaptor>
TestSuite* ProcessingInstructionTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<PITest<string_type, string_adaptor> >("testNull", &PITest<string_type, string_adaptor>::testNull));
    suiteOfTests->addTest(new TestCaller<PITest<string_type, string_adaptor> >("testCreate", &PITest<string_type, string_adaptor>::testCreate));
    suiteOfTests->addTest(new TestCaller<PITest<string_type, string_adaptor> >("testConversion", &PITest<string_type, string_adaptor>::testConversion));
    suiteOfTests->addTest(new TestCaller<PITest<string_type, string_adaptor> >("testEverythingElse", &PITest<string_type, string_adaptor>::testEverythingElse));
    return suiteOfTests;
} // ProcessingInstructionTest_suite

#endif

