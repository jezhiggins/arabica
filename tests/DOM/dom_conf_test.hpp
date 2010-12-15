#ifndef ARABICA_DOM_CONF_TEST_HPP
#define ARABICA_DOM_CONF_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>


#ifdef ARABICA_WINDOWS
const std::string PATH_PREFIX="../tests/DOM/conformance/files/";
#else
#include "test_path.hpp"
const std::string PATH_PREFIX=test_path;
#endif

template<class string_type, class string_adaptor>
class DOMTestCase : public TestCase 
{
public:
  typedef typename Arabica::DOM::Document<string_type, string_adaptor> Document;
  typedef typename Arabica::DOM::Node<string_type, string_adaptor> Node;
  typedef typename Arabica::DOM::NodeList<string_type, string_adaptor> NodeList;
  typedef typename Arabica::DOM::NamedNodeMap<string_type, string_adaptor> NamedNodeMap;

  typedef string_adaptor SA;

  DOMTestCase(std::string name) : TestCase(name)
  {
  } // DOMTestCase
  
  virtual void runTest() = 0;
  virtual std::string getTargetURI() const = 0;
  
protected:

  std::string getContentType() const
  {
    return "";
  } // getContentType
  
  void preload(const std::string& /*contentType*/, const std::string& /*docURI*/, bool /*willBeModified*/) const
  {
  } // preload

  template<class T>
  bool equals(const T& lhs, const T& rhs) const { return lhs == rhs; }
  
  Document load(const std::string& docURI, bool /*willBeModified*/) 
  {
    std::string filename = PATH_PREFIX + docURI + ".xml";
    
    Arabica::SAX::InputSource<string_type, string_adaptor> is(SA::construct_from_utf8(filename.c_str()));
    Arabica::SAX2DOM::Parser<string_type, string_adaptor> parser;
    parser.parse(is);       
    
    Document d = parser.getDocument();
    if(d == 0)
      assertImplementation(false, "Could not load", -1, filename);
    
    //d.normalize();
    return d;
  } // load
  
  void assertEquals(int expected, int actual, int lineNo, const char* fileName)
  {
    TestCase::assertEquals((long)expected, (long)actual, lineNo, fileName);
  } // assertEquals
  void assertEquals(const char* expected, const string_type& actual, int lineNo, const char* fileName)
  {
    if(SA::construct_from_utf8(expected) != actual)
      assertImplementation (false, notEqualsMessage(expected, SA::asStdString(actual)), lineNo, fileName);
  } // assertEquals
  void assertEquals(const string_type& expected, const string_type& actual, int lineNo, const char* fileName)
  {
    if(expected != actual)
      assertImplementation (false, notEqualsMessage(SA::asStdString(expected), SA::asStdString(actual)), lineNo, fileName);
  } // assertEquals
  void assertEquals(const std::vector<string_type>& expected, const std::vector<string_type>& actual, int lineNo, const char* fileName)
  {
    std::string e = serialise_vector(expected);
    std::string a = serialise_vector(actual);
    if(e != a)
      assertImplementation (false, notEqualsMessage(e, a), lineNo, fileName);
  } // assertEquals
  void assertSame(const Node& lhs, const Node& rhs, int lineNo, const char* fileName)
  {
    if(lhs != rhs)
      assertImplementation(false, "Nodes should be the same", lineNo, fileName); 
  } // assertSame
  
  void assertSize(int size, const NodeList& l, int lineNo, const char* fileName) 
  { 
    assertEquals(size, l.getLength(), lineNo, fileName); 
  } // assertSize
  void assertSize(int size, const NamedNodeMap& l, int lineNo, const char* fileName) 
  { 
    assertEquals(size, l.getLength(), lineNo, fileName); 
  } // assertSize
  
  bool isNull(const string_type& actual) { return SA::empty(actual); } 
  bool isNull(const Node& actual) { return (actual == 0); }
  bool notNull(const string_type& actual) { return !isNull(actual); }
  bool notNull(const Node& actual) { return !isNull(actual); }
  
  void assertNull(const string_type& actual, int lineNo, const char* fileName)
  {
    if(!SA::empty(actual))
      assertImplementation(false, "String should be empty", lineNo, fileName);
  } // assertNull
  void assertNull(const Node& actual, int lineNo, const char* fileName)
  {
    if(actual != 0)
      assertImplementation(false, "Node should be null", lineNo, fileName);
  } // assertNull
  void assertNull(const NamedNodeMap& actual, int lineNo, const char* fileName)
  {
    if(actual != 0)
      assertImplementation(false, "NamedNodeMap should be empty", lineNo, fileName);
  } // assertNotNull
  void assertNotNull(const Node& actual, int lineNo, const char* fileName)
  {
    if(actual == 0)
      assertImplementation(false, "Node should not be null", lineNo, fileName);
  } // assertNull
  void assertNotNull(const NamedNodeMap& actual, int lineNo, const char* fileName)
  {
    if(actual == 0)
      assertImplementation(false, "NamedNodeMap should not be empty", lineNo, fileName);
  } // assertNotNull
  void skipIfNull(const Node& actual)
  {
    if(actual == 0)
      throw SkipException(getTargetURI());
  } // skipIfNull
  template<typename T>
  void skipIfNot(const Node& actual)
  {
     bool ok = false;
     try {
       T t = (T)actual;
       ok = true;
     }
     catch(const std::bad_cast&) {
     }
     if(!ok)
       throw SkipException(getTargetURI());
  } // skipIfNot
  void assertURIEquals(const char* /*dummy*/, 
                       const char* /*scheme*/, 
                       const char* /*path*/, 
                       const char* /*host*/, 
                       const char* /*file*/, 
                       const char* /*name*/, 
                       const char* /*query*/, 
                       const char* /*fragment*/, 
                       bool /*isAbsolute*/, 
                       const string_type& /*actual*/)
  {
    assertImplementation(false, "Haven't implemented assertURIEquals yet", -1, getTargetURI());
  } // assertURIEquals

  bool equals(const char* expected, const string_type& actual)
  {
    return (SA::construct_from_utf8(expected) == actual);
  } // equals
  
  void fail(const char* msg, int lineNo, const char* fileName)
  {
    assertImplementation(false, msg, lineNo, fileName);
  } // fail
  
private:
  std::string serialise_vector(std::vector<string_type> v)
  {
    std::sort(v.begin(), v.end());
    std::string s;
    typedef typename std::vector<string_type>::const_iterator const_iterator;
    for(const_iterator a = v.begin(), e = v.end(); a != e; ++a)
      s += SA::asStdString(*a);
    return s;
  } // serialise_vector
};

#endif
