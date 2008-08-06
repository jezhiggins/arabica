//---------------------------------------------------------------------------
// $Id$
//---------------------------------------------------------------------------
#include <convert/utf16beucs2codecvt.hpp>
#ifndef ARABICA_NO_WCHAR_T
#include <convert/impl/ucs2_utf16.hpp>

//---------------------------------------------------------------------------
using namespace Arabica::convert;

std::codecvt_base::result utf16beucs2codecvt::do_out(std::mbstate_t& /* state */,
                        const wchar_t* from,
                        const wchar_t* from_end,
                        const wchar_t*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const
{
  return impl::ucs2_2_utf16(true, from, from_end, from_next, to, to_limit, to_next);
} // do_out

std::codecvt_base::result utf16beucs2codecvt::do_in(std::mbstate_t& /* state */,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       wchar_t* to,
                       wchar_t* to_limit,
                       wchar_t*& to_next) const
{
  return impl::utf16_2_ucs2(true, from, from_end, from_next, to, to_limit, to_next);
} // do_in

std::codecvt_base::result utf16beucs2codecvt::do_unshift(std::mbstate_t& /* state */,
                            char* to,
                            char* /* to_limit */,
                            char*& to_next) const
{
  to_next = to;
  return noconv;
} // do_unshift

int utf16beucs2codecvt::do_length(const std::mbstate_t&,
                                const char* from,
                                const char* end,
                                size_t max) const
{
  return std::max<int>((end-from), max/2);
} // do_length

#endif
// end of file

