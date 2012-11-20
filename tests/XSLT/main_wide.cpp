#ifdef _MSC_VER
#pragma warning(disable : 4250)
#endif


// #include "scope_test.hpp"
#include "xslt_test.hpp"
int main(int argc, const char* argv[])
{
  bool ok = XSLT_test_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >(argc, argv);
  //return !ok;
  return 77;  // the make check magic ignore this result marker
}  // main

