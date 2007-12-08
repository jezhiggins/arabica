
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
  bool ok = XPath_test_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >(argc, argv);
  return !ok;
} // main

