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

template<class stringT>
class default_string_adaptor
{
public:
  typedef stringT string_type;
  typedef typename string_type::const_iterator const_iterator;
  typedef typename string_type::value_type value_type;
  typedef typename string_type::size_type size_type;
  static const size_type npos;

  template<class InputIterator> static string_type construct(InputIterator from, InputIterator to);
  static string_type construct(const value_type* s);

  static value_type convert_from_utf8(char c);
  static string_type construct_from_utf8(const char* str);
  static string_type construct_from_utf8(const char* str, int length);
#ifndef ARABICA_NO_WCHAR_T
  static string_type construct_from_utf16(const wchar_t* str);
  static string_type construct_from_utf16(const wchar_t* str, int length);
#endif

  // all these functions should operate as std::string member functions do
  static bool empty(const string_type& str);  
  static size_type find(const string_type& str, const string_type& what); 
  static string_type substr(const string_type& str, const size_type& offset);
  static string_type substr(const string_type& str, const size_type& offset, const size_type& count);
  static size_type length(const string_type& str);
  static void append(string_type& str, const string_type& a);
  static void insert(string_type& str, size_type offset, const string_type& a);
  static void replace(string_type& str, size_type offser, size_type count, const string_type& a);
  static const_iterator begin(const string_type& str);
  static const_iterator end(const string_type& str);

  // only used to constuct error strings - don't have to be highly efficient!
  static std::string asStdString(const string_type& str);
#ifndef ARABICA_NO_WCHAR_T
  static std::wstring asStdWString(const string_type& str);
#endif
}; // class default_string_adaptor

// specialize for std::string and std::wstring
template<>
class default_string_adaptor<std::string>
{
public:
  typedef std::string string_type;
  typedef std::string::const_iterator const_iterator;
  typedef std::string::iterator mutable_iterator;
  typedef std::string::value_type value_type;
  typedef std::string::size_type size_type;
  static const size_type npos = static_cast<size_type>(-1);

  template<class InputIterator> static std::string construct(InputIterator from, InputIterator to)
  {
    return std::string(from, to);
  } // construct

  static std::string construct(const value_type* s)
  {
    return std::string(s);
  } // construct

  static char convert_from_utf8(char c) { return c; }

  static std::string construct_from_utf8(const char* str)
  {
    return str ? std::string(str) : std::string();
  } // makeStringT
  static std::string construct_from_utf8(const char* str, int length)
  {
    return std::string(str, length);
  } // makeStringT
  static const std::string& asStdString(const std::string& str)
  {
    return str;
  } // toStdString

#ifndef ARABICA_NO_WCHAR_T
  typedef Arabica::convert::basic_iconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > widener;
  typedef Arabica::convert::basic_oconvertstream<wchar_t, std::char_traits<wchar_t>,
                               char, std::char_traits<char> > narrower;

  static std::string construct_from_utf16(const wchar_t* str)
  {
#ifndef ARABICA_VS6_WORKAROUND
    std::locale loc(std::locale(), new Arabica::convert::utf8ucs2codecvt());
#else
    std::locale loc(std::_Addfac(std::locale(), new Arabica::convert::utf8ucs2codecvt));
#endif
    narrower n;
    n.imbue(loc);

    n << str;
    return n.str();
  } // makeStringT

  static std::string construct_from_utf16(const wchar_t* str, int length) 
  {
#ifndef ARABICA_VS6_WORKAROUND
    std::locale loc(std::locale(), new Arabica::convert::utf8ucs2codecvt());
#else
    std::locale loc(std::_Addfac(std::locale(), new Arabica::convert::utf8ucs2codecvt));
#endif
    narrower n;
    n.imbue(loc);

    for(int i = 0; i < length; ++i)
      n << str[i];
    return n.str();
  } // construct_from_utf16

  static std::wstring asStdWString(const std::string& str) 
  {
#ifndef ARABICA_VS6_WORKAROUND
    std::locale loc(std::locale(), new Arabica::convert::utf8ucs2codecvt());
#else
    std::locale loc(std::_Addfac(std::locale(), new Arabica::convert::utf8ucs2codecvt));
#endif
    widener w;
    w.str(str);
    return w.str();
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

  static size_type find(const std::string& str, char what)
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
  static mutable_iterator begin(std::string& str) { return str.begin(); }
  static const_iterator end(const std::string& str) { return str.end(); }
  static mutable_iterator end(std::string& str) { return str.end(); }
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

  std::wstring construct_from_utf8(const char* str) const
  {
    if(str)
      w_.str(str);
    else
      w_.str("");
    return w_.str();
  } // makeStringT
  std::wstring construct_from_utf8(const char* str, int length) const
  {
    w_.str(std::string(str, length));
    return w_.str();
  } // makeStringT
  std::wstring construct_from_utf16(const wchar_t* str) const
  {
    return str ? std::wstring(str) : std::wstring();
  } // makeStringT
  std::wstring construct_from_utf16(const wchar_t* str, int length) const 
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
