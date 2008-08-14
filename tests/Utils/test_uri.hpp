#ifndef UTILS_URI_TEST_HPP
#define UTILS_URI_TEST_HPP

#include <io/uri.hpp>

using namespace Arabica::io;

class URITest : public TestCase
{
  public:
    URITest(std::string name) : 
      TestCase(name)
    {
    } // URITest

    void test1()
    {
      URI u("woo");
      
      assertEquals("woo", u.path());
      assertEquals("", u.host());
      assertEquals("", u.scheme());
      assertEquals("0", u.port());
      assertEquals("woo", u.as_string());
    } // test1

    void test2()
    {
      URI u("woo.xml");
      
      assertEquals("woo.xml", u.path());
      assertEquals("", u.host());
      assertEquals("", u.scheme());
      assertEquals("0", u.port());
      assertEquals("woo.xml", u.as_string());
    } // test2

    void test3()
    {
      URI u("woo/woo.xml");
      
      assertEquals("woo/woo.xml", u.path());
      assertEquals("", u.host());
      assertEquals("", u.scheme());
      assertEquals("0", u.port());
      assertEquals("woo/woo.xml", u.as_string());
    } // test3

    void test4()
    {
      URI u("/woo/woo.xml");
      
      assertEquals("/woo/woo.xml", u.path());
      assertEquals("", u.host());
      assertEquals("", u.scheme());
      assertEquals("0", u.port());
      assertEquals("/woo/woo.xml", u.as_string());
    } // test4

    void test5()
    {
      URI u("http://localhost/woo/woo.xml");

      assertEquals("/woo/woo.xml", u.path());
      assertEquals("localhost", u.host());
      assertEquals("http", u.scheme());
      assertEquals("80", u.port());
      assertEquals("http://localhost/woo/woo.xml", u.as_string());
    }

    void test6()
    {
      URI u("http://localhost:8080/woo/woo.xml");

      assertEquals("/woo/woo.xml", u.path());
      assertEquals("localhost", u.host());
      assertEquals("http", u.scheme());
      assertEquals("8080", u.port());
      assertEquals("http://localhost:8080/woo/woo.xml", u.as_string());
    }

    void test7()
    {
      URI u("http://www.jezuk.co.uk/arabica/news");

      assertEquals("/arabica/news", u.path());
      assertEquals("www.jezuk.co.uk", u.host());
      assertEquals("http", u.scheme());
      assertEquals("80", u.port());
      assertEquals("http://www.jezuk.co.uk/arabica/news", u.as_string());
    }

    void test8()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news");

      assertEquals("/arabica/news", u.path());
      assertEquals("www.jezuk.co.uk", u.host());
      assertEquals("http", u.scheme());
      assertEquals("8000", u.port());
      assertEquals("http://www.jezuk.co.uk:8000/arabica/news", u.as_string());
    }

    void test9()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news");
      URI r(u, "http://localhost/nobby");

      assertEquals("/nobby", r.path());
      assertEquals("localhost", r.host());
      assertEquals("http", r.scheme());
      assertEquals("80", r.port());
      assertEquals("http://localhost/nobby", r.as_string());
    } // test9

    void test10()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news");
      URI r(u, "http://localhost/");

      assertEquals("/", r.path());
      assertEquals("localhost", r.host());
      assertEquals("http", r.scheme());
      assertEquals("80", r.port());
      assertEquals("http://localhost/", r.as_string());
    } // test10

    void test11()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news");
      URI r(u, "/trouser/press");

      assertEquals("/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/trouser/press", r.as_string());
    } // test11

    void test12()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news");
      URI r(u, "trouser/press");

      assertEquals("/arabica/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/arabica/trouser/press", r.as_string());
    } // test12

    void test13()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news");
      URI r(u, "./trouser/press");

      assertEquals("/arabica/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/arabica/trouser/press", r.as_string());
    } // test13

    void test14()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news");
      URI r(u, "../trouser/press");

      assertEquals("/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/trouser/press", r.as_string());
    } // test14

    void test15()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news/");
      URI r(u, "/trouser/press");

      assertEquals("/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/trouser/press", r.as_string());
    } // test15

    void test16()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news/");
      URI r(u, "trouser/press");

      assertEquals("/arabica/news/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/arabica/news/trouser/press", r.as_string());
    } // test16

    void test17()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news/");
      URI r(u, "./trouser/press");

      assertEquals("/arabica/news/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/arabica/news/trouser/press", r.as_string());
    } // test17

    void test18()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news/");
      URI r(u, "../trouser/press");

      assertEquals("/arabica/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/arabica/trouser/press", r.as_string());
    } // test18

    void test19()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news/");
      URI r(u, "../../trouser/press");

      assertEquals("/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
    } // test19

    void test20()
    {
      URI u("http://www.jezuk.co.uk:8000/arabica/news/");
      URI r(u, "../../../trouser/press");

      assertEquals("/trouser/press", r.path());
      assertEquals("www.jezuk.co.uk", r.host());
      assertEquals("http", r.scheme());
      assertEquals("8000", r.port());
      assertEquals("http://www.jezuk.co.uk:8000/trouser/press", r.as_string());
    } // test20

    void test21()
    {
      URI e("http://www.jezuk.co.uk/arabica/news");
      URI u;

      u = e;

      assertEquals("/arabica/news", u.path());
      assertEquals("www.jezuk.co.uk", u.host());
      assertEquals("http", u.scheme());
      assertEquals("80", u.port());
    } // test21

   void test22()
   {
     URI e("/one/two/three/four");
     URI r(e, "five");

     assertEquals("/one/two/three/five", r.path());
   } // test22

   void test23()
   {
     URI e("/one/two/three/four");
     URI r(e, "../five");

     assertEquals("/one/two/five", r.path());
   } // test23

   void test24()
   {
     URI e("/one/two/three/four");
     URI r(e, "../../five");

     assertEquals("/one/five", r.path());
   } // test24

   void test25()
   {
     URI e("../one/two/three/four");
     URI r(e, "../../five");

     assertEquals("../one/five", r.path());
   } // test25

   void test26()
   {
     URI e("../../one/two/three/four");
     URI r(e, "../../five");

     assertEquals("../../one/five", r.path());
   } // test26

   void test27()
   {
     URI e("../../one/two/three/four");
     URI r(e, "../five");

     assertEquals("../../one/two/five", r.path());
   } // test27

   void test28()
   {
     URI e("../../one/two/three/four");
     URI r(e, "five");

     assertEquals("../../one/two/three/five", r.path());
   } // test28

   void test29()
   {
     URI e("../../../one/two/three/four");
     URI r(e, "../../five");

     assertEquals("../../../one/five", r.path());
   } // test26

   void test30()
   {
     URI e("../../../one/two/three/four");
     URI r(e, "../five");

     assertEquals("../../../one/two/five", r.path());
   } // test30

   void test31()
   {
     URI e("../../../one/two/three/four");
     URI r(e, "five");

     assertEquals("../../../one/two/three/five", r.path());
   } // test31

   
    void test32()
    {
      // windows file path tests
      URI u("d:\\work\\jezuk\\arabica\\file.xml");

      assertEquals("d:/work/jezuk/arabica/file.xml", u.path());
      assertEquals("", u.host());
      assertEquals("file", u.scheme());
      assertEquals("0", u.port());
      assertEquals("file://d:/work/jezuk/arabica/file.xml", u.as_string());
    } // test32

  void test33()
  {
    URI u("file:///woot.txt");
    
    assertEquals("", u.host());
    assertEquals("file", u.scheme());
    assertEquals("/woot.txt", u.path());
  } // test33

  void test34()
  {
    URI u("file:/woot.txt");
    
    assertEquals("", u.host());
    assertEquals("file", u.scheme());
    assertEquals("/woot.txt", u.path());
  } // test34

  void test35()
  {
    URI u("file:woot.txt");
    
    assertEquals("", u.host());
    assertEquals("file", u.scheme());
    assertEquals("woot.txt", u.path());
  } // URI 

  void test36()
  {
    URI u("file://localhost/woot.txt");
    
    assertEquals("localhost", u.host());
    assertEquals("file", u.scheme());
    assertEquals("/woot.txt", u.path());
  } // test36

  void test37()
  {
    URI u("file:///woot/woot/");
    URI r(u, "woo.txt");
    
    assertEquals("", r.host());
    assertEquals("file", r.scheme());
    assertEquals("/woot/woot/woo.txt", r.path());    
  } // test37

  void test38()
  {
    URI u("file:///woot/woot/");
    URI r(u, "file:woo.txt");
    
    assertEquals("", r.host());
    assertEquals("file", r.scheme());
    assertEquals("/woot/woot/woo.txt", r.path());    
  } // test38

}; // class URITest

TestSuite* URITest_suite()
{
  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<URITest>("test1", &URITest::test1));
  suiteOfTests->addTest(new TestCaller<URITest>("test2", &URITest::test2));
  suiteOfTests->addTest(new TestCaller<URITest>("test3", &URITest::test3));
  suiteOfTests->addTest(new TestCaller<URITest>("test4", &URITest::test4));
  suiteOfTests->addTest(new TestCaller<URITest>("test5", &URITest::test5));
  suiteOfTests->addTest(new TestCaller<URITest>("test6", &URITest::test6));
  suiteOfTests->addTest(new TestCaller<URITest>("test7", &URITest::test7));
  suiteOfTests->addTest(new TestCaller<URITest>("test8", &URITest::test8));
  suiteOfTests->addTest(new TestCaller<URITest>("test9", &URITest::test9));
  suiteOfTests->addTest(new TestCaller<URITest>("test10", &URITest::test10));
  suiteOfTests->addTest(new TestCaller<URITest>("test11", &URITest::test11));
  suiteOfTests->addTest(new TestCaller<URITest>("test12", &URITest::test12));
  suiteOfTests->addTest(new TestCaller<URITest>("test13", &URITest::test13));
  suiteOfTests->addTest(new TestCaller<URITest>("test14", &URITest::test14));
  suiteOfTests->addTest(new TestCaller<URITest>("test15", &URITest::test15));
  suiteOfTests->addTest(new TestCaller<URITest>("test16", &URITest::test16));
  suiteOfTests->addTest(new TestCaller<URITest>("test17", &URITest::test17));
  suiteOfTests->addTest(new TestCaller<URITest>("test18", &URITest::test18));
  suiteOfTests->addTest(new TestCaller<URITest>("test19", &URITest::test19));
  suiteOfTests->addTest(new TestCaller<URITest>("test20", &URITest::test20));
  suiteOfTests->addTest(new TestCaller<URITest>("test21", &URITest::test21));
  suiteOfTests->addTest(new TestCaller<URITest>("test22", &URITest::test22));
  suiteOfTests->addTest(new TestCaller<URITest>("test23", &URITest::test23));
  suiteOfTests->addTest(new TestCaller<URITest>("test24", &URITest::test24));
  suiteOfTests->addTest(new TestCaller<URITest>("test25", &URITest::test25));
  suiteOfTests->addTest(new TestCaller<URITest>("test26", &URITest::test26));
  suiteOfTests->addTest(new TestCaller<URITest>("test27", &URITest::test27));
  suiteOfTests->addTest(new TestCaller<URITest>("test28", &URITest::test28));
  suiteOfTests->addTest(new TestCaller<URITest>("test29", &URITest::test29));
  suiteOfTests->addTest(new TestCaller<URITest>("test30", &URITest::test30));
  suiteOfTests->addTest(new TestCaller<URITest>("test31", &URITest::test31));
  suiteOfTests->addTest(new TestCaller<URITest>("test32", &URITest::test32));
  suiteOfTests->addTest(new TestCaller<URITest>("test33", &URITest::test33));
  suiteOfTests->addTest(new TestCaller<URITest>("test34", &URITest::test34));
  suiteOfTests->addTest(new TestCaller<URITest>("test35", &URITest::test35));
  suiteOfTests->addTest(new TestCaller<URITest>("test36", &URITest::test36));
  suiteOfTests->addTest(new TestCaller<URITest>("test37", &URITest::test37));
  suiteOfTests->addTest(new TestCaller<URITest>("test38", &URITest::test38));

  return suiteOfTests;
} // URITest_suite

#endif
