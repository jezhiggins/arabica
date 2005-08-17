#ifndef ARABICA_XPATH_FUNCTION_HPP
#define ARABICA_XPATH_FUNCTION_HPP

#include <boost/shared_ptr.hpp>
#include <cmath>
#include <XML/XMLCharacterClasses.h>
#include <XML/UnicodeCharacters.h>
#include "xpath_value.hpp"
#include "xpath_execution_context.hpp"

namespace Arabica
{
namespace XPath
{

class XPathFunction
{
protected:
  XPathFunction(int minArgs, int maxArgs, const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) :
      args_(args)
  {
    if(((minArgs != -1) && (static_cast<int>(args.size()) < minArgs)) ||
       ((maxArgs != -1) && (static_cast<int>(args.size()) > maxArgs)))
       throw SyntaxException("wrong number of arguments to function");
  } // XPathFunction

public:
  virtual ~XPathFunction() { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context, 
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const = 0;

protected:
  size_t argCount() const { return args_.size(); }

  bool argAsBool(size_t index,
                 const DOM::Node<std::string>& context,
                 const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return args_[index]->evaluate(context, executionContext)->asBool();
  } // argAsBool

  double argAsNumber(size_t index,
                     const DOM::Node<std::string>& context,
                     const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return args_[index]->evaluate(context, executionContext)->asNumber();
  } // argAsNumber

  std::string argAsString(size_t index, 
                          const DOM::Node<std::string>& context,
                          const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return args_[index]->evaluate(context, executionContext)->asString();
  } // argAsString

  NodeSet<std::string> argAsNodeSet(size_t index,
                                    const DOM::Node<std::string>& context,
                                    const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return args_[index]->evaluate(context, executionContext)->asNodeSet();
  } // argAsNodeSet

private:
  const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > > args_;
}; // class XPathFunction

////////////////////////////////
// node-set functions
// number last()
class LastFn : public XPathFunction
{
public:
  LastFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 0, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(executionContext.last());
  } // evaluate
}; // class LastFn

// number position()
class PositionFn : public XPathFunction
{
public:
  PositionFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 0, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(executionContext.position());
  } // evaluate
}; // class PositionFn

// number count(node-set)
class CountFn : public XPathFunction
{
public:
  CountFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(argAsNodeSet(0, context, executionContext).size());
  } // evaluate
}; // class CountFn

// node-set id(object)
// string local-name(node-set?)
class LocalNameFn : public XPathFunction
{
public:
  LocalNameFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    DOM::Node<std::string> node;
    if(argCount() == 0)
      node = context;
    else
    {
      NodeSet<std::string> ns = argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
        case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
          return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(node.hasNamespaceURI() ? node.getLocalName() : node.getNodeName());
        default: // put this in to keep gcc quiet
          ; 
      } // switch ...
    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >("");
  } // evaluate
}; // class LocalNameFn

// string namespace-uri(node-set?)
class NamespaceURIFn : public XPathFunction
{
public:
  NamespaceURIFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    DOM::Node<std::string> node;
    if(argCount() == 0)
      node = context;
    else
    {
      NodeSet<std::string> ns = argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
          return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(node.getNamespaceURI());
        default: // put this in to keep gcc quiet
          ; 
      } // switch ...
    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >("");
  } // evaluate
}; // class NamespaceURIFn

// string name(node-set?) 
class NameFn : public XPathFunction
{
public:
  NameFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    DOM::Node<std::string> node;
    if(argCount() == 0)
      node = context;
    else
    {
      NodeSet<std::string> ns = argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
        case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
          return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(node.getNodeName());
        default: // stop gcc generating a warning about unhandled enum values
          ;
      } // switch ...
    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >("");
  } // evaluate
}; // class NameFn

///////////////////////////////////////////////
// string functions

// string string(object?)
class StringFn : public XPathFunction
{
public:
  StringFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >((argCount() > 0) ? argAsString(0, context, executionContext) : nodeStringValue(context));
  } // evaluate
}; // class StringFn

// string concat(string, string, string*)
class ConcatFn : public XPathFunction
{
public:
  ConcatFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(2, -1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    std::string s;
    for(size_t a = 0, ae = argCount(); a < ae; ++a)
      s.append(argAsString(a, context, executionContext));
    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(s);
  } // evaluate
}; // ConcatFn

// boolean starts-with(string, string)
class StartsWithFn : public XPathFunction
{
public:
  StartsWithFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(2, 2, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    std::string value = argAsString(0, context, executionContext);
    std::string start = argAsString(1, context, executionContext);

    if(value.length() < start.length())
      return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false);

    for(size_t i = 0, ie = start.length(); i < ie; ++i)
      if(value[i] != start[i])
        return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false);

    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true);
  } // evaluate
}; // StartsWithFn

// boolean contains(string, string)
class ContainsFn : public XPathFunction
{
public:
  ContainsFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(2, 2, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(argAsString(0, context, executionContext).find(argAsString(1, context, executionContext)) != std::string::npos);
  } // evaluate
}; // class ContainsFn

// string substring-before(string, string)
class SubstringBeforeFn : public XPathFunction
{
public:
  SubstringBeforeFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(2, 2, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    std::string value = argAsString(0, context, executionContext);
    size_t splitAt = value.find(argAsString(1, context, executionContext));

    if(splitAt == std::string::npos)
      return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >("");

    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(value.substr(0, splitAt));
  } // evaluate
}; // class SubstringBeforeFn

// string substring-after(string, string)
class SubstringAfterFn : public XPathFunction
{
public:
  SubstringAfterFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(2, 2, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    std::string value = argAsString(0, context, executionContext);
    std::string split = argAsString(1, context, executionContext);
    size_t splitAt = value.find(split);

    if((splitAt == std::string::npos) || ((splitAt + split.length()) >= value.length()))
      return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >("");

    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(value.substr(splitAt + split.length()));
  } // evaluate
}; // class SubstringAfterFn

// string substring(string, number, number?)
class SubstringFn : public XPathFunction
{
public:
  SubstringFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(2, 3, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    std::string value = argAsString(0, context, executionContext);
    double startAt = roundNumber(argAsNumber(1, context, executionContext)) - 1;
    double endAt = roundNumber((argCount() == 3 ? argAsNumber(2, context, executionContext) : Infinity)) + startAt;

    if((endAt < 0) || (endAt < startAt) || (isNaN(endAt)))
      return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >("");

    if(startAt < 0)
      startAt = 0;
    if((isInfinite(endAt)) || (endAt > value.length()))
      endAt = value.length();

    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(value.substr(static_cast<int>(startAt), static_cast<int>(endAt - startAt)));
  } // evaluate
}; // SubstringFn

// number string-length(string?)
class StringLengthFn : public XPathFunction
{
public:
  StringLengthFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(((argCount() > 0) ? argAsString(0, context, executionContext) : nodeStringValue(context)).length());
  } // evaluate
}; // StringLengthFn

// string normalize-space(string?)
class NormalizeSpaceFn : public XPathFunction
{
public:
  NormalizeSpaceFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    std::string value = ((argCount() > 0) ? argAsString(0, context, executionContext) : nodeStringValue(context));
    size_t i = 0, ie = value.length();

    // string leading space
    while((i != ie) && (XML::is_space(static_cast<wchar_t>(value[i]))))
      ++i;
    
    size_t p = 0;
    while(i != ie)
    {
      while((i != ie) && (!XML::is_space(static_cast<wchar_t>(value[i])))) 
        value[p++] = value[i++];
      while((i != ie) && (XML::is_space(static_cast<wchar_t>(value[i]))))
        ++i;
      if(i != ie)
        value[p++] = Unicode<char>::SPACE;
    } // while ...
    if(p != ie)
      value.resize(p);

    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(value);
  } // evaluate
}; // class NormalizeSpaceFn

// string translate(string, string, string) 
class TranslateFn : public XPathFunction
{
public:
  TranslateFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(3, 3, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    std::string str = argAsString(0, context, executionContext);
    std::string from = argAsString(1, context, executionContext);
    std::string to = argAsString(2, context, executionContext);

    size_t p = 0;
    for(size_t i = 0, ie = str.length(); i != ie; ++i)
    {
      size_t r = from.find(str[i]);
      if(r == std::string::npos)
        ++p;
      else if(r < to.length())
        str[p++] = to[r];
    } // for ...
    if(p != str.length())
      str.resize(p);

    return new StringValue<std::string, Arabica::default_string_adaptor<std::string> >(str);
  } // evaluate
}; // class TranslateFn

///////////////////////////////////////////////////////
// boolean functions

// boolean boolean(object)
class BooleanFn : public XPathFunction
{
public:
  BooleanFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(argAsBool(0, context, executionContext));
  } // evaluate
}; // class BooleanFn

// boolean not(boolean)
class NotFn : public XPathFunction
{
public:
  NotFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(!argAsBool(0, context, executionContext));
  }
}; // class NotFn

// boolean true()
class TrueFn : public XPathFunction
{
public:
  TrueFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 0, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true);
  } // evaluate
}; // TrueFn

// boolean false()
class FalseFn : public XPathFunction
{
public:
  FalseFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 0, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(false);
  } // evaluate
}; // FalseFn

// boolean lang(string) 

/////////////////////////////////////////////////
// number functions

// number number(object?)
class NumberFn : public XPathFunction
{
public:
  NumberFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(0, 1, args) { }
  
  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    double result = (argCount() > 0) ? argAsNumber(0, context, executionContext) :
                                       StringValue<std::string, Arabica::default_string_adaptor<std::string> >(nodeStringValue(context)).asNumber();
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(result);
  } // evaluate
}; // NumberFn

// number sum(node-set)
class SumFn : public XPathFunction
{
public:
  SumFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    double sum = 0;
    NodeSet<std::string> ns = argAsNodeSet(0, context, executionContext);
    for(NodeSet<std::string>::const_iterator n = ns.begin(), end = ns.end(); n != end; ++n)
      sum += nodeNumberValue(*n);
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(sum);
  } // evaluate
}; // class SumFn

// number floor(number)
class FloorFn : public XPathFunction
{
public:
  FloorFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(std::floor(argAsNumber(0, context, executionContext)));
  } // evaluate
}; // class FloorFn

// number ceiling(number)
class CeilingFn : public XPathFunction
{
public:
  CeilingFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(std::ceil(argAsNumber(0, context, executionContext)));
  } // evaluate
}; // class CeilingFn

// number round(number) 
class RoundFn : public XPathFunction
{
public:
  RoundFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(roundNumber(argAsNumber(0, context, executionContext)));
  } // evaluate
}; // class RoundFn

} // namespace XPath
} // namespace Arabica

#endif
