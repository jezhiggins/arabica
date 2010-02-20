#ifndef XPATHIC_EXECUTE_TEST_HPP
#define XPATHIC_EXECUTE_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class StringVariableResolver : public Arabica::XPath::VariableResolver<string_type, string_adaptor>
{
public:
  virtual Arabica::XPath::XPathValue<string_type, string_adaptor> resolveVariable(const string_type& /* namespace_uri */,
                                                                     const string_type& name) const
  {
    using namespace Arabica::XPath;
    typename VarMap::const_iterator n = map_.find(name);
    if(n == map_.end())
      throw UnboundVariableException(string_adaptor::asStdString(name));
    return XPathValue<string_type, string_adaptor>(new StringValue<string_type, string_adaptor>((*n).second));
  } // resolveVariable

  void setVariable(const string_type& name, const string_type& value)
  {
    map_[name] = value;
  } // setVariable

private:
  typedef std::map<string_type, string_type> VarMap;
  VarMap map_;
}; // StringVariableResolver

template<class string_type, class string_adaptor>
class NodeSetVariableResolver : public Arabica::XPath::VariableResolver<string_type, string_adaptor>
{
  //typedef string_adaptorstring_adaptor;
public:
  virtual Arabica::XPath::XPathValue<string_type, string_adaptor> resolveVariable(const string_type& /* namepace_uri */,
                                                                     const string_type& name) const
  {
    using namespace Arabica::XPath;
    typename VarMap::const_iterator n = map_.find(name);
    if(n == map_.end())
      throw UnboundVariableException(string_adaptor::asStdString(name));
    return XPathValue<string_type, string_adaptor>(new NodeSetValue<string_type, string_adaptor>((*n).second));
  } // resolveVariable

  void setVariable(const string_type& name, const Arabica::XPath::NodeSet<string_type, string_adaptor>& value)
  {
    map_[name] = value;
  } // setVariable

private:
  typedef std::map<string_type, Arabica::XPath::NodeSet<string_type, string_adaptor> > VarMap;
  VarMap map_;
}; // class NodeSetVariableResolver

template<class string_type, class string_adaptor>
class TestFunction : public Arabica::XPath::XPathFunction<string_type, string_adaptor>
{
  //typedef string_adaptorstring_adaptor;
public:
  TestFunction(const std::vector<Arabica::XPath::XPathExpression<string_type, string_adaptor> >& args) :
      Arabica::XPath::XPathFunction<string_type, string_adaptor>(0, 0, args) { }

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::STRING; }

  virtual Arabica::XPath::XPathValue_impl<string_type, string_adaptor>* evaluate(const Arabica::DOM::Node<string_type, string_adaptor>& context, 
										 const Arabica::XPath::ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    string_type name = string_adaptor::construct_from_utf8("test-");
    string_adaptor::append(name, context.getLocalName());
    return new Arabica::XPath::StringValue<string_type, string_adaptor>(name);
  } // evaluate
}; // TestFunction

template<class string_type, class string_adaptor>
class TestFunctionResolver : public Arabica::XPath::NullFunctionResolver<string_type, string_adaptor>
{
  //typedef string_adaptorstring_adaptor;
public:
  virtual Arabica::XPath::XPathFunction<string_type, string_adaptor>* resolveFunction(
                                         const string_type& /* namespace_uri */,
                                         const string_type& name,
                                         const std::vector<Arabica::XPath::XPathExpression<string_type, string_adaptor> >& argExprs) const
  {
    if(name == string_adaptor::construct_from_utf8("test-function"))
      return new TestFunction<string_type, string_adaptor>(argExprs);
    return 0;
  } // resolveFunction
}; // class TestFunctionResolver

template<class string_type, class string_adaptor>
class ExecuteTest : public TestCase
{
  Arabica::XPath::XPath<string_type, string_adaptor> parser;
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory_;
  Arabica::DOM::Document<string_type, string_adaptor> document_;

  Arabica::DOM::Element<string_type, string_adaptor> root_;

  Arabica::DOM::Element<string_type, string_adaptor> element1_;
  Arabica::DOM::Element<string_type, string_adaptor> element2_;
  Arabica::DOM::Element<string_type, string_adaptor> element3_;
  Arabica::DOM::Element<string_type, string_adaptor> spinkle_;

  Arabica::DOM::Attr<string_type, string_adaptor> attr_;

  Arabica::DOM::Text<string_type, string_adaptor> text_;

  Arabica::DOM::Comment<string_type, string_adaptor> comment_;

  Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> processingInstruction_;

  Arabica::DOM::Document<string_type, string_adaptor> chapters_;

  Arabica::DOM::Document<string_type, string_adaptor> numbers_;

  typedef string_adaptor SA;
public:
  ExecuteTest(std::string name) : TestCase(name)
  {
  } // ExecuteTest

  void setUp()
  {
    factory_ = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    document_ = factory_.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8("root"), 0);
    root_ = document_.getDocumentElement();

    element1_ = document_.createElement(SA::construct_from_utf8("child1"));
    element2_ = document_.createElement(SA::construct_from_utf8("child2"));
    element3_ = document_.createElement(SA::construct_from_utf8("child3"));

    element1_.setAttribute(SA::construct_from_utf8("one"), SA::construct_from_utf8("1"));

    element2_.setAttribute(SA::construct_from_utf8("one"), SA::construct_from_utf8("1"));
    element2_.setAttribute(SA::construct_from_utf8("two"), SA::construct_from_utf8("1"));
    element2_.setAttribute(SA::construct_from_utf8("three"), SA::construct_from_utf8("1"));
    element2_.setAttribute(SA::construct_from_utf8("four"), SA::construct_from_utf8("1"));

    text_ = document_.createTextNode(SA::construct_from_utf8("data"));
    comment_ = document_.createComment(SA::construct_from_utf8("comment"));
    processingInstruction_ = document_.createProcessingInstruction(SA::construct_from_utf8("target"), SA::construct_from_utf8("data"));
    element2_.appendChild(text_);
    spinkle_ = document_.createElement(SA::construct_from_utf8("spinkle"));
    element2_.appendChild(spinkle_);
    element2_.appendChild(comment_);
    element2_.appendChild(processingInstruction_);

    attr_ = element1_.getAttributeNode(SA::construct_from_utf8("one"));

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);

    chapters_ = factory_.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8("document"), 0);
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("one")));
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("two")));
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("three")));
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("four")));
    chapters_.getFirstChild().appendChild(chapters_.createElement(SA::construct_from_utf8("chapter"))).appendChild(chapters_.createTextNode(SA::construct_from_utf8("five")));

    numbers_ = factory_.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8("doc"), 0);
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("1")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("2")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("3")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("4")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("5")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("6")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("7")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("8")));
    numbers_.getFirstChild().appendChild(numbers_.createElement(SA::construct_from_utf8("number"))).appendChild(numbers_.createTextNode(SA::construct_from_utf8("9")));
  } // setUp

  void test1()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath;
    xpath = parser.compile(SA::construct_from_utf8("root"));
    assertValuesEqual(NODE_SET, xpath.type());
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    Arabica::DOM::Node<string_type, string_adaptor> n = result.asNodeSet()[0];
    assertTrue(root_ == n);
  } // test1

  void test2()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/child2"));
    assertValuesEqual(NODE_SET, xpath.type());
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    Arabica::DOM::Node<string_type, string_adaptor> n = result.asNodeSet()[0];
    assertTrue(element2_ == n);
  } // test2

  void test3()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*"));
    assertValuesEqual(NODE_SET, xpath.type());
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(element3_ == result.asNodeSet()[2]);
  } // test4

  void test4()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*/text()"));
    assertValuesEqual(NODE_SET, xpath.type());
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(text_ == result.asNodeSet()[0]);
    assertTrue(text_.getNodeValue() == result.asString());
  } // test4

  void test5() 
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*/text()"));
    assertTrue(text_.getNodeValue() == xpath.evaluateAsString(document_));
  } // test5

  void test6()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("*"));
    assertValuesEqual(NODE_SET, xpath.type());

    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(root_ == result.asNodeSet()[0]);

    result = xpath.evaluate(root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(element3_ == result.asNodeSet()[2]);

    result = xpath.evaluate(element1_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());

    result = xpath.evaluate(element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());

    result = xpath.evaluate(element3_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());
  } // test6

  void test7()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("/root"));

    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(root_ == result.asNodeSet()[0]);

    result = xpath.evaluate(text_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(root_ == result.asNodeSet()[0]);
  } // test7

  void test8()
  {
    using namespace Arabica::XPath;
    StandardNamespaceContext<string_type, string_adaptor> nsContext;
    nsContext.addNamespaceDeclaration(SA::construct_from_utf8("urn:something:or:other"), SA::construct_from_utf8("ns"));
    parser.setNamespaceContext(nsContext);
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("/ns:root"));
    assertValuesEqual(NODE_SET, xpath.type());
    parser.resetNamespaceContext();

    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());

    result = xpath.evaluate(text_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());
  } // test8

  void test9()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("child2"));

    XPathValue<string_type, string_adaptor> result = xpath.evaluate(root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);

    xpath = parser.compile(SA::construct_from_utf8("./child2"));
    result = xpath.evaluate(root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // test9

  void test10()
  {
    assertTrue(root_ == parser.evaluate(SA::construct_from_utf8("."), root_).asNodeSet()[0]);
    assertTrue(document_ == parser.evaluate(SA::construct_from_utf8("."), document_).asNodeSet()[0]);
    assertTrue(element3_ == parser.evaluate(SA::construct_from_utf8("."), element3_).asNodeSet()[0]);
    assertTrue(comment_ == parser.evaluate(SA::construct_from_utf8("."), comment_).asNodeSet()[0]);
    assertTrue(processingInstruction_ == parser.evaluate(SA::construct_from_utf8("."), processingInstruction_).asNodeSet()[0]);
    assertTrue(text_ == parser.evaluate(SA::construct_from_utf8("."), text_).asNodeSet()[0]);
    assertTrue(attr_ == parser.evaluate(SA::construct_from_utf8("."), attr_).asNodeSet()[0]);
  } // test10

  void test11()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8(".."));

    XPathValue<string_type, string_adaptor> result = xpath.evaluate(element3_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(root_ == result.asNodeSet()[0]);
  } // test11

  void test12()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*[2]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    Arabica::DOM::Node<string_type, string_adaptor> n = result.asNodeSet()[0];
    assertTrue(element2_ == n);
  } // test12

  void test13()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[2]/comment()"), document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(comment_ == result.asNodeSet()[0]);
  } // test13

  void test14()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[2]/node()[3]"), document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(comment_ == result.asNodeSet()[0]);
  } // test14

  void test15()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("root/*[spinkle]"), document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // test15

  void test16()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("root/*[doesnotmatch]"), document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());
  } // test16

  void test17()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@two = '1']"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // test17

  void test18()
  {
    using namespace Arabica::XPath;
    StringVariableResolver<string_type, string_adaptor> svr;
    svr.setVariable(SA::construct_from_utf8("index"), SA::construct_from_utf8("1"));

    parser.setVariableResolver(svr);
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@two = $index]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);

    parser.resetVariableResolver();
  } // test18

  void test19()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*[position() = 2]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    Arabica::DOM::Node<string_type, string_adaptor> n = result.asNodeSet()[0];
    assertTrue(element2_ == n);
  } // test19

  void test20()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*[last()]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element3_ == result.asNodeSet()[0]);
  } // test20

  void test21()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*[position() != last()]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
  } // test21

  void test22()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*[position() = 2 or position() = 1]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
  } // test22

  void test23()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*[position() = 2 and @two = '1']"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // test23

  void test24()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*[last()][1]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element3_ == result.asNodeSet()[0]);
  } // test24

  void test25()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("root/*[last()][2]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());
  } // test25

  void test26()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("/root/child2/spinkle/ancestor::*"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(result.asNodeSet()[0] == element2_);
    assertTrue(result.asNodeSet()[1] == root_);
    assertTrue(result.asNodeSet().forward() == false);
  } // test26

  void test26a()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("/root/child2/spinkle/ancestor::node()[2]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(result.asNodeSet()[0] == root_);
    assertTrue(result.asNodeSet().forward() == false);
  } // test26a

  void test27()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("/root/child2/spinkle/ancestor-or-self::*"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(result.asNodeSet()[0] == spinkle_);
    assertTrue(result.asNodeSet()[1] == element2_);
    assertTrue(result.asNodeSet()[2] == root_);
    assertTrue(result.asNodeSet().forward() == false);
  } // test27

  void test27a()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("/root/child2/spinkle/ancestor-or-self::node()[2]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(result.asNodeSet()[0] == element2_);
    assertTrue(result.asNodeSet().forward() == false);
 } // test27a

  void test28()
  {
    using namespace Arabica::XPath;
    XPathExpression<string_type, string_adaptor> xpath = parser.compile(SA::construct_from_utf8("/root/child2/spinkle/ancestor-or-self::node()[3]"));
    XPathValue<string_type, string_adaptor> result = xpath.evaluate(document_);

    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(result.asNodeSet()[0] == root_);
  } // test28

  void test29()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/child::root/child::*[attribute::two = '1']"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // test29

  void test30()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(document_ == result.asNodeSet()[0]);
  } // test30

  void test31()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/"), element1_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(document_ == result.asNodeSet()[0]);
  } // test31

  void test32()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("//comment()"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(comment_ == result.asNodeSet()[0]);
  } // test32

  void test33()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("//comment()"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(comment_ == result.asNodeSet()[0]);
    assertTrue(result.asNodeSet().forward() == true);
  } // test33

  void test34()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("//*"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(5, result.asNodeSet().size());
    assertTrue(root_ == result.asNodeSet()[0]);
    assertTrue(element1_ == result.asNodeSet()[1]);
    assertTrue(element2_ == result.asNodeSet()[2]);
    assertTrue(spinkle_ == result.asNodeSet()[3]);
    assertTrue(element3_ == result.asNodeSet()[4]);
  } // test34

  void test35()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("//*"), element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(5, result.asNodeSet().size());
    assertTrue(root_ == result.asNodeSet()[0]);
    assertTrue(element1_ == result.asNodeSet()[1]);
    assertTrue(element2_ == result.asNodeSet()[2]);
    assertTrue(spinkle_ == result.asNodeSet()[3]);
    assertTrue(element3_ == result.asNodeSet()[4]);
  } // test35

  void test36()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("//*/*"), element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(4, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(spinkle_ == result.asNodeSet()[2]);
    assertTrue(element3_ == result.asNodeSet()[3]);
  } // test36

  void test37()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("//*/*/*"), element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(spinkle_ == result.asNodeSet()[0]);
  } // test37

  void test38()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("//*/*/*/*"), element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());
  } // test38

  void test39()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/*/*"), element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(element3_ == result.asNodeSet()[2]);
  } // test39

  void test40()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root//*"), element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(4, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(spinkle_ == result.asNodeSet()[2]);
    assertTrue(element3_ == result.asNodeSet()[3]);
  } // test40

  // see http://jira.codehaus.org/browse/JAXEN-94
  void test41()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("2+1-1+1"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(3.0, result.asNumber(), 0.0);
  } // test41

  void test42()
  {
    using namespace Arabica::XPath;
    Arabica::DOM::Element<string_type, string_adaptor> f1 = chapters_.createElement(SA::construct_from_utf8("footer"));
    Arabica::DOM::Element<string_type, string_adaptor> f2 = chapters_.createElement(SA::construct_from_utf8("footer"));
    XPathValue<string_type, string_adaptor> ch = parser.evaluate(SA::construct_from_utf8("/document/chapter"), chapters_);
    Arabica::DOM::Node<string_type, string_adaptor> n = ch.asNodeSet()[0];
    n.appendChild(f1);
    n = ch.asNodeSet()[1];
    n.appendChild(f2);

    XPathValue<string_type, string_adaptor> footers = parser.evaluate(SA::construct_from_utf8("//footer"), chapters_);
    assertValuesEqual(NODE_SET, footers.type());
    assertValuesEqual(2, footers.asNodeSet().size());
    assertTrue(f1 == footers.asNodeSet()[0]);
    assertTrue(f2 == footers.asNodeSet()[1]);

    footers = parser.evaluate(SA::construct_from_utf8("/document/chapter/footer[1]"), chapters_);
    assertValuesEqual(NODE_SET, footers.type());
    assertValuesEqual(2, footers.asNodeSet().size());
    assertTrue(f1 == footers.asNodeSet()[0]);
    assertTrue(f2 == footers.asNodeSet()[1]);

    footers = parser.evaluate(SA::construct_from_utf8("//footer[1]"), chapters_);
    assertValuesEqual(NODE_SET, footers.type());
    assertValuesEqual(2, footers.asNodeSet().size());
    assertTrue(f1 == footers.asNodeSet()[0]);
    assertTrue(f2 == footers.asNodeSet()[1]);

    footers = parser.evaluate(SA::construct_from_utf8("//footer[2]"), chapters_);
    assertValuesEqual(NODE_SET, footers.type());
    assertValuesEqual(0, footers.asNodeSet().size());

    footers = parser.evaluate_expr(SA::construct_from_utf8("(//footer)[1]"), chapters_);
    assertValuesEqual(NODE_SET, footers.type());
    assertValuesEqual(1, footers.asNodeSet().size());
    assertTrue(f1 == footers.asNodeSet()[0]);
    footers = parser.evaluate_expr(SA::construct_from_utf8("(//footer)[2]"), chapters_);
    assertValuesEqual(NODE_SET, footers.type());
    assertValuesEqual(1, footers.asNodeSet().size());
    assertTrue(f2 == footers.asNodeSet()[0]);
  } // test42

  void testUnion1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@one|data]"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
  } // testUnion1

  void testUnion2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[buttle|tuttle]"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());
    assertTrue(result.asNodeSet().forward() == true);
  } // testUnion2

  void testUnion3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[preceding-sibling::child2|@two]"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
    assertTrue(element3_ == result.asNodeSet()[1]);
  } // testUnion3

  void testUnion4()
  {
    using namespace Arabica::XPath;
    try {
      XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@two|4]"), root_);
    } // try
    catch(RuntimeException re) {
      // yay!
    } // catch
  } // testUnion4

  void testUnion5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[preceding-sibling::child2|@two|following-sibling::child2]"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(element3_ == result.asNodeSet()[2]);
  } // testUnion5

  void testUnion6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("/root/child2|/root/child1"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
  } // testUnion6

  void testUnion7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("/root/child1|/root/child2"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
  } // testUnion7

  void testUnion8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("/root/child2/@one|/root/child2|/root/child1"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(element2_.getAttributeNode(SA::construct_from_utf8("one")) == result.asNodeSet()[2]);
  } // testUnion8

  void testUnion9()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("/root/child1/@one|/root/child2/@one|/root/child2|/root/child1"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(4, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element1_.getAttributeNode(SA::construct_from_utf8("one")) == result.asNodeSet()[1]);
    assertTrue(element2_ == result.asNodeSet()[2]);
    assertTrue(element2_.getAttributeNode(SA::construct_from_utf8("one")) == result.asNodeSet()[3]);
  } // testUnion9

  void testUnion10()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("/root/child3|/root/child3/preceding-sibling::*"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(element3_ == result.asNodeSet()[2]);
  } // testUnion10

  void testUnion11()
  {
    using namespace Arabica::XPath;
    Arabica::DOM::DocumentFragment<string_type, string_adaptor> frag = document_.createDocumentFragment();
    frag.appendChild(document_.createElement(SA::construct_from_utf8("foo")));

    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(frag);
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);
    parser.setVariableResolver(svr);

    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit/foo|/root/child3"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(element3_ == result.asNodeSet()[0]);
  } // testUnion11

  void testUnion12()
  {
    using namespace Arabica::XPath;
    Arabica::DOM::DocumentFragment<string_type, string_adaptor> frag = document_.createDocumentFragment();
    Arabica::DOM::Node<string_type, string_adaptor> n1 = document_.createElement(SA::construct_from_utf8("foo"));
    Arabica::DOM::Node<string_type, string_adaptor> n2 = document_.createElement(SA::construct_from_utf8("bar"));

    frag.appendChild(n1);
    frag.appendChild(n2);

    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(frag);
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);
    parser.setVariableResolver(svr);

    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit/bar|$fruit/foo"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(n1 == result.asNodeSet()[0]);
    assertTrue(n2 == result.asNodeSet()[1]);
  } // testUnion12

  void testUnion13()
  {
    using namespace Arabica::XPath;
    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(document_.createElement(SA::construct_from_utf8("foo")));
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);
    parser.setVariableResolver(svr);

    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit|/root/child3"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(element3_ == result.asNodeSet()[0]);
  } // testUnion13

  void testUnion14()
  {
    using namespace Arabica::XPath;
    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(document_.createElement(SA::construct_from_utf8("foo")));
    ns.push_back(document_.createElement(SA::construct_from_utf8("bar")));
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);
    parser.setVariableResolver(svr);

    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit|/root/child3|$fruit"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(element3_ == result.asNodeSet()[0]);
  } // testUnion14

  void testPlus1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[1+1]"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testPlus1

  void testPlus2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[1+1+1]"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element3_ == result.asNodeSet()[0]);
  } // testPlus2

  void testNodeSetEquality1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@two = 1]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNodeSetEquality1

  void testNodeSetEquality2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@two = true()]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNodeSetEquality2

  void testNodeSetEquality3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@two != false()]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNodeSetEquality3

  void testNodeSetEquality4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@* = 1]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
  } // testNodeSetEquality4

  void testNodeSetEquality5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@* = '1']"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
  } // testNodeSetEquality5

  void testNodeSetEquality6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@* = @one]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
  } // testNodeSetEquality6

  void testNodeSetEquality7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@* = @two]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNodeSetEquality7

  void testNodeSetEquality8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/child2[-(@two) = -1]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNodeSetEquality8

  void testNodeSetEquality9()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/child2[-(@two) - 1 = -2]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNodeSetEquality9

  void testCountFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[count(@*) = 4]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testCountFn1

  void testCountFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[count(@*) = 1]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
  } // testCountFn2

  void testCountFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[count(@*) = 999]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(0, result.asNodeSet().size());
  } // testCountFn3

  void testNotFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@two != not(true())]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNotFn1

  void testNotFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[@two = not(false())]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNotFn2

  void testBooleanFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[boolean(@three)]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testBooleanFn1

  void testBooleanFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate(SA::construct_from_utf8("/root/*[boolean(1)]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(element3_ == result.asNodeSet()[2]);
  } // testBooleanFn2

  void testNumberFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number(true())"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testNumberFn1

  void testNumberFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number(false())"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(0.0, result.asNumber(), 0.0);
  } // testNumberFn2

  void testNumberFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number(1.5)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.5, result.asNumber(), 0.0);
  } // testNumberFn3

  void testNumberFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number('1.5')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.5, result.asNumber(), 0.0);
  } // testNumberFn4

  void testNumberFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number(\"1.5\")"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.5, result.asNumber(), 0.0);
  } // testNumberFn5

  void testNumberFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number(/root/child2/@one)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testNumberFn6

  void testNumberFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number('trousers')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertTrue(isNaN(result.asNumber()));
  } // testNumberFn7

  void testNumberFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number('-1.5')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.5, result.asNumber(), 0.0);
  } // testNumberFn8

  void testNumberFn9()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number('+1.5')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertTrue(isNaN(result.asNumber()));
  } // testNumberFn9

  void testNumberFn10()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number('-1.5                       ')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.5, result.asNumber(), 0.0);
  } // testNumberFn10

  void testNumberFn11()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number('+1.5')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertTrue(isNaN(result.asNumber()));
  } // testNumberFn11

  void testNumberFn12()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number('                  -1.5                     ')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.5, result.asNumber(), 0.0);
  } // testNumberFn12

  void testNumberFn13()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("number('               +1.5                        ')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertTrue(isNaN(result.asNumber()));
  } // testNumberFn13

  void testFloorFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor(1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testFloorFn1

  void testFloorFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor(1.0)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testFloorFn2

  void testFloorFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor('1.0')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testFloorFn3

  void testFloorFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor(1.1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testFloorFn4

  void testFloorFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor(0)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(0.0, result.asNumber(), 0.0);
  } // testFloorFn5

  void testFloorFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor(-1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.0, result.asNumber(), 0.0);
  } // testFloorFn6

  void testFloorFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor(-1.0)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.0, result.asNumber(), 0.0);
  } // testFloorFn7

  void testFloorFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor(-1.1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-2.0, result.asNumber(), 0.0);
  } // testFloorFn8

  void testFloorFn9()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("floor('NaN')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertTrue(isNaN(result.asNumber()));
  } // testFloorFn9

  void testCeilingFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling(1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testCeilingFn1

  void testCeilingFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling(1.0)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testCeilingFn2

  void testCeilingFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling('1.0')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testCeilingFn3

  void testCeilingFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling(1.1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(2.0, result.asNumber(), 0.0);
  } // testCeilingFn4

  void testCeilingFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling(0)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(0.0, result.asNumber(), 0.0);
  } // testCeilingFn5

  void testCeilingFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling(-1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.0, result.asNumber(), 0.0);
  } // testCeilingFn6

  void testCeilingFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling(-1.0)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.0, result.asNumber(), 0.0);
  } // testCeilingFn7

  void testCeilingFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling(-1.1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.0, result.asNumber(), 0.0);
  } // testCeilingFn8

  void testCeilingFn9()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("ceiling('NaN')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertTrue(isNaN(result.asNumber()));
  } // testCeilingFn9

  void testStringFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(0)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("0") == result.asString());
  } // testStringFn1

  void testStringFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(true())"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("true") == result.asString());
  } // testStringFn2

  void testStringFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(false())"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("false") == result.asString());
  } // testStringFn3

  void testStringFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(number('poo'))"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("NaN") == result.asString());
  } // testStringFn4

  void testStringFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string('NaN')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("NaN") == result.asString());
  } // testStringFn5

  void testRoundFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(1.0)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testRoundFn1

  void testRoundFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(1.1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testRoundFn2

  void testRoundFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(1.5)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(2.0, result.asNumber(), 0.0);
  } // testRoundFn3

  void testRoundFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(1.9)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(2.0, result.asNumber(), 0.0);
  } // testRoundFn4

  void testRoundFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(-1.0)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.0, result.asNumber(), 0.0);
  } // testRoundFn5

  void testRoundFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(-1.1)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.0, result.asNumber(), 0.0);
  } // testRoundFn6

  void testRoundFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(-1.5)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-1.0, result.asNumber(), 0.0);
  } // testRoundFn7

  void testRoundFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(-1.9)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-2.0, result.asNumber(), 0.0);
  } // testRoundFn8

  void testRoundFn9()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round('NaN')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertTrue(isNaN(result.asNumber()));
  } // testRoundFn9

  void testRoundFn10()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("round(-0.4)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(-0.0, result.asNumber(), 0.0);
  } // testRoundFn10

  void testSumFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("sum(/root)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(0.0, result.asNumber(), 0.0);
  } // testSumFn1

  void testSumFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("sum(/root/child1/@one)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testSumFn2

  void testSumFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("sum(/root//@one)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(2.0, result.asNumber(), 0.0);
  } // testSumFn3

  void testSumFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("sum(/root/child2/@*)"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(4.0, result.asNumber(), 0.0);
  } // testSumFn4

  void testConcatFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("concat('a', 'b')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("ab") == result.asString());
  } // testConcatFn1

  void testConcatFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("concat('a', 'b', 'c')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("abc") == result.asString());
  } // testConcatFn2

  void testConcatFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("concat('a', 'b', 'c', 'd')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("abcd") == result.asString());
  } // testConcatFn3

  void testConcatFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("concat(/root/child2/@one, /root/child2/@two, /root/child2/@three)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("111") == result.asString());
  } // testConcatFn4

  void testConcatFn5()
  {
    try {
      parser.evaluate_expr(SA::construct_from_utf8("concat('please explode')"), document_);
      assertTrue(false);
    }
    catch(...) { }
  } // testConcatFn5

  void testStartsWithFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("starts-with('hello', 'charlie drake')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(false, result.asBool());
  } // testStartsWithFn1

  void testStartsWithFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("starts-with('hello', 'hello mother')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(false, result.asBool());
  } // testStartsWithFn2

  void testStartsWithFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("starts-with('hello mother', 'hello')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(true, result.asBool());
  } // testStartsWithFn3

  void testStartsWithFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("starts-with('hello mother', 'hello mother')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(true, result.asBool());
  } // testStartsWithFn4

  void testStringLengthFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string-length('')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(0.0, result.asNumber(), 0.0);
  } // testStringLengthFn1

  void testStringLengthFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string-length('ab')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(2.0, result.asNumber(), 0.0);
  } // testStringLengthFn2

  void testStringLengthFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string-length('abcd')"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(4.0, result.asNumber(), 0.0);
  } // testStringLengthFn3

  void testStringLengthFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string-length(concat('ab', 'cd'))"), document_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(4.0, result.asNumber(), 0.0);
  } // testStringLengthFn4

  void testStringLengthFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string-length()"), attr_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(1.0, result.asNumber(), 0.0);
  } // testStringLengthFn5

  void testStringLengthFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string-length()"), element1_);
    assertValuesEqual(NUMBER, result.type());
    assertDoublesEqual(0.0, result.asNumber(), 0.0);
  } // testStringLengthFn6

  void testContainsFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("contains('hello', 'charlie drake')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(false, result.asBool());
  } // testContainsFn1

  void testContainsFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("contains('hello', 'hello mother')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(false, result.asBool());
  } // testContainsFn2

  void testContainsFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("contains('hello mother', 'hello')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(true, result.asBool());
  } // testContainsFn3

  void testContainsFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("contains('hello mother', 'hello mother')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(true, result.asBool());
  } // testContainsFn4

  void testContainsFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("contains('she heard a call hello mother somewhere in the distance', 'hello')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(true, result.asBool());
  } // testContainsFn5

  void testContainsFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("contains('my dogs says hello mother', 'hello mother')"), document_);
    assertValuesEqual(Arabica::XPath::BOOL, result.type());
    assertValuesEqual(true, result.asBool());
  } // testContainsFn6

  void testSubstringBeforeFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring-before('1999/04/01', '/')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("1999") == result.asString());
  } // testSubstringBeforeFn1

  void testSubstringBeforeFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring-before('1999/04/01', 'mogadon')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testSubstringBeforeFn2

  void testSubstringBeforeFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring-before('1999/04/01', '/01')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("1999/04") == result.asString());
  } // testStringBeforeFn3

  void testSubstringBeforeFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring-before('1999/04/01', '1')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testStringBeforeFn4

  void testSubstringAfterFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring-after('1999/04/01', '/')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("04/01") == result.asString());
  } // testSubstringAfterFn1

  void testSubstringAfterFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring-after('1999/04/01', 'mogadon')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testSubstringAfterFn2

  void testSubstringAfterFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring-after('1999/04/01', '/01')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testStringAfterFn3

  void testSubstringAfterFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring-after('1999/04/01', '19')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("99/04/01") == result.asString());
  } // testStringAfterFn4

  void testSubstringFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', 2, 3)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("234") == result.asString());
  } // testSubstringFn1

  void testSubstringFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', 2)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("2345") == result.asString());
  } // testSubstringFn2

  void testSubstringFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', 1.5, 2.6)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("234") == result.asString());
  } // testSubstringFn3

  void testSubstringFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', 0, 3)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("12") == result.asString());
  } // testSubstringFn4

  void testSubstringFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', 0 div 0, 3)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testSubstringFn5

  void testSubstringFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', 1, 0 div 0)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testSubstringFn6

  void testSubstringFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', -42, 1 div 0)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("12345") == result.asString());
  } // testSubstringFn7

  void testSubstringFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', -1 div 0, 1 div 0)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testSubstringFn8

  void testSubstringFn9()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', 1, 'NaN')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testSubstringFn9

  void testSubstringFn10()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', NaN)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testSubstringFn10

  void testSubstringFn11()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("substring('12345', NaN, NaN)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testSubstringFn11

  void testNormalizeSpaceFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('12345')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("12345") == result.asString());
  } // testNormalizeSpaceFn1

  void testNormalizeSpaceFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('    12345')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("12345") == result.asString());
  } // testNormalizeSpaceFn2

  void testNormalizeSpaceFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('12345 ')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("12345") == result.asString());
  } // testNormalizeSpaceFn3

  void testNormalizeSpaceFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('    12345    ')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("12345") == result.asString());
  } // testNormalizeSpaceFn4

  void testNormalizeSpaceFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('   12   3   45   ')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("12 3 45") == result.asString());
  } // testNormalizeSpaceFn5

  void testNormalizeSpaceFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('1     2    3   4  5')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("1 2 3 4 5") == result.asString());
  } // testNormalizeSpaceFn6

  void testNormalizeSpaceFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('1\t2\r3\n4\r\n5')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("1 2 3 4 5") == result.asString());
  } // testNormalizeSpaceFn7

  void testNormalizeSpaceFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('\n\n\n\n\n1\n\n\n\n\n2\n\n\n\n\n3\n\n\n\n\n\n4\n\n\n\n\n\n5\n\n\n\n\n')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("1 2 3 4 5") == result.asString());
  } // testNormalizeSpaceFn8

  void testNormalizeSpaceFn9()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("normalize-space('\r\n\r\n\r\n\r\n\r\n1\r\n\r\n\r\n\r\n\r\n2\r\n\r\n\r\n\r\n\r\n3\r\n\r\n\r\n\r\n\r\n\r\n4\r\n\r\n\r\n\r\n\r\n\r\n5\r\n\r\n\r\n\r\n\r\n')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("1 2 3 4 5") == result.asString());
  } // testNormalizeSpaceFn9

  void testTranslateFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("translate('bar','abc','ABC')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("BAr") == result.asString());
  } // testTranslateFn1

  void testTranslateFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("translate('--aaa--','abc-','ABC')"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("AAA") == result.asString());
  } // testTranslateFn2

  void testLocalNameFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(/root)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("root") == result.asString());
  } // testLocalNameFn1

  void testLocalNameFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(/root/child2/@one)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("one") == result.asString());
  } // testLocalNameFn2

  void testLocalNameFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(//comment())"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testLocalNameFn3

  void testLocalNameFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(//processing-instruction())"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("target") == result.asString());
  } // testLocalNameFn4

  void testLocalNameFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name()"), root_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("root") == result.asString());
  } // testLocalNameFn5

  void testLocalNameFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name()"), attr_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("one") == result.asString());
  } // testLocalNameFn6

  void testLocalNameFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(//comment())"), comment_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testLocalNameFn7

  void testLocalNameFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(//processing-instruction())"), processingInstruction_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("target") == result.asString());
  } // testLocalNameFn8

  void testLocalNameFn9()
  {
    using namespace Arabica::XPath;
    root_.appendChild(document_.createElementNS(SA::construct_from_utf8("test-uri"), 
                                                SA::construct_from_utf8("element4")));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(/root/*[last()])"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("element4") == result.asString());
  } // testLocalNameFn9

  void testLocalNameFn10()
  {
    using namespace Arabica::XPath;
    root_.setAttributeNS(SA::construct_from_utf8("test-uri"), 
                         SA::construct_from_utf8("q:woot"), 
                         SA::construct_from_utf8("hello"));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(/root/@*)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("woot") == result.asString());
  } // testLocalNameFn10

  void testLocalNameFn11()
  {
    using namespace Arabica::XPath;
    root_.appendChild(document_.createElementNS(SA::construct_from_utf8("test-uri"), 
                                                SA::construct_from_utf8("q:noob")));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("local-name(/root/*[last()])"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("noob") == result.asString());
  } // testLocalNameFn11

  void testNamespaceURIFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(/root)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNamespaceURIFn1

  void testNamespaceURIFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(/root/child2/@one)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNamespaceURIFn2

  void testNamespaceURIFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(//comment())"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNamespaceURIFn3

  void testNamespaceURIFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(//processing-instruction())"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNamespaceURIFn4

  void testNamespaceURIFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri()"), root_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNamespaceURIFn5

  void testNamespaceURIFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri()"), attr_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNamespaceURIFn6

  void testNamespaceURIFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(//comment())"), comment_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNamespaceURIFn7

  void testNamespaceURIFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(//processing-instruction())"), processingInstruction_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNamespaceURIFn8

  void testNamespaceURIFn9()
  {
    using namespace Arabica::XPath;
    root_.appendChild(document_.createElementNS(SA::construct_from_utf8("test-uri"), 
                                                SA::construct_from_utf8("element4")));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(/root/*[last()])"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("test-uri") == result.asString());
  } // testNamespaceURIFn9

  void testNamespaceURIFn10()
  {
    using namespace Arabica::XPath;
    root_.setAttributeNS(SA::construct_from_utf8("test-uri"), 
                         SA::construct_from_utf8("q:woot"), 
                         SA::construct_from_utf8("hello"));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(/root/@*)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("test-uri") == result.asString());
  } // testNamespaceURIFn10

  void testNamespaceURIFn11()
  {
    using namespace Arabica::XPath;
    root_.appendChild(document_.createElementNS(SA::construct_from_utf8("test-uri"), SA::construct_from_utf8("q:noob")));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace-uri(/root/*[last()])"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("test-uri") == result.asString());
  } // testNamespaceURIFn1
  
  void testNameFn1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(/root)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("root") == result.asString());
  } // testNameFn1

  void testNameFn2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(/root/child2/@one)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("one") == result.asString());
  } // testNameFn2

  void testNameFn3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(//comment())"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNameFn3

  void testNameFn4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(//processing-instruction())"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("target") == result.asString());
  } // testNameFn4

  void testNameFn5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name()"), root_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("root") == result.asString());
  } // testNameFn5

  void testNameFn6()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name()"), attr_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("one") == result.asString());
  } // testNameFn6

  void testNameFn7()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(//comment())"), comment_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("") == result.asString());
  } // testNameFn7

  void testNameFn8()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(//processing-instruction())"), processingInstruction_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("target") == result.asString());
  } // testNameFn8

  void testNameFn9()
  {
    using namespace Arabica::XPath;
    root_.appendChild(document_.createElementNS(SA::construct_from_utf8("test-uri"), 
                                                SA::construct_from_utf8("element4")));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(/root/*[last()])"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("element4") == result.asString());
  } // testNameFn9

  void testNameFn10()
  {
    using namespace Arabica::XPath;
    root_.setAttributeNS(SA::construct_from_utf8("test-uri"), 
                         SA::construct_from_utf8("q:woot"), 
                         SA::construct_from_utf8("hello"));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(/root/@*)"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("q:woot") == result.asString());
  } // testNameFn10

  void testNameFn11()
  {
    using namespace Arabica::XPath;
    root_.appendChild(document_.createElementNS(SA::construct_from_utf8("test-uri"), 
                                                SA::construct_from_utf8("q:noob")));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("name(/root/*[last()])"), document_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("q:noob") == result.asString());
  } // testNameFn11

  void testDocumentOrder1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(/document/*)"), chapters_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("one") == result.asString());
  } // testDocumentOrder1

  void testDocumentOrder2()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(/document/*[last()])"), chapters_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("five") == result.asString());
  } // testDocumentOrder2

  void testDocumentOrder3()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(/document/chapter[5]/preceding-sibling::*[1])"), chapters_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("four") == result.asString());
  } // testDocumentOrder3

  void testDocumentOrder4()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(/document/chapter[5]/preceding-sibling::*[last()])"), chapters_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("one") == result.asString());
  } // testDocumentOrder4

  void testDocumentOrder5()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("string(/document/chapter[5]/preceding-sibling::*)"), chapters_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("one") == result.asString());
  } // testDocumentOrder5

  void testLessThan1()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("true() < true()"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("true() < false()"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("false() < false()"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("false() < true()"), chapters_).asBool());
  } // testLessThan1

  void testLessThan2()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("1 < 1"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("3.0 < 2.0"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("2.0 < 3.0"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("-1 < 1"), chapters_).asBool());
  } // testLessThan2

  void testLessThan3()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("'1' < '1'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("'3.0' < '2.0'"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("'2.0' < '3.0'"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("'-1' < '1'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("-1 < 'ooop'"), chapters_).asBool());
  } // testLessThan3

  void testLessThan4()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number < 0"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[2] < 0"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number < 2"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number < 12"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("0 < /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("0 < /doc/number[2]"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("1 < /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("7 < /doc/number"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("12 < /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()<5] < /doc/number[position()>5]"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()<=5] < /doc/number[position()>4]"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()>5] < /doc/number[position()<5]"), numbers_).asBool());
  } // testLessThan4

  void testLessThanEquals1()
  {
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("true() <= true()"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("true() <= false()"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("false() <= false()"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("false() <= true()"), chapters_).asBool());
  } // testLessThanEquals1

  void testLessThanEquals2()
  {
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("1 <= 1"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("3.0 <= 2.0"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("2.0 <= 3.0"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("-1 <= 1"), chapters_).asBool());
  } // testLessThanEquals2

  void testLessThanEquals3()
  {
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("'1' <= '1'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("'3.0' <= '2.0'"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("'2.0' <= '3.0'"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("'-1' <= '1'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("-1 <= 'ooop'"), chapters_).asBool());
  } // testLessThanEquals3

  void testLessThanEquals4()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number <= 0"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[2] <= 0"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number <= 2"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number <= 12"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("0 <= /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("0 <= /doc/number[2]"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("1 <= /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("7 <= /doc/number"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("12 <= /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()<5] <= /doc/number[position()>5]"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()<=5] <= /doc/number[position()>4]"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()>5] <= /doc/number[position()<5]"), numbers_).asBool());
  } // testLessThanEquals4

  void testGreaterThan1()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("true() > true()"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("true() > false()"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("false() > false()"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("false() > true()"), chapters_).asBool());
  } // testGreaterThan1

  void testGreaterThan2()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("1 > 1"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("3.0 > 2.0"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("2.0 > 3.0"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("-1 > 1"), chapters_).asBool());
  } // testGreaterThan2

  void testGreaterThan3()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("'1' > '1'"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("'3.0' > '2.0'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("'2.0' > '3.0'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("'-1' > '1'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("-1 > 'ooop'"), chapters_).asBool());
  } // testGreaterThan3

  void testGreaterThan4()
  {
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("3 > 2 > 1"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("(3>2)>1"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("3 > (2 > 1)"), chapters_).asBool());
  } // testGreaterThan4

  void testGreaterThan5()
  {
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number > 0"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[2] > 0"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number > 1"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number > 12"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("0 > /doc/number"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("0 > /doc/number[2]"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("1 > /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("7 > /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("12 > /doc/number"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()<5] > /doc/number[position()>5]"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()<=5] > /doc/number[position()>4]"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()>5] > /doc/number[position()<5]"), numbers_).asBool());
  } // testGreaterThan4

  void testGreaterThanEquals1()
  {
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("true() >= true()"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("true() >= false()"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("false() >= false()"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("false() >= true()"), chapters_).asBool());
  } // testGreaterThanEquals1

  void testGreaterThanEquals2()
  {
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("1 >= 1"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("3.0 >= 2.0"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("2.0 >= 3.0"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("-1 >= 1"), chapters_).asBool());
  } // testGreaterThanEquals2

  void testGreaterThanEquals3()
  {
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("'1' >= '1'"), chapters_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("'3.0' >= '2.0'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("'2.0' >= '3.0'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("'-1' >= '1'"), chapters_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("-1 >= 'ooop'"), chapters_).asBool());
  } // testGreaterThanEquals3

  void testGreaterThanEquals4()
  {
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number >= 0"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[2] >= 0"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number >= 1"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number >= 12"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("0 >= /doc/number"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("0 >= /doc/number[2]"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("1 >= /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("7 >= /doc/number"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("12 >= /doc/number"), numbers_).asBool());
    assertValuesEqual(false, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()<5] >= /doc/number[position()>5]"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()<=5] >= /doc/number[position()>4]"), numbers_).asBool());
    assertValuesEqual(true, parser.evaluate_expr(SA::construct_from_utf8("/doc/number[position()>5] >= /doc/number[position()<5]"), numbers_).asBool());
  } // testGreaterThanEquals4

  void testNodeSetVars1()
  {
    using namespace Arabica::XPath;
    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);

    parser.setVariableResolver(svr);
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element1_ == result.asNodeSet()[0]);
    assertTrue(element2_ == result.asNodeSet()[1]);
    assertTrue(element3_ == result.asNodeSet()[2]);
  } // testNodeSetVars1

  void testNodeSetVars2()
  {
    using namespace Arabica::XPath;
    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);

    parser.setVariableResolver(svr);
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit/spinkle"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(spinkle_ == result.asNodeSet()[0]);
  } // testNodeSetVars2

  void testNodeSetVars3()
  {
    using namespace Arabica::XPath;
    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);

    parser.setVariableResolver(svr);
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit[2]/*"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(spinkle_ == result.asNodeSet()[0]);
  } // testNodeSetVars3

  void testNodeSetVars4()
  {
    using namespace Arabica::XPath;
    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);

    parser.setVariableResolver(svr);
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit[true()][2]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNodeSetVars4

  void testNodeSetVars5()
  {
    using namespace Arabica::XPath;
    NodeSetVariableResolver<string_type, string_adaptor> svr;
    NodeSet<string_type, string_adaptor> ns;
    ns.push_back(element1_);
    ns.push_back(element2_);
    ns.push_back(element3_);
    svr.setVariable(SA::construct_from_utf8("fruit"), ns);

    parser.setVariableResolver(svr);
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("$fruit[@two]"), document_);
    assertValuesEqual(NODE_SET, result.type());
    assertTrue(element2_ == result.asNodeSet()[0]);
  } // testNodeSetVars5

  void namespaceAxisTest1()
  {
    using namespace Arabica::XPath;
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace::*"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(1, result.asNodeSet().size());
  } // namespaceAxisTest1()

  void namespaceAxisTest2()
  {
    using namespace Arabica::XPath;
    root_.setAttributeNS(SA::construct_from_utf8("http://www.w3.org/2000/xmlns/"), 
                         SA::construct_from_utf8("xmlns:poop"), 
                         SA::construct_from_utf8("urn:test"));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace::*"), root_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(2, result.asNodeSet().size());
    assertTrue(SA::construct_from_utf8("xml") == result.asNodeSet()[0].getLocalName());
    assertTrue(SA::construct_from_utf8("poop") == result.asNodeSet()[1].getLocalName());
    assertTrue(SA::construct_from_utf8("urn:test") == result.asNodeSet()[1].getNodeValue());
  } // namespaceAxisTest2

  void namespaceAxisTest3()
  {
    using namespace Arabica::XPath;
    root_.setAttributeNS(SA::construct_from_utf8("http://www.w3.org/2000/xmlns/"), 
                         SA::construct_from_utf8("xmlns:poop"), 
                         SA::construct_from_utf8("urn:test"));
    element2_.setAttributeNS(SA::construct_from_utf8("http://www.w3.org/2000/xmlns/"), 
                             SA::construct_from_utf8("xmlns:test"), 
                             SA::construct_from_utf8("urn:another-test"));
    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("namespace::*"), element2_);
    assertValuesEqual(NODE_SET, result.type());
    assertValuesEqual(3, result.asNodeSet().size());
  } // namespaceAxisTest3

  void testFunctionResolver1()
  {
    try {
      parser.compile_expr(SA::construct_from_utf8("test-function()"));
      assertTrue(false);
    }
    catch(...) { }
  } // testFunctionResolver1

  void testFunctionResolver2()
  {
    using namespace Arabica::XPath;
    TestFunctionResolver<string_type, string_adaptor> tfr;
    parser.setFunctionResolver(tfr);

    XPathValue<string_type, string_adaptor> result = parser.evaluate_expr(SA::construct_from_utf8("test-function()"), root_);
    assertValuesEqual(STRING, result.type());
    assertTrue(SA::construct_from_utf8("test-root") == result.asString());
  } // testFunctionResolver2

  void testSort1()
  {
    using namespace Arabica::XPath;
    NodeSet<string_type, string_adaptor> ns;

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
    using namespace Arabica::XPath;
    NodeSet<string_type, string_adaptor> ns;

    ns.push_back(element3_);
    ns.push_back(element2_);
    ns.push_back(element1_);

    ns.to_document_order();

    assertTrue(element1_ == ns[0]);
    assertTrue(element2_ == ns[1]);
    assertTrue(element3_ == ns[2]);
  } // testSort2
}; // class ExecuteTest

template<class string_type, class string_adaptor>
TestSuite* ExecuteTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test1", &ExecuteTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test2", &ExecuteTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test3", &ExecuteTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test4", &ExecuteTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test5", &ExecuteTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test6", &ExecuteTest<string_type, string_adaptor>::test6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test7", &ExecuteTest<string_type, string_adaptor>::test7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test8", &ExecuteTest<string_type, string_adaptor>::test8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test9", &ExecuteTest<string_type, string_adaptor>::test9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test10", &ExecuteTest<string_type, string_adaptor>::test10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test11", &ExecuteTest<string_type, string_adaptor>::test11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test12", &ExecuteTest<string_type, string_adaptor>::test12));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test13", &ExecuteTest<string_type, string_adaptor>::test13));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test14", &ExecuteTest<string_type, string_adaptor>::test14));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test15", &ExecuteTest<string_type, string_adaptor>::test15));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test16", &ExecuteTest<string_type, string_adaptor>::test16));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test17", &ExecuteTest<string_type, string_adaptor>::test17));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test18", &ExecuteTest<string_type, string_adaptor>::test18));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test19", &ExecuteTest<string_type, string_adaptor>::test19));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test20", &ExecuteTest<string_type, string_adaptor>::test20));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test21", &ExecuteTest<string_type, string_adaptor>::test21));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test22", &ExecuteTest<string_type, string_adaptor>::test22));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test23", &ExecuteTest<string_type, string_adaptor>::test23));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test24", &ExecuteTest<string_type, string_adaptor>::test24));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test25", &ExecuteTest<string_type, string_adaptor>::test25));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test26", &ExecuteTest<string_type, string_adaptor>::test26));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test26a", &ExecuteTest<string_type, string_adaptor>::test26a));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test27", &ExecuteTest<string_type, string_adaptor>::test27));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test27a", &ExecuteTest<string_type, string_adaptor>::test27a));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test28", &ExecuteTest<string_type, string_adaptor>::test28));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test29", &ExecuteTest<string_type, string_adaptor>::test29));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test30", &ExecuteTest<string_type, string_adaptor>::test30));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test31", &ExecuteTest<string_type, string_adaptor>::test31));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test32", &ExecuteTest<string_type, string_adaptor>::test32));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test33", &ExecuteTest<string_type, string_adaptor>::test33));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test34", &ExecuteTest<string_type, string_adaptor>::test34));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test35", &ExecuteTest<string_type, string_adaptor>::test35));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test36", &ExecuteTest<string_type, string_adaptor>::test36));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test37", &ExecuteTest<string_type, string_adaptor>::test37));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test38", &ExecuteTest<string_type, string_adaptor>::test38));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test39", &ExecuteTest<string_type, string_adaptor>::test39));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test40", &ExecuteTest<string_type, string_adaptor>::test40));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test41", &ExecuteTest<string_type, string_adaptor>::test41));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("test42", &ExecuteTest<string_type, string_adaptor>::test42));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion1", &ExecuteTest<string_type, string_adaptor>::testUnion1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion2", &ExecuteTest<string_type, string_adaptor>::testUnion2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion3", &ExecuteTest<string_type, string_adaptor>::testUnion3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion4", &ExecuteTest<string_type, string_adaptor>::testUnion4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion5", &ExecuteTest<string_type, string_adaptor>::testUnion5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion6", &ExecuteTest<string_type, string_adaptor>::testUnion6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion7", &ExecuteTest<string_type, string_adaptor>::testUnion7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion8", &ExecuteTest<string_type, string_adaptor>::testUnion8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion9", &ExecuteTest<string_type, string_adaptor>::testUnion9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion10", &ExecuteTest<string_type, string_adaptor>::testUnion10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion11", &ExecuteTest<string_type, string_adaptor>::testUnion11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion12", &ExecuteTest<string_type, string_adaptor>::testUnion12));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion13", &ExecuteTest<string_type, string_adaptor>::testUnion13));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testUnion14", &ExecuteTest<string_type, string_adaptor>::testUnion14));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testPlus1", &ExecuteTest<string_type, string_adaptor>::testPlus1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testPlus2", &ExecuteTest<string_type, string_adaptor>::testPlus2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality1", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality2", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality3", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality4", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality5", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality6", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality7", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality8", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetEquality9", &ExecuteTest<string_type, string_adaptor>::testNodeSetEquality9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCountFn1", &ExecuteTest<string_type, string_adaptor>::testCountFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCountFn2", &ExecuteTest<string_type, string_adaptor>::testCountFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCountFn3", &ExecuteTest<string_type, string_adaptor>::testCountFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNotFn1", &ExecuteTest<string_type, string_adaptor>::testNotFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNotFn2", &ExecuteTest<string_type, string_adaptor>::testNotFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testBooleanFn1", &ExecuteTest<string_type, string_adaptor>::testBooleanFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testBooleanFn2", &ExecuteTest<string_type, string_adaptor>::testBooleanFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn1", &ExecuteTest<string_type, string_adaptor>::testNumberFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn2", &ExecuteTest<string_type, string_adaptor>::testNumberFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn3", &ExecuteTest<string_type, string_adaptor>::testNumberFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn4", &ExecuteTest<string_type, string_adaptor>::testNumberFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn5", &ExecuteTest<string_type, string_adaptor>::testNumberFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn6", &ExecuteTest<string_type, string_adaptor>::testNumberFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn7", &ExecuteTest<string_type, string_adaptor>::testNumberFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn8", &ExecuteTest<string_type, string_adaptor>::testNumberFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn9", &ExecuteTest<string_type, string_adaptor>::testNumberFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn10", &ExecuteTest<string_type, string_adaptor>::testNumberFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn11", &ExecuteTest<string_type, string_adaptor>::testNumberFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn12", &ExecuteTest<string_type, string_adaptor>::testNumberFn12));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNumberFn13", &ExecuteTest<string_type, string_adaptor>::testNumberFn13));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn1", &ExecuteTest<string_type, string_adaptor>::testFloorFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn2", &ExecuteTest<string_type, string_adaptor>::testFloorFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn3", &ExecuteTest<string_type, string_adaptor>::testFloorFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn4", &ExecuteTest<string_type, string_adaptor>::testFloorFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn5", &ExecuteTest<string_type, string_adaptor>::testFloorFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn6", &ExecuteTest<string_type, string_adaptor>::testFloorFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn7", &ExecuteTest<string_type, string_adaptor>::testFloorFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn8", &ExecuteTest<string_type, string_adaptor>::testFloorFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFloorFn9", &ExecuteTest<string_type, string_adaptor>::testFloorFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn1", &ExecuteTest<string_type, string_adaptor>::testCeilingFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn2", &ExecuteTest<string_type, string_adaptor>::testCeilingFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn3", &ExecuteTest<string_type, string_adaptor>::testCeilingFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn4", &ExecuteTest<string_type, string_adaptor>::testCeilingFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn5", &ExecuteTest<string_type, string_adaptor>::testCeilingFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn6", &ExecuteTest<string_type, string_adaptor>::testCeilingFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn7", &ExecuteTest<string_type, string_adaptor>::testCeilingFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn8", &ExecuteTest<string_type, string_adaptor>::testCeilingFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testCeilingFn9", &ExecuteTest<string_type, string_adaptor>::testCeilingFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringFn1", &ExecuteTest<string_type, string_adaptor>::testStringFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringFn2", &ExecuteTest<string_type, string_adaptor>::testStringFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringFn3", &ExecuteTest<string_type, string_adaptor>::testStringFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringFn4", &ExecuteTest<string_type, string_adaptor>::testStringFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringFn5", &ExecuteTest<string_type, string_adaptor>::testStringFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn1", &ExecuteTest<string_type, string_adaptor>::testRoundFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn2", &ExecuteTest<string_type, string_adaptor>::testRoundFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn3", &ExecuteTest<string_type, string_adaptor>::testRoundFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn4", &ExecuteTest<string_type, string_adaptor>::testRoundFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn5", &ExecuteTest<string_type, string_adaptor>::testRoundFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn6", &ExecuteTest<string_type, string_adaptor>::testRoundFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn7", &ExecuteTest<string_type, string_adaptor>::testRoundFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn8", &ExecuteTest<string_type, string_adaptor>::testRoundFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn9", &ExecuteTest<string_type, string_adaptor>::testRoundFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testRoundFn10", &ExecuteTest<string_type, string_adaptor>::testRoundFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSumFn1", &ExecuteTest<string_type, string_adaptor>::testSumFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSumFn2", &ExecuteTest<string_type, string_adaptor>::testSumFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSumFn3", &ExecuteTest<string_type, string_adaptor>::testSumFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSumFn4", &ExecuteTest<string_type, string_adaptor>::testSumFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testConcatFn1", &ExecuteTest<string_type, string_adaptor>::testConcatFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testConcatFn2", &ExecuteTest<string_type, string_adaptor>::testConcatFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testConcatFn3", &ExecuteTest<string_type, string_adaptor>::testConcatFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testConcatFn4", &ExecuteTest<string_type, string_adaptor>::testConcatFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testConcatFn5", &ExecuteTest<string_type, string_adaptor>::testConcatFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStartsWithFn1", &ExecuteTest<string_type, string_adaptor>::testStartsWithFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStartsWithFn2", &ExecuteTest<string_type, string_adaptor>::testStartsWithFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStartsWithFn3", &ExecuteTest<string_type, string_adaptor>::testStartsWithFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStartsWithFn4", &ExecuteTest<string_type, string_adaptor>::testStartsWithFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringLengthFn1", &ExecuteTest<string_type, string_adaptor>::testStringLengthFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringLengthFn2", &ExecuteTest<string_type, string_adaptor>::testStringLengthFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringLengthFn3", &ExecuteTest<string_type, string_adaptor>::testStringLengthFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringLengthFn4", &ExecuteTest<string_type, string_adaptor>::testStringLengthFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringLengthFn5", &ExecuteTest<string_type, string_adaptor>::testStringLengthFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testStringLengthFn6", &ExecuteTest<string_type, string_adaptor>::testStringLengthFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testContainsFn1", &ExecuteTest<string_type, string_adaptor>::testContainsFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testContainsFn2", &ExecuteTest<string_type, string_adaptor>::testContainsFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testContainsFn3", &ExecuteTest<string_type, string_adaptor>::testContainsFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testContainsFn4", &ExecuteTest<string_type, string_adaptor>::testContainsFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testContainsFn5", &ExecuteTest<string_type, string_adaptor>::testContainsFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testContainsFn6", &ExecuteTest<string_type, string_adaptor>::testContainsFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringBeforeFn1", &ExecuteTest<string_type, string_adaptor>::testSubstringBeforeFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringBeforeFn2", &ExecuteTest<string_type, string_adaptor>::testSubstringBeforeFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringBeforeFn3", &ExecuteTest<string_type, string_adaptor>::testSubstringBeforeFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringBeforeFn4", &ExecuteTest<string_type, string_adaptor>::testSubstringBeforeFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringAfterFn1", &ExecuteTest<string_type, string_adaptor>::testSubstringAfterFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringAfterFn2", &ExecuteTest<string_type, string_adaptor>::testSubstringAfterFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringAfterFn3", &ExecuteTest<string_type, string_adaptor>::testSubstringAfterFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringAfterFn4", &ExecuteTest<string_type, string_adaptor>::testSubstringAfterFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn1", &ExecuteTest<string_type, string_adaptor>::testSubstringFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn2", &ExecuteTest<string_type, string_adaptor>::testSubstringFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn3", &ExecuteTest<string_type, string_adaptor>::testSubstringFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn4", &ExecuteTest<string_type, string_adaptor>::testSubstringFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn5", &ExecuteTest<string_type, string_adaptor>::testSubstringFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn6", &ExecuteTest<string_type, string_adaptor>::testSubstringFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn7", &ExecuteTest<string_type, string_adaptor>::testSubstringFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn8", &ExecuteTest<string_type, string_adaptor>::testSubstringFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn9", &ExecuteTest<string_type, string_adaptor>::testSubstringFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn10", &ExecuteTest<string_type, string_adaptor>::testSubstringFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSubstringFn11", &ExecuteTest<string_type, string_adaptor>::testSubstringFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn1", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn2", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn3", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn4", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn5", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn6", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn7", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn8", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNormalizeSpaceFn9", &ExecuteTest<string_type, string_adaptor>::testNormalizeSpaceFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testTranslateFn1", &ExecuteTest<string_type, string_adaptor>::testTranslateFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testTranslateFn2", &ExecuteTest<string_type, string_adaptor>::testTranslateFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn1", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn2", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn3", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn4", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn5", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn6", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn7", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn8", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn9", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn10", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLocalNameFn11", &ExecuteTest<string_type, string_adaptor>::testLocalNameFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn1", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn2", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn3", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn4", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn5", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn6", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn7", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn8", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn9", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn10", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNamespaceURIFn11", &ExecuteTest<string_type, string_adaptor>::testNamespaceURIFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn1", &ExecuteTest<string_type, string_adaptor>::testNameFn1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn2", &ExecuteTest<string_type, string_adaptor>::testNameFn2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn3", &ExecuteTest<string_type, string_adaptor>::testNameFn3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn4", &ExecuteTest<string_type, string_adaptor>::testNameFn4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn5", &ExecuteTest<string_type, string_adaptor>::testNameFn5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn6", &ExecuteTest<string_type, string_adaptor>::testNameFn6));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn7", &ExecuteTest<string_type, string_adaptor>::testNameFn7));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn8", &ExecuteTest<string_type, string_adaptor>::testNameFn8));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn9", &ExecuteTest<string_type, string_adaptor>::testNameFn9));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn10", &ExecuteTest<string_type, string_adaptor>::testNameFn10));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNameFn11", &ExecuteTest<string_type, string_adaptor>::testNameFn11));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testDocumentOrder1", &ExecuteTest<string_type, string_adaptor>::testDocumentOrder1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testDocumentOrder2", &ExecuteTest<string_type, string_adaptor>::testDocumentOrder2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testDocumentOrder3", &ExecuteTest<string_type, string_adaptor>::testDocumentOrder3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testDocumentOrder4", &ExecuteTest<string_type, string_adaptor>::testDocumentOrder4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testDocumentOrder5", &ExecuteTest<string_type, string_adaptor>::testDocumentOrder5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLessThan1", &ExecuteTest<string_type, string_adaptor>::testLessThan1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLessThan2", &ExecuteTest<string_type, string_adaptor>::testLessThan2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLessThan3", &ExecuteTest<string_type, string_adaptor>::testLessThan3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLessThan4", &ExecuteTest<string_type, string_adaptor>::testLessThan4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLessThanEquals1", &ExecuteTest<string_type, string_adaptor>::testLessThanEquals1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLessThanEquals2", &ExecuteTest<string_type, string_adaptor>::testLessThanEquals2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLessThanEquals3", &ExecuteTest<string_type, string_adaptor>::testLessThanEquals3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testLessThanEquals4", &ExecuteTest<string_type, string_adaptor>::testLessThanEquals4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThan1", &ExecuteTest<string_type, string_adaptor>::testGreaterThan1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThan2", &ExecuteTest<string_type, string_adaptor>::testGreaterThan2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThan3", &ExecuteTest<string_type, string_adaptor>::testGreaterThan3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThan4", &ExecuteTest<string_type, string_adaptor>::testGreaterThan4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThan5", &ExecuteTest<string_type, string_adaptor>::testGreaterThan5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThanEquals1", &ExecuteTest<string_type, string_adaptor>::testGreaterThanEquals1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThanEquals2", &ExecuteTest<string_type, string_adaptor>::testGreaterThanEquals2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThanEquals3", &ExecuteTest<string_type, string_adaptor>::testGreaterThanEquals3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testGreaterThanEquals4", &ExecuteTest<string_type, string_adaptor>::testGreaterThanEquals4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetVars1", &ExecuteTest<string_type, string_adaptor>::testNodeSetVars1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetVars2", &ExecuteTest<string_type, string_adaptor>::testNodeSetVars2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetVars3", &ExecuteTest<string_type, string_adaptor>::testNodeSetVars3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetVars4", &ExecuteTest<string_type, string_adaptor>::testNodeSetVars4));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testNodeSetVars5", &ExecuteTest<string_type, string_adaptor>::testNodeSetVars5));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("namespaceAxisTest1", &ExecuteTest<string_type, string_adaptor>::namespaceAxisTest1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("namespaceAxisTest2", &ExecuteTest<string_type, string_adaptor>::namespaceAxisTest2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("namespaceAxisTest3", &ExecuteTest<string_type, string_adaptor>::namespaceAxisTest3));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFunctionResolver1", &ExecuteTest<string_type, string_adaptor>::testFunctionResolver1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testFunctionResolver2", &ExecuteTest<string_type, string_adaptor>::testFunctionResolver2));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSort1", &ExecuteTest<string_type, string_adaptor>::testSort1));
  suiteOfTests->addTest(new TestCaller<ExecuteTest<string_type, string_adaptor> >("testSort2", &ExecuteTest<string_type, string_adaptor>::testSort2));
 
  return suiteOfTests;
} // ExecuteTest_suite

#endif

