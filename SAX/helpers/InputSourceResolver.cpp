/*
 * $Id$
 */

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <SAX/helpers/InputSourceResolver.h>
#include <istream>
#include <fstream>
#include <Utils/socket_stream.h>

InputSourceResolver::InputSourceResolver(const SAX::InputSource& inputSource) :
  deleteStream_(false),
  byteStream_(0)
{
  open(inputSource.getPublicId(),
       inputSource.getSystemId(),
       inputSource.getByteStream());
} // InputSourceResolver

void InputSourceResolver::open(const std::string& publicId, 
            const std::string& systemId,
            std::istream* byteStream)
{
    if(byteStream != 0)
    {
      byteStream_ = byteStream;
      return;
    } 

    // does it look like a URL?
    std::string::size_type colonIndex = systemId.find("://");
    if(colonIndex != std::string::npos)
    {
      URIResolver res = findResolver(systemId.substr(0, colonIndex));
      if(res)
        byteStream_ = res(systemId);
      if(byteStream_)
      {
        deleteStream_ = true;
        return;
      } // if ...
    } // if ...

    // try and open it as a file
    std::ifstream* ifs = new std::ifstream(systemId.c_str());
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
  std::istream* fileResolver(const std::string& fileURL)
  {
    int colon = fileURL.find("://");
    std::string fileName = fileURL.substr(colon+3);

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

  std::istream* httpResolver(const std::string& httpURL)
  {
#ifdef ARABICA_WINDOWS
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup( wVersionRequested, &wsaData );
    if(err != 0)
        return 0;
#endif

    int colon1 = httpURL.find("://");
    colon1 += 3;
    //int colon2 = httpURL.find("://", colon1);
    int slash1 = httpURL.find("/", colon1);

    std::string hostName = httpURL.substr(colon1, slash1 - (colon1));
    std::string path = httpURL.substr(slash1);

    socketstream* ifs = new socketstream(hostName.c_str(), 80);
    if(!ifs->is_open())
      return 0;
    *ifs << "GET " << path << " HTTP/1.0" << std::endl;
    *ifs << "Host: " << hostName << std::endl;
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
