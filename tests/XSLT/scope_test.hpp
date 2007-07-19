#ifndef MANGLE_SCOPE_TEST_HPP
#define MANGLE_SCOPE_TEST_HPP

using namespace Arabica::XPath;

template<class string_type, class string_adaptor>
class ScopeTest : public TestCase
{
  typedef XPathValuePtr<string_type> ValuePtr;

public:
  ScopeTest(std::string name) : TestCase(name)
  {
  } // ScopeTest

  void test1()
  {
    VariableStack stack;

    assertTrue(dontResolve(stack, "nothing"));
    assertTrue(dontResolve(stack, "charlie"));
  } // test1

  void test2()
  {
    VariableStack stack;

    stack.declareVariable("name", stringValue("value"));
    
    assertTrue(getString(stack, "name", "value"));
    assertTrue(dontResolve(stack, "charlie"));
  } // test2

  void test3()
  {
    VariableStack stack;

    stack.declareVariable("name", stringValue("value"));
    stack.pushScope();
    stack.pushScope();

    assertTrue(getString(stack, "name", "value"));
    assertTrue(dontResolve(stack, "charlie"));

    stack.popScope();

    assertTrue(getString(stack, "name", "value"));
    assertTrue(dontResolve(stack, "charlie"));

    stack.popScope();

    assertTrue(getString(stack, "name", "value"));
  } // test3

  void test4()
  {
    VariableStack stack;

    stack.declareVariable("name", stringValue("value"));
    stack.pushScope();
    stack.declareVariable("charlie", stringValue("charlie"));

    assertTrue(getString(stack, "name", "value"));
    assertTrue(getString(stack, "charlie", "charlie"));

    stack.popScope();

    dontResolve(stack, "charlie");
  } // test4

  void test5()
  {
    VariableStack stack;

    dontResolve(stack, "charlie");

    stack.declareVariable("charlie", stringValue("charlie"));
    assertTrue(getString(stack, "charlie", "charlie"));

    stack.pushScope();
    stack.declareVariable("charlie", stringValue("charli"));
    assertTrue(getString(stack, "charlie", "charli"));

    stack.pushScope();
    stack.declareVariable("charlie", stringValue("charl"));
    assertTrue(getString(stack, "charlie", "charl"));

    stack.popScope();
    assertTrue(getString(stack, "charlie", "charli"));

    stack.popScope();
    assertTrue(getString(stack, "charlie", "charlie"));
  } // test5

private:
  ValuePtr stringValue(const char* val)
  {
    return ValuePtr(new StringValue<string_type, string_adaptor>(val));
  } // stringValue

  bool getString(const VariableStack& stack, const std::string& name, const std::string& value)
  {
    ValuePtr v = stack.resolveVariable(name);
    assertTrue(v->type() == STRING);
    assertTrue(v->asString() == value);
    return true;
  } // getString

  bool dontResolve(const VariableStack& stack, const std::string& name)
  {
    try
    {
      stack.resolveVariable(name);
    }
    catch(Arabica::XPath::UnboundVariableException&)
    {
      return true;
    }
    return false;
  } // dontResolve
}; // class ScopeTest

template<class string_type, class string_adaptor>
TestSuite* ScopeTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ScopeTest<string_type, string_adaptor> >("test1", &ScopeTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<ScopeTest<string_type, string_adaptor> >("test2", &ScopeTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<ScopeTest<string_type, string_adaptor> >("test3", &ScopeTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<ScopeTest<string_type, string_adaptor> >("test4", &ScopeTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<ScopeTest<string_type, string_adaptor> >("test5", &ScopeTest<string_type, string_adaptor>::test5));
 
  return suiteOfTests;
} // ScopeTest_suite

#endif
