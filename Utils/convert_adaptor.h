#ifndef ARABICA_CONVERT_ADAPTOR_H
#define ARABICA_CONVERT_ADAPTOR_H
//////////////////////////////////////////////////////
//
// $Id$
//
//////////////////////////////////////////////////////
#include <locale>
#include <istream>
#include <ostream>
#include <vector>
#include <algorithm>
#if!(_MSC_VER < 1300)
#include <minmax.h>
#endif

template<typename charT, 
         typename traitsT = std::char_traits<charT>,
         typename externalCharT = charT,
         typename externalTraitsT = std::char_traits<externalCharT> >
class convert_bufadaptor : public std::basic_streambuf<charT, traitsT>
{
  public:
    typedef typename traitsT::int_type int_type;
    typedef std::basic_streambuf<externalCharT, externalTraitsT> fromStreambufT;

    convert_bufadaptor(fromStreambufT& frombuf) : externalbuf_(frombuf) { }
    virtual ~convert_bufadaptor() { }

  protected:
    virtual int_type overflow(int_type c = traitsT::eof());
    virtual int sync();
    virtual int_type underflow();
    virtual int_type pbackfail(int_type c);

  private:
    typedef typename traitsT::state_type state_t;

    fromStreambufT& externalbuf_;
    std::vector<charT> outBuffer_;
    state_t outState_;
    std::vector<charT> inBuffer_;
    state_t inState_;

    void growOutBuffer();
    bool flushOut();
    void growInBuffer();
    int_type readIn();

    static const size_t bufferSize_;
    static const size_t pbSize_;
}; // convert_bufadaptor

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
const size_t convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::bufferSize_ = 1024;
template<class charT, class traitsT, class externalCharT, class externalTraitsT>
const size_t convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::pbSize_ = 4;
  // why 4? both Josuttis and Langer&Kreft use 4.

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::int_type convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::overflow(convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::int_type c)
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
convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::int_type convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::underflow()
{
	if(gptr() != 0 && gptr() < egptr())
	  return (traitsT::to_int_type(*gptr()));

  size_t length = readIn();
  if(!length)
    return traitsT::eof();
    
  return traitsT::to_int_type(*gptr());
} // underflow

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::int_type convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::pbackfail(int_type c)
{
  if(gptr() == eback())
    return traitsT::eof();

  gbump(-1);
  if(!traitsT::eq_int_type(c, traitsT::eof()))
    *(gptr()) = traitsT::to_char_type(c);
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
  size_t length = pptr() - &outBuffer_[0];
  if(!length)
    return true;

  bool ok(true);
  const std::codecvt<charT, char, state_t>& cvt =
#if!(_MSC_VER < 1300)
      std::use_facet<std::codecvt<charT, char, typename traitsT::state_type> >(this->getloc());
#else
      std::use_facet(this->getloc(), (std::codecvt<charT, char, traitsT::state_type>*)0, true);
#endif

  if(cvt.always_noconv())
    std::copy(&outBuffer_[0], &outBuffer_[0] + length, std::ostreambuf_iterator<externalCharT>(&externalbuf_));
  else
  {
    // we must do code conversion
    std::vector<externalCharT> to(length);
    const charT* from_next = outBuffer_.begin();
    std::codecvt_base::result r;

    do
    {
      externalCharT* to_next;
      r = cvt.out(outState_, from_next, pptr(), from_next,
                  &to[0], &to[0]+length, to_next);

      if(r == std::codecvt_base::noconv)
      {
        std::copy(&outBuffer_[0], &outBuffer_[0] + length, std::ostreambuf_iterator<externalCharT>(&externalbuf_));
        break;
      }
      std::copy(&to[0], to_next, std::ostreambuf_iterator<externalCharT>(&externalbuf_));
    }
    while(r == std::codecvt_base::partial);

    ok = ok ? (r != std::codecvt_base::error) : false;
  } // if(cvt.always_noconv())
 
  if(ok)
    setp(&outBuffer_[0], &outBuffer_[0] + outBuffer_.capacity());

  return ok;
} // flushOut

template<class charT, class traitsT, class externalCharT, class externalTraitsT>
convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::int_type convert_bufadaptor<charT, traitsT, externalCharT, externalTraitsT>::readIn()
{
  if(!inBuffer_.capacity())
    growInBuffer();

#if!(_MSC_VER < 1300)
  size_t pbCount = std::min<int>(gptr() - eback(), pbSize_);
#else
  size_t pbCount = min(gptr() - eback(), pbSize_);
#endif
  memcpy(&(inBuffer_[0]) + (pbSize_-pbCount)*sizeof(charT),
         gptr() - pbCount*sizeof(charT),
         pbCount*sizeof(charT));

  const std::codecvt<charT, char, state_t>& cvt =
#if!(_MSC_VER < 1300)
      std::use_facet<std::codecvt<charT, char, typename traitsT::state_type> >(this->getloc());
#else
      std::use_facet(this->getloc(), (std::codecvt<charT, char, traitsT::state_type>*)0, true);
#endif

  std::vector<externalCharT> from(inBuffer_.capacity());
  int res = externalbuf_.sgetn(&(from[0]), from.capacity());
  if(res > 0)
  {
    std::codecvt_base::result r;
    do
    {
      const externalCharT* from_next;
      charT* to_next;
      r = cvt.in(inState_, &(from[0]), &(from[0]) + res, from_next,
                 &(inBuffer_[0])+pbSize_, &(inBuffer_[0]) + inBuffer_.capacity() - pbSize_, to_next);

      if(r == std::codecvt_base::noconv)
        memcpy(&(inBuffer_[0])+pbSize_, &from[0], res);
      else
        res = to_next - (&(inBuffer_[0])+pbSize_);
      if(r == std::codecvt_base::partial)
        growInBuffer();
    }
    while(r == std::codecvt_base::partial);

    if(r == std::codecvt_base::error)
    {
      // couldn't convert - let's bail
      return 0;
    } // if(r == std::codecvt_base::error)
  }

  setg(&(inBuffer_[0]) + (pbSize_-pbCount), &(inBuffer_[0])+pbSize_, &(inBuffer_[0])+pbSize_+res);

  return res;
} // readIn

////////////////////////////////////////////////////
// iconvert_adaptor
template<typename charT, 
         typename traitsT = std::char_traits<charT>,
         typename fromCharT = charT,
         typename fromTraitsT = std::char_traits<fromCharT> >
class iconvert_adaptor : public std::basic_istream<charT, traitsT>
{
  typedef std::basic_istream<fromCharT, fromTraitsT> fromStreamT;
  public:
    explicit iconvert_adaptor(fromStreamT& fromstream) :
      std::basic_istream<charT, traitsT>(&bufadaptor_),
      bufadaptor_(*(fromstream.rdbuf()))
      {
      } // iconvert_adaptor

    virtual ~iconvert_adaptor() { } 

    convert_bufadaptor<charT,traitsT>* rdbuf() const 
    { 
      return const_cast<convert_bufadaptor<charT, traitsT, fromCharT, fromTraitsT>*>(&bufadaptor_); 
    } // rdbuf

  private:
    convert_bufadaptor<charT, traitsT, fromCharT, fromTraitsT> bufadaptor_;
}; // class iconvert_adaptor

#endif
