#ifndef ARABICA_UTILS_NORMALIZE_WHITESPACE_HPP
#define ARABICA_UTILS_NORMALIZE_WHITESPACE_HPP

#include <Utils/StringAdaptor.hpp>
#include <XML/XMLCharacterClasses.hpp>
#include <XML/UnicodeCharacters.hpp>

namespace Arabica
{

namespace string
{

template<class string_type, class string_adaptor>
string_type normalize_whitespace(const string_type& ch)
{
  std::string value = string_adaptor::asStdString(ch);
  std::string stripped = normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(value);
  return string_adaptor::construct_from_utf8(stripped.c_str());
} // normalize_whitespace

template<>
std::string normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(const std::string& ch)
{
  std::string value(ch);
  std::string::const_iterator i = value.begin(), ie = value.end();
  std::string::iterator p = value.begin(), pe = value.end();

  // string leading space
  while((i != ie) && (Arabica::XML::is_space(static_cast<char>(*i))))
    ++i;
    
  while(i != ie)
  {
    while((i != ie) && (!Arabica::XML::is_space(static_cast<char>(*i)))) 
      *p++ = *i++;
    while((i != ie) && (Arabica::XML::is_space(static_cast<char>(*i))))
      ++i;
    if(i != ie)
      *p++ = Arabica::Unicode<char>::SPACE;
  } // while ...
  if(p != pe)
    value.erase(p, pe);

  return value;
} // normalize_whitespace

} // namespace string

} // namespace Arabica
#endif

