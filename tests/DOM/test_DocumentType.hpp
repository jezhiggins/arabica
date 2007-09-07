#ifndef test_DocumentType_h
#define test_DocumentType_h

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class DocumentTypeTest : public TestCase 
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  typedef string_adaptor SA;

  public: 
    DocumentTypeTest(std::string name) :
        TestCase(name) 
    {
    } // DocumentTypeTest
    
    void setUp() 
    {
      factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      Arabica::DOM::DocumentType<string_type, string_adaptor> d;
      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      Arabica::DOM::DocumentType<string_type, string_adaptor> d = factory.createDocumentType(SA::construct_from_utf8("charlie"), 
                                                                    SA::construct_from_utf8(""), 
                                                                    SA::construct_from_utf8("http://gruesome/"));
      assert(d != 0);

      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(n == 0);
      assert(n != d);

      n = d;

      assert(n == d);
      assert(d == (Arabica::DOM::DocumentType<string_type, string_adaptor>(n)));

      Arabica::DOM::DocumentType<string_type, string_adaptor> d2;
      assert(d != d2);
      assert(d2 != d);
      d2 = d;
      assert(d == d2);
      assert(d2 == d);

      Arabica::DOM::DocumentType<string_type, string_adaptor> d3 = factory.createDocumentType(SA::construct_from_utf8("billy"), 
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
      Arabica::DOM::DocumentType<string_type, string_adaptor> d = factory.createDocumentType(SA::construct_from_utf8("charlie"), 
                                                                    SA::construct_from_utf8("sss"), 
                                                                    SA::construct_from_utf8("http://gruesome/"));

      Arabica::DOM::Document<string_type, string_adaptor> doc = factory.createDocument(SA::construct_from_utf8(""), 
                                                              SA::construct_from_utf8("doc"), 
                                                              d);

      Arabica::DOM::DocumentType<string_type, string_adaptor> dt = doc.getDoctype();
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

