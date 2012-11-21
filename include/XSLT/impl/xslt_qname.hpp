#ifndef ARABICA_XSLT_QNAME_HPP
#define ARABICA_XSLT_QNAME_HPP

#include <XML/strings.hpp>
#include "handler/xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
struct QName
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;

  string_type prefix;
  string_type localName;
  string_type namespaceURI;
  string_type qname;

  QName(const string_type& p,
        const string_type& lN,
        const string_type& uri) :
    prefix(p),
    localName(lN),
    namespaceURI(uri),
    qname()
  {
    if(!string_adaptor::empty(p)) 
    {
      string_adaptor::append(qname, p);
      string_adaptor::append(qname, SC::COLON);
    } // if ...
    string_adaptor::append(qname, lN);
  } // QName

  static QName create(const XML::QualifiedName<string_type, string_adaptor>& qName)
  {
    if(string_adaptor::length(qName.prefix()) && string_adaptor::empty(qName.namespaceUri()))
      throw SAX::SAXException("Prefix " + string_adaptor::asStdString(qName.prefix()) + " is not declared.");
    return QName(qName.prefix(), qName.localName(), qName.namespaceUri());
  } // create

  static QName create(const string_type& qName)
  {
    return create(qName, string_adaptor::empty_string());
  } // create

  static QName create(const string_type& qName, const string_type& namespaceURI)
  {
    if(!Arabica::XML::is_qname<string_adaptor>(qName))
      throw SAX::SAXException("Bad name : '" + string_adaptor::asStdString(qName) + "'");

    string_type prefix;
    string_type localName;

    size_t colon = string_adaptor::find(qName, SC::COLON);
     
    if(colon == string_adaptor::npos()) 
      localName = qName;
    else
    {
      prefix = string_adaptor::substr(qName, 0, colon);
      localName = string_adaptor::substr(qName, colon+1);
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
