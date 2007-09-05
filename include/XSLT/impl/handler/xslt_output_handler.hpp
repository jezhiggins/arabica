#ifndef ARABICA_XSLT_OUTPUT_HANDLER_HPP
#define ARABICA_XSLT_OUTPUT_HANDLER_HPP

#include "xslt_value_validation.hpp"

namespace Arabica
{
namespace XSLT
{

class OutputHandler : public SAX::DefaultHandler<std::string>
{
public:
  OutputHandler(CompilationContext& context) :
    context_(context)
  {
  } // OutputHandler

  virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(settings_.empty())
    {
      static const char* AllowedMethods[] = { "xml", "html", "text", 0 };
      static const ValueRule rules[] = { { "method", false, "xml", AllowedMethods },
                                         { "version", false, "1.0" },
                                         { "encoding", false, "UTF-8" },
                                         { "omit-xml-declaration", false, No, AllowedYesNo },
                                         { "standalone", false, "", AllowedYesNo },
                                         { "doctype-public", false, ""},
                                         { "doctype-system", false, ""},
                                         { "cdata-section-elements", false, ""},
                                         { "indent", false, No, AllowedYesNo },
                                         { "media-type", false, "" },
                                         { 0, false, 0 } };
      settings_ = gatherAttributes(qName, atts, rules);

      return;
    } // if(settings_ == 0)

    throw SAX::SAXException(qName + " can not contain elements");
  } // startElement

  virtual void endElement(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName)
  {
    context_.stylesheet().output_settings(settings_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    throw SAX::SAXException("xsl:output must be empty");
  } // characters
 
private:
  CompilationContext& context_;
  Output::Settings settings_;
}; // class OutputHandler

} // namespace XSLT
} // namespace Arabica

#endif
