#ifndef ARABICA_XSLT_CALL_TEMPLATE_HANDLER_HPP
#define ARABICA_XSLT_CALL_TEMPLATE_HANDLER_HPP

#include "../xslt_call_template.hpp"
#include "xslt_with_param_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class CallTemplateHandler : public SAX::DefaultHandler<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  CallTemplateHandler(CompilationContext<string_type, string_adaptor>& context) :
    context_(context),
    callTemplate_(0)
  {
  } // CallTemplateHandler

  virtual void startElement(const string_type& namespaceURI,
                            const string_type& localName,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(callTemplate_ == 0)
    {
      static const ValueRule rules[] = { { "name", true, 0, 0 },
                                         { 0, false, 0, 0 } };
    
      std::map<string_type, string_type> attrs = gatherAttributes(qName, atts, rules);

      string_type name = context_.processInternalQName(attrs["name"]).clarkName();

      callTemplate_ = new CallTemplate<string_type, string_adaptor>(name);
      return;
    } // if(callTemplate_ == 0)

    if((namespaceURI == StylesheetConstant::NamespaceURI()) && (localName == "with-param"))
    {
      context_.push(0,
                    new WithParamHandler<string_type, string_adaptor>(context_, *callTemplate_),
                    namespaceURI, 
                    localName, 
                    qName, 
                    atts);
       return;
    } // if(localName == "with-param")
  
    throw SAX::SAXException("xsl:call-template can only contain xsl:sort and xsl:with-param elements.");
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    context_.parentContainer().add_item(callTemplate_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& /* ch */)
  {
  } // characters

private:
  CompilationContext<string_type, string_adaptor>& context_;
  CallTemplate<string_type, string_adaptor>* callTemplate_;
}; // class CallTemplateHandler

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CALL_TEMPLATE_HANDLER_HPP

