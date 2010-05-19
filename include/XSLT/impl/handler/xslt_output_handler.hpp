#ifndef ARABICA_XSLT_OUTPUT_HANDLER_HPP
#define ARABICA_XSLT_OUTPUT_HANDLER_HPP

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

  virtual void startElement(const std::string& /* namespaceURI */,
                            const std::string& /* localName */,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(settings_.empty())
    {
      static const char* AllowedMethods[] = { "xml", "html", "text", 0 };
      static const ValueRule rules[] = { { "method", false, "xml", AllowedMethods },
                                         { "version", false, "1.0", 0 },
                                         { "encoding", false, "UTF-8", 0 },
                                         { "omit-xml-declaration", false, No, AllowedYesNo },
                                         { "standalone", false, "", AllowedYesNo },
                                         { "doctype-public", false, "", 0},
                                         { "doctype-system", false, "", 0},
                                         { "cdata-section-elements", false, "", 0},
                                         { "indent", false, No, AllowedYesNo },
                                         { "media-type", false, "", 0 },
                                         { 0, false, 0, 0 } };
      settings_ = gatherAttributes(qName, atts, rules);
      cdataElements_ = extractCDATAElements(settings_["cdata-section-elements"]);

      return;
    } // if(settings_ == 0)

    throw SAX::SAXException(qName + " can not contain elements");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    context_.stylesheet().output_settings(settings_, cdataElements_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    verifyNoCharacterData(ch, "xsl:output");
  } // characters
 
private:
  Output::CDATAElements extractCDATAElements(const std::string& cdata_section_elements) const
  {
    Output::CDATAElements elements;

    if(cdata_section_elements.empty())
      return elements;

    std::istringstream is(text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(cdata_section_elements));
    while(!is.eof())
    {
      std::string e;
      is >> e;

      XML::QualifiedName<std::string> qualifiedName = context_.processElementQName(e);
      elements.insert(QName::create(qualifiedName));
    } // while

    return elements;
  } // extractCDATAElements

  CompilationContext& context_;
  Output::Settings settings_;
  Output::CDATAElements cdataElements_;
}; // class OutputHandler

} // namespace XSLT
} // namespace Arabica

#endif
