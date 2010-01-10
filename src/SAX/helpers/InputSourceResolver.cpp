/*
 * $Id$
 */

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <SAX/helpers/InputSourceResolver.hpp>
#include <istream>
#include <fstream>
#include <io/socket_stream.hpp>
#include <io/uri.hpp>
#include <cmath>

using namespace Arabica::SAX;

void InputSourceResolver::open(const std::string& /* publicId */, 
            const std::string& systemId,
            std::istream* byteStream)
{
    if(byteStream != 0)
    {
      byteStream_ = byteStream;
      return;
    } 

    // does it look like a URI?
    Arabica::io::URI url(systemId);
    if(!url.scheme().empty())
    {
      URIResolver res = findResolver(url.scheme());
      if(res)
        byteStream_ = res(systemId);
      if(byteStream_)
      {
        deleteStream_ = true;
        return;
      } // if ...
    } // if ...

    // try and open it as a file
    std::ifstream* ifs = new std::ifstream(url.path().c_str());
    if(ifs->is_open())
    {
      deleteStream_ = true;
      byteStream_ = ifs;
    }
    else
      delete ifs;
} // InputSourceResolver

InputSourceResolver::~InputSourceResolver()
{
  if(deleteStream_)
    delete byteStream_;
} // ~InputSourceResolver

//////////////////////////////////////////////////////
// resolverMap register/unregister
bool InputSourceResolver::registerResolver(const std::string& method, URIResolver resolver)
{
  resolverMap()[method] = resolver;
  return true;
} // registerResolver

bool InputSourceResolver::unRegisterResolver(const std::string& method)
{
  resolverMapT::iterator i = resolverMap().find(method);
  if(i != resolverMap().end())
    resolverMap().erase(i);
  return true;
} // unRegisterResolver

InputSourceResolver::URIResolver InputSourceResolver::findResolver(std::string method)
{
  resolverMapT::iterator i = resolverMap().find(method);
  return (i != resolverMap().end()) ? i->second : 0;
} // findResolver

namespace 
{
  std::istream* fileResolver(const std::string& fileURI)
  {
    Arabica::io::URI url(fileURI);
    std::string fileName = url.path();

    std::ifstream* ifs = new std::ifstream(fileName.c_str());
    if(ifs->is_open())
      return ifs;
    delete ifs;

    // WIN32 specific stuff
    for(std::string::iterator i = fileName.begin(); i != fileName.end(); ++i)
      if(*i == '/')
        *i = '\\';

    if((fileName[0] == '\\') && (fileName[2] == ':'))
      fileName.erase(0, 1);

    ifs = new std::ifstream(fileName.c_str());
    if(ifs->is_open())
      return ifs;
    delete ifs;

    return 0;
  } // fileResolver

  static bool fileReg = InputSourceResolver::registerResolver("file", fileResolver);

  std::istream* httpResolver(const std::string& httpURI)
  {
#ifdef ARABICA_USE_WINSOCK
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup( wVersionRequested, &wsaData );
    if(err != 0)
        return 0;
#endif

    Arabica::io::URI url(httpURI);

    Arabica::io::socketstream* ifs = new Arabica::io::socketstream(url.host().c_str(), std::atoi(url.port().c_str()));
    if(!ifs->is_open())
      return 0;
    *ifs << "GET " << url.path() << " HTTP/1.0" << std::endl;
    *ifs << "Host: " << url.host() << std::endl;
    *ifs << "Connection: close" << std::endl;
    *ifs << std::endl;

    char buffer[1024];
    do
    {
      ifs->getline(buffer, sizeof(buffer));
    }
    while(buffer[0] != '\r');

    return ifs;
  } // httpResolver

  static bool httpReg = InputSourceResolver::registerResolver("http", httpResolver);
} // namespace

// end of file
