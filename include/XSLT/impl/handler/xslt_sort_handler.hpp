#ifndef ARABICA_XSLT_SORT_HANDLER_HPP
#define ARABICA_XSLT_SORT_HANDLER_HPP

#include "../xslt_sort.hpp"

namespace Arabica
{
namespace XSLT
{

class SortHandler : public SAX::DefaultHandler<std::string>
{ 
public:
  SortHandler(CompilationContext& context,
              Sortable& sortee) : 
    context_(context),
    sortee_(sortee),
    sort_(0)
  {
  } // SortHandler

  virtual void startElement(const std::string& /* namespaceURI */,
                            const std::string& /* localName */,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(sort_ == 0)
    {
      static const ValueRule rules[] = { { "select", false, ".", 0 },
                                         { "lang", false, 0, 0 },
                                         { "data-type", false, "text", 0 },
                                         { "order", false, "ascending", 0 },
                                         { "case-order", false, "upper-first", 0 },
                                         { 0, false, 0, 0 } };

      std::map<std::string, std::string> attr = gatherAttributes(qName, atts, rules);

      Arabica::XPath::XPathExpressionPtr<std::string> select, lang, datatype, order, caseorder;
      select = context_.xpath_expression(attr["select"]);
      datatype = context_.xpath_attribute_value_template(attr["data-type"]);
      order = context_.xpath_attribute_value_template(attr["order"]);
      caseorder = context_.xpath_attribute_value_template(attr["case-order"]);

      if(attr["lang"].length() != 0)
	std::cerr << "Sorry!  Don't support xsl:sort lang attribute yet" << std::endl;
 
      sort_ = new Sort(select,
                       lang, 
                       datatype, 
                       order,
                       caseorder);
      return;
    } // if(sort_ == 0)

    throw SAX::SAXException("xsl:sort can not contain elements");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    sortee_.add_sort(sort_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    verifyNoCharacterData(ch, "xsl:sort");
  } // characters

private:
  CompilationContext& context_;
  Sortable& sortee_;
  Sort* sort_;
}; // SortHandler

} // namespace XSLT
} // namespace Arabica

#endif

