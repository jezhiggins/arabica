//---------------------------------------------------------------------------
// $Id$
//---------------------------------------------------------------------------
#include "iso88591utf8codecvt.h"
#include "impl/iso88591_utf8.h"
//---------------------------------------------------------------------------
// This facet converts from ISO8859:1 (Latin 1) chars to UTF-8 encoded chars.

std::codecvt_base::result iso88591utf8codecvt::do_out(std::mbstate_t& /* state */,
                        const char* from,
                        const char* from_end,
                        const char*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const
{
  return ArabicaInternal::utf8_2_iso88591(from, from_end, from_next, to, to_limit, to_next);
} // do_out

std::codecvt_base::result iso88591utf8codecvt::do_in(std::mbstate_t& /* state */,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       char* to,
                       char* to_limit,
                       char*& to_next) const
{
  return ArabicaInternal::iso88591_2_utf8(from, from_end, from_next, to, to_limit, to_next);
} // do_in

std::codecvt_base::result iso88591utf8codecvt::do_unshift(std::mbstate_t& /* state */,
                            char* to,
                            char* /* to_limit */,
                            char*& to_next) const
{
  to_next = to;
  return noconv;
} // do_unshift

int iso88591utf8codecvt::do_length(const std::mbstate_t&,
                        const char* from,
                        const char* end,
                        size_t max) const
{
  size_t count(0);
  const char* from_next = from;

  while((from_next < end) && (count < max))
  {
    unsigned char fn = static_cast<unsigned char>(*from_next);
    if(fn & 0x80)
      ++count;
    ++count;
    ++from_next;
  } // while

  return (from_next-from);
} // do_length

// end of file




















