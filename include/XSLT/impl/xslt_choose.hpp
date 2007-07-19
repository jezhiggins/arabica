#ifndef ARABICA_XSLT_CHOOSE_HPP
#define ARABICA_XSLT_CHOOSE_HPP

#include <boost/ptr_container/ptr_vector.hpp>
#include "xslt_item.hpp"
#include "xslt_if.hpp"

namespace Arabica
{
namespace XSLT
{

class When : public ItemContainer
{
public:
  When(Arabica::XPath::XPathExpressionPtr<std::string> test) :
    test_(test)
  { 
  } // When

  virtual ~When() { }

  bool is_met(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    return test_->evaluateAsBool(node, context.xpathContext());
  } // is_met

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    execute_children(node, context);
  } // execute

private:
  Arabica::XPath::XPathExpressionPtr<std::string> test_;
}; // class When

class Otherwise : public ItemContainer
{
public:
  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    execute_children(node, context);
  } // execute
}; // class Otherwise

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
    delete otherwise_;
  } // ~Choose

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    for(boost::ptr_vector<When>::const_iterator w = when_.begin(), e = when_.end(); w != e; ++w)
      if(w->is_met(node, context))
      {
        w->execute(node, context);
        return;
      } // if ...

    if(otherwise_)
      otherwise_->execute(node, context);
  } // execute

public:
  void add_when(When* child) 
  {
    when_.push_back(child);
  } // add_when

  void set_otherwise(Otherwise* otherwise)
  {
    otherwise_ = otherwise;
  } // set_otherwise

private:
  boost::ptr_vector<When> when_;
  Otherwise* otherwise_;
}; // class Choose

} // namespace XSLT
} // namespace Arabica

#endif

