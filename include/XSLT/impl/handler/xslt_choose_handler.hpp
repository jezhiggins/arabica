#ifndef ARABICA_XSLT_CHOOSE_HANDLER_HPP
#define ARABICA_XSLT_CHOOSE_HANDLER_HPP

#include "../xslt_choose.hpp"

namespace Arabica
{
namespace XSLT
{

class WhenHandler : public ItemContainerHandler<When>
{
public:
  WhenHandler(Choose* choose,
              CompilationContext& context) :
      ItemContainerHandler<When>(context),
      choose_(choose)
  {
  } // WhenHandler

  virtual When* createContainer(const std::string& /* namespaceURI */,
				const std::string& /* localName */,
				const std::string& qName,
				const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "test", true, 0, 0 },
                                       { 0, false, 0, 0 } };
    std::string test = gatherAttributes(qName, atts, rules)["test"];

    return new When(ItemContainerHandler<When>::context().xpath_expression(test));
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */, 
			  const std::string& /* localName */, 
			  const std::string& /* qName */)
  {
    choose_->add_when(ItemContainerHandler<When>::container());
    context().pop();
  } // endElement

private:
  Choose* choose_;
}; // class WhenHandler

class OtherwiseHandler : public ItemContainerHandler<Otherwise>
{
public:
  OtherwiseHandler(Choose* choose,
                   CompilationContext& context) :
      ItemContainerHandler<Otherwise>(context),
      choose_(choose)
  {
  } // OtherwiseHandler

  virtual Otherwise* createContainer(const std::string& /* namespaceURI */,
                                     const std::string& /* localName */,
                                     const std::string& /* qName */,
                                     const SAX::Attributes<std::string>& atts)
  {
    if(atts.getLength())
      throw SAX::SAXException("xsl:otherwise may not have any attributes");

    return new Otherwise();
  } // createContainer

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    choose_->set_otherwise(container());
    context().pop();
  } // endElement

private:
  Choose* choose_;
}; // class OtherwiseHandler

class ChooseHandler : public SAX::DefaultHandler<std::string>
{
public:
  ChooseHandler(CompilationContext& context) :
      context_(context),
      choose_(0),
      seenWhere_(false),
      seenOtherwise_(false)
  {
  } // ChooseHandler

  virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(!choose_)
    {
      if(atts.getLength() != 0)
        throw SAX::SAXException("xsl:choose can not have attributes");

      choose_ = new Choose();
      return;
    } // if ...

    if(namespaceURI == StylesheetConstant::NamespaceURI())
    {
      if(localName == "when")
      {
        seenWhere_ = true;
        if(seenOtherwise_)
          throw SAX::SAXException("xsl:otherwise must be the last element in an xsl:choose");

        context_.push(0,
                      new WhenHandler(choose_, context_), 
                      namespaceURI,
                      localName,
                      qName, 
                      atts);
        return;
      } // if(localName == "when")

      if(localName == "otherwise")
      {
        if(seenOtherwise_)
          throw SAX::SAXException("xsl:choose may only have one xsl:otherwise element");
        seenOtherwise_ = true;
        context_.push(0,
                      new OtherwiseHandler(choose_, context_), 
                      namespaceURI,
                      localName,
                      qName, 
                      atts);
        return;
      } // if(localName == "otherwise")
    } // if ...
    throw SAX::SAXException("xsl:choose can not contain " + qName + ".  Only xsl:when and xsl:otherwise are allowed");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    if(!seenWhere_)
      throw SAX::SAXException("xsl:choose must contain at least one xsl:where element");
    context_.parentContainer().add_item(choose_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    verifyNoCharacterData(ch, "xsl:choose");
  } // characters

private:
  CompilationContext& context_;
  Choose* choose_;
  bool seenWhere_;
  bool seenOtherwise_;
}; // class ChooseHandler

} // namespace XSLT
} // namespace Arabica

#endif

