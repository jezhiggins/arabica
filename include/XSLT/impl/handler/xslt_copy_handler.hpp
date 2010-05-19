#ifndef ARABICA_XSLT_COPY_HANDLER_HPP
#define ARABICA_XSLT_COPY_HANDLER_HPP

#include "../xslt_copy.hpp"

namespace Arabica
{
namespace XSLT
{

class CopyHandler : public ItemContainerHandler<Copy>
{
public:
  CopyHandler(CompilationContext& context) :
      ItemContainerHandler<Copy>(context)
  {
  } // CopyHandler

  virtual Copy* createContainer(const std::string& /* namespaceURI */,
                                const std::string& /* localName */,
                                const std::string& qName,
                                const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "use-attribute-sets", false, 0, 0 },
                                       { 0, false, 0, 0 } };
    std::string sets = gatherAttributes(qName, atts, rules)["use-attribute-sets"];

    return new Copy(sets);
  } // createContainer
}; // class WhenHandler

class CopyOfHandler : public SAX::DefaultHandler<std::string>
{
public:
  CopyOfHandler(CompilationContext& context) : 
    context_(context),
    copyOf_(0)
  {
  } // CopyOfHandler

  virtual void startElement(const std::string& /* namespaceURI */,
                            const std::string& /* localName */,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(copyOf_ == 0)
    {
      static const ValueRule rules[] = { { "select", true, 0, 0 },
                                         { 0, false, 0, 0 } };
      std::string select = gatherAttributes(qName, atts, rules)["select"];

      copyOf_ = new CopyOf(context_.xpath_expression(select));

      return;
    } // if(copyOf_ == 0)

    throw SAX::SAXException(qName + " can not contain elements");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    context_.parentContainer().add_item(copyOf_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    verifyNoCharacterData(ch, "xsl:copy-of");
  } // characters

private:
  CompilationContext& context_;
  CopyOf* copyOf_;
}; // class CopyOfHandler

} // namespace XSLT
} // namespace Arabica

#endif

