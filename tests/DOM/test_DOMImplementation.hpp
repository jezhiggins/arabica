#ifndef test_DOMImplementation_H
#define test_DOMImplementation_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class DOMImplementationTest : public TestCase 
{
    typedef string_adaptor SA;
  public: 
    DOMImplementationTest(std::string name) :
        TestCase(name) 
    {
    } // DOMImplementationTest
    
    void setUp() 
    {
    } // setUp

    void testNull() 
    {
      Arabica::DOM::DOMImplementation<string_type, string_adaptor> di;
      assert(di == 0);
      assert(!di);

      Arabica::DOM::DOMImplementation<string_type, string_adaptor> di2 = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
      assert(di2 != 0);
      assert(di2);

      assert(di != di2);
      assert(di2 != di);

      di = di2;
      assert(di == di2);
      assert(di2 == di);
    } // testNull

    void testFeatures()
    {
      Arabica::DOM::DOMImplementation<string_type, string_adaptor> di = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();

      assert(di.hasFeature(SA::construct_from_utf8("Core"), SA::construct_from_utf8("")) == true);
      assert(di.hasFeature(SA::construct_from_utf8("Core"), SA::construct_from_utf8("1.0")) == true);
      assert(di.hasFeature(SA::construct_from_utf8("Core"), SA::construct_from_utf8("2.0")) == true);
      assert(di.hasFeature(SA::construct_from_utf8("Core"), SA::construct_from_utf8("trousers")) == false);
//      assert(di.hasFeature("cOrE", "1.0") == true);
//    assert(di.hasFeature("CorE", "2.0") == true);

      assert(di.hasFeature(SA::construct_from_utf8("XML"), SA::construct_from_utf8("")) == true);
      assert(di.hasFeature(SA::construct_from_utf8("XML"), SA::construct_from_utf8("1.0")) == true);
      assert(di.hasFeature(SA::construct_from_utf8("XML"), SA::construct_from_utf8("2.0")) == true);
      assert(di.hasFeature(SA::construct_from_utf8("xml"), SA::construct_from_utf8("")) == true);
      assert(di.hasFeature(SA::construct_from_utf8("xml"), SA::construct_from_utf8("1.0")) == true);
      assert(di.hasFeature(SA::construct_from_utf8("xml"), SA::construct_from_utf8("2.0")) == true);

      assert(di.hasFeature(SA::construct_from_utf8("barleymow"), SA::construct_from_utf8("")) == false);
    } // testDeatures
};

template<class string_type, class string_adaptor>
TestSuite* DOMImplementationTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<DOMImplementationTest<string_type, string_adaptor> >("testNill", &DOMImplementationTest<string_type, string_adaptor>::testNull));
    suiteOfTests->addTest(new TestCaller<DOMImplementationTest<string_type, string_adaptor> >("testFeatures", &DOMImplementationTest<string_type, string_adaptor>::testFeatures));
    return suiteOfTests;
} // DOMImplementationTest_suite

#endif

