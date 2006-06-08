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
#include <XML/UnicodeCharacters.h>

namespace SAX
{

template<class string_type, class string_adaptor_type>
struct XMLBaseConstants
{
  typedef string_type stringT;
  typedef string_adaptor_type string_adaptorT;

  const stringT xml;
  const stringT xml_uri;
  const stringT colon;
  const stringT base;

  XMLBaseConstants() :
    xml(string_adaptorT().construct_from_utf8("xml")),
    xml_uri(string_adaptorT().construct_from_utf8("http://www.w3.org/XML/1998/namespace")),
    colon(string_adaptorT().construct_from_utf8(":")),
    base(string_adaptorT().construct_from_utf8("base"))
  {
  } // XMLBaseConstants
}; // struct XMLBaseConstants

template<class string_type, class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
class basic_XMLBaseSupport
{
public:
  typedef string_type stringT;
  typedef string_adaptor_type string_adaptorT;
  typedef typename string_adaptor_type::value_type valueT;
  typedef basic_Attributes<stringT> AttributesT;

  basic_XMLBaseSupport() :
      depth_(0) { }

  void setDocumentLocation(const stringT& loc)
  {
    bases_.push(std::make_pair(-1, loc));
  } // setDocumentLocation

  void startElement(const AttributesT& atts)
  {
    ++depth_;
    stringT base = atts.getValue(xbc_.xml_uri, xbc_.base);
    if(base.empty())
      return;

    stringT baseURI = absolutiseAndTrim(currentBase(), base);
    bases_.push(std::make_pair(depth_, baseURI));
  } // startElement

  void endElement()
  {
    if(currentDepth() == depth_)
      bases_.pop();
    --depth_;
  } // endElement

  stringT makeAbsolute(const stringT& spec)
  {
    return absolutise(currentBase(), spec);
  } // makeAbsolute

private:
  stringT absolutise(const stringT& baseURI, const stringT& location)
  {
    static const stringT SCHEME_MARKER = string_adaptorT::construct_from_utf8("://");
    static const valueT FORWARD_SLASH = string_adaptorT::convert_from_utf8(Arabica::Unicode<char>::SLASH);

    if(location.find(SCHEME_MARKER) != stringT::npos())
      return location;

    std::ostringstream ss;
    if(location[0] == FORWARD_SLASH)
    {
      // prepend URI scheme and location
      size_t schemeLen = baseURI.find(SCHEME_MARKER) + SCHEME_MARKER.length();
      ss << baseURI.substr(0, baseURI.find(FORWARD_SLASH, schemeLen+1));
    }
    else
    {
      // relative
      ss << baseURI;
      if(baseURI.find(FORWARD_SLASH) == baseURI.length()-1)
        ss << FORWARD_SLASH;
    }
    ss << location;

    return string_adaptorT::construct_from_utf8(ss.str().c_str());
  } // absolutise

  stringT absolutiseAndTrim(const stringT& baseURI, const stringT& location)
  {
    static const valueT FORWARD_SLASH = string_adaptorT::convert_from_utf8(Arabica::Unicode<char>::SLASH);

    stringT newlocation = absolutise(baseURI, location);
    if(newlocation[newlocation.length()] == FORWARD_SLASH)
      return newlocation;

    return newlocation.substr(0, newlocation.rfind(FORWARD_SLASH)+1);
  } // absolutiseAndTrim

  stringT currentBase() const
  {
    if(!bases_.size())
      return stringT();
    return bases_.top().second;
  } // currentBase()

  int currentDepth() const
  {
    if(!bases_.size())
      return -1;
    return bases_.top().first;
  } // currentDepths

private:
  typedef std::pair<int, stringT> baseInfoT;
  typedef std::stack<baseInfoT> baseStackT;

  baseStackT bases_;
  int depth_;

  const XMLBaseConstants<stringT, string_adaptorT> xbc_;

  // no impl
  basic_XMLBaseSupport(const basic_XMLBaseSupport&);
  basic_XMLBaseSupport& operator=(const basic_XMLBaseSupport&);
  bool operator==(const basic_XMLBaseSupport&);
}; // class basic_XMLBaseSupport

typedef basic_XMLBaseSupport<std::string> XMLBaseSupport;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_XMLBaseSupport<std::wstring> wXMLBaseSupport;
#endif

} // namespace SAX

#endif

