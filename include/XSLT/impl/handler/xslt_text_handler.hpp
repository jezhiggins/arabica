#ifndef ARABICA_XSLT_TEXT_HANDLER_HPP
#define ARABICA_XSLT_TEXT_HANDLER_HPP

#include "../xslt_text.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class TextHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
  typedef AttributeValidators<string_type, string_adaptor> AV;
public:
  TextHandler(CompilationContext<string_type, string_adaptor>& context) :
    context_(context),
    text_(0)
  {
  } // TextHandler

  virtual void startElement(const string_type& /* namespaceURI */,
                            const string_type& /* localName */,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(text_ == 0)
    {
      static const AV rules = AV::rule(SC::disable_output_escaping, false, SC::no, AllowedValues<string_type>(SC::yes, SC::no));
      text_ = new Text<string_type, string_adaptor>(rules.gather(qName, atts)[SC::disable_output_escaping] == SC::yes);
      return;
    } // if(text_ == 0)

    throw SAX::SAXException(string_adaptor::asStdString(qName) + " can not contain elements");
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    text_->set(buffer_);
    context_.parentContainer().add_item(text_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    buffer_ += ch;
  } // characters

private:
  CompilationContext<string_type, string_adaptor>& context_;
  Text<string_type, string_adaptor>* text_;
  string_type buffer_;
}; // class TextHandler

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_TEXT_TEMPLATE_HPP

