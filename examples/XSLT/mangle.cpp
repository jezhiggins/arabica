
#pragma warning(disable : 4250)

#include <iostream>
#include <string>
#include <sstream>

#include <SAX/InputSource.h>
#include <DOM/SAX2DOM/SAX2DOM.h>
#include <XSLT/XSLT.hpp>

void test_suite(int argc, const char* argv[]);
DOM::Document<std::string> buildDOM(const std::string& xml);

int main(int argc, const char* argv[])
{
/*
	if((argc >= 2) && (std::string("test") == argv[1]))
	{
		test_suite(argc, argv);
		return 0;
	} // if ...
*/

  if(argc != 3)
  {
    std::cout << "mangle is an (in-development) XSLT processor\n" 
              << argv[0] << " xmlfile xsltfile" << std::endl;
    return 0;
  } // if ...

  Arabica::XSLT::StylesheetCompiler compiler;
  std::ostringstream errors;
  try 
  {
    SAX::InputSource source(argv[2]);
    std::auto_ptr<Arabica::XSLT::Stylesheet> stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
    {
      std::cerr << "Couldn't compile stylesheet: " << compiler.error() << std::endl;
      return -1;
    } // if ...

    stylesheet->set_error_output(errors);

    DOM::Document<std::string> document = buildDOM(argv[1]); 
    if(document == 0)
    {
      std::cerr << "Could not parse XML source" << std::endl;
      return 0;
    } // if ...
    document.normalize();
    stylesheet->execute(document);
  }
  catch(const std::runtime_error& ex)
  {
    std::cerr << ex.what() << std::endl;
  } // catch

  std::cerr << "\n\n" << errors.str() << std::endl;

  return 0;
} // main

DOM::Document<std::string> buildDOM(const std::string& filename)
{
  SAX::InputSource is(filename);
  SAX2DOM::Parser<std::string> parser;
  parser.parse(is);       

  return parser.getDocument();
} // buildDOM

/*
///////////////////////////////////////////////
#include "../src/test/CppUnit/TestRunner.hpp"
#include "../src/test/CppUnit/framework/Test.h"
#include "../src/test/CppUnit/framework/TestSuite.h"

#include "tests/scope_test.hpp"

typedef std::string string_type;
typedef Arabica::default_string_adaptor<std::string> string_adaptor;

void test_suite(int argc, const char* argv[])
{
  TestRunner runner;

  runner.addTest("ScopeTest", ScopeTest_suite<string_type, string_adaptor>());

	runner.run(argc-1, argv+1);
} // test_suite
*/
