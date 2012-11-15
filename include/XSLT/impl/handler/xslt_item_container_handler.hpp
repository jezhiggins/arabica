#ifndef ARABICA_XSLT_ITEM_CONTAINER_HPP
#define ARABICA_XSLT_ITEM_CONTAINER_HPP

#include "xslt_create_handler.hpp"
#include "../xslt_text.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
SAX::DefaultHandler<string_type, string_adaptor>* createInlineElementHandler(CompilationContext<string_type, string_adaptor>& context);

template<class string_type, class string_adaptor>
const ChildElements<string_type, string_adaptor>& AllowedChildren();

template<class container_type>
class ItemContainerHandler : public SAX::DefaultHandler<typename container_type::string_type, typename container_type::string_adaptor>
{
public:
  typedef typename container_type::string_type string_type;
  typedef typename container_type::string_adaptor string_adaptor;

protected:
  ItemContainerHandler(CompilationContext<string_type, string_adaptor>& context) :
         context_(context),
         container_(0)
  {
  } // ItemContainerHandler

  ItemContainerHandler(CompilationContext<string_type, string_adaptor>& context, container_type* container) :
         context_(context),
         container_(container)
  {
  } // ItemContainerHandler

  virtual container_type* createContainer(const string_type& namespaceURI,
                                         const string_type& localName,
                                         const string_type& qName,
                                         const SAX::Attributes<string_type, string_adaptor>& atts) = 0;

  CompilationContext<string_type, string_adaptor>& context() const { return context_; }
  container_type* container() const { return container_; }

public:
  virtual void startElement(const string_type& namespaceURI,
                            const string_type& localName,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(container_ == 0)
    {
      container_ = createContainer(namespaceURI, localName, qName, atts);
      return;
    } // if(item_ == 0)

    if(createChild(namespaceURI, localName, qName, atts))
      return;

    throw SAX::SAXException(string_adaptor::asStdString(qName) + " <- Sorry, don't know about that yet :)");
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    context_.parentContainer().add_item(container_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    for(typename string_type::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
      if(!Arabica::XML::is_space(*i))
      {
        container_->add_item(new Text<string_type, string_adaptor>(ch));
        return;
      } // if ...
  } // characters

protected:
  virtual bool createChild(const string_type& namespaceURI,
                           const string_type& localName,
                           const string_type& qName,
                           const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(namespaceURI == StylesheetConstant<string_type, string_adaptor>::NamespaceURI)
    {
      SAX::DefaultHandler<string_type, string_adaptor>* child = AllowedChildren<string_type, string_adaptor>().create(localName, context_);

      if(child != 0)
      {
        context_.push(container_, child, namespaceURI, localName, qName, atts);
        return true;
      }
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
  CompilationContext<string_type, string_adaptor>& context_;
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
const ChildElements<string_type, string_adaptor>& AllowedChildren()
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
   
  static const ChildElements<string_type, string_adaptor> allowedChildren = 
      ChildElements<string_type, string_adaptor>::add(SC::apply_imports, CreateHandler<ApplyImportsHandler<string_type, string_adaptor> >)
                                                 .add(SC::apply_templates, CreateHandler<ApplyTemplatesHandler<string_type, string_adaptor> >)
                                                 .add(SC::attribute, CreateHandler<AttributeHandler<string_type, string_adaptor> >)
                                                 .add(SC::call_template, CreateHandler<CallTemplateHandler<string_type, string_adaptor> >)
                                                 .add(SC::choose, CreateHandler<ChooseHandler<string_type, string_adaptor> >)
                                                 .add(SC::comment, CreateHandler<CommentHandler<string_type, string_adaptor> >)
                                                 .add(SC::copy, CreateHandler<CopyHandler<string_type, string_adaptor> >)
                                                 .add(SC::copy_of, CreateHandler<CopyOfHandler<string_type, string_adaptor> >)
                                                 .add(SC::element, CreateHandler<ElementHandler<string_type, string_adaptor> >)
                                                 .add(SC::fallback, CreateHandler<NotImplementedYetHandler<string_type, string_adaptor> >)
                                                 .add(SC::for_each, CreateHandler<ForEachHandler<string_type, string_adaptor> >)
                                                 .add(SC::if_, CreateHandler<IfHandler<string_type, string_adaptor> >)
                                                 .add(SC::message, CreateHandler<MessageHandler<string_type, string_adaptor> >)
                                                 .add(SC::number, CreateHandler<NotImplementedYetHandler<string_type, string_adaptor> >)
                                                 .add(SC::processing_instruction, CreateHandler<ProcessingInstructionHandler<string_type, string_adaptor> >)
                                                 .add(SC::text, CreateHandler<TextHandler<string_type, string_adaptor> >)
                                                 .add(SC::value_of, CreateHandler<ValueOfHandler<string_type, string_adaptor> >)
                                                 .add(SC::variable, CreateHandler<VariableHandler<Variable<string_type, string_adaptor> > >);
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

