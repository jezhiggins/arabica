#ifdef _MSC_VER 
#pragma warning(disable: 4786 4250 4503)
#endif
#include "CppUnit/framework/TestCase.h"
#include "CppUnit/framework/TestSuite.h"
#include "CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class DocumentTypeTest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    DocumentTypeTest(std::string name) :
        TestCase(name) 
    {
    } // DocumentTypeTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::DocumentType<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      DOM::DocumentType<std::string> d = factory.createDocumentType("charlie", "", "http://gruesome/");
      assert(d != 0);

      DOM::Node<std::string> n;
      assert(n == 0);
      assert(n != d);

      n = d;

      assert(n == d);
      assert(d == static_cast<DOM::DocumentType<std::string> >(n));

      DOM::DocumentType<std::string> d2;
      assert(d != d2);
      assert(d2!= d);
      d2 = d;
      assert(d == d2);
      assert(d2 == d);

      DOM::DocumentType<std::string> d3 = factory.createDocumentType("billy", "", "http://gruesome/");;
      assert(d != d3);
      assert(d3!= d);
      d3 = d;
      assert(d == d3);
      assert(d3 == d);
    } // testCreate

    void testDoc()
    {
      DOM::DocumentType<std::string> d = factory.createDocumentType("charlie", "sss", "http://gruesome/");

      DOM::Document<std::string> doc = factory.createDocument("", "doc", d);

      DOM::DocumentType<std::string> dt = doc.getDoctype();
      assert(dt.getPublicId() == "sss");
      assert(dt.getSystemId() == "http://gruesome/");
      assert(dt.getNodeName() == "charlie");
    } // testDoc
};

TestSuite* DocumentTypeTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<DocumentTypeTest>("testNill", &DocumentTypeTest::testNull));
    suiteOfTests->addTest(new TestCaller<DocumentTypeTest>("testCreate", &DocumentTypeTest::testCreate));
    suiteOfTests->addTest(new TestCaller<DocumentTypeTest>("testDoc", &DocumentTypeTest::testDoc));
    return suiteOfTests;
} // MathTest_suite

