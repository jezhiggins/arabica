#ifndef ARABICA_UTILS_STRING_ADAPTOR_H
#define ARABICA_UTILS_STRING_ADAPTOR_H
/*
 * $Id$
 */

#include <SAX/ArabicaConfig.h>
#include <string>
#include <Utils/convertstream.h>
#include <Utils/utf8ucs2codecvt.h>

namespace Arabica
{

template<class string_type>
class default_string_adaptor
{
public:
  typedef string_type stringT;
  typedef typename stringT::const_iterator const_iterator;
  typedef typename stringT::value_type value_type;
  typedef typename stringT::size_type size_type;
  static const size_type npos;

  value_type makeValueT(char c) const;
  stringT makeStringT(const char* str) const;
  stringT makeStringT(const char* str, int length) const;
  stringT makeStringT(const_iterator s, const_iterator e) const;
#ifndef ARABICA_NO_WCHAR_T
  stringT makeStringT(const wchar_t* str) const;
  stringT makeStringT(const wchar_t* str, int length) const;
#endif

  static bool empty(const string_type& str);  // as std::string::empty
  static size_type find(const string_type& str, const string_type& what); // return npos if not found, otherwise index
  static string_type substr(const string_type& str, const size_type& offset);
  static string_type substr(const string_type& str, const size_type& offset, const size_type& count);
  static size_type length(const string_type& str);
  static void append(string_type& str, const string_type& a);
  static void insert(string_type& str, size_type offset, const string_type& a);
  static void replace(string_type& str, size_type offser, size_type count, const string_type& a);
  static const_iterator begin(const string_type& str);
  static const_iterator end(const string_type& str);

  // only used to constuct error strings - don't have to be highly efficient!
  std::string asStdString(const stringT& str);
#ifndef ARABICA_NO_WCHAR_T
  std::wstring asStdWString(const stringT& str);
#endif
}; // class default_string_maker

// specialize for std::string and std::wstring
template<>
class default_string_adaptor<std::string>
{
public:
  typedef std::string stringT;
  typedef std::string::const_iterator const_iterator;
  typedef std::string::value_type value_type;
  typedef std::string::size_type size_type;
  static const size_type npos = static_cast<size_type>(-1);

  char makeValueT(char c) const { return c; }

  std::string makeStringT(const char* str) const
  {
    return str ? std::string(str) : std::string();
  } // makeStringT
  std::string makeStringT(const char* str, int length) const
  {
    return std::string(str, length);
  } // makeStringT
  std::string makeString(const const_iterator& first, const const_iterator& last) const
  {
    return std::string(first, last);
  } // 
  const std::string& asStdString(const std::string& str) const
  {
    return str;
  } // toStdString

#ifndef ARABICA_NO_WCHAR_T
  typedef Arabica::convert::basic_iconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > widener;
  typedef Arabica::convert::basic_oconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > narrower;

  std::string makeStringT(const wchar_t* str)
  {
    std::wstring s;
    if(str)
      s = str;
    n_.str(s);
    return n_.str();
  } // makeStringT
  std::string makeStringT(const wchar_t* str, int length) 
  {
    n_.str(std::wstring(str, length));
    return n_.str();
  } // makeStringT
  std::wstring asStdWString(const std::string& str) 
  {
    w_.str(str);
    return w_.str();
  } // toStdWString
#endif

  static bool empty(const std::string& str)
  {
    return str.empty();
  } // empty

  static size_type find(const std::string& str, const std::string& what)
  {
    return str.find(what);
  } // find

  static std::string substr(const std::string& str, const size_type& offset)
  {
    return str.substr(offset);
  } // substr

  static std::string substr(const std::string& str, const size_type& offset, const size_type& count)
  {
    return str.substr(offset, count);
  } // substr

  static size_type length(const std::string& str)
  {
    return str.length(); // TODO - fix me for utf8
  } // length

  static void append(std::string& str, const std::string& a)
  {
    str.append(a);
  } // append

  static void insert(std::string& str, size_type offset, const std::string& a)
  {
    str.insert(offset, a);
  } // insert

  static void replace(std::string& str, size_type offset, size_type count, const std::string& a)
  {
    str.replace(offset, count, a);
  } // replace

  static const_iterator begin(const std::string& str) { return str.begin(); }
  static const_iterator end(const std::string& str) { return str.end(); }

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
  typedef std::wstring::const_iterator const_iterator;
  typedef std::wstring::value_type value_type;
  typedef std::wstring::size_type size_type;
  static const size_type npos = static_cast<size_type>(-1);

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
  std::wstring makeStringT(const const_iterator& first, const const_iterator& last) const
  {
    return std::wstring(first, last);
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

  static bool empty(const std::wstring& str)
  {
    return str.empty();
  } // empty

  static size_type find(const std::wstring& str, const std::wstring& what)
  {
    return str.find(what);
  } // find

  static std::wstring substr(const std::wstring& str, const size_type& offset)
  {
    return str.substr(offset);
  } // substr

  static std::wstring substr(const std::wstring& str, const size_type& offset, const size_type& count)
  {
    return str.substr(offset, count);
  } // substr

  static size_type length(const std::string& str)
  {
    return str.length(); // TODO - fix me for utf8
  } // length

  static void append(std::wstring& str, const std::wstring& a)
  {
    str.append(a);
  } // append

  static void insert(std::wstring& str, size_type offset, const std::wstring& a)
  {
    str.insert(offset, a);
  } // insert

  static void replace(std::wstring& str, size_type offset, size_type count, const std::wstring& a)
  {
    str.replace(offset, count, a);
  } // replace

  static const_iterator begin(const std::wstring& str) { return str.begin(); }
  static const_iterator end(const std::wstring& str) { return str.end(); }

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

} // namespace Arabica

#endif
// end of file
