#ifndef ARABICA_XSLT_FOREIGN_ELEMENT_HPP
#define ARABICA_XSLT_FOREIGN_ELEMENT_HPP

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ForeignElementHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
public:
  ForeignElementHandler(CompilationContext<string_type, string_adaptor>& context) :
         context_(context),
         depth_(0)
  {
  } // ForeignElementHandler

  virtual void startElement(const string_type& /* namespaceURI */,
                            const string_type& /* localName */,
                            const string_type& /* qName */,
                            const SAX::Attributes<string_type, string_adaptor>& /* atts */)
  {
    ++depth_;
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    if(--depth_ == 0)
      context_.pop();
  } // endElement

private:
  CompilationContext<string_type, string_adaptor>& context_;
  unsigned int depth_;
}; // class ForeignElementHandler

} // namespace XSLT
} // namespace Arabica

#endif

