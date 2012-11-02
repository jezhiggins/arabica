#ifndef ARABICA_XSLT_STYLESHEETPARSER_HPP
#define ARABICA_XSLT_STYLESHEETPARSER_HPP

#include <SAX/filter/NamespaceTracker.hpp>
#include <SAX/filter/XMLBaseTracker.hpp>
#include <SAX/filter/TextCoalescer.hpp>


namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class StylesheetParser
{
public:
	typedef SAX::ContentHandler<string_type, string_adaptor> ContentHandlerT;
	typedef SAX::InputSource<string_type, string_adaptor> InputSourceT;
  typedef SAX::XMLReader<string_type, string_adaptor> XMLReaderT;
  typedef SAX::TextCoalescer<string_type, string_adaptor> TextCoalescerT;
  typedef SAX::XMLBaseTracker<string_type, string_adaptor> XMLBaseTrackerT;
  typedef SAX::NamespaceTracker<string_type, string_adaptor> NamespaceTrackerT;
  typedef XML::QualifiedName<string_type, string_adaptor> QualifiedNameT;

  StylesheetParser() { }

  void setContentHandler(ContentHandlerT& handler)
  {
    namespace_tracker_.setContentHandler(handler);
  } // setContentHandler

  ContentHandlerT& contentHandler() 
  {
    return text_coalescer_;
  } // contentHandler
 
  void parse(InputSourceT& source)
  {
    XMLReaderT base_parser;
    text_coalescer_.setParent(base_parser);
    xmlbase_tracker_.setParent(text_coalescer_);
    namespace_tracker_.setParent(xmlbase_tracker_);

    namespace_tracker_.parse(source);
  } // parse

  string_type namespaceURI(const string_type& prefix) const
  {
    return namespace_tracker_.getURI(prefix);
  } // namespaceURI

  QualifiedNameT processElementQName(const string_type& rawName) const
  {
    QualifiedNameT qName = namespace_tracker_.processElementName(rawName);
    verifyQName(qName);
    return qName;
  } // processElementQName

  QualifiedNameT processInternalQName(const string_type& rawName) const
  {
    QualifiedNameT qName = namespace_tracker_.processName(rawName);
    verifyQName(qName);
    return qName;
  } // processQName

  std::map<string_type, string_type> inScopeNamespaces() const
  {
    return namespace_tracker_.inScopeNamespaces();
  } // inScopeNamespaces

  string_type setBase(const string_type& loc)
  {
    string_type current = currentBase();
    xmlbase_tracker_.setDocumentLocation(loc);
    return current;
  } // setBase
  
  string_type currentBase() const
  {
    return xmlbase_tracker_.currentBase();
  } // currentBase

  string_type makeAbsolute(const string_type& href) 
  {
    return xmlbase_tracker_.makeAbsolute(href);
  } // makeAbsolute

private:
  void verifyQName(const QualifiedNameT& qName) const
  {
    if(qName.has_prefix() && !qName.has_namespaceUri())
      throw SAX::SAXException("Namespace prefix '" + qName.prefix() + "' is not bound");
  } // verifyQName
  
  TextCoalescerT text_coalescer_;
  XMLBaseTrackerT xmlbase_tracker_;
  NamespaceTrackerT namespace_tracker_;

  StylesheetParser(const StylesheetParser&);
  StylesheetParser operator=(const StylesheetParser&);
  bool operator==(const StylesheetParser&);
}; // class StylesheetParser 

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_STYLESHEETPARSER_HPP

