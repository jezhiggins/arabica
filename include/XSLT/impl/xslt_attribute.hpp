#ifndef ARABICA_XSLT_ATTRIBUTE_HPP
#define ARABICA_XSLT_ATTRIBUTE_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class Attribute : public ItemContainer<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor; 

  Attribute(const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& name,
            const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& name_space) :
    name_(name),
    namespace_(name_space)
  {
  } // Attribute

  Attribute(const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& name,
            const std::map<string_type, string_type>& namespaces) :
    name_(name),
    namespaces_(namespaces)
  {
  } // Attribute

  virtual ~Attribute() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext<string_type, string_adaptor>& context) const
  {
    string_type name = name_->evaluateAsString(node, context.xpathContext());
    if(string_adaptor::empty(name))
      throw SAX::SAXException("xsl:attribute name attribute must evaluate to a valid element name");

    string_type namesp;

    if(namespace_ != 0)
      namesp = namespace_->evaluateAsString(node, context.xpathContext());
    else
    { 
      QName<string_type, string_adaptor> qn = QName<string_type, string_adaptor>::create(name);
      if(!string_adaptor::empty(qn.prefix))
      {
        typename std::map<string_type, string_type>::const_iterator ns = namespaces_.find(qn.prefix);
        if(ns == namespaces_.end())
          throw SAX::SAXException("xsl:attribute Runtime Error - Undeclared prefix " + string_adaptor::asStdString(qn.prefix));
        namesp = ns->second;
      } // if(!qn.prefix.empty())
    } // if ...

    context.sink().start_attribute(name, namesp);
    ChainStackFrame<string_type, string_adaptor> frame(context);
    this->execute_children(node, context);
    context.sink().end_attribute();
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> name_;
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> namespace_;

  std::map<string_type, string_type> namespaces_;
}; // class Attribute

} // namespace XSLT
} // namespace Arabica

#endif

