#ifndef basic_socketstreamH
#define basic_socketstreamH
///////////////////////////////////////////////////////////////////////
//
// socketstream.h 
// 
// Written by Jez Higgins <jez@jezuk.co.uk>
// 
// Copyright 1999-2000 Jez UK Ltd, http://www.jezuk.co.uk/
//
// Permission is granted to anyone to use this software for any purpose
// on any computer system, and redistribute it freely, subject to the 
// following restrictions:
//
// 1. This softwre is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// 2. The origin of this software must not be misrepresented, either by
//    explicit claim or by omission.
// 
// 3. Altered version must be plainly marked as such, and must not be 
//    misrepresented as being the original software.
//
// 4. If this software is used in any software which is released under
//    the GNU General Public Licence (GPL), then the terms of that 
//    licence shall supercede any condition above with which it is 
//    incompatible.
//
///////////////////////////////////////////////////////////////////////
// $Id$
///////////////////////////////////////////////////////////////////////

#ifndef _MSC_VER
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#else
#include <winsock.h>
#endif
#include <streambuf>
#include <algorithm>
#include <vector>
#include <cstdlib>

#ifndef INADDR_NONE
#  define INADDR_NONE             ((in_addr_t) -1)
#endif

///////////////////////////////////////////////////////////
// basic_socketbuf declaration
template<class charT, class traitsT>
class basic_socketbuf : public std::basic_streambuf<charT, traitsT>
{
  public:
    typedef typename traitsT::int_type int_type;

    basic_socketbuf();
    virtual ~basic_socketbuf();

    bool is_open() const;

    basic_socketbuf<charT, traitsT>* open(const char* hostname, unsigned short port);
    basic_socketbuf<charT, traitsT>* close();

  protected:
    virtual int_type overflow(int_type c = traitsT::eof());
    virtual int sync();
    virtual int_type underflow();
    virtual int_type pbackfail(int_type c);

  private:
    typedef typename traitsT::state_type state_t;

    int sock_;
    std::vector<charT> outBuffer_;
    state_t outState_;
    std::vector<charT> inBuffer_;
    state_t inState_;

    void growOutBuffer();
    bool writeSocket();
    void growInBuffer();
    int readSocket();
    int closeSocket(int sock) const;

    static const size_t bufferSize_;
    static const size_t pbSize_;

#ifndef _MSC_VER
    static const int INVALID_SOCKET;
    static const int SOCKET_ERROR;
#endif
}; // class basic_socketbuf

template<class charT, class traitsT>
const size_t basic_socketbuf<charT, traitsT>::bufferSize_ = 1024;
template<class charT, class traitsT>
const size_t basic_socketbuf<charT, traitsT>::pbSize_ = 4;
  // why 4? both Josuttis and Langer&Kreft use 4.
#ifndef _MSC_VER
template<class charT, class traitsT>
const int basic_socketbuf<charT, traitsT>::INVALID_SOCKET = -1;
template<class charT, class traitsT>
const int basic_socketbuf<charT, traitsT>::SOCKET_ERROR = -1;
#endif
typedef basic_socketbuf<char, std::char_traits<char> > socketbuf;
typedef basic_socketbuf<wchar_t, std::char_traits<wchar_t> > wsocketbuf;

///////////////////////////////////////////////////////////
// basic_socketbuf definition
template<class charT, class traitsT>
basic_socketbuf<charT, traitsT>::basic_socketbuf()
     : std::basic_streambuf<charT, traitsT>(),
       sock_(INVALID_SOCKET),
       outBuffer_(0),
       inBuffer_(0)
{
//  outState_ = 0;
//  inState_ = 0;

  setp(0, 0);
  setg(0, 0, 0);
} // basic_socketbuf

template<class charT, class traitsT>
basic_socketbuf<charT,traitsT>::~basic_socketbuf()
{
  if(is_open())
  {
    sync();
    closeSocket(sock_);
  } // if(is_open())
} // ~basic_socketbuf

template<class charT, class traitsT>
bool basic_socketbuf<charT ,traitsT>::is_open() const
{
  return (sock_ != INVALID_SOCKET);
} // is_open

template<class charT, class traitsT>
basic_socketbuf<charT, traitsT>* basic_socketbuf<charT, traitsT>::open(const char* hostname,
                                                  unsigned short port)
{
  // already open? and crappy data
  if((sock_ != INVALID_SOCKET) ||
     (hostname == 0) ||
     (strlen(hostname) == 0))
      return 0;

  // set up address
  sockaddr_in sockAddr;
  memset(&sockAddr, 0, sizeof(sockAddr));

  sockAddr.sin_family = AF_INET;
  sockAddr.sin_addr.s_addr = inet_addr(hostname);
  if(sockAddr.sin_addr.s_addr == INADDR_NONE)
  {
    hostent* host = gethostbyname(hostname);
    if(!host)
      return 0;

    sockAddr.sin_addr.s_addr =
                       reinterpret_cast<in_addr*>(host->h_addr)->s_addr;
  } // if(sockAddr.sin_addr.s_addr == INADDR_NONE)
  sockAddr.sin_port = htons(port);

  // connect
  int tmpsock = socket(AF_INET, SOCK_STREAM, 0);
  if(tmpsock == INVALID_SOCKET)
    return 0;
  if(connect(tmpsock, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockaddr_in)) != 0)
  {
    closeSocket(tmpsock);
    return 0;
  }

  // hurray, we've connected so initialise everything else we need to
  sock_ = tmpsock;

  return this;
} // open

template<class charT, class traitsT>
basic_socketbuf<charT, traitsT>* basic_socketbuf<charT, traitsT>::close()
{
  if(!is_open())
    return 0;

  if(closeSocket(sock_) == SOCKET_ERROR)
    return 0;

  sock_ = INVALID_SOCKET;
  setg(0,0,0);

  return this;
} // close;

template<class charT, class traitsT>
typename basic_socketbuf<charT, traitsT>::int_type basic_socketbuf<charT, traitsT>::overflow(typename basic_socketbuf<charT, traitsT>::int_type c)
{
  if(traitsT::eq_int_type(traitsT::eof(), c))
    return traitsT::not_eof(c);
  if(!is_open())
    return traitsT::eof();

  growOutBuffer();
  sputc(traitsT::to_char_type(c));

  return traitsT::not_eof(c);
} // overflow

template<class charT, class traitsT>
int basic_socketbuf<charT, traitsT>::sync()
{
  return writeSocket() ? 0 : -1;
} // sync

template<class charT, class traitsT>
typename basic_socketbuf<charT, traitsT>::int_type basic_socketbuf<charT, traitsT>::underflow()
{
  if(!is_open())
    return traitsT::eof();
	if(gptr() != 0 && gptr() < egptr())
	  return (traitsT::to_int_type(*gptr()));

  size_t length = readSocket();
  if(!length)
    return traitsT::eof();
    
  return traitsT::to_int_type(*gptr());
} // underflow

template<class charT, class traitsT>
typename basic_socketbuf<charT, traitsT>::int_type basic_socketbuf<charT, traitsT>::pbackfail(int_type c)
{
  if(gptr() == eback())
    return traitsT::eof();

  gbump(-1);
  if(!traitsT::eq_int_type(c, traitsT::eof()))
    *(gptr()) = traitsT::to_char_type(c);
  return traitsT::not_eof(c);
} // pbackfail

template<class charT, class traitsT>
void basic_socketbuf<charT, traitsT>::growOutBuffer()
{
  size_t oldsize = outBuffer_.capacity();
  size_t newsize = (oldsize ? oldsize*2 : bufferSize_);
  outBuffer_.resize(newsize);
  
  char* out_begin = &(outBuffer_[0]);
  setp(out_begin + oldsize, out_begin + newsize);
} // growOutBuffer

template<class charT, class traitsT>
bool basic_socketbuf<charT, traitsT>::writeSocket()
{
  // write to the socket
  size_t length = pptr() - &(outBuffer_[0]);
  if(!length)
    return true;

  bool ok(true);
  const std::codecvt<charT, char, state_t>& cvt =
#ifndef _MSC_VER
      std::use_facet<std::codecvt<charT, char, typename traitsT::state_type> >(this->getloc());
#else
      std::use_facet(this->getloc(), (std::codecvt<charT, char, traitsT::state_type>*)0, true);
#endif

  if(cvt.always_noconv())
    ok = (send(sock_, &(outBuffer_[0]), length, 0) != SOCKET_ERROR);
  else
  {
    // we must do code conversion
    std::vector<char> to(length);
    char* to_begin = &(to[0]);
    const charT* from_next = &(outBuffer_[0]);
    std::codecvt_base::result r;

    do
    {
      char* to_next;
      r = cvt.out(outState_, from_next, pptr(), from_next,
                  to_begin, to_begin + length, to_next);

      if(r == std::codecvt_base::noconv)
      {
        ok = (send(sock_, from_next, length, 0) != SOCKET_ERROR);
        break;
      }
      ok = (send(sock_, to_begin, to_next - to_begin, 0) != SOCKET_ERROR);
    }
    while((r == std::codecvt_base::partial) && (ok));

    ok = ok ? (r != std::codecvt_base::error) : false;
  } // if(cvt.always_noconv())
 
  if(ok)
  {
    charT* from_next = &(outBuffer_[0]);
    setp(from_next, from_next + outBuffer_.capacity());
  } // if(ok)

  return ok;
} // writeSocket

template<class charT, class traitsT>
void basic_socketbuf<charT, traitsT>::growInBuffer()
{
  size_t oldsize = inBuffer_.capacity();
  size_t newsize = (oldsize ? oldsize*2 : bufferSize_+pbSize_);
  inBuffer_.resize(newsize);
} // growInBuffer

template <class charT, class traitsT>
int basic_socketbuf<charT, traitsT>::readSocket()
{
  if(!inBuffer_.capacity())
    growInBuffer();

#ifndef _MSC_VER
  size_t pbCount = std::min<int>(gptr() - eback(), pbSize_);
#else
  size_t pbCount = min(gptr() - eback(), pbSize_);
#endif
  memcpy(&(inBuffer_[0]) + (pbSize_-pbCount)*sizeof(charT),
         gptr() - pbCount*sizeof(charT),
         pbCount*sizeof(charT));

  const std::codecvt<charT, char, state_t>& cvt =
#ifndef _MSC_VER
      std::use_facet<std::codecvt<charT, char, typename traitsT::state_type> >(this->getloc());
#else
      std::use_facet(this->getloc(), (std::codecvt<charT, char, traitsT::state_type>*)0, true);
#endif
  std::vector<char> from(inBuffer_.capacity() - pbSize_);
  int res = recv(sock_, &(from[0]), from.capacity(), 0);
  if(res > 0)
  {
    std::codecvt_base::result r;
    do
    {
      const char* from_begin = &(from[0]);
      const char* from_next;
      charT* to_begin = &(inBuffer_[0]) + pbSize_;
      charT* to_next;
      charT* to_end = &(inBuffer_[0]) + inBuffer_.capacity();

      r = cvt.in(inState_, from_begin, from_begin + res, from_next,
                 to_begin, to_end, to_next);

      if(r == std::codecvt_base::noconv)
        memcpy(to_begin, from_begin, res);
      else
        res = to_next - to_begin;
      if(r == std::codecvt_base::partial)
        growInBuffer();
    }
    while(r == std::codecvt_base::partial);

    if(r == std::codecvt_base::error)
    {
      // couldn't convert - let's bail
      close();
      return 0;
    } // if(r == std::codecvt_base::error)
  }
  else if(res == 0)
  {
    // server closed the socket
    close();
    return 0;
  } // if(res == 0)
  else if(res == SOCKET_ERROR)
  {
#ifdef _MSC_VER
    if(GetLastError() == WSAEMSGSIZE)
    {
      // buffer was too small, so make it bigger
      growInBuffer();
      return readSocket();
    } // if(GetLastError() != WSAEMSGSIZE)
#endif 

    // unclever error handling
    close();
    return 0;
  } // if(res == SOCKET_ERROR)

  charT* to_begin = &(inBuffer_[0]) + pbSize_;
  setg(to_begin - pbCount, to_begin, to_begin + res);

  return res;
} // readSocket

template <class charT, class traitsT>
int basic_socketbuf<charT, traitsT>::closeSocket(int sock) const
{
#ifdef _MSC_VER
  return closesocket(sock);
#else
  return ::close(sock);
#endif
} // closeSocket

///////////////////////////////////////////////////////////
// basic_socketstream declaration
template<class charT, class traitsT>
class basic_socketstream : public std::basic_iostream<charT, traitsT>
{
  public:
    basic_socketstream();
    explicit basic_socketstream(const char* hostname, int port);

    virtual ~basic_socketstream();

    basic_socketbuf<charT,traitsT>* rdbuf() const;
    bool is_open() const;
    void open(const char* hostname, unsigned short port);
    void close();

  private:
    basic_socketbuf<charT, traitsT> sockbuf;
}; // class basic_socketstream

typedef basic_socketstream<char, std::char_traits<char> > socketstream;
typedef basic_socketstream<wchar_t, std::char_traits<wchar_t> > wsocketstream;

////////////////////////////////////////////////////////////////
// basic_socketstream definition
template<class charT, class traitsT>
basic_socketstream<charT, traitsT>::basic_socketstream() :
    std::basic_iostream<charT, traitsT>( 0 )
{
  std::basic_ios<charT,traitsT>::init( &sockbuf );
} // basic_socketstream

template<class charT, class traitsT>
basic_socketstream<charT, traitsT>::basic_socketstream(const char* hostname, int port) :
    std::basic_iostream<charT, traitsT>( 0 )
{
  std::basic_ios<charT,traitsT>::init( &sockbuf );
  open(hostname, port);
} // basic_socketstream

template<class charT, class traitsT>
basic_socketstream<charT, traitsT>::~basic_socketstream()
{
} // ~basic_socketstream

template<class charT, class traitsT>
basic_socketbuf<charT, traitsT>* basic_socketstream<charT, traitsT>::rdbuf() const
{
  return const_cast<basic_socketbuf<charT, traitsT>* >(&sockbuf);
} // rdbuf

template<class charT, class traitsT>
bool basic_socketstream<charT, traitsT>::is_open() const
{
  return sockbuf.is_open();
} // is_open

template<class charT, class traitsT>
void basic_socketstream<charT, traitsT>::open(const char* hostname, unsigned short port)
{
  if(sockbuf.open(hostname, port) == 0)
    setstate(badbit);
} // open

template<class charT, class traitsT>
void basic_socketstream<charT, traitsT>::close()
{
  if(!is_open())
    return;

  if(sockbuf.close() == 0)
    setstate(badbit);
} // close

#endif
//end of file
