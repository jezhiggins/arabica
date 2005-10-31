#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include "../DOM/dom_test_suite.hpp"
#include "../silly_string/silly_string.hpp"

//template<> class Arabica::default_string_adaptor<silly_string> : public silly_string_adaptor { };

////////////////////////////////////////////////
int main(int argc, const char* argv[])
{
  DOM_test_suite<silly_string, silly_string_adaptor>(argc, argv);

  return 0;
} // main

// end of file
