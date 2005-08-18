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

template<class string_type, class string_adaptor>
class XPathFunction
{
protected:
  XPathFunction(int minArgs, int maxArgs, const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) :
      args_(args)
  {
    if(((minArgs != -1) && (static_cast<int>(args.size()) < minArgs)) ||
       ((maxArgs != -1) && (static_cast<int>(args.size()) > maxArgs)))
       throw SyntaxException("wrong number of arguments to function");
  } // XPathFunction

public:
  virtual ~XPathFunction() { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context, 
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const = 0;

protected:
  size_t argCount() const { return args_.size(); }

  bool argAsBool(size_t index,
                 const DOM::Node<string_type>& context,
                 const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index]->evaluate(context, executionContext)->asBool();
  } // argAsBool

  double argAsNumber(size_t index,
                     const DOM::Node<string_type>& context,
                     const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index]->evaluate(context, executionContext)->asNumber();
  } // argAsNumber

  string_type argAsString(size_t index, 
                          const DOM::Node<string_type>& context,
                          const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index]->evaluate(context, executionContext)->asString();
  } // argAsString

  NodeSet<string_type> argAsNodeSet(size_t index,
                                    const DOM::Node<string_type>& context,
                                    const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return args_[index]->evaluate(context, executionContext)->asNodeSet();
  } // argAsNodeSet

private:
  const std::vector<XPathExpressionPtr<string_type, string_adaptor> > args_;
}; // class XPathFunction

////////////////////////////////
// node-set functions
// number last()
template<class string_type, class string_adaptor>
class LastFn : public XPathFunction<string_type, string_adaptor>
{
public:
  LastFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(0, 0, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new NumericValue<string_type, string_adaptor>(executionContext.last());
  } // evaluate
}; // class LastFn

// number position()
template<class string_type, class string_adaptor>
class PositionFn : public XPathFunction<string_type, string_adaptor>
{
public:
  PositionFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(0, 0, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new NumericValue<string_type, string_adaptor>(executionContext.position());
  } // evaluate
}; // class PositionFn

// number count(node-set)
template<class string_type, class string_adaptor>
class CountFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  CountFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(1, 1, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new NumericValue<string_type, string_adaptor>(baseT::argAsNodeSet(0, context, executionContext).size());
  } // evaluate
}; // class CountFn

// node-set id(object)
// string local-name(node-set?)
template<class string_type, class string_adaptor>
class LocalNameFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  LocalNameFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(0, 1, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    DOM::Node<string_type> node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      NodeSet<string_type> ns = baseT::argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
        case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
          return new StringValue<string_type, string_adaptor>(node.hasNamespaceURI() ? node.getLocalName() : node.getNodeName());
        default: // put this in to keep gcc quiet
          ; 
      } // switch ...
    return new StringValue<string_type, string_adaptor>("");
  } // evaluate
}; // class LocalNameFn

// string namespace-uri(node-set?)
template<class string_type, class string_adaptor>
class NamespaceURIFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  NamespaceURIFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(0, 1, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    DOM::Node<string_type> node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      NodeSet<string_type> ns = baseT::argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
          return new StringValue<string_type, string_adaptor>(node.getNamespaceURI());
        default: // put this in to keep gcc quiet
          ; 
      } // switch ...
    return new StringValue<string_type, string_adaptor>("");
  } // evaluate
}; // class NamespaceURIFn

// string name(node-set?) 
template<class string_type, class string_adaptor>
class NameFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  NameFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(0, 1, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    DOM::Node<string_type> node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      NodeSet<string_type> ns = baseT::argAsNodeSet(0, context, executionContext);
      if(ns.size() != 0)
        node = ns.top();
    } // if ...

    if(node != 0)
      switch(node.getNodeType())
      {
        case DOM::Node_base::ATTRIBUTE_NODE:
        case DOM::Node_base::ELEMENT_NODE:
        case DOM::Node_base::PROCESSING_INSTRUCTION_NODE:
          return new StringValue<string_type, string_adaptor>(node.getNodeName());
        default: // stop gcc generating a warning about unhandled enum values
          ;
      } // switch ...
    return new StringValue<string_type, string_adaptor>("");
  } // evaluate
}; // class NameFn

///////////////////////////////////////////////
// string functions

// string string(object?)
template<class string_type, class string_adaptor>
class StringFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  StringFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(0, 1, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new StringValue<string_type, string_adaptor>((baseT::argCount() > 0) ? baseT::argAsString(0, context, executionContext) : nodeStringValue(context));
  } // evaluate
}; // class StringFn

// string concat(string, string, string*)
template<class string_type, class string_adaptor>
class ConcatFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  ConcatFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(2, -1, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type s;
    for(size_t a = 0, ae = baseT::argCount(); a < ae; ++a)
      s.append(baseT::argAsString(a, context, executionContext));
    return new StringValue<string_type, string_adaptor>(s);
  } // evaluate
}; // ConcatFn

// boolean starts-with(string, string)
template<class string_type, class string_adaptor>
class StartsWithFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  StartsWithFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(2, 2, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = baseT::argAsString(0, context, executionContext);
    string_type start = baseT::argAsString(1, context, executionContext);

    if(value.length() < start.length())
      return new BoolValue<string_type, string_adaptor>(false);

    for(size_t i = 0, ie = start.length(); i < ie; ++i)
      if(value[i] != start[i])
        return new BoolValue<string_type, string_adaptor>(false);

    return new BoolValue<string_type, string_adaptor>(true);
  } // evaluate
}; // StartsWithFn

// boolean contains(string, string)
template<class string_type, class string_adaptor>
class ContainsFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  ContainsFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(2, 2, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new BoolValue<string_type, string_adaptor>(baseT::argAsString(0, context, executionContext).find(baseT::argAsString(1, context, executionContext)) != string_type::npos);
  } // evaluate
}; // class ContainsFn

// string substring-before(string, string)
template<class string_type, class string_adaptor>
class SubstringBeforeFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  SubstringBeforeFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(2, 2, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = baseT::argAsString(0, context, executionContext);
    size_t splitAt = value.find(baseT::argAsString(1, context, executionContext));

    if(splitAt == string_type::npos)
      return new StringValue<string_type, string_adaptor>("");

    return new StringValue<string_type, string_adaptor>(value.substr(0, splitAt));
  } // evaluate
}; // class SubstringBeforeFn

// string substring-after(string, string)
template<class string_type, class string_adaptor>
class SubstringAfterFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  SubstringAfterFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(2, 2, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = baseT::argAsString(0, context, executionContext);
    string_type split = baseT::argAsString(1, context, executionContext);
    size_t splitAt = value.find(split);

    if((splitAt == string_type::npos) || ((splitAt + split.length()) >= value.length()))
      return new StringValue<string_type, string_adaptor>("");

    return new StringValue<string_type, string_adaptor>(value.substr(splitAt + split.length()));
  } // evaluate
}; // class SubstringAfterFn

// string substring(string, number, number?)
template<class string_type, class string_adaptor>
class SubstringFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  SubstringFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(2, 3, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = baseT::argAsString(0, context, executionContext);
    double startAt = roundNumber(baseT::argAsNumber(1, context, executionContext)) - 1;
    double endAt = roundNumber((baseT::argCount() == 3 ? baseT::argAsNumber(2, context, executionContext) : Infinity)) + startAt;

    if((endAt < 0) || (endAt < startAt) || (isNaN(endAt)))
      return new StringValue<string_type, string_adaptor>("");

    if(startAt < 0)
      startAt = 0;
    if((isInfinite(endAt)) || (endAt > value.length()))
      endAt = value.length();

    return new StringValue<string_type, string_adaptor>(value.substr(static_cast<int>(startAt), static_cast<int>(endAt - startAt)));
  } // evaluate
}; // SubstringFn

// number string-length(string?)
template<class string_type, class string_adaptor>
class StringLengthFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  StringLengthFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(0, 1, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return new NumericValue<string_type, string_adaptor>(((baseT::argCount() > 0) ? baseT::argAsString(0, context, executionContext) : nodeStringValue(context)).length());
  } // evaluate
}; // StringLengthFn

// string normalize-space(string?)
template<class string_type, class string_adaptor>
class NormalizeSpaceFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  NormalizeSpaceFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(0, 1, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type value = ((baseT::argCount() > 0) ? baseT::argAsString(0, context, executionContext) : nodeStringValue(context));
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

    return new StringValue<string_type, string_adaptor>(value);
  } // evaluate
}; // class NormalizeSpaceFn

// string translate(string, string, string) 
template<class string_type, class string_adaptor>
class TranslateFn : public XPathFunction<string_type, string_adaptor>
{
  typedef XPathFunction<string_type, string_adaptor> baseT;
public:
  TranslateFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& args) : XPathFunction<string_type, string_adaptor>(3, 3, args) { }

  virtual XPathValue<string_type>* evaluate(const DOM::Node<string_type>& context,
                                            const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    string_type str = baseT::argAsString(0, context, executionContext);
    string_type from = baseT::argAsString(1, context, executionContext);
    string_type to = baseT::argAsString(2, context, executionContext);

    size_t p = 0;
    for(size_t i = 0, ie = str.length(); i != ie; ++i)
    {
      size_t r = from.find(str[i]);
      if(r == string_type::npos)
        ++p;
      else if(r < to.length())
        str[p++] = to[r];
    } // for ...
    if(p != str.length())
      str.resize(p);

    return new StringValue<string_type, string_adaptor>(str);
  } // evaluate
}; // class TranslateFn

///////////////////////////////////////////////////////
// boolean functions

// boolean boolean(object)
class BooleanFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  BooleanFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(argAsBool(0, context, executionContext));
  } // evaluate
}; // class BooleanFn

// boolean not(boolean)
class NotFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  NotFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(!argAsBool(0, context, executionContext));
  }
}; // class NotFn

// boolean true()
class TrueFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  TrueFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(0, 0, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new BoolValue<std::string, Arabica::default_string_adaptor<std::string> >(true);
  } // evaluate
}; // TrueFn

// boolean false()
class FalseFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  FalseFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(0, 0, args) { }

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
class NumberFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  NumberFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(0, 1, args) { }
  
  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    double result = (argCount() > 0) ? argAsNumber(0, context, executionContext) :
                                       StringValue<std::string, Arabica::default_string_adaptor<std::string> >(nodeStringValue(context)).asNumber();
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(result);
  } // evaluate
}; // NumberFn

// number sum(node-set)
class SumFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  SumFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(1, 1, args) { }

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
class FloorFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  FloorFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(std::floor(argAsNumber(0, context, executionContext)));
  } // evaluate
}; // class FloorFn

// number ceiling(number)
class CeilingFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  CeilingFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(std::ceil(argAsNumber(0, context, executionContext)));
  } // evaluate
}; // class CeilingFn

// number round(number) 
class RoundFn : public XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >
{
public:
  RoundFn(const std::vector<XPathExpressionPtr<std::string, Arabica::default_string_adaptor<std::string> > >& args) : XPathFunction<std::string, Arabica::default_string_adaptor<std::string> >(1, 1, args) { }

  virtual XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const ExecutionContext<std::string, Arabica::default_string_adaptor<std::string> >& executionContext) const
  {
    return new NumericValue<std::string, Arabica::default_string_adaptor<std::string> >(roundNumber(argAsNumber(0, context, executionContext)));
  } // evaluate
}; // class RoundFn

} // namespace XPath
} // namespace Arabica

#endif
