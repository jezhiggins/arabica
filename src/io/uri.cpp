
#include <algorithm>
#include <io/uri.hpp>

using namespace Arabica::io;

namespace {
  const std::string ZERO = "0";
  const std::string PORT_EIGHTY = "80";
  const std::string PORT_443 = "443";

  const std::string SCHEME_HTTP = "http";
  const std::string SCHEME_HTTPS = "https";
  const std::string SCHEME_FILE = "file";

  const std::string COLON = ":";
  const char FORWARD_SLASH = '/';
  
  const std::string& wellKnownPort(const std::string& scheme)
  {
    if(scheme.empty())
      return ZERO;

    if(scheme == SCHEME_HTTP)
      return PORT_EIGHTY;
    if(scheme == SCHEME_HTTPS)
      return PORT_443;

    return ZERO;
  } // wellKnownPort
} // namespace 

URI::URI(const std::string& uri) :
  is_absolute_(false)
{
  parse(uri);
} // URI

URI::URI(const URI& base, const std::string& relativeUrl) :
  scheme_(base.scheme_),
  host_(base.host_),
  path_(base.path_),
  port_(base.port_),
  is_absolute_(base.is_absolute_)
{
  if(!relativeUrl.empty())
  {
    URI relUrl(relativeUrl);
    absolutise(relUrl);
  } // if ... 
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
    str.append(scheme_).append(COLON);
  if(is_absolute_)
    str.append("//");
  if(!host_.empty())
  {
    str.append(host_);
    if(!port_.empty())
      str.append(COLON).append(port_);
  }
  str.append(path_);
  return str;
} // as_string

void fixSlashes(std::string& path)
{
  for(size_t i = path.find('\\'); i != std::string::npos; i = path.find('\\', i))
    path[i] = FORWARD_SLASH;
} // fixSlashes

void URI::parse(const std::string& uri)
{
  parse_uri(uri);

  is_absolute_ = (!scheme_.empty() && !host_.empty()) ||
    (((scheme_ == SCHEME_FILE) && (!path_.empty())) && 
     ((path_[0] == FORWARD_SLASH) || (path_[1] == ':')));
} // parse

void URI::parse_uri(const std::string& uri)
{
  // I'd like to use something a bit stronger - http://code.google.com/p/uri-grammar/
  // but that would put a Boost Spirit dependence right in the core, which I'm not prepared to do at the moment

  size_t d = uri.find_first_of(COLON);
  if(d == std::string::npos)
  {
    path_ = uri;
    fixSlashes(path_);
    return;
  } // if ...

  if(d == 1) 
  {
    // looks like a windows file path
    path_ = uri;
    fixSlashes(path_);
    scheme_ = SCHEME_FILE;
    return;
  } // if ...

  scheme_ = uri.substr(0, d);

  std::string::const_iterator u = uri.begin() + d;
  std::string::const_iterator ue = uri.end();

  ++u;
  if(*u == FORWARD_SLASH && *(u+1) == FORWARD_SLASH)
  {
    u += 2;
    u = parseAuthority(u, ue);
  } // if ...

  path_.append(u, ue);
} // parse

std::string::const_iterator URI::parseAuthority(const std::string::const_iterator& u, 
						const std::string::const_iterator& ue)
{
  std::string::const_iterator slash = std::find(u, ue, FORWARD_SLASH);
  if(slash == ue)
  {
    // ah, this is easy
    host_.append(u, ue);
    return ue;
  } // if(slash == we)

  std::string::const_iterator colon = std::find(u, slash, ':');
  host_.append(u, colon);

  if(colon != slash)
    port_.append(colon+1, slash);

  return slash;
} // parseAuthority

bool compatible_schemes(const std::string& scheme,
			const std::string& relative)
{
  if(scheme.empty() && (relative == "file"))
    return true;
  if(relative.empty())
    return true;
  return (scheme == relative);
} // compatible_schemes

void URI::absolutise(URI& relative)
{
  if((relative.is_absolute()) || 
     !compatible_schemes(scheme_, relative.scheme()))
  {
    swap(relative);
    return;
  }

  if(relative.path_[0] == FORWARD_SLASH)
    path_ = relative.path_;
  else 
    combinePath(relative.path_);
} // absolutise

void URI::combinePath(const std::string& relPath)
{
  if(*(path_.rbegin()) != FORWARD_SLASH)
    path_.erase(path_.rfind(FORWARD_SLASH)+1);

  std::string::size_type from = path_.length() - 1;
  path_.append(relPath);

  size_t dots = path_.find("/../", from);
  while(dots != std::string::npos)
  {
    int preceding_slash = (dots > 0) ? path_.rfind(FORWARD_SLASH, dots-1) : 0;
    path_.erase(preceding_slash, dots+3-preceding_slash);
    dots = path_.find("/../", preceding_slash);
  } // while

  size_t dot = path_.find("/./");
  while(dot != std::string::npos)
  {
    path_.erase(dot, 2);
    dot = path_.find("/./", dot);
  }
} // combinePath

