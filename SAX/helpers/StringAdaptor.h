#ifndef ARABICA_STRING_ADAPTOR_H
#define ARABICA_STRING_ADAPTOR_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.h>
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
#ifndef ARABICA_NO_WCHAR_T
  stringT makeStringT(const wchar_t* str) const;
  stringT makeStringT(const wchar_t* str, int length) const;
#endif

  // only used to constuct error strings - don't have to be highly efficient!
  std::string asStdString(const stringT& str) const;
#ifndef ARABICA_NO_WCHAR_T
  std::wstring asStdWString(const stringT& str) const;
#endif
}; // class default_string_maker

// specialize for std::string and std::wstring
template<>
class default_string_adaptor<std::string>
{
public:
  typedef std::string stringT;
  typedef std::string::value_type value_type;

  char makeValueT(char c) const { return c; }

  std::string makeStringT(const char* str) const
  {
    return str ? std::string(str) : std::string();
  } // makeStringT
  std::string makeStringT(const char* str, int length) const
  {
    return std::string(str, length);
  } // makeStringT
  const std::string& asStdString(const std::string& str) const
  {
    return str;
  } // toStdString

#ifndef ARABICA_NO_WCHAR_T
  typedef Arabica::convert::basic_iconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > widener;
  typedef Arabica::convert::basic_oconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > narrower;

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
  std::wstring asStdWString(const std::string& str) const
  {
    w_.str(str);
    return w_.str();
  } // toStdWString
#endif

#ifndef ARABICA_NO_WCHAR_T
  default_string_adaptor() :
#ifndef ARABICA_VS6_WORKAROUND
    loc_(std::locale(), new Arabica::convert::utf8ucs2codecvt()),
#else
    loc_(std::_Addfac(std::locale(), new Arabica::convert::utf8ucs2codecvt)),
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
#else
  default_string_adaptor() { }
#endif
}; // class default_string_adaptor

#ifndef ARABICA_NO_WCHAR_T
template<>
class default_string_adaptor<std::wstring>
{
  typedef Arabica::convert::basic_iconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > widener;
  typedef Arabica::convert::basic_oconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > narrower;
public:
  typedef std::wstring stringT;
  typedef std::wstring::value_type value_type;

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
#ifndef ARABICA_VS6_WORKAROUND
    loc_(std::locale(), new Arabica::convert::utf8ucs2codecvt()),
#else
    loc_(std::_Addfac(std::locale(), new Arabica::convert::utf8ucs2codecvt())),
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
#endif // ARABICA_NO_WCHAR_T

} // namespace SAX

#endif
// end of file
