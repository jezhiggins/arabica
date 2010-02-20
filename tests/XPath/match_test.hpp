#ifndef XPATHIC_MATCH_TEST_HPP
#define XPATHIC_MATCH_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

template<class string_type, class string_adaptor>
class TestIdFunction : public Arabica::XPath::XPathFunction<string_type, string_adaptor>
{
public:
  TestIdFunction(const std::vector<Arabica::XPath::XPathExpression<string_type, string_adaptor> >& args) :
      Arabica::XPath::XPathFunction<string_type, string_adaptor>(1, 1, args) { }

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::STRING; }

  virtual Arabica::XPath::XPathValue_impl<string_type, string_adaptor>* evaluate(const Arabica::DOM::Node<string_type, string_adaptor>& context, 
                                            const Arabica::XPath::ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    string_type name = string_adaptor::construct_from_utf8("test-");
    string_adaptor::append(name, context.getLocalName());
    return new Arabica::XPath::StringValue<string_type, string_adaptor>(name);
  } // evaluate
}; // TestIdFunction

template<class string_type, class string_adaptor>
class TestKeyFunction : public Arabica::XPath::XPathFunction<string_type, string_adaptor>
{
public:
  TestKeyFunction(const std::vector<Arabica::XPath::XPathExpression<string_type, string_adaptor> >& args) :
      Arabica::XPath::XPathFunction<string_type, string_adaptor>(2, 2, args) { }

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::STRING; }

  virtual Arabica::XPath::XPathValue_impl<string_type, string_adaptor>* evaluate(const Arabica::DOM::Node<string_type, string_adaptor>& context, 
                                            const Arabica::XPath::ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    string_type name = string_adaptor::construct_from_utf8("test-");
    string_adaptor::append(name, context.getLocalName());
    return new Arabica::XPath::StringValue<string_type, string_adaptor>(name);
  } // evaluate
}; // TestKeyFunction

template<class string_type, class string_adaptor>
class TestIdKeyFunctionResolver : public Arabica::XPath::NullFunctionResolver<string_type, string_adaptor>
{
  //typedef string_adaptorstring_adaptor;
public:
  virtual Arabica::XPath::XPathFunction<string_type, string_adaptor>* resolveFunction(
                                         const string_type& /* namespace_uri */,
                                         const string_type& name,
                                         const std::vector<Arabica::XPath::XPathExpression<string_type, string_adaptor> >& argExprs) const
  {
    if(name == string_adaptor::construct_from_utf8("id"))
      return new TestIdFunction<string_type, string_adaptor>(argExprs);
    if(name == string_adaptor::construct_from_utf8("key"))
      return new TestKeyFunction<string_type, string_adaptor>(argExprs);
    return 0;
  } // resolveFunction
}; // class TestFunctionResolver


template<class string_type, class string_adaptor>
class MatchTest : public TestCase
{
  Arabica::XPath::XPath<string_type, string_adaptor> parser;
  TestIdKeyFunctionResolver<string_type, string_adaptor> tfr;
  typedef string_adaptor SA;

public:
  MatchTest(std::string name) : TestCase(name)
  {
  } // MatchTest

  void setUp()
  {
    parser.setFunctionResolver(tfr);
  } // setUp

  void testParse()
  {
    using namespace Arabica::XPath;
    assertTrue(compileThis("@hello"));
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
    assertTrue(compileThis("hello"));
    assertTrue(compileThis("doc"));
    assertTrue(compileThis("child::hello"));
    assertTrue(compileThis("attribute::hello"));
    assertTrue(compileThis("hello[@ref]"));
    assertTrue(compileThis("@hello[../poop]"));
    assertTrue(compileThis("child::hello[../poop]"));
    assertTrue(compileThis("attribute::hello[../poop]"));
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
    assertTrue(compileThis("node()|@*"));
    assertTrue(compileThis("node()|attribute::*"));
    assertTrue(compileThis("element[@type]|element[complexType]|attribute"));
    assertTrue(compileThis("node()|/"));
    assertTrue(compileThis("/|node()"));
    assertTrue(compileThis("node|/"));
    assertTrue(compileThis("/|node"));
    assertTrue(compileThis("node|/|//charlie"));
    assertTrue(compileThis("//charlie|/|node"));
    assertTrue(compileThis("/|*"));
    assertTrue(compileThis("*|/"));
    assertTrue(compileThis("* | /"));
    assertTrue(compileThis("   / | *   "));
    assertTrue(compileThis("     / | *    "));
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
    Arabica::DOM::Document<string_type, string_adaptor> doc = parseXML("<doc><para>hello</para></doc>");

    assertTrue(applyMatch("/", doc));

    assertFalse(applyMatch("node()", doc));
    assertFalse(applyMatch("*", doc));
    assertFalse(applyMatch("@charlie", doc));
  } // testEvaluateDocMatch

  void testDocElementMatch()
  {
    Arabica::DOM::Document<string_type, string_adaptor> doc = parseXML("<doc><para>hello</para></doc>");

    assertTrue(applyMatch("doc", doc.getFirstChild()));
    assertTrue(applyMatch("doc[para]", doc.getFirstChild()));
    assertTrue(applyMatch("*", doc.getFirstChild()));
    assertTrue(applyMatch("node()", doc.getFirstChild()));
    assertTrue(applyMatch("/doc", doc.getFirstChild()));
    assertTrue(applyMatch("//doc", doc.getFirstChild()));
    assertTrue(applyMatches("comment()|doc", doc.getFirstChild()));
    assertTrue(applyMatches("comment()|/doc", doc.getFirstChild()));
    assertTrue(applyMatches("comment()|//doc", doc.getFirstChild()));
    assertTrue(applyMatches("processing-instruction()|comment()|doc", doc.getFirstChild()));
    assertTrue(applyMatches("processing-instruction()|comment()|/doc", doc.getFirstChild()));
    assertTrue(applyMatches("processing-instruction()|comment()|//doc", doc.getFirstChild()));
    assertTrue(applyMatches("processing-instruction()|doc|comment()", doc.getFirstChild()));
    assertTrue(applyMatches("processing-instruction()|/doc|comment()", doc.getFirstChild()));
    assertTrue(applyMatches("processing-instruction()|//doc|comment()", doc.getFirstChild()));
    assertTrue(applyMatches("doc|processing-instruction()|comment()", doc.getFirstChild()));
    assertTrue(applyMatches("/doc|processing-instruction()|comment()", doc.getFirstChild()));
    assertTrue(applyMatches("//doc|processing-instruction()|comment()", doc.getFirstChild()));
  } // testDocElementMatch

  void testDocElementNotMatch()
  {
    Arabica::DOM::Document<string_type, string_adaptor> doc = parseXML("<doc><para>hello</para></doc>");

    assertFalse(applyMatch("para", doc.getFirstChild()));
    assertFalse(applyMatch("@*", doc.getFirstChild()));
    assertFalse(applyMatch("text()", doc.getFirstChild()));
    assertFalse(applyMatch("comment()", doc.getFirstChild()));
    assertFalse(applyMatch("processing-instruction()", doc.getFirstChild()));
    assertFalse(applyMatch("//para", doc.getFirstChild()));
    assertFalse(applyMatch("/para", doc.getFirstChild()));
    assertFalse(applyMatches("/para|text()", doc.getFirstChild()));
    assertFalse(applyMatches("/para|@*", doc.getFirstChild()));
    assertFalse(applyMatches("/para|poopsicle|comment()", doc.getFirstChild()));
    assertFalse(applyMatch("/", doc.getFirstChild()));
  } // testDocElementNotMatch

  void testAttributeMatch()
  {
    Arabica::DOM::Document<string_type, string_adaptor> doc = parseXML("<doc><para id='woop' name='charlie'>hello</para></doc>");
    Arabica::DOM::Node<string_type, string_adaptor> a1 = doc.getFirstChild().getFirstChild().getAttributes().getNamedItem(SA::construct_from_utf8("id"));
    Arabica::DOM::Node<string_type, string_adaptor> a2 = doc.getFirstChild().getFirstChild().getAttributes().getNamedItem(SA::construct_from_utf8("name"));

    assertTrue(applyMatch("@id", a1));
    assertTrue(applyMatch("@*", a1));
    assertTrue(applyMatch("para/@id", a1));
    assertTrue(applyMatch("node()/@id", a1));
    assertTrue(applyMatch("doc//@*", a1));
    assertTrue(applyMatch("//@*", a1));

    assertFalse(applyMatch("@id", a2));
    assertTrue(applyMatch("@*", a2));
    assertFalse(applyMatch("para/@id", a2));
    assertTrue(applyMatch("doc/para/@*", a2));
    assertFalse(applyMatch("@id[../para]", a2));

    assertFalse(applyMatch("node()", a1));
    assertFalse(applyMatch("*", a1));
    assertFalse(applyMatch("pod/para/@*", a1));
    assertFalse(applyMatch("/", a1));
    assertFalse(applyMatch("/", a2));
    assertFalse(applyMatches("/|comment()", a2));

    assertTrue(applyMatches("@id|@name", a1));
    assertTrue(applyMatches("@id|@name", a2));
    assertTrue(applyMatches("@name|@id", a1));
    assertTrue(applyMatches("@name|@id", a2));
  } // testAttributeMatch

  void testCommentMatch()
  {
    Arabica::DOM::Document<string_type, string_adaptor> doc = parseXML("<doc><para>hello</para><!-- woo --></doc>");
    Arabica::DOM::Node<string_type, string_adaptor> comment = doc.getFirstChild().getLastChild();

    assertFalse(applyMatch("comment()", doc));
    assertFalse(applyMatch("comment()", doc.getFirstChild()));
    assertFalse(applyMatch("comment()", doc.getFirstChild().getFirstChild()));
    assertTrue(applyMatch("comment()", comment));
  } // testCommentMatch

  void testProcessingInstructionMatch()
  {
    Arabica::DOM::Document<string_type, string_adaptor> doc = parseXML("<doc><para>hello</para><?target data?></doc>");
    Arabica::DOM::Node<string_type, string_adaptor> pi = doc.getFirstChild().getLastChild();

    assertFalse(applyMatch("processing-instruction()", doc));
    assertFalse(applyMatch("processing-instruction()", doc.getFirstChild()));
    assertFalse(applyMatch("processing-instruction()", doc.getFirstChild().getFirstChild()));
    assertTrue(applyMatch("processing-instruction()", pi));

    assertFalse(applyMatch("processing-instruction('target')", doc));
    assertFalse(applyMatch("processing-instruction('target')", doc.getFirstChild()));
    assertFalse(applyMatch("processing-instruction('target')", doc.getFirstChild().getFirstChild()));
    assertTrue(applyMatch("processing-instruction('target')", pi));

    assertFalse(applyMatch("processing-instruction('budget')", doc));
    assertFalse(applyMatch("processing-instruction('budget')", doc.getFirstChild()));
    assertFalse(applyMatch("processing-instruction('budget')", doc.getFirstChild().getFirstChild()));
    assertFalse(applyMatch("processing-instruction('budget')", pi));
  } // testProcessingInstructionMatch

  void testNameTestMatch()
  {
    Arabica::XPath::StandardNamespaceContext<string_type, string_adaptor> nsContext;
    nsContext.addNamespaceDeclaration(SA::construct_from_utf8("bang"), SA::construct_from_utf8("bang"));
    parser.setNamespaceContext(nsContext);

    Arabica::DOM::Document<string_type, string_adaptor> doc = parseXML("<bang:doc xmlns:bang='bang'><bang:para>hello</bang:para></bang:doc>");

    assertFalse(applyMatch("bang:*", doc));
    assertTrue(applyMatch("bang:*", doc.getFirstChild()));
    assertTrue(applyMatch("bang:*", doc.getFirstChild().getFirstChild()));
    assertFalse(applyMatch("bang:*", doc.getFirstChild().getFirstChild().getFirstChild()));

    assertFalse(applyMatch("bang:para", doc));
    assertFalse(applyMatch("bang:para", doc.getFirstChild()));
    assertTrue(applyMatch("bang:para", doc.getFirstChild().getFirstChild()));
    assertFalse(applyMatch("bang:para", doc.getFirstChild().getFirstChild().getFirstChild()));

    assertFalse(applyMatch("bang:doc", doc));
    assertTrue(applyMatch("bang:doc", doc.getFirstChild()));
    assertFalse(applyMatch("bang:doc", doc.getFirstChild().getFirstChild()));
    assertFalse(applyMatch("bang:doc", doc.getFirstChild().getFirstChild().getFirstChild()));

    assertFalse(applyMatch("bang:*/bang:para", doc));
    assertFalse(applyMatch("bang:*/bang:para", doc.getFirstChild()));
    assertTrue(applyMatch("bang:*/bang:para", doc.getFirstChild().getFirstChild()));
    assertFalse(applyMatch("bang:*/bang:para", doc.getFirstChild().getFirstChild().getFirstChild()));

    parser.resetNamespaceContext();
  } // testNameTestMatch

  void testPriority()
  {
    using namespace Arabica::XPath;
    Arabica::XPath::StandardNamespaceContext<string_type, string_adaptor> nsContext;
    nsContext.addNamespaceDeclaration(SA::construct_from_utf8("bang"), SA::construct_from_utf8("bang"));
    parser.setNamespaceContext(nsContext);

    assertEquals(0.5, matchPriority("/"), 0);
    assertEquals(0.5, matchPriority("/element"), 0);
    assertEquals(0.5, matchPriority("//element"), 0);

    assertEquals(-0.5, matchPriority("node()"), 0);
    assertEquals(-0.5, matchPriority("child::node()"), 0);
    assertEquals(-0.5, matchPriority("attribute::node()"), 0);
    assertEquals(-0.5, matchPriority("@node()"), 0);
    assertEquals(-0.5, matchPriority("text()"), 0);
    assertEquals(-0.5, matchPriority("child::text()"), 0);
    assertEquals(-0.5, matchPriority("comment()"), 0);
    assertEquals(-0.5, matchPriority("child::comment()"), 0);
    assertEquals(-0.5, matchPriority("processing-instruction()"), 0);
    assertEquals(-0.5, matchPriority("child::processing-instruction()"), 0);
    assertEquals(-0.5, matchPriority("*"), 0);
    assertEquals(-0.5, matchPriority("child::*"), 0);
    assertEquals(-0.5, matchPriority("attribute::*"), 0);
    assertEquals(-0.5, matchPriority("@*"), 0);

    assertEquals(-0.25, matchPriority("bang:*"), 0);
    assertEquals(-0.25, matchPriority("child::bang:*"), 0);
    assertEquals(-0.25, matchPriority("attribute::bang:*"), 0);
    assertEquals(-0.25, matchPriority("@bang:*"), 0);

    assertEquals(0, matchPriority("processing-instruction('noon')"), 0);
    assertEquals(0, matchPriority("element"), 0);
    assertEquals(0, matchPriority("hello"), 0);
    assertEquals(0, matchPriority("doc"), 0);
    assertEquals(0, matchPriority("@hello"), 0);
    assertEquals(0, matchPriority("child::hello"), 0);
    assertEquals(0, matchPriority("attribute::hello"), 0);

    assertEquals(0.5, matchPriority("*[2]"), 0);
    assertEquals(0.5, matchPriority("element/child/child"), 0);
    assertEquals(0.5, matchPriority("element/child[@id='1']/child"), 0);
    assertEquals(0.5, matchPriority("element/child[@id='1']/child[@id='1']"), 0);
    assertEquals(0.5, matchPriority("element/child::child[@id='1']/child::child"), 0);
    assertEquals(0.5, matchPriority("element/child::child[@id='1']/child::child[@id='1']"), 0);
    assertEquals(0.5, matchPriority("/element/child/child"), 0);
    assertEquals(0.5, matchPriority("/element/child[@id='1']/child"), 0);
    assertEquals(0.5, matchPriority("//element/child/child"), 0);
    assertEquals(0.5, matchPriority("/element//child/child"), 0);
    assertEquals(0.5, matchPriority("//element//child/child"), 0);
    assertEquals(0.5, matchPriority("//element//child//child"), 0);
    assertEquals(0.5, matchPriority("/bang:*"), 0);
    assertEquals(0.5, matchPriority("//bang:*"), 0);
    assertEquals(0.5, matchPriority("element[@ref]"), 0);
    assertEquals(0.5, matchPriority("hello[@ref]"), 0);
    assertEquals(0.5, matchPriority("@hello[../poop]"), 0);
    assertEquals(0.5, matchPriority("child::hello[../poop]"), 0);
    assertEquals(0.5, matchPriority("attribute::hello[../poop]"), 0);
    assertEquals(0.5, matchPriority("element/child"), 0);
    assertEquals(0.5, matchPriority("bang:element/bang:child"), 0);
    assertEquals(0.5, matchPriority("bang:*/bang:child"), 0);
    assertEquals(0.5, matchPriority("/element/child"), 0);
    assertEquals(0.5, matchPriority("//element/child"), 0);
    assertEquals(0.5, matchPriority("/element//child"), 0);
    assertEquals(0.5, matchPriority("//element//child"), 0);
    assertEquals(0.5, matchPriority("element/child::child"), 0);
    assertEquals(0.5, matchPriority("child::element/@child"), 0);
    assertEquals(0.5, matchPriority("/child::element/child::child"), 0);
    assertEquals(0.5, matchPriority("/child::element/@child"), 0);
    assertEquals(0.5, matchPriority("/child::element/attribute::child"), 0);
    assertEquals(0.5, matchPriority("//element/child::child"), 0);
    assertEquals(0.5, matchPriority("/child::element//child::child"), 0);
    assertEquals(0.5, matchPriority("//child::element//child::child"), 0);

    parser.resetNamespaceContext();
  } // testPriority

  void testPriority2()
  {
    assertEquals(-0.5, matchPriority("node()"), 0);
  } // testPriority2

  void testPriority3()
  {
    assertEquals(-0.5, matchPriority("*"), 0);
  } // testPriority3

  void testPriority4()
  {
    assertEquals(0, matchPriority("foo"), 0);
  } // testPriority4

  void testIdKey()
  {
    assertTrue(compileThis("id('nob')"));
    assertTrue(compileThis("id(    'nob'   )"));
    assertTrue(dontCompileThis("id()"));
    assertTrue(dontCompileThis("id(nob)"));
    assertTrue(dontCompileThis("id('nob','c')"));
  } // testIdKey

  void testIdKey2()
  {
    assertTrue(compileThis("key('a','b')"));
    assertTrue(compileThis("key('a', 'b')"));
//    assertTrue(compileThis("key('a','b')/woot"));
    assertTrue(dontCompileThis("key()"));
    assertTrue(dontCompileThis("key(a)"));
    assertTrue(dontCompileThis("key('a', 'b', 'c')"));
    assertTrue(dontCompileThis("key(a, 'b')"));
  } // testIdKey2

  bool dontCompileThis(const char* path)
  {
    try {
      compileMatches(path);
      return false;
    }
    catch(const Arabica::XPath::SyntaxException&) {
    }
    return true;
  } // dontCompileThis

  bool compileThis(const char* path)
  {
    try {
      compileMatches(path);
      return true;
    }
    catch(const Arabica::XPath::UnsupportedException&) {
    }
    catch(const Arabica::XPath::SyntaxException& ex) {
      std::cerr << ex.what() << std::endl;
    }
    return false;
  } // compileThis

  std::vector<Arabica::XPath::MatchExpr<string_type, string_adaptor> > matches;

  Arabica::XPath::MatchExpr<string_type, string_adaptor> compileMatch(const char* match)
  {
    //std::cout << "----\n" << match << std::endl;
    compileMatches(match);
    assertEquals(1, matches.size());
    return matches[0];
  } // compileMatch

  double matchPriority(const char* match)
  {
    compileMatches(match);
    assertEquals(1, matches.size());
    return matches[0].priority();
  } // matchPriority

  std::vector<Arabica::XPath::MatchExpr<string_type, string_adaptor> >& compileMatches(const char* match)
  {
    matches = parser.compile_match(SA::construct_from_utf8(match));
    return matches;
  } // compileMatches

  bool applyMatches(const char* match, const Arabica::DOM::Node<string_type, string_adaptor>& node)
  {
    compileMatches(match);
    Arabica::XPath::ExecutionContext<string_type, string_adaptor> context;
    for(unsigned int i = 0; i < matches.size(); ++i)
      if(matches[i].evaluate(node, context))
      	return true;
    return false;
  } // applyMatches

  bool applyMatch(const char* match, const Arabica::DOM::Node<string_type, string_adaptor>& node)
  {
    Arabica::XPath::ExecutionContext<string_type, string_adaptor> context;
    return compileMatch(match).evaluate(node, context);
  } // applyMatch

  Arabica::DOM::Document<string_type, string_adaptor> parseXML(const char* match)
  {
    std::stringstream ss;
    ss << match;

    Arabica::SAX::InputSource<string_type, string_adaptor> is(ss);
    Arabica::SAX::CatchErrorHandler<string_type, string_adaptor> eh;
    Arabica::SAX2DOM::Parser<string_type, string_adaptor> parser;
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
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testAttributeMatch", &MatchTest<string_type, string_adaptor>::testAttributeMatch));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testCommentMatch", &MatchTest<string_type, string_adaptor>::testCommentMatch));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testProcessingInstructionMatch", &MatchTest<string_type, string_adaptor>::testProcessingInstructionMatch));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testNameTestMatch", &MatchTest<string_type, string_adaptor>::testNameTestMatch));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testPriority", &MatchTest<string_type, string_adaptor>::testPriority));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testPriority2", &MatchTest<string_type, string_adaptor>::testPriority2));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testPriority3", &MatchTest<string_type, string_adaptor>::testPriority3));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testPriority4", &MatchTest<string_type, string_adaptor>::testPriority4));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testIdKey", &MatchTest<string_type, string_adaptor>::testIdKey));
  suiteOfTests->addTest(new TestCaller<MatchTest<string_type, string_adaptor> >("testIdKey2", &MatchTest<string_type, string_adaptor>::testIdKey2));
 
  return suiteOfTests;
} // MatchTest_suite

#endif

