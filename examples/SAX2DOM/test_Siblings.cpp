#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include "CppUnit/framework/TestCase.h"
#include "CppUnit/framework/TestSuite.h"
#include "CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class SiblingsTest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    SiblingsTest(std::string name) :
        TestCase(name) 
    {
    } // SiblingsTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void test1()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::Element<std::string> root = d.createElement("root");
      d.appendChild(root);

      assert(root.getPreviousSibling() == 0);
      assert(root.getNextSibling() == 0);

      DOM::ProcessingInstruction<std::string> p = d.createProcessingInstruction("target", "data");
      d.insertBefore(p, root);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == root);
      assert(root.getPreviousSibling() == p);
      assert(root.getNextSibling() == 0);

      DOM::ProcessingInstruction<std::string> p2 = d.createProcessingInstruction("target", "data");
      d.insertBefore(p2, root);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == p2);
      assert(p2.getPreviousSibling() == p);
      assert(p2.getNextSibling() == root);
      assert(root.getPreviousSibling() == p2);
      assert(root.getNextSibling() == 0);

      d.removeChild(p2);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == root);
      assert(p2.getPreviousSibling() == 0);
      assert(p2.getNextSibling() == 0);
      assert(root.getPreviousSibling() == p);
      assert(root.getNextSibling() == 0);

      d.insertBefore(p2, root);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == p2);
      assert(p2.getPreviousSibling() == p);
      assert(p2.getNextSibling() == root);
      assert(root.getPreviousSibling() == p2);
      assert(root.getNextSibling() == 0);

      d.removeChild(p);
      assert(d.getFirstChild() == p2);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == 0);
      assert(p2.getPreviousSibling() == 0);
      assert(p2.getNextSibling() == root);
      assert(root.getPreviousSibling() == p2);
      assert(root.getNextSibling() == 0);

      d.replaceChild(p, p2);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == root);
      assert(p2.getPreviousSibling() == 0);
      assert(p2.getNextSibling() == 0);
      assert(root.getPreviousSibling() == p);
      assert(root.getNextSibling() == 0);

      d.appendChild(p2);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == p2);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == root);
      assert(root.getPreviousSibling() == p);
      assert(root.getNextSibling() == p2);
      assert(p2.getPreviousSibling() == root);
      assert(p2.getNextSibling() == 0);
    } // test1

    void test2()
    {
      DOM::Element<std::string> root;
      {
        DOM::Document<std::string> d = factory.createDocument("","", 0);
        root = d.createElement("root");
        d.appendChild(root);

        assert(root.getPreviousSibling() == 0);
        assert(root.getNextSibling() == 0);

        DOM::ProcessingInstruction<std::string> p = d.createProcessingInstruction("target", "data");
        d.insertBefore(p, root);
      }

      DOM::Node<std::string> n = root.getPreviousSibling();
      DOM::ProcessingInstruction<std::string> p = DOM::ProcessingInstruction<std::string>(n);
      assert(p.getTarget() == "target");
      assert(p.getData() == "data");
    } // test2
};

TestSuite* SiblingsTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<SiblingsTest>("test1", &SiblingsTest::test1));
    suiteOfTests->addTest(new TestCaller<SiblingsTest>("test2", &SiblingsTest::test2));
    return suiteOfTests;
} // MathTest_suite

