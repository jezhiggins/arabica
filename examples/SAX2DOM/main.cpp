
#pragma warning(disable: 4786 4250 4503)
#include <iostream>
#include <string>
//#include <wrappers/saxexpat.h>
#include <DOM/SAX2DOM/SAX2DOM.h>

#include <iostream>
#include <vector>
#include <map>

#include "CppUnit/textui/TextTestResult.h"
#include "CppUnit/framework/Test.h"

#include "CppUnit/framework/TestSuite.h"

#include "test_DOMImplementation.h"
#include "test_DocumentType.h"
#include "test_Document.h"
#include "test_ProcessingInstruction.h"
#include "test_Siblings.h"
#include "test_Element.h"
#include "test_DocumentFragment.h"
#include "test_Attribute.h"

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

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  TestRunner runner;

  runner.addTest("DOMImplementationTest", DOMImplementationTest_suite());
  runner.addTest("DocumentTypeTest", DocumentTypeTest_suite());
  runner.addTest("DocumentTest", DocumentTest_suite());
  runner.addTest("ProcessingInstructionTest", ProcessingInstructionTest_suite());
  runner.addTest("SiblingsTest", SiblingsTest_suite());
  runner.addTest("ElementTest", ElementTest_suite());
  runner.addTest("DocumentFragmentTest", DocumentFragmentTest_suite());
  runner.addTest("AttributeTest", AttrTest_suite());
  runner.run(argc, argv);

  return 0;
} // main



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

// end of file
