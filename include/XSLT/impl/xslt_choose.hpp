#ifndef ARABICA_XSLT_CHOOSE_HPP
#define ARABICA_XSLT_CHOOSE_HPP

#include "xslt_item.hpp"
#include "xslt_if.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class When : public ItemContainer
{
public:
  When(Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> test) :
    test_(test)
  { 
  } // When

  virtual ~When() { }

  bool is_met(const DOM::Node<string_type, string_adaptor>& node, 
              ExecutionContext& context) const
  {
    return test_->evaluateAsBool(node, context.xpathContext());
  } // is_met

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const
  {
    execute_children(node, context);
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> test_;
}; // class When

template<class string_type, class string_adaptor>
class Otherwise : public ItemContainer
{
public:
  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const
  {
    execute_children(node, context);
  } // execute
}; // class Otherwise

template<class string_type, class string_adaptor>
class Choose : public Item
{
public:
  Choose()  :
    when_(),
    otherwise_(0)
  {
  } // Choose

  virtual ~Choose()
  { 
    for(typename WhenList::const_iterator w = when_.begin(), e = when_.end(); w != e; ++w)
      delete (*w);
    delete otherwise_;
  } // ~Choose

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const
  {
    ChainStackFrame frame(context);
    for(typename WhenList::const_iterator w = when_.begin(), e = when_.end(); w != e; ++w)
      if((*w)->is_met(node, context))
      {
        (*w)->execute(node, context);
        return;
      } // if ...

    if(otherwise_)
      otherwise_->execute(node, context);
  } // execute

public:
  void add_when(When<string_type, string_adaptor>* child) 
  {
    when_.push_back(child);
  } // add_when

  void set_otherwise(Otherwise<string_type, string_adaptor>* otherwise)
  {
    otherwise_ = otherwise;
  } // set_otherwise

private:
  typedef std::vector<When<string_type, string_adaptor>*> WhenList;
  WhenList when_;
  Otherwise<string_type, string_adaptor>* otherwise_;
}; // class Choose

} // namespace XSLT
} // namespace Arabica

#endif

