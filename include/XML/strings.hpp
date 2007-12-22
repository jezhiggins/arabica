#ifndef ARABICA_XML_STRINGS_HPP
#define ARABICA_XML_STRINGS_HPP

#include <XML/XMLCharacterClasses.hpp>
#include <text/UnicodeCharacters.hpp>

namespace Arabica
{
namespace XML
{

  bool is_ncname(const std::string& str)
  {
    using namespace Arabica::text;

    std::string::const_iterator s = str.begin();
    if(!(is_letter(*s) || (*s == Unicode<char>::LOW_LINE)))
       return false;

    ++s;
    for(std::string::const_iterator se; s != se; ++s)
    {
      wchar_t c = static_cast<wchar_t>(*s);
      if(!(is_letter(c) || 
           is_digit(c) || 
           (c == Unicode<wchar_t>::FULL_STOP) || 
           (c == Unicode<wchar_t>::HYPHEN_MINUS) ||
           (c == Unicode<wchar_t>::LOW_LINE) ||
           (c == Unicode<wchar_t>::COLON) ||
           is_combining_char(c) ||
           is_extender(c)))
        return false;
    }
    return true;
  } // is_ncname  

} // namespace XML
} // namespace Arabica


#endif
