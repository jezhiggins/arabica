// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
#include <convert/impl/ucs2_utf16.hpp>
// --------------------------------------------------------------------------

std::codecvt_base::result Arabica::convert::impl::utf16_2_ucs2(bool be,
                       char const* from, char const* from_end, char const*& from_next,
                       wchar_t* to, wchar_t* to_limit, wchar_t*& to_next)
{
  from_next = from;
  to_next = to;

  while((from_next+1 < from_end) && (to_next < to_limit))
	{ 
    wchar_t b1 = static_cast<unsigned char>(*from_next++);
    wchar_t b2 = static_cast<unsigned char>(*from_next++);

    *to_next++ = be ? ((b1 << 8) + b2) : ((b2 << 8) + b1);
  } // while

  return (from_next == from_end) ? std::codecvt_base::ok : std::codecvt_base::partial;
} // utf16_2_ucs2

std::codecvt_base::result Arabica::convert::impl::ucs2_2_utf16(bool be,
                        wchar_t const* from, wchar_t const* from_end, wchar_t const*& from_next,
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
} // ucs2_2_utf8

// end of file
