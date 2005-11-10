
#ifdef _MSC_VER
#pragma warning(disable:4224 4267)
#endif


#include <iostream>
#include "../XPath/xpath_test_suite.hpp"
#include "../silly_string/silly_string.hpp"

namespace Arabica
{

template<> class default_string_adaptor<silly_string> : public silly_string_adaptor { };

} // namespace Arabica

/////////////////////////////////////////
int main(int argc, const char** argv)
{
  std::cout << "Hello" << std::endl;

  XPath_test_suite<silly_string, Arabica::default_string_adaptor<silly_string> >(argc, argv);
} // main

