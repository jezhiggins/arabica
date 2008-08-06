#ifndef ARABICA_ISO88591UTF8ISO88591_CODECVT_H
#define ARABICA_ISO88591UTF8ISO88591_CODECVT_H
#include <locale>
#include <SAX/ArabicaConfig.hpp>
#include <Arabica/mbstate.hpp>

namespace Arabica
{
namespace convert
{

class iso88591utf8codecvt : public std::codecvt<char, char, std::mbstate_t>
{
protected:
  virtual ~iso88591utf8codecvt() { }

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

  virtual int do_encoding() const throw() { return 1; }

  virtual bool do_always_noconv() const throw() { return false; }

  virtual int do_length(const std::mbstate_t&,
                        const char* from,
                        const char* end,
                        size_t max) const;

  virtual int do_max_length() const throw() { return 1; }
}; // class iso88591utf8codecvt

} // namespace convert
} // namespace Arabica
#endif
