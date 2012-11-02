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
      static const ValueRule rules[] = { { "disable-output-escaping", false, No, AllowedYesNo },
                                         { 0, false, 0, 0 } };
      text_ = new Text<string_type, string_adaptor>(gatherAttributes(qName, atts, rules)["disable-output-escaping"] == Yes);
      return;
    } // if(text_ == 0)

    throw SAX::SAXException(qName + " can not contain elements");
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

