#ifndef ARABICA_XSLT_FOR_EACH_HANDLER_HPP
#define ARABICA_XSLT_FOR_EACH_HANDLER_HPP

#include "../xslt_for_each.hpp"
#include "xslt_item_container_handler.hpp"
#include "xslt_sort_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ForEachHandler : public ItemContainerHandler<ForEach<string_type, string_adaptor> >
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
  typedef AttributeValidators<string_type, string_adaptor> AV;
  typedef ItemContainerHandler<ForEach<string_type, string_adaptor> > baseT;

public:
  ForEachHandler(CompilationContext<string_type, string_adaptor>& context) :
      baseT(context),
      done_sort_(false)
  {
  } // ForEachHandler

protected:
  virtual ForEach<string_type, string_adaptor>* createContainer(const string_type& /* namespaceURI */,
                                   const string_type& /* localName */,
                                   const string_type& qName,
                                   const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const AV rules = AV::rule(SC::select, true);
    string_type select = rules.gather(qName, atts)[SC::select];

    return new ForEach<string_type, string_adaptor>(baseT::context().xpath_expression(select));
  } // createContainer

  virtual bool createChild(const string_type& namespaceURI,
                           const string_type& localName,
                           const string_type& qName,
                           const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if((namespaceURI == StylesheetConstant<string_type, string_adaptor>::NamespaceURI) &&
       (localName == SC::sort))
    {
      if(!done_sort_)
      {
        baseT::context().push(0,
                       new SortHandler<string_type, string_adaptor>(baseT::context(), *baseT::container()),
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
    return baseT::createChild(namespaceURI, localName, qName, atts);
  } // createChild

private:
  bool done_sort_;
}; // class ForEachHandler

} // namespace XSLT
} // namespace Arabica

#endif

