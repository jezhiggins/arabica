#ifndef ARABICA_XSLT_APPLY_IMPORTS_HANDLER_HPP
#define ARABICA_XSLT_APPLY_IMPORTS_HANDLER_HPP

#include "../xslt_apply_imports.hpp"

namespace Arabica
{
namespace XSLT
{

class ApplyImportsHandler : public SAX::DefaultHandler<std::string>
{
public:
  ApplyImportsHandler(CompilationContext& context):
    context_(context),
    applyImports_(0)
  {
  } // ApplyImportsHandler

  ~ApplyImportsHandler() 
  {
  } // ~ApplyImportsHandler

  virtual void startElement(const std::string& /* namespaceURI */,
			    const std::string& /* localName */,
			    const std::string& /* qName */,
			    const SAX::Attributes<std::string>& atts)
  {
    if(applyImports_ == 0)
    {
      if(atts.getLength() != 0)
	throw SAX::SAXException("xsl:apply-imports element does not have any attributes");
      applyImports_ = new ApplyImports();
      return;
    } // if(applyImports_ == 0)

    throw SAX::SAXException("xsl:apply-imports element must be empty");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
			  const std::string& /* localName */,
			  const std::string& /* qName */)
  {
    context_.parentContainer().add_item(applyImports_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    verifyNoCharacterData(ch, "xsl:apply-imports");
  } // characters

private:
  CompilationContext& context_;
  ApplyImports* applyImports_;
}; // class ApplyImportsHandler

} // namespace XSLT
} // namespace Arabica


#endif
