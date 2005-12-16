#ifndef XPATHIC_MATCH_TEST_HPP
#define XPATHIC_MATCH_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.h>


template<class string_type, class string_adaptor>
class MatchTest : public TestCase
{
  Arabica::XPath::XPath<string_type> parser;
  typedef string_adaptor SA;

public:
  MatchTest(std::string name) : TestCase(name)
  {
  } // MatchTest

  void setUp()
  {
  } // setUp

  void testParse()
  {
    using namespace Arabica::XPath;
    assertTrue(compileThis("/"));
    assertTrue(compileThis("/element"));
    assertTrue(compileThis("//element"));
    assertTrue(compileThis("node()"));
    assertTrue(compileThis("text()"));
    assertTrue(compileThis("element"));
    assertTrue(compileThis("element/child"));
    assertTrue(compileThis("/element/child"));
    assertTrue(compileThis("//element/child"));
    assertTrue(compileThis("/element//child"));
    assertTrue(compileThis("//element//child"));
    assertTrue(compileThis("element/child/child"));
    assertTrue(compileThis("/element/child/child"));
    assertTrue(compileThis("//element/child/child"));
    assertTrue(compileThis("/element//child/child"));
    assertTrue(compileThis("//element//child/child"));
    assertTrue(compileThis("//element//child//child"));
    assertTrue(compileThis("element[@ref]"));
    assertTrue(compileThis("element[@type]|element[complexType]|attribute"));
    assertTrue(compileThis("node()|@*"));
    assertTrue(compileThis("hello"));
    assertTrue(compileThis("@hello"));
    assertTrue(compileThis("child::hello"));
    assertTrue(compileThis("attribute::hello"));
    assertTrue(compileThis("node()|attribute::*"));
  } // testParse

  void testParseFails()
  {
    std::cerr << "\n\n\ntestParseFails";
    using namespace Arabica::XPath;
    assertTrue(dontCompileThis("boolean(../hello)"));
    assertTrue(dontCompileThis("../hello"));
    assertTrue(dontCompileThis("following-sibling::hello"));
    assertTrue(dontCompileThis("descendant::hello"));
    assertTrue(dontCompileThis("ancestor-or-self::hello"));
    assertTrue(dontCompileThis("///"));
    assertTrue(dontCompileThis("test///test"));
    assertTrue(dontCompileThis("descendant-or-self::element"));
    assertTrue(dontCompileThis("//element/following-sibling::trousers"));
  } // testParseFails

  bool dontCompileThis(const char* path)
  {
    try {
      parser.compile_match(SA::construct_from_utf8(path));
      return false;
    }
    catch(const Arabica::XPath::SyntaxException& ex) {
      std::cerr << ex.what() << std::endl;
    }
    return true;
  } // dontCompileThis

  bool compileThis(const char* path)
  {
    try {
      parser.compile_match(SA::construct_from_utf8(path));
      return true;
    }
    catch(const Arabica::XPath::UnsupportedException&) {
      return true;
    }
    catch(const Arabica::XPath::SyntaxException& ex) {
      std::cerr << ex.what() << std::endl;
    }
    return false;
  } // compileThis

}; // class MatchTest

template<class string_type, class string_adaptor>
TestSuite* MatchTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testParse", &MatchTest<string_type, string_adaptor>::testParse));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testParseFail", &MatchTest<string_type, string_adaptor>::testParseFails));
 
  return suiteOfTests;
} // MatchTest_suite

#endif

