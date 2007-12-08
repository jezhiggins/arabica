
#ifdef _MSC_VER
#pragma warning(disable:4244 4267)
#endif

#include <iostream>
#include "xpath_test_suite.hpp"

/////////////////////////////////////////
int main(int argc, const char** argv)
{
  bool ok = XPath_test_suite<std::string, Arabica::default_string_adaptor<std::string> >(argc, argv);
  return !ok;
} // main

