#ifndef ARABICA_XSLT_ELEMENT_HPP
#define ARABICA_XSLT_ELEMENT_HPP

#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class Element : public ItemContainer<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor; 

  Element(const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& name,
          const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& name_space,
          const string_type& use_attribute_sets) :
    name_(name),
    namespace_(name_space),
    use_attribute_sets_(use_attribute_sets)
  {
  } // Element

  Element(const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& name,
          const std::map<string_type, string_type>& namespaces,
          const string_type& use_attribute_sets) :
    name_(name),
    namespaces_(namespaces),
    use_attribute_sets_(use_attribute_sets)
  {
  } // Element

  virtual ~Element() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    string_type name = name_->evaluateAsString(node, context.xpathContext());
    if(!Arabica::XML::is_qname<string_adaptor>(name))
      throw SAX::SAXException("xsl:element name attribute must evaluate to a valid element name");

    string_type namesp;

    if(namespace_ != 0)
      namesp = namespace_->evaluateAsString(node, context.xpathContext());
    else
    { 
      QName<string_type, string_adaptor> qn = QName<string_type, string_adaptor>::create(name);
      typename std::map<string_type, string_type>::const_iterator ns = namespaces_.find(qn.prefix);
      if(ns == namespaces_.end())
        throw SAX::SAXException("xsl:element Runtime Error - Undeclared prefix " + qn.prefix);
      namesp = ns->second;
    } // if ...

    if(context.sink().start_element(name, namesp)) 
    {
      ChainStackFrame<string_type, string_adaptor> frame(context);
      execute_children(node, context);
      context.sink().end_element(name, namesp);
    }
  } // execute

private:
  const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> name_;
  const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> namespace_;
  const std::map<string_type, string_type> namespaces_;
  const string_type use_attribute_sets_;
}; // class Element

} // namespace XSLT
} // namespace Arabica

#endif

