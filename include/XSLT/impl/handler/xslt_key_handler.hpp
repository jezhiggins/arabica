#ifndef ARABICA_XSLT_KEY_HANDLER_HPP
#define ARABICA_XSLT_KEY_HANDLER_HPP

#include "../xslt_key.hpp"
#include <XML/XMLCharacterClasses.hpp>

namespace Arabica
{
namespace XSLT
{

class KeyHandler : public SAX::DefaultHandler<std::string>
{
public:
  KeyHandler(CompilationContext& context) :
    context_(context),
    key_(0)
  {
  } // KeyHandler

  virtual void startElement(const std::string& namespaceURI,
			    const std::string& localName,
			    const std::string& qName,
			    const SAX::Attributes<std::string>& atts)
  {
    if(key_ != 0)
      throw SAX::SAXException(qName + " can not contain elements");

    static const ValueRule rules[] = { { "name", true, 0 },
                                       { "match", true, 0 }, 
                                       { "use", true, 0 },
                                       { 0, false, 0 } };

    std::map<std::string, std::string> attrs = gatherAttributes(qName, atts, rules);
    name_ = context_.processInternalQName(attrs["name"]).clarkName();
    Key::MatchExprList matches = context_.xpath_match(attrs["match"]);
    Arabica::XPath::XPathExpression<std::string> use = context_.xpath_expression(attrs["use"]);

    key_ = new Key(matches, use);
  } // startElement

  virtual void endElement(const std::string& namespaceURI,
			  const std::string& localName,
			  const std::string& qName)
  {
    context_.stylesheet().add_key(name_, key_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    for(std::string::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
      if(!Arabica::XML::is_space(*i))
        throw SAX::SAXException("xsl:key element must be empty");
  } // characters

private:
  CompilationContext& context_;
  std::string name_;
  Key* key_;
}; // class KeyHandler

} // namespace XSLT
} // namespace Arabica

#endif
