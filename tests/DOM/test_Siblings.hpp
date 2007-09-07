#ifndef test_Siblings_H
#define test_Siblings_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class SiblingsTest : public TestCase 
{
  Arabica::DOM::DOMImplementation<string_type, string_adaptor> factory;
  typedef string_adaptor SA;

  public: 
    SiblingsTest(std::string name) :
        TestCase(name) 
    {
    } // SiblingsTest
    
    void setUp() 
    {
      factory = Arabica::SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    } // setUp

    void test1()
    {
      Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
      Arabica::DOM::Element<string_type, string_adaptor> root = d.createElement(SA::construct_from_utf8("root"));
      d.appendChild(root);

      assert(root.getPreviousSibling() == 0);
      assert(root.getNextSibling() == 0);

      Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> p = d.createProcessingInstruction(SA::construct_from_utf8("target"), SA::construct_from_utf8("data"));
      d.insertBefore(p, root);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == root);
      assert(root.getPreviousSibling() == p);
      assert(root.getNextSibling() == 0);

      Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> p2 = d.createProcessingInstruction(SA::construct_from_utf8("target"), SA::construct_from_utf8("data"));
      d.insertBefore(p2, root);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == p2);
      assert(p2.getPreviousSibling() == p);
      assert(p2.getNextSibling() == root);
      assert(root.getPreviousSibling() == p2);
      assert(root.getNextSibling() == 0);

      d.removeChild(p2);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == root);
      assert(p2.getPreviousSibling() == 0);
      assert(p2.getNextSibling() == 0);
      assert(root.getPreviousSibling() == p);
      assert(root.getNextSibling() == 0);

      d.insertBefore(p2, root);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == p2);
      assert(p2.getPreviousSibling() == p);
      assert(p2.getNextSibling() == root);
      assert(root.getPreviousSibling() == p2);
      assert(root.getNextSibling() == 0);

      d.removeChild(p);
      assert(d.getFirstChild() == p2);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == 0);
      assert(p2.getPreviousSibling() == 0);
      assert(p2.getNextSibling() == root);
      assert(root.getPreviousSibling() == p2);
      assert(root.getNextSibling() == 0);

      d.replaceChild(p, p2);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == root);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == root);
      assert(p2.getPreviousSibling() == 0);
      assert(p2.getNextSibling() == 0);
      assert(root.getPreviousSibling() == p);
      assert(root.getNextSibling() == 0);

      d.appendChild(p2);
      assert(d.getFirstChild() == p);
      assert(d.getLastChild() == p2);
      assert(p.getPreviousSibling() == 0);
      assert(p.getNextSibling() == root);
      assert(root.getPreviousSibling() == p);
      assert(root.getNextSibling() == p2);
      assert(p2.getPreviousSibling() == root);
      assert(p2.getNextSibling() == 0);
    } // test1

    void test2()
    {
      Arabica::DOM::Element<string_type, string_adaptor> root;
      {
        Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
        root = d.createElement(SA::construct_from_utf8("root"));
        d.appendChild(root);

        assert(root.getPreviousSibling() == 0);
        assert(root.getNextSibling() == 0);

        Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> p = d.createProcessingInstruction(SA::construct_from_utf8("target"), SA::construct_from_utf8("data"));
        d.insertBefore(p, root);
      }

      Arabica::DOM::Node<string_type, string_adaptor> n = root.getPreviousSibling();
      Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> p = Arabica::DOM::ProcessingInstruction<string_type, string_adaptor>(n);
      assert(p.getTarget() == SA::construct_from_utf8("target"));
      assert(p.getData() == SA::construct_from_utf8("data"));
    } // test2

    void test3()
    {
      Arabica::DOM::Element<string_type, string_adaptor> root;
      {
        Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
        root = d.createElement(SA::construct_from_utf8("root"));
        d.appendChild(root);

        root.appendChild(d.createElement(SA::construct_from_utf8("child1")));
	root.appendChild(d.createElement(SA::construct_from_utf8("child2")));
      }

      Arabica::DOM::Node<string_type, string_adaptor> c = root.getFirstChild();
      assert(c.getNextSibling() == root.getLastChild());

      root.purgeChild(c);

      assert(c == 0);
      assert(root.getLastChild() == root.getFirstChild());
   } // test3

   void test4()
   {
      Arabica::DOM::Element<string_type, string_adaptor> root;
      {
        Arabica::DOM::Document<string_type, string_adaptor> d = factory.createDocument(SA::construct_from_utf8(""), SA::construct_from_utf8(""), 0);
        root = d.createElement(SA::construct_from_utf8("root"));
        d.appendChild(root);

        root.appendChild(d.createElement(SA::construct_from_utf8("child1")));
        root.appendChild(d.createElement(SA::construct_from_utf8("child2")));
      }
    
      Arabica::DOM::Node<string_type, string_adaptor> c1 = root.getFirstChild();
      Arabica::DOM::Node<string_type, string_adaptor> c2 = root.getLastChild();

      try {
        c1.purgeChild(c2);
      }
      catch(Arabica::DOM::DOMException& e)
      {
        assert(e.code() == Arabica::DOM::DOMException::NOT_FOUND_ERR);
      } // catch

  
      assert(c1 != 0);
      assert(c2 != 0);

      assert(c1.getNextSibling() == c2);
      assert(c2.getPreviousSibling() == c1);
    } // test4
};

template<class string_type, class string_adaptor>
TestSuite* SiblingsTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<SiblingsTest<string_type, string_adaptor> >("test1", &SiblingsTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<SiblingsTest<string_type, string_adaptor> >("test2", &SiblingsTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<SiblingsTest<string_type, string_adaptor> >("test3", &SiblingsTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<SiblingsTest<string_type, string_adaptor> >("test4", &SiblingsTest<string_type, string_adaptor>::test4));

  return suiteOfTests;
} // SiblingsTest_suite

#endif

