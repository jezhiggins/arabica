#ifndef ARABICA_IMPL_CODECVT_SPECIALISATIONS_H
#define ARABICA_IMPL_CODECVT_SPECIALISATIONS_H

#include <locale>

namespace std
{

template<> 
class codecvt<char, wchar_t, std::mbstate_t> :
  public locale::facet, public codecvt_base
{
public:
  static locale::id id;

  codecvt_base::result out(std::mbstate_t& state,
                           const char* from,
                           const char* from_end,
                           const char*& from_next,
                           wchar_t* to,
                           wchar_t* to_limit,
                           wchar_t*& to_next) const
  {
    return this->do_out(state, from, from_end, from_next, to, to_limit, to_next);
  } // out

  
  codecvt_base::result in(std::mbstate_t& state,
                          const wchar_t* from,
                          const wchar_t* from_end,
                          const wchar_t*& from_next,
                          char* to,
                          char* to_limit,
                          char*& to_next) const
  {
    return this->do_in(state, from, from_end, from_next, to, to_limit, to_next);
  } // in

  int encoding() const throw()
  {
    return this->do_encoding(); 
  } // encoding

  bool always_noconv() const throw()
  {
    return this->do_always_noconv();
  } // always_noconv

  int length(std::mbstate_t& state, 
             const wchar_t* from,
             const wchar_t* end,
             size_t max) const
  {
    return this->do_length(state, from, end, max);
  } // length

protected:
  virtual ~codecvt() { }

  virtual codecvt_base::result do_out(std::mbstate_t&,
                                      const char* from,
                                      const char* from_end,
                                      const char*& from_next,
                                      wchar_t* to,
                                      wchar_t* to_limit,
		                                  wchar_t*& to_next) const
  {
    int limit = std::max<int>(from_end - from, to_limit - to);
    from_next = from;
    to_next = to;

    while(limit--)
      *to_next++ = static_cast<wchar_t>(*from_next++);

    return codecvt_base::ok;
  } // do_out


  virtual codecvt_base::result do_in(std::mbstate_t&,
                                     const wchar_t* from,
                                     const wchar_t* from_end,
                                     const wchar_t*& from_next,
                                     char* to,
                                     char* to_limit,
                                     char*& to_next) const
  {
    int limit = std::max<int>(from_end - from, to_limit - to);
    from_next = from;
    to_next = to;

    while(limit--)
      *to_next++ = static_cast<char>(*from_next++);

    return codecvt_base::ok;
  } // do_in

  virtual codecvt_base::result do_unshift(std::mbstate_t&,
                                          wchar_t* to,
                                          wchar_t* /*to_limit*/,
                                          wchar_t*& to_next) const
  {
    to_next = to;
    return codecvt_base::noconv;
  } // do_unshift

  virtual int do_encoding() const throw()
  {
    return 1;
  } // do_encoding

  virtual bool do_always_noconv() const throw()
  {
    return false;
  } // do_always_noconv

  virtual int do_length(std::mbstate_t&,
                        const wchar_t* from,
                        const wchar_t* end,
                        size_t max) const
  {
    return std::min<int>(max, (end - from));
  } // do_length

  virtual int do_max_length() const throw()
  {
    return 1;
  } // do_max_length
}; // class codecvt<char, wchar_t, std::mbstate_t> :

} // namespace std
#endif
