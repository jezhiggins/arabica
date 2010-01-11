#ifndef ARABICA_XSLT_TEXT_HANDLER_HPP
#define ARABICA_XSLT_TEXT_HANDLER_HPP

#include "../xslt_text.hpp"

namespace Arabica
{
namespace XSLT
{

class TextHandler : public SAX::DefaultHandler<std::string>
{
public:
  TextHandler(CompilationContext& context) :
    context_(context),
    text_(0)
  {
  } // TextHandler

  virtual void startElement(const std::string& /* namespaceURI */,
                            const std::string& /* localName */,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(text_ == 0)
    {
      static const ValueRule rules[] = { { "disable-output-escaping", false, No, AllowedYesNo },
                                         { 0, false, 0, 0 } };
      text_ = new Text(gatherAttributes(qName, atts, rules)["disable-output-escaping"] == Yes);
      return;
    } // if(text_ == 0)

    throw SAX::SAXException(qName + " can not contain elements");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    text_->set(buffer_);
    context_.parentContainer().add_item(text_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    buffer_ += ch;
  } // characters

private:
  CompilationContext& context_;
  Text* text_;
  std::string buffer_;
}; // class TextHandler

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_TEXT_TEMPLATE_HPP

