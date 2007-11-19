
#pragma warning(disable : 4250)

#include <iostream>
#include <string>
#include <sstream>


///////////////////////////////////////////////
#include "../CppUnit/TestRunner.hpp"
#include "../CppUnit/framework/Test.h"
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"

// #include "scope_test.hpp"
#include "xslt_test.hpp"

/*
typedef std::string string_type;
typedef Arabica::default_string_adaptor<std::string> string_adaptor;
*/

int main(int argc, const char* argv[])
{
  TestRunner runner;

  // runner.addTest("ScopeTest", ScopeTest_suite<string_type, string_adaptor>());
  // Xalan supplied test cases
/*
  //runner.addTest("attribset", XSLTTest_suite("attribset"));
  runner.addTest("attribvaltemplate", XSLTTest_suite("attribvaltemplate"));
  runner.addTest("axes", XSLTTest_suite("axes"));
  runner.addTest("boolean", XSLTTest_suite("boolean"));
  runner.addTest("conditional", XSLTTest_suite("conditional"));
  runner.addTest("conflictres", XSLTTest_suite("conflictres"));
  runner.addTest("copy", XSLTTest_suite("copy"));
  runner.addTest("dflt", XSLTTest_suite("dflt"));
  runner.addTest("expression", XSLTTest_suite("expression"));
  runner.addTest("extend", XSLTTest_suite("extend"));
  //runner.addTest("idkey", XSLTTest_suite("idkey"));
*/
  runner.addTest("impincl", XSLTTest_suite("impincl"));
/*
  runner.addTest("lre", XSLTTest_suite("lre"));
  runner.addTest("match", XSLTTest_suite("match"));
  runner.addTest("math", XSLTTest_suite("math"));
  runner.addTest("mdocs", XSLTTest_suite("mdocs"));
  runner.addTest("message", XSLTTest_suite("message"));
  runner.addTest("modes", XSLTTest_suite("modes"));
  runner.addTest("namedtemplate", XSLTTest_suite("namedtemplate"));
  runner.addTest("namespace", XSLTTest_suite("namespace"));
  runner.addTest("node", XSLTTest_suite("node"));
  //runner.addTest("numberformat", XSLTTest_suite("numberformat"));
  //runner.addTest("numbering", XSLTTest_suite("numbering"));
  runner.addTest("output", XSLTTest_suite("output"));
  runner.addTest("position", XSLTTest_suite("position"));
  runner.addTest("predicate", XSLTTest_suite("predicate"));
  runner.addTest("processorinfo", XSLTTest_suite("processorinfo"));
  runner.addTest("reluri", XSLTTest_suite("reluri"));
  runner.addTest("select", XSLTTest_suite("select"));
  runner.addTest("sort", XSLTTest_suite("sort"));
  runner.addTest("string", XSLTTest_suite("string"));
  runner.addTest("variable", XSLTTest_suite("variable"));
  runner.addTest("ver", XSLTTest_suite("ver"));
  runner.addTest("whitespace", XSLTTest_suite("whitespace"));

  // MSFT supplied test cases
  runner.addTest("AVTs", XSLTTest_suite("AVTs"));
  //runner.addTest("AttributeSets", XSLTTest_suite("AttributeSets"));
  runner.addTest("Attributes", XSLTTest_suite("Attributes"));
  runner.addTest("BVTs", XSLTTest_suite("BVTs"));
  runner.addTest("Comment", XSLTTest_suite("Comment"));
  runner.addTest("Completeness", XSLTTest_suite("Completeness"));
  runner.addTest("ConflictResolution", XSLTTest_suite("ConflictResolution"));
  runner.addTest("Copying", XSLTTest_suite("Copying"));
  runner.addTest("Elements", XSLTTest_suite("Elements"));
*/
  runner.addTest("Errors", XSLTTest_suite("Errors"));
/*
  runner.addTest("Fallback", XSLTTest_suite("Fallback"));
  runner.addTest("ForEach", XSLTTest_suite("ForEach"));
  //runner.addTest("FormatNumber", XSLTTest_suite("FormatNumber"));
  runner.addTest("ForwardComp", XSLTTest_suite("ForwardComp"));
  runner.addTest("Import", XSLTTest_suite("Import"));
  //runner.addTest("Keys", XSLTTest_suite("Keys"));
  runner.addTest("Messages", XSLTTest_suite("Messages"));
  runner.addTest("Miscellaneous", XSLTTest_suite("Miscellaneous"));
  runner.addTest("Modes", XSLTTest_suite("Modes"));
  runner.addTest("NamedTemplates", XSLTTest_suite("NamedTemplates"));
  runner.addTest("Namespace", XSLTTest_suite("Namespace"));
  runner.addTest("Namespace-alias", XSLTTest_suite("Namespace-alias"));
  runner.addTest("Namespace_XPath", XSLTTest_suite("Namespace_XPath"));
  //runner.addTest("Number", XSLTTest_suite("Number"));
  runner.addTest("Output", XSLTTest_suite("Output"));
  runner.addTest("ProcessingInstruction", XSLTTest_suite("ProcessingInstruction"));
  runner.addTest("RTF", XSLTTest_suite("RTF"));
  runner.addTest("Sorting", XSLTTest_suite("Sorting"));
  runner.addTest("Stylesheet", XSLTTest_suite("Stylesheet"));
  runner.addTest("Template", XSLTTest_suite("Template"));
  runner.addTest("Text", XSLTTest_suite("Text"));
  runner.addTest("Valueof", XSLTTest_suite("Valueof"));
  runner.addTest("Variables", XSLTTest_suite("Variables"));
  runner.addTest("Whitespaces", XSLTTest_suite("Whitespaces"));
  runner.addTest("XSLTFunctions", XSLTTest_suite("XSLTFunctions"));
*/

  runner.run(argc, argv);

  return 77;
} // test_suite
