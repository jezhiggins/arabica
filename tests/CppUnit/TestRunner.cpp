#include "TestRunner.hpp"
#include "textui/TextTestResult.h"
#include "textui/TableTestResult.hpp"
#include "textui/XmlTestResult.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>

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
  if(!logprefix.empty())
  {
    string filename = logprefix + name + ".log";
    ofstream of(filename.c_str());
    of << result;
    of.close();

    if(verbose)
      cout << result;
  } // if ...
  else 
    cout << result;
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

  string executable = av[0];
  size_t slash = executable.find_last_of("/\\");
  if(slash != string::npos)
    executable.erase(0, slash+1);
  executable += "-";

  vector<string> args;

  {
    // this is a mighty horrible hack, but 
    // it makes it easier to hook into the 
    // CI server
    const char* jcu = getenv("JEZUK_CPP_UNIT");
    if(jcu)
    {
      stringstream env;
      env << jcu;
      string e;
      while(env >> e)
        args.push_back(e);
    } // if ...
  } // 

  for(int i = 1; i < ac; ++i)
    args.push_back(av[i]);

  for(vector<string>::const_iterator a = args.begin(), ae = args.end(); a != ae; ++a)
  {
    if(*a == "-wait") 
    {
      m_wait = true;
      ++opt;
      continue;
    }

    if(*a == "-v")
    {
      verbose_ = true;
      ++opt;
      continue;
    }

    if(*a == "-table")
    {
      runner = tablerun;
      ++opt;
      continue;
    }

    if(*a == "-xml")
    {
      runner = xmlrun;
      ++opt;
      continue;
    } 

    if(*a == "-log")
    {
      ++a;
      logprefix_ = *a;
      logprefix_ += executable;
      opt += 2;
      continue;
    } 


    testCase = *a;

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

  if((args.size()-opt) == 0)
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

