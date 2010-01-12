#include "TestRunner.hpp"
#include "textui/TextTestResult.h"
#include "textui/TableTestResult.hpp"
#include "textui/XmlTestResult.hpp"
#include <iostream>
#include <fstream>

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
bool run(const string& name, Test *test, bool verbose, const string& logprefix)
{
  if(verbose)
    cout << "Running " << name << endl;
  result_type  result(name, verbose);
  test->run (&result);
  cout << result;
  if(!logprefix.empty())
  {
    std::string filename = logprefix + name + ".log";
    std::ofstream of(filename.c_str());
    of << result;
    of.close();
  } // if ...
  return result.wasSuccessful();
} // run

bool textrun(const string& name, Test *test, bool verbose, const string& logprefix)
{
  return run<TextTestResult>(name, test, verbose, logprefix);
} // textrun

bool tablerun(const string& name, Test *test, bool verbose, const string& logprefix)
{
  return run<TableTestResult>(name, test, verbose, logprefix);
} // tablerun

bool xmlrun(const string& name, Test *test, bool verbose, const string& logprefix)
{
  return run<XmlTestResult>(name, test, verbose, logprefix);
} // xmlrun



void printBanner ()
{
  cout << "Usage: driver [-v] [-table] [ -wait ] testName, where name is the name of a test case class" << endl;
} // printBanner

typedef bool (*runFn)(const string& name, Test *test, bool verbose, const string& logprefix);

bool TestRunner::run(int ac, const char **av)
{
  bool ok = true;
  string  testCase;
  int     numberOfTests = 0;
  int opt = 0;
  runFn runner = textrun;

  std::string executable = av[0];
  size_t slash = executable.find_last_of("/\\");
  if(slash != -1)
    executable.erase(0, slash+1);
  executable += "-";

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

    if(string(av[i]) == "-xml")
    {
      runner = xmlrun;
      ++opt;
      continue;
    } 

    if(string(av[i]) == "-log")
    {
      logprefix_ = av[++i];
      logprefix_ += executable;
      cout << "logprefix=" << logprefix_ << std::endl;
      opt += 2;
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
        ok &= runner(executable + (*it).first, testToRun, verbose_, logprefix_);
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
      ok &= runner(executable + (*it).first, (*it).second, verbose_, logprefix_);
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

