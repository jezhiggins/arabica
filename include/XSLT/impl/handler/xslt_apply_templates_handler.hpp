#ifndef ARABICA_XSLT_APPLY_TEMPLATES_HANDLER_HPP
#define ARABICA_XSLT_APPLY_TEMPLATES_HANDLER_HPP

#include "../xslt_apply_templates.hpp"
#include "xslt_sort_handler.hpp"
#include "xslt_with_param_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class ApplyTemplatesHandler : public SAX::DefaultHandler<stringT, adaptorT>
{
  typedef StylesheetConstant<stringT, adaptorT> SC;
  typedef AttributeValidators<stringT, adaptorT> AV;

public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  ApplyTemplatesHandler(CompilationContext<string_type, string_adaptor>& context) :
    context_(context),
    applyTemplates_(0)
  {
  } // ApplyTemplatesHandler

  virtual void startElement(const string_type& namespaceURI,
                            const string_type& localName,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(applyTemplates_ == 0)
    {
      static const AV rules = AV::rule(SC::select, false)
                                 .rule(SC::mode, false);

      std::map<string_type, string_type> attrs = rules.gather(qName, atts);
    
      const string_type& select = attrs[SC::select];
      Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> xpath;
      if(select != string_adaptor::empty_string())
        xpath = context_.xpath_expression(select);

      string_type mode;
      if(attrs[SC::mode] != string_adaptor::empty_string())
        mode = context_.processInternalQName(attrs[SC::mode]).clarkName();
      applyTemplates_ = new ApplyTemplates<string_type, string_adaptor>(xpath, mode);

      return;
    } // if(applyTemplates_ == 0)

    if(namespaceURI == StylesheetConstant<string_type, string_adaptor>::NamespaceURI)
    {
      if(localName == SC::sort)
      {

        context_.push(0,
                      new SortHandler<string_type, string_adaptor>(context_, *applyTemplates_),
                      namespaceURI, 
                      localName, 
                      qName, 
                      atts);
        return;
      } // if(localName == "sort")

      if(localName == SC::with_param)
      {
        context_.push(0,
                      new WithParamHandler<string_type, string_adaptor>(context_, *applyTemplates_),
                      namespaceURI, 
                      localName, 
                      qName, 
                      atts);
        return;
      } // if(localName == "sort")
    } // if ...
  
    throw SAX::SAXException("xsl:apply-templates can only contain xsl:sort and xsl:with-param elements.");
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    context_.parentContainer().add_item(applyTemplates_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData<string_type, string_adaptor>(ch, SC::apply_templates);
  } // characters

private:
  CompilationContext<string_type>& context_;
  ApplyTemplates<string_type, string_adaptor>* applyTemplates_;
}; // class ApplyTemplatesHandler

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_APPLY_TEMPLATES_HANDLER_HPP

