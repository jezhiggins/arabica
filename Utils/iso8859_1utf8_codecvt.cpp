//---------------------------------------------------------------------------
// $Id$
//---------------------------------------------------------------------------
#include "iso8859_1utf8_codecvt.h"
//---------------------------------------------------------------------------
// This facet converts from ISO8859:1 (Latin 1) chars to UTF-8 encoded chars.
//
// Some of this code is derived from work done by Ken Thompson,
// provided to the X/Open Group.

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

iso8859_1utf8_codecvt::~iso8859_1utf8_codecvt()
{
} // ~iso8859_1utf8_codecvt

std::codecvt_base::result iso8859_1utf8_codecvt::do_out(std::mbstate_t& /* state */,
                        const char* from,
                        const char* from_end,
                        const char*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const
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
} // do_out

std::codecvt_base::result iso8859_1utf8_codecvt::do_in(std::mbstate_t& /* state */,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       char* to,
                       char* to_limit,
                       char*& to_next) const
{
  from_next = from;
  to_next = to;

	while((from_next < from_end) && (to_next < to_limit))
	{
    char start = *from_next;
    wchar_t next = static_cast<unsigned char>(*from_next);
    for(const Tab *t = tab; t->char_mask; t++)
    {
      if((start & t->char_mask) == t->char_value)
      {
        next &= t->wide_mask;
        break;
      }
      from_next++;
      next = (next << 6) | ((*from_next ^ 0x80) & 0xff);
    } // for(Tab *t = tab;  t->char_mask; t++)

    if(next <= 0xFF)
      *to_next = static_cast<char>(next);
    else
      *to_next = '?';  // error state!

    ++from_next;
    ++to_next;
  } // while

  return (from_next == from_end) ? std::codecvt_base::ok : std::codecvt_base::partial;
} // do_in

std::codecvt_base::result iso8859_1utf8_codecvt::do_unshift(std::mbstate_t& /* state */,
                            char* to,
                            char* /* to_limit */,
                            char*& to_next) const
{
  to_next = to;
  return noconv;
} // do_unshift

int iso8859_1utf8_codecvt::do_encoding() const throw()
{
  return 0;
} // do_encoding

bool iso8859_1utf8_codecvt::do_always_noconv() const throw()
{
  return false;
} // do_always_noconv

int iso8859_1utf8_codecvt::do_length(const std::mbstate_t&,
                        const char* from,
                        const char* end,
                        size_t max) const
{
  size_t count(0);
  const char* from_next = from;

  while((from_next < end) && (count < max))
  {
    if(!(*from_next & 0x80))
    {
	    ++count;
      ++from_next;
    }
    else if((*from_next&0xc0) == 0xc0)
    {
      if(from_next+2 < end)
      {
  	    ++count;
        from_next += 2;
      }
      else
        break;
    }
    else if((*from_next&0xe0) == 0xe0)
    {
      if(from_next+3 < end)
      {
  	    ++count;
        from_next += 3;
      }
      else
        break;
    }
  } // while

  return (from_next-from);
} // do_length

int iso8859_1utf8_codecvt::do_max_length() const throw()
{
  return 2;
} // do_max_length

// end of file
