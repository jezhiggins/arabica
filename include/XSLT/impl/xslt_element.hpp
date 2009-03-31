#ifndef ARABICA_XSLT_ELEMENT_HPP
#define ARABICA_XSLT_ELEMENT_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

class Element : public ItemContainer
{
public:
  Element(const Arabica::XPath::XPathExpressionPtr<std::string>& name,
          const Arabica::XPath::XPathExpressionPtr<std::string>& name_space,
          const std::string& use_attribute_sets) :
    name_(name),
    namespace_(name_space),
    use_attribute_sets_(use_attribute_sets)
  {
  } // Element

  Element(const Arabica::XPath::XPathExpressionPtr<std::string>& name,
          const std::map<std::string, std::string>& namespaces,
          const std::string& use_attribute_sets) :
    name_(name),
    namespaces_(namespaces),
    use_attribute_sets_(use_attribute_sets)
  {
  } // Element

  virtual ~Element() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    std::string name = name_->evaluateAsString(node, context.xpathContext());
    if(!Arabica::XML::is_qname<Arabica::default_string_adaptor<std::string> >(name))
      throw SAX::SAXException("xsl:element name attribute must evaluate to a valid element name");

    std::string namesp;

    if(namespace_ != 0)
      namesp = namespace_->evaluateAsString(node, context.xpathContext());
    else
    { 
      QName qn = QName::create(name);
      std::map<std::string, std::string>::const_iterator ns = namespaces_.find(qn.prefix);
      if(ns == namespaces_.end())
        throw SAX::SAXException("xsl:element Runtime Error - Undeclared prefix " + qn.prefix);
      namesp = ns->second;
    } // if ...

    if(context.sink().start_element(name, namesp)) 
    {
      ChainStackFrame frame(context);
      execute_children(node, context);
      context.sink().end_element(name, namesp);
    }
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<std::string> name_;
  Arabica::XPath::XPathExpressionPtr<std::string> namespace_;
  std::map<std::string, std::string> namespaces_;
  std::string use_attribute_sets_;
}; // class Element

} // namespace XSLT
} // namespace Arabica

#endif

