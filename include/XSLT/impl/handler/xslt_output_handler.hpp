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
  typedef AttributeValidators<string_type, string_adaptor> AV;

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
      static const AV rules = AV::rule(SC::method, false, SC::xml, AllowedValues<string_type>(SC::xml, SC::html, SC::text))
                                 .rule(SC::version, false, SC::Version)
                                 .rule(SC::encoding, false, SC::utf8)
                                 .rule(SC::omit_xml_declaration, false, SC::no, AllowedValues<string_type>(SC::yes, SC::no))
                                 .rule(SC::standalone, false, string_adaptor::empty_string(), AllowedValues<string_type>(SC::yes, SC::no))
                                 .rule(SC::doctype_public, false, string_adaptor::empty_string())
                                 .rule(SC::doctype_system, false, string_adaptor::empty_string())
                                 .rule(SC::cdata_section_elements, false, string_adaptor::empty_string())
                                 .rule(SC::indent, false, SC::no, AllowedValues<string_type>(SC::yes, SC::no))
                                 .rule(SC::media_type, false, string_adaptor::empty_string());

      settings_ = rules.gather(qName, atts);
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
