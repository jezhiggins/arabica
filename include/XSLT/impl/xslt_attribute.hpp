#ifndef ARABICA_XSLT_ATTRIBUTE_HPP
#define ARABICA_XSLT_ATTRIBUTE_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

class Attribute : public ItemContainer
{
public:
  Attribute(const Arabica::XPath::XPathExpressionPtr<std::string>& name,
            const Arabica::XPath::XPathExpressionPtr<std::string>& name_space) :
    name_(name),
    namespace_(name_space)
  {
  } // Attribute

  Attribute(const Arabica::XPath::XPathExpressionPtr<std::string>& name,
            const std::map<std::string, std::string>& namespaces) :
    name_(name),
    namespaces_(namespaces)
  {
  } // Attribute

  virtual ~Attribute() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    std::string name = name_->evaluateAsString(node, context.xpathContext());
    if(name.empty())
      throw SAX::SAXException("xsl:attribute name attribute must evaluate to a valid element name");

    std::string namesp;

    if(namespace_ != 0)
      namesp = namespace_->evaluateAsString(node, context.xpathContext());
    else
    { 
      QName qn = QName::create(name);
      if(!qn.prefix.empty())
      {
        std::map<std::string, std::string>::const_iterator ns = namespaces_.find(qn.prefix);
        if(ns == namespaces_.end())
          throw SAX::SAXException("xsl:attribute Runtime Error - Undeclared prefix " + qn.prefix);
        namesp = ns->second;
      } // if(!qn.prefix.empty())
    } // if ...

    context.sink().start_attribute(name, namesp);
    ChainStackFrame frame(context);
    execute_children(node, context);
    context.sink().end_attribute();
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<std::string> name_;
  Arabica::XPath::XPathExpressionPtr<std::string> namespace_;
  std::map<std::string, std::string> namespaces_;
}; // class Attribute

} // namespace XSLT
} // namespace Arabica

#endif

