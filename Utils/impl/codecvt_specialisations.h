#ifndef ARABICA_IMPL_CODECVT_SPECIALISATIONS_H
#define ARABICA_IMPL_CODECVT_SPECIALISATIONS_H

#include <locale>

namespace std
{

template<> 
class codecvt<char, wchar_t, mbstate_t> :
  public codecvt_base
{
protected:
  virtual result do_out(mbstate_t&,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       wchar_t* to,
                       wchar_t* to_limit,
		       wchar_t*& to_next) const = 0;

  virtual result do_in(mbstate_t&,
                        const wchar_t* from,
                        const wchar_t* from_end,
                        const wchar_t*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const = 0;

  virtual result do_unshift(mbstate_t&,
                            wchar_t* to,
                            wchar_t* to_limit,
                            wchar_t*& to_next) const = 0;

  virtual int do_encoding() const throw() = 0;

  virtual bool do_always_noconv() const throw() = 0;

  virtual int do_length(const mbstate_t&,
                        const wchar_t* from,
                        const wchar_t* end,
                        size_t max) const = 0;

  virtual int do_max_length() const throw() = 0;
};

}
#endif
