#ifndef ARABICA_XPATH_FUNCTION_HPP
#define ARABICA_XPATH_FUNCTION_HPP

#include <boost/shared_ptr.hpp>
#include <cmath>
#include <XML/XMLCharacterClasses.hpp>
#include <text/UnicodeCharacters.hpp>
#include <text/normalize_whitespace.hpp>
#include "xpath_value.hpp"
#include "xpath_execution_context.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class XPathFunction
{
protected:
  XPathFunction(int minArgs, int maxArgs, const std::vector<XPathExpression<string_type, string_adaptor> >& args) :
      args_(args)
  {
    if(((minArgs != -1) && (static_cast<int>(args.size()) < minArgs)) ||
       ((maxArgs != -1) && (static_cast<int>(args.size()) > maxArgs)))
       throw SyntaxException("wrong number of arguments to function");
  } // XPathFunction

public:
  virtual ~XPathFunction() { }

  virtual ValueType type() const = 0;

  virtual XPathValue_impl<string_type, string_adaptor>* evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;

protected:
  size_t argCount() const { return args_.size(); }

  XPathValue<string_type, string_adaptor> arg(size_t index,
                 const DOM::Node<string_type, string_adaptor>& context,
                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index].evaluate(context, executionContext);
  } // arg
    
  bool argAsBool(size_t index,
                 const DOM::Node<string_type, string_adaptor>& context,
                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index].evaluateAsBool(context, executionContext);
  } // argAsBool

  double argAsNumber(size_t index,
                     const DOM::Node<string_type, string_adaptor>& context,
                     const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index].evaluateAsNumber(context, executionContext);
  } // argAsNumber

  string_type argAsString(size_t index, 
                          const DOM::Node<string_type, string_adaptor>& context,
                          const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index].evaluateAsString(context, executionContext);
  } // argAsString

  NodeSet<string_type, string_adaptor> argAsNodeSet(size_t index,
                                    const DOM::Node<string_type, string_adaptor>& context,
                                    const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index].evaluateAsNodeSet(context, executionContext);
  } // argAsNodeSet

private:
  const std::vector<XPathExpression<string_type, string_adaptor> > args_;
}; // class XPathFunction

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class BooleanXPathFunction : public XPathFunction<string_type, string_adaptor>
{
public:
  BooleanXPathFunction(int minArgs, int maxArgs, const std::vector<XPathExpression<string_type, string_adaptor> >& args) :
    XPathFunction<string_type, string_adaptor>(minArgs, maxArgs, args) { }

  virtual ValueType type() const { return BOOL; }

  virtual XPathValue_impl<string_type, string_adaptor>* evaluate(const DOM::Node<string_type, string_adaptor>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new BoolValue<string_type, string_adaptor>(doEvaluate(context, executionContext));
  } // evaluate

protected:
  virtual bool doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                          const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;
}; // class BooleanXPathFunction

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NumericXPathFunction : public XPathFunction<string_type, string_adaptor>
{
public:
  NumericXPathFunction(int minArgs, int maxArgs, const std::vector<XPathExpression<string_type, string_adaptor> >& args) :
      XPathFunction<string_type, string_adaptor>(minArgs, maxArgs, args) { }

  virtual ValueType type() const { return NUMBER; }

  virtual XPathValue_impl<string_type, string_adaptor>* evaluate(const DOM::Node<string_type, string_adaptor>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new NumericValue<string_type, string_adaptor>(doEvaluate(context, executionContext));
  } // evaluate

protected:
  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                            const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;
}; // class NumericXPathFunction

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class StringXPathFunction : public XPathFunction<string_type, string_adaptor>
{
public:
  StringXPathFunction(int minArgs, int maxArgs, const std::vector<XPathExpression<string_type, string_adaptor> >& args) :
      XPathFunction<string_type, string_adaptor>(minArgs, maxArgs, args) { }

  virtual ValueType type() const { return STRING; }

  virtual XPathValue_impl<string_type, string_adaptor>* evaluate(const DOM::Node<string_type, string_adaptor>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new StringValue<string_type, string_adaptor>(doEvaluate(context, executionContext));
  } // evaluate

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;
}; // class StringXPathFunction

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class NodeSetXPathFunction : public XPathFunction<string_type, string_adaptor>
{
public:
  NodeSetXPathFunction(int minArgs, int maxArgs, const std::vector<XPathExpression<string_type, string_adaptor> >& args) :
      XPathFunction<string_type, string_adaptor>(minArgs, maxArgs, args) { }

  virtual ValueType type() const { return NODE_SET; }

  virtual XPathValue_impl<string_type, string_adaptor>* evaluate(const DOM::Node<string_type, string_adaptor>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new NodeSetValue<string_type, string_adaptor>(doEvaluate(context, executionContext));
  } // evaluate

protected:
  virtual NodeSet<string_type, string_adaptor> doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                                          const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;
}; // class NodeSetXPathFunction

namespace impl 
{

////////////////////////////////
// node-set functions
// number last()
template<class string_type, class string_adaptor>
class LastFn : public NumericXPathFunction<string_type, string_adaptor>
{
public:
  LastFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(0, 0, args) { }

protected:
  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& /* context */,
                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return executionContext.last();
  } // evaluate
}; // class LastFn

// number position()
template<class string_type, class string_adaptor>
class PositionFn : public NumericXPathFunction<string_type, string_adaptor>
{
public:
  PositionFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(0, 0, args) { }

protected:
  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& /* context */,
                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return executionContext.position();
  } // evaluate
}; // class PositionFn

// number count(node-set)
template<class string_type, class string_adaptor>
class CountFn : public NumericXPathFunction<string_type, string_adaptor>
{
  typedef NumericXPathFunction<string_type, string_adaptor> baseT;
public:
  CountFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(1, 1, args) { }

  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return baseT::argAsNodeSet(0, context, executionContext).size();
  } // evaluate
}; // class CountFn

// node-set id(object)
// string local-name(node-set?)
template<class string_type, class string_adaptor>
class LocalNameFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  LocalNameFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(0, 1, args) { }

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    DOM::Node<string_type, string_adaptor> node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      NodeSet<string_type, string_adaptor> ns = baseT::argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
        case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
        case NAMESPACE_NODE_TYPE:
          return node.hasNamespaceURI() ? node.getLocalName() : node.getNodeName();
        default: // put this in to keep gcc quiet
          ; 
      } // switch ...
    return string_adaptor::empty_string();
  } // evaluate
}; // class LocalNameFn

// string namespace-uri(node-set?)
template<class string_type, class string_adaptor>
class NamespaceURIFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  NamespaceURIFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(0, 1, args) { }

protected:
   virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                  const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    DOM::Node<string_type, string_adaptor> node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      NodeSet<string_type, string_adaptor> ns = baseT::argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
          return node.getNamespaceURI();
        default: // put this in to keep gcc quiet
          ; 
      } // switch ...
    return string_adaptor::empty_string();
  } // evaluate
}; // class NamespaceURIFn

// string name(node-set?) 
template<class string_type, class string_adaptor>
class NameFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  NameFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(0, 1, args) { }


protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    DOM::Node<string_type, string_adaptor> node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      NodeSet<string_type, string_adaptor> ns = baseT::argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
        case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
        case NAMESPACE_NODE_TYPE:
          return node.getNodeName();
        default: // stop gcc generating a warning about unhandled enum values
          ;
      } // switch ...
    return string_adaptor::empty_string();
  } // evaluate
}; // class NameFn

///////////////////////////////////////////////
// string functions

// string string(object?)
template<class string_type, class string_adaptor>
class StringFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  StringFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(0, 1, args) { }

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return (baseT::argCount() > 0) ? baseT::argAsString(0, context, executionContext) : 
                                     nodeStringValue<string_type, string_adaptor>(context);
  } // doEvaluate
}; // class StringFn

// string concat(string, string, string*)
template<class string_type, class string_adaptor>
class ConcatFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  ConcatFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(2, -1, args) { }

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type s;
    for(size_t a = 0, ae = baseT::argCount(); a < ae; ++a)
      string_adaptor::append(s, baseT::argAsString(a, context, executionContext));
    return s;
  } // evaluate
}; // ConcatFn

// boolean starts-with(string, string)
template<class string_type, class string_adaptor>
class StartsWithFn : public BooleanXPathFunction<string_type, string_adaptor>
{
  typedef BooleanXPathFunction<string_type, string_adaptor> baseT;
public:
  StartsWithFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : BooleanXPathFunction<string_type, string_adaptor>(2, 2, args) { }

protected:
  virtual bool doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                          const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = baseT::argAsString(0, context, executionContext);
    string_type start = baseT::argAsString(1, context, executionContext);

    if(string_adaptor::length(value) < string_adaptor::length(start))
      return false;

    typename string_adaptor::const_iterator i = string_adaptor::begin(value);
    typename string_adaptor::const_iterator s = string_adaptor::begin(start);
    typename string_adaptor::const_iterator e = string_adaptor::end(start);
    for(; s != e; ++s, ++i)
      if(*i != *s)
        return false;

    return true;
  } // evaluate
}; // StartsWithFn

// boolean contains(string, string)
template<class string_type, class string_adaptor>
class ContainsFn : public BooleanXPathFunction<string_type, string_adaptor>
{
  typedef BooleanXPathFunction<string_type, string_adaptor> baseT;
public:
  ContainsFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : BooleanXPathFunction<string_type, string_adaptor>(2, 2, args) { }

protected:
  virtual bool doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                          const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return string_adaptor::find(baseT::argAsString(0, context, executionContext),
                                baseT::argAsString(1, context, executionContext)) != string_adaptor::npos();
  } // evaluate
}; // class ContainsFn

// string substring-before(string, string)
template<class string_type, class string_adaptor>
class SubstringBeforeFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  SubstringBeforeFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(2, 2, args) { }

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = baseT::argAsString(0, context, executionContext);
    size_t splitAt = string_adaptor::find(value, baseT::argAsString(1, context, executionContext));

    if(splitAt == string_adaptor::npos())
      return string_adaptor::empty_string();

    return string_adaptor::substr(value, 0, splitAt);
  } // evaluate
}; // class SubstringBeforeFn

// string substring-after(string, string)
template<class string_type, class string_adaptor>
class SubstringAfterFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  SubstringAfterFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(2, 2, args) { }

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = baseT::argAsString(0, context, executionContext);
    string_type split = baseT::argAsString(1, context, executionContext);
    size_t splitAt = string_adaptor::find(value, split);

    if((splitAt == string_adaptor::npos()) || ((splitAt + string_adaptor::length(split)) >= string_adaptor::length(value)))
      return string_adaptor::empty_string();

    return string_adaptor::substr(value, splitAt + string_adaptor::length(split));
  } // evaluate
}; // class SubstringAfterFn

// string substring(string, number, number?)
template<class string_type, class string_adaptor>
class SubstringFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  SubstringFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(2, 3, args) { }

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = baseT::argAsString(0, context, executionContext);
    if(string_adaptor::empty(value))
      return string_adaptor::empty_string();

    double startAt = roundNumber(baseT::argAsNumber(1, context, executionContext)) - 1;
    double endAt = roundNumber((baseT::argCount() == 3 ? baseT::argAsNumber(2, context, executionContext) : Infinity)) + startAt;

    if((endAt < 0) || (endAt < startAt) || (isNaN(endAt)))
      return string_adaptor::empty_string();

    if(startAt < 0)
      startAt = 0;
    if((isInfinite(endAt)) || (endAt > string_adaptor::length(value)))
      endAt = string_adaptor::length(value);

    return string_adaptor::substr(value, static_cast<int>(startAt), static_cast<int>(endAt - startAt));
  } // evaluate
}; // SubstringFn

// number string-length(string?)
template<class string_type, class string_adaptor>
class StringLengthFn : public NumericXPathFunction<string_type, string_adaptor>
{
  typedef NumericXPathFunction<string_type, string_adaptor> baseT;
public:
  StringLengthFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(0, 1, args) { }

  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type v = (baseT::argCount() > 0) ? baseT::argAsString(0, context, executionContext) : nodeStringValue<string_type, string_adaptor>(context);
    return string_adaptor::length(v);
  } // evaluate
}; // StringLengthFn

// string normalize-space(string?)
template<class string_type, class string_adaptor>
class NormalizeSpaceFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  NormalizeSpaceFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(0, 1, args) { }

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type initial = ((baseT::argCount() > 0) ? baseT::argAsString(0, context, executionContext) : nodeStringValue<string_type, string_adaptor>(context));
    string_type value = Arabica::text::normalize_whitespace<string_type, string_adaptor>(initial);
    return value;
  } // evaluate
}; // class NormalizeSpaceFn

// string translate(string, string, string) 
template<class string_type, class string_adaptor>
class TranslateFn : public StringXPathFunction<string_type, string_adaptor>
{
  typedef StringXPathFunction<string_type, string_adaptor> baseT;
public:
  TranslateFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : 
      StringXPathFunction<string_type, string_adaptor>(3, 3, args) { }

protected:
  virtual string_type doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type str = baseT::argAsString(0, context, executionContext);
    string_type from = baseT::argAsString(1, context, executionContext);
    string_type to = baseT::argAsString(2, context, executionContext);

    typename string_adaptor::mutable_iterator p = string_adaptor::begin(str);
    for(typename string_adaptor::mutable_iterator i = string_adaptor::begin(str), ie = string_adaptor::end(str); i != ie; ++i)
    {
      size_t r = string_adaptor::find(from, *i);
      if(r == string_adaptor::npos())
        ++p;
      else if(r < string_adaptor::length(to))
        *p++ = *(string_adaptor::begin(to) + r);
    } // for ...
    if(p != string_adaptor::end(str))
      *p = 0;

		return string_adaptor::construct(string_adaptor::begin(str), p);
  } // evaluate
}; // class TranslateFn

///////////////////////////////////////////////////////
// boolean functions

// boolean boolean(object)
template<class string_type, class string_adaptor>
class BooleanFn : public BooleanXPathFunction<string_type, string_adaptor>
{
  typedef BooleanXPathFunction<string_type, string_adaptor> baseT;
public:
  BooleanFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : BooleanXPathFunction<string_type, string_adaptor>(1, 1, args) { }

protected:
  virtual bool doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                          const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return baseT::argAsBool(0, context, executionContext);
  } // doEvaluate
}; // class BooleanFn

// boolean not(boolean)
template<class string_type, class string_adaptor>
class NotFn : public BooleanXPathFunction<string_type, string_adaptor>
{
  typedef BooleanXPathFunction<string_type, string_adaptor> baseT;
public:
  NotFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : BooleanXPathFunction<string_type, string_adaptor>(1, 1, args) { }

protected:
  virtual bool doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                          const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return !baseT::argAsBool(0, context, executionContext);
  } // doEvaluate
}; // class NotFn

// boolean true()
template<class string_type, class string_adaptor>
class TrueFn : public BooleanXPathFunction<string_type, string_adaptor>
{
public:
  TrueFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : BooleanXPathFunction<string_type, string_adaptor>(0, 0, args) { }

protected:
  virtual bool doEvaluate(const DOM::Node<string_type, string_adaptor>& /* context */,
			  const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    return true;
  } // doEvaluate
}; // TrueFn

// boolean false()
template<class string_type, class string_adaptor>
class FalseFn : public BooleanXPathFunction<string_type, string_adaptor>
{
public:
  FalseFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : BooleanXPathFunction<string_type, string_adaptor>(0, 0, args) { }

protected:
  virtual bool doEvaluate(const DOM::Node<string_type, string_adaptor>& /* context */,
                          const ExecutionContext<string_type, string_adaptor>& /* executionContext */) const
  {
    return false;
  } // evaluate
}; // FalseFn

// boolean lang(string) 

/////////////////////////////////////////////////
// number functions

// number number(object?)
template<class string_type, class string_adaptor>
class NumberFn : public NumericXPathFunction<string_type, string_adaptor>
{
  typedef NumericXPathFunction<string_type, string_adaptor> baseT;
public:
  NumberFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(0, 1, args) { }
  
  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    double result = (baseT::argCount() > 0) ? baseT::argAsNumber(0, context, executionContext) :
                                       StringValue<string_type, string_adaptor>(nodeStringValue<string_type, string_adaptor>(context)).asNumber();
    return result;
  } // evaluate
}; // NumberFn

// number sum(node-set)
template<class string_type, class string_adaptor>
class SumFn : public NumericXPathFunction<string_type, string_adaptor>
{
  typedef NumericXPathFunction<string_type, string_adaptor> baseT;
public:
  SumFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(1, 1, args) { }

protected:
  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                     const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    double sum = 0;
    NodeSet<string_type, string_adaptor> ns = baseT::argAsNodeSet(0, context, executionContext);
    for(typename NodeSet<string_type, string_adaptor>::const_iterator n = ns.begin(), end = ns.end(); n != end; ++n)
      sum += nodeNumberValue<string_type, string_adaptor>(*n);
    return sum;
  } // doEvaluate
}; // class SumFn

// number floor(number)
template<class string_type, class string_adaptor>
class FloorFn : public NumericXPathFunction<string_type, string_adaptor>
{
  typedef NumericXPathFunction<string_type, string_adaptor> baseT;
public:
  FloorFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(1, 1, args) { }
  
protected:
  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return std::floor(baseT::argAsNumber(0, context, executionContext));
  } // doEvaluate
}; // class FloorFn

// number ceiling(number)
template<class string_type, class string_adaptor>
class CeilingFn : public NumericXPathFunction<string_type, string_adaptor>
{
  typedef NumericXPathFunction<string_type, string_adaptor> baseT;
public:
  CeilingFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(1, 1, args) { }

protected:
  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                     const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return std::ceil(baseT::argAsNumber(0, context, executionContext));
  } // doEvaluate
}; // class CeilingFn

// number round(number) 
template<class string_type, class string_adaptor>
class RoundFn : public NumericXPathFunction<string_type, string_adaptor>
{
  typedef NumericXPathFunction<string_type, string_adaptor> baseT;
public:
  RoundFn(const std::vector<XPathExpression<string_type, string_adaptor> >& args) : NumericXPathFunction<string_type, string_adaptor>(1, 1, args) { }

protected:
  virtual double doEvaluate(const DOM::Node<string_type, string_adaptor>& context,
                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return roundNumber(baseT::argAsNumber(0, context, executionContext));
  } // doEvaluate
}; // class RoundFn

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
