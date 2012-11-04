#ifndef ARABICA_XSLT_ITEM_CONTAINER_HPP
#define ARABICA_XSLT_ITEM_CONTAINER_HPP

#include "xslt_create_handler.hpp"
#include "../xslt_text.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
const ChildElement<string_type, string_adaptor>* AllowedChildren();

template<class string_type, class string_adaptor>
SAX::DefaultHandler<string_type, string_adaptor>* createInlineElementHandler(CompilationContext<string_type, string_adaptor>& context);

template<class container_type>
class ItemContainerHandler : public SAX::DefaultHandler<typename container_type::string_type, typename container_type::string_adaptor>
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
      for(const ChildElement<std::string, Arabica::default_string_adaptor<std::string> >* c = AllowedChildren<std::string, Arabica::default_string_adaptor<std::string> >(); c->name != 0; ++c)
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

template<class string_type, class string_adaptor>
const ChildElement<string_type, string_adaptor>* AllowedChildren()
{
  static const ChildElement<string_type, string_adaptor> allowedChildren[] = 
  {
    { "apply-imports", CreateHandler<ApplyImportsHandler<string_type, string_adaptor> > },
    { "apply-templates", CreateHandler<ApplyTemplatesHandler<string_type, string_adaptor> > },
    { "attribute", CreateHandler<AttributeHandler<string_type, string_adaptor> > },
    { "call-template", CreateHandler<CallTemplateHandler<string_type, string_adaptor> > },
    { "choose", CreateHandler<ChooseHandler<string_type, string_adaptor> > },
    { "comment", CreateHandler<CommentHandler<string_type, string_adaptor> > },
    { "copy", CreateHandler<CopyHandler<string_type, string_adaptor> > },
    { "copy-of", CreateHandler<CopyOfHandler<string_type, string_adaptor> > },
    { "element", CreateHandler<ElementHandler<string_type, string_adaptor> > },
    { "fallback", CreateHandler<NotImplementedYetHandler<string_type, string_adaptor> >},
    { "for-each", CreateHandler<ForEachHandler<string_type, string_adaptor> > },
    { "if", CreateHandler<IfHandler<string_type, string_adaptor> > },
    { "message", CreateHandler<MessageHandler<string_type, string_adaptor> >},
    { "number", CreateHandler<NotImplementedYetHandler<string_type, string_adaptor> >},
    { "processing-instruction", CreateHandler<ProcessingInstructionHandler<string_type, string_adaptor> > },
    { "text", CreateHandler<TextHandler<string_type, string_adaptor> > },
    { "value-of", CreateHandler<ValueOfHandler<string_type, string_adaptor> > },
    { "variable", CreateHandler<VariableHandler<Variable<string_type, string_adaptor> > > },
    { 0, 0 }
  };
  return allowedChildren;
} // AllowedChildren

template<class string_type, class string_adaptor>
SAX::DefaultHandler<string_type, string_adaptor>* createInlineElementHandler(CompilationContext<string_type, string_adaptor>& context)
{
  return new InlineElementHandler<string_type, string_adaptor>(context);
} // InlineElementHandler


} // namespace XSLT
} // namespace Arabica

#endif

