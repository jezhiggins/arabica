#ifndef ARABICA_XSLT_OUTPUT_HANDLER_HPP
#define ARABICA_XSLT_OUTPUT_HANDLER_HPP

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class OutputHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
public:
  OutputHandler(CompilationContext<string_type, string_adaptor>& context) :
    context_(context)
  {
  } // OutputHandler

  virtual void startElement(const string_type& /* namespaceURI */,
                            const string_type& /* localName */,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
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

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    context_.stylesheet().output_settings(settings_, cdataElements_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData(ch, "xsl:output");
  } // characters
 
private:
  typedef typename Output<string_type, string_adaptor>::CDATAElements CDATAElements;
  typedef typename Output<string_type, string_adaptor>::Settings Settings;

  CDATAElements extractCDATAElements(const string_type& cdata_section_elements) const
  {
    CDATAElements elements;

    if(cdata_section_elements.empty())
      return elements;

    std::istringstream is(text::normalize_whitespace<string_type, string_adaptor>(cdata_section_elements));
    while(!is.eof())
    {
      string_type e;
      is >> e;

      XML::QualifiedName<string_type, string_adaptor> qualifiedName = context_.processElementQName(e);
      elements.insert(QName::create(qualifiedName));
    } // while

    return elements;
  } // extractCDATAElements

  CompilationContext<string_type, string_adaptor>& context_;
  Settings settings_;
  CDATAElements cdataElements_;
}; // class OutputHandler

} // namespace XSLT
} // namespace Arabica

#endif
