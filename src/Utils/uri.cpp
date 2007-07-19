
#include <algorithm>
#include <Utils/uri.hpp>

using namespace Arabica::io;

namespace {
  const std::string ZERO = "0";
  const std::string PORT_EIGHTY = "80";
  const std::string PORT_443 = "443";
  
  const std::string& wellKnownPort(const std::string& scheme)
  {
    if(scheme.empty())
      return ZERO;

    if(scheme == "http")
      return PORT_EIGHTY;
    if(scheme == "https")
      return PORT_443;

    return ZERO;
  } // wellKnownPort
} // namespace 

URI::URI(const std::string& uri) 
{
  parse(uri);
} // URI

URI::URI(const URI& base, const std::string& relativeUrl) :
  scheme_(base.scheme_),
  host_(base.host_),
  path_(base.path_),
  port_(base.port_)
{
  URI relUrl(relativeUrl);
  absolutise(relUrl);
} // URI         

const std::string& URI::port() const
{
  if(port_.empty())
    return wellKnownPort(scheme_);
  return port_;
} // port()

std::string URI::as_string() const
{
  std::string str;
  if(!scheme_.empty())
    str.append(scheme_).append("://");
  if(!host_.empty())
  {
    str.append(host_);
    if(!port_.empty())
      str.append(":").append(port_);
  }
  str.append(path_);
  return str;
} // as_string


void URI::parse(const std::string& uri)
{
  // I'd like to use something a bit stronger - http://code.google.com/p/uri-grammar/
  // but that would put a Boost Spirit dependence right in the core, which I'm not prepared to do at the moment

  int d = uri.find_first_of(":");
  if(d == std::string::npos)
  {
    path_ = uri;
    return;
  } // if ...

  scheme_ = uri.substr(0, d);

  std::string::const_iterator u = uri.begin() + d;
  std::string::const_iterator ue = uri.end();

  ++u;
  if(*u == '/' && *(u+1) == '/')
  {
    u += 2;
    parseAuthority(u, ue);
  } // if ...

  path_.append(u, ue);
} // parse

void URI::parseAuthority(std::string::const_iterator& u, std::string::const_iterator& ue)
{
  std::string::const_iterator slash = std::find(u, ue, '/');
  if(slash == ue)
    return;

  std::string::const_iterator colon = std::find(u, slash, ':');
  host_.append(u, colon);

  if(colon != slash)
    port_.append(colon+1, slash);

  u = slash;
} // parseAuthority

void URI::absolutise(URI& relative)
{
  if(!relative.scheme().empty())
  {
    swap(relative);
    return;
  }

  if(relative.path_[0] == '/')
    path_ = relative.path_;
  else 
    combinePath(relative.path_);
} // absolutise

void URI::combinePath(const std::string& relPath)
{
  if(*(path_.rbegin()) != '/')
    path_.erase(path_.rfind('/')+1);

  path_.append(relPath);

  int dots = path_.find("/../");
  while(dots != std::string::npos)
  {
    int preceding_slash = (dots > 0) ? path_.rfind('/', dots-1) : 0;
    path_.erase(preceding_slash, dots+3-preceding_slash);
    dots = path_.find("/../");
  } // while

  int dot = path_.find("/./");
  while(dot != std::string::npos)
  {
    path_.erase(dot, 2);
    dot = path_.find("/./", dot);
  }
} // combinePath