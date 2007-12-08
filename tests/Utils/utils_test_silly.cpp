#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include "util_test_suite.hpp"
#include "../silly_string/silly_string.hpp"

////////////////////////////////////////////////
int main(int argc, const char* argv[])
{
  bool ok = Util_test_suite<silly_string, silly_string_adaptor>(argc, argv);

  return !ok;
} // main

// end of file
