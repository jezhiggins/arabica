#ifndef ARABICA_SAX_NAMESPACE_TRACKER_HPP
#define ARABICA_SAX_NAMESPACE_TRACKER_HPP

#include <map>
#include <SAX/ArabicaConfig.hpp>
#include <SAX/helpers/XMLFilterImpl.hpp>
#include <SAX/helpers/NamespaceSupport.hpp>
#include <Utils/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NamespaceTracker : public XMLFilterImpl<string_type>
{
  typedef NamespaceSupport<string_type, string_adaptor> NamespaceSupportT;
  typedef typename NamespaceSupportT::stringListT stringListT;
  typedef XMLFilterImpl<string_type> XMLFilterT;

public:
  typedef XMLReaderInterface<string_type> XMLReaderT;
  typedef Attributes<string_type> AttributesT;

  NamespaceTracker() : 
    XMLFilterImpl<string_type>()
  { 
  } // NamespaceTracker

  NamespaceTracker(XMLReaderT& parent) : 
    XMLFilterImpl<string_type>(parent)
  { 
  } // NamespaceTracker

  virtual ~NamespaceTracker() { } 

  std::pair<string_type, string_type> process(const string_type& qName) const
  {
    typename NamespaceSupportT::Parts parts = namespaces_.processName(qName, false);
    return std::make_pair(parts.URI, parts.localName);
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
