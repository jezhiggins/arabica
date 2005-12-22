#ifndef XPATHIC_MATCH_TEST_HPP
#define XPATHIC_MATCH_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/SAX2DOM/SAX2DOM.h>
#include <SAX/helpers/CatchErrorHandler.h>


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
    assertTrue(compileThis("element/child/child"));
    assertTrue(compileThis("element/child[@id='1']/child"));
    assertTrue(compileThis("element/child[@id='1']/child[@id='1']"));
    assertTrue(compileThis("element/child::child[@id='1']/child::child"));
    assertTrue(compileThis("element/child::child[@id='1']/child::child[@id='1']"));
    assertTrue(compileThis("/element/child/child"));
    assertTrue(compileThis("/element/child[@id='1']/child"));
    assertTrue(compileThis("//element/child/child"));
    assertTrue(compileThis("/element//child/child"));
    assertTrue(compileThis("//element//child/child"));
    assertTrue(compileThis("//element//child//child"));
    assertTrue(compileThis("element[@ref]"));
    assertTrue(compileThis("element[@type]|element[complexType]|attribute"));
    assertTrue(compileThis("node()|@*"));
    assertTrue(compileThis("hello"));
    assertTrue(compileThis("doc"));
    assertTrue(compileThis("@hello"));
    assertTrue(compileThis("child::hello"));
    assertTrue(compileThis("attribute::hello"));
    assertTrue(compileThis("hello[@ref]"));
    assertTrue(compileThis("@hello[../poop]"));
    assertTrue(compileThis("child::hello[../poop]"));
    assertTrue(compileThis("attribute::hello[../poop]"));
    assertTrue(compileThis("node()|attribute::*"));
    assertTrue(compileThis("element/child"));
    assertTrue(compileThis("/element/child"));
    assertTrue(compileThis("//element/child"));
    assertTrue(compileThis("/element//child"));
    assertTrue(compileThis("//element//child"));
    assertTrue(compileThis("element/child::child"));
    assertTrue(compileThis("child::element/@child"));
    assertTrue(compileThis("/child::element/child::child"));
    assertTrue(compileThis("/child::element/@child"));
    assertTrue(compileThis("/child::element/attribute::child"));
    assertTrue(compileThis("//element/child::child"));
    assertTrue(compileThis("/child::element//child::child"));
    assertTrue(compileThis("//child::element//child::child"));
  } // testParse

  void testParseFails()
  {
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

  void testEvaluateDocMatch()
  {
    DOM::Document<string_type> doc = parseXML("<doc><para>hello</para></doc>");
    assertTrue(compileMatch("/")->evaluateAsBool(doc));
  } // testEvaluateDocMatch

  void testDocElementMatch()
  {
    DOM::Document<string_type> doc = parseXML("<doc><para>hello</para></doc>");

    assertTrue(compileMatch("doc")->evaluateAsBool(doc.getDocumentElement()));
    assertTrue(compileMatch("doc[para]")->evaluateAsBool(doc.getDocumentElement()));
    assertTrue(compileMatch("*")->evaluateAsBool(doc.getDocumentElement()));
    assertTrue(compileMatch("node()")->evaluateAsBool(doc.getDocumentElement()));
    assertTrue(compileMatch("/doc")->evaluateAsBool(doc.getDocumentElement()));
    assertTrue(compileMatch("//doc")->evaluateAsBool(doc.getDocumentElement()));
  } // testDocElementMatch

  void testDocElementNotMatch()
  {
    DOM::Document<string_type> doc = parseXML("<doc><para>hello</para></doc>");

    assertFalse(compileMatch("para")->evaluateAsBool(doc.getDocumentElement()));
    assertFalse(compileMatch("text()")->evaluateAsBool(doc.getDocumentElement()));
    assertFalse(compileMatch("comment()")->evaluateAsBool(doc.getDocumentElement()));
    assertFalse(compileMatch("processing-instruction()")->evaluateAsBool(doc.getDocumentElement()));
    assertFalse(compileMatch("//para")->evaluateAsBool(doc.getDocumentElement()));
    assertFalse(compileMatch("/para")->evaluateAsBool(doc.getDocumentElement()));
  } // testDocElementNotMatch


  bool dontCompileThis(const char* path)
  {
    try {
      compileMatch(path);
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
      std::cout << "\n-----\n" << path << "\n";
      compileMatch(path);
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

  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> compileMatch(const char* match)
  {
    return parser.compile_match(SA::construct_from_utf8(match));
  } // compileMatch

  DOM::Document<string_type> parseXML(const char* match)
  {
    std::stringstream ss;
    ss << match;

    SAX::basic_InputSource<string_type> is(ss);
    SAX::CatchErrorHandler<string_type> eh;
    SAX2DOM::Parser<string_type, string_adaptor> parser;
    parser.setErrorHandler(eh);
    parser.parse(is);       

    if(eh.errorsReported())
      throw std::runtime_error(eh.errors());

    return parser.getDocument();
  } // parse
}; // class MatchTest

template<class string_type, class string_adaptor>
TestSuite* MatchTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testParse", &MatchTest<string_type, string_adaptor>::testParse));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testParseFail", &MatchTest<string_type, string_adaptor>::testParseFails));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testEvaluateDocMatch", &MatchTest<string_type, string_adaptor>::testEvaluateDocMatch));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testDocElementMatch", &MatchTest<string_type, string_adaptor>::testDocElementMatch));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testDocElementNotMatch", &MatchTest<string_type, string_adaptor>::testDocElementNotMatch));
 
  return suiteOfTests;
} // MatchTest_suite

#endif

