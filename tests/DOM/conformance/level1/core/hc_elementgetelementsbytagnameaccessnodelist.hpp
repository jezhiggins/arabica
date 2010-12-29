#ifndef test_hc_elementgetelementsbytagnameaccessnodelist
#define test_hc_elementgetelementsbytagnameaccessnodelist


/*
This C++ source file was generated for Arabica
from the source document contained in the W3C
DOM Conformance Test Suite.
The source document contained the following notice:


Copyright (c) 2001 World Wide Web Consortium,
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
 * The "getElementsByTagName(name)" method returns a list
 * of all descendant Elements in the order the children
 * were encountered in a pre order traversal of the element
 * tree.
 * Create a NodeList of all the descendant elements
 * using the string "p" as the tagName.
 * The method should return a NodeList whose length is
 * "5" in the order the children were encountered.
 * Access the FOURTH element in the NodeList.  The FOURTH
 * element, the first or second should be an "em" node with
 * the content "EMP0004".
* @author Curt Arnold
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-1938918D">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-1938918D</a>
* @see <a href="http://www.w3.org/Bugs/Public/show_bug.cgi?id=246">http://www.w3.org/Bugs/Public/show_bug.cgi?id=246</a>
*/

template<class string_type, class string_adaptor>
class hc_elementgetelementsbytagnameaccessnodelist : public DOMTestCase<string_type, string_adaptor> 
{
    typedef DOMTestCase<string_type, string_adaptor> baseT;
   public: 
     hc_elementgetelementsbytagnameaccessnodelist(std::string name) : baseT(name)
     {

       //   check if loaded documents are supported for content type
       const std::string contentType = baseT::getContentType();
    baseT::preload(contentType, "hc_staff", false);
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
      Element testEmployee;
      Node firstC;
      String childName;
      int nodeType;
      CharacterData employeeIDNode;
      String employeeID;
      doc = (Document) baseT::load("hc_staff", false);
      elementList = doc.getElementsByTagName(SA::construct_from_utf8("p"));
      testEmployee = (Element) elementList.item(3);
      firstC = testEmployee.getFirstChild();
      nodeType = (int) firstC.getNodeType();
      
    while (baseT::equals(3, nodeType)) {
    firstC = firstC.getNextSibling();
      nodeType = (int) firstC.getNodeType();
      
    }
childName = firstC.getNodeName();
      baseT::assertEquals("em", childName, __LINE__, __FILE__);
  employeeIDNode = (CharacterData) firstC.getFirstChild();
      employeeID = employeeIDNode.getNodeValue();
      baseT::assertEquals("EMP0004", employeeID, __LINE__, __FILE__);
  
   }
  
   /*
    *  Gets URI that identifies the test.
    */
   std::string getTargetURI() const
   {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/hc_elementgetelementsbytagnameaccessnodelist";
   }
};

#endif
