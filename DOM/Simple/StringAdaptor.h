#ifndef JEZUK_SimpleDOM_STRINGADAPTOR_H
#define JEZUK_SimpleDOM_STRINGADAPTOR_H
/*
 * $Id$
 */

#include <string>

namespace SimpleDOM
{

template<class stringT>
class default_string_adaptor
{
public:
  stringT makeStringT(const char* str) const;
  stringT makeStringT(const char* str, int length) const;
}; // class default_string_maker

// specialize for std::string and std::wstring
template<>
class default_string_adaptor<std::string>
{
public:
  std::string makeStringT(const char* str) const
  {
    return str ? std::string(str) : std::string();
  } // makeStringT
  std::string makeStringT(const char* str, int length) const
  {
    return std::string(str, length);
  } // makeStringT
}; // class default_string_adaptor

template<>
class default_string_adaptor<std::wstring>
{
public:
  std::wstring makeStringT(const char* str) const
  {
    std::wstring ws;
    while(*str != 0)
      ws += static_cast<wchar_t>(*str++);
    return ws;
  } // makeStringT
  std::wstring makeStringT(const char* str, int length) const
  {
    std::wstring ws;
    for(int i = 0; i != length; ++i)
      ws += static_cast<wchar_t>(str[i]);
    return ws;
  } // makeStringT
}; // class default_string_adaptor

} // namespace SimpleDOM

#endif
// end of file
