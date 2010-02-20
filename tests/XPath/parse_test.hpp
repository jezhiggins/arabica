#ifndef XPATHIC_PARSE_TEST_H
#define XPATHIC_PARSE_TEST_H

#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"
#include <XPath/XPath.hpp>

template<class string_type, class string_adaptor>
class TrueFunctionResolver : public Arabica::XPath::NullFunctionResolver<string_type, string_adaptor>
{
  //typedef string_adaptorstring_adaptor;
public:
  virtual Arabica::XPath::XPathFunction<string_type, string_adaptor>* resolveFunction(
                                         const string_type& namespace_uri,
                                         const string_type& name,
                                         const std::vector<Arabica::XPath::XPathExpression<string_type> >& argExprs) const
  {
    if((namespace_uri == string_adaptor::construct_from_utf8("something")) && 
       (name == string_adaptor::construct_from_utf8("true")))
       return new Arabica::XPath::impl::TrueFn<string_type, string_adaptor>(argExprs);
    return 0;
  } // resolveFunction
}; // class TrueFunctionResolver

template<class string_type, class string_adaptor>
class ParseTest : public TestCase
{
  Arabica::XPath::XPath<string_type> parser;
  typedef string_adaptor SA;

public:
  ParseTest(std::string name) : TestCase(name)
  {
  } // ParseTest

  void setUp()
  {
  } // setUp

  void test1()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("text")));
    assertTrue(parser.compile(SA::construct_from_utf8("comment")));
    assertTrue(parser.compile(SA::construct_from_utf8("text()")));
    assertTrue(parser.compile(SA::construct_from_utf8("text(   )")));
    assertTrue(parser.compile(SA::construct_from_utf8("text()  ")));
    assertTrue(parser.compile(SA::construct_from_utf8("text  (   )")));
    assertTrue(parser.compile(SA::construct_from_utf8("comment()")));
    assertTrue(parser.compile(SA::construct_from_utf8("following-sibling::comment()")));
    assertTrue(parser.compile(SA::construct_from_utf8("descendant::comment()")));
    assertTrue(parser.compile(SA::construct_from_utf8("comment()[1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("comment()[2]")));
    assertTrue(parser.compile(SA::construct_from_utf8("comment()[3]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/following-sibling::comment()")));
    assertTrue(parser.compile(SA::construct_from_utf8("/descendant::comment()")));
    assertTrue(parser.compile(SA::construct_from_utf8("/comment()[1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/comment()[2]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/comment()[3]")));
  }

  void test2()
  {
    Arabica::XPath::StandardNamespaceContext<string_type> nsContext;
    nsContext.addNamespaceDeclaration(SA::construct_from_utf8("something"), SA::construct_from_utf8("a"));
    parser.setNamespaceContext(nsContext);
    assertTrue(parser.compile(SA::construct_from_utf8("a:b")));
    assertTrue(parser.compile(SA::construct_from_utf8("  a:b")));
    assertTrue(parser.compile(SA::construct_from_utf8("a:b  ")));
    assertTrue(parser.compile(SA::construct_from_utf8("   a:b  ")));
    assertTrue(parser.compile(SA::construct_from_utf8("a:*")));
    assertTrue(parser.compile(SA::construct_from_utf8("  a:*")));
    assertTrue(parser.compile(SA::construct_from_utf8("a:*  ")));
    assertTrue(parser.compile(SA::construct_from_utf8("   a:*  ")));
    parser.resetNamespaceContext();
  }

  void test3()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("processing-instruction()")));
    assertTrue(parser.compile(SA::construct_from_utf8("processing-instruction( ) ")));
    assertTrue(parser.compile(SA::construct_from_utf8("processing-instruction('poo')")));
    assertTrue(parser.compile(SA::construct_from_utf8("processing-instruction(\"poo\")")));
    assertTrue(parser.compile(SA::construct_from_utf8("processing-instruction(  \"poo\")")));
    assertTrue(parser.compile(SA::construct_from_utf8("processing-instruction(   \"poo\"    )")));
    assertTrue(parser.compile(SA::construct_from_utf8("processing-instruction  (   \"poo\"    )")));
  }

  void test4()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("self::name")));
    assertTrue(parser.compile(SA::construct_from_utf8("   self::name")));
    assertTrue(parser.compile(SA::construct_from_utf8("self    ::name")));
    assertTrue(parser.compile(SA::construct_from_utf8("self::   name")));
    assertTrue(parser.compile(SA::construct_from_utf8("   self   ::   name")));
  }

  void test5()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("@fruit")));
    assertTrue(parser.compile(SA::construct_from_utf8("  @fruit")));
    assertTrue(parser.compile(SA::construct_from_utf8("@  fruit")));
    assertTrue(parser.compile(SA::construct_from_utf8("    @   fruit")));
  }

  void test6()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/@fruit")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/@fruit[1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/descendant-or-self::woot[1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two[1]/three")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/comment()")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/text()")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/processing-instruction()")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/node()")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/*")));

    Arabica::XPath::StandardNamespaceContext<string_type> nsContext;
    nsContext.addNamespaceDeclaration(SA::construct_from_utf8("urn:I:made:this:up"), SA::construct_from_utf8("ns"));
    parser.setNamespaceContext(nsContext);
    assertTrue(parser.compile(SA::construct_from_utf8("one/ns:*")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/ns:two")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/processing-instruction('parp')")));
  }

  void test7()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("/")));
    assertTrue(parser.compile(SA::construct_from_utf8("/one")));
    assertTrue(parser.compile(SA::construct_from_utf8("/one/two")));
    assertTrue(parser.compile(SA::construct_from_utf8("/one[1]/two[2]/comment()")));
    assertTrue(parser.compile(SA::construct_from_utf8("/one[1]/two[2][1]")));
  }

  void test8()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("//one")));
    assertTrue(parser.compile(SA::construct_from_utf8("//one/two")));
    assertTrue(parser.compile(SA::construct_from_utf8("//one/two//@id")));
    assertTrue(parser.compile(SA::construct_from_utf8("//*[@id]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one//two")));
  }

  void test9()
  {
    assertTrue(parser.compile(SA::construct_from_utf8(".")));
    assertTrue(parser.compile(SA::construct_from_utf8("./something")));
    assertTrue(parser.compile(SA::construct_from_utf8("./something/else")));
    assertTrue(parser.compile(SA::construct_from_utf8("./something/./else")));
    assertTrue(parser.compile(SA::construct_from_utf8("..")));
    assertTrue(parser.compile(SA::construct_from_utf8("../something")));
    assertTrue(parser.compile(SA::construct_from_utf8("../../something")));
    assertTrue(parser.compile(SA::construct_from_utf8("../../something/../text()")));
  }

  void test10()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("/one/*")));
  }

  void test11()
  {
    Arabica::XPath::StandardNamespaceContext<string_type> nsContext;
    nsContext.addNamespaceDeclaration(SA::construct_from_utf8("something"), SA::construct_from_utf8("ns"));
    parser.setNamespaceContext(nsContext);

    assertTrue(parser.compile(SA::construct_from_utf8("/ns:one")));
    assertTrue(parser.compile(SA::construct_from_utf8("//one/ns:two")));
    assertTrue(parser.compile(SA::construct_from_utf8("//ns:one/ns:two//@id")));
    assertTrue(parser.compile(SA::construct_from_utf8("//one/ns:*")));

    parser.resetNamespaceContext();
  }

  void test12()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[@attr]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[@attr][1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[four/@attr]")));
  }

  void test13()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[four|@attr]")));
  }

  void test14()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[-($a)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[--($a)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[-$a|$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[2*-$a|$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[2mod-$a|$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[-(@two)=-1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[-(@two) =-1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[ -(@two)=-1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[-(@two) = -1]")));
  }

  void test15()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[four]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[  four]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[four  ]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[   four  ]")));
  }

  void test16()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[/four]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[/four/five]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[/four/five[1]]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[/four/five[@id][1]]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[/four/five[1]/six]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[/four/five[1]/six[@id][1]]")));
  }

  void test17()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[@attr1='nob']")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a=$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a!=$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a=$b=$c]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[child = true()]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[child = 1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[child = '1']")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[1]/trousers")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@* = @two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@*]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[*]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[charlie[one]]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[/one]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[charlie[/one]]")));

    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@* = child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[//root/child/@two = @*]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[/root/child/@two = @*]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@*=//root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@* =//root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@* = //root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@*= //root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@*=/root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@* =/root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@* = /root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@*= /root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("root/*[@*=root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("root/*[@* =root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("root/*[@* = root/child/@two]")));
    assertTrue(parser.compile(SA::construct_from_utf8("root/*[@*= root/child/@two]")));

    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a<$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a <$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a<   $b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a  <$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a>$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a >$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a> $b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a > $b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a<$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a>=$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a<=$b]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a>$b>$c]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a>$b<$c]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$a=$b<$c]")));

    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[($a>$b)or($b>$c)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[($a>$b)and($b>$c)]")));

    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@* = string('woo')]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[@* = string(//root/child/@two)]")));
    assertTrue(parser.compile_expr(SA::construct_from_utf8("$fruit/*[2]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root[$fruit/root = @*]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[$fruit/root/child/@two = @*]")));
    assertTrue(parser.compile(SA::construct_from_utf8("/root/*[$fruit/root/child/@two = $fruit/root/child/@two]")));
  }

  void test18()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[last()]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[comment()]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[string($a)]")));

    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$var]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[position()=1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(@attr)or(@id)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$var=1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[contains($a,string($b))]")));
  }

  void test18a()
  {
    try {
      parser.compile(SA::construct_from_utf8("one/two/three[string($a,$b)]"));
      assert(false);
    }
    catch(std::exception&) { 
      // we expect this to throw
    }
  } // test18a

  void test19()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1+1)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1-1)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1+1-1)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1+1+1)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1+1+1+1)]")));

    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1*1)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1*1*1)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1*1*1*1)]")));

    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(6div2)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(5mod4)]")));

    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(2*2)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one[1 + 2 * 3]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one[3 * 2 + 1]")));
  }

  void test20()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1.1)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(1.)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[.1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[  .1  ]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(12)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(123.456)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(.123456)]")));
  }

  void test21()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$var]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three    [$var]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$var]   ")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$var] /four")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$var ]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$var    ]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[ $var]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[  $var]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[   $var   ]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[$var = 1]")));
  }

  void test22()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[position() = 1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[position(  ) = 1]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[(@attr) or (@id)]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[@attr or @id]")));
    try {
      parser.compile(SA::construct_from_utf8("one/two/three[string($a, $b)]"));
      assert(false);
    }
    catch(...) { }
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[contains($a, string($b))]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[contains(    $a, string($b))]")));
    assertTrue(parser.compile(SA::construct_from_utf8("one/two/three[contains    ($a, string($b)   )]")));
  } // test22

  void test23()
  {
    assertTrue(parser.compile(SA::construct_from_utf8("/root[count(something)]")));
    try {
      parser.compile(SA::construct_from_utf8("/root[count()]"));
      assert(false);
    }
    catch(...) { }
    try {
      parser.compile(SA::construct_from_utf8("/root[count(one, two)]"));
      assert(false);
    }
    catch(...) { }
    try {
      parser.compile(SA::construct_from_utf8("/root[count(one,two)]"));
      assert(false);
    }
    catch(...) { }
    try {
      parser.compile(SA::construct_from_utf8("/root/count(one,two)"));
      assert(false);
    }
    catch(...) { }
  } // test23

  void test24()
  {
    assertTrue(parser.compile_expr(SA::construct_from_utf8("true()")));
    assertTrue(parser.compile_expr(SA::construct_from_utf8("$one")));
  } // test24

  void test25()
  {
    Arabica::XPath::StandardNamespaceContext<string_type> nsContext;
    nsContext.addNamespaceDeclaration(SA::construct_from_utf8("something"), SA::construct_from_utf8("p"));
    parser.setNamespaceContext(nsContext);
    TrueFunctionResolver<string_type, string_adaptor> tfr;
    parser.setFunctionResolver(tfr);

    assertTrue(parser.compile_expr(SA::construct_from_utf8("$p:one")));
    assertTrue(parser.compile_expr(SA::construct_from_utf8("p:true()")));

    parser.resetNamespaceContext();
    parser.resetFunctionResolver();
    try {
      parser.compile_expr(SA::construct_from_utf8("$p:one"));
      assert(false);
    }
    catch(...) { }
    try {
      parser.compile_expr(SA::construct_from_utf8("$p:true()"));
      assert(false);
    }
    catch(...) { }
  } // test25
}; // class ParseTest

template<class string_type, class string_adaptor>
TestSuite* ParseTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test1", &ParseTest<string_type, string_adaptor>::test1));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test2", &ParseTest<string_type, string_adaptor>::test2));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test3", &ParseTest<string_type, string_adaptor>::test3));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test4", &ParseTest<string_type, string_adaptor>::test4));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test5", &ParseTest<string_type, string_adaptor>::test5));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test6", &ParseTest<string_type, string_adaptor>::test6));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test7", &ParseTest<string_type, string_adaptor>::test7));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test8", &ParseTest<string_type, string_adaptor>::test8));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test9", &ParseTest<string_type, string_adaptor>::test9));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test10", &ParseTest<string_type, string_adaptor>::test10));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test11", &ParseTest<string_type, string_adaptor>::test11));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test12", &ParseTest<string_type, string_adaptor>::test12));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test13", &ParseTest<string_type, string_adaptor>::test13));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test14", &ParseTest<string_type, string_adaptor>::test14));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test15", &ParseTest<string_type, string_adaptor>::test15));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test16", &ParseTest<string_type, string_adaptor>::test16));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test17", &ParseTest<string_type, string_adaptor>::test17));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test18", &ParseTest<string_type, string_adaptor>::test18));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test18a", &ParseTest<string_type, string_adaptor>::test18a));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test19", &ParseTest<string_type, string_adaptor>::test19));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test20", &ParseTest<string_type, string_adaptor>::test20));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test21", &ParseTest<string_type, string_adaptor>::test21));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test22", &ParseTest<string_type, string_adaptor>::test22));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test23", &ParseTest<string_type, string_adaptor>::test23));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test24", &ParseTest<string_type, string_adaptor>::test24));
  suiteOfTests->addTest(new TestCaller<ParseTest<string_type, string_adaptor> >("test25", &ParseTest<string_type, string_adaptor>::test25));

  return suiteOfTests;
} // ParseTest_suite

#endif

