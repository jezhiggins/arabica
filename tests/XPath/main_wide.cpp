
#ifdef _MSC_VER
#pragma warning(disable:4244 4267)
#endif

#include <iostream>
#ifndef ARABICA_NO_WCHAR_T
#include "xpath_test_suite.hpp"
#endif

/////////////////////////////////////////
int main(int argc, const char** argv)
{
#ifndef ARABICA_NO_WCHAR_T
  XPath_test_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >(argc, argv);
#else
  std::cout << "No wide tests on this platform" << std::endl;
#endif
} // main

