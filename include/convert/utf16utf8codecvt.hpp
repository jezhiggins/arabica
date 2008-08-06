#ifndef ARABICA_UTF16UTF8_CODECVT_H
#define ARABICA_UTF16UTF8_CODECVT_H
//---------------------------------------------------------------------------
// class utf16utf8codecvt
// This facet converts from Unicode (UCS-2) wchar_ts to
// char using the UTF-8 encoding.
//
// For the full guff on codecvts see section 22.2.1.5 of
// The C++ Standard (ISO/IEC 14882 to be pedantic).
//
// I got my information about UTF-8 from RFC 2044.
//
// $Id$
//---------------------------------------------------------------------------
#include <SAX/ArabicaConfig.hpp>
#include <Arabica/mbstate.hpp>
#include <locale>

#ifndef ARABICA_NO_CODECVT_SPECIALISATIONS
#include <convert/impl/codecvt_specialisations.hpp>
#endif

namespace Arabica
{
namespace convert
{

class utf16utf8codecvt : public std::codecvt<char, wchar_t, std::mbstate_t>
{
protected:
  typedef std::codecvt_base::result result;

  virtual ~utf16utf8codecvt() { }

  virtual result do_out(std::mbstate_t&,
                       const char* from,
                       const char* from_end,
                       const char*& from_next,
                       wchar_t* to,
                       wchar_t* to_limit,
                       wchar_t*& to_next) const;

  virtual result do_in(std::mbstate_t&,
                        const wchar_t* from,
                        const wchar_t* from_end,
                        const wchar_t*& from_next,
                        char* to,
                        char* to_limit,
                        char*& to_next) const;

  virtual result do_unshift(std::mbstate_t&,
                            wchar_t*,
                            wchar_t*,
                            wchar_t*&) const;

  virtual int do_encoding() const throw() { return 0; }

  virtual bool do_always_noconv() const throw() { return false; }

  virtual int do_length(const std::mbstate_t&,
                        const wchar_t* from,
                        const wchar_t* end,
                        size_t max) const;

  virtual int do_max_length() const throw() { return 1; }
}; // class utf16utf8codecvt

} // namespace convert
} // namespace Arabica

#endif

