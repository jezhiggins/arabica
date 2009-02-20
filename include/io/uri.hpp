#ifndef ARABICA_IO_URI_HPP
#define ARABICA_IO_URI_HPP

#include <string>

namespace Arabica
{
  namespace io
  {
    class URI
    {
    public:
      URI() { }

      URI(const std::string& URI);

      URI(const URI& base, const std::string& relativeURI);

      URI(const URI& rhs) :
        scheme_(rhs.scheme_),
        host_(rhs.host_),
        path_(rhs.path_),
        port_(rhs.port_),
	is_absolute_(rhs.is_absolute_)
        {
        } // URI

      URI& operator=(const URI& rhs)
      {
        URI t(rhs);
        swap(t);
        return *this;
      } // operator=

      bool operator==(const URI& rhs) const
      {
        return scheme_ == rhs.scheme_ &&
               host_ == rhs.host_ &&
               path_ == rhs.path_ &&
               port_ == rhs.port_ &&
	       is_absolute_ == rhs.is_absolute_;
      } // operator==

      bool operator!=(const URI& rhs) const
      {
        return !(operator==(rhs));
      } // operator!=

      ~URI() { }

      void swap(URI& rhs)
      {
        std::swap(scheme_, rhs.scheme_);
        std::swap(host_, rhs.host_);
        std::swap(path_, rhs.path_);
        std::swap(port_, rhs.port_);
	std::swap(is_absolute_, rhs.is_absolute_);
      } // swap

      const std::string& scheme() const { return scheme_; }
      const std::string& host() const { return host_; }
      const std::string& port() const;
      const std::string& path() const { return path_; }
      const bool& is_absolute() const { return is_absolute_; }

      std::string as_string() const;
      
    private:
      void parse(const std::string& URI);
      void parse_uri(const std::string& URI);
      std::string::const_iterator parseAuthority(const std::string::const_iterator& u, const std::string::const_iterator& ue);
      void absolutise(URI& relURI);
      void combinePath(const std::string& path);

      std::string scheme_;
      std::string host_;
      std::string path_;
      std::string port_;
      bool is_absolute_;
    }; // class URI
  } // namespace io
} // namespace Arabica

#endif 
