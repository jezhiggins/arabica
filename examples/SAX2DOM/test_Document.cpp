#ifdef _MSC_VER 
#pragma warning(disable: 4786 4250 4503)
#endif
#include "CppUnit/framework/TestCase.h"
#include "CppUnit/framework/TestSuite.h"
#include "CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.h>

class DocumentTest : public TestCase 
{
  DOM::DOMImplementation<std::string> factory;

  public: 
    DocumentTest(std::string name) :
        TestCase(name) 
    {
    } // DocumentTest
    
    void setUp() 
    {
      factory = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    } // setUp

    void testNull() 
    {
      DOM::Document<std::string> d;
      DOM::Node<std::string> n;
      assert(d == 0);
      assert(n == 0);
      assert(n == d);
    } // testNull

    void testAssignment()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      assert(d != 0);
      assert(d.getNodeName() == "#document");
      assert(d.getNodeValue() == "");

      DOM::Node<std::string> n;
      assert(n == 0);
      assert(n != d);

      n = d;

      assert(n == d);
      assert(d == DOM::Document<std::string>(n));

      DOM::Document<std::string> d2;
      assert(d != d2);
      assert(d2!= d);
      d2 = d;
      assert(d == d2);
      assert(d2 == d);

      DOM::Document<std::string> d3 = factory.createDocument("","", 0);
      assert(d != d3);
      assert(d3!= d);
      d3 = d;
      assert(d == d3);
      assert(d3 == d);
    } // testAssignment

    void testDocElem()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      DOM::NodeList<std::string> nl = d.getChildNodes();
      assert(nl.getLength() == 0);

      DOM::Element<std::string> elem = d.createElement("root");
      assert(elem.getParentNode() == 0);
      assert(elem.getOwnerDocument() == d);

      d.appendChild(elem);
      assert(nl.getLength() == 1);
      assert(elem.getParentNode() == d);
      assert(elem.getOwnerDocument() == d);

      assert(d.getDocumentElement() == elem);
      assert(d.getFirstChild() == elem);
      assert(nl.item(0) == elem);

      DOM::Element<std::string> elem2 = d.createElement("root1");
      try 
      {
        d.appendChild(elem2);
      }
      catch(const DOM::DOMException&)
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
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      d.appendChild(d.createElement("root"));
      d.getFirstChild().appendChild(d.createElement("child"));
      d.getFirstChild().appendChild(d.createElement("child2"));
      d.getFirstChild().appendChild(d.createElement("child3"));

      DOM::Document<std::string> clone = DOM::Document<std::string>(d.cloneNode(false));
      assert(clone.getFirstChild() == 0);
    } // test4

    void test5()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      d.appendChild(d.createElement("root"));
      d.getFirstChild().appendChild(d.createElement("child"));
      d.getFirstChild().appendChild(d.createElement("child2"));
      d.getFirstChild().appendChild(d.createElement("child3"));

      DOM::Document<std::string> clone = DOM::Document<std::string>(d.cloneNode(true));
      assert(clone.getFirstChild().getNodeName() == "root");
      assert(clone.getFirstChild().getFirstChild().getNodeName() == "child");
      assert(clone.getFirstChild().getLastChild().getNodeName() == "child3");
    } // test5

    void test6()
    {
      DOM::Document<std::string> d1 = factory.createDocument("","", 0);
      DOM::Document<std::string> d2 = factory.createDocument("","", 0);

      DOM::Attr<std::string> a1 = d1.createAttribute("attr");
      a1.setNodeValue("value");

      DOM::Node<std::string> a2 = d2.importNode(a1, true);
      assert(a2.getNodeType() == DOM::Node<std::string>::ATTRIBUTE_NODE);
      assert(a2.getNodeName() == a1.getNodeName());
      assert(a2.getNodeValue() == a1.getNodeValue());
      assert(a2.getOwnerDocument() == d2);
      assert(a2.getChildNodes().getLength() == 1);
      assert(a2.getFirstChild().getNodeValue() == "value");
      DOM::Attr<std::string> asAttr = DOM::Attr<std::string>(a2);
      assert(asAttr.getSpecified());
      assert(asAttr.getOwnerElement() == 0);
    } // test6

    void test7()
    {
      DOM::Document<std::string> d1 = factory.createDocument("","", 0);
      DOM::Document<std::string> d2 = factory.createDocument("","", 0);

      DOM::DocumentFragment<std::string> df1 = d1.createDocumentFragment();
      df1.appendChild(d1.createElement("c1"));
      df1.appendChild(d1.createElement("c2"));
      df1.appendChild(d1.createElement("c3"));
      df1.appendChild(d1.createElement("c4"));
      df1.getFirstChild().appendChild(d1.createElement("sc1"));
      df1.getFirstChild().appendChild(d1.createElement("sc2"));
      df1.getFirstChild().appendChild(d1.createElement("sc3"));
      df1.getFirstChild().appendChild(d1.createElement("sc4"));

      DOM::Node<std::string> df2nc = d2.importNode(df1, false);
      assert(df2nc.getOwnerDocument() == d2);
      assert(df2nc.getChildNodes().getLength() == 0);

      DOM::Node<std::string> df2 = d2.importNode(df1, true);
      assert(df2.getOwnerDocument() == d2);
      assert(df2.getNodeType() == DOM::Node<std::string>::DOCUMENT_FRAGMENT_NODE);
      assert(df2.getChildNodes().getLength() == 4);
      assert(df2.getFirstChild().getChildNodes().getLength() == 4);
      DOM::NodeList<std::string> c = df2.getChildNodes();
      assert(c.item(0).getNodeName() == "c1");
      assert(c.item(1).getNodeName() == "c2");
      assert(c.item(2).getNodeName() == "c3");
      assert(c.item(3).getNodeName() == "c4");
      assert(c.item(0).getChildNodes().getLength() == 4);
      assert(c.item(1).getChildNodes().getLength() == 0);
      assert(c.item(2).getChildNodes().getLength() == 0);
      assert(c.item(3).getChildNodes().getLength() == 0);
      c = df2.getFirstChild().getChildNodes();
      assert(c.item(0).getNodeName() == "sc1");
      assert(c.item(1).getNodeName() == "sc2");
      assert(c.item(2).getNodeName() == "sc3");
      assert(c.item(3).getNodeName() == "sc4");
    } // test7

    void test8()
    {
      DOM::Document<std::string> d = factory.createDocument("","", 0);
      d.appendChild(d.createElement("root"));
      d.getFirstChild().appendChild(d.createElement("child"));
      d.getFirstChild().appendChild(d.createElement("child"));
      d.getFirstChild().appendChild(d.createElement("child"));

      assert(d.getElementsByTagName("boots").getLength() == 0);
      assert(d.getElementsByTagName("root").getLength() == 1);
      assert(d.getElementsByTagName("*").getLength() == 4);
      assert(d.getElementsByTagNameNS("*", "*").getLength() == 4);

      DOM::NodeList<std::string> children = d.getElementsByTagName("child");
      assert(children.getLength() == 3);
      assert(children.item(0) == d.getFirstChild().getFirstChild());

      d.getFirstChild().getFirstChild().appendChild(d.createElement("donkey"));
      d.getFirstChild().getFirstChild().appendChild(d.createElement("child"));
      d.getFirstChild().getFirstChild().appendChild(d.createElement("donkey"));
      d.getFirstChild().getLastChild().appendChild(d.createElement("donkey"));
      d.getFirstChild().getLastChild().appendChild(d.createElement("child"));
      d.getFirstChild().getLastChild().appendChild(d.createElement("donkey"));

      assert(children.getLength() == 5);
      assert(DOM::Element<std::string>(d.getFirstChild().getFirstChild()).getElementsByTagName("donkey").getLength() == 2);
      assert(DOM::Element<std::string>(d.getFirstChild()).getElementsByTagName("donkey").getLength() == 4);
    } // test8

    void test9()
    {
      DOM::Document<std::string> d = factory.createDocument("","root", 0);
      assert(d.getFirstChild().getNodeName() == "root");
      assert(d.getFirstChild().hasPrefix() == false);
      assert(d.getFirstChild().hasNamespaceURI() == false);
      assert(d.getFirstChild().getLocalName() == "root");
      assert(d.getFirstChild().getPrefix() == "");
      assert(d.getFirstChild().getNamespaceURI() == "");
    } // test9

    void test10()
    {
      DOM::Document<std::string> d = factory.createDocument("http://test/test","test:root", 0);
      assert(d.getFirstChild().getNodeName() == "test:root");
      assert(d.getFirstChild().hasPrefix() == true);
      assert(d.getFirstChild().hasNamespaceURI() == true);
      assert(d.getFirstChild().getLocalName() == "root");
      assert(d.getFirstChild().getPrefix() == "test");
      assert(d.getFirstChild().getNamespaceURI() == "http://test/test");
    } // test10

    void test11()
    {
      DOM::Document<std::string> d = factory.createDocument("http://test/test","root", 0);
      assert(d.getFirstChild().getNodeName() == "root");
      assert(d.getFirstChild().hasPrefix() == false);
      assert(d.getFirstChild().hasNamespaceURI() == true);
      assert(d.getFirstChild().getLocalName() == "root");
      assert(d.getFirstChild().getPrefix() == "");
      assert(d.getFirstChild().getNamespaceURI() == "http://test/test");
    } // test11

    void test12()
    {
      DOM::Document<std::string> d = factory.createDocument("http://test/test","root", 0);
      assert(d.getFirstChild().getNodeName() == "root");
      assert(d.getFirstChild().hasPrefix() == false);
      assert(d.getFirstChild().hasNamespaceURI() == true);
      assert(d.getFirstChild().getLocalName() == "root");
      assert(d.getFirstChild().getPrefix() == "");
      assert(d.getFirstChild().getNamespaceURI() == "http://test/test");

      d.getFirstChild().setPrefix("test");
      assert(d.getFirstChild().getNodeName() == "test:root");
      assert(d.getFirstChild().hasPrefix() == true);
      assert(d.getFirstChild().hasNamespaceURI() == true);
      assert(d.getFirstChild().getLocalName() == "root");
      assert(d.getFirstChild().getPrefix() == "test");
      assert(d.getFirstChild().getNamespaceURI() == "http://test/test");
    } // test12

    void test13()
    {
      DOM::Document<std::string> d = factory.createDocument("http://test/test","root", 0);
      DOM::Element<std::string> root = d.getDocumentElement();
      root.appendChild(d.createTextNode("hello "));
      root.appendChild(d.createTextNode("mother, " ));
      root.appendChild(d.createTextNode("how "));
      root.appendChild(d.createTextNode("are "));
      root.appendChild(d.createTextNode("you?"));

      assert(root.getChildNodes().getLength() == 5);
      root.normalize();
      assert(root.getChildNodes().getLength() == 1);
      assert(root.getFirstChild().getNodeValue() == "hello mother, how are you?");
    } // test13
};

TestSuite* DocumentTest_suite() 
{
    TestSuite *suiteOfTests = new TestSuite;
    suiteOfTests->addTest(new TestCaller<DocumentTest>("testNill", &DocumentTest::testNull));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("testAssignment", &DocumentTest::testAssignment));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("testDocElem", &DocumentTest::testDocElem));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test4", &DocumentTest::test4));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test5", &DocumentTest::test5));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test6", &DocumentTest::test6));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test7", &DocumentTest::test7));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test8", &DocumentTest::test8));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test9", &DocumentTest::test9));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test10", &DocumentTest::test10));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test11", &DocumentTest::test11));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test12", &DocumentTest::test12));
    suiteOfTests->addTest(new TestCaller<DocumentTest>("test13", &DocumentTest::test13));
    return suiteOfTests;
} // MathTest_suite

