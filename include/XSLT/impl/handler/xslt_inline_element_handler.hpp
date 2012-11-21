#ifndef ARABICA_XSLT_INLINE_ELEMENT_HANDLER_HPP
#define ARABICA_XSLT_INLINE_ELEMENT_HANDLER_HPP

#include "../xslt_inline_element.hpp"
#include "xslt_item_container_handler.hpp"
#include "xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class InlineElementHandler : public ItemContainerHandler<InlineElement<string_type, string_adaptor> >
{
  typedef ItemContainerHandler<InlineElement<string_type, string_adaptor> > baseT;
  typedef StylesheetConstant<string_type, string_adaptor> SC;

public:
  InlineElementHandler(CompilationContext<string_type, string_adaptor>& context) :
      baseT(context)
  {
  } // InlineElementHandler

protected:
  virtual InlineElement<string_type, string_adaptor>* createContainer(const string_type& namespaceURI,
                                         const string_type& localName,
                                         const string_type& qName,
                                         const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    std::vector<InlineAttribute<string_type, string_adaptor> > inlineAtts;
    for(int i = 0; i != atts.getLength(); ++i)
    {      
      if(string_adaptor::find(atts.getQName(i), SC::xmlns_colon) == 0)
        continue;
      if(atts.getURI(i) == StylesheetConstant<string_type, string_adaptor>::NamespaceURI)
        continue;
      if(!baseT::context().isRemapped(atts.getURI(i)))
        inlineAtts.push_back(InlineAttribute<string_type, string_adaptor>(atts.getQName(i), 
                                             atts.getURI(i),
                                             baseT::context().xpath_attribute_value_template(atts.getValue(i))));
      else
      {
        std::pair<string_type, string_type> remap = baseT::context().remappedNamespace(atts.getURI(i));
        if(string_adaptor::empty(remap.first) && !string_adaptor::empty(remap.second))
           remap.first = baseT::context().autoNamespacePrefix();
        string_type name = makeName(remap.first, atts.getLocalName(i));
        inlineAtts.push_back(InlineAttribute<string_type, string_adaptor>(name, 
                                             remap.second,
                                             baseT::context().xpath_attribute_value_template(atts.getValue(i))));
      } // if ... 
    } // for ...

    if(!baseT::context().isRemapped(namespaceURI))
      return new InlineElement<string_type, string_adaptor>(qName, namespaceURI, inlineAtts);

    const std::pair<string_type, string_type>& remap = baseT::context().remappedNamespace(namespaceURI);
    string_type name = makeName(remap.first, localName);
    return new InlineElement<string_type, string_adaptor>(name, remap.second, inlineAtts);
  } // createContainer

private:
  string_type makeName(const string_type prefix, const string_type localName) const
  {
    string_type n = prefix;
    string_adaptor::append(n, SC::COLON);
    string_adaptor::append(n, localName);
    return n;
  } // makeName
}; // class InlineElementHandler


template<class string_type, class string_adaptor>
class LREStylesheetHandler : public InlineElementHandler<string_type, string_adaptor>
{
  typedef InlineElementHandler<string_type, string_adaptor> baseT;
public:
  LREStylesheetHandler(CompilationContext<string_type, string_adaptor>& context, 
                       Template<string_type, string_adaptor>* lreStylesheet) :
    baseT(context),
    lreStylesheet_(lreStylesheet)                                                         
  {
  } // LREStylesheetHandler

  virtual void endElement(const string_type& namespaceURI,
                          const string_type& localName,
                          const string_type& qName)
  {
    baseT::context().stylesheet().add_template(lreStylesheet_);
    baseT::endElement(namespaceURI, localName, qName);
  } // endElement

private:
  Template<string_type, string_adaptor>* lreStylesheet_;
}; // class LREStylesheetHandler


} // namespace XSLT
} // namespace Arabica

#endif 

