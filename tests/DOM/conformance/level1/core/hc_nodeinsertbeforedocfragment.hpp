#ifndef test_hc_nodeinsertbeforedocfragment
#define test_hc_nodeinsertbeforedocfragment


/*
This C++ source file was generated for Arabica
from the source document contained in the W3C
DOM Conformance Test Suite.
The source document contained the following notice:


Copyright (c) 2001-2003 World Wide Web Consortium,
(Massachusetts Institute of Technology, Institut National de
Recherche en Informatique et en Automatique, Keio University). All
Rights Reserved. This program is distributed under the W3C's Software
Intellectual Property License. This program is distributed in the
hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.
See W3C License http://www.w3.org/Consortium/Legal/ for more details.

*/
/**
 *     If the "newChild" is a DocumentFragment object then all
 *     its children are inserted in the same order before the
 *     the "refChild". 
 *     
 *     Create a DocumentFragment object and populate it with
 *     two Element nodes.   Retrieve the second employee and
 *     insert the newly created DocumentFragment before its
 *     fourth child.   The second employee should now have two
 *     extra children("newChild1" and "newChild2") at 
 *     positions fourth and fifth respectively.
* @author Curt Arnold
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-952280727">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-952280727</a>
* @see <a href="http://www.w3.org/Bugs/Public/show_bug.cgi?id=247">http://www.w3.org/Bugs/Public/show_bug.cgi?id=247</a>
*/

template<class string_type, class string_adaptor>
class hc_nodeinsertbeforedocfragment : public DOMTestCase<string_type, string_adaptor> 
{
    typedef DOMTestCase<string_type, string_adaptor> baseT;
   public: 
     hc_nodeinsertbeforedocfragment(std::string name) : baseT(name)
     {

       //   check if loaded documents are supported for content type
       const std::string contentType = baseT::getContentType();
    baseT::preload(contentType, "hc_staff", true);
    }

  typedef typename Arabica::DOM::DOMImplementation<string_type, string_adaptor>  DOMImplementation;
  typedef typename Arabica::DOM::Document<string_type, string_adaptor> Document; 
  typedef typename Arabica::DOM::DocumentType<string_type, string_adaptor> DocumentType;
  typedef typename Arabica::DOM::DocumentFragment<string_type, string_adaptor> DocumentFragment; 
  typedef typename Arabica::DOM::Node<string_type, string_adaptor> Node;
  typedef typename Arabica::DOM::Element<string_type, string_adaptor> Element;
  typedef typename Arabica::DOM::Attr<string_type, string_adaptor> Attr;
  typedef typename Arabica::DOM::NodeList<string_type, string_adaptor> NodeList;
  typedef typename Arabica::DOM::NamedNodeMap<string_type, string_adaptor> NamedNodeMap;
  typedef typename Arabica::DOM::Entity<string_type, string_adaptor> Entity;
  typedef typename Arabica::DOM::EntityReference<string_type, string_adaptor> EntityReference;
  typedef typename Arabica::DOM::CharacterData<string_type, string_adaptor> CharacterData;
  typedef typename Arabica::DOM::CDATASection<string_type, string_adaptor> CDATASection;
  typedef typename Arabica::DOM::Text<string_type, string_adaptor> Text;
  typedef typename Arabica::DOM::Comment<string_type, string_adaptor> Comment;
  typedef typename Arabica::DOM::ProcessingInstruction<string_type, string_adaptor> ProcessingInstruction;
  typedef typename Arabica::DOM::Notation<string_type, string_adaptor> Notation;

  typedef typename Arabica::DOM::DOMException DOMException;
  typedef string_type String;
  typedef string_adaptor SA;
  typedef bool boolean;


   /*
    * Runs the test case.
    */
   void runTest()
   {
      Document doc;
      NodeList elementList;
      Node employeeNode;
      NodeList childList;
      Node refChild;
      DocumentFragment newdocFragment;
      Node newChild1;
      Node newChild2;
      Node child;
      String childName;
      Node appendedChild;
      Node insertedNode;
      doc = (Document) baseT::load("hc_staff", true);
      elementList = doc.getElementsByTagName(SA::construct_from_utf8("p"));
      employeeNode = elementList.item(1);
      childList = employeeNode.getChildNodes();
      refChild = childList.item(3);
      newdocFragment = doc.createDocumentFragment();
      newChild1 = doc.createElement(SA::construct_from_utf8("br"));
      newChild2 = doc.createElement(SA::construct_from_utf8("b"));
      appendedChild = newdocFragment.appendChild(newChild1);
      appendedChild = newdocFragment.appendChild(newChild2);
      insertedNode = employeeNode.insertBefore(newdocFragment, refChild);
      child = childList.item(3);
      childName = child.getNodeName();
      baseT::assertEquals("br", childName, __LINE__, __FILE__);
  child = childList.item(4);
      childName = child.getNodeName();
      baseT::assertEquals("b", childName, __LINE__, __FILE__);
  
   }
  
   /*
    *  Gets URI that identifies the test.
    */
   std::string getTargetURI() const
   {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/hc_nodeinsertbeforedocfragment";
   }
};

#endif
