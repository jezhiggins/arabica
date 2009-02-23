#ifndef ARABICA_XML_QNAME_HPP
#define ARABICA_XML_QNAME_HPP


class QualifiedName
{
public:
  QualifiedName(const std::string& localName) :
    prefix_(),
    localName_(localName),
    namespaceUri_()
  {
  } // QualifiedName
  
  QualifiedName(const std::string& prefix,
		const std::string& localName,
		const std::string& namespaceUri) :
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

  std::string clarkName() const 
  {
    if(namespaceUri_.length() == 0)
      return localName_;
    return "{" + namespaceUri_ + "}" + localName_;
  } // clarkName

  bool has_prefix() const { return !prefix_.empty(); }
  void set_prefix(const std::string& prefix) { prefix_ = prefix; }

  const std::string& prefix() const { return prefix_; }
  const std::string& namespaceUri() const { return namespaceUri_; }
  const std::string& localName() const { return localName_; }
  
private:
  std::string prefix_;
  std::string localName_;
  std::string namespaceUri_;

  QualifiedName();
}; // class QualifiedName

#endif
