#ifndef STRINGADAPTOR_H
#define STRINGADAPTOR_H
/*
 * $Id$
 */

#include <string>
#include <Utils/convertstream.h>
#include <Utils/utf8ucs2codecvt.h>

namespace SAX
{

template<class string_type>
class default_string_adaptor
{
public:
  typedef string_type stringT;
  typedef typename stringT::value_type value_type;

  value_type makeValueT(char c) const;
  stringT makeStringT(const char* str) const;
  stringT makeStringT(const char* str, int length) const;
  stringT makeStringT(const wchar_t* str) const;
  stringT makeStringT(const wchar_t* str, int length) const;

  // only used to constuct error strings - don't have to be highly efficient!
  std::string asStdString(const stringT& str) const;
  std::wstring asStdWString(const stringT& str) const;
}; // class default_string_maker

// specialize for std::string and std::wstring
template<>
class default_string_adaptor<std::string>
{
  typedef basic_iconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > widener;
  typedef basic_oconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > narrower;
public:
  char makeValueT(char c) const { return c; }

  std::string makeStringT(const char* str) const
  {
    return str ? std::string(str) : std::string();
  } // makeStringT
  std::string makeStringT(const char* str, int length) const
  {
    return std::string(str, length);
  } // makeStringT
  std::string makeStringT(const wchar_t* str) const
  {
    std::wstring s;
    if(str)
      s = str;
    n_.str(s);
    return n_.str();
  } // makeStringT
  std::string makeStringT(const wchar_t* str, int length) const
  {
    n_.str(std::wstring(str, length));
    return n_.str();
  } // makeStringT

  const std::string& asStdString(const std::string& str) const
  {
    return str;
  } // toStdString
  std::wstring asStdWString(const std::string& str) const
  {
    w_.str(str);
    return w_.str();
  } // toStdWString

  default_string_adaptor() :
#if !(defined _MSC_VER) || !(_MSC_VER < 1300)
    loc_(std::locale(), new utf8ucs2codecvt()),
#else
    loc_(std::_Addfac(std::locale(), new utf8ucs2codecvt)),
#endif
    n_(),
    w_()
  {
    n_.imbue(loc_);
    w_.imbue(loc_);
  } // default_string_adaptor 

private:
  std::locale loc_;
  mutable narrower n_;
  mutable widener w_;
}; // class default_string_adaptor

template<>
class default_string_adaptor<std::wstring>
{
  typedef basic_iconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > widener;
  typedef basic_oconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > narrower;
public:
  wchar_t makeValueT(char c) const 
  { 
    return static_cast<wchar_t>(c);
  } // makeValueT

  std::wstring makeStringT(const char* str) const
  {
    if(str)
      w_.str(str);
    else
      w_.str("");
    return w_.str();
  } // makeStringT
  std::wstring makeStringT(const char* str, int length) const
  {
    w_.str(std::string(str, length));
    return w_.str();
  } // makeStringT
  std::wstring makeStringT(const wchar_t* str) const
  {
    return str ? std::wstring(str) : std::wstring();
  } // makeStringT
  std::wstring makeStringT(const wchar_t* str, int length) const
  {
    return std::wstring(str, length);
  } // makeStringT

  std::string asStdString(const std::wstring& str) const
  {
    n_.str(str);
    return n_.str();
  } // toStdString
  const std::wstring& asStdWString(const std::wstring& str) const
  {
    return str;
  } // toStdWString

  default_string_adaptor() :
#if !(defined _MSC_VER) || !(_MSC_VER < 1300)
    loc_(std::locale(), new utf8ucs2codecvt()),
#else
    loc_(std::_Addfac(std::locale(), new utf8ucs2codecvt())),
#endif
    n_(), 
    w_()
  {
    n_.imbue(loc_);
    w_.imbue(loc_);
  } // default_string_adaptor 

private:
  std::locale loc_;
  mutable narrower n_;
  mutable widener w_;
}; // class default_string_adaptor

} // namespace SAX

#endif
// end of file
