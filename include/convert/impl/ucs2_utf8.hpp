#ifndef ARABICA_UTILS_UCS2_UTF8_H
#define ARABICA_UTILS_UCS2_UTF8_H

#include <locale>

namespace Arabica
{
namespace convert
{
namespace impl
{

std::codecvt_base::result ucs2_2_utf8(const wchar_t* from, const wchar_t* from_end, const wchar_t*& from_next,
                                      char* to, char* to_limit, char*& to_next);

std::codecvt_base::result utf8_2_ucs2(const char* from, const char* from_end, const char*& from_next,
                                      wchar_t* to, wchar_t* to_limit, wchar_t*& to_next);

} // namespace impl
} // namespace convert
} // namespace Arabica

#endif
