#ifndef ARABICA_DOM_CONF_TEST_HPP
#define ARABICA_DOM_CONF_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <DOM/Simple/DOMImplementation.hpp>

template<class string_type, class string_adaptor>
class DOMTestCase : public TestCase 
{
public:
    typedef typename Arabica::DOM::DOMImplementation<string_type, string_adaptor> DOMImplementation;
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

	void preload(const std::string& contentType, const std::string& docURI, bool willBeModified) const
	{
	} // preload

	template<class T>
	bool equals(const T& lhs, const T& rhs) const { return lhs == rhs; }

	Document load(const std::string& docURI, bool willBeModified) 
	{
	  std::string filename = "c:\\work\\DOM-Test-Suite\\tests\\level1\\core\\files\\" + docURI + ".xml";

	  Arabica::SAX::InputSource<string_type, string_adaptor> is(SA::construct_from_utf8(filename.c_str()));
   	  Arabica::SAX2DOM::Parser<string_type, string_adaptor> parser;
      parser.parse(is);       

      Document d = parser.getDocument();
      if(d == 0)
		  assertImplementation(false, "Could not load", -1, filename);

	  d.normalize();
      return d;
	} // load

	void assertEquals(int expected, int actual)
	{
		TestCase::assertEquals((long)expected, (long)actual, -1, getTargetURI());
	} // assertEquals
	void assertEquals(const char* expected, const string_type& actual)
	{
		if(SA::construct_from_utf8(expected) != actual)
			assertImplementation (false, notEqualsMessage(expected, SA::asStdString(actual)), -1, getTargetURI()); 
	} // assertEquals
	void assertEquals(const string_type& expected, const string_type& actual)
	{
		if(expected != actual)
			assertImplementation (false, notEqualsMessage(SA::asStdString(expected), SA::asStdString(actual)), -1, getTargetURI()); 
	} // assertEquals
	void assertEquals(const std::vector<string_type>& expected, const std::vector<string_type>& actual)
	{
		std::string e = serialise_vector(expected);
		std::string a = serialise_vector(actual);
		if(e != a)
			assertImplementation (false, notEqualsMessage(e, a), -1, getTargetURI()); 
	} // assertEquals
	void assertSame(const Node& lhs, const Node& rhs)
	{
		if(lhs != rhs)
			assertImplementation(false, "Nodes should be the same", -1, getTargetURI()); 
	} // assertSame

	void assertSize(int size, const NodeList& l) { assertEquals(size, l.getLength()); }
	void assertSize(int size, const NamedNodeMap& l) { assertEquals(size, l.getLength()); }

	bool isNull(const string_type& actual) { return SA::empty(actual); } 
	bool isNull(const Node& actual) { return (actual == 0); }
	bool notNull(const string_type& actual) { return !isNull(actual); }
	bool notNull(const Node& actual) { return !isNull(actual); }

	void assertNull(const string_type& actual)
	{
		if(!SA::empty(actual))
			assertImplementation(false, "String should be empty", -1, getTargetURI());
	} // assertNull
	void assertNull(const Node& actual)
	{
		if(actual != 0)
			assertImplementation(false, "Node should be null", -1, getTargetURI());
	} // assertNull
	void assertNull(const NamedNodeMap& actual)
	{
		if(actual != 0)
			assertImplementation(false, "NamedNodeMap should be empty", -1, getTargetURI());
	} // assertNotNull
	void assertNotNull(const Node& actual)
	{
		if(actual == 0)
			assertImplementation(false, "Node should not be null", -1, getTargetURI());
	} // assertNull
	void assertNotNull(const NamedNodeMap& actual)
	{
		if(actual == 0)
			assertImplementation(false, "NamedNodeMap should not be empty", -1, getTargetURI());
	} // assertNotNull
	void skipIfNull(const Node& actual)
	{
		if(actual == 0)
			throw SkipException(getTargetURI());
	} // skipIfNull
  
  void assertURIEquals(const char* dummy, 
                       const char* scheme, 
                       const char* path, 
                       const char* host, 
                       const char* file, 
                       const char* name, 
                       const char* query, 
                       const char* fragment, 
                       bool isAbsolute, 
                       const string_type& actual)
  {
    assertImplementation(false, "Haven't implemented assertURIEquals yet", -1, getTargetURI());
  } // assertURIEquals

	bool equals(const char* expected, const string_type& actual)
	{
      return (SA::construct_from_utf8(expected) != actual);
	} // equals

	void fail(const char* msg)
	{
		assertImplementation(false, msg, -1, getTargetURI());
	} // fail

private:
	std::string serialise_vector(const std::vector<string_type>& v)
	{
		std::string s;
		for(std::vector<string_type>::const_iterator a = v.begin(), e = v.end(); a != e; ++a)
			s += SA::asStdString(*a);
		return s;
	} // serialise_vector
};

#endif