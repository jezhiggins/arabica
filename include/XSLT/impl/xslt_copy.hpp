#ifndef ARABICA_XSLT_COPY_HPP
#define ARABICA_XSLT_COPY_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class Copy_base : public ItemContainer<string_type, string_adaptor>
{
protected:
  Copy_base()
  {
    Arabica::XPath::XPath<string_type, string_adaptor> compiler;
    namespace_select_ = compiler.compile("namespace::node()");
  } // Copy_base

  virtual ~Copy_base() { }

protected:
  void copy(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    switch(node.getNodeType())
    {
    case DOM::Node_base::ATTRIBUTE_NODE:
      context.sink().add_attribute(node.getNamespaceURI(),
                                   node.getLocalName(),
                                   node.getNodeName(),
                                   node.getNodeValue());
      break;
    case DOM::Node_base::COMMENT_NODE:
      context.sink().start_comment();
      context.sink().characters(node.getNodeValue());
      context.sink().end_comment();
      break;
    case DOM::Node_base::DOCUMENT_NODE:
    case DOM::Node_base::DOCUMENT_FRAGMENT_NODE:
      process_content(node, context);
      break;
    case DOM::Node_base::ELEMENT_NODE:
      if(context.sink().start_element(node.getPrefix(), node.getLocalName(), node.getNamespaceURI()))
      {
        process_content(node, context);
        context.sink().end_element(node.getPrefix(), node.getLocalName(), node.getNamespaceURI());
      }
      break;
    case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
      context.sink().start_processing_instruction(node.getNodeName());
      context.sink().characters(node.getNodeValue());
      context.sink().end_processing_instruction();
      break;
    case DOM::Node_base::TEXT_NODE:
    case DOM::Node_base::CDATA_SECTION_NODE:
      context.sink().characters(node.getNodeValue());
      break;
    } // switch
  } // execute

  virtual void process_content(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const = 0;

private:
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> namespace_select_;
}; // class Copy_base

template<class stringT, class adaptorT>
class Copy : public Copy_base<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor; 

  Copy(const string_type& attributes_sets) :
      attributes_sets_(attributes_sets)
  {
  } // Copy

  virtual ~Copy() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    copy(node, context);
  } // execute

protected:
  virtual void process_content(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    execute_children(node, context);
  } // process_content

private:
  string_type attributes_sets_;
}; // class Copy

template<class stringT, class adaptorT>
class CopyOf : public Copy_base<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor; 

  CopyOf(const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& select) :
      select_(select)
  {
  } // CopyOf

  virtual ~CopyOf() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    Arabica::XPath::XPathValue<string_type, string_adaptor> value = select_->evaluate(node, context.xpathContext());
    if(value.type() != Arabica::XPath::NODE_SET)
    {
      context.sink().characters(value.asString());
      return;
    } 

    Arabica::XPath::NodeSet<string_type, string_adaptor> nodes = value.asNodeSet();
    for(typename Arabica::XPath::NodeSet<string_type, string_adaptor>::const_iterator n = nodes.begin(), e = nodes.end(); n != e; ++n)
      copy(*n, context);
  } // execute

protected:
  virtual void process_content(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    if(node.hasAttributes())
    {
      const DOM::NamedNodeMap<string_type, string_adaptor>& attrs = node.getAttributes();
      for(unsigned int a = 0; a < attrs.getLength(); ++a)
        copy(attrs.item(a), context);
    } // if ...

    for(DOM::Node<string_type, string_adaptor> n = node.getFirstChild(); n != 0; n = n.getNextSibling())
      copy(n, context);
  } // process_content

private:
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> select_;
}; // class CopyOf

} // namespace XSLT
} // namespace Arabica

#endif

