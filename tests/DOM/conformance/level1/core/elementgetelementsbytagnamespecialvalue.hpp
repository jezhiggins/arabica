#ifndef test_elementgetelementsbytagnamespecialvalue
#define test_elementgetelementsbytagnamespecialvalue


/*
This C++ source file was generated for Arabica
from the source document contained in the W3C
DOM Conformance Test Suite.
The source document contained the following notice:


Copyright (c) 2001-2004 World Wide Web Consortium,
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
 * The "getElementsByTagName(name)" method may use the
 * special value "*" to match all tags in the element
 * tree.
 * Create a NodeList of all the descendant elements
 * of the last employee by using the special value "*".
 * The method should return all the descendant children(6)
 * in the order the children were encountered.
* @author NIST
* @author Mary Brady
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-1938918D">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-1938918D</a>
*/

template<class string_type, class string_adaptor>
class elementgetelementsbytagnamespecialvalue : public DOMTestCase<string_type, string_adaptor> 
{
    typedef DOMTestCase<string_type, string_adaptor> baseT;
   public: 
     elementgetelementsbytagnamespecialvalue(std::string name) : baseT(name)
     {

       //   check if loaded documents are supported for content type
       const std::string contentType = baseT::getContentType();
    baseT::preload(contentType, "staff", false);
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
      Element lastEmployee;
      NodeList lastempList;
      Node child;
      String childName;
      std::vector<string_type> result;
      
      std::vector<string_type> expectedResult;
      expectedResult.push_back(SA::construct_from_utf8("employeeId"));
      expectedResult.push_back(SA::construct_from_utf8("name"));
      expectedResult.push_back(SA::construct_from_utf8("position"));
      expectedResult.push_back(SA::construct_from_utf8("salary"));
      expectedResult.push_back(SA::construct_from_utf8("gender"));
      expectedResult.push_back(SA::construct_from_utf8("address"));
      
      doc = (Document) baseT::load("staff", false);
      elementList = doc.getElementsByTagName(SA::construct_from_utf8("employee"));
      lastEmployee = (Element) elementList.item(4);
      lastempList = lastEmployee.getElementsByTagName(SA::construct_from_utf8("*"));
      for (unsigned int indexN65642 = 0; indexN65642 != lastempList.getLength(); indexN65642++) {
          child = (Node) lastempList.item(indexN65642);
    childName = child.getNodeName();
      result.push_back(childName);
        }
      baseT::assertEquals(expectedResult, result, __LINE__, __FILE__);
  
   }
  
   /*
    *  Gets URI that identifies the test.
    */
   std::string getTargetURI() const
   {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/elementgetelementsbytagnamespecialvalue";
   }
};

#endif
