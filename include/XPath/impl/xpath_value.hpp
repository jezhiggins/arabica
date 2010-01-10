#ifndef ARABICA_XPATHIC_XPATH_VALUE_H
#define ARABICA_XPATHIC_XPATH_VALUE_H

#include <string>
#include <DOM/Node.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <Arabica/StringAdaptor.hpp>
#include "xpath_object.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class Value_base : 
    public XPathExpression_impl<string_type, string_adaptor>,
    public XPathValue_impl<string_type, string_adaptor>
{
  typedef XPathValue_impl<string_type, string_adaptor> XPathValue_implT;
  using XPathValue_implT::asBool;
  using XPathValue_implT::asNumber;
  using XPathValue_implT::asString;
  using XPathValue_implT::asNodeSet;

protected:
  Value_base() { }
  ~Value_base() { }

public:
  virtual bool evaluateAsBool(const DOM::Node<string_type, string_adaptor>& /* context */) { return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& /* context */) { return asNumber(); }
  virtual string_type evaluateAsString(const DOM::Node<string_type, string_adaptor>& /* context */) { return asString(); }
  virtual NodeSet<string_type, string_adaptor> evaluateAsNodeSet(const DOM::Node<string_type, string_adaptor>& /* context */) { return asNodeSet(); }

  virtual bool evaluateAsBool(const DOM::Node<string_type, string_adaptor>& /* context */, 
			      const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const 
  { 
    return asBool(); 
  }
  virtual double evaluateAsNumber(const DOM::Node<string_type, string_adaptor>& /* context */, 
                                  const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const 
  { 
    return asNumber(); 
  }
  virtual string_type evaluateAsString(const DOM::Node<string_type, string_adaptor>& /* context */, 
                                       const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const 
  { 
    return asString(); 
  }
  virtual NodeSet<string_type, string_adaptor> evaluateAsNodeSet(const DOM::Node<string_type, string_adaptor>& /* context */, 
								 const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const 
  {
    return asNodeSet(); 
  }
}; // class Value_base

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class BoolValue : public Value_base<string_type, string_adaptor>
{
public:
  BoolValue(bool value) :
      value_(value) { }

  static XPathValue<string_type, string_adaptor> createValue(bool value) { return XPathValue<string_type, string_adaptor>(new BoolValue(value)); }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& /* context */, 
							   const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    return XPathValue<string_type, string_adaptor>(new BoolValue(value_));
  } // evaluate

  virtual bool asBool() const { return value_; }
  virtual double asNumber() const { return value_ ? 1 : 0; }
  virtual string_type asString() const { return string_adaptor::construct_from_utf8(value_ ? "true" : "false"); }
  virtual const NodeSet<string_type, string_adaptor>& asNodeSet() const { static NodeSet<string_type, string_adaptor> empty; return empty; }

  virtual ValueType type() const { return BOOL; }

private:
  bool value_;
}; // class BoolValue

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NumericValue : public Value_base<string_type, string_adaptor>
{
public:
  NumericValue(double value) :
      value_(value) { }
  
  static XPathValue<string_type, string_adaptor> createValue(double value) { return XPathValue<string_type, string_adaptor>(new NumericValue(value)); }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& /* context */, 
							   const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    return createValue(value_);
  } // evaluate

  virtual bool asBool() const 
  { 
    if(isNaN(value_)) 
      return false;
    return (value_ != 0.0); 
  } // asBool
  virtual double asNumber() const { return value_; }
  virtual string_type asString() const
  {
    if(isNaN(value_)) 
      return string_adaptor::construct_from_utf8("NaN");
    if(isInfinity(value_))
      return string_adaptor::construct_from_utf8("Infinity");
    if(isNegativeInfinity(value_))
      return string_adaptor::construct_from_utf8("-Infinity");
    return string_adaptor::construct_from_utf8(boost::lexical_cast<std::string>(value_).c_str());
  } // asString
  virtual const NodeSet<string_type, string_adaptor>& asNodeSet() const { static NodeSet<string_type, string_adaptor> empty; return empty; }

  virtual ValueType type() const { return NUMBER; }

private:
  double value_;
}; // class NumberValue

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class StringValue : public Value_base<string_type, string_adaptor>
{
public:
  StringValue(const char* value) :
      value_(string_adaptor::construct_from_utf8(value)) { }
  StringValue(const string_type& value) :
      value_(value) { }

  static XPathValue<string_type, string_adaptor> createValue(const string_type& value) { return XPathValue<string_type, string_adaptor>(new StringValue(value)); }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& /* context */, 
							   const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    return XPathValue<string_type, string_adaptor>(new StringValue(value_));
  } // evaluate

  virtual bool asBool() const { return !string_adaptor::empty(value_); }
  virtual double asNumber() const 
  { 
    return impl::stringAsNumber<string_type, string_adaptor>(value_);
  } // asNumber
  virtual string_type asString() const { return value_; }
  virtual const NodeSet<string_type, string_adaptor>& asNodeSet() const { static NodeSet<string_type, string_adaptor> empty; return empty; }
 
  virtual ValueType type() const { return STRING; }

private:
  string_type value_;
}; // class StringValue

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NodeSetValue : public Value_base<string_type, string_adaptor>
{
public:
  NodeSetValue(const NodeSet<string_type, string_adaptor>& set) : set_(set) { }

  static XPathValue<string_type, string_adaptor> createValue(const NodeSet<string_type, string_adaptor>& set) 
  { 
    return XPathValue<string_type, string_adaptor>(new NodeSetValue(set)); 
  } // createValue

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& /* context */, 
							   const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    return XPathValue<string_type, string_adaptor>(this);
  } // evaluate

  virtual bool asBool() const 
  { 
    return !set_.empty();
  } // asBool
  virtual double asNumber() const 
  { 
    return impl::stringAsNumber<string_type, string_adaptor>(asString());
  } // asNumber
  virtual string_type asString() const 
  { 
    if(set_.empty())
      return string_adaptor::construct_from_utf8("");  
    return impl::nodeStringValue<string_type, string_adaptor>(set_.top());
  } // asStringx
  virtual const NodeSet<string_type, string_adaptor>& asNodeSet() const 
  { 
    return set_; 
  } // asNodeSet

  virtual ValueType type() const { return NODE_SET; }

private:
  mutable NodeSet<string_type, string_adaptor> set_;
}; // NodeSetValue

} // namespace XPath
} // namespace Arabica

#endif
