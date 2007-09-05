#ifndef ARABICA_XSLT_APPLY_TEMPLATES_HANDLER_HPP
#define ARABICA_XSLT_APPLY_TEMPLATES_HANDLER_HPP

#include "../xslt_apply_templates.hpp"
#include "xslt_sort_handler.hpp"
#include "xslt_with_param_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class ApplyTemplatesHandler : public SAX::DefaultHandler<std::string>
{
public:
  ApplyTemplatesHandler(CompilationContext& context) :
    context_(context),
    applyTemplates_(0)
  {
  } // ApplyTemplatesHandler

  virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(applyTemplates_ == 0)
    {
      static const ValueRule rules[] = { { "select", false, 0 },
                                         { "mode", false, 0 },
                                         { 0, false, 0} };
      std::map<std::string, std::string> attrs = gatherAttributes(qName, atts, rules);
    
      const std::string& select = attrs["select"];
      Arabica::XPath::XPathExpressionPtr<std::string> xpath;
      if(select != "")
        xpath = context_.xpath().compile_expr(select);

      const std::string& mode = attrs["mode"];
      applyTemplates_ = new ApplyTemplates(xpath, mode);

      return;
    } // if(applyTemplates_ == 0)

    if(namespaceURI == StylesheetConstant::NamespaceURI())
    {
      if(localName == "sort")
      {

        context_.push(0,
                      new SortHandler(context_, *applyTemplates_),
                      namespaceURI, 
                      qName, 
                      localName, 
                      atts);
        return;
      } // if(localName == "sort")

      if(localName == "with-param")
      {
        context_.push(0,
                      new WithParamHandler(context_, *applyTemplates_),
                      namespaceURI, 
                      qName, 
                      localName, 
                      atts);
        return;
      } // if(localName == "sort")
    } // if ...
  
    throw SAX::SAXException("xsl:apply-templates can only contain xsl:sort and xsl:with-param elements.");
  } // startElement

  virtual void endElement(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName)
  {
    context_.parentContainer().add_item(applyTemplates_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    for(std::string::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
      if(!Arabica::XML::is_space(*i))
	throw SAX::SAXException("xsl:apply-templates element can only contain xsl:sort and xsl:with-param elements.");
  } // characters

private:
  CompilationContext& context_;
  ApplyTemplates* applyTemplates_;
}; // class ApplyTemplatesHandler

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_APPLY_TEMPLATES_HANDLER_HPP

