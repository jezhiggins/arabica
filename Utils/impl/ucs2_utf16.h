#ifndef ARABICA_UTILS_UCS2_UTF16_H
#define ARABICA_UTILS_UCS2_UTF16_H
#include <locale>
namespace Arabica
{
namespace Internal 
{
std::codecvt_base::result ucs2_2_utf16(bool be, const wchar_t* from, const wchar_t* from_end, const wchar_t*& from_next,
                                      char* to, char* to_limit, char*& to_next);
std::codecvt_base::result utf16_2_ucs2(bool be, const char* from, const char* from_end, const char*& from_next,
                                      wchar_t* to, wchar_t* to_limit, wchar_t*& to_next);
} // namepsace Internal
} // namespace Arabica
#endif

