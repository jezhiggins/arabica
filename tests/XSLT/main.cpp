
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

int main(int argc, const char* argv[])
{
  TestRunner runner;

  // runner.addTest("ScopeTest", ScopeTest_suite<string_type, string_adaptor>());

  Loader loader;
  // Xalan supplied test cases
  //runner.addTest("attribset", loader.XSLTTest_suite("attribset"));
  runner.addTest("attribvaltemplate", loader.XSLTTest_suite("attribvaltemplate"));
  runner.addTest("axes", loader.XSLTTest_suite("axes"));
  runner.addTest("boolean", loader.XSLTTest_suite("boolean"));
  runner.addTest("conditional", loader.XSLTTest_suite("conditional"));
  runner.addTest("conflictres", loader.XSLTTest_suite("conflictres"));
  runner.addTest("copy", loader.XSLTTest_suite("copy"));
  runner.addTest("dflt", loader.XSLTTest_suite("dflt"));
  runner.addTest("expression", loader.XSLTTest_suite("expression"));
  runner.addTest("extend", loader.XSLTTest_suite("extend"));
  //runner.addTest("idkey", loader.XSLTTest_suite("idkey"));
  runner.addTest("impincl", loader.XSLTTest_suite("impincl"));
  runner.addTest("lre", loader.XSLTTest_suite("lre"));
  runner.addTest("match", loader.XSLTTest_suite("match"));
  runner.addTest("math", loader.XSLTTest_suite("math"));
  runner.addTest("mdocs", loader.XSLTTest_suite("mdocs"));
  runner.addTest("message", loader.XSLTTest_suite("message"));
  runner.addTest("modes", loader.XSLTTest_suite("modes"));
  runner.addTest("namedtemplate", loader.XSLTTest_suite("namedtemplate"));
  runner.addTest("namespace", loader.XSLTTest_suite("namespace"));
  runner.addTest("node", loader.XSLTTest_suite("node"));
  //runner.addTest("numberformat", loader.XSLTTest_suite("numberformat"));
  //runner.addTest("numbering", loader.XSLTTest_suite("numbering"));
  runner.addTest("output", loader.XSLTTest_suite("output"));
  runner.addTest("position", loader.XSLTTest_suite("position"));
  runner.addTest("predicate", loader.XSLTTest_suite("predicate"));
  runner.addTest("processorinfo", loader.XSLTTest_suite("processorinfo"));
  runner.addTest("reluri", loader.XSLTTest_suite("reluri"));
  runner.addTest("select", loader.XSLTTest_suite("select"));
  runner.addTest("sort", loader.XSLTTest_suite("sort"));
  runner.addTest("string", loader.XSLTTest_suite("string"));
  runner.addTest("variable", loader.XSLTTest_suite("variable"));
  runner.addTest("ver", loader.XSLTTest_suite("ver"));
  runner.addTest("whitespace", loader.XSLTTest_suite("whitespace"));

  // MSFT supplied test cases
  runner.addTest("AVTs", loader.XSLTTest_suite("AVTs"));
  //runner.addTest("AttributeSets", loader.XSLTTest_suite("AttributeSets"));
  runner.addTest("Attributes", loader.XSLTTest_suite("Attributes"));
  runner.addTest("BVTs", loader.XSLTTest_suite("BVTs"));
  runner.addTest("Comment", loader.XSLTTest_suite("Comment"));
  runner.addTest("Completeness", loader.XSLTTest_suite("Completeness"));
  runner.addTest("ConflictResolution", loader.XSLTTest_suite("ConflictResolution"));
  runner.addTest("Copying", loader.XSLTTest_suite("Copying"));
  runner.addTest("Elements", loader.XSLTTest_suite("Elements"));
  runner.addTest("Errors", loader.XSLTTest_suite("Errors"));
  runner.addTest("Fallback", loader.XSLTTest_suite("Fallback"));
  runner.addTest("ForEach", loader.XSLTTest_suite("ForEach"));
  //runner.addTest("FormatNumber", loader.XSLTTest_suite("FormatNumber"));
  runner.addTest("ForwardComp", loader.XSLTTest_suite("ForwardComp"));
  //runner.addTest("Import", loader.XSLTTest_suite("Import"));
  //runner.addTest("Keys", loader.XSLTTest_suite("Keys"));
  runner.addTest("Messages", loader.XSLTTest_suite("Messages"));
  //runner.addTest("Miscellaneous", loader.XSLTTest_suite("Miscellaneous"));
  runner.addTest("Modes", loader.XSLTTest_suite("Modes"));
  //runner.addTest("NamedTemplates", loader.XSLTTest_suite("NamedTemplates"));
  //runner.addTest("Namespace", loader.XSLTTest_suite("Namespace"));
  //runner.addTest("Namespace-alias", loader.XSLTTest_suite("Namespace-alias"));
  //runner.addTest("Namespace_XPath", loader.XSLTTest_suite("Namespace_XPath"));
  //runner.addTest("Number", loader.XSLTTest_suite("Number"));
  //runner.addTest("Output", loader.XSLTTest_suite("Output"));
  runner.addTest("ProcessingInstruction", loader.XSLTTest_suite("ProcessingInstruction"));

  runner.addTest("RTF", loader.XSLTTest_suite("RTF"));
  runner.addTest("Sorting", loader.XSLTTest_suite("Sorting"));
  //runner.addTest("Stylesheet", loader.XSLTTest_suite("Stylesheet"));
  //runner.addTest("Template", loader.XSLTTest_suite("Template"));
  //runner.addTest("Text", loader.XSLTTest_suite("Text"));
  //runner.addTest("Valueof", loader.XSLTTest_suite("Valueof"));
  //runner.addTest("Variables", loader.XSLTTest_suite("Variables"));
  //runner.addTest("Whitespaces", loader.XSLTTest_suite("Whitespaces"));
  runner.addTest("XSLTFunctions", loader.XSLTTest_suite("XSLTFunctions"));

  runner.addTest("ArabicaErrors", loader.ArabicaTest_suite("errors"));
  runner.addTest("ArabicaInclude", loader.ArabicaTest_suite("include"));
  runner.addTest("ArabicaProcessingInstruction", loader.ArabicaTest_suite("processing-instruction"));
  runner.addTest("ArabicaStylesheets", loader.ArabicaTest_suite("stylesheet"));

  runner.run(argc, argv);

  return 77;
}
