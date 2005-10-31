
#ifdef _MSC_VER
#pragma warning(disable:4224 4267)
#endif

#include <iostream>
#include "../XPath/xpath_test_suite.hpp"

/////////////////////////////////////////
int main(int argc, const char** argv)
{
  std::cout << "Hello" << std::endl;

  XPath_test_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >(argc, argv);
} // main

