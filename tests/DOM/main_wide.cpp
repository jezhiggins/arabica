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
  bool ok = DOM_test_suite<std::wstring, Arabica::default_string_adaptor<std::wstring> >(argc, argv);

  return !ok;
} // main

// end of file
