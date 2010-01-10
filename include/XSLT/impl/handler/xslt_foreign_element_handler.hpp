#ifndef ARABICA_XSLT_FOREIGN_ELEMENT_HPP
#define ARABICA_XSLT_FOREIGN_ELEMENT_HPP

namespace Arabica
{
namespace XSLT
{

class ForeignElementHandler : public SAX::DefaultHandler<std::string>
{
public:
  ForeignElementHandler(CompilationContext& context) :
         context_(context),
         depth_(0)
  {
  } // ForeignElementHandler

  virtual void startElement(const std::string& /* namespaceURI */,
                            const std::string& /* localName */,
                            const std::string& /* qName */,
                            const SAX::Attributes<std::string>& /* atts */)
  {
    ++depth_;
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    if(--depth_ == 0)
      context_.pop();
  } // endElement

private:
  CompilationContext& context_;
  unsigned int depth_;
}; // class ForeignElementHandler

} // namespace XSLT
} // namespace Arabica

#endif

