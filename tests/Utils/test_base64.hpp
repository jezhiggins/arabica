#ifndef UTILS_BASE64_TEST_HPP
#define UTILS_BASE64_TEST_HPP

#include <convert/base64codecvt.hpp>

#ifdef _MSC_VER
#pragma warning(disable: 4244)
#endif

#include <cstring>

class Base64Test : public TestCase
{
  public:
    Base64Test(std::string name) : 
      TestCase(name)
    {
    } // Base64Test

    void testEncode1()
    {
      const char* in = "ABC";
      char out[10];
      std::memset(out, '#', 10);

      Arabica::convert::base64codecvt cvt;
      std::mbstate_t state = std::mbstate_t();

      const char* in_next = in;
      char* out_next = out;
      std::codecvt_base::result res = cvt.out(state, in, in+3, in_next, out, out+10, out_next);
 

      assertEquals(std::codecvt_base::ok, res);
      assertEquals(4, (out_next-out));
      assertEquals('#', out[4]);
      assertEquals("QUJD", std::string(out, out_next));
    } // testEncode1

    void testEncode2()
    {
      const char* in = "ABCD";
      char out[10];
      std::memset(out, '#', 10);

      Arabica::convert::base64codecvt cvt;
      std::mbstate_t state = std::mbstate_t();

      const char* in_next = in;
      char* out_next = out;
      std::codecvt_base::result res = cvt.out(state, in, in+4, in_next, out, out+10, out_next);

      assertEquals(std::codecvt_base::ok, res);
      assertEquals(8, (out_next-out));
      assertEquals('#', out[8]);
      assertEquals("QUJDRA==", std::string(out, out_next));
    } // testEncode2

    void testDecode1()
    {
      const char* out = "QUJD";
      char in[10];
      std::memset(in, '#', 10);

      Arabica::convert::base64codecvt cvt;
      std::mbstate_t state = std::mbstate_t();

      const char* out_next = out;
      char* in_next = in;
      std::codecvt_base::result res = cvt.in(state, out, out+4, out_next, in, in+10, in_next);

      assertEquals("ABC", std::string(in, in_next));
      assertEquals(3, (in_next-in));
      assertEquals('#', in[3]);
      assertEquals(std::codecvt_base::ok, res);
    } // testDecode1

    void testDecode2()
    {
      const char* out = "QUJDRA==";
      char in[10];
      std::memset(in, '#', 10);

      Arabica::convert::base64codecvt cvt;
      std::mbstate_t state = std::mbstate_t();

      const char* out_next = out;
      char* in_next = in;
      std::codecvt_base::result res = cvt.in(state, out, out+8, out_next, in, in+10, in_next);

      assertEquals(std::codecvt_base::ok, res);
      assertEquals(4, (in_next-in));
      assertEquals('#', in[4]);
      assertEquals("ABCD", std::string(in, in_next));
    } // testDecode2

    void testDecode3()
    {
      const char* out = "QUJDRA==";
      char in[10];
      std::memset(in, '#', 10);

      Arabica::convert::base64codecvt cvt;
      std::mbstate_t state = std::mbstate_t();

      const char* out_next = out;
      char* in_next = in;
      std::codecvt_base::result res = cvt.in(state, out, out+8, out_next, in, in+2, in_next);

      assertEquals(std::codecvt_base::partial, res);
      assertEquals(2, (in_next-in));
      assertEquals('#', in[3]);
      assertEquals("AB", std::string(in, in_next));

      in_next = in;
      res = cvt.in(state, out_next, out+8, out_next, in, in+2, in_next);

      assertEquals(std::codecvt_base::partial, res);
      assertEquals(2, (in_next-in));
      assertEquals('#', in[3]);
      assertEquals("CD", std::string(in, in_next));

      in_next = in;
      res = cvt.in(state, out_next, out+8, out_next, in, in+2, in_next);

      assertEquals(std::codecvt_base::ok, res);
      assertEquals(0, (in_next-in));
    } // testDecode3

    void testDecode4()
    {
      const char* out = "QUJDRA==";
      char in[10];
      std::memset(in, '#', 10);

      Arabica::convert::base64codecvt cvt;
      std::mbstate_t state = std::mbstate_t();

      const char* out_next = out;
      char* in_next = in;
      std::codecvt_base::result res = cvt.in(state, out, out+8, out_next, in, in+3, in_next);

      assertEquals(std::codecvt_base::partial, res);
      assertEquals(3, (in_next-in));
      assertEquals('#', in[4]);
      assertEquals("ABC", std::string(in, in_next));

      in_next = in;
      std::memset(in, '#', 10);
      res = cvt.in(state, out_next, out+8, out_next, in, in+3, in_next);

      assertEquals(std::codecvt_base::ok, res);
      assertEquals(1, (in_next-in));
      assertEquals('#', in[1]);
      assertEquals("D", std::string(in, in_next));
    } // testDecode4


}; // class Base64Test

TestSuite* Base64Test_suite()
{
  TestSuite* suiteOfTests = new TestSuite();

  suiteOfTests->addTest(new TestCaller<Base64Test>("testEncode1", &Base64Test::testEncode1));
  suiteOfTests->addTest(new TestCaller<Base64Test>("testEncode2", &Base64Test::testEncode2));
  suiteOfTests->addTest(new TestCaller<Base64Test>("testDecode1", &Base64Test::testDecode1));
  suiteOfTests->addTest(new TestCaller<Base64Test>("testDecode2", &Base64Test::testDecode2));
  suiteOfTests->addTest(new TestCaller<Base64Test>("testDecode3", &Base64Test::testDecode3));
  suiteOfTests->addTest(new TestCaller<Base64Test>("testDecode4", &Base64Test::testDecode4));

  return suiteOfTests;
} // Base64Test_suite

#endif
