#ifndef ARABICA_XSLT_SORT_HANDLER_HPP
#define ARABICA_XSLT_SORT_HANDLER_HPP

#include "../xslt_sort.hpp"

namespace Arabica
{
namespace XSLT
{

class SortHandler : public SAX::DefaultHandler
{ 
public:
  SortHandler(CompilationContext& context,
              Sortable& sortee) : 
    context_(context),
    sortee_(sortee),
    sort_(0)
  {
  } // SortHandler

  virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes& atts)
  {
    if(sort_ == 0)
    {
      static const ValueRule rules[] = { { "select", false, "." },
                                         { "lang", false, 0 },
                                         { "data-type", false, "text" },
                                         { "order", false, "ascending" },
                                         { "case-order", false, 0 }, 
                                         { 0, false, 0 } };

      std::map<std::string, std::string> attr = gatherAttributes(qName, atts, rules);

      Arabica::XPath::XPathExpressionPtr<std::string> select, lang, datatype, order, caseorder;
      select = context_.xpath().compile_expr(attr["select"]);
      datatype = context_.xpath().compile_attribute_value_template(attr["data-type"]);
      order = context_.xpath().compile_attribute_value_template(attr["order"]);

      sort_ = new Sort(select,
                       lang, 
                       datatype, 
                       order,
                       caseorder);
      return;
    } // if(sort_ == 0)

    throw SAX::SAXException("xsl:sort can not contain elements");
  } // startElement

  virtual void endElement(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName)
  {
    sortee_.add_sort(sort_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    for(std::string::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
      if(!Arabica::XML::is_space(*i))
        throw SAX::SAXException("xsl:sort element must be empty");
  } // characters

private:
  CompilationContext& context_;
  Sortable& sortee_;
  Sort* sort_;
}; // SortHandler

} // namespace XSLT
} // namespace Arabica

#endif

