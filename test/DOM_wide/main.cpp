#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#ifndef ARABICA_NO_WCHAR_T
#include <iostream>
#endif 

#include "../DOM/dom_test_suite.hpp"

////////////////////////////////////////////////
int main(int argc, const char* argv[])
{
#ifndef ARABICA_NO_WCHAR_T
  DOM_test_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >(argc, argv);
#else
	std::cout << "No DOM_wide tests on this platform :)" << std::endl;
#endif

  return 0;
} // main

// end of file
