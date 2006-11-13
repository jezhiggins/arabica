#include "TestRunner.hpp"
#include "textui/TextTestResult.h"
#include <iostream>

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
  cout << "Usage: driver [-q] [ -wait ] testName, where name is the name of a test case class" << endl;
} // printBanner

void TestRunner::run(int ac, const char **av)
{
  string  testCase;
  int     numberOfTests = 0;
  int opt = 0;

  for(int i = 1; i < ac; i++) 
  {
    if(string(av[i]) == "-wait") 
    {
      m_wait = true;
      ++opt;
      continue;
    }

    if(string(av[i]) == "-q")
    {
      verbose_ = false;
      ++opt;
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
	if(verbose_)
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

  if((ac-opt) == 1)
  {
    // run everything
    for(mappings::iterator it = m_mappings.begin(); it != m_mappings.end(); ++it) 
    {
      if(verbose_)
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
  TextTestResult  result(verbose_);
  test->run (&result);
  cout << result;
} // run

