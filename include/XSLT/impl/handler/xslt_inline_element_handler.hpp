#ifndef ARABICA_XSLT_INLINE_ELEMENT_HANDLER_HPP
#define ARABICA_XSLT_INLINE_ELEMENT_HANDLER_HPP

#include "../xslt_inline_element.hpp"
#include "xslt_item_container_handler.hpp"
#include "xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

class InlineElementHandler : public ItemContainerHandler<InlineElement>
{
public:
  InlineElementHandler(CompilationContext& context) :
      ItemContainerHandler<InlineElement>(context)
  {
  } // InlineElementHandler

protected:
  virtual InlineElement* createContainer(const std::string& namespaceURI,
                                         const std::string& localName,
                                         const std::string& qName,
                                         const SAX::Attributes<std::string>& atts)
  {
    std::vector<InlineAttribute> inlineAtts;
    for(int i = 0; i != atts.getLength(); ++i)
    {      
      if(atts.getQName(i).find("xmlns:") == 0)
        continue;
      if(atts.getURI(i) == StylesheetConstant::NamespaceURI())
        continue;
      if(!context().isRemapped(atts.getURI(i)))
        inlineAtts.push_back(InlineAttribute(atts.getQName(i), 
                                             atts.getURI(i),
                                             context().xpath_attribute_value_template(atts.getValue(i))));
      else
      {
        std::pair<std::string, std::string> remap = context().remappedNamespace(atts.getURI(i));
        if(remap.first.empty() && !remap.second.empty())
           remap.first = context().autoNamespacePrefix();
        std::string name = remap.first + ":" + atts.getLocalName(i);
        inlineAtts.push_back(InlineAttribute(name, 
                                             remap.second,
                                             context().xpath_attribute_value_template(atts.getValue(i))));
      } // if ... 
    } // for ...

    if(!context().isRemapped(namespaceURI))
      return new InlineElement(qName, namespaceURI, inlineAtts);

    const std::pair<std::string, std::string>& remap = context().remappedNamespace(namespaceURI);
    std::string name = remap.first + ":" + localName;
    return new InlineElement(name, remap.second, inlineAtts);
  } // createContainer
}; // class InlineElementHandler

class LREStylesheetHandler : public InlineElementHandler
{
public:
  LREStylesheetHandler(CompilationContext& context, Template* lreStylesheet) :
    InlineElementHandler(context),
    lreStylesheet_(lreStylesheet)                                                         
  {
  } // LREStylesheetHandler

  virtual void endElement(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName)
  {
    context().stylesheet().add_template(lreStylesheet_);
    InlineElementHandler::endElement(namespaceURI, localName, qName);
  } // endElement

private:
  Template* lreStylesheet_;
}; // class LREStylesheetHandler


} // namespace XSLT
} // namespace Arabica

#endif 

