#ifndef test_hc_documentgetelementsbytagnametotallength
#define test_hc_documentgetelementsbytagnametotallength


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
 *    Retrieve the entire DOM document and invoke its 
 *    "getElementsByTagName(tagName)" method with tagName
 *    equal to "*".  The method should return a NodeList 
 *    that contains all the elements of the document. 
* @author Curt Arnold
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-A6C9094">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-A6C9094</a>
* @see <a href="http://www.w3.org/Bugs/Public/show_bug.cgi?id=251">http://www.w3.org/Bugs/Public/show_bug.cgi?id=251</a>
*/

template<class string_type, class string_adaptor>
class hc_documentgetelementsbytagnametotallength : public DOMTestCase<string_type, string_adaptor> 
{
    typedef DOMTestCase<string_type, string_adaptor> baseT;
   public: 
     hc_documentgetelementsbytagnametotallength(std::string name) : baseT(name)
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
      NodeList nameList;
      std::vector<string_type> expectedNames;
      expectedNames.push_back(SA::construct_from_utf8("html"));
      expectedNames.push_back(SA::construct_from_utf8("head"));
      expectedNames.push_back(SA::construct_from_utf8("meta"));
      expectedNames.push_back(SA::construct_from_utf8("title"));
      expectedNames.push_back(SA::construct_from_utf8("script"));
      expectedNames.push_back(SA::construct_from_utf8("script"));
      expectedNames.push_back(SA::construct_from_utf8("script"));
      expectedNames.push_back(SA::construct_from_utf8("body"));
      expectedNames.push_back(SA::construct_from_utf8("p"));
      expectedNames.push_back(SA::construct_from_utf8("em"));
      expectedNames.push_back(SA::construct_from_utf8("strong"));
      expectedNames.push_back(SA::construct_from_utf8("code"));
      expectedNames.push_back(SA::construct_from_utf8("sup"));
      expectedNames.push_back(SA::construct_from_utf8("var"));
      expectedNames.push_back(SA::construct_from_utf8("acronym"));
      expectedNames.push_back(SA::construct_from_utf8("p"));
      expectedNames.push_back(SA::construct_from_utf8("em"));
      expectedNames.push_back(SA::construct_from_utf8("strong"));
      expectedNames.push_back(SA::construct_from_utf8("code"));
      expectedNames.push_back(SA::construct_from_utf8("sup"));
      expectedNames.push_back(SA::construct_from_utf8("var"));
      expectedNames.push_back(SA::construct_from_utf8("acronym"));
      expectedNames.push_back(SA::construct_from_utf8("p"));
      expectedNames.push_back(SA::construct_from_utf8("em"));
      expectedNames.push_back(SA::construct_from_utf8("strong"));
      expectedNames.push_back(SA::construct_from_utf8("code"));
      expectedNames.push_back(SA::construct_from_utf8("sup"));
      expectedNames.push_back(SA::construct_from_utf8("var"));
      expectedNames.push_back(SA::construct_from_utf8("acronym"));
      expectedNames.push_back(SA::construct_from_utf8("p"));
      expectedNames.push_back(SA::construct_from_utf8("em"));
      expectedNames.push_back(SA::construct_from_utf8("strong"));
      expectedNames.push_back(SA::construct_from_utf8("code"));
      expectedNames.push_back(SA::construct_from_utf8("sup"));
      expectedNames.push_back(SA::construct_from_utf8("var"));
      expectedNames.push_back(SA::construct_from_utf8("acronym"));
      expectedNames.push_back(SA::construct_from_utf8("p"));
      expectedNames.push_back(SA::construct_from_utf8("em"));
      expectedNames.push_back(SA::construct_from_utf8("strong"));
      expectedNames.push_back(SA::construct_from_utf8("code"));
      expectedNames.push_back(SA::construct_from_utf8("sup"));
      expectedNames.push_back(SA::construct_from_utf8("var"));
      expectedNames.push_back(SA::construct_from_utf8("acronym"));
      
      std::vector<string_type> svgExpectedNames;
      svgExpectedNames.push_back(SA::construct_from_utf8("svg"));
      svgExpectedNames.push_back(SA::construct_from_utf8("rect"));
      svgExpectedNames.push_back(SA::construct_from_utf8("script"));
      svgExpectedNames.push_back(SA::construct_from_utf8("head"));
      svgExpectedNames.push_back(SA::construct_from_utf8("meta"));
      svgExpectedNames.push_back(SA::construct_from_utf8("title"));
      svgExpectedNames.push_back(SA::construct_from_utf8("body"));
      svgExpectedNames.push_back(SA::construct_from_utf8("p"));
      svgExpectedNames.push_back(SA::construct_from_utf8("em"));
      svgExpectedNames.push_back(SA::construct_from_utf8("strong"));
      svgExpectedNames.push_back(SA::construct_from_utf8("code"));
      svgExpectedNames.push_back(SA::construct_from_utf8("sup"));
      svgExpectedNames.push_back(SA::construct_from_utf8("var"));
      svgExpectedNames.push_back(SA::construct_from_utf8("acronym"));
      svgExpectedNames.push_back(SA::construct_from_utf8("p"));
      svgExpectedNames.push_back(SA::construct_from_utf8("em"));
      svgExpectedNames.push_back(SA::construct_from_utf8("strong"));
      svgExpectedNames.push_back(SA::construct_from_utf8("code"));
      svgExpectedNames.push_back(SA::construct_from_utf8("sup"));
      svgExpectedNames.push_back(SA::construct_from_utf8("var"));
      svgExpectedNames.push_back(SA::construct_from_utf8("acronym"));
      svgExpectedNames.push_back(SA::construct_from_utf8("p"));
      svgExpectedNames.push_back(SA::construct_from_utf8("em"));
      svgExpectedNames.push_back(SA::construct_from_utf8("strong"));
      svgExpectedNames.push_back(SA::construct_from_utf8("code"));
      svgExpectedNames.push_back(SA::construct_from_utf8("sup"));
      svgExpectedNames.push_back(SA::construct_from_utf8("var"));
      svgExpectedNames.push_back(SA::construct_from_utf8("acronym"));
      svgExpectedNames.push_back(SA::construct_from_utf8("p"));
      svgExpectedNames.push_back(SA::construct_from_utf8("em"));
      svgExpectedNames.push_back(SA::construct_from_utf8("strong"));
      svgExpectedNames.push_back(SA::construct_from_utf8("code"));
      svgExpectedNames.push_back(SA::construct_from_utf8("sup"));
      svgExpectedNames.push_back(SA::construct_from_utf8("var"));
      svgExpectedNames.push_back(SA::construct_from_utf8("acronym"));
      svgExpectedNames.push_back(SA::construct_from_utf8("p"));
      svgExpectedNames.push_back(SA::construct_from_utf8("em"));
      svgExpectedNames.push_back(SA::construct_from_utf8("strong"));
      svgExpectedNames.push_back(SA::construct_from_utf8("code"));
      svgExpectedNames.push_back(SA::construct_from_utf8("sup"));
      svgExpectedNames.push_back(SA::construct_from_utf8("var"));
      svgExpectedNames.push_back(SA::construct_from_utf8("acronym"));
      
      std::vector<string_type> actualNames;
      
      Element thisElement;
      String thisTag;
      doc = (Document) baseT::load("hc_staff", false);
      nameList = doc.getElementsByTagName(SA::construct_from_utf8("*"));
      for (unsigned int indexN65864 = 0; indexN65864 != nameList.getLength(); indexN65864++) {
          thisElement = (Element) nameList.item(indexN65864);
    thisTag = thisElement.getTagName();
      actualNames.push_back(thisTag);
        }
      
      if (("image/svg+xml" == baseT::getContentType())) {
          baseT::assertEquals(svgExpectedNames, actualNames, __LINE__, __FILE__);
  } else {
          baseT::assertEquals(expectedNames, actualNames, __LINE__, __FILE__);
  }
        
    
   }
  
   /*
    *  Gets URI that identifies the test.
    */
   std::string getTargetURI() const
   {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/hc_documentgetelementsbytagnametotallength";
   }
};

#endif
