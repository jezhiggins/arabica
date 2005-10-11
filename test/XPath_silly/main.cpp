
#ifdef _MSC_VER
#pragma warning(disable:4224 4267)
#endif

#include <iostream>
#include "../CppUnit/textui/TextTestResult.h"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestSuite.h"

#include "parse_test.hpp"
#include "../XPath/value_test.hpp"
#include "../XPath/arithmetic_test.hpp"
#include "relational_test.hpp"
#include "logical_test.hpp"
#include "axis_enumerator_test.hpp"
#include "node_test_test.hpp"
#include "step_test.hpp"
#include "execute_test.hpp"

class TestRunner
{
protected:
    bool m_wait;
    std::vector<std::pair<std::string,Test *> > m_mappings;

public:
	  TestRunner() : m_wait(false) {}
    ~TestRunner();

    void run(int ac, char **av);
    void addTest(std::string name, Test *test)
    { m_mappings.push_back(std::make_pair(name, test)); }

protected:
    void run(Test *test);
    void printBanner();
}; // TestRunner;


#include "../silly_string/silly_string.hpp"

template<> class Arabica::default_string_adaptor<silly_string> : public silly_string_adaptor { };

/////////////////////////////////////////
int main(int argc, char** argv)
{
  std::cout << "Hello" << std::endl;

  TestRunner runner;

  runner.addTest("ValueTest", ValueTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("ArithmeticTest", ArithmeticTest_suite<silly_string, Arabica::default_string_adaptor<silly_string> >());
  runner.addTest("RelationalTest", RelationalTest_suite());
  runner.addTest("LogicalTest", LogicalTest_suite());
  runner.addTest("AxisEnumeratorTest", AxisEnumeratorTest_suite());
  runner.addTest("NodeTestTest", NodeTestTest_suite());
  runner.addTest("StepTest", StepTest_suite());
  runner.addTest("ParseTest", ParseTest_suite());
  runner.addTest("ExecuteTest", ExecuteTest_suite());

  runner.run(argc, argv);
} // main

//////////////////////////////////////////
/*
 * A command line based tool to run tests.
 * TestRunner expects as its only argument the name of a TestCase class.
 * TestRunner prints out a trace as the tests are executed followed by a
 * summary at the end.
 *
 * You can add to the tests that the TestRunner knows about by 
 * making additional calls to "addTest (...)" in main.
 *
 * Here is the synopsis:
 *
 * TestRunner [-wait] ExampleTestCase
 *
 */

using namespace std;

typedef pair<string, Test *>           mapping;
typedef vector<pair<string, Test *> >   mappings;

void TestRunner::printBanner ()
{
    cout << "Usage: driver [ -wait ] testName, where name is the name of a test case class" << endl;
} // printBanner

void TestRunner::run(int ac, char **av)
{
    string  testCase;
    int     numberOfTests = 0;

    for(int i = 1; i < ac; i++) 
    {

        if(string(av[i]) == "-wait") 
        {
            m_wait = true;
            continue;
        }

        testCase = av[i];

        if(testCase == "") 
        {
            printBanner ();
            return;
        }

        Test *testToRun = NULL;

        for(mappings::iterator it = m_mappings.begin();
            it != m_mappings.end();
            ++it) 
        {
            if((*it).first == testCase) 
            {
                cout << (*it).first << std::endl;
                testToRun = (*it).second;
                run(testToRun);
            }
        }

        numberOfTests++;

        if(!testToRun) 
        {
            cout << "Test " << testCase << " not found." << endl;
            return;
        } 
    } // for ...

    if(ac == 1)
    {
      // run everything
      for(mappings::iterator it = m_mappings.begin(); it != m_mappings.end(); ++it) 
      {
        cout << (*it).first << std::endl;
        run((*it).second);
      }
      return;
    } 

    if(numberOfTests == 0) 
    {
        printBanner ();
        return;        
    }

    if(m_wait) 
    {
        cout << "<RETURN> to continue" << endl;
        cin.get ();
    }
} // run

TestRunner::~TestRunner ()
{
    for(mappings::iterator it = m_mappings.begin ();
             it != m_mappings.end ();
             ++it)
       delete it->second;
} // ~TestRunner

void TestRunner::run(Test *test)
{
    TextTestResult  result;
    test->run (&result);
    cout << result << endl;
} // run

