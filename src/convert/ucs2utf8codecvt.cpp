//---------------------------------------------------------------------------
// $Id$
//---------------------------------------------------------------------------
#include <convert/ucs2utf8codecvt.hpp>
#include <convert/impl/ucs2_utf8.hpp>
//---------------------------------------------------------------------------
// This facet converts from wide chars to char using the
// FSS-UTF (UCS2) encoding.
//
using namespace Arabica::convert;

std::codecvt_base::result ucs2utf8codecvt::do_out(std::mbstate_t& /* state */,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       wchar_t* to,
                       wchar_t* to_limit,
                       wchar_t*& to_next) const
{
  return impl::utf8_2_ucs2(from, from_end, from_next, to, to_limit, to_next);
} // do_out

std::codecvt_base::result ucs2utf8codecvt::do_in(std::mbstate_t& /* state */,
                        const wchar_t* from,
                        const wchar_t* from_end,
                        const wchar_t*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const
{
  return impl::ucs2_2_utf8(from, from_end, from_next, to, to_limit, to_next);
} // do_in

std::codecvt_base::result ucs2utf8codecvt::do_unshift(std::mbstate_t& /* state */,
                            wchar_t* to,
                            wchar_t* /* to_limit */,
                            wchar_t*& to_next) const
{
  to_next = to;
  return std::codecvt_base::noconv;
} // do_unshift

int ucs2utf8codecvt::do_length(const std::mbstate_t&,
                                const wchar_t* from,
                                const wchar_t* end,
                                size_t max) const
{
  size_t count(0);
  const wchar_t* from_next = from;

  while((from_next < end) && (count < max))
  {
    if(*from_next > 0x7FF)
      ++count;
    if(*from_next > 0x7F)
      ++count;
    ++count;
    ++from_next;
  } // while

  return (from_next-from);
} // do_length

// end of file

