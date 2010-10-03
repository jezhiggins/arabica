#include "silly_string.hpp"

#include <io/convertstream.hpp>
#include <convert/utf8ucs2codecvt.hpp>
#include <convert/ucs2utf8codecvt.hpp>

silly_string::silly_string()
{
} // silly_string

silly_string::silly_string(const silly_string& rhs)
{
  s_ = rhs.s_;
} // silly_string

silly_string::~silly_string()
{
} // ~silly_string

bool silly_string::operator==(const silly_string& rhs) const
{
  return s_ == rhs.s_;
} // operator== 

silly_string& silly_string::operator=(const silly_string& rhs)
{
  s_ = rhs.s_;
  return *this;
} // operator=

bool operator<(const silly_string& lhs, const silly_string& rhs)
{
  return lhs.s_ < rhs.s_;
} // operator<

////////////////////////////////////////
////////////////////////////////////////
char silly_string_adaptor::convert_from_utf8(char c)
{
  return c;
} // convert_from_utf8
  
silly_string silly_string_adaptor::construct_from_utf8(const char* str)
{
  silly_string s;
  if(str)
    s.s_ = str;
  return s;
} // construct_from_utf8

silly_string silly_string_adaptor::construct_from_utf8(const char* str, int length)
{
  silly_string s;
  if(str)
    s.s_ = std::string(str, length);
  return s;
} // construct_from_utf8

#ifndef ARABICA_NO_WCHAR_T
silly_string silly_string_adaptor::construct_from_utf16(const wchar_t* str)
{
  Arabica::io::basic_oconvertstream<wchar_t, std::char_traits<wchar_t>,
                                    char, std::char_traits<char> > narrower;
  narrower.imbue(std::locale(narrower.getloc(), new Arabica::convert::utf8ucs2codecvt()));
  narrower.str(str ? str : L"");
  silly_string s;
  s.s_ = narrower.str();
  return s;
} // construct_from_utf16

silly_string silly_string_adaptor::construct_from_utf16(const wchar_t* str, int length)
{
  Arabica::io::basic_oconvertstream<wchar_t, std::char_traits<wchar_t>,
                                    char, std::char_traits<char> > narrower;
  narrower.imbue(std::locale(narrower.getloc(), new Arabica::convert::utf8ucs2codecvt()));
  narrower.str(std::wstring(str, length));
  silly_string s;
  s.s_ = narrower.str();
  return s;
} // construct_from_utf16
#endif

bool silly_string_adaptor::empty(const silly_string& s)
{
  return s.s_.empty();
} // empty

silly_string_adaptor::size_type silly_string_adaptor::find(const silly_string& str, const silly_string& what)
{
  return str.s_.find(what.s_);
} // find

silly_string_adaptor::size_type silly_string_adaptor::find(const silly_string& str, value_type c)
{
  return str.s_.find(c);
} // find

silly_string silly_string_adaptor::substr(const silly_string& str, const size_type& offset)
{
  return silly_string_adaptor::construct_from_utf8(str.s_.substr(offset).c_str());
} // substr

silly_string silly_string_adaptor::substr(const silly_string& str, const size_type& offset, const size_type& count)
{
  return silly_string_adaptor::construct_from_utf8(str.s_.substr(offset, count).c_str());
} // substr

silly_string_adaptor::size_type silly_string_adaptor::length(const silly_string& str)
{
  return str.s_.length();
} // length

void silly_string_adaptor::append(silly_string& str, const silly_string& a)
{
  str.s_.append(a.s_);
} // append

void silly_string_adaptor::insert(silly_string& str, size_type offset, const silly_string& a)
{
  str.s_.insert(offset, a.s_);
} // insert

void silly_string_adaptor::replace(silly_string& str, size_type offset, size_type count, const silly_string& a)
{
  str.s_.replace(offset, count, a.s_);
} // replace


// only used to constuct error strings - don't have to be highly efficient!
std::string silly_string_adaptor::asStdString(const silly_string& str)
{
  return str.s_;
} // asStdString

#ifndef ARABICA_NO_WCHAR_T
std::wstring silly_string_adaptor::asStdWString(const silly_string& str)
{
  Arabica::io::basic_oconvertstream<char, std::char_traits<char>,
                                    wchar_t, std::char_traits<wchar_t> > widener;
  std::codecvt<char, wchar_t, std::mbstate_t>* cc = new Arabica::convert::ucs2utf8codecvt();
  widener.imbue(std::locale(widener.getloc(), cc));
  widener.str(str.s_);
  return widener.str();
} // asStdWString
#endif

