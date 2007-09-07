#ifndef test_Document_H
#define test_Document_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class DocumentTest : public TestCase 
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  typedef string_adaptor SA;


  public: 
    DocumentTest(std::string name) :
        TestCase(name) 
    {
    } // DocumentTest
    
    void setUp() 
    {
      factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      Arabica::DOM::Document<string_type, string_adaptor> d;
      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
      assert(!d);
      assert(!n);
    } // testNull

    void testAssignment()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      assert(d != 0);
      assert(d);
      assert(d.getNodeName() == SA::construct_from_utf8("#document"));
      assert(d.getNodeValue() == SA::construct_from_utf8(""));

      Arabica::DOM::Node<string_type, string_adaptor> n;
      assert(n == 0);
      assert(!n);
      assert(n != d);

      n = d;

      assert(n);
      assert(n == d);
      assert(d == (Arabica::DOM::Document<string_type, string_adaptor>(n)));

      Arabica::DOM::Document<string_type, string_adaptor> d2;
      assert(d != d2);
      assert(d2!= d);
      d2 = d;
      assert(d == d2);
      assert(d2 == d);

      Arabica::DOM::Document<string_type, string_adaptor> d3 = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      assert(d != d3);
      assert(d3!= d);
      d3 = d;
      assert(d == d3);
      assert(d3 == d);
    } // testAssignment

    void testDocElem()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::NodeList<string_type, string_adaptor> nl = d.getChildNodes();
      assert(nl.getLength() == 0);

      Arabica::DOM::Element<string_type, string_adaptor> elem = d.createElement(SA::construct_from_utf8("root"));
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);

      d.appendChild(elem);
      assert(nl.getLength() == 1);
      assert(elem.getParentNode() == d);
      assert(elem.getOwnerDocument() == d);

      assert(d.getDocumentElement() == elem);
      assert(d.getFirstChild() == elem);
      assert(nl.item(0) == elem);

      Arabica::DOM::Element<string_type, string_adaptor> elem2 = d.createElement(SA::construct_from_utf8("root1"));
      try 
      {
        d.appendChild(elem2);
      }
      catch(const Arabica::DOM::DOMException&)
      {
      }

      d.replaceChild(elem2, elem);
      assert(nl.getLength() == 1);
      assert(elem2.getParentNode() == d);
      assert(elem2.getOwnerDocument() == d);
      assert(elem.getParentNode() == 0);
      assert(d.getDocumentElement() == elem2);
      assert(d.getFirstChild() == elem2);
      assert(nl.item(0) == elem2);

      d.removeChild(elem2);
      assert(nl.getLength() == 0);
      assert(d.getDocumentElement() == 0);
      assert(d.getFirstChild() == 0);
    } // testDocElem

    void test4()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      d.appendChild(d.createElement(SA::construct_from_utf8("root")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child2")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child3")));

      Arabica::DOM::Document<string_type, string_adaptor> clone = Arabica::DOM::Document<string_type, string_adaptor>(d.cloneNode(false));
      assert(clone.getFirstChild() == 0);
    } // test4

    void test5()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      d.appendChild(d.createElement(SA::construct_from_utf8("root")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child2")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child3")));

      Arabica::DOM::Document<string_type, string_adaptor> clone = Arabica::DOM::Document<string_type, string_adaptor>(d.cloneNode(true));
      assert(clone.getFirstChild().getNodeName() == SA::construct_from_utf8("root"));
      assert(clone.getFirstChild().getFirstChild().getNodeName() == SA::construct_from_utf8("child"));
      assert(clone.getFirstChild().getLastChild().getNodeName() == SA::construct_from_utf8("child3"));
    } // test5

    void test6()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d1 = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Document<string_type, string_adaptor> d2 = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);

      Arabica::DOM::Attr<string_type, string_adaptor> a1 = d1.createAttribute(SA::construct_from_utf8("attr"));
      a1.setNodeValue(SA::construct_from_utf8("value"));

      Arabica::DOM::Node<string_type, string_adaptor> a2 = d2.importNode(a1, true);
      assert(a2.getNodeType() == Arabica::DOM::Node_base::ATTRIBUTE_NODE);
      assert(a2.getNodeName() == a1.getNodeName());
      assert(a2.getNodeValue() == a1.getNodeValue());
      assert(a2.getOwnerDocument() == d2);
      assert(a2.getChildNodes().getLength() == 1);
      assert(a2.getFirstChild().getNodeValue() == SA::construct_from_utf8("value"));
      Arabica::DOM::Attr<string_type, string_adaptor> asAttr = Arabica::DOM::Attr<string_type, string_adaptor>(a2);
      assert(asAttr.getSpecified());
      assert(asAttr.getOwnerElement() == 0);
    } // test6

    void test7()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d1 = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Document<string_type, string_adaptor> d2 = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);

      Arabica::DOM::DocumentFragment<string_type, string_adaptor> df1 = d1.createDocumentFragment();
      df1.appendChild(d1.createElement(SA::construct_from_utf8("c1")));
      df1.appendChild(d1.createElement(SA::construct_from_utf8("c2")));
      df1.appendChild(d1.createElement(SA::construct_from_utf8("c3")));
      df1.appendChild(d1.createElement(SA::construct_from_utf8("c4")));
      df1.getFirstChild().appendChild(d1.createElement(SA::construct_from_utf8("sc1")));
      df1.getFirstChild().appendChild(d1.createElement(SA::construct_from_utf8("sc2")));
      df1.getFirstChild().appendChild(d1.createElement(SA::construct_from_utf8("c3")));
      df1.getFirstChild().appendChild(d1.createElement(SA::construct_from_utf8("c4")));

      Arabica::DOM::Node<string_type, string_adaptor> df2nc = d2.importNode(df1, false);
      assert(df2nc.getOwnerDocument() == d2);
      assert(df2nc.getChildNodes().getLength() == 0);

      Arabica::DOM::Node<string_type, string_adaptor> df2 = d2.importNode(df1, true);
      assert(df2.getOwnerDocument() == d2);
      assert(df2.getNodeType() == Arabica::DOM::Node_base::DOCUMENT_FRAGMENT_NODE);
      assert(df2.getChildNodes().getLength() == 4);
      assert(df2.getFirstChild().getChildNodes().getLength() == 4);
      Arabica::DOM::NodeList<string_type, string_adaptor> c = df2.getChildNodes();
      assert(c.item(0).getNodeName() == SA::construct_from_utf8("c1"));
      assert(c.item(1).getNodeName() == SA::construct_from_utf8("c2"));
      assert(c.item(2).getNodeName() == SA::construct_from_utf8("c3"));
      assert(c.item(3).getNodeName() == SA::construct_from_utf8("c4"));
      assert(c.item(0).getChildNodes().getLength() == 4);
      assert(c.item(1).getChildNodes().getLength() == 0);
      assert(c.item(2).getChildNodes().getLength() == 0);
      assert(c.item(3).getChildNodes().getLength() == 0);
      c = df2.getFirstChild().getChildNodes();
      assert(c.item(0).getNodeName() == SA::construct_from_utf8("sc1"));
      assert(c.item(1).getNodeName() == SA::construct_from_utf8("sc2"));
      assert(c.item(2).getNodeName() == SA::construct_from_utf8("c3"));
      assert(c.item(3).getNodeName() == SA::construct_from_utf8("c4"));
    } // test7

    void test8()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      d.appendChild(d.createElement(SA::construct_from_utf8("root")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child")));
      d.getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child")));

      assert(d.getElementsByTagName(SA::construct_from_utf8("boots")).getLength() == 0);
      assert(d.getElementsByTagName(SA::construct_from_utf8("root")).getLength() == 1);
      assert(d.getElementsByTagName(SA::construct_from_utf8("*")).getLength() == 4);
      assert(d.getElementsByTagNameNS(SA::construct_from_utf8("*"), SA::construct_from_utf8("*")).getLength() == 4);

      Arabica::DOM::NodeList<string_type, string_adaptor> children = d.getElementsByTagName(SA::construct_from_utf8("child"));
      assert(children.getLength() == 3);
      assert(children.item(0) == d.getFirstChild().getFirstChild());

      d.getFirstChild().getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("donkey")));
      d.getFirstChild().getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("child")));
      d.getFirstChild().getFirstChild().appendChild(d.createElement(SA::construct_from_utf8("donkey")));
      d.getFirstChild().getLastChild().appendChild(d.createElement(SA::construct_from_utf8("donkey")));
      d.getFirstChild().getLastChild().appendChild(d.createElement(SA::construct_from_utf8("child")));
      d.getFirstChild().getLastChild().appendChild(d.createElement(SA::construct_from_utf8("donkey")));

      assert(children.getLength() == 5);
      assert((Arabica::DOM::Element<string_type, string_adaptor>(d.getFirstChild().getFirstChild()).getElementsByTagName(SA::construct_from_utf8("donkey")).getLength()) == 2);
      assert((Arabica::DOM::Element<string_type, string_adaptor>(d.getFirstChild()).getElementsByTagName(SA::construct_from_utf8("donkey")).getLength()) == 4);
    } // test8

    void test9()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8("root"), 0);
      assert(d.getFirstChild().getNodeName() == SA::construct_from_utf8("root"));
      assert(d.getFirstChild().hasPrefix() == false);
      assert(d.getFirstChild().hasNamespaceURI() == false);
      assert(d.getFirstChild().getLocalName() == SA::construct_from_utf8("root"));
      assert(d.getFirstChild().getPrefix() == SA::construct_from_utf8(""));
      assert(d.getFirstChild().getNamespaceURI() == SA::construct_from_utf8(""));
    } // test9

    void test10()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8("http://test/test"), SA::construct_from_utf8("test:root"), 0);
      assert(d.getFirstChild().getNodeName() == SA::construct_from_utf8("test:root"));
      assert(d.getFirstChild().hasPrefix() == true);
      assert(d.getFirstChild().hasNamespaceURI() == true);
      assert(d.getFirstChild().getLocalName() == SA::construct_from_utf8("root"));
      assert(d.getFirstChild().getPrefix() == SA::construct_from_utf8("test"));
      assert(d.getFirstChild().getNamespaceURI() == SA::construct_from_utf8("http://test/test"));
    } // test10

    void test11()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8("http://test/test"), SA::construct_from_utf8("root"), 0);
      assert(d.getFirstChild().getNodeName() == SA::construct_from_utf8("root"));
      assert(d.getFirstChild().hasPrefix() == false);
      assert(d.getFirstChild().hasNamespaceURI() == true);
      assert(d.getFirstChild().getLocalName() == SA::construct_from_utf8("root"));
      assert(d.getFirstChild().getPrefix() == SA::construct_from_utf8(""));
      assert(d.getFirstChild().getNamespaceURI() == SA::construct_from_utf8("http://test/test"));
    } // test11

    void test12()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8("http://test/test"), SA::construct_from_utf8("root"), 0);
      assert(d.getFirstChild().getNodeName() == SA::construct_from_utf8("root"));
      assert(d.getFirstChild().hasPrefix() == false);
      assert(d.getFirstChild().hasNamespaceURI() == true);
      assert(d.getFirstChild().getLocalName() == SA::construct_from_utf8("root"));
      assert(d.getFirstChild().getPrefix() == SA::construct_from_utf8(""));
      assert(d.getFirstChild().getNamespaceURI() == SA::construct_from_utf8("http://test/test"));

      d.getFirstChild().setPrefix(SA::construct_from_utf8("test"));
      assert(d.getFirstChild().getNodeName() == SA::construct_from_utf8("test:root"));
      assert(d.getFirstChild().hasPrefix() == true);
      assert(d.getFirstChild().hasNamespaceURI() == true);
      assert(d.getFirstChild().getLocalName() == SA::construct_from_utf8("root"));
      assert(d.getFirstChild().getPrefix() == SA::construct_from_utf8("test"));
      assert(d.getFirstChild().getNamespaceURI() == SA::construct_from_utf8("http://test/test"));
    } // test12

    void test13()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8("http://test/test"), SA::construct_from_utf8("root"), 0);
      Arabica::DOM::Element<string_type, string_adaptor> root = d.getDocumentElement();
      root.appendChild(d.createTextNode(SA::construct_from_utf8("hello ")));
      root.appendChild(d.createTextNode(SA::construct_from_utf8("mother, ")));
      root.appendChild(d.createTextNode(SA::construct_from_utf8("how ")));
      root.appendChild(d.createTextNode(SA::construct_from_utf8("are ")));
      root.appendChild(d.createTextNode(SA::construct_from_utf8("you?")));

      assert(root.getChildNodes().getLength() == 5);
      root.normalize();
      assert(root.getChildNodes().getLength() == 1);
      assert(root.getFirstChild().getNodeValue() == SA::construct_from_utf8("hello mother, how are you?"));
    } // test13
};

template<class string_type, class string_adaptor>
TestSuite* DocumentTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("testNill", &DocumentTest<string_type, string_adaptor>::testNull));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("testAssignment", &DocumentTest<string_type, string_adaptor>::testAssignment));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("testDocElem", &DocumentTest<string_type, string_adaptor>::testDocElem));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test4", &DocumentTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test5", &DocumentTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test6", &DocumentTest<string_type, string_adaptor>::test6));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test7", &DocumentTest<string_type, string_adaptor>::test7));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test8", &DocumentTest<string_type, string_adaptor>::test8));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test9", &DocumentTest<string_type, string_adaptor>::test9));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test10", &DocumentTest<string_type, string_adaptor>::test10));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test11", &DocumentTest<string_type, string_adaptor>::test11));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test12", &DocumentTest<string_type, string_adaptor>::test12));
  suiteOfTests->addTest(new TestCaller<DocumentTest<string_type, string_adaptor> >("test13", &DocumentTest<string_type, string_adaptor>::test13));
  return suiteOfTests;
} // DocumentTest_suite

#endif
