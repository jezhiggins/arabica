#ifndef AXIS_ENUMERATOR_TEST_H
#define AXIS_ENUMERATOR_TEST_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>
#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class AxisEnumeratorTest : public TestCase
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory_;
  Arabica::DOM::Document<string_type, string_adaptor> document_;

  Arabica::DOM::Element<string_type, string_adaptor> root_;

  Arabica::DOM::Element<string_type, string_adaptor> element1_;
  Arabica::DOM::Element<string_type, string_adaptor> element2_;
  Arabica::DOM::Element<string_type, string_adaptor> element3_;

  Arabica::DOM::Attr<string_type, string_adaptor> attr_;

  Arabica::DOM::Text<string_type, string_adaptor> text_;

  Arabica::DOM::Comment<string_type, string_adaptor> comment_;

  Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> processingInstruction_;

public:
  AxisEnumeratorTest(const std::string& name) : TestCase(name)
  {
  } // AxisEnumeratorTest

  void setUp()
  {
    factory_ = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    document_ = factory_.createDocument(string_adaptor::construct_from_utf8(""), string_adaptor::construct_from_utf8("root"), 0);
    root_ = document_.getDocumentElement();

    element1_ = document_.createElement(string_adaptor::construct_from_utf8("child1"));
    element2_ = document_.createElement(string_adaptor::construct_from_utf8("child2"));
    element3_ = document_.createElement(string_adaptor::construct_from_utf8("child3"));

    element1_.setAttribute(string_adaptor::construct_from_utf8("one"), string_adaptor::construct_from_utf8("1"));

    element2_.setAttribute(string_adaptor::construct_from_utf8("one"), string_adaptor::construct_from_utf8("1"));
    element2_.setAttribute(string_adaptor::construct_from_utf8("two"), string_adaptor::construct_from_utf8("1"));
    element2_.setAttribute(string_adaptor::construct_from_utf8("three"), string_adaptor::construct_from_utf8("1"));
    element2_.setAttribute(string_adaptor::construct_from_utf8("four"), string_adaptor::construct_from_utf8("1"));

    text_ = document_.createTextNode(string_adaptor::construct_from_utf8("data"));
    comment_ = document_.createComment(string_adaptor::construct_from_utf8("comment"));
    processingInstruction_ = document_.createProcessingInstruction(string_adaptor::construct_from_utf8("target"), string_adaptor::construct_from_utf8("data"));
    element2_.appendChild(text_);
    element2_.appendChild(document_.createElement(string_adaptor::construct_from_utf8("spinkle")));
    element2_.appendChild(comment_);
    element2_.appendChild(processingInstruction_);

    attr_ = element1_.getAttributeNode(string_adaptor::construct_from_utf8("one"));

    root_.appendChild(element1_);
    root_.appendChild(element2_);
    root_.appendChild(element3_);
  } // setup

  void childTest1()
  {
    Arabica::DOM::DocumentFragment<string_type, string_adaptor> node;

    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(node, Arabica::XPath::CHILD);
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // test1

  void childTest2()
  {
    Arabica::DOM::Node<string_type, string_adaptor> node;

    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(node, Arabica::XPath::CHILD);
    assertTrue(*e == 0);
  } // test2

  void childTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::CHILD);

    assertTrue(element1_ == *e);
    assertTrue(string_adaptor::construct_from_utf8("child1") == e->getNodeName());
    ++e;
    assertTrue(element2_ == *e);
    assertTrue(string_adaptor::construct_from_utf8("child2") == e->getNodeName());
    ++e;
    assertTrue(element3_ == *e);
    assertTrue(string_adaptor::construct_from_utf8("child3") == e->getNodeName());
    ++e;
    assertTrue((Arabica::DOM::Node<string_type, string_adaptor>()) == *e);
    assertTrue(*e == 0);
  } // test3

  void childTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(document_, Arabica::XPath::CHILD);

    assertTrue(root_ == *e);
    ++e;
    assertTrue(*e == 0);
  } // childTest4

  void attributeTest1()
  {
    Arabica::DOM::DocumentFragment<string_type, string_adaptor> node;

    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(node, Arabica::XPath::ATTRIBUTE);
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // attributeTest1

  void attributeTest2()
  {
    Arabica::DOM::Node<string_type, string_adaptor> node;

    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(node, Arabica::XPath::ATTRIBUTE);
    assertTrue(*e == 0);
  } // attributeTest2

  void attributeTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element1_, Arabica::XPath::ATTRIBUTE);
    assertTrue(string_adaptor::construct_from_utf8("one") == e->getNodeName());
    assertTrue(string_adaptor::construct_from_utf8("1") == e->getNodeValue());
    ++e;
    assertTrue(*e == 0);
  } // attributeTest3

  void attributeTest4()
  {
    int count = 0;
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::ATTRIBUTE);
    while(*e++ != 0)
      ++count;
    assertEquals(4, count);
  } // attributeTest4

  void attributeTest5()
  {
    element2_.setAttributeNS(string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/"),
                             string_adaptor::construct_from_utf8("xmlns:poop"), 
                             string_adaptor::construct_from_utf8("poop-uri"));

    int count = 0;
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::ATTRIBUTE);
    while(*e++ != 0)
      ++count;
    assertEquals(4, count);
  } // attributeTest5

  void attributeTest6()
  {
    element2_.setAttributeNS(string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/"), string_adaptor::construct_from_utf8("xmlns:poop"), string_adaptor::construct_from_utf8("poop-uri"));
    element2_.setAttributeNS(string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/"), string_adaptor::construct_from_utf8("xmlns:qooq"), string_adaptor::construct_from_utf8("qooq-uri"));

    int count = 0;
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::ATTRIBUTE);
    while(*e++ != 0)
      ++count;
    assertEquals(4, count);
  } // attributeTest6

  void followingSiblingTest1()
  {
    Arabica::DOM::Node<string_type, string_adaptor> node;
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(node, Arabica::XPath::FOLLOWING_SIBLING);
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // followingSiblingTest1

  void followingSiblingTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(document_, Arabica::XPath::FOLLOWING_SIBLING);
    assertTrue(*e == 0);
  } // followingSiblingTest2

  void followingSiblingTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element1_, Arabica::XPath::FOLLOWING_SIBLING);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingSiblingTest3

  void followingSiblingTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::FOLLOWING_SIBLING);
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingSiblingTest4

  void followingSiblingTest5()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element3_, Arabica::XPath::FOLLOWING_SIBLING);
    assertTrue(*e == 0);
  } // followingSiblingTest5

  void followingSiblingTest6()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(attr_, Arabica::XPath::FOLLOWING_SIBLING);
    assertTrue(*e == 0);
  } // followingSiblingTest6

  void precedingSiblingTest1()
  {
    Arabica::DOM::Node<string_type, string_adaptor> node;
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(node, Arabica::XPath::PRECEDING_SIBLING);
    assertTrue(*e == 0);
    assertTrue(e.reverse());
  } // precedingSiblingTest1

  void precedingSiblingTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(document_, Arabica::XPath::PRECEDING_SIBLING);
    assertTrue(*e == 0);
  } // precedingSiblingTest2

  void precedingSiblingTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element3_, Arabica::XPath::PRECEDING_SIBLING);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingSiblingTest3

  void precedingSiblingTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::PRECEDING_SIBLING);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingSiblingTest4

  void precedingSiblingTest5()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element1_, Arabica::XPath::PRECEDING_SIBLING);
    assertTrue(*e == 0);
  } // precedingSiblingTest5

  void precedingSiblingTest6()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(attr_, Arabica::XPath::PRECEDING_SIBLING);
    assertTrue(*e == 0);
  } // precedingSiblingTest6

  void selfTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(document_, Arabica::XPath::SELF);
    assertTrue(document_ == *e);
    ++e;
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // selfTest1

  void selfTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::SELF);
    assertTrue(root_ == *e);
    ++e;
    assertTrue(*e == 0);
  } // selfTest2

  void selfTest3()
  {
    Arabica::DOM::Node<string_type, string_adaptor> node;
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(node, Arabica::XPath::SELF);
    assertTrue(*e == 0);
  } // selfTest3

  void parentTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(document_, Arabica::XPath::PARENT);
    assertTrue(*e == 0);
    assertTrue(e.reverse());
  } // parentTest1

  void parentTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::PARENT);
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // parentTest2

  void parentTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::PARENT);
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == 0);
  } // parentTest3

  void parentTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(attr_, Arabica::XPath::PARENT);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // parentTest4

  void ancestorTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(document_, Arabica::XPath::ANCESTOR);
    assertTrue(*e == 0);
    assertTrue(e.reverse());
  } // ancestorTest1

  void ancestorTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::ANCESTOR);
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorTest2

  void ancestorTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::ANCESTOR);
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorTest3

  void ancestorTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(attr_, Arabica::XPath::ANCESTOR);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorTest4

  void ancestorOrSelfTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(document_, Arabica::XPath::ANCESTOR_OR_SELF);
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
    assertTrue(e.reverse());
  } // ancestorOrSelfTest1

  void ancestorOrSelfTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::ANCESTOR_OR_SELF);
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorOrSelfTest2

  void ancestorOrSelfTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::ANCESTOR_OR_SELF);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorOrSelfTest3

  void ancestorOrSelfTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(attr_, Arabica::XPath::ANCESTOR_OR_SELF);
    assertTrue(*e == attr_);
    ++e;
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == document_);
    ++e;
    assertTrue(*e == 0);
  } // ancestorOrSelfTest4

  void descendantTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::DESCENDANT);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // descendantTest1

  void descendantTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element1_, Arabica::XPath::DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest2

  void descendantTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::DESCENDANT);
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == 0);
  } // descendantTest3

  void descendantTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(comment_, Arabica::XPath::DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest4

  void descendantTest5()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(processingInstruction_, Arabica::XPath::DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest5

  void descendantTest6()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(text_, Arabica::XPath::DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest6

  void descendantTest7()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(attr_, Arabica::XPath::DESCENDANT);
    assertTrue(*e == 0);
  } // descendantTest7

  void descendantOrSelfTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::DESCENDANT_OR_SELF);
    assertTrue(e.forward());
    assertTrue(*e == root_);
    ++e;
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest1

  void descendantOrSelfTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element1_, Arabica::XPath::DESCENDANT_OR_SELF);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest2

  void descendantOrSelfTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::DESCENDANT_OR_SELF);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest3

  void descendantOrSelfTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(comment_, Arabica::XPath::DESCENDANT_OR_SELF);
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest4

  void descendantOrSelfTest5()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(processingInstruction_, Arabica::XPath::DESCENDANT_OR_SELF);
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest5

  void descendantOrSelfTest6()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(text_, Arabica::XPath::DESCENDANT_OR_SELF);
    assertTrue(*e == text_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest6

  void descendantOrSelfTest7()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(attr_, Arabica::XPath::DESCENDANT_OR_SELF);
    assertTrue(*e == attr_);
    ++e;
    assertTrue(*e == 0);
  } // descendantOrSelfTest7

  void followingTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::FOLLOWING);
    assertTrue(*e == 0);
    assertTrue(e.forward());
  } // followingTest1

  void followingTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element1_, Arabica::XPath::FOLLOWING);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest2

  void followingTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::FOLLOWING);
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest3

  void followingTest4()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(comment_, Arabica::XPath::FOLLOWING);
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest4

  void followingTest5()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(processingInstruction_, Arabica::XPath::FOLLOWING);
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest5

  void followingTest6()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(text_, Arabica::XPath::FOLLOWING);
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest6

  void followingTest7()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(attr_, Arabica::XPath::FOLLOWING);
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == text_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == comment_);
    ++e;
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == element3_);
    ++e;
    assertTrue(*e == 0);
  } // followingTest7

  void precedingTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::PRECEDING);
    assertTrue(*e == 0);
  } // precedingTest1

  void precedingTest2()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element1_, Arabica::XPath::PRECEDING);
    assertTrue(*e == 0);
  } // precedingTest2

  void precedingTest3()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::PRECEDING);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingTest3

  void precedingTest4() 
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(comment_, Arabica::XPath::PRECEDING);
    assertTrue(e.reverse());
    ++e; // spinkle
    assertTrue(*e == text_);
    ++e;
    assertTrue(*e == element1_);
    ++e; 
    assertTrue(*e == 0);
  } // precedingTest4();

  void precedingTest5()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(processingInstruction_, Arabica::XPath::PRECEDING);
    assertTrue(*e == comment_);
    ++e;
    ++e; // spinkle
    assertTrue(*e == text_);
    ++e;
    assertTrue(*e == element1_);
    ++e; 
    assertTrue(*e == 0);
  } // precedingTest5

  void precedingTest6()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(text_, Arabica::XPath::PRECEDING);
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingTest6

  void precedingTest7()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element3_, Arabica::XPath::PRECEDING);
    assertTrue(*e == processingInstruction_);
    ++e;
    assertTrue(*e == comment_);
    ++e;
    ++e; // spinkle;
    assertTrue(*e == text_);
    ++e;
    assertTrue(*e == element2_);
    ++e;
    assertTrue(*e == element1_);
    ++e;
    assertTrue(*e == 0);
  } // precedingTest7

  void namespaceNodeTest1()
  {
    using namespace Arabica::XPath;
    Arabica::DOM::Node<string_type, string_adaptor> node(new impl::NamespaceNodeImpl<string_type, string_adaptor>(element1_, string_adaptor::construct_from_utf8("p"), string_adaptor::construct_from_utf8("test-uri")));
    Arabica::DOM::Node<string_type, string_adaptor> node2;

    node2 = node;
  } // namespaceNodeTest1

  void namespaceNodeTest2()
  {
    using namespace Arabica::XPath;
    Arabica::DOM::Node<string_type, string_adaptor> node;
    {
      Arabica::DOM::Node<string_type, string_adaptor> node2(new impl::NamespaceNodeImpl<string_type, string_adaptor>(element1_, string_adaptor::construct_from_utf8("p"), string_adaptor::construct_from_utf8("test-uri")));
      node = node2;
    }
  } // namespaceNodeTest2

  void namespaceNodeTest3()
  {
    using namespace Arabica::XPath;
    Arabica::DOM::Node<string_type, string_adaptor> node;
    {
      Arabica::DOM::Node<string_type, string_adaptor> node2(new impl::NamespaceNodeImpl<string_type, string_adaptor>(element1_, string_adaptor::construct_from_utf8("p"), string_adaptor::construct_from_utf8("test-uri")));
      node = node2;
    }
    node = 0;
  } // namespaceNodeTest3

  void namespaceNodeTest4()
  {
    using namespace Arabica::XPath;
    Arabica::DOM::Node<string_type, string_adaptor> node(new impl::NamespaceNodeImpl<string_type, string_adaptor>(element1_, string_adaptor::construct_from_utf8("p"), string_adaptor::construct_from_utf8("test-uri")));
    assertTrue(string_adaptor::construct_from_utf8("p") == node.getLocalName());
    assertTrue(string_adaptor::construct_from_utf8("test-uri") == node.getNodeValue());
    assertTrue(string_adaptor::construct_from_utf8("") == node.getNamespaceURI());
    assertTrue(string_adaptor::construct_from_utf8("p") == node.getNodeName());
  } // namespaceNodeTest4

  void namespaceNodeTest5()
  {
    using namespace Arabica::XPath;
    Arabica::DOM::Node<string_type, string_adaptor> node(new impl::NamespaceNodeImpl<string_type, string_adaptor>(element1_, string_adaptor::construct_from_utf8("p"), string_adaptor::construct_from_utf8("test-uri")));
    assertTrue(element1_ == node.getParentNode());
    assertTrue(document_ == node.getOwnerDocument());
  } // namespaceNodeTest5

  void namespaceAxisTest1()
  {
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::NAMESPACE);
    assertTrue(*e != 0);
    Arabica::DOM::Node<string_type, string_adaptor> ns = *e;
    assertTrue(string_adaptor::construct_from_utf8("xml") == ns.getLocalName());
    assertTrue(string_adaptor::construct_from_utf8("http://www.w3.org/XML/1998/namespace") == ns.getNodeValue());
    ++e;
    assertTrue(*e == 0);
  } // namespaceAxisTest1()

  void namespaceAxisTest2()
  {
    root_.setAttributeNS(string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/"), 
                         string_adaptor::construct_from_utf8("xmlns:poop"), 
                         string_adaptor::construct_from_utf8("urn:test"));
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(root_, Arabica::XPath::NAMESPACE);
    assertTrue(*e != 0);
    Arabica::DOM::Node<string_type, string_adaptor> ns = *e;
    assertTrue(string_adaptor::construct_from_utf8("xml") == ns.getLocalName());
    ++e;
    assertTrue(*e != 0);
    ns = *e;
    assertTrue(string_adaptor::construct_from_utf8("poop") == ns.getLocalName());
    assertTrue(string_adaptor::construct_from_utf8("urn:test") == ns.getNodeValue());
    ++e;
    assertTrue(*e == 0);
  } // namespaceAxisTest2

  void namespaceAxisTest3()
  {
    root_.setAttributeNS(string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/"), 
                         string_adaptor::construct_from_utf8("xmlns:poop"), 
                         string_adaptor::construct_from_utf8("urn:test"));
    element2_.setAttributeNS(string_adaptor::construct_from_utf8("http://www.w3.org/2000/xmlns/"), 
                             string_adaptor::construct_from_utf8("xmlns:test"), 
                             string_adaptor::construct_from_utf8("urn:another-test"));
    Arabica::XPath::AxisEnumerator<string_type, string_adaptor> e(element2_, Arabica::XPath::NAMESPACE);
    assertTrue(*e != 0);
    ++e;
    assertTrue(*e != 0);
    ++e;
    assertTrue(*e != 0);
    ++e;
    assertTrue(*e == 0);
  } // namespaceAxisTest3

}; // AxisEnumeratorTest

template<class string_type, class string_adaptor>
TestSuite* AncestorTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("ancestorTest1", &AxisEnumeratorTest<string_type, string_adaptor>::ancestorTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("ancestorTest2", &AxisEnumeratorTest<string_type, string_adaptor>::ancestorTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("ancestorTest3", &AxisEnumeratorTest<string_type, string_adaptor>::ancestorTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("ancestorTest4", &AxisEnumeratorTest<string_type, string_adaptor>::ancestorTest4));

  return suiteOfTests;
} // AncestorTest_suite

template<class string_type, class string_adaptor>
TestSuite* AncestorOrSelfTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("ancestorOrSelfTest1", &AxisEnumeratorTest<string_type, string_adaptor>::ancestorOrSelfTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("ancestorOrSelfTest2", &AxisEnumeratorTest<string_type, string_adaptor>::ancestorOrSelfTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("ancestorOrSelfTest3", &AxisEnumeratorTest<string_type, string_adaptor>::ancestorOrSelfTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("ancestorOrSelfTest4", &AxisEnumeratorTest<string_type, string_adaptor>::ancestorOrSelfTest4));

  return suiteOfTests;
} // AncestorOrSelfTest_suite

template<class string_type, class string_adaptor>
TestSuite* ChildTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("childTest1", &AxisEnumeratorTest<string_type, string_adaptor>::childTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("childTest2", &AxisEnumeratorTest<string_type, string_adaptor>::childTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("childTest3", &AxisEnumeratorTest<string_type, string_adaptor>::childTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("childTest4", &AxisEnumeratorTest<string_type, string_adaptor>::childTest4));

  return suiteOfTests;
} // ChildTest_suite

template<class string_type, class string_adaptor>
TestSuite* AttributeTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("attributeTest1", &AxisEnumeratorTest<string_type, string_adaptor>::attributeTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("attributeTest2", &AxisEnumeratorTest<string_type, string_adaptor>::attributeTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("attributeTest3", &AxisEnumeratorTest<string_type, string_adaptor>::attributeTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("attributeTest4", &AxisEnumeratorTest<string_type, string_adaptor>::attributeTest4));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("attributeTest5", &AxisEnumeratorTest<string_type, string_adaptor>::attributeTest5));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("attributeTest6", &AxisEnumeratorTest<string_type, string_adaptor>::attributeTest6));

  return suiteOfTests;
} // AttributeTest_suite

template<class string_type, class string_adaptor>
TestSuite* FollowingSibling_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingSiblingTest1", &AxisEnumeratorTest<string_type, string_adaptor>::followingSiblingTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingSiblingTest2", &AxisEnumeratorTest<string_type, string_adaptor>::followingSiblingTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingSiblingTest3", &AxisEnumeratorTest<string_type, string_adaptor>::followingSiblingTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingSiblingTest4", &AxisEnumeratorTest<string_type, string_adaptor>::followingSiblingTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingSiblingTest5", &AxisEnumeratorTest<string_type, string_adaptor>::followingSiblingTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingSiblingTest6", &AxisEnumeratorTest<string_type, string_adaptor>::followingSiblingTest6));

  return suite;
} // FollowingSibling_suite

template<class string_type, class string_adaptor>
TestSuite* PrecedingSibling_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingSiblingTest1", &AxisEnumeratorTest<string_type, string_adaptor>::precedingSiblingTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingSiblingTest2", &AxisEnumeratorTest<string_type, string_adaptor>::precedingSiblingTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingSiblingTest3", &AxisEnumeratorTest<string_type, string_adaptor>::precedingSiblingTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingSiblingTest4", &AxisEnumeratorTest<string_type, string_adaptor>::precedingSiblingTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingSiblingTest5", &AxisEnumeratorTest<string_type, string_adaptor>::precedingSiblingTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingSiblingTest6", &AxisEnumeratorTest<string_type, string_adaptor>::precedingSiblingTest6));

  return suite;
} // PrecedingSibling_suite

template<class string_type, class string_adaptor>
TestSuite* SelfTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("selfTest1", &AxisEnumeratorTest<string_type, string_adaptor>::selfTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("selfTest2", &AxisEnumeratorTest<string_type, string_adaptor>::selfTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("selfTest3", &AxisEnumeratorTest<string_type, string_adaptor>::selfTest3));

  return suiteOfTests;
} // SelfTest_suite

template<class string_type, class string_adaptor>
TestSuite* ParentTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("parentTest1", &AxisEnumeratorTest<string_type, string_adaptor>::parentTest1));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("parentTest2", &AxisEnumeratorTest<string_type, string_adaptor>::parentTest2));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("parentTest3", &AxisEnumeratorTest<string_type, string_adaptor>::parentTest3));
  suiteOfTests->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("parentTest4", &AxisEnumeratorTest<string_type, string_adaptor>::parentTest4));

  return suiteOfTests;
} // ParentTest_suite

template<class string_type, class string_adaptor>
TestSuite* DescendantTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantTest1", &AxisEnumeratorTest<string_type, string_adaptor>::descendantTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantTest2", &AxisEnumeratorTest<string_type, string_adaptor>::descendantTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantTest3", &AxisEnumeratorTest<string_type, string_adaptor>::descendantTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantTest4", &AxisEnumeratorTest<string_type, string_adaptor>::descendantTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantTest5", &AxisEnumeratorTest<string_type, string_adaptor>::descendantTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantTest6", &AxisEnumeratorTest<string_type, string_adaptor>::descendantTest6));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantTest7", &AxisEnumeratorTest<string_type, string_adaptor>::descendantTest7));

  return suite;
} // DescendantTest_suite

template<class string_type, class string_adaptor>
TestSuite* DescendantOrSelfTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantOrSelfTest1", &AxisEnumeratorTest<string_type, string_adaptor>::descendantOrSelfTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantOrSelfTest2", &AxisEnumeratorTest<string_type, string_adaptor>::descendantOrSelfTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantOrSelfTest3", &AxisEnumeratorTest<string_type, string_adaptor>::descendantOrSelfTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantOrSelfTest4", &AxisEnumeratorTest<string_type, string_adaptor>::descendantOrSelfTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantOrSelfTest5", &AxisEnumeratorTest<string_type, string_adaptor>::descendantOrSelfTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantOrSelfTest6", &AxisEnumeratorTest<string_type, string_adaptor>::descendantOrSelfTest6));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("descendantOrSelfTest7", &AxisEnumeratorTest<string_type, string_adaptor>::descendantOrSelfTest7));

  return suite;
} // DescendantOrSelfTest_suite

template<class string_type, class string_adaptor>
TestSuite* FollowingTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingTest1", &AxisEnumeratorTest<string_type, string_adaptor>::followingTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingTest2", &AxisEnumeratorTest<string_type, string_adaptor>::followingTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingTest3", &AxisEnumeratorTest<string_type, string_adaptor>::followingTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingTest4", &AxisEnumeratorTest<string_type, string_adaptor>::followingTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingTest5", &AxisEnumeratorTest<string_type, string_adaptor>::followingTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingTest6", &AxisEnumeratorTest<string_type, string_adaptor>::followingTest6));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("followingTest7", &AxisEnumeratorTest<string_type, string_adaptor>::followingTest7));

  return suite;
} // FollowingTest_suite

template<class string_type, class string_adaptor>
TestSuite* PrecedingTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingTest1", &AxisEnumeratorTest<string_type, string_adaptor>::precedingTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingTest2", &AxisEnumeratorTest<string_type, string_adaptor>::precedingTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingTest3", &AxisEnumeratorTest<string_type, string_adaptor>::precedingTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingTest4", &AxisEnumeratorTest<string_type, string_adaptor>::precedingTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingTest5", &AxisEnumeratorTest<string_type, string_adaptor>::precedingTest5));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingTest6", &AxisEnumeratorTest<string_type, string_adaptor>::precedingTest6));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("precedingTest7", &AxisEnumeratorTest<string_type, string_adaptor>::precedingTest7));

  return suite;
} // PrecedingTest_suite

template<class string_type, class string_adaptor>
TestSuite* NamespaceNodeTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("namespaceNodeTest1", &AxisEnumeratorTest<string_type, string_adaptor>::namespaceNodeTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("namespaceNodeTest2", &AxisEnumeratorTest<string_type, string_adaptor>::namespaceNodeTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("namespaceNodeTest3", &AxisEnumeratorTest<string_type, string_adaptor>::namespaceNodeTest3));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("namespaceNodeTest4", &AxisEnumeratorTest<string_type, string_adaptor>::namespaceNodeTest4));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("namespaceNodeTest5", &AxisEnumeratorTest<string_type, string_adaptor>::namespaceNodeTest5));

  return suite;
} // NamespaceNodeTest_suite

template<class string_type, class string_adaptor>
TestSuite* NamespaceAxisTest_suite()
{
  TestSuite* suite = new TestSuite;

  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("namespaceAxisTest1", &AxisEnumeratorTest<string_type, string_adaptor>::namespaceAxisTest1));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("namespaceAxisTest2", &AxisEnumeratorTest<string_type, string_adaptor>::namespaceAxisTest2));
  suite->addTest(new TestCaller<AxisEnumeratorTest<string_type, string_adaptor> >("namespaceAxisTest3", &AxisEnumeratorTest<string_type, string_adaptor>::namespaceAxisTest3));

  return suite;
} // NamespaceAxisTest_suite

template<class string_type, class string_adaptor>
TestSuite* AxisEnumeratorTest_suite()
{
  TestSuite* suiteOfTests = new TestSuite;

  suiteOfTests->addTest(AncestorTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(AncestorOrSelfTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(AttributeTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(ChildTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(FollowingSibling_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(PrecedingSibling_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(SelfTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(ParentTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(DescendantTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(DescendantOrSelfTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(FollowingTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(PrecedingTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(NamespaceNodeTest_suite<string_type, string_adaptor>());
  suiteOfTests->addTest(NamespaceAxisTest_suite<string_type, string_adaptor>());

  return suiteOfTests;
} // AxisEnumeratorTest_suite

#endif

