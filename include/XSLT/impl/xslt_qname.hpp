#ifndef ARABICA_XSLT_QNAME_HPP
#define ARABICA_XSLT_QNAME_HPP

#include <XML/strings.hpp>

namespace Arabica
{
namespace XSLT
{

struct QName
{
  std::string prefix;
  std::string localName;
  std::string namespaceURI;
  std::string qname;

  QName(const std::string& p,
              const std::string& lN,
              const std::string& uri) :
    prefix(p),
    localName(lN),
    namespaceURI(uri),
    qname(p.empty() ? lN : (p + ":" + lN))
  {
  } // QName

  static QName create(const XML::QualifiedName<std::string>& qName)
  {
    if(qName.prefix().length() && qName.namespaceUri().empty())
      throw SAX::SAXException("Prefix " + qName.prefix() + " is not declared.");
    return QName(qName.prefix(), qName.localName(), qName.namespaceUri());
  } // create

  static QName create(const std::string& qName)
  {
    return create(qName, "");
  } // create

  static QName create(const std::string& qName, const std::string& namespaceURI)
  {
    if(!Arabica::XML::is_qname<Arabica::default_string_adaptor<std::string> >(qName))
      throw SAX::SAXException("Bad name : '" + qName + "'");

    static char COLON = Arabica::text::Unicode<char>::COLON;

    std::string prefix;
    std::string localName;

    size_t colon = qName.find(COLON);
     
    if(colon == std::string::npos) 
      localName = qName;
    else
    {
      prefix = qName.substr(0, colon);
     localName = qName.substr(colon+1);
    }
    return QName(prefix, localName, namespaceURI);
  } // create

  bool operator==(const QName& rhs) const
  {
    return (namespaceURI == rhs.namespaceURI) &&
           (localName == rhs.localName);
  } // operator==

  bool operator<(const QName& rhs) const
  {
    if(namespaceURI == rhs.namespaceURI)
      return localName < rhs.localName;
    return namespaceURI < rhs.namespaceURI;
  } // operator<
}; // struct QName



} // namespace XSLT
} // namespace Arabica
#endif
