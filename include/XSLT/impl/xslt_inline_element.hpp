#ifndef ARABICA_XSLT_INLINE_ELEMENT_HPP
#define ARABICA_XSLT_INLINE_ELEMENT_HPP

#include "xslt_item.hpp"
#include <SAX/helpers/AttributesImpl.hpp>

namespace Arabica
{
namespace XSLT
{

class InlineAttribute
{
public:
  InlineAttribute(const std::string& name,
                  const std::string& name_space,
                  Arabica::XPath::XPathExpressionPtr<std::string> value) :
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

  void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    context.sink().start_attribute(name_, namespace_);
    context.sink().characters(value_->evaluateAsString(node, context.xpathContext()));
    context.sink().end_attribute();
  } // execute

private:
  std::string name_;
  std::string namespace_;
  Arabica::XPath::XPathExpressionPtr<std::string> value_;
}; // class InlineAttribute

class InlineElement : public ItemContainer
{
public:
  InlineElement(const std::string& name,
                const std::string& name_space,
                const std::vector<InlineAttribute>& attrs) :
    name_(name),
    namespace_(name_space),
    attrs_(attrs)
  {
  } // InlineElement

  virtual ~InlineElement() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    if(context.sink().start_element(name_, namespace_))
    {
      for(std::vector<InlineAttribute>::const_iterator a = attrs_.begin(), ae = attrs_.end(); a != ae; ++a)
        a->execute(node, context);

      ChainStackFrame frame(context);
      execute_children(node, context);
      context.sink().end_element(name_, namespace_);
    }
  } // execute

private:
  std::string name_;
  std::string namespace_;
  std::vector<InlineAttribute> attrs_;
}; // class InlineElement

} // namespace XSLT
} // namespace Arabica

#endif

