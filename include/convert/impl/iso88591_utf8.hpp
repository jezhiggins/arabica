#ifndef ARABICA_UTILS_ISO88591_UTF8_H
#define ARABICA_UTILS_ISO88591_UTF8_H

#include <locale>

namespace Arabica
{
namespace convert
{
namespace impl
{

std::codecvt_base::result iso88591_2_utf8(const char* from, const char* from_end, const char*& from_next,
                                          char* to, char* to_limit, char*& to_next);

std::codecvt_base::result utf8_2_iso88591(const char* from, const char* from_end, const char*& from_next,
                                          char* to, char* to_limit, char*& to_next);

} // namespace impl
} // namespace convert
} // namespace Arabica

#endif
