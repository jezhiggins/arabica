#ifndef test_documentcreateelementcasesensitive
#define test_documentcreateelementcasesensitive


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
 *     The tagName parameter in the "createElement(tagName)"
 *    method is case-sensitive for XML documents.
 *    Retrieve the entire DOM document and invoke its 
 *    "createElement(tagName)" method twice.  Once for tagName
 *    equal to "address" and once for tagName equal to "ADDRESS"
 *    Each call should create a distinct Element node.  The
 *    newly created Elements are then assigned attributes 
 *    that are retrieved.
* @author NIST
* @author Mary Brady
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-2141741547">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-2141741547</a>
*/

template<class string_type, class string_adaptor>
class documentcreateelementcasesensitive : public DOMTestCase<string_type, string_adaptor> 
{
    typedef DOMTestCase<string_type, string_adaptor> baseT;
   public: 
     documentcreateelementcasesensitive(std::string name) : baseT(name)
     {

       //   check if loaded documents are supported for content type
       const std::string contentType = baseT::getContentType();
    baseT::preload(contentType, "staff", true);
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
      Element newElement1;
      Element newElement2;
      String attribute1;
      String attribute2;
      doc = (Document) baseT::load("staff", true);
      newElement1 = doc.createElement(SA::construct_from_utf8("ADDRESS"));
      newElement2 = doc.createElement(SA::construct_from_utf8("address"));
      newElement1.setAttribute(SA::construct_from_utf8("district"), SA::construct_from_utf8("Fort Worth"));
      newElement2.setAttribute(SA::construct_from_utf8("county"), SA::construct_from_utf8("Dallas"));
      attribute1 = newElement1.getAttribute(SA::construct_from_utf8("district"));
      attribute2 = newElement2.getAttribute(SA::construct_from_utf8("county"));
      baseT::assertEquals("Fort Worth", attribute1, __LINE__, __FILE__);
  baseT::assertEquals("Dallas", attribute2, __LINE__, __FILE__);
  
   }
  
   /*
    *  Gets URI that identifies the test.
    */
   std::string getTargetURI() const
   {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/documentcreateelementcasesensitive";
   }
};

#endif
