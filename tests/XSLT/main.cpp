#ifdef _MSC_VER
#pragma warning(disable : 4250)
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <map>

///////////////////////////////////////////////
#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"

// #include "scope_test.hpp"
#include "xslt_test.hpp"

std::set<std::string> parse_tests_to_run(int argc, const char* argv[]);
void add_tests(TestRunner& runner, Loader& loader, const std::set<std::string>& wanted, const char** test_names);
void add_arabica_tests(TestRunner& runner, Loader& loader, const std::set<std::string>& wanted, const char** test_names);

const char* xalan_tests[] = {"attribvaltemplate", "axes", "boolean", "conditional", 
                             "conflictres", "copy", "dflt", "expression", "extend", 
                             /*"idkey",*/ "impincl", "lre", "match", "math", 
                             "mdocs", "message", "modes", "namedtemplate", 
                             "namespace", "node", /*"numberformat",*/ /*"numbering",*/
                             "output", "position", "predicate", "processorinfo", "reluri",
                             "select", "sort", "string", "variable", "ver", "whitespace", 0};

const char* msft_tests[] = { "AVTs", /*"AttributeSets",*/ "Attributes", "BVTs", 
                             "Comment", "Completeness", "ConflictResolution", "Copying", 
                             "Elements", "Errors", "Fallback", "ForEach", /*"FormatNumber",*/
                             "ForwardComp", "Import", "Keys", "Messages", 
                             "Miscellaneous", "Modes", "NamedTemplates", "Namespace",
                             "Namespace-alias", "Namespace_XPath", /*"Number",*/
                             /*"Output",*/ "ProcessingInstruction", "RTF", "Sorting", 
                             "Stylesheet", "Template", "Text",  "Valueof",
                             "Variables", "Whitespaces", "XSLTFunctions", 0 };

const char* arabica_tests[] = { "attributes",
                                "errors", "include", "processing-instruction", 
                                "stylesheet", "text", "variables", 0 };

int main(int argc, const char* argv[])
{
  TestRunner runner;
  std::set<std::string> tests_to_run = parse_tests_to_run(argc, argv);

  // runner.addTest("ScopeTest", ScopeTest_suite<string_type, string_adaptor>());

  Loader loader;

  add_tests(runner, loader, tests_to_run, xalan_tests);
  add_tests(runner, loader, tests_to_run, msft_tests);
  add_arabica_tests(runner, loader, tests_to_run, arabica_tests);

  runner.run(argc, argv);

  return 77;
}  // main

std::set<std::string> parse_tests_to_run(int argc, const char* argv[])
{
  std::set<std::string> tests;
  for(int a = 1; a != argc; ++a)
    if(argv[a][0] != '-')
      tests.insert(argv[a]);
    else
    {
      if(std::string(argv[a]) == "-log")
	++a; // skip next
    } // if ...
     
  return tests;
} // tests_to_run

void add_tests(TestRunner& runner, Loader& loader, const std::set<std::string>& wanted, const char** test_names)
{
  std::set<std::string>::const_iterator end = wanted.end();
  while(*test_names != 0)
  {
    if(wanted.empty() || (wanted.find(*test_names) != end))
      runner.addTest(*test_names, loader.XSLTTest_suite(*test_names));
    ++test_names;
  } // while ...
} // all_all_tests

void add_arabica_tests(TestRunner& runner, Loader& loader, const std::set<std::string>& wanted, const char** test_names)
{
  std::set<std::string>::const_iterator end = wanted.end();
  while(*test_names != 0)
  {
    if(wanted.empty() || (wanted.find(*test_names) != end))
      runner.addTest(*test_names, loader.ArabicaTest_suite(*test_names));
    ++test_names;
  } // while ...
} // all_all_tests
