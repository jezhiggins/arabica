
#ifdef _MSC_VER
#pragma warning(disable:4224 4267)
#endif

#include <iostream>
#include "xpath_test_suite.hpp"

/////////////////////////////////////////
int main(int argc, char** argv)
{
  std::cout << "Hello" << std::endl;

  XPath_test_suite<std::string, Arabica::default_string_adaptor<std::string> >(argc, argv);
} // main

