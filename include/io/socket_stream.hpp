#ifndef ARABICA_SOCKET_STREAM_H
#define ARABICA_SOCKET_STREAM_H
///////////////////////////////////////////////////////////////////////
//
// socket_stream.h 
// 
// Written by Jez Higgins <jez@jezuk.co.uk>
// Copyright 1999-2003 Jez UK Ltd, http://www.jezuk.co.uk/
//
///////////////////////////////////////////////////////////////////////
// $Id$
///////////////////////////////////////////////////////////////////////

#include <SAX/ArabicaConfig.hpp>
#ifndef ARABICA_USE_WINSOCK
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
#include <cstring>

#ifndef INADDR_NONE
#  define INADDR_NONE             ((in_addr_t) -1)
#endif

namespace Arabica
{
namespace io
{

///////////////////////////////////////////////////////////
// basic_socketbuf declaration
template<class charT, class traitsT>
class basic_socketbuf : public std::basic_streambuf<charT, traitsT>
{
  public:
    typedef typename traitsT::int_type int_type;

    using std::basic_streambuf<charT, traitsT>::setp;
    using std::basic_streambuf<charT, traitsT>::setg;
    using std::basic_streambuf<charT, traitsT>::underflow;
    using std::basic_streambuf<charT, traitsT>::gptr;
    using std::basic_streambuf<charT, traitsT>::gbump;
    using std::basic_streambuf<charT, traitsT>::egptr;
    using std::basic_streambuf<charT, traitsT>::eback;
    using std::basic_streambuf<charT, traitsT>::pptr;

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

#ifndef ARABICA_USE_WINSOCK
    static const int INVALID_SOCKET;
    static const int SOCKET_ERROR;
#endif
}; // class basic_socketbuf

template<class charT, class traitsT>
const size_t basic_socketbuf<charT, traitsT>::bufferSize_ = 1024;
template<class charT, class traitsT>
const size_t basic_socketbuf<charT, traitsT>::pbSize_ = 4;
  // why 4? both Josuttis and Langer&Kreft use 4.
#ifndef ARABICA_USE_WINSOCK
template<class charT, class traitsT>
const int basic_socketbuf<charT, traitsT>::INVALID_SOCKET = -1;
template<class charT, class traitsT>
const int basic_socketbuf<charT, traitsT>::SOCKET_ERROR = -1;
#endif

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
  charT* from_next = &(outBuffer_[0]);
  size_t length = pptr() - from_next;
  if(!length)
    return true;

  bool ok = (send(sock_, from_next, length, 0) != SOCKET_ERROR);

  if(ok)
    setp(from_next, from_next + outBuffer_.capacity());

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

  size_t pbCount = std::min<int>(gptr() - eback(), pbSize_);

  memcpy(&(inBuffer_[0]) + (pbSize_-pbCount)*sizeof(charT), 
         gptr() - pbCount*sizeof(charT),
         pbCount*sizeof(charT));

  int res = recv(sock_, &(inBuffer_[0]) + pbSize_, inBuffer_.capacity() - pbSize_, 0);
  if(res == 0)
  {
    // server closed the socket
    close();
    return 0;
  } // if(res == 0)
  else if(res == SOCKET_ERROR)
  {
#ifdef ARABICA_USE_WINSOCK
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
#ifdef ARABICA_USE_WINSOCK
  return closesocket(sock);
#else
  return ::close(sock);
#endif
} // closeSocket

///////////////////////////////////////////////////////////
// basic_socketstream declaration
template<class charT, class traitsT>
class socketstreambuf_init
{
public:
  typedef basic_socketbuf<charT, traitsT> sockbuf;

  sockbuf* buf() const
  {
    return &buf_;
  } // buf()

private:
  mutable sockbuf buf_;
}; // class socketstreambuf_init

template<class charT, class traitsT>
class basic_socketstream : 
  private virtual socketstreambuf_init<charT, traitsT>,
  public std::basic_iostream<charT, traitsT>
{
  public:
    using std::basic_iostream<charT, traitsT>::setstate;
    using std::basic_iostream<charT, traitsT>::badbit;

    basic_socketstream();
    explicit basic_socketstream(const char* hostname, int port);

    virtual ~basic_socketstream();

    basic_socketbuf<charT,traitsT>* rdbuf() const;
    bool is_open() const;
    void open(const char* hostname, unsigned short port);
    void close();
}; // class basic_socketstream

////////////////////////////////////////////////////////////////
// basic_socketstream definition
template<class charT, class traitsT>
basic_socketstream<charT, traitsT>::basic_socketstream() :
    socketstreambuf_init<charT, traitsT>(), 
    std::basic_iostream<charT, traitsT>(socketstreambuf_init<charT, traitsT>::buf())
{
} // basic_socketstream

template<class charT, class traitsT>
basic_socketstream<charT, traitsT>::basic_socketstream(const char* hostname, int port) :
    socketstreambuf_init<charT, traitsT>(), 
    std::basic_iostream<charT, traitsT>(socketstreambuf_init<charT, traitsT>::buf())
{
  open(hostname, port);
} // basic_socketstream

template<class charT, class traitsT>
basic_socketstream<charT, traitsT>::~basic_socketstream()
{
} // ~basic_socketstream

template<class charT, class traitsT>
basic_socketbuf<charT, traitsT>* basic_socketstream<charT, traitsT>::rdbuf() const
{
  return socketstreambuf_init<charT, traitsT>::buf();
} // rdbuf

template<class charT, class traitsT>
bool basic_socketstream<charT, traitsT>::is_open() const
{
  return socketstreambuf_init<charT, traitsT>::buf()->is_open();
} // is_open

template<class charT, class traitsT>
void basic_socketstream<charT, traitsT>::open(const char* hostname, unsigned short port)
{
  if(socketstreambuf_init<charT, traitsT>::buf()->open(hostname, port) == 0)
    setstate(badbit);
} // open

template<class charT, class traitsT>
void basic_socketstream<charT, traitsT>::close()
{
  if(!is_open())
    return;

  if(socketstreambuf_init<charT, traitsT>::buf()->close() == 0)
    setstate(badbit);
} // close

typedef basic_socketbuf<char, std::char_traits<char> > socketbuf;
typedef basic_socketstream<char, std::char_traits<char> > socketstream;
#ifndef ARABICA_NO_WSTRING_T
typedef basic_socketbuf<wchar_t, std::char_traits<wchar_t> > wsocketbuf;
typedef basic_socketstream<wchar_t, std::char_traits<wchar_t> > wsocketstream;
#endif

} // namespace io
} // namespace Arabica

#endif
//end of file
