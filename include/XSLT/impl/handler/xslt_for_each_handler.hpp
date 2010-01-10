#ifndef ARABICA_XSLT_FOR_EACH_HANDLER_HPP
#define ARABICA_XSLT_FOR_EACH_HANDLER_HPP

#include "../xslt_for_each.hpp"
#include "xslt_item_container_handler.hpp"
#include "xslt_sort_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class ForEachHandler : public ItemContainerHandler<ForEach>
{
public:
  ForEachHandler(CompilationContext& context) :
      ItemContainerHandler<ForEach>(context),
      done_sort_(false)
  {
  } // ForEachHandler

protected:
  virtual ForEach* createContainer(const std::string& /* namespaceURI */,
                                   const std::string& /* localName */,
                                   const std::string& qName,
                                   const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "select", true, 0, 0 },
                                       { 0, false, 0, 0 } };
    std::string select = gatherAttributes(qName, atts, rules)["select"];

    return new ForEach(context().xpath_expression(select));
  } // createContainer

  virtual bool createChild(const std::string& namespaceURI,
                           const std::string& localName,
                           const std::string& qName,
                           const SAX::Attributes<std::string>& atts)
  {
    if((namespaceURI == StylesheetConstant::NamespaceURI()) &&
       (localName == "sort"))
    {
      if(!done_sort_)
      {
        context().push(0,
                       new SortHandler(context(), *container()),
                       namespaceURI, 
                       localName, 
                       qName, 
                       atts);
        return true;
      }
      else
        throw SAX::SAXException("xsl:sort must immediately follow xsl:for-each");
    } // if ...
    done_sort_ = true;
    return ItemContainerHandler<ForEach>::createChild(namespaceURI, localName, qName, atts);
  } // createChild

private:
  bool done_sort_;
}; // class ForEachHandler

} // namespace XSLT
} // namespace Arabica

#endif

