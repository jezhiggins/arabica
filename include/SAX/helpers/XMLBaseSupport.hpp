#ifndef ARABICA_XMLBASE_SUPPORT_H
#define ARABICA_XMLBASE_SUPPORT_H

/*
 * $Id$
 *
 * XMLBaseSupport is a helper class for tracking xml:base attributes.
 * Usage:
 *   set location of the containing document by calling setDocumentLocation
 *       this is usually done when during the setDocumentLocator SAX event
 *   forward each startElement and endElement event 
 *   to resolve a relative URL against the current base, call makeAbsolute
 *
 * Derived from org.apache.cocoon.xml.XMLBaseSupport.
 *
 * XML Base is described at http://www.w3.org/TR/xmlbase/
 */

#include <stack>
#include <utility>
#include <sstream>
#include <text/UnicodeCharacters.hpp>
#include <io/uri.hpp>

namespace Arabica
{
namespace SAX
{

template<class string_type, class string_adaptor>
struct XMLBaseConstants
{
  const string_type xml;
  const string_type xml_uri;
  const string_type colon;
  const string_type base;

  XMLBaseConstants() :
    xml(string_adaptor::construct_from_utf8("xml")),
    xml_uri(string_adaptor::construct_from_utf8("http://www.w3.org/XML/1998/namespace")),
    colon(string_adaptor::construct_from_utf8(":")),
    base(string_adaptor::construct_from_utf8("base"))
  {
  } // XMLBaseConstants
}; // struct XMLBaseConstants

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XMLBaseSupport
{
public:
  typedef typename string_adaptor::value_type valueT;
  typedef Attributes<string_type, string_adaptor> AttributesT;

  XMLBaseSupport() :
      depth_(0) { }

  void setDocumentLocation(const string_type& loc)
  {
    bases_.push(std::make_pair(-1, loc));
  } // setDocumentLocation

  void startElement(const AttributesT& atts)
  {
    ++depth_;
    string_type base = atts.getValue(xbc_.xml_uri, xbc_.base);
    if(base.empty())
      return;

    string_type baseURI = absolutise(currentBase(), base);
    bases_.push(std::make_pair(depth_, baseURI));
  } // startElement

  void endElement()
  {
    if(currentDepth() == depth_)
      bases_.pop();
    --depth_;
  } // endElement

  string_type currentBase() const
  {
    if(!bases_.size())
      return string_type();
    return bases_.top().second;
  } // currentBase()

  string_type makeAbsolute(const string_type& spec) const
  {
    return absolutise(currentBase(), spec);
  } // makeAbsolute

private:
  string_type absolutise(const string_type& baseURI, const string_type& location) const
  {
    Arabica::io::URI base(string_adaptor::asStdString(baseURI));
    Arabica::io::URI absolute(base, string_adaptor::asStdString(location));
    return string_adaptor::construct_from_utf8(absolute.as_string().c_str());
  } // absolutise

  int currentDepth() const
  {
    if(!bases_.size())
      return -1;
    return bases_.top().first;
  } // currentDepths

private:
  typedef std::pair<int, string_type> baseInfoT;
  typedef std::stack<baseInfoT> baseStackT;

  baseStackT bases_;
  int depth_;

  const XMLBaseConstants<string_type, string_adaptor> xbc_;

  // no impl
  XMLBaseSupport(const XMLBaseSupport&);
  XMLBaseSupport& operator=(const XMLBaseSupport&);
  bool operator==(const XMLBaseSupport&);
}; // class XMLBaseSupport

} // namespace SAX
} // namespace Arabica

#endif

