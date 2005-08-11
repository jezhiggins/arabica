#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503 4224 4180)
#endif
#include "../CppUnit/framework/TestCase.h"
#include "../CppUnit/framework/TestSuite.h"
#include "../CppUnit/framework/TestCaller.h"
#include <XPath/XPath.hpp>

#include <iostream>

class ParseTest : public TestCase
{
  Arabica::XPath::XPath parser;

public:
  ParseTest(std::string name) : TestCase(name)
  {
  } // ParseTest

  void setUp()
  {
  } // setUp

  void test1()
  {
    assertTrue(parser.compile("text"));
    assertTrue(parser.compile("comment"));
    assertTrue(parser.compile("text()"));
    assertTrue(parser.compile("text(   )"));
    assertTrue(parser.compile("text()  "));
    assertTrue(parser.compile("text  (   )"));
    assertTrue(parser.compile("comment()"));
    assertTrue(parser.compile("following-sibling::comment()"));
    assertTrue(parser.compile("descendant::comment()"));
    assertTrue(parser.compile("comment()[1]"));
    assertTrue(parser.compile("comment()[2]"));
    assertTrue(parser.compile("comment()[3]"));
    assertTrue(parser.compile("/following-sibling::comment()"));
    assertTrue(parser.compile("/descendant::comment()"));
    assertTrue(parser.compile("/comment()[1]"));
    assertTrue(parser.compile("/comment()[2]"));
    assertTrue(parser.compile("/comment()[3]"));
  }

  void test2()
  {
    Arabica::XPath::StandardNamespaceContext nsContext;
    nsContext.addNamespaceDeclaration("something", "a");
    parser.setNamespaceContext(nsContext);
    assertTrue(parser.compile("a:b"));
    assertTrue(parser.compile("  a:b"));
    assertTrue(parser.compile("a:b  "));
    assertTrue(parser.compile("   a:b  "));
    parser.resetNamespaceContext();
  }

  void test3()
  {
    assertTrue(parser.compile("processing-instruction()"));
    assertTrue(parser.compile("processing-instruction( ) "));
    assertTrue(parser.compile("processing-instruction('poo')"));
    assertTrue(parser.compile("processing-instruction(\"poo\")"));
    assertTrue(parser.compile("processing-instruction(  \"poo\")"));
    assertTrue(parser.compile("processing-instruction(   \"poo\"    )"));
    assertTrue(parser.compile("processing-instruction  (   \"poo\"    )"));
  }

  void test4()
  {
    assertTrue(parser.compile("self::name"));
    assertTrue(parser.compile("   self::name"));
    assertTrue(parser.compile("self    ::name"));
    assertTrue(parser.compile("self::   name"));
    assertTrue(parser.compile("   self   ::   name"));
  }

  void test5()
  {
    assertTrue(parser.compile("@fruit"));
    assertTrue(parser.compile("  @fruit"));
    assertTrue(parser.compile("@  fruit"));
    assertTrue(parser.compile("    @   fruit"));
  }

  void test6()
  {
    assertTrue(parser.compile("one/two"));
    assertTrue(parser.compile("one/@fruit"));
    assertTrue(parser.compile("one/@fruit[1]"));
    assertTrue(parser.compile("one/descendant-or-self::woot[1]"));
    assertTrue(parser.compile("one/two/three"));
    assertTrue(parser.compile("one/two/three[1]"));
    assertTrue(parser.compile("one/two[1]/three"));
    assertTrue(parser.compile("one/comment()"));
    assertTrue(parser.compile("one/text()"));
    assertTrue(parser.compile("one/processing-instruction()"));
    assertTrue(parser.compile("one/node()"));
    assertTrue(parser.compile("one/*"));

    Arabica::XPath::StandardNamespaceContext nsContext;
    nsContext.addNamespaceDeclaration("urn:I:made:this:up", "ns");
    parser.setNamespaceContext(nsContext);
    assertTrue(parser.compile("one/ns:*"));
    assertTrue(parser.compile("one/ns:two"));
    assertTrue(parser.compile("one/processing-instruction('parp')"));
  }

  void test7()
  {
    assertTrue(parser.compile("/"));
    assertTrue(parser.compile("/one"));
    assertTrue(parser.compile("/one/two"));
    assertTrue(parser.compile("/one[1]/two[2]/comment()"));
    assertTrue(parser.compile("/one[1]/two[2][1]"));
  }

  void test8()
  {
    assertTrue(parser.compile("//one"));
    assertTrue(parser.compile("//one/two"));
    assertTrue(parser.compile("//one/two//@id"));
    assertTrue(parser.compile("//*[@id]"));
    assertTrue(parser.compile("one//two"));
  }

  void test9()
  {
    assertTrue(parser.compile("."));
    assertTrue(parser.compile("./something"));
    assertTrue(parser.compile("./something/else"));
    assertTrue(parser.compile("./something/./else"));
    assertTrue(parser.compile(".."));
    assertTrue(parser.compile("../something"));
    assertTrue(parser.compile("../../something"));
    assertTrue(parser.compile("../../something/../text()"));
  }

  void test10()
  {
    assertTrue(parser.compile("/one/*"));
  }

  void test11()
  {
    Arabica::XPath::StandardNamespaceContext nsContext;
    nsContext.addNamespaceDeclaration("something", "ns");
    parser.setNamespaceContext(nsContext);

    assertTrue(parser.compile("/ns:one"));
    assertTrue(parser.compile("//one/ns:two"));
    assertTrue(parser.compile("//ns:one/ns:two//@id"));
    assertTrue(parser.compile("//one/ns:*"));

    parser.resetNamespaceContext();
  }

  void test12()
  {
    assertTrue(parser.compile("one/two/three[@attr]"));
    assertTrue(parser.compile("one/two/three[@attr][1]"));
    assertTrue(parser.compile("one/two/three[four/@attr]"));
  }

  void test13()
  {
    assertTrue(parser.compile("one/two/three[four|@attr]"));
  }

  void test14()
  {
    assertTrue(parser.compile("one/two/three[-($a)]"));
    assertTrue(parser.compile("one/two/three[--($a)]"));
    assertTrue(parser.compile("one/two/three[-$a|$b]"));
    assertTrue(parser.compile("one/two/three[2*-$a|$b]"));
    assertTrue(parser.compile("one/two/three[2mod-$a|$b]"));
    assertTrue(parser.compile("one/two/three[-(@two)=-1]"));
    assertTrue(parser.compile("one/two/three[-(@two) =-1]"));
    assertTrue(parser.compile("one/two/three[ -(@two)=-1]"));
    assertTrue(parser.compile("one/two/three[-(@two) = -1]"));
  }

  void test15()
  {
    assertTrue(parser.compile("one/two/three[four]"));
    assertTrue(parser.compile("one/two/three[  four]"));
    assertTrue(parser.compile("one/two/three[four  ]"));
    assertTrue(parser.compile("one/two/three[   four  ]"));
  }

  void test16()
  {
    assertTrue(parser.compile("one/two/three[/four]"));
    assertTrue(parser.compile("one/two/three[/four/five]"));
    assertTrue(parser.compile("one/two/three[/four/five[1]]"));
    assertTrue(parser.compile("one/two/three[/four/five[@id][1]]"));
    assertTrue(parser.compile("one/two/three[/four/five[1]/six]"));
    assertTrue(parser.compile("one/two/three[/four/five[1]/six[@id][1]]"));
  }

  void test17()
  {
    assertTrue(parser.compile("one/two/three[@attr1='nob']"));
    assertTrue(parser.compile("one/two/three[$a=$b]"));
    assertTrue(parser.compile("one/two/three[$a!=$b]"));
    assertTrue(parser.compile("one/two/three[$a=$b=$c]"));
    assertTrue(parser.compile("/root/*[child = true()]"));
    assertTrue(parser.compile("/root/*[child = 1]"));
    assertTrue(parser.compile("/root/*[child = '1']"));
    assertTrue(parser.compile("/root/*[1]/trousers"));
    assertTrue(parser.compile("/root/*[@* = @two]"));
    assertTrue(parser.compile("/root/*[@*]"));
    assertTrue(parser.compile("/root/*[*]"));
    assertTrue(parser.compile("/root/*[charlie[one]]"));
    assertTrue(parser.compile("/root/*[/one]"));
    assertTrue(parser.compile("/root/*[charlie[/one]]"));

    assertTrue(parser.compile("/root/*[@* = child/@two]"));
    assertTrue(parser.compile("/root/*[//root/child/@two = @*]"));
    assertTrue(parser.compile("/root/*[/root/child/@two = @*]"));
    assertTrue(parser.compile("/root/*[@*=//root/child/@two]"));
    assertTrue(parser.compile("/root/*[@* =//root/child/@two]"));
    assertTrue(parser.compile("/root/*[@* = //root/child/@two]"));
    assertTrue(parser.compile("/root/*[@*= //root/child/@two]"));
    assertTrue(parser.compile("/root/*[@*=/root/child/@two]"));
    assertTrue(parser.compile("/root/*[@* =/root/child/@two]"));
    assertTrue(parser.compile("/root/*[@* = /root/child/@two]"));
    assertTrue(parser.compile("/root/*[@*= /root/child/@two]"));
    assertTrue(parser.compile("root/*[@*=root/child/@two]"));
    assertTrue(parser.compile("root/*[@* =root/child/@two]"));
    assertTrue(parser.compile("root/*[@* = root/child/@two]"));
    assertTrue(parser.compile("root/*[@*= root/child/@two]"));

    assertTrue(parser.compile("one/two/three[$a<$b]"));
    assertTrue(parser.compile("one/two/three[$a <$b]"));
    assertTrue(parser.compile("one/two/three[$a<   $b]"));
    assertTrue(parser.compile("one/two/three[$a  <$b]"));
    assertTrue(parser.compile("one/two/three[$a>$b]"));
    assertTrue(parser.compile("one/two/three[$a >$b]"));
    assertTrue(parser.compile("one/two/three[$a> $b]"));
    assertTrue(parser.compile("one/two/three[$a > $b]"));
    assertTrue(parser.compile("one/two/three[$a<$b]"));
    assertTrue(parser.compile("one/two/three[$a>=$b]"));
    assertTrue(parser.compile("one/two/three[$a<=$b]"));
    assertTrue(parser.compile("one/two/three[$a>$b>$c]"));
    assertTrue(parser.compile("one/two/three[$a>$b<$c]"));
    assertTrue(parser.compile("one/two/three[$a=$b<$c]"));

    assertTrue(parser.compile("one/two/three[($a>$b)or($b>$c)]"));
    assertTrue(parser.compile("one/two/three[($a>$b)and($b>$c)]"));

    assertTrue(parser.compile("/root/*[@* = string('woo')]"));
    assertTrue(parser.compile("/root/*[@* = string(//root/child/@two)]"));
    assertTrue(parser.compile_expr("$fruit/*[2]"));
    assertTrue(parser.compile("/root[$fruit/root = @*]"));
    assertTrue(parser.compile("/root/*[$fruit/root/child/@two = @*]"));
    assertTrue(parser.compile("/root/*[$fruit/root/child/@two = $fruit/root/child/@two]"));
  }

  void test18()
  {
    assertTrue(parser.compile("one/two/three[last()]"));
    assertTrue(parser.compile("one/two/three[comment()]"));
    assertTrue(parser.compile("one/two/three[string($a)]"));

    assertTrue(parser.compile("one/two/three[$var]"));
    assertTrue(parser.compile("one/two/three[position()=1]"));
    assertTrue(parser.compile("one/two/three[(@attr)or(@id)]"));
    assertTrue(parser.compile("one/two/three[$var=1]"));
    try {
      parser.compile("one/two/three[string($a,$b)]");
      assert(false);
    }
    catch(...) { }
    assertTrue(parser.compile("one/two/three[contains($a,string($b))]"));
  }

  void test19()
  {
    assertTrue(parser.compile("one/two/three[(1+1)]"));
    assertTrue(parser.compile("one/two/three[(1-1)]"));
    assertTrue(parser.compile("one/two/three[(1+1-1)]"));
    assertTrue(parser.compile("one/two/three[(1+1+1)]"));
    assertTrue(parser.compile("one/two/three[(1+1+1+1)]"));

    assertTrue(parser.compile("one/two/three[(1*1)]"));
    assertTrue(parser.compile("one/two/three[(1*1*1)]"));
    assertTrue(parser.compile("one/two/three[(1*1*1*1)]"));

    assertTrue(parser.compile("one/two/three[(6div2)]"));
    assertTrue(parser.compile("one/two/three[(5mod4)]"));

    assertTrue(parser.compile("one/two/three[(2*2)]"));
    assertTrue(parser.compile("one[1 + 2 * 3]"));
    assertTrue(parser.compile("one[3 * 2 + 1]"));
  }

  void test20()
  {
    assertTrue(parser.compile("one/two/three[(1)]"));
    assertTrue(parser.compile("one/two/three[(1.1)]"));
    assertTrue(parser.compile("one/two/three[(1.)]"));
    assertTrue(parser.compile("one/two/three[.1]"));
    assertTrue(parser.compile("one/two/three[  .1  ]"));
    assertTrue(parser.compile("one/two/three[(12)]"));
    assertTrue(parser.compile("one/two/three[(123.456)]"));
    assertTrue(parser.compile("one/two/three[(.123456)]"));
  }

  void test21()
  {
    assertTrue(parser.compile("one/two/three[$var]"));
    assertTrue(parser.compile("one/two/three    [$var]"));
    assertTrue(parser.compile("one/two/three[$var]   "));
    assertTrue(parser.compile("one/two/three[$var] /four"));
    assertTrue(parser.compile("one/two/three[$var ]"));
    assertTrue(parser.compile("one/two/three[$var    ]"));
    assertTrue(parser.compile("one/two/three[ $var]"));
    assertTrue(parser.compile("one/two/three[  $var]"));
    assertTrue(parser.compile("one/two/three[   $var   ]"));
    assertTrue(parser.compile("one/two/three[$var = 1]"));
  }

  void test22()
  {
    assertTrue(parser.compile("one/two/three[position() = 1]"));
    assertTrue(parser.compile("one/two/three[position(  ) = 1]"));
    assertTrue(parser.compile("one/two/three[(@attr) or (@id)]"));
    assertTrue(parser.compile("one/two/three[@attr or @id]"));
    try {
      parser.compile("one/two/three[string($a, $b)]");
      assert(false);
    }
    catch(...) { }
    assertTrue(parser.compile("one/two/three[contains($a, string($b))]"));
    assertTrue(parser.compile("one/two/three[contains(    $a, string($b))]"));
    assertTrue(parser.compile("one/two/three[contains    ($a, string($b)   )]"));
  } // test22

  void test23()
  {
    assertTrue(parser.compile("/root[count(something)]"));
    try {
      parser.compile("/root[count()]");
      assert(false);
    }
    catch(...) { }
    try {
      parser.compile("/root[count(one, two)]");
      assert(false);
    }
    catch(...) { }
    try {
      parser.compile("/root[count(one,two)]");
      assert(false);
    }
    catch(...) { }
    try {
      parser.compile("/root/count(one,two)");
      assert(false);
    }
    catch(...) { }
  } // test23
}; // class ParseTest

TestSuite* ParseTest_suite() 
{
  TestSuite *suiteOfTests = new TestSuite;

  suiteOfTests->addTest(new TestCaller<ParseTest>("test1", &ParseTest::test1));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test2", &ParseTest::test2));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test3", &ParseTest::test3));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test4", &ParseTest::test4));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test5", &ParseTest::test5));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test6", &ParseTest::test6));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test7", &ParseTest::test7));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test8", &ParseTest::test8));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test9", &ParseTest::test9));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test10", &ParseTest::test10));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test11", &ParseTest::test11));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test12", &ParseTest::test12));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test13", &ParseTest::test13));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test14", &ParseTest::test14));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test15", &ParseTest::test15));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test16", &ParseTest::test16));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test17", &ParseTest::test17));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test18", &ParseTest::test18));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test19", &ParseTest::test19));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test20", &ParseTest::test20));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test21", &ParseTest::test21));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test22", &ParseTest::test22));
  suiteOfTests->addTest(new TestCaller<ParseTest>("test23", &ParseTest::test23));

  return suiteOfTests;
} // ParseTest_suite
