#ifndef ARABICA_CONVERT_STREAM_H
#define ARABICA_CONVERT_STREAM_H
//////////////////////////////////////////////////////
//
// $Id$
//
//////////////////////////////////////////////////////
//
// basic_iconvertstream, basic_oconvertstream
//
// Written by Jez Higgins <jez@jezuk.co.uk>
// Copyright 1999-2005 Jez UK Ltd, http://www.jezuk.co.uk/
//
// Normal basic_stringstream do not apply the codecvt facet
// of their locale.  These two streams act exactly like
// basic_stringstream except that they do apply the imbued codecvt
// facet to their input (in the case of basic_iconvertstream) 
// or output (int the case of basic_oconvertstream).  
//
// This means you can to cool things like this
//
//  std::locale loc(std::_Addfac(std::locale(), new base64_codecvt));
//  converting_ostringstream os;
//  os.imbue(loc);
//
//  os << "stuff"; 
//     ...  lots more stuff streamed into os
//
//  std::cout << os.str() << std::endl;
//     os.str() contains the Base64 encoded byte sequence
//
// Decoding is just as simple.
//
//  std::locale loc(std::_Addfac(std::locale(), new base64_codecvt));
// 
//  converting_istringstream is;
//  is.imbue(loc);
//  is.str(a_base64_byte_stream);
//  std::cout << is.str();
//    ... is.str() is the decode byte stream, which can also be extracted 
//    ... using >> operators (is >> byte; etc)
//
////////////////////////////////////////////////////////////

#include <SAX/ArabicaConfig.hpp>
#include <locale>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace Arabica
{
namespace io
{

template<typename charT, typename traitsT>
class convertstreambuf_init
{
public:
  typedef std::basic_stringbuf<charT, traitsT> stringbufT;

  convertstreambuf_init(std::ios_base::openmode mode) :
    buf_(mode) 
  { 
  } // convertstreambuf_init

  stringbufT const* buf() const
  {
    return &buf_;
  } // buf()

  stringbufT* buf() 
  {
    return &buf_;
  } // buf()

private:
  stringbufT buf_;
}; // class convertstreambuf_init

template<typename charT, 
         typename traitsT = std::char_traits<charT>,
         typename fromCharT = charT,
         typename fromTraitsT = std::char_traits<fromCharT> >
class basic_iconvertstream : 
  private virtual convertstreambuf_init<charT, traitsT>,
  public std::basic_istream<charT, traitsT>
{
  typedef convertstreambuf_init<charT, traitsT> convertstreambuf_initT;
public:
  typedef std::basic_istream<charT, traitsT> istreamT;
  typedef typename convertstreambuf_initT::stringbufT stringbufT;
  typedef std::basic_string<charT, traitsT> stringT;
  typedef std::basic_string<fromCharT, fromTraitsT> fromStringT;

  explicit basic_iconvertstream(std::ios_base::openmode mode = std::ios_base::in) :
      convertstreambuf_initT(mode | std::ios_base::in),
      std::basic_istream<charT, traitsT>(convertstreambuf_initT::buf())
  { 
  } // basic_iconvertstream

  explicit basic_iconvertstream(const stringT& str, std::ios_base::openmode mode = std::ios_base::in) : 
    convertstreambuf_initT(mode | std::ios_base::in),
    std::basic_istream<charT, traitsT>(convertstreambuf_initT::buf())
  {
    str(str);
  } // basic_iconvertstream

  virtual ~basic_iconvertstream()
  {}

  stringbufT* rdbuf() const
  {
    return const_cast<stringbufT*>(convertstreambuf_initT::buf()); 
  } // rdbuf

  stringT str() const
  {
    return convertstreambuf_initT::buf()->str(); 
  } // str

  void str(const fromStringT& str)
  {
    // do conversion
    const std::codecvt<charT, fromCharT, typename traitsT::state_type>& cvt =
      std::use_facet<std::codecvt<charT, fromCharT, typename traitsT::state_type> >(this->getloc());

    if(cvt.always_noconv())
    {
      convertstreambuf_initT::buf()->str(no_conversion(str)); 
      return;
    }

    // we must do code conversion
    stringT converted;
    const fromCharT* from_next = str.data();
    typename std::codecvt_base::result r;
    typename traitsT::state_type state;

    do
    {
      charT* to_next;
      r = cvt.in(state, from_next, str.data() + str.length(), from_next, 
                 to_, to_ + toSize_, to_next);
      if(r == std::codecvt_base::noconv)
      {
        converted.append(no_conversion(str));
        break;
      }
      converted.append(to_, (to_next - to_));
    }
    while(r == std::codecvt_base::partial);

    // naughty! ignore (r == std::codecvt_base::error)
    convertstreambuf_initT::buf()->str(converted); 
  } // str

private:
  stringT no_conversion(const fromStringT& str)
  {
    stringT dest;

    std::back_insert_iterator<stringT> id(dest);
    for(typename fromStringT::const_iterator i = str.begin(); i != str.end(); ++i, ++id)
      *id = static_cast<charT>(*i);

    return dest;
  } // no_conversion

  static const int toSize_ = 4096;
  charT to_[toSize_];
}; // basic_iconvertstream

template<typename charT, 
         typename traitsT = std::char_traits<charT>,
         typename toCharT = charT,
         typename toTraitsT = std::char_traits<toCharT> >
class basic_oconvertstream : 
  private virtual convertstreambuf_init<charT, traitsT>,
  public std::basic_ostream<charT, traitsT> 
{
  typedef convertstreambuf_init<charT, traitsT> convertstreambuf_initT;
public:
  typedef std::basic_ostream<charT, traitsT> ostreamT;
  typedef typename convertstreambuf_initT::stringbufT stringbufT;
  typedef std::basic_string<charT, traitsT> stringT;
  typedef std::basic_string<toCharT, toTraitsT> toStringT;

  explicit basic_oconvertstream(std::ios_base::openmode mode = std::ios_base::out) :
      convertstreambuf_initT(mode | std::ios_base::out),
      std::basic_ostream<charT, traitsT>(convertstreambuf_initT::buf())
  { 
  } // basic_oconvertstream

  explicit basic_oconvertstream(const stringT& str, std::ios_base::openmode mode = std::ios_base::out) :
      convertstreambuf_initT(mode | std::ios_base::out),
      std::basic_ostream<charT, traitsT>(convertstreambuf_initT::buf())
  { 
    convertstreambuf_initT::buf()->str(str);
  } // basic_oconvertstream

  virtual ~basic_oconvertstream()
  {}

  stringbufT* rdbuf() const
  {
    return const_cast<stringbufT*>(convertstreambuf_initT::buf()); 
  } // rdbuf

  toStringT str()
  {
    toStringT out;
    stringT newstuff(convertstreambuf_initT::buf()->str()); 

    if(newstuff.length() == 0)
      return out;

    // convert it here
    const std::codecvt<charT, toCharT, typename traitsT::state_type>& cvt =
      std::use_facet<std::codecvt<charT, toCharT, typename traitsT::state_type> >(this->getloc());

    if(cvt.always_noconv())
      out.append(no_conversion(newstuff));
    else
    {
      // we must do code conversion
      const charT* from_next = newstuff.data();
      typename std::codecvt_base::result r;
      typename traitsT::state_type state;

      do
      {
        toCharT* to_next;
        r = cvt.out(state, from_next, newstuff.data() + newstuff.length(), from_next, 
                    to_, to_ + toSize_, to_next);
        if(r == std::codecvt_base::noconv)
        {
          out.append(no_conversion(newstuff));
          break;
        }
        out.append(to_, (to_next - to_));
      }
      while(r == std::codecvt_base::partial);
      // naughty! ignore (r == std::codecvt_base::error)
    } // if(cvt.always_noconv())

    convertstreambuf_initT::buf()->str(stringT());

    return out;
  } // str

  void str(const stringT& str)
  {
    convertstreambuf_initT::buf()->str(str); 
  } // str

private:
  toStringT no_conversion(const stringT& str)
  {
    toStringT dest;

    std::back_insert_iterator<toStringT> id(dest);
    for(typename stringT::const_iterator i = str.begin(); i != str.end(); ++i, ++id)
      *id = static_cast<toCharT>(*i);

    return dest;
  } // no_conversion

  static const int toSize_ = 4096;
  toCharT to_[toSize_];
}; // basic_oconvertstream

typedef basic_iconvertstream<char> converting_istringstream;
typedef basic_oconvertstream<char> converting_ostringstream;
#ifndef ARABICA_NO_WSTRING_T
typedef basic_iconvertstream<wchar_t> converting_iwstringstream;
typedef basic_oconvertstream<wchar_t> converting_owstringstream;
#endif

} // namespace io
} // namespace Arabica
#endif
