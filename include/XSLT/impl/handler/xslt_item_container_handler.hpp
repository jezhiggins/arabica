#ifndef ARABICA_XSLT_ITEM_CONTAINER_HPP
#define ARABICA_XSLT_ITEM_CONTAINER_HPP

#include "xslt_create_handler.hpp"
#include "../xslt_text.hpp"

namespace Arabica
{
namespace XSLT
{

const ChildElement* AllowedChildren();
SAX::DefaultHandler<std::string>* createInlineElementHandler(CompilationContext<std::string>& context);

template<class container_type>
class ItemContainerHandler : public SAX::DefaultHandler<std::string>
{
protected:
  ItemContainerHandler(CompilationContext<std::string>& context) :
         context_(context),
         container_(0)
  {
  } // ItemContainerHandler

  ItemContainerHandler(CompilationContext<std::string>& context, container_type* container) :
         context_(context),
         container_(container)
  {
  } // ItemContainerHandler

  virtual container_type* createContainer(const std::string& namespaceURI,
                                         const std::string& localName,
                                         const std::string& qName,
                                         const SAX::Attributes<std::string>& atts) = 0;

  CompilationContext<std::string>& context() const { return context_; }
  container_type* container() const { return container_; }

public:
  virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(container_ == 0)
    {
      container_ = createContainer(namespaceURI, localName, qName, atts);
      return;
    } // if(item_ == 0)

    if(createChild(namespaceURI, localName, qName, atts))
      return;

    throw SAX::SAXException(qName + " <- Sorry, don't know about that yet :)");
  } // startElement

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    context_.parentContainer().add_item(container_);
    context_.pop();
  } // endElement

  virtual void characters(const std::string& ch)
  {
    for(std::string::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
      if(!Arabica::XML::is_space(*i))
      {
        container_->add_item(new Text<std::string, Arabica::default_string_adaptor<std::string> >(ch));
        return;
      } // if ...
  } // characters

protected:
  virtual bool createChild(const std::string& namespaceURI,
                           const std::string& localName,
                           const std::string& qName,
                           const SAX::Attributes<std::string>& atts)
  {
    if(namespaceURI == StylesheetConstant::NamespaceURI())
    {
      for(const ChildElement* c = AllowedChildren(); c->name != 0; ++c)
        if(c->name == localName)
        {
          context_.push(container_,
                        c->createHandler(context_),
                        namespaceURI, 
                        localName, 
                        qName, 
                        atts);
          return true;
        } // if ...
      return false;
    } // if(namespaceURI ...

    context_.push(container_,
                  createInlineElementHandler(context_),
                  namespaceURI, 
                  localName, 
                  qName, 
                  atts);
    return true;
  } // createChild

private:
  CompilationContext<std::string>& context_;
  container_type* container_;
}; // class ItemContainerHandler

} // namespace XSLT
} // namespace Arabica

#include "xslt_apply_imports_handler.hpp"
#include "xslt_apply_templates_handler.hpp"
#include "xslt_attribute_handler.hpp"
#include "xslt_call_template_handler.hpp"
#include "xslt_choose_handler.hpp"
#include "xslt_comment_handler.hpp"
#include "xslt_copy_handler.hpp"
#include "xslt_element_handler.hpp"
#include "xslt_for_each_handler.hpp"
#include "xslt_if_handler.hpp"
#include "xslt_message_handler.hpp"
#include "xslt_processing_instruction_handler.hpp"
#include "xslt_text_handler.hpp"
#include "xslt_value_of_handler.hpp"
#include "xslt_variable_handler.hpp"

#include "xslt_inline_element_handler.hpp"

namespace Arabica
{
namespace XSLT
{

const ChildElement* AllowedChildren()
{
  static const ChildElement allowedChildren[] = 
  {
    { "apply-imports", CreateHandler<ApplyImportsHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "apply-templates", CreateHandler<ApplyTemplatesHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "attribute", CreateHandler<AttributeHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "call-template", CreateHandler<CallTemplateHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "choose", CreateHandler<ChooseHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "comment", CreateHandler<CommentHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "copy", CreateHandler<CopyHandler> },
    { "copy-of", CreateHandler<CopyOfHandler> },
    { "element", CreateHandler<ElementHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "fallback", CreateHandler<NotImplementedYetHandler<std::string, Arabica::default_string_adaptor<std::string> > >},
    { "for-each", CreateHandler<ForEachHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "if", CreateHandler<IfHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "message", CreateHandler<MessageHandler>},
    { "number", CreateHandler<NotImplementedYetHandler<std::string, Arabica::default_string_adaptor<std::string> > >},
    { "processing-instruction", CreateHandler<ProcessingInstructionHandler> },
    { "text", CreateHandler<TextHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "value-of", CreateHandler<ValueOfHandler<std::string, Arabica::default_string_adaptor<std::string> > > },
    { "variable", CreateHandler<VariableHandler<Variable> > },
    { 0, 0 }
  };
  return allowedChildren;
} // AllowedChildren

SAX::DefaultHandler<std::string>* createInlineElementHandler(CompilationContext<std::string>& context)
{
  return new InlineElementHandler(context);
} // InlineElementHandler


} // namespace XSLT
} // namespace Arabica

#endif

