#ifndef ARABICA_XSLT_VALUE_OF_HANDLER_HPP
#define ARABICA_XSLT_VALUE_OF_HANDLER_HPP

#include <XML/XMLCharacterClasses.hpp>
#include "../xslt_value_of.hpp"

namespace Arabica
{
namespace XSLT
{

class ValueOfHandler : public SAX::DefaultHandler<std::string>
{
public:
  ValueOfHandler(CompilationContext& context) : 
    context_(context),
    valueOf_(0)
  {
  } // ValueOfHandler

  virtual void startElement(const std::string& /* namespaceURI */,
                            const std::string& /* localName */,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(valueOf_ == 0)
    {
      static const ValueRule rules[] = { { "select", true, 0, 0 },
                                         { "disable-output-escaping", false, No, AllowedYesNo },
                                         { 0, false, 0, 0 } };

      std::map<std::string, std::string> attrs = gatherAttributes(qName, atts, rules);
      valueOf_ = new ValueOf(context_.xpath_expression(attrs["select"]), 
			     attrs["disable-output-escaping"] == Yes);
      return;
    } // if(valueOf_ == 0)

    throw SAX::SAXException(qName + " can not contain elements");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    context_.parentContainer().add_item(valueOf_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    verifyNoCharacterData(ch, "xsl:value-of");
  } // characters

private:
  CompilationContext& context_;
  ValueOf* valueOf_;
}; // class ValueOfHandler

} //namespace XSLT
} //namespace Arabica

#endif 

