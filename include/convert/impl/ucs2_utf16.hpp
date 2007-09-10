#ifndef ARABICA_UTILS_UCS2_UTF16_H
#define ARABICA_UTILS_UCS2_UTF16_H

#include <locale>

namespace Arabica
{
namespace convert
{
namespace impl
{

std::codecvt_base::result ucs2_2_utf16(bool be, 
                                       wchar_t const* from, wchar_t const* from_end, wchar_t const*& from_next,
                                       char* to, char* to_limit, char*& to_next);
std::codecvt_base::result utf16_2_ucs2(bool be, 
                                       char const* from, char const* from_end, char const*& from_next,
                                       wchar_t* to, wchar_t* to_limit, wchar_t*& to_next);

} // namespace impl
} // namepsace convert
} // namespace Arabica

#endif



