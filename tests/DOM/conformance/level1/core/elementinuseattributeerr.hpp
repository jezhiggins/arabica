#ifndef test_elementinuseattributeerr
#define test_elementinuseattributeerr


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
 *     The "setAttributeNode(newAttr)" method raises an 
 *    "INUSE_ATTRIBUTE_ERR DOMException if the "newAttr" 
 *    is already an attribute of another element.
 *    
 *    Retrieve the last child of the second employee and append
 *    a newly created element.  The "createAttribute(name)"
 *    and "setAttributeNode(newAttr)" methods are invoked
 *    to create and add a new attribute to the newly created
 *    Element.  The "setAttributeNode(newAttr)" method is
 *    once again called to add the new attribute causing an
 *    exception to be raised since the attribute is already
 *    an attribute of another element.
* @author NIST
* @author Mary Brady
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#xpointer(id('ID-258A00AF')/constant[@name='INUSE_ATTRIBUTE_ERR'])">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#xpointer(id('ID-258A00AF')/constant[@name='INUSE_ATTRIBUTE_ERR'])</a>
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-887236154">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-887236154</a>
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#xpointer(id('ID-887236154')/raises/exception[@name='DOMException']/descr/p[substring-before(.,':')='INUSE_ATTRIBUTE_ERR'])">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#xpointer(id('ID-887236154')/raises/exception[@name='DOMException']/descr/p[substring-before(.,':')='INUSE_ATTRIBUTE_ERR'])</a>
*/

template<class string_type, class string_adaptor>
class elementinuseattributeerr : public DOMTestCase<string_type, string_adaptor> 
{
    typedef DOMTestCase<string_type, string_adaptor> baseT;
   public: 
     elementinuseattributeerr(std::string name) : baseT(name)
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
      Attr newAttribute;
      NodeList addressElementList;
      Element testAddress;
      Element newElement;
      Node appendedChild;
      Attr setAttr1;
      Attr setAttr2;
      doc = (Document) baseT::load("staff", true);
      addressElementList = doc.getElementsByTagName(SA::construct_from_utf8("address"));
      testAddress = (Element) addressElementList.item(1);
      newElement = doc.createElement(SA::construct_from_utf8("newElement"));
      appendedChild = testAddress.appendChild(newElement);
      newAttribute = doc.createAttribute(SA::construct_from_utf8("newAttribute"));
      setAttr1 = newElement.setAttributeNode(newAttribute);
      
      {
         boolean success = false;
         try {
            setAttr2 = testAddress.setAttributeNode(newAttribute);
          } catch (const DOMException& ex) {
            success = (ex.code() == DOMException::INUSE_ATTRIBUTE_ERR);
         }
         assertTrue(success);
      }

   }
  
   /*
    *  Gets URI that identifies the test.
    */
   std::string getTargetURI() const
   {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/elementinuseattributeerr";
   }
};

#endif
