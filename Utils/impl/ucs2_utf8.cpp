//---------------------------------------------------------------------------
// $Id$
//---------------------------------------------------------------------------
#include "ucs2_utf8.h"
//---------------------------------------------------------------------------
// Some of this code is derived from work done by Ken Thompson,
// provided to the X/Open Group.
//
// I got my information about UTF-8 from RFC 2044.


namespace {
  struct Tab
  {
    char char_mask;
    char char_value;
    int shift;
    wchar_t wide_mask;
  };

  static const Tab tab[] =
  {
    { char(0x80),  char(0x00),   0*6,    0x7F,   },   // 1 byte sequence
    { char(0xE0),  char(0xC0),   1*6,    0x7FF,  },   // 2 byte sequence
    { char(0xF0),  char(0xE0),   2*6,    0xFFFF, },   // 3 byte sequence
    { 0,           0,            0,      0,      }    // end of table
  };
} // namespace 

std::codecvt_base::result ArabicaInternal::ucs2_2_utf8(
                        const wchar_t* from, const wchar_t* from_end, const wchar_t*& from_next,
                        char* to, char* to_limit, char*& to_next)
{
  from_next = from;
  to_next = to;

  while(from_next < from_end)
  {
    for(const Tab *t = tab; t->char_mask; t++)
    {
      if(*from_next > t->wide_mask )
        continue;

      // is there enough room in outbuffer?
      if(to_next + (t - tab) + 1 >= to_limit)
        return std::codecvt_base::partial;

      int c = t->shift;
      *to_next++ = static_cast<char>(t->char_value | (*from_next >> c));
      while(c > 0)
      {
      	c -= 6;
       	*to_next++ = static_cast<char>(0x80 | ((*from_next >> c) & 0x3F));
      } // while(c > 0)
      break;
    } // for(Tab *t = tab;  t->char_mask; t++)
    ++from_next;
  } // while(from_next < from_end)

  return std::codecvt_base::ok;
} // iso88591_2_utf8

std::codecvt_base::result ArabicaInternal::utf8_2_ucs2(
                       const char* from, const char* from_end, const char*& from_next,
                       wchar_t* to, wchar_t* to_limit, wchar_t*& to_next)
{
  from_next = from;
  to_next = to;

	while((from_next < from_end) && (to_next < to_limit))
	{
    char start = *from_next;
    *to_next = static_cast<unsigned char>(*from_next);
    for(const Tab *t = tab; t->char_mask; t++)
    {
      if((start & t->char_mask) == t->char_value)
      {
        *to_next &= t->wide_mask;
        break;
      }
      from_next++;
      *to_next = (*to_next << 6) | ((*from_next ^ 0x80) & 0xff);
    } // for(Tab *t = tab;  t->char_mask; t++)

    ++from_next;
    ++to_next;
  } // while

  return (from_next == from_end) ? std::codecvt_base::ok : std::codecvt_base::partial;
} // utf8_2_iso88591
// end of file
