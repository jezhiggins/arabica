//---------------------------------------------------------------------------
// $Id$
//---------------------------------------------------------------------------
#include "ucs2_utf16.h"
//---------------------------------------------------------------------------
std::codecvt_base::result ArabicaInternal::ucs2_2_utf16(
                        bool be,
                        const wchar_t* from, const wchar_t* from_end, const wchar_t*& from_next,
                        char* to, char* to_limit, char*& to_next)
{
  from_next = from;
  to_next = to;

  while(from_next < from_end)
  {
    if(to_next + 2 >= to_limit)
      return std::codecvt_base::partial;

    wchar_t ch = *from_next;
    unsigned char lb = static_cast<unsigned char>(ch & 0xFF);
    unsigned char hb = static_cast<unsigned char>((ch >> 8) & 0xFF);
    if(be)
    { // big endian
      *to_next++ = hb;
      *to_next++ = lb;
    } 
    else
    { // little endian
      *to_next++ = lb;
      *to_next++ = hb;
    }

    ++from_next;
  } // while(from_next < from_end)

  return std::codecvt_base::ok;
} // iso88591_2_utf8

std::codecvt_base::result ArabicaInternal::utf16_2_ucs2(
                       bool be,
                       const char* from, const char* from_end, const char*& from_next,
                       wchar_t* to, wchar_t* to_limit, wchar_t*& to_next)
{
  from_next = from;
  to_next = to;

	while((from_next+2 < from_end) && (to_next < to_limit))
	{
    wchar_t b1 = static_cast<wchar_t>(*from_next++);
    wchar_t b2 = static_cast<wchar_t>(*from_next++);

    *to_next++ = be ? ((b2 << 8) + b1) : ((b1 << 8) + b2);
  } // while

  return (from_next == from_end) ? std::codecvt_base::ok : std::codecvt_base::partial;
} // utf8_2_iso88591
// end of file
