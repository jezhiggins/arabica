#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

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
      DOM::DOMImplementation<std::string> di;
      assert(di == 0);

      DOM::DOMImplementation<std::string> di2 = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
      assert(di2 != 0);

      assert(di != di2);
      assert(di2 != di);

      di = di2;
      assert(di == di2);
      assert(di2 == di);
    } // testNull

    void testFeatures()
    {
      DOM::DOMImplementation<std::string> di = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();

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

TestSuite* DOMImplementationTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<DOMImplementationTest>("testNill", &DOMImplementationTest::testNull));
    suiteOfTests->addTest(new TestCaller<DOMImplementationTest>("testFeatures", &DOMImplementationTest::testFeatures));
    return suiteOfTests;
} // MathTest_suite

