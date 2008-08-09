#include "TestRunner.hpp"
#include "textui/TextTestResult.h"
#include "textui/TableTestResult.hpp"
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

template<typename result_type>
bool run(const string& name, Test *test, bool verbose)
{
  if(verbose)
    cout << "Running " << name << endl;
  result_type  result(name, verbose);
  test->run (&result);
  cout << result;
  return result.wasSuccessful();
} // run

bool textrun(const string& name, Test *test, bool verbose)
{
  return run<TextTestResult>(name, test, verbose);
} // textrun

bool tablerun(const string& name, Test *test, bool verbose)
{
  return run<TableTestResult>(name, test, verbose);
} // tablerun



void printBanner ()
{
  cout << "Usage: driver [-v] [-table] [ -wait ] testName, where name is the name of a test case class" << endl;
} // printBanner

typedef bool (*runFn)(const string& name, Test *test, bool verbose);

bool TestRunner::run(int ac, const char **av)
{
  bool ok = true;
  string  testCase;
  int     numberOfTests = 0;
  int opt = 0;
  runFn runner = textrun;

  for(int i = 1; i < ac; i++) 
  {
    if(string(av[i]) == "-wait") 
    {
      m_wait = true;
      ++opt;
      continue;
    }

    if(string(av[i]) == "-v")
    {
      verbose_ = true;
      ++opt;
      continue;
    }

    if(string(av[i]) == "-table")
    {
      runner = tablerun;
      ++opt;
      continue;
    }


    testCase = av[i];

    if(testCase == "") 
    {
      printBanner ();
      return ok;
    }

    Test *testToRun = NULL;

    for(mappings::iterator it = m_mappings.begin();
            it != m_mappings.end();
            ++it) 
    {
      if((*it).first == testCase) 
      {
        testToRun = (*it).second;
        ok &= runner((*it).first, testToRun, verbose_);
      }
    }

    numberOfTests++;

    if(!testToRun) 
    {
      cout << "Test " << testCase << " not found." << endl;
      return false;
    } 
  } // for ...

  if((ac-opt) == 1)
  {
    // run everything
    for(mappings::iterator it = m_mappings.begin(); it != m_mappings.end(); ++it) 
    {
      ok &= runner((*it).first, (*it).second, verbose_);
    }
    return ok;
  } 

  if(numberOfTests == 0) 
  {
      printBanner ();
      return false;        
  }

  if(m_wait) 
  {
      cout << "<RETURN> to continue" << endl;
      cin.get ();
  }

  return ok;
} // run

TestRunner::~TestRunner ()
{
  for(mappings::iterator it = m_mappings.begin ();
             it != m_mappings.end ();
             ++it)
    delete it->second;
} // ~TestRunner

