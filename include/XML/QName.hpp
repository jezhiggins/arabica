#ifndef ARABICA_XML_QNAME_HPP
#define ARABICA_XML_QNAME_HPP

#include <SAX/ArabicaConfig.hpp>
#include <Arabica/StringAdaptor.hpp>
#include <XML/strings.hpp>
#include <stdexcept>

template<class string_type, class string_adaptor> class QualifiedNameTest;

namespace Arabica
{
namespace XML
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class QualifiedName
{
  typedef string_adaptor SA;

public:
  /**
   * <p>This function processes a raw XML 1.0 name in the current
   * context by removing the prefix and looking it up among the
   * prefixes currently declared.  
   *
   * <p>If the raw name has a prefix that has not been declared, 
   * then the return value will be empty.</p>
   *
   * <p>Note that attribute names are processed differently than
   * element names: an unprefixed element name will received the
   * default Namespace (if any), while an unprefixed attribute name
   * will not.</p>
   */
  template<typename UriMapper>
  static QualifiedName parseQName(const string_type& rawname, 
				  bool is_attribute,
				  const UriMapper& mapper)
  {
    if(!Arabica::XML::is_qname<string_adaptor>(rawname))
      throw std::runtime_error("Bad qname : " + SA::asStdString(rawname));

    static string_type COLON = SA::construct_from_utf8(":");

    typename string_adaptor::size_type index = string_adaptor::find(rawname, COLON);

    if(index == string_adaptor::npos())
      return QualifiedName(rawname, 
			                     is_attribute ? SA::empty_string() : mapper(SA::empty_string()));

    // prefix
    string_type prefix = string_adaptor::substr(rawname, 0, index);
    string_type localName = string_adaptor::substr(rawname, index + 1);
    string_type uri = mapper(prefix);

    return QualifiedName(prefix, localName, uri, rawname);
  } // parseQName				  

  QualifiedName(const QualifiedName& rhs) :
    prefix_(rhs.prefix_),
    localName_(rhs.localName_),
    namespaceUri_(rhs.namespaceUri_),
    rawName_(rhs.rawName_)
  {
  } // QualifiedName

  QualifiedName& operator=(const QualifiedName& rhs) 
  {
    QualifiedName qn(rhs);
    std::swap(prefix_, qn.prefix_);
    std::swap(localName_, qn.localName_);
    std::swap(namespaceUri_, qn.namespaceUri_);
    std::swap(rawName_, qn.rawName_);
    return *this;
  } // operator=

  bool operator==(const QualifiedName& rhs) const
  {
    return (localName_ == rhs.localName_) &&
           (namespaceUri_ == rhs.namespaceUri_);
  } // operator==

  bool operator!=(const QualifiedName& rhs) const
  {
    return !(operator==(rhs));
  } // operator!=

  string_type clarkName() const 
  {
    if(SA::empty(namespaceUri_))
      return localName_;

    string_type cn;
    SA::append(cn, SA::construct_from_utf8("{"));
    SA::append(cn, namespaceUri_);
    SA::append(cn, SA::construct_from_utf8("}"));
    SA::append(cn, localName_);
    return cn;
  } // clarkName

  bool has_prefix() const { return !SA::empty(prefix_); }
  void set_prefix(const string_type& prefix) { prefix_ = prefix; }
  bool has_namespaceUri() const { return !SA::empty(namespaceUri_); }

  const string_type& prefix() const { return prefix_; }
  const string_type& localName() const { return localName_; }
  const string_type& namespaceUri() const { return namespaceUri_; }

  bool has_rawName() const { return !SA::empty(rawName_); }
  const string_type& rawName() const { return rawName_; }
  
private:
  string_type prefix_;
  string_type localName_;
  string_type namespaceUri_;
  string_type rawName_;

  QualifiedName(const string_type& localName,
                const string_type& namespaceUri) :
    prefix_(),
    localName_(localName),
    namespaceUri_(namespaceUri),
    rawName_(localName)
  {
  } // QualifiedName
  
  QualifiedName(const string_type& prefix,
		            const string_type& localName,
		            const string_type& namespaceUri) :
    prefix_(prefix),
    localName_(localName),
    namespaceUri_(namespaceUri),
    rawName_()
  {
  } // QualifiedName

  QualifiedName(const string_type& prefix,
		            const string_type& localName,
		            const string_type& namespaceUri,
                const string_type& rawName) :
    prefix_(prefix),
    localName_(localName),
    namespaceUri_(namespaceUri),
    rawName_(rawName)
  {
  } // QualifiedName


  QualifiedName();

  friend class QualifiedNameTest<string_type, string_adaptor>;
}; // class QualifiedName

} // namespace XML

} // namespace Arabica
#endif
