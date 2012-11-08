#ifndef ARABICA_XSLT_INLINE_ELEMENT_HPP
#define ARABICA_XSLT_INLINE_ELEMENT_HPP

#include "xslt_item.hpp"
#include <SAX/helpers/AttributesImpl.hpp>

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class InlineAttribute
{
public:
  InlineAttribute(const string_type& name,
                  const string_type& name_space,
                  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> value) :
    name_(name),
    namespace_(name_space),
    value_(value)
  {
  } // InlineAttribute

  InlineAttribute(const InlineAttribute& rhs) :
    name_(rhs.name_),
    namespace_(rhs.namespace_),
    value_(rhs.value_)
  {
  } // InlineAttribute

  InlineAttribute& operator==(const InlineAttribute& rhs)
  {
    name_ = rhs.name_;
    namespace_ = rhs.namespace_;
    value_ = rhs.value_;
    return *this;
  } // operator==

  void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    context.sink().start_attribute(name_, namespace_);
    context.sink().characters(value_->evaluateAsString(node, context.xpathContext()));
    context.sink().end_attribute();
  } // execute

private:
  string_type name_;
  string_type namespace_;
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> value_;
}; // class InlineAttribute

template<class stringT, class adaptorT>
class InlineElement : public ItemContainer<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  InlineElement(const string_type& name,
                const string_type& name_space,
                const std::vector<InlineAttribute<string_type, string_adaptor> >& attrs) :
    name_(name),
    namespace_(name_space),
    attrs_(attrs)
  {
  } // InlineElement

  virtual ~InlineElement() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    if(context.sink().start_element(name_, namespace_))
    {
      for(typename std::vector<InlineAttribute<string_type, string_adaptor> >::const_iterator a = attrs_.begin(), ae = attrs_.end(); a != ae; ++a)
        a->execute(node, context);

      ChainStackFrame<string_type, string_adaptor> frame(context);
      execute_children(node, context);
      context.sink().end_element(name_, namespace_);
    }
  } // execute

private:
  string_type name_;
  string_type namespace_;
  std::vector<InlineAttribute<string_type, string_adaptor> > attrs_;
}; // class InlineElement

} // namespace XSLT
} // namespace Arabica

#endif

