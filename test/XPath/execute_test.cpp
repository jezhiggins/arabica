#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4267 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.h>

using namespace Arabica::XPath;

class StringVariableResolver : public VariableResolver<std::string>
{
public:
  virtual XPathValuePtr<std::string> resolveVariable(const std::string& name) const
  {
    VarMap::const_iterator n = map_.find(name);
    if(n == map_.end())
      throw UnboundVariableException(name);
    return XPathValuePtr<std::string>(new StringValue((*n).second));
  } // resolveVariable

  void setVariable(const std::string& name, const std::string& value)
  {
    map_[name] = value;
  } // setVariable

private:
  typedef std::map<std::string, std::string> VarMap;
  VarMap map_;
}; // StringVariableResolver

class NodeSetVariableResolver : public VariableResolver<std::string>
{
public:
  virtual XPathValuePtr<std::string> resolveVariable(const std::string& name) const
  {
    VarMap::const_iterator n = map_.find(name);
    if(n == map_.end())
      throw UnboundVariableException(name);
    return XPathValuePtr<std::string>(new NodeSetValue((*n).second));
  } // resolveVariable

  void setVariable(const std::string& name, const NodeSet<std::string>& value)
  {
    map_[name] = value;
  } // setVariable

private:
  typedef std::map<std::string, NodeSet<std::string> > VarMap;
  VarMap map_;
}; // class NodeSetVariableResolver

class TestFunction : public XPathFunction
{
public:
  TestFunction(const std::vector<XPathExpressionPtr<std::string> >& args) :
      XPathFunction(0, 0, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context, 
                                            const ExecutionContext& executionContext) const
  {
    return new StringValue("test-" + context.getLocalName());
  } // evaluate
}; // TestFunction

class TestFunctionResolver : public FunctionResolver
{
public:
  virtual XPathFunction* resolveFunction(const std::string& name,
                                         const std::vector<XPathExpressionPtr<std::string> >& argExprs) const
  {
    if(name == "test-function")
      return new TestFunction(argExprs);
    return 0;
  } // resolveFunction
}; // class TestFunctionResolver

class ExecuteTest : public TestCase
{
  Arabica::XPath::XPath parser;
  DOM::DOMImplementation<std::string> factory_;
  DOM::Document<std::string> document_;

  DOM::Element<std::string> root_;

  DOM::Element<std::string> element1_;
  DOM::Element<std::string> element2_;
  DOM::Element<std::string> element3_;
  DOM::Element<std::string> spinkle_;

  DOM::Attr<std::string> attr_;

  DOM::Text<std::string> text_;

  DOM::Comment<std::string> comment_;

  DOM::ProcessingInstruction<std::string> processingInstruction_;

  DOM::Document<std::string> chapters_;

  DOM::Document<std::string> numbers_;

public:
  ExecuteTest(std::string name) : TestCase(name)
  {
  } // ExecuteTest

  void setUp()
  {
    factory_ = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    document_ = factory_.createDocument("", "root", 0);
    root_ = document_.getDocumentElement();

    element1_ = document_.createElement("child1");
    element2_ = document_.createElement("child2");
    element3_ = document_.createElement("child3");

    element1_.setAttribute("one", "1");

    element2_.setAttribute("one", "1");
    element2_.setAttribute("two", "1");
    element2_.setAttribute("three", "1");
    element2_.setAttribute("four", "1");

    text_ = document_.createTextNode("data");
    comment_ = document_.createComment("comment");
    processingInstruction_ = document_.createProcessingInstruction("target", "data");
    element2_.appendChild(text_);
    spinkle_ = document_.createElement("spinkle");
    element2_.appendChild(spinkle_);
    element2_.appendChild(comment_);
    element2_.appendChild(processingInstruction_);

    attr_ = element1_.getAttributeNode("one");

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);

    chapters_ = factory_.createDocument("", "document", 0);
    chapters_.getFirstChild().appendChild(chapters_.createElement("chapter")).appendChild(chapters_.createTextNode("one"));
    chapters_.getFirstChild().appendChild(chapters_.createElement("chapter")).appendChild(chapters_.createTextNode("two"));
    chapters_.getFirstChild().appendChild(chapters_.createElement("chapter")).appendChild(chapters_.createTextNode("three"));
    chapters_.getFirstChild().appendChild(chapters_.createElement("chapter")).appendChild(chapters_.createTextNode("four"));
    chapters_.getFirstChild().appendChild(chapters_.createElement("chapter")).appendChild(chapters_.createTextNode("five"));

    numbers_ = factory_.createDocument("", "doc", 0);
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("1"));
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("2"));
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("3"));
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("4"));
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("5"));
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("6"));
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("7"));
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("8"));
    numbers_.getFirstChild().appendChild(numbers_.createElement("number")).appendChild(numbers_.createTextNode("9"));
  } // setUp

  void test1()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    DOM::Node<std::string> n = result->asNodeSet()[0];
    assertTrue(root_ == n);
  } // test1

  void test2()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/child2");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    DOM::Node<std::string> n = result->asNodeSet()[0];
    assertTrue(element2_ == n);
  } // test2

  void test3()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(3, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);
  } // test4

  void test4()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*/text()");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(text_ == result->asNodeSet()[0]);
    assertValuesEqual(text_.getNodeValue(), result->asString());
  } // test4

  void test5() 
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*/text()");
    assertValuesEqual(text_.getNodeValue(), xpath->evaluateAsString(document_));
  } // test5

  void test6()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("*");

    XPathValuePtr<std::string> result = xpath->evaluate(document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(root_ == result->asNodeSet()[0]);

    result = xpath->evaluate(root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(3, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);

    result = xpath->evaluate(element1_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());

    result = xpath->evaluate(element2_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());

    result = xpath->evaluate(element3_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());
  } // test6

  void test7()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("/root");

    XPathValuePtr<std::string> result = xpath->evaluate(document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(root_ == result->asNodeSet()[0]);

    result = xpath->evaluate(text_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(root_ == result->asNodeSet()[0]);
  } // test7

  void test8()
  {
    StandardNamespaceContext nsContext;
    nsContext.addNamespaceDeclaration("urn:something:or:other", "ns");
    parser.setNamespaceContext(nsContext);
    XPathExpressionPtr<std::string> xpath = parser.compile("/ns:root");
    parser.resetNamespaceContext();

    XPathValuePtr<std::string> result = xpath->evaluate(document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());

    result = xpath->evaluate(text_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());
  } // test8

  void test9()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("child2");

    XPathValuePtr<std::string> result = xpath->evaluate(root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);

    xpath = parser.compile("./child2");
    result = xpath->evaluate(root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // test9

  void test10()
  {
    assertTrue(root_ == parser.evaluate(".", root_)->asNodeSet()[0]);
  } // test10

  void test11()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("..");

    XPathValuePtr<std::string> result = xpath->evaluate(element3_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(root_ == result->asNodeSet()[0]);
  } // test11

  void test12()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*[2]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    DOM::Node<std::string> n = result->asNodeSet()[0];
    assertTrue(element2_ == n);
  } // test12

  void test13()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[2]/comment()", document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(comment_ == result->asNodeSet()[0]);
  } // test13

  void test14()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[2]/node()[3]", document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(comment_ == result->asNodeSet()[0]);
  } // test14

  void test15()
  {
    XPathValuePtr<std::string> result = parser.evaluate("root/*[spinkle]", document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // test15

  void test16()
  {
    XPathValuePtr<std::string> result = parser.evaluate("root/*[doesnotmatch]", document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());
  } // test16

  void test17()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@two = '1']", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // test17

  void test18()
  {
    StringVariableResolver svr;
    svr.setVariable("index", "1");

    parser.setVariableResolver(svr);
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@two = $index]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);

    parser.resetVariableResolver();
  } // test18

  void test19()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*[position() = 2]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    DOM::Node<std::string> n = result->asNodeSet()[0];
    assertTrue(element2_ == n);
  } // test19

  void test20()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*[last()]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element3_ == result->asNodeSet()[0]);
  } // test20

  void test21()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*[position() != last()]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
  } // test21

  void test22()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*[position() = 2 or position() = 1]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
  } // test22

  void test23()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*[position() = 2 and @two = '1']");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // test23

  void test24()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*[last()][1]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element3_ == result->asNodeSet()[0]);
  } // test24

  void test25()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("root/*[last()][2]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());
  } // test25

  void test26()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("/root/child2/spinkle/ancestor::node()[2]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(result->asNodeSet()[0] == root_);
    assertTrue(result->asNodeSet().forward() == false);
  } // test26

  void test27()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("/root/child2/spinkle/ancestor-or-self::node()[2]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(result->asNodeSet()[0] == element2_);
    assertTrue(result->asNodeSet().forward() == false);
 } // test27

  void test28()
  {
    XPathExpressionPtr<std::string> xpath = parser.compile("/root/child2/spinkle/ancestor-or-self::node()[3]");
    XPathValuePtr<std::string> result = xpath->evaluate(document_);

    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(result->asNodeSet()[0] == root_);
  } // test28

  void test29()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/child::root/child::*[attribute::two = '1']", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // test29

  void test30()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(document_ == result->asNodeSet()[0]);
  } // test30

  void test31()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/", element1_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(document_ == result->asNodeSet()[0]);
  } // test31

  void test32()
  {
    XPathValuePtr<std::string> result = parser.evaluate("//comment()", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(comment_ == result->asNodeSet()[0]);
  } // test32

  void test33()
  {
    XPathValuePtr<std::string> result = parser.evaluate("//comment()", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(comment_ == result->asNodeSet()[0]);
    assertTrue(result->asNodeSet().forward() == true);
  } // test33

  void test34()
  {
    XPathValuePtr<std::string> result = parser.evaluate("//*", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(5, result->asNodeSet().size());
    assertTrue(root_ == result->asNodeSet()[0]);
    assertTrue(element1_ == result->asNodeSet()[1]);
    assertTrue(element2_ == result->asNodeSet()[2]);
    assertTrue(element3_ == result->asNodeSet()[3]);
    assertTrue(spinkle_ == result->asNodeSet()[4]);
  } // test34

  void test35()
  {
    XPathValuePtr<std::string> result = parser.evaluate("//*", element2_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(5, result->asNodeSet().size());
    assertTrue(root_ == result->asNodeSet()[0]);
    assertTrue(element1_ == result->asNodeSet()[1]);
    assertTrue(element2_ == result->asNodeSet()[2]);
    assertTrue(element3_ == result->asNodeSet()[3]);
    assertTrue(spinkle_ == result->asNodeSet()[4]);
  } // test35

  void test36()
  {
    XPathValuePtr<std::string> result = parser.evaluate("//*/*", element2_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(4, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);
    assertTrue(spinkle_ == result->asNodeSet()[3]);
  } // test36

  void test37()
  {
    XPathValuePtr<std::string> result = parser.evaluate("//*/*/*", element2_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(spinkle_ == result->asNodeSet()[0]);
  } // test37

  void test38()
  {
    XPathValuePtr<std::string> result = parser.evaluate("//*/*/*/*", element2_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());
  } // test38

  void test39()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/*/*", element2_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(3, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);
  } // test39

  void test40()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root//*", element2_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(4, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);
    assertTrue(spinkle_ == result->asNodeSet()[3]);
  } // test40

  // see http://jira.codehaus.org/browse/JAXEN-94
  void test41()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("2+1-1+1", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(3.0, result->asNumber(), 0.0);
  } // test41

  void testUnion1()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@one|data]", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
  } // testUnion1

  void testUnion2()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[buttle|tuttle]", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());
    assertTrue(result->asNodeSet().forward() == true);
  } // testUnion2

  void testUnion3()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[preceding-sibling::child2|@two]", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
    assertTrue(element3_ == result->asNodeSet()[1]);
  } // testUnion3

  void testUnion4()
  {
    try {
      XPathValuePtr<std::string> result = parser.evaluate("/root/*[@two|4]", root_);
    } // try
    catch(RuntimeException re) {
      // yay!
    } // catch
  } // testUnion4

  void testUnion5()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[preceding-sibling::child2|@two|following-sibling::child2]", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(3, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);
  } // testUnion5

  void testUnion6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("/root/child2|/root/child1", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
  } // testUnion6

  void testUnion7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("/root/child1|/root/child2", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
  } // testUnion7

  void testUnion8()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("/root/child2/@one|/root/child2|/root/child1", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(3, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element2_.getAttributeNode("one") == result->asNodeSet()[2]);
  } // testUnion8

  void testUnion9()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("/root/child1/@one|/root/child2/@one|/root/child2|/root/child1", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(4, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element1_.getAttributeNode("one") == result->asNodeSet()[1]);
    assertTrue(element2_ == result->asNodeSet()[2]);
    assertTrue(element2_.getAttributeNode("one") == result->asNodeSet()[3]);
  } // testUnion9

  void testUnion10()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("/root/child3|/root/child3/preceding-sibling::*", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(3, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);
  } // testUnion10

  void testUnion11()
  {
    DOM::DocumentFragment<std::string> frag = document_.createDocumentFragment();
    frag.appendChild(document_.createElement("foo"));

    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(frag);
    svr.setVariable("fruit", ns);
    parser.setVariableResolver(svr);

    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit/foo|/root/child3", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(element3_ == result->asNodeSet()[0]);
  } // testUnion11

  void testUnion12()
  {
    DOM::DocumentFragment<std::string> frag = document_.createDocumentFragment();
    DOM::Node<std::string> n1 = document_.createElement("foo");
    DOM::Node<std::string> n2 = document_.createElement("bar");

    frag.appendChild(n1);
    frag.appendChild(n2);

    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(frag);
    svr.setVariable("fruit", ns);
    parser.setVariableResolver(svr);

    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit/bar|$fruit/foo", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(n1 == result->asNodeSet()[0]);
    assertTrue(n2 == result->asNodeSet()[1]);
  } // testUnion12

  void testUnion13()
  {
    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(document_.createElement("foo"));
    svr.setVariable("fruit", ns);
    parser.setVariableResolver(svr);

    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit|/root/child3", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
    assertTrue(element3_ == result->asNodeSet()[0]);
  } // testUnion13

  void testUnion14()
  {
    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(document_.createElement("foo"));
    ns.push_back(document_.createElement("bar"));
    svr.setVariable("fruit", ns);
    parser.setVariableResolver(svr);

    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit|/root/child3|$fruit", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(3, result->asNodeSet().size());
    assertTrue(element3_ == result->asNodeSet()[0]);
  } // testUnion14

  void testPlus1()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[1+1]", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testPlus1

  void testPlus2()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[1+1+1]", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element3_ == result->asNodeSet()[0]);
  } // testPlus2

  void testNodeSetEquality1()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@two = 1]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNodeSetEquality1

  void testNodeSetEquality2()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@two = true()]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNodeSetEquality2

  void testNodeSetEquality3()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@two != false()]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNodeSetEquality3

  void testNodeSetEquality4()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@* = 1]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
  } // testNodeSetEquality4

  void testNodeSetEquality5()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@* = '1']", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
  } // testNodeSetEquality5

  void testNodeSetEquality6()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@* = @one]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
  } // testNodeSetEquality6

  void testNodeSetEquality7()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@* = @two]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNodeSetEquality7

  void testNodeSetEquality8()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/child2[-(@two) = -1]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNodeSetEquality8

  void testNodeSetEquality9()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/child2[-(@two) - 1 = -2]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNodeSetEquality9

  void testCountFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[count(@*) = 4]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testCountFn1

  void testCountFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[count(@*) = 1]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
  } // testCountFn2

  void testCountFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[count(@*) = 999]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());
  } // testCountFn3

  void testNotFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@two != not(true())]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNotFn1

  void testNotFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[@two = not(false())]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNotFn2

  void testBooleanFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[boolean(@three)]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testBooleanFn1

  void testBooleanFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate("/root/*[boolean(1)]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(3, result->asNodeSet().size());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);
  } // testBooleanFn2

  void testNumberFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("number(true())", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testNumberFn1

  void testNumberFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("number(false())", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(0.0, result->asNumber(), 0.0);
  } // testNumberFn2

  void testNumberFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("number(1.5)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.5, result->asNumber(), 0.0);
  } // testNumberFn3

  void testNumberFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("number('1.5')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.5, result->asNumber(), 0.0);
  } // testNumberFn4

  void testNumberFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("number(\"1.5\")", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.5, result->asNumber(), 0.0);
  } // testNumberFn5

  void testNumberFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("number(/root/child2/@one)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testNumberFn6

  void testNumberFn7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("number('trousers')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertTrue(isNaN(result->asNumber()));
  } // testNumberFn7

  void testFloorFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor(1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testFloorFn1

  void testFloorFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor(1.0)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testFloorFn2

  void testFloorFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor('1.0')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testFloorFn3

  void testFloorFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor(1.1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testFloorFn4

  void testFloorFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor(0)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(0.0, result->asNumber(), 0.0);
  } // testFloorFn5

  void testFloorFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor(-1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-1.0, result->asNumber(), 0.0);
  } // testFloorFn6

  void testFloorFn7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor(-1.0)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-1.0, result->asNumber(), 0.0);
  } // testFloorFn7

  void testFloorFn8()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor(-1.1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-2.0, result->asNumber(), 0.0);
  } // testFloorFn8

  void testFloorFn9()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("floor('NaN')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertTrue(isNaN(result->asNumber()));
  } // testFloorFn9

  void testCeilingFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling(1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testCeilingFn1

  void testCeilingFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling(1.0)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testCeilingFn2

  void testCeilingFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling('1.0')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testCeilingFn3

  void testCeilingFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling(1.1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(2.0, result->asNumber(), 0.0);
  } // testCeilingFn4

  void testCeilingFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling(0)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(0.0, result->asNumber(), 0.0);
  } // testCeilingFn5

  void testCeilingFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling(-1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-1.0, result->asNumber(), 0.0);
  } // testCeilingFn6

  void testCeilingFn7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling(-1.0)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-1.0, result->asNumber(), 0.0);
  } // testCeilingFn7

  void testCeilingFn8()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling(-1.1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-1.0, result->asNumber(), 0.0);
  } // testCeilingFn8

  void testCeilingFn9()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("ceiling('NaN')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertTrue(isNaN(result->asNumber()));
  } // testCeilingFn9

  void testStringFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(0)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("0", result->asString());
  } // testStringFn1

  void testStringFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(true())", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("true", result->asString());
  } // testStringFn2

  void testStringFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(false())", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("false", result->asString());
  } // testStringFn3

  void testStringFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(number('poo'))", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("NaN", result->asString());
  } // testStringFn4

  void testStringFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string('NaN')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("NaN", result->asString());
  } // testStringFn5

  void testRoundFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(1.0)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testRoundFn1

  void testRoundFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(1.1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testRoundFn2

  void testRoundFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(1.5)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(2.0, result->asNumber(), 0.0);
  } // testRoundFn3

  void testRoundFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(1.9)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(2.0, result->asNumber(), 0.0);
  } // testRoundFn4

  void testRoundFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(-1.0)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-1.0, result->asNumber(), 0.0);
  } // testRoundFn5

  void testRoundFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(-1.1)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-1.0, result->asNumber(), 0.0);
  } // testRoundFn6

  void testRoundFn7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(-1.5)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-1.0, result->asNumber(), 0.0);
  } // testRoundFn7

  void testRoundFn8()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(-1.9)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-2.0, result->asNumber(), 0.0);
  } // testRoundFn8

  void testRoundFn9()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round('NaN')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertTrue(isNaN(result->asNumber()));
  } // testRoundFn9

  void testRoundFn10()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("round(-0.4)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(-0.0, result->asNumber(), 0.0);
  } // testRoundFn10

  void testSumFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("sum(/root)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(0.0, result->asNumber(), 0.0);
  } // testSumFn1

  void testSumFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("sum(/root/child1/@one)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testSumFn2

  void testSumFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("sum(/root//@one)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(2.0, result->asNumber(), 0.0);
  } // testSumFn3

  void testSumFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("sum(/root/child2/@*)", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(4.0, result->asNumber(), 0.0);
  } // testSumFn4

  void testConcatFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("concat('a', 'b')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("ab", result->asString());
  } // testConcatFn1

  void testConcatFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("concat('a', 'b', 'c')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("abc", result->asString());
  } // testConcatFn2

  void testConcatFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("concat('a', 'b', 'c', 'd')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("abcd", result->asString());
  } // testConcatFn3

  void testConcatFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("concat(/root/child2/@one, /root/child2/@two, /root/child2/@three)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("111", result->asString());
  } // testConcatFn4

  void testConcatFn5()
  {
    try {
      parser.evaluate_expr("concat('please explode')", document_);
      assertTrue(false);
    }
    catch(...) { }
  } // testConcatFn5

  void testStartsWithFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("starts-with('hello', 'charlie drake')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(false, result->asBool());
  } // testStartsWithFn1

  void testStartsWithFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("starts-with('hello', 'hello mother')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(false, result->asBool());
  } // testStartsWithFn2

  void testStartsWithFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("starts-with('hello mother', 'hello')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(true, result->asBool());
  } // testStartsWithFn3

  void testStartsWithFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("starts-with('hello mother', 'hello mother')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(true, result->asBool());
  } // testStartsWithFn4

  void testStringLengthFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string-length('')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(0.0, result->asNumber(), 0.0);
  } // testStringLengthFn1

  void testStringLengthFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string-length('ab')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(2.0, result->asNumber(), 0.0);
  } // testStringLengthFn2

  void testStringLengthFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string-length('abcd')", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(4.0, result->asNumber(), 0.0);
  } // testStringLengthFn3

  void testStringLengthFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string-length(concat('ab', 'cd'))", document_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(4.0, result->asNumber(), 0.0);
  } // testStringLengthFn4

  void testStringLengthFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string-length()", attr_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(1.0, result->asNumber(), 0.0);
  } // testStringLengthFn5

  void testStringLengthFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string-length()", element1_);
    assertValuesEqual(NUMBER, result->type());
    assertDoublesEqual(0.0, result->asNumber(), 0.0);
  } // testStringLengthFn6

  void testContainsFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("contains('hello', 'charlie drake')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(false, result->asBool());
  } // testContainsFn1

  void testContainsFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("contains('hello', 'hello mother')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(false, result->asBool());
  } // testContainsFn2

  void testContainsFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("contains('hello mother', 'hello')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(true, result->asBool());
  } // testContainsFn3

  void testContainsFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("contains('hello mother', 'hello mother')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(true, result->asBool());
  } // testContainsFn4

  void testContainsFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("contains('she heard a call hello mother somewhere in the distance', 'hello')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(true, result->asBool());
  } // testContainsFn5

  void testContainsFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("contains('my dogs says hello mother', 'hello mother')", document_);
    assertValuesEqual(BOOL, result->type());
    assertValuesEqual(true, result->asBool());
  } // testContainsFn6

  void testSubstringBeforeFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring-before('1999/04/01', '/')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("1999", result->asString());
  } // testSubstringBeforeFn1

  void testSubstringBeforeFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring-before('1999/04/01', 'mogadon')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testSubstringBeforeFn2

  void testSubstringBeforeFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring-before('1999/04/01', '/01')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("1999/04", result->asString());
  } // testStringBeforeFn3

  void testSubstringBeforeFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring-before('1999/04/01', '1')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testStringBeforeFn4

  void testSubstringAfterFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring-after('1999/04/01', '/')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("04/01", result->asString());
  } // testSubstringAfterFn1

  void testSubstringAfterFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring-after('1999/04/01', 'mogadon')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testSubstringAfterFn2

  void testSubstringAfterFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring-after('1999/04/01', '/01')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testStringAfterFn3

  void testSubstringAfterFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring-after('1999/04/01', '19')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("99/04/01", result->asString());
  } // testStringAfterFn4

  void testSubstringFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', 2, 3)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("234", result->asString());
  } // testSubstringFn1

  void testSubstringFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', 2)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("2345", result->asString());
  } // testSubstringFn2

  void testSubstringFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', 1.5, 2.6)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("234", result->asString());
  } // testSubstringFn3

  void testSubstringFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', 0, 3)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("12", result->asString());
  } // testSubstringFn4

  void testSubstringFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', 0 div 0, 3)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testSubstringFn5

  void testSubstringFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', 1, 0 div 0)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testSubstringFn6

  void testSubstringFn7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', -42, 1 div 0)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("12345", result->asString());
  } // testSubstringFn7

  void testSubstringFn8()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', -1 div 0, 1 div 0)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testSubstringFn8

  void testSubstringFn9()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', 1, 'NaN')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testSubstringFn9

  void testSubstringFn10()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', NaN)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testSubstringFn10

  void testSubstringFn11()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("substring('12345', NaN, NaN)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testSubstringFn11

  void testNormalizeSpaceFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("normalize-space('12345')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("12345", result->asString());
  } // testNormalizeSpaceFn1

  void testNormalizeSpaceFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("normalize-space('    12345')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("12345", result->asString());
  } // testNormalizeSpaceFn2

  void testNormalizeSpaceFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("normalize-space('12345 ')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("12345", result->asString());
  } // testNormalizeSpaceFn3

  void testNormalizeSpaceFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("normalize-space('    12345    ')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("12345", result->asString());
  } // testNormalizeSpaceFn4

  void testNormalizeSpaceFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("normalize-space('   12   3   45   ')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("12 3 45", result->asString());
  } // testNormalizeSpaceFn5

  void testNormalizeSpaceFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("normalize-space('1     2    3   4  5')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("1 2 3 4 5", result->asString());
  } // testNormalizeSpaceFn6

  void testTranslateFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("translate('bar','abc','ABC')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("BAr", result->asString());
  } // testTranslateFn1

  void testTranslateFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("translate('--aaa--','abc-','ABC')", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("AAA", result->asString());
  } // testTranslateFn2

  void testLocalNameFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(/root)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("root", result->asString());
  } // testLocalNameFn1

  void testLocalNameFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(/root/child2/@one)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("one", result->asString());
  } // testLocalNameFn2

  void testLocalNameFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(//comment())", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testLocalNameFn3

  void testLocalNameFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(//processing-instruction())", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("target", result->asString());
  } // testLocalNameFn4

  void testLocalNameFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name()", root_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("root", result->asString());
  } // testLocalNameFn5

  void testLocalNameFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name()", attr_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("one", result->asString());
  } // testLocalNameFn6

  void testLocalNameFn7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(//comment())", comment_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testLocalNameFn7

  void testLocalNameFn8()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(//processing-instruction())", processingInstruction_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("target", result->asString());
  } // testLocalNameFn8

  void testLocalNameFn9()
  {
    root_.appendChild(document_.createElementNS("test-uri", "element4"));
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(/root/*[last()])", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("element4", result->asString());
  } // testLocalNameFn9

  void testLocalNameFn10()
  {
    root_.setAttributeNS("test-uri", "q:woot", "hello");
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(/root/@*)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("woot", result->asString());
  } // testLocalNameFn10

  void testLocalNameFn11()
  {
    root_.appendChild(document_.createElementNS("test-uri", "q:noob"));
    XPathValuePtr<std::string> result = parser.evaluate_expr("local-name(/root/*[last()])", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("noob", result->asString());
  } // testLocalNameFn11

  void testNamespaceURIFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(/root)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNamespaceURIFn1

  void testNamespaceURIFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(/root/child2/@one)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNamespaceURIFn2

  void testNamespaceURIFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(//comment())", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNamespaceURIFn3

  void testNamespaceURIFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(//processing-instruction())", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNamespaceURIFn4

  void testNamespaceURIFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri()", root_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNamespaceURIFn5

  void testNamespaceURIFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri()", attr_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNamespaceURIFn6

  void testNamespaceURIFn7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(//comment())", comment_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNamespaceURIFn7

  void testNamespaceURIFn8()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(//processing-instruction())", processingInstruction_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNamespaceURIFn8

  void testNamespaceURIFn9()
  {
    root_.appendChild(document_.createElementNS("test-uri", "element4"));
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(/root/*[last()])", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("test-uri", result->asString());
  } // testNamespaceURIFn9

  void testNamespaceURIFn10()
  {
    root_.setAttributeNS("test-uri", "q:woot", "hello");
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(/root/@*)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("test-uri", result->asString());
  } // testNamespaceURIFn10

  void testNamespaceURIFn11()
  {
    root_.appendChild(document_.createElementNS("test-uri", "q:noob"));
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace-uri(/root/*[last()])", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("test-uri", result->asString());
  } // testNamespaceURIFn1
  
  void testNameFn1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(/root)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("root", result->asString());
  } // testNameFn1

  void testNameFn2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(/root/child2/@one)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("one", result->asString());
  } // testNameFn2

  void testNameFn3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(//comment())", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNameFn3

  void testNameFn4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(//processing-instruction())", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("target", result->asString());
  } // testNameFn4

  void testNameFn5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("name()", root_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("root", result->asString());
  } // testNameFn5

  void testNameFn6()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("name()", attr_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("one", result->asString());
  } // testNameFn6

  void testNameFn7()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(//comment())", comment_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("", result->asString());
  } // testNameFn7

  void testNameFn8()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(//processing-instruction())", processingInstruction_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("target", result->asString());
  } // testNameFn8

  void testNameFn9()
  {
    root_.appendChild(document_.createElementNS("test-uri", "element4"));
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(/root/*[last()])", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("element4", result->asString());
  } // testNameFn9

  void testNameFn10()
  {
    root_.setAttributeNS("test-uri", "q:woot", "hello");
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(/root/@*)", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("q:woot", result->asString());
  } // testNameFn10

  void testNameFn11()
  {
    root_.appendChild(document_.createElementNS("test-uri", "q:noob"));
    XPathValuePtr<std::string> result = parser.evaluate_expr("name(/root/*[last()])", document_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("q:noob", result->asString());
  } // testNameFn11

  void testDocumentOrder1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(/document/*)", chapters_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("one", result->asString());
  } // testDocumentOrder1

  void testDocumentOrder2()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(/document/*[last()])", chapters_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("five", result->asString());
  } // testDocumentOrder2

  void testDocumentOrder3()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(/document/chapter[5]/preceding-sibling::*[1])", chapters_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("four", result->asString());
  } // testDocumentOrder3

  void testDocumentOrder4()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(/document/chapter[5]/preceding-sibling::*[last()])", chapters_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("one", result->asString());
  } // testDocumentOrder4

  void testDocumentOrder5()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("string(/document/chapter[5]/preceding-sibling::*)", chapters_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("one", result->asString());
  } // testDocumentOrder5

  void testLessThan1()
  {
    assertValuesEqual(false, parser.evaluate_expr("true() < true()", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("true() < false()", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("false() < false()", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("false() < true()", chapters_)->asBool());
  } // testLessThan1

  void testLessThan2()
  {
    assertValuesEqual(false, parser.evaluate_expr("1 < 1", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("3.0 < 2.0", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("2.0 < 3.0", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("-1 < 1", chapters_)->asBool());
  } // testLessThan2

  void testLessThan3()
  {
    assertValuesEqual(false, parser.evaluate_expr("'1' < '1'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("'3.0' < '2.0'", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("'2.0' < '3.0'", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("'-1' < '1'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("-1 < 'ooop'", chapters_)->asBool());
  } // testLessThan3

  void testLessThan4()
  {
    assertValuesEqual(false, parser.evaluate_expr("/doc/number < 0", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number[2] < 0", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number < 2", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number < 12", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("0 < /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("0 < /doc/number[2]", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("1 < /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("7 < /doc/number", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("12 < /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[position()<5] < /doc/number[position()>5]", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[position()<=5] < /doc/number[position()>4]", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number[position()>5] < /doc/number[position()<5]", numbers_)->asBool());
  } // testLessThan4

  void testLessThanEquals1()
  {
    assertValuesEqual(true, parser.evaluate_expr("true() <= true()", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("true() <= false()", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("false() <= false()", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("false() <= true()", chapters_)->asBool());
  } // testLessThanEquals1

  void testLessThanEquals2()
  {
    assertValuesEqual(true, parser.evaluate_expr("1 <= 1", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("3.0 <= 2.0", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("2.0 <= 3.0", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("-1 <= 1", chapters_)->asBool());
  } // testLessThanEquals2

  void testLessThanEquals3()
  {
    assertValuesEqual(true, parser.evaluate_expr("'1' <= '1'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("'3.0' <= '2.0'", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("'2.0' <= '3.0'", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("'-1' <= '1'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("-1 <= 'ooop'", chapters_)->asBool());
  } // testLessThanEquals3

  void testLessThanEquals4()
  {
    assertValuesEqual(false, parser.evaluate_expr("/doc/number <= 0", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number[2] <= 0", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number <= 2", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number <= 12", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("0 <= /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("0 <= /doc/number[2]", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("1 <= /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("7 <= /doc/number", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("12 <= /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[position()<5] <= /doc/number[position()>5]", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[position()<=5] <= /doc/number[position()>4]", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number[position()>5] <= /doc/number[position()<5]", numbers_)->asBool());
  } // testLessThanEquals4

  void testGreaterThan1()
  {
    assertValuesEqual(false, parser.evaluate_expr("true() > true()", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("true() > false()", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("false() > false()", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("false() > true()", chapters_)->asBool());
  } // testGreaterThan1

  void testGreaterThan2()
  {
    assertValuesEqual(false, parser.evaluate_expr("1 > 1", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("3.0 > 2.0", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("2.0 > 3.0", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("-1 > 1", chapters_)->asBool());
  } // testGreaterThan2

  void testGreaterThan3()
  {
    assertValuesEqual(false, parser.evaluate_expr("'1' > '1'", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("'3.0' > '2.0'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("'2.0' > '3.0'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("'-1' > '1'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("-1 > 'ooop'", chapters_)->asBool());
  } // testGreaterThan3

  void testGreaterThan4()
  {
    assertValuesEqual(false, parser.evaluate_expr("3 > 2 > 1", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("(3>2)>1", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("3 > (2 > 1)", chapters_)->asBool());
  } // testGreaterThan4

  void testGreaterThan5()
  {
    assertValuesEqual(true, parser.evaluate_expr("/doc/number > 0", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[2] > 0", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number > 1", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number > 12", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("0 > /doc/number", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("0 > /doc/number[2]", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("1 > /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("7 > /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("12 > /doc/number", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number[position()<5] > /doc/number[position()>5]", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number[position()<=5] > /doc/number[position()>4]", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[position()>5] > /doc/number[position()<5]", numbers_)->asBool());
  } // testGreaterThan4

  void testGreaterThanEquals1()
  {
    assertValuesEqual(true, parser.evaluate_expr("true() >= true()", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("true() >= false()", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("false() >= false()", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("false() >= true()", chapters_)->asBool());
  } // testGreaterThanEquals1

  void testGreaterThanEquals2()
  {
    assertValuesEqual(true, parser.evaluate_expr("1 >= 1", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("3.0 >= 2.0", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("2.0 >= 3.0", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("-1 >= 1", chapters_)->asBool());
  } // testGreaterThanEquals2

  void testGreaterThanEquals3()
  {
    assertValuesEqual(true, parser.evaluate_expr("'1' >= '1'", chapters_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("'3.0' >= '2.0'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("'2.0' >= '3.0'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("'-1' >= '1'", chapters_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("-1 >= 'ooop'", chapters_)->asBool());
  } // testGreaterThanEquals3

  void testGreaterThanEquals4()
  {
    assertValuesEqual(true, parser.evaluate_expr("/doc/number >= 0", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[2] >= 0", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number >= 1", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number >= 12", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("0 >= /doc/number", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("0 >= /doc/number[2]", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("1 >= /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("7 >= /doc/number", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("12 >= /doc/number", numbers_)->asBool());
    assertValuesEqual(false, parser.evaluate_expr("/doc/number[position()<5] >= /doc/number[position()>5]", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[position()<=5] >= /doc/number[position()>4]", numbers_)->asBool());
    assertValuesEqual(true, parser.evaluate_expr("/doc/number[position()>5] >= /doc/number[position()<5]", numbers_)->asBool());
  } // testGreaterThanEquals4

  void testNodeSetVars1()
  {
    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable("fruit", ns);

    parser.setVariableResolver(svr);
    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element1_ == result->asNodeSet()[0]);
    assertTrue(element2_ == result->asNodeSet()[1]);
    assertTrue(element3_ == result->asNodeSet()[2]);
  } // testNodeSetVars1

  void testNodeSetVars2()
  {
    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable("fruit", ns);

    parser.setVariableResolver(svr);
    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit/spinkle", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(spinkle_ == result->asNodeSet()[0]);
  } // testNodeSetVars2

  void testNodeSetVars3()
  {
    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable("fruit", ns);

    parser.setVariableResolver(svr);
    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit[2]/*", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(spinkle_ == result->asNodeSet()[0]);
  } // testNodeSetVars3

  void testNodeSetVars4()
  {
    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable("fruit", ns);

    parser.setVariableResolver(svr);
    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit[true()][2]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNodeSetVars4

  void testNodeSetVars5()
  {
    NodeSetVariableResolver svr;
    NodeSet<std::string> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable("fruit", ns);

    parser.setVariableResolver(svr);
    XPathValuePtr<std::string> result = parser.evaluate_expr("$fruit[@two]", document_);
    assertValuesEqual(NODE_SET, result->type());
    assertTrue(element2_ == result->asNodeSet()[0]);
  } // testNodeSetVars5

  void namespaceAxisTest1()
  {
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace::*", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(0, result->asNodeSet().size());
  } // namespaceAxisTest1()

  void namespaceAxisTest2()
  {
    root_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:poop", "urn:test");
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace::*", root_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(1, result->asNodeSet().size());
    assertValuesEqual("poop", result->asNodeSet()[0].getLocalName());
    assertValuesEqual("urn:test", result->asNodeSet()[0].getNodeValue());
  } // namespaceAxisTest2

  void namespaceAxisTest3()
  {
    root_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:poop", "urn:test");
    element2_.setAttributeNS("http://www.w3.org/2000/xmlns/", "xmlns:test", "urn:another-test");
    XPathValuePtr<std::string> result = parser.evaluate_expr("namespace::*", element2_);
    assertValuesEqual(NODE_SET, result->type());
    assertValuesEqual(2, result->asNodeSet().size());
  } // namespaceAxisTest3

  void testFunctionResolver1()
  {
    try {
      parser.compile_expr("test-function()");
      assertTrue(false);
    }
    catch(...) { }
  } // testFunctionResolver1

  void testFunctionResolver2()
  {
    TestFunctionResolver tfr;
    parser.setFunctionResolver(tfr);

    XPathValuePtr<std::string> result = parser.evaluate_expr("test-function()", root_);
    assertValuesEqual(STRING, result->type());
    assertValuesEqual("test-root", result->asString());
  } // testFunctionResolver2

  void testSort1()
  {
    NodeSet<std::string> ns;

    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);

    ns.to_document_order();

    assertTrue(element1_ == ns[0]);
    assertTrue(element2_ == ns[1]);
    assertTrue(element3_ == ns[2]);
  } // testSort1

  void testSort2()
  {
    NodeSet<std::string> ns;

    ns.push_back(element3_);
    ns.push_back(element2_);
    ns.push_back(element1_);

    ns.to_document_order();

    assertTrue(element1_ == ns[0]);
    assertTrue(element2_ == ns[1]);
    assertTrue(element3_ == ns[2]);
  } // testSort2
}; // class ExecuteTest

TestSuite* ExecuteTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test1", &ExecuteTest::test1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test2", &ExecuteTest::test2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test3", &ExecuteTest::test3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test4", &ExecuteTest::test4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test5", &ExecuteTest::test5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test6", &ExecuteTest::test6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test7", &ExecuteTest::test7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test8", &ExecuteTest::test8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test9", &ExecuteTest::test9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test10", &ExecuteTest::test10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test11", &ExecuteTest::test11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test12", &ExecuteTest::test12));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test13", &ExecuteTest::test13));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test14", &ExecuteTest::test14));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test15", &ExecuteTest::test15));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test16", &ExecuteTest::test16));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test17", &ExecuteTest::test17));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test18", &ExecuteTest::test18));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test19", &ExecuteTest::test19));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test20", &ExecuteTest::test20));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test21", &ExecuteTest::test21));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test22", &ExecuteTest::test22));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test23", &ExecuteTest::test23));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test24", &ExecuteTest::test24));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test25", &ExecuteTest::test25));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test26", &ExecuteTest::test26));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test27", &ExecuteTest::test27));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test28", &ExecuteTest::test28));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test29", &ExecuteTest::test29));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test30", &ExecuteTest::test30));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test31", &ExecuteTest::test31));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test32", &ExecuteTest::test32));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test33", &ExecuteTest::test33));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test34", &ExecuteTest::test34));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test35", &ExecuteTest::test35));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test36", &ExecuteTest::test36));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test37", &ExecuteTest::test37));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test38", &ExecuteTest::test38));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test39", &ExecuteTest::test39));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test40", &ExecuteTest::test40));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("test41", &ExecuteTest::test41));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion1", &ExecuteTest::testUnion1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion2", &ExecuteTest::testUnion2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion3", &ExecuteTest::testUnion3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion4", &ExecuteTest::testUnion4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion5", &ExecuteTest::testUnion5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion6", &ExecuteTest::testUnion6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion7", &ExecuteTest::testUnion7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion8", &ExecuteTest::testUnion8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion9", &ExecuteTest::testUnion9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion10", &ExecuteTest::testUnion10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion11", &ExecuteTest::testUnion11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion12", &ExecuteTest::testUnion12));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion13", &ExecuteTest::testUnion13));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testUnion14", &ExecuteTest::testUnion14));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testPlus1", &ExecuteTest::testPlus1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testPlus2", &ExecuteTest::testPlus2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality1", &ExecuteTest::testNodeSetEquality1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality2", &ExecuteTest::testNodeSetEquality2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality3", &ExecuteTest::testNodeSetEquality3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality4", &ExecuteTest::testNodeSetEquality4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality5", &ExecuteTest::testNodeSetEquality5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality6", &ExecuteTest::testNodeSetEquality6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality7", &ExecuteTest::testNodeSetEquality7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality8", &ExecuteTest::testNodeSetEquality8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetEquality9", &ExecuteTest::testNodeSetEquality9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCountFn1", &ExecuteTest::testCountFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCountFn2", &ExecuteTest::testCountFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCountFn3", &ExecuteTest::testCountFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNotFn1", &ExecuteTest::testNotFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNotFn2", &ExecuteTest::testNotFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testBooleanFn1", &ExecuteTest::testBooleanFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testBooleanFn2", &ExecuteTest::testBooleanFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNumberFn1", &ExecuteTest::testNumberFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNumberFn2", &ExecuteTest::testNumberFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNumberFn3", &ExecuteTest::testNumberFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNumberFn4", &ExecuteTest::testNumberFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNumberFn5", &ExecuteTest::testNumberFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNumberFn6", &ExecuteTest::testNumberFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNumberFn7", &ExecuteTest::testNumberFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn1", &ExecuteTest::testFloorFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn2", &ExecuteTest::testFloorFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn3", &ExecuteTest::testFloorFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn4", &ExecuteTest::testFloorFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn5", &ExecuteTest::testFloorFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn6", &ExecuteTest::testFloorFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn7", &ExecuteTest::testFloorFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn8", &ExecuteTest::testFloorFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFloorFn9", &ExecuteTest::testFloorFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn1", &ExecuteTest::testCeilingFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn2", &ExecuteTest::testCeilingFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn3", &ExecuteTest::testCeilingFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn4", &ExecuteTest::testCeilingFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn5", &ExecuteTest::testCeilingFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn6", &ExecuteTest::testCeilingFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn7", &ExecuteTest::testCeilingFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn8", &ExecuteTest::testCeilingFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testCeilingFn9", &ExecuteTest::testCeilingFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringFn1", &ExecuteTest::testStringFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringFn2", &ExecuteTest::testStringFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringFn3", &ExecuteTest::testStringFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringFn4", &ExecuteTest::testStringFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringFn5", &ExecuteTest::testStringFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn1", &ExecuteTest::testRoundFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn2", &ExecuteTest::testRoundFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn3", &ExecuteTest::testRoundFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn4", &ExecuteTest::testRoundFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn5", &ExecuteTest::testRoundFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn6", &ExecuteTest::testRoundFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn7", &ExecuteTest::testRoundFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn8", &ExecuteTest::testRoundFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn9", &ExecuteTest::testRoundFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testRoundFn10", &ExecuteTest::testRoundFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSumFn1", &ExecuteTest::testSumFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSumFn2", &ExecuteTest::testSumFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSumFn3", &ExecuteTest::testSumFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSumFn4", &ExecuteTest::testSumFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testConcatFn1", &ExecuteTest::testConcatFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testConcatFn2", &ExecuteTest::testConcatFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testConcatFn3", &ExecuteTest::testConcatFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testConcatFn4", &ExecuteTest::testConcatFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testConcatFn5", &ExecuteTest::testConcatFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStartsWithFn1", &ExecuteTest::testStartsWithFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStartsWithFn2", &ExecuteTest::testStartsWithFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStartsWithFn3", &ExecuteTest::testStartsWithFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStartsWithFn4", &ExecuteTest::testStartsWithFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringLengthFn1", &ExecuteTest::testStringLengthFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringLengthFn2", &ExecuteTest::testStringLengthFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringLengthFn3", &ExecuteTest::testStringLengthFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringLengthFn4", &ExecuteTest::testStringLengthFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringLengthFn5", &ExecuteTest::testStringLengthFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testStringLengthFn6", &ExecuteTest::testStringLengthFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testContainsFn1", &ExecuteTest::testContainsFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testContainsFn2", &ExecuteTest::testContainsFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testContainsFn3", &ExecuteTest::testContainsFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testContainsFn4", &ExecuteTest::testContainsFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testContainsFn5", &ExecuteTest::testContainsFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testContainsFn6", &ExecuteTest::testContainsFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringBeforeFn1", &ExecuteTest::testSubstringBeforeFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringBeforeFn2", &ExecuteTest::testSubstringBeforeFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringBeforeFn3", &ExecuteTest::testSubstringBeforeFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringBeforeFn4", &ExecuteTest::testSubstringBeforeFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringAfterFn1", &ExecuteTest::testSubstringAfterFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringAfterFn2", &ExecuteTest::testSubstringAfterFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringAfterFn3", &ExecuteTest::testSubstringAfterFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringAfterFn4", &ExecuteTest::testSubstringAfterFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn1", &ExecuteTest::testSubstringFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn2", &ExecuteTest::testSubstringFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn3", &ExecuteTest::testSubstringFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn4", &ExecuteTest::testSubstringFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn5", &ExecuteTest::testSubstringFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn6", &ExecuteTest::testSubstringFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn7", &ExecuteTest::testSubstringFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn8", &ExecuteTest::testSubstringFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn9", &ExecuteTest::testSubstringFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn10", &ExecuteTest::testSubstringFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSubstringFn11", &ExecuteTest::testSubstringFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNormalizeSpaceFn1", &ExecuteTest::testNormalizeSpaceFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNormalizeSpaceFn2", &ExecuteTest::testNormalizeSpaceFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNormalizeSpaceFn3", &ExecuteTest::testNormalizeSpaceFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNormalizeSpaceFn4", &ExecuteTest::testNormalizeSpaceFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNormalizeSpaceFn5", &ExecuteTest::testNormalizeSpaceFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNormalizeSpaceFn6", &ExecuteTest::testNormalizeSpaceFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testTranslateFn1", &ExecuteTest::testTranslateFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testTranslateFn2", &ExecuteTest::testTranslateFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn1", &ExecuteTest::testLocalNameFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn2", &ExecuteTest::testLocalNameFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn3", &ExecuteTest::testLocalNameFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn4", &ExecuteTest::testLocalNameFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn5", &ExecuteTest::testLocalNameFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn6", &ExecuteTest::testLocalNameFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn7", &ExecuteTest::testLocalNameFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn8", &ExecuteTest::testLocalNameFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn9", &ExecuteTest::testLocalNameFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn10", &ExecuteTest::testLocalNameFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLocalNameFn11", &ExecuteTest::testLocalNameFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn1", &ExecuteTest::testNamespaceURIFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn2", &ExecuteTest::testNamespaceURIFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn3", &ExecuteTest::testNamespaceURIFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn4", &ExecuteTest::testNamespaceURIFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn5", &ExecuteTest::testNamespaceURIFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn6", &ExecuteTest::testNamespaceURIFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn7", &ExecuteTest::testNamespaceURIFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn8", &ExecuteTest::testNamespaceURIFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn9", &ExecuteTest::testNamespaceURIFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn10", &ExecuteTest::testNamespaceURIFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNamespaceURIFn11", &ExecuteTest::testNamespaceURIFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn1", &ExecuteTest::testNameFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn2", &ExecuteTest::testNameFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn3", &ExecuteTest::testNameFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn4", &ExecuteTest::testNameFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn5", &ExecuteTest::testNameFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn6", &ExecuteTest::testNameFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn7", &ExecuteTest::testNameFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn8", &ExecuteTest::testNameFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn9", &ExecuteTest::testNameFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn10", &ExecuteTest::testNameFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNameFn11", &ExecuteTest::testNameFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testDocumentOrder1", &ExecuteTest::testDocumentOrder1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testDocumentOrder2", &ExecuteTest::testDocumentOrder2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testDocumentOrder3", &ExecuteTest::testDocumentOrder3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testDocumentOrder4", &ExecuteTest::testDocumentOrder4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testDocumentOrder5", &ExecuteTest::testDocumentOrder5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLessThan1", &ExecuteTest::testLessThan1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLessThan2", &ExecuteTest::testLessThan2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLessThan3", &ExecuteTest::testLessThan3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLessThan4", &ExecuteTest::testLessThan4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLessThanEquals1", &ExecuteTest::testLessThanEquals1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLessThanEquals2", &ExecuteTest::testLessThanEquals2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLessThanEquals3", &ExecuteTest::testLessThanEquals3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testLessThanEquals4", &ExecuteTest::testLessThanEquals4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThan1", &ExecuteTest::testGreaterThan1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThan2", &ExecuteTest::testGreaterThan2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThan3", &ExecuteTest::testGreaterThan3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThan4", &ExecuteTest::testGreaterThan4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThan5", &ExecuteTest::testGreaterThan5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThanEquals1", &ExecuteTest::testGreaterThanEquals1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThanEquals2", &ExecuteTest::testGreaterThanEquals2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThanEquals3", &ExecuteTest::testGreaterThanEquals3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testGreaterThanEquals4", &ExecuteTest::testGreaterThanEquals4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetVars1", &ExecuteTest::testNodeSetVars1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetVars2", &ExecuteTest::testNodeSetVars2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetVars3", &ExecuteTest::testNodeSetVars3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetVars4", &ExecuteTest::testNodeSetVars4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testNodeSetVars5", &ExecuteTest::testNodeSetVars5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("namespaceAxisTest1", &ExecuteTest::namespaceAxisTest1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("namespaceAxisTest2", &ExecuteTest::namespaceAxisTest2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("namespaceAxisTest3", &ExecuteTest::namespaceAxisTest3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFunctionResolver1", &ExecuteTest::testFunctionResolver1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testFunctionResolver2", &ExecuteTest::testFunctionResolver2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSort1", &ExecuteTest::testSort1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest>("testSort2", &ExecuteTest::testSort2));
 
  return suiteOfTests;
} // ExecuteTest_suite
