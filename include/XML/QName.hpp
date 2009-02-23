#ifndef ARABICA_XML_QNAME_HPP
#define ARABICA_XML_QNAME_HPP

#include <SAX/ArabicaConfig.hpp>
#include <Arabica/StringAdaptor.hpp>

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class QualifiedName
{
  typedef string_adaptor SA;

public:
  QualifiedName(const string_type& localName) :
    prefix_(),
    localName_(localName),
    namespaceUri_()
  {
  } // QualifiedName
  
  QualifiedName(const string_type& prefix,
		const string_type& localName,
		const string_type& namespaceUri) :
    prefix_(prefix),
    localName_(localName),
    namespaceUri_(namespaceUri)
  {
  } // QualifiedName

  QualifiedName(const QualifiedName& rhs) :
    prefix_(rhs.prefix_),
    localName_(rhs.localName_),
    namespaceUri_(rhs.namespaceUri_)
  {
  } // QualifiedName

  QualifiedName& operator=(const QualifiedName& rhs) 
  {
    QualifiedName qn(rhs);
    std::swap(prefix_, qn.prefix_);
    std::swap(localName_, qn.localName_);
    std::swap(namespaceUri_, qn.namespaceUri_);
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

  const string_type& prefix() const { return prefix_; }
  const string_type& namespaceUri() const { return namespaceUri_; }
  const string_type& localName() const { return localName_; }
  
private:
  string_type prefix_;
  string_type localName_;
  string_type namespaceUri_;

  QualifiedName();
}; // class QualifiedName

#endif
