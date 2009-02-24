#ifndef ARABICA_SAX_NAMESPACE_TRACKER_HPP
#define ARABICA_SAX_NAMESPACE_TRACKER_HPP

#include <map>
#include <SAX/ArabicaConfig.hpp>
#include <SAX/helpers/XMLFilterImpl.hpp>
#include <SAX/helpers/NamespaceSupport.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

  template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NamespaceTracker : public XMLFilterImpl<string_type, string_adaptor>
{
  typedef XMLFilterImpl<string_type, string_adaptor> XMLFilterT;
  typedef NamespaceSupport<string_type, string_adaptor> NamespaceSupportT;
  typedef typename NamespaceSupportT::stringListT stringListT;

public:
  typedef XMLReaderInterface<string_type, string_adaptor> XMLReaderT;
  typedef Attributes<string_type, string_adaptor> AttributesT;

  NamespaceTracker() : 
    XMLFilterT()
  { 
  } // NamespaceTracker

  NamespaceTracker(XMLReaderT& parent) : 
    XMLFilterT(parent)
  { 
  } // NamespaceTracker

  virtual ~NamespaceTracker() { } 

  XML::QualifiedName<string_type, string_adaptor> processElementName(const string_type& rawName) const
  {
    return namespaces_.processName(rawName, false);
  } // process

  XML::QualifiedName<string_type, string_adaptor> processName(const string_type& rawName) const
  {
    return namespaces_.processName(rawName, true);
  } // process

  string_type getURI(const string_type& prefix) const
  {
    return namespaces_.getURI(prefix);
  } // getURI

  std::map<string_type, string_type> inScopeNamespaces() const
  {
    std::map<string_type, string_type> ns;
    stringListT prefixes = namespaces_.getPrefixes();
    for(typename stringListT::const_iterator p = prefixes.begin(), pe = prefixes.end(); p != pe; ++p)
    {
      if(ns.find(*p) != ns.end())
        continue;

      ns[*p] = namespaces_.getURI(*p);
    } // for ...
    ns[""] = namespaces_.getURI("");
    return ns;
  } // inScopeNamespaces

  virtual void startElement(const string_type& namespaceURI, const string_type& localName,
                            const string_type& qName, const AttributesT& atts)
  {
    namespaces_.pushContext();
    for(typename std::map<string_type, string_type>::const_iterator i = buffer_.begin(), ie = buffer_.end(); i != ie; ++i)
      namespaces_.declarePrefix(i->first, i->second);
    buffer_.clear();

    XMLFilterT::startElement(namespaceURI, localName, qName, atts);
  } // startElement

  virtual void endElement(const string_type& namespaceURI, const string_type& localName,
                          const string_type& qName)
  {
    XMLFilterT::endElement(namespaceURI, localName, qName);
    namespaces_.popContext();
  } // endElement

  virtual void startPrefixMapping(const string_type& prefix, const string_type& uri)
  {
    // startPrefixMappings precede the startElement, so buffer 'em up
    buffer_[prefix] = uri;
    XMLFilterT::startPrefixMapping(prefix, uri);
  } // startPrefixMapping

private:
  NamespaceSupportT namespaces_;
  std::map<string_type, string_type> buffer_;
}; // class NamespaceTracker

} // namespace SAX
} // namespace Arabica

#endif
