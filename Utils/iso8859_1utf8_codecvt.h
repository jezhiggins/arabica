#ifndef ISO8859_1utf8_codecvtH
#define ISO8859_1utf8_codecvtH
#include <locale>

#ifdef _MSC_VER
namespace std {
  typedef ::mbstate_t mbstate_t;
}
#endif

class iso8859_1utf8_codecvt : public std::codecvt<char, char, std::mbstate_t>
{
protected:
  virtual ~iso8859_1utf8_codecvt();

  virtual result do_out(std::mbstate_t&,
                        const char* from,
                        const char* from_end,
                        const char*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const;

  virtual result do_in(std::mbstate_t&,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       char* to,
                       char* to_limit,
                       char*& to_next) const;

  virtual result do_unshift(std::mbstate_t&,
                            char*,
                            char*,
                            char*&) const;

  virtual int do_encoding() const throw();

  virtual bool do_always_noconv() const throw();

  virtual int do_length(const std::mbstate_t&,
                        const char* from,
                        const char* end,
                        size_t max) const;

  virtual int do_max_length() const throw();
}; // class iso8859_1utf8_codecvt

#endif
