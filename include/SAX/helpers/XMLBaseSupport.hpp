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
#include <XML/UnicodeCharacters.hpp>
#include <Utils/uri.hpp>

namespace Arabica
{
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
class XMLBaseSupport
{
public:
  typedef string_type stringT;
  typedef string_adaptor_type string_adaptorT;
  typedef typename string_adaptor_type::value_type valueT;
  typedef Attributes<stringT> AttributesT;

  XMLBaseSupport() :
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

    stringT baseURI = absolutise(currentBase(), base);
    bases_.push(std::make_pair(depth_, baseURI));
  } // startElement

  void endElement()
  {
    if(currentDepth() == depth_)
      bases_.pop();
    --depth_;
  } // endElement

  stringT currentBase() const
  {
    if(!bases_.size())
      return stringT();
    return bases_.top().second;
  } // currentBase()

  stringT makeAbsolute(const stringT& spec) const
  {
    return absolutise(currentBase(), spec);
  } // makeAbsolute

private:
  stringT absolutise(const stringT& baseURI, const stringT& location) const
  {
    Arabica::io::URI absolute(Arabica::io::URI(baseURI), location);
    return string_adaptorT::construct_from_utf8(absolute.as_string().c_str());
  } // absolutise

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
  XMLBaseSupport(const XMLBaseSupport&);
  XMLBaseSupport& operator=(const XMLBaseSupport&);
  bool operator==(const XMLBaseSupport&);
}; // class XMLBaseSupport

} // namespace SAX
} // namespace Arabica

#endif

