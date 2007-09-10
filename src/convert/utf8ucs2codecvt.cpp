//---------------------------------------------------------------------------
// $Id$
//---------------------------------------------------------------------------
#include <convert/utf8ucs2codecvt.hpp>
#include <convert/impl/ucs2_utf16.hpp>
#include <convert/impl/ucs2_utf8.hpp>
//---------------------------------------------------------------------------
#ifndef ARABICA_NO_WCHAR_T

using namespace Arabica::convert;

std::codecvt_base::result utf8ucs2codecvt::do_out(std::mbstate_t& /* state */,
                        const wchar_t* from,
                        const wchar_t* from_end,
                        const wchar_t*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const
{
  return impl::ucs2_2_utf8(from, from_end, from_next, to, to_limit, to_next);
} // do_out

std::codecvt_base::result utf8ucs2codecvt::do_in(std::mbstate_t& /* state */,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       wchar_t* to,
                       wchar_t* to_limit,
                       wchar_t*& to_next) const
{
  return impl::utf8_2_ucs2(from, from_end, from_next, to, to_limit, to_next);
} // do_in

std::codecvt_base::result utf8ucs2codecvt::do_unshift(std::mbstate_t& /* state */,
                            char* to,
                            char* /* to_limit */,
                            char*& to_next) const
{
  to_next = to;
  return noconv;
} // do_unshift

int utf8ucs2codecvt::do_length(const std::mbstate_t&,
                                const char* from,
                                const char* end,
                                size_t max) const throw()
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

#endif
// end of file

