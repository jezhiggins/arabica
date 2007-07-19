#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include "util_test_suite.hpp"

////////////////////////////////////////////////
int main(int argc, const char* argv[])
{
  Util_test_suite<std::string, Arabica::default_string_adaptor<std::string> >(argc, argv);

  return 0;
} // main

// end of file
