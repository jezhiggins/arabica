#ifndef ARABICA_XSLT_OUTPUT_HANDLER_HPP
#define ARABICA_XSLT_OUTPUT_HANDLER_HPP

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class OutputHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;

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
      static string_type AllowedMethods[] = { SC::xml, SC::html, SC::text, string_adaptor::empty_string() };
      static const ValueRule<string_type> rules[] = 
                                       { { SC::method, false, SC::xml, AllowedMethods },
                                         { SC::version, false, SC::Version, 0 },
                                         { SC::encoding, false, SC::utf8, 0 },
                                         { SC::omit_xml_declaration, false, SC::no, SC::AllowedYesNo },
                                         { SC::standalone, false, string_adaptor::empty_string(), SC::AllowedYesNo },
                                         { SC::doctype_public, false, string_adaptor::empty_string(), 0 },
                                         { SC::doctype_system, false, string_adaptor::empty_string(), 0 },
                                         { SC::cdata_section_elements, false, string_adaptor::empty_string(), 0 },
                                         { SC::indent, false, SC::no, SC::AllowedYesNo },
                                         { SC::media_type, false, string_adaptor::empty_string(), 0 },
                                         { string_adaptor::empty_string(), false, 0, 0 } };
      settings_ = gatherAttributes(qName, atts, rules);
      cdataElements_ = extractCDATAElements(settings_[SC::cdata_section_elements]);

      return;
    } // if(settings_ == 0)

    throw SAX::SAXException(string_adaptor::asStdString(qName) + " can not contain elements");
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
    verifyNoCharacterData<string_type, string_adaptor>(ch, SC::output);
  } // characters
 
private:
  typedef typename Output<string_type, string_adaptor>::CDATAElements CDATAElements;
  typedef typename Output<string_type, string_adaptor>::Settings Settings;

  CDATAElements extractCDATAElements(const string_type& cdata_section_elements) const
  {
    CDATAElements elements;

    if(cdata_section_elements.empty())
      return elements;

    std::basic_istringstream<string_adaptor::value_type>
                 is(text::normalize_whitespace<string_type, string_adaptor>(cdata_section_elements));
    while(!is.eof())
    {
      string_type e;
      is >> e;

      XML::QualifiedName<string_type, string_adaptor> qualifiedName = context_.processElementQName(e);
      elements.insert(QName<string_type, string_adaptor>::create(qualifiedName));
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
