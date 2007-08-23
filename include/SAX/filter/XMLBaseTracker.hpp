#ifndef ARABICA_SAX_XMLBASE_TRACKER_HPP
#define ARABICA_SAX_XMLBASE_TRACKER_HPP

#include <SAX/ArabicaConfig.h>
#include <SAX/helpers/XMLFilterImpl.h>
#include <SAX/helpers/XMLBaseSupport.h>
#include <Utils/StringAdaptor.h>

namespace SAX
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XMLBaseTracker : public basic_XMLFilterImpl<string_type>
{
  typedef basic_XMLBaseSupport<string_type, string_adaptor> XMLBaseSupportT;
  typedef basic_XMLFilterImpl<string_type> XMLFilterT;

public:
  typedef basic_XMLReader<string_type> XMLReaderT;
  typedef basic_Locator<string_type> LocatorT;
  typedef basic_Attributes<string_type> AttributesT;

  XMLBaseTracker() : 
    basic_XMLFilterImpl<string_type>(),
    locator_(0),
    base_set_(false)
  { 
  } // XMLBaseTracker

  XMLBaseTracker(XMLReaderT& parent) : 
    basic_XMLFilterImpl<string_type>(parent),
    locator_(0),
    base_set_(false)
  { 
  } // XMLBaseTracker

  virtual ~XMLBaseTracker() { } 

  void setDocumentLocation(const string_type& loc)
  {
    setDocLoc(loc);
  } // setDocumentLocation

  virtual void setDocumentLocator(const LocatorT& locator)
  {
    locator_ = &locator;
    XMLFilterT::setDocumentLocator(locator);
  } // setDocumentLocator

  virtual void startElement(const string_type& namespaceURI, const string_type& localName,
                            const string_type& qName, const AttributesT& atts)
  {
    xmlbase_.startElement(atts);
    XMLFilterT::startElement(namespaceURI, localName, qName, atts);
  } // startElement

  virtual void endElement(const string_type& namespaceURI, const string_type& localName,
                          const string_type& qName)
  {
    XMLFilterT::endElement(namespaceURI, localName, qName);
    xmlbase_.endElement();
  } // endElement

  string_type currentBase() const
  {
    if(!base_set_ && locator_)
      setDocLoc(locator_->getSystemId());
    return xmlbase_.currentBase();
  } // currentBase

  string_type makeAbsolute(const string_type& url) const
  {
    if(!base_set_ && locator_)
      setDocLoc(locator_->getSystemId());
    return xmlbase_.makeAbsolute(url);
  } // makeAbsolute

private:
  void setDocLoc(const string_type& loc) const
  {
    base_set_ = true;
    xmlbase_.setDocumentLocation(loc);
  } // setDocLoc

  mutable XMLBaseSupportT xmlbase_;
  const LocatorT* locator_;
  mutable bool base_set_;
}; // class XMLBaseTracker

} // namespace SAX

#endif
