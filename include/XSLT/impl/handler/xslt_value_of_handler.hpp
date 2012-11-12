#ifndef ARABICA_XSLT_VALUE_OF_HANDLER_HPP
#define ARABICA_XSLT_VALUE_OF_HANDLER_HPP

#include <XML/XMLCharacterClasses.hpp>
#include "../xslt_value_of.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ValueOfHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
public:
  ValueOfHandler(CompilationContext<string_type, string_adaptor>& context) : 
    context_(context),
    valueOf_(0)
  {
  } // ValueOfHandler

  virtual void startElement(const string_type& /* namespaceURI */,
                            const string_type& /* localName */,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(valueOf_ == 0)
    {
      static const ValueRule<string_type> rules[] = { { SC::select, true, 0, 0 },
                                                      { SC::disable_output_escaping, false, SC::no, SC::AllowedYesNo },
                                                      { 0, false, 0, 0 } };

      std::map<string_type, string_type> attrs = gatherAttributes(qName, atts, rules);
      valueOf_ = new ValueOf<string_type, string_adaptor>(context_.xpath_expression(attrs[SC::select]), 
			                                               attrs[SC::disable_output_escaping] == SC::yes);
      return;
    } // if(valueOf_ == 0)

    throw SAX::SAXException(string_adaptor::asStdString(qName) + " can not contain elements");
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    context_.parentContainer().add_item(valueOf_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData<string_type, string_adaptor>(ch, SC::value_of);
  } // characters

private:
  CompilationContext<string_type, string_adaptor>& context_;
  ValueOf<string_type, string_adaptor>* valueOf_;
}; // class ValueOfHandler

} //namespace XSLT
} //namespace Arabica

#endif 

