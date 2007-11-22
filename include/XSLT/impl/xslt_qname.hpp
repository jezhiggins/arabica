#ifndef ARABICA_XSLT_QNAME_HPP
#define ARABICA_XSLT_QNAME_HPP

namespace Arabica
{
namespace XSLT
{

struct QName
{
  std::string prefix;
  std::string localName;
  std::string namespaceURI;

  static QName createQName(const std::string& qName) 
  {
    static char COLON = Arabica::text::Unicode<char>::COLON;
    QName qn;

    size_t colon = qName.find(COLON);
    if(colon == std::string::npos) 
      qn.localName = qName;
    else
    {
      qn.prefix = qName.substr(0, colon);
      qn.localName = qName.substr(colon+1);

      if((qn.prefix.length() == 0) || 
         (qn.localName.length() == 0) || 
         (qn.localName.find(COLON) != std::string::npos))
        throw SAX::SAXException("Bad qname");
    }

    return qn;
  } // createQName

  static QName createQName(const std::string& qName, const std::string namespaceURI) 
  {
    QName qn(createQName(qName));
    qn.namespaceURI = namespaceURI;
  
    if(!qn.prefix.empty() && qn.namespaceURI.empty())
      throw SAX::SAXException("Undeclared prefix " + qn.prefix);
    return qn;
  } // createQName
}; // QName


} // namespace XSLT
} // namespace Arabica
#endif
