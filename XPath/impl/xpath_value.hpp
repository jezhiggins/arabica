#ifndef ARABICA_XPATHIC_XPATH_VALUE_H
#define ARABICA_XPATHIC_XPATH_VALUE_H

#include <string>
#include <DOM/Node.h>
#include <boost/lexical_cast.hpp>
#include <vector>
#include "xpath_object.hpp"
#include "xpath_expression.hpp"

namespace Arabica
{
namespace XPath
{

class BoolValue : public XPathValue<std::string>, public XPathExpression
{
public:
  BoolValue(bool value) :
      value_(value) { }

  static XPathValuePtr<std::string> createValue(bool value) { return XPathValuePtr<std::string>(new BoolValue(value)); }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext) const
  {
    return XPathValuePtr<std::string>(new BoolValue(value_));
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<std::string>& context) { return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<std::string>& context) { return asNumber(); }
  virtual std::string evaluateAsString(const DOM::Node<std::string>& context) { return asString(); }
  virtual NodeSet<std::string> evaluateAsNodeSet(const DOM::Node<std::string>& context) { return asNodeSet(); }

  virtual bool asBool() const { return value_; }
  virtual double asNumber() const { return value_ ? 1 : 0; }
  virtual std::string asString() const { return value_ ? "true" : "false"; }
  virtual const NodeSet<std::string>& asNodeSet() const { static NodeSet<std::string> empty; return empty; }

  virtual ValueType type() const { return BOOL; }

private:
  bool value_;
}; // class BoolValue

class NumericValue : public XPathValue<std::string>, public XPathExpression
{
public:
  NumericValue(double value) :
      value_(value) { }
  
  static XPathValuePtr<std::string> createValue(double value) { return XPathValuePtr<std::string>(new NumericValue(value)); }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext) const
  {
    return createValue(value_);
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<std::string>& context) { return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<std::string>& context) { return asNumber(); }
  virtual std::string evaluateAsString(const DOM::Node<std::string>& context) { return asString(); }
  virtual NodeSet<std::string> evaluateAsNodeSet(const DOM::Node<std::string>& context) { return asNodeSet(); }

  virtual bool asBool() const { return (value_ != 0.0); }
  virtual double asNumber() const { return value_; }
  virtual std::string asString() const
  {
    if(isNaN(value_)) 
      return "NaN";
    if(isInfinity(value_))
      return "Infinity";
    if(isNegativeInfinity(value_))
      return "-Infinity";
    return boost::lexical_cast<std::string>(value_);
  } // asString
  virtual const NodeSet<std::string>& asNodeSet() const { static NodeSet<std::string> empty; return empty; }

  virtual ValueType type() const { return NUMBER; }

private:
  double value_;
}; // class NumberValue

class StringValue : public XPathValue<std::string>, public XPathExpression
{
public:
  StringValue(const char* value) :
      value_(value) { }
  StringValue(const std::string& value) :
      value_(value) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext) const
  {
    return XPathValuePtr<std::string>(new StringValue(value_));
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<std::string>& context) { return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<std::string>& context) { return asNumber(); }
  virtual std::string evaluateAsString(const DOM::Node<std::string>& context) { return asString(); }
  virtual NodeSet<std::string> evaluateAsNodeSet() const { return asNodeSet(); }

  virtual bool asBool() const { return !value_.empty(); }
  virtual double asNumber() const 
  { 
    return stringAsNumber(value_);
  } // asNumber
  virtual std::string asString() const { return value_; }
  virtual const NodeSet<std::string>& asNodeSet() const { static NodeSet<std::string> empty; return empty; }
 
  virtual ValueType type() const { return STRING; }

private:
  std::string value_;
}; // class StringValue

class NodeSetValue : public XPathValue<std::string>, public XPathExpression
{
public:
  NodeSetValue(const NodeSet<std::string>& set) : set_(set) { }

  virtual XPathValuePtr<std::string> evaluate(const DOM::Node<std::string>& context, const ExecutionContext& executionContext)  const
  {
    return XPathValuePtr<std::string>(this);
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<std::string>& context) const{ return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<std::string>& context) const { return asNumber(); }
  virtual std::string evaluateAsString(const DOM::Node<std::string>& context) const { return asString(); }
  virtual const NodeSet<std::string>& evaluateAsNodeSet() const { return asNodeSet(); }

  virtual bool asBool() const 
  { 
    return !set_.empty();
  } // asBool
  virtual double asNumber() const 
  { 
    return stringAsNumber(asString());
  } // asNumber
  virtual std::string asString() const 
  { 
    return !set_.empty() ? nodeStringValue(set_.top()) : "";
  } // asStringx
  virtual const NodeSet<std::string>& asNodeSet() const { return set_; }

  virtual ValueType type() const { return NODE_SET; }

private:
  NodeSet<std::string> set_;
}; // NodeSetValue

} // namespace XPath
} // namespace Arabica

#endif
