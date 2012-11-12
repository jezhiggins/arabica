#ifndef ARABICA_XSLT_COPY_HANDLER_HPP
#define ARABICA_XSLT_COPY_HANDLER_HPP

#include "../xslt_copy.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class CopyHandler : public ItemContainerHandler<Copy<string_type, string_adaptor> >
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
public:
  CopyHandler(CompilationContext<string_type, string_adaptor>& context) :
      ItemContainerHandler<Copy<string_type, string_adaptor> >(context)
  {
  } // CopyHandler

  virtual Copy<string_type, string_adaptor>* createContainer(const string_type& /* namespaceURI */,
                                const string_type& /* localName */,
                                const string_type& qName,
                                const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const ValueRule<string_type> rules[] = { { SC::use_attribute_sets, false, 0, 0 },
                                                    { string_adaptor::empty_string(), false, 0, 0 } };
    string_type sets = gatherAttributes(qName, atts, rules)[SC::use_attribute_sets];

    return new Copy<string_type, string_adaptor>(sets);
  } // createContainer
}; // class WhenHandler

template<class string_type, class string_adaptor>
class CopyOfHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
public:
  CopyOfHandler(CompilationContext<string_type, string_adaptor>& context) : 
    context_(context),
    copyOf_(0)
  {
  } // CopyOfHandler

  virtual void startElement(const string_type& /* namespaceURI */,
                            const string_type& /* localName */,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(copyOf_ == 0)
    {
      static const ValueRule<string_type> rules[] = { { SC::select, true, 0, 0 },
                                                      { string_adaptor::empty_string(), false, 0, 0 } };
      string_type select = gatherAttributes(qName, atts, rules)[SC::select];

      copyOf_ = new CopyOf<string_type, string_adaptor>(context_.xpath_expression(select));

      return;
    } // if(copyOf_ == 0)

    throw SAX::SAXException(string_adaptor::asStdString(qName) + " can not contain elements");
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    context_.parentContainer().add_item(copyOf_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData<string_type, string_adaptor>(ch, SC::copy_of);
  } // characters

private:
  CompilationContext<string_type, string_adaptor>& context_;
  CopyOf<string_type, string_adaptor>* copyOf_;
}; // class CopyOfHandler

} // namespace XSLT
} // namespace Arabica

#endif

