#ifndef test_DOMImplementation_H
#define test_DOMImplementation_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

template<class string_type, class string_adaptor>
class DOMImplementationTest : public TestCase 
{
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
      DOM::DOMImplementation<string_type> di;
      assert(di == 0);

      DOM::DOMImplementation<string_type> di2 = SimpleDOM::DOMImplementation<string_type>::getDOMImplementation();
      assert(di2 != 0);

      assert(di != di2);
      assert(di2 != di);

      di = di2;
      assert(di == di2);
      assert(di2 == di);
    } // testNull

    void testFeatures()
    {
      DOM::DOMImplementation<string_type> di = SimpleDOM::DOMImplementation<string_type>::getDOMImplementation();

      assert(di.hasFeature("Core", "") == true);
      assert(di.hasFeature("Core", "1.0") == true);
      assert(di.hasFeature("Core", "2.0") == true);
      assert(di.hasFeature("Core", "trousers") == false);
//      assert(di.hasFeature("cOrE", "1.0") == true);
//    assert(di.hasFeature("CorE", "2.0") == true);

      assert(di.hasFeature("XML", "") == true);
      assert(di.hasFeature("XML", "1.0") == true);
      assert(di.hasFeature("XML", "2.0") == true);
      assert(di.hasFeature("xml", "") == true);
      assert(di.hasFeature("xml", "1.0") == true);
      assert(di.hasFeature("xml", "2.0") == true);

      assert(di.hasFeature("barleymow", "") == false);
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

