#ifndef ARABICA_IMPL_CODECVT_SPECIALISATIONS_H
#define ARABICA_IMPL_CODECVT_SPECIALISATIONS_H

#include <locale>

namespace std
{

template<> 
class codecvt<char, wchar_t, std::mbstate_t> 
{
protected:
  virtual codecvt_base::result do_out(mbstate_t&,
                                      const char* from,
                                      const char* from_end,
                                      const char*& from_next,
                                      wchar_t* to,
                                      wchar_t* to_limit,
		                                  wchar_t*& to_next) const;

  virtual codecvt_base::result do_in(mbstate_t&,
                                     const wchar_t* from,
                                     const wchar_t* from_end,
                                     const wchar_t*& from_next,
                                     char* to,
                                     char* to_limit,
                                     char*& to_next) const;

  virtual codecvt_base::result do_unshift(mbstate_t&,
                                          wchar_t* to,
                                          wchar_t* to_limit,
                                          wchar_t*& to_next) const;

  virtual int do_encoding() const throw();

  virtual bool do_always_noconv() const throw();

  virtual int do_length(const mbstate_t&,
                        const wchar_t* from,
                        const wchar_t* end,
                        size_t max) const;

  virtual int do_max_length() const throw();
}; // class codecvt<char, wchar_t, std::mbstate_t> :


} // namespace std
#endif
