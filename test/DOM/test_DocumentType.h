#ifndef test_DocumentType_h
#define test_DocumentType_h

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

template<class string_type, class string_adaptor>
class DocumentTypeTest : public TestCase 
{
  DOM::DOMImplementation<string_type> factory;
  typedef string_adaptor SA;

  public: 
    DocumentTypeTest(std::string name) :
        TestCase(name) 
    {
    } // DocumentTypeTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::DocumentType<string_type> d;
      DOM::Node<string_type> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      DOM::DocumentType<string_type> d = factory.createDocumentType(SA::construct_from_utf8("charlie"), 
                                                                    SA::construct_from_utf8(""), 
                                                                    SA::construct_from_utf8("http://gruesome/"));
      assert(d != 0);

      DOM::Node<string_type> n;
      assert(n == 0);
      assert(n != d);

      n = d;

      assert(n == d);
      assert(d == DOM::DocumentType<string_type>(n));

      DOM::DocumentType<string_type> d2;
      assert(d != d2);
      assert(d2 != d);
      d2 = d;
      assert(d == d2);
      assert(d2 == d);

      DOM::DocumentType<string_type> d3 = factory.createDocumentType(SA::construct_from_utf8("billy"), 
                                                                     SA::construct_from_utf8(""), 
                                                                     SA::construct_from_utf8("http://gruesome/"));
      assert(d != d3);
      assert(d3!= d);
      d3 = d;
      assert(d == d3);
      assert(d3 == d);
    } // testCreate

    void testDoc()
    {
      DOM::DocumentType<string_type> d = factory.createDocumentType(SA::construct_from_utf8("charlie"), 
                                                                    SA::construct_from_utf8("sss"), 
                                                                    SA::construct_from_utf8("http://gruesome/"));

      DOM::Document<string_type> doc = factory.createDocument(SA::construct_from_utf8(""), 
                                                              SA::construct_from_utf8("doc"), 
                                                              d);

      DOM::DocumentType<string_type> dt = doc.getDoctype();
      assert(dt.getPublicId() == SA::construct_from_utf8("sss"));
      assert(dt.getSystemId() == SA::construct_from_utf8("http://gruesome/"));
      assert(dt.getNodeName() == SA::construct_from_utf8("charlie"));
    } // testDoc
};

template<class string_type, class string_adaptor>
TestSuite* DocumentTypeTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<DocumentTypeTest<string_type, string_adaptor> >("testNull", &DocumentTypeTest<string_type, string_adaptor>::testNull));
    suiteOfTests->addTest(new TestCaller<DocumentTypeTest<string_type, string_adaptor> >("testCreate", &DocumentTypeTest<string_type, string_adaptor>::testCreate));
    suiteOfTests->addTest(new TestCaller<DocumentTypeTest<string_type, string_adaptor> >("testDoc", &DocumentTypeTest<string_type, string_adaptor>::testDoc));
    return suiteOfTests;
} // DocumentTypeTest_suite


#endif

