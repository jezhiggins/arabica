#ifndef XPATHIC_ATTRIBUTE_VALUE_TEST_HPP
#define XPATHIC_ATTRIBUTE_VALUE_TEST_HPP

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"

#include <XPath/XPath.hpp>

template<class string_type, class string_adaptor>
class AttributeValueTest : public TestCase
{
  Arabica::XPath::XPath<string_type, string_adaptor> parser;
  typedef string_adaptor SA;

public:
  AttributeValueTest(std::string name) : TestCase(name)
  {
  } // AttributeValueTest

  void setUp()
  {
  } // setUp

  void testParse()
  {
    Arabica::DOM::Node<string_type, string_adaptor> dummy;
    assertTrue(SA::construct_from_utf8("hello") == compileThis("hello").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("") == compileThis("{hello}").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("{hello}") == compileThis("{{hello}}").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("{hello}") == compileThis("{{{'hello'}}}").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("{}") == compileThis("{{{hello}}}").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("{") == compileThis("{{").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("}") == compileThis("}}").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("hello") == compileThis("hello{@there}").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("helloMOTHER{}") == compileThis("hello{@there}MOTHER{{}}").evaluateAsString(dummy));
    assertTrue(SA::construct_from_utf8("hello there everyone look a }") == compileThis("hello {string('there')} everyone {string('look a }')}").evaluateAsString(dummy));
  } // testParse

  void testParseFail()
  {
    assertTrue(dontCompileThis(""));
    assertTrue(dontCompileThis("{"));
    assertTrue(dontCompileThis("}"));
    assertTrue(dontCompileThis("{}}"));
    assertTrue(dontCompileThis("{{}"));
    assertTrue(dontCompileThis("{{{{{{{}"));
    assertTrue(dontCompileThis("{}"));
  } // testParseFail


  bool dontCompileThis(const char* path)
  {
    try {
      compileThis(path);
      return false;
    }
    catch(const Arabica::XPath::SyntaxException&) {
    }
    return true;
  } // dontCompileThis

  Arabica::XPath::XPathExpression<string_type, string_adaptor> compileThis(const char* match)
  {
    //std::cout << "----\n" << match << std::endl;
    return parser.compile_attribute_value_template(SA::construct_from_utf8(match));
  } // compileMatch
}; // class AttributeValueTest

template<class string_type, class string_adaptor>
TestSuite* AttributeValueTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<AttributeValueTest<string_type, string_adaptor> >("testParse", &AttributeValueTest<string_type, string_adaptor>::testParse));
  suiteOfTests->addTest(new TestCaller<AttributeValueTest<string_type, string_adaptor> >("testParseFail", &AttributeValueTest<string_type, string_adaptor>::testParseFail));
 
  return suiteOfTests;
} // AttributeValueTest_suite

#endif
