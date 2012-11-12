#ifndef ARABICA_XSLT_SORT_HANDLER_HPP
#define ARABICA_XSLT_SORT_HANDLER_HPP

#include "../xslt_sort.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class SortHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{ 
  typedef StylesheetConstant<string_type, string_adaptor> SC;

public:
  SortHandler(CompilationContext<string_type, string_adaptor>& context,
              Sortable<string_type, string_adaptor>& sortee) : 
    context_(context),
    sortee_(sortee),
    sort_(0)
  {
  } // SortHandler

  virtual void startElement(const string_type& /* namespaceURI */,
                            const string_type& /* localName */,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(sort_ == 0)
    {
      static const ValueRule<string_type> rules[] = { { SC::select, false, SC::current_xpath, 0 },
                                                      { SC::lang, false, 0, 0 },
                                                      { SC::data_type, false, SC::text, 0 },
                                                      { SC::order, false, SC::ascending, 0 },
                                                      { SC::case_order, false, SC::upper_first, 0 },
                                                      { 0, false, 0, 0 } };

      std::map<string_type, string_type> attr = gatherAttributes(qName, atts, rules);

      Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> select, lang, datatype, order, caseorder;
      select = context_.xpath_expression(attr[SC::select]);
      datatype = context_.xpath_attribute_value_template(attr[SC::data_type]);
      order = context_.xpath_attribute_value_template(attr[SC::order]);
      caseorder = context_.xpath_attribute_value_template(attr[SC::case_order]);

      if(attr[SC::lang].length() != 0)
	      std::cerr << "Sorry!  Don't support xsl:sort lang attribute yet" << std::endl;
 
      sort_ = new Sort<string_type, string_adaptor>(select,
                       lang, 
                       datatype, 
                       order,
                       caseorder);
      return;
    } // if(sort_ == 0)

    throw SAX::SAXException("xsl:sort can not contain elements");
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    sortee_.add_sort(sort_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData<string_type, string_adaptor>(ch, SC::sort);
  } // characters

private:
  CompilationContext<string_type, string_adaptor>& context_;
  Sortable<string_type, string_adaptor>& sortee_;
  Sort<string_type, string_adaptor>* sort_;
}; // SortHandler

} // namespace XSLT
} // namespace Arabica

#endif

