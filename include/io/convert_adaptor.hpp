#ifndef ARABICA_CONVERT_ADAPTOR_H
#define ARABICA_CONVERT_ADAPTOR_H
//////////////////////////////////////////////////////
//
// $Id$
// Written by Jez Higgins <jez@jezuk.co.uk>
// Copyright 1999-2003 Jez UK Ltd, http://www.jezuk.co.uk/
//
// convert_adaptor is a stream that wraps around another stream.  This
// may not seem like a big deal, but convert_adaptor applies codecvt
// facets along the way.  This allows you to apply encryption or 
// decryption (or any other transcoding) transparently.  It can 
// also adapt wchar_t streams to char streams, or vice versa, allowing
// you to write std::wstrings out as UTF-8 chars to a file, for instance.
//////////////////////////////////////////////////////
#include <locale>
#include <istream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <cstring>

#include <SAX/ArabicaConfig.hpp>
#include <Arabica/mbstate.hpp>

namespace Arabica
{
namespace io
{

template<typename charT, 
         typename traitsT = std::char_traits<charT>,
         typename externalCharT = charT,
         typename externalTraitsT = std::char_traits<externalCharT> >
class convert_bufadaptor : public std::basic_streambuf<charT, traitsT>
{
  public:
    typedef typename traitsT::int_type int_type;
    typedef std::basic_streambuf<externalCharT, externalTraitsT> externalStreambufT;
    typedef std::basic_streambuf<charT, traitsT> streambufT;

    explicit convert_bufadaptor(externalStreambufT& externalbuf) : externalbuf_(&externalbuf), inEof_(false) { }
    virtual ~convert_bufadaptor() { }
  
    void set_buffer(externalStreambufT& externalbuf) { externalbuf_ = &externalbuf; inEof_ = false; }

  protected:
    virtual int_type overflow(int_type c = traitsT::eof());
    virtual int sync();
    virtual int_type underflow();
    virtual int_type pbackfail(int_type c);

  private:
    typedef typename externalTraitsT::int_type external_int_type;
    typedef typename traitsT::state_type state_t;

    externalStreambufT* externalbuf_;
    std::vector<charT> outBuffer_;
    state_t outState_;
    std::vector<charT> inBuffer_;
    state_t inState_;
    bool inEof_;

    void growOutBuffer();
    bool flushOut();
    void growInBuffer();
    std::streamsize readIn();

    static const std::streamsize bufferSize_;
    static const std::streamsize pbSize_;
}; // convert_bufadaptor

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
const std::streamsize convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::bufferSize_ = 1024;
template<class charT, class traitsT, class externalCharT, class externalTraitsT>
const std::streamsize convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::pbSize_ = 4;
  // why 4? both Josuttis and Langer&Kreft use 4.

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
typename convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::int_type convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::overflow(int_type c)
{
  if(traitsT::eq_int_type(traitsT::eof(), c))
    return traitsT::not_eof(c);

  growOutBuffer();
  sputc(traitsT::to_char_type(c));

  return traitsT::not_eof(c);
} // overflow

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
int convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::sync()
{
  return flushOut() ? 0 : -1;
} // sync

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
typename convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::int_type convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::underflow()
{
  if(streambufT::gptr() != 0 && streambufT::gptr() < streambufT::egptr())
    return (traitsT::to_int_type(*streambufT::gptr()));

  if(!readIn())
    return traitsT::eof();
    
  return traitsT::to_int_type(*streambufT::gptr());
} // underflow

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
typename convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::int_type convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::pbackfail(int_type c)
{
  if(streambufT::gptr() == streambufT::eback())
    return traitsT::eof();

  streambufT::gbump(-1);
  if(!traitsT::eq_int_type(c, traitsT::eof()))
    *(streambufT::gptr()) = traitsT::to_char_type(c);
  return traitsT::not_eof(c);
} // pbackfail

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
void convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::growOutBuffer()
{
  size_t oldsize = outBuffer_.capacity();
  size_t newsize = (oldsize ? oldsize*2 : bufferSize_);
  outBuffer_.resize(newsize);
  setp(&outBuffer_[0] + oldsize, &outBuffer_[0] + outBuffer_.capacity());
} // growOutBuffer

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
void convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::growInBuffer()
{
  size_t oldsize = inBuffer_.capacity();
  size_t newsize = (oldsize ? oldsize*2 : bufferSize_) + pbSize_;
  inBuffer_.resize(newsize);
} // growInBuffer

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
bool convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::flushOut()
{
  size_t length = streambufT::pptr() - &outBuffer_[0];
  if(!length)
    return true;

  bool ok(true);
  const std::codecvt<charT, externalCharT, state_t>& cvt =
      std::use_facet<std::codecvt<charT, externalCharT, std::mbstate_t> >(this->getloc());

  if(cvt.always_noconv())
    std::copy(&outBuffer_[0], &outBuffer_[0] + length, std::ostreambuf_iterator<externalCharT>(externalbuf_));
  else
  {
    // we must do code conversion
    length += cvt.max_length(); // add a little 
    std::vector<externalCharT> to(length);
    const charT* from_next = &(outBuffer_[0]);
    std::codecvt_base::result r;

    do
    {
      externalCharT* to_next;
      r = cvt.out(outState_, from_next, streambufT::pptr(), from_next, 
                  &to[0], &to[0]+length, to_next);

      if(r == std::codecvt_base::noconv)
      {
        std::copy(&outBuffer_[0], &outBuffer_[0] + length, std::ostreambuf_iterator<externalCharT>(externalbuf_));
        break;
      }
      std::copy(&to[0], to_next, std::ostreambuf_iterator<externalCharT>(externalbuf_));
    }
    while(r == std::codecvt_base::partial);

    ok = ok ? (r != std::codecvt_base::error) : false;
  } // if(cvt.always_noconv())
 
  if(ok)
    setp(&outBuffer_[0], &outBuffer_[0] + outBuffer_.capacity());

  return ok;
} // flushOut

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
std::streamsize convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::readIn()
{
  if(!inBuffer_.capacity())
    growInBuffer();

  size_t pbCount = std::min<size_t>(streambufT::gptr() - streambufT::eback(), pbSize_);
  memcpy(&(inBuffer_[0]) + (pbSize_-pbCount)*sizeof(charT),
         streambufT::gptr() - pbCount*sizeof(charT),
         pbCount*sizeof(charT));

  const std::codecvt<charT, externalCharT, state_t>& cvt =
      std::use_facet<std::codecvt<charT, externalCharT, std::mbstate_t> >(this->getloc());

  externalCharT from[1024];

  std::streamsize res = 0;
  if(!inEof_)
  {
    external_int_type ec = externalbuf_->sgetc();
    while((!externalTraitsT::eq_int_type(externalTraitsT::eof(), ec)) && (res != bufferSize_))
    {
      from[res++] = static_cast<externalCharT>(ec);
      ec = externalbuf_->snextc();
    }
    inEof_ = (externalTraitsT::eq_int_type(externalTraitsT::eof(), ec));
  } // if ...

  std::streamsize converted = 0;
  if(res > 0)
  {
    std::codecvt_base::result r;
    const externalCharT* from_next = from;
    do
    {
      // can't cache this as may reallocate buffer
      charT* const to = &(inBuffer_[0])+pbSize_;
      charT* const to_end = &(inBuffer_[0]) + inBuffer_.capacity() - pbSize_;
      charT* to_next;

      externalCharT* const from_end = from + res;
      
      r = cvt.in(inState_, from_next, from_end, from_next,
                 to + converted, to_end, to_next);

      if(r == std::codecvt_base::noconv)
      {
        memcpy(&(inBuffer_[0])+pbSize_, from, res);
        converted = res;
      }
      else
        converted += static_cast<std::streamsize>(to_next - (to + converted));

      if(r == std::codecvt_base::partial)
      {
        // haven't done everything
        if(to_next == to_end)
          growInBuffer();  // need more room!
        else
        {
          int shortfall = (from + res) - from_next;
          memcpy(from, from_next, shortfall);
          res = externalbuf_->sgetn(from + shortfall, static_cast<std::streamsize>(bufferSize_ - shortfall));
          from_next = &from[0];
          if(res == 0) // oh dear
            break; // let's bail!
          res += shortfall;
        }
      } // if(r == std::codecvt_base::partial)
    }
    while(r == std::codecvt_base::partial);

    if(r == std::codecvt_base::error)
    {
      // couldn't convert - let's bail
      return 0;
    } // if(r == std::codecvt_base::error)
  }

  setg(&(inBuffer_[0]) + (pbSize_-pbCount), &(inBuffer_[0])+pbSize_, &(inBuffer_[0])+pbSize_+converted);

  return static_cast<int_type>(res);
} // readIn

////////////////////////////////////////////////////
// iconvert_adaptor
template<typename charT, typename traitsT, typename externalCharT, typename externalTraitsT>
class convert_adaptor_buffer
{
  protected:
    typedef std::basic_streambuf<externalCharT, externalTraitsT> externalStreambufT;

    explicit convert_adaptor_buffer(externalStreambufT& externalbuf) : bufadaptor_(externalbuf) { }

    convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT> bufadaptor_;
}; // convert_adaptor_buffer

template<typename charT, 
         typename traitsT = std::char_traits<charT>,
         typename fromCharT = charT,
         typename fromTraitsT = std::char_traits<fromCharT> >
class iconvert_adaptor : private convert_adaptor_buffer<charT, traitsT, fromCharT, fromTraitsT>,
                         public std::basic_istream<charT, traitsT>
{
  typedef std::basic_istream<charT, traitsT> baseStreamT;
  typedef std::basic_istream<fromCharT, fromTraitsT> fromStreamT;
  typedef convert_adaptor_buffer<charT, traitsT, fromCharT, fromTraitsT> baseBufT;
  protected:
    using baseBufT::bufadaptor_;
  public:
    explicit iconvert_adaptor(fromStreamT& fromstream) :
      baseBufT(*(fromstream.rdbuf())),
      baseStreamT(&bufadaptor_)
      {
      } // iconvert_adaptor

    virtual ~iconvert_adaptor() { } 

    baseBufT* rdbuf() const 
    { 
      return const_cast<baseBufT*>(&bufadaptor_); 
    } // rdbuf

    void set_stream(fromStreamT& fromStream) { bufadaptor_.set_buffer(*fromStream.rdbuf()); }
}; // class iconvert_adaptor

////////////////////////////////////////////////////////
// oconvert_adaptor
template<typename charT,
         typename traitsT = std::char_traits<charT>,
         typename toCharT = charT,
         typename toTraitsT = std::char_traits<toCharT> >
class oconvert_adaptor : private convert_adaptor_buffer<charT, traitsT, toCharT, toTraitsT>,
                         public std::basic_ostream<charT, traitsT>
{
  typedef std::basic_ostream<charT, traitsT> baseStreamT;
  typedef std::basic_ostream<toCharT, toTraitsT> toStreamT;
  typedef convert_adaptor_buffer<charT, traitsT, toCharT, toTraitsT> baseBufT;
  protected:
    using baseBufT::bufadaptor_;
  public:
    explicit oconvert_adaptor(toStreamT &toStream) :
      baseBufT(*(toStream.rdbuf())),
      baseStreamT(&bufadaptor_)
      {
      } // oconvert_adaptor

    virtual ~oconvert_adaptor() 
    {
      baseStreamT::flush(); 
    } // ~oconvert_adaptor

    convert_bufadaptor<charT, traitsT>* rdbuf() const
    {
      return const_cast<convert_bufadaptor<charT, traitsT, toCharT, toTraitsT>*>(&bufadaptor_); 
    } // rdbuf

    void set_stream(toStreamT& toStream) { bufadaptor_.set_buffer(*toStream.rdbuf()); }
}; // class oconvert_adaptor

} // namespace io
} // namespace Arabica
#endif
