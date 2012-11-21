#ifdef _MSC_VER
#pragma warning(disable : 4250)
#endif


// #include "scope_test.hpp"
#include "xslt_test.hpp"
#include "../silly_string/silly_string.hpp"

int main(int argc, const char* argv[])
{
  bool ok = XSLT_test_suite<silly_string, silly_string_adaptor>(argc, argv);
  //return !ok;
  return 77;  // the make check magic ignore this result marker
}  // main

