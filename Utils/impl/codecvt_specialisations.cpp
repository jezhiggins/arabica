
#include <SAX/ArabicaConfig.h>
#ifndef ARABICA_NO_CODECVT_SPECIALISATIONS
#include <Utils/impl/codecvt_specialisations.h>

namespace std
{

////////////////////////////////////////////////////////////////////////
codecvt_base::result 
codecvt<char, wchar_t, mbstate_t>:: 
do_out(mbstate_t&, const char* from, const char* from_end, const char*& from_next,
       wchar_t* to, wchar_t* to_limit, wchar_t*& to_next) const
{
  int limit = std::max<int>(from_end - from, to_limit - to);
  from_next = from;
  to_next = to;

  while(limit--)
    *to_next++ = static_cast<wchar_t>(*from_next++);

  return codecvt_base::ok;
} // do_out

codecvt_base::result 
codecvt<char, wchar_t, mbstate_t>:: 
do_in(mbstate_t&, const wchar_t* from, const wchar_t* from_end, const wchar_t*& from_next,
                  char* to, char* to_limit, char*& to_next)  const
{
  int limit = std::max<int>(from_end - from, to_limit - to);
  from_next = from;
  to_next = to;

  while(limit--)
    *to_next++ = static_cast<char>(*from_next++);

  return codecvt_base::ok;
} // do_in

codecvt_base::result 
codecvt<char, wchar_t, mbstate_t>:: 
do_unshift(mbstate_t&, wchar_t* to, wchar_t* to_limit, wchar_t*& to_next) const
{
  to_next = to;
  return codecvt_base::noconv;
} // do_unshift

int 
codecvt<char, wchar_t, mbstate_t>:: 
do_encoding() const throw()
{
  return 1;
} // do_encoding

bool 
codecvt<char, wchar_t, mbstate_t>:: 
do_always_noconv() const throw()
{
  return false;
} // do_always_noconv

int 
codecvt<char, wchar_t, mbstate_t>:: 
do_length(const mbstate_t&, const wchar_t* from, const wchar_t* end, size_t max) const
{
  return std::min<int>(max, (end - from));
} // do_length

int 
codecvt<char, wchar_t, mbstate_t>:: 
do_max_length() const throw()
{
  return 1;
} // do_max_length

} // namespace std

#endif
