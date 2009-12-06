#ifndef ARABICA_TEST_SAX2DOM_TEXT_HPP
#define ARABICA_TEST_SAX2DOM_TEXT_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class TextTest : public TestCase 
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  typedef string_adaptor SA;

  public: 
    TextTest(std::string name) :
        TestCase(name) 
    {
    } // TextTest
    
    void setUp() 
    {
      factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      Arabica::DOM::Text<string_type, string_adaptor> d;
      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testCreate()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Text<string_type, string_adaptor> t = d.createTextNode(SA::construct_from_utf8("some data"));

      assert(t.getData() == SA::construct_from_utf8("some data"));
      assert(t.getNodeName() == SA::construct_from_utf8("#text"));
      assert(t.getNodeValue() == t.getData());

      t.setData(SA::construct_from_utf8("newData"));
      assert(t.getData() == SA::construct_from_utf8("newData"));
    } // testCreate

    void testConversion()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Text<string_type, string_adaptor> t = d.createTextNode(SA::construct_from_utf8("some data"));

      Arabica::DOM::Node<string_type, string_adaptor> n;

      assert(n != t);

      n = t;
      assert(n == t);

      Arabica::DOM::Text<string_type, string_adaptor> t2;

      assert(n != t2);

      t2 = Arabica::DOM::Text<string_type, string_adaptor>(n);
      assert(t == t2);
      assert(n == t2);

      Arabica::DOM::Text<string_type, string_adaptor> t3;
      t3 = t2;
      assert(t3 == t2);
      assert(t3 == t);

      Arabica::DOM::Comment<string_type, string_adaptor> c = d.createComment(SA::construct_from_utf8("woo"));
      try {
        t = Arabica::DOM::Text<string_type, string_adaptor>(c);
        assertImplementation(false, "converted comment to text");
      } 
      catch(const std::bad_cast&) {
      }
    } // testConverstion

    void testSplit()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8("doc"), 0);
      Arabica::DOM::Text<string_type, string_adaptor> t = d.createTextNode(SA::construct_from_utf8("some data"));

      assert(t.getData() == SA::construct_from_utf8("some data"));

      Arabica::DOM::Text<string_type, string_adaptor> s = t.splitText(5);
      assert(t.getData() == SA::construct_from_utf8("some "));
      assert(s.getData() == SA::construct_from_utf8("data"));

      t.setData(SA::construct_from_utf8("some data"));
      d.getDocumentElement().appendChild(t);

      assert(t.getData() == SA::construct_from_utf8("some data"));
      assert(t.getPreviousSibling() == 0);
      assert(t.getNextSibling() == 0);

      s = t.splitText(5);
      assert(t.getData() == SA::construct_from_utf8("some "));
      assert(s.getData() == SA::construct_from_utf8("data"));
      assert(t.getPreviousSibling() == 0);
      assert(t.getNextSibling() == s);
      assert(s.getPreviousSibling() == t);
      assert(s.getNextSibling() == 0);
    } // testSplit

    void testEverythingElse()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""),SA::construct_from_utf8(""), 0);
      Arabica::DOM::Text<string_type, string_adaptor> t = d.createTextNode(SA::construct_from_utf8("some data"));

      assert(t.getNodeType() == Arabica::DOM::Node_base::TEXT_NODE);
      assert(t.hasAttributes() == false);
      assert(t.getAttributes() == 0);
      assert(t.getChildNodes() == 0);
      assert(t.getFirstChild() == 0);

      try
      {
        t.appendChild(Arabica::DOM::Node<string_type, string_adaptor>());
      } 
      catch(const Arabica::DOM::DOMException&)
      {
      } 

      assert(t.getFirstChild() == 0);

      assert(t.getOwnerDocument() == d);
      assert(t.getParentNode() == 0);
    } // 
};

template<class string_type, class string_adaptor>
TestSuite* TextTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testNull", &TextTest<string_type, string_adaptor>::testNull));
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testCreate", &TextTest<string_type, string_adaptor>::testCreate));
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testConversion", &TextTest<string_type, string_adaptor>::testConversion));
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testSplit", &TextTest<string_type, string_adaptor>::testSplit));
    suiteOfTests->addTest(new TestCaller<TextTest<string_type, string_adaptor> >("testEverythingElse", &TextTest<string_type, string_adaptor>::testEverythingElse));
    return suiteOfTests;
} // TextTest_suite

#endif

