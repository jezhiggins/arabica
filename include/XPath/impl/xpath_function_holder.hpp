#ifndef ARABICA_XPATH_FUNCTION_HOLDER_HPP
#define ARABICA_XPATH_FUNCTION_HOLDER_HPP

#include <boost/shared_ptr.hpp>
#include "xpath_value.hpp"
#include "xpath_function.hpp"

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class function_type, class string_type, class string_adaptor>
XPathFunction<string_type, string_adaptor>* CreateFn(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& argExprs) { return new function_type(argExprs); }

template<class string_type, class string_adaptor>
class FunctionHolder : public XPathExpression<string_type, string_adaptor>
{
public:
  FunctionHolder(XPathFunction<string_type, string_adaptor>* func) :
    func_(func)
  {
  } // FunctionHolder

  virtual ~FunctionHolder()
  {
    delete func_;
  } // ~FunctionHolder

  virtual XPathValuePtr<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return XPathValuePtr<string_type, string_adaptor>(func_->evaluate(context, executionContext));
  } // evaluate

  static FunctionHolder* createFunction(const string_type& namespace_uri,
                                        const string_type& name, 
                                        const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& argExprs,
                                        const CompilationContext<string_type, string_adaptor>& context)
  {
    if(string_adaptor::empty(namespace_uri))
      for(const NamedFunction* fn = FunctionLookupTable; fn->name != 0; ++fn)
        if(name == string_adaptor::construct_from_utf8(fn->name))
          return new FunctionHolder(fn->creator(argExprs));

    XPathFunction<string_type, string_adaptor>* func = 
                      context.functionResolver().resolveFunction(namespace_uri, name, argExprs);
    if(func == 0)
    {
      string_type error;
      if(!string_adaptor::empty(namespace_uri))
      {
        string_adaptor::append(error, string_adaptor::construct_from_utf8("{"));
        string_adaptor::append(error, namespace_uri);
        string_adaptor::append(error, string_adaptor::construct_from_utf8("}"));
      } // if ...
      string_adaptor::append(error, name);
      throw UndefinedFunctionException(string_adaptor().asStdString(error));
    } // if(func == 0)
    
    return new FunctionHolder(func);
  } // createFunction

private:
  XPathFunction<string_type, string_adaptor>* func_;

  typedef XPathFunction<string_type, string_adaptor>* (*CreateFnPtr)(const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& argExprs);

  struct NamedFunction { const char* name; CreateFnPtr creator; };

  static const NamedFunction FunctionLookupTable[];
}; // class FunctionHolder

template<class string_type, class string_adaptor>
const typename FunctionHolder<string_type, string_adaptor>::NamedFunction 
FunctionHolder<string_type, string_adaptor>::FunctionLookupTable[] = 
      { // node-set functions
        { "position",        CreateFn<PositionFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "last",            CreateFn<LastFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "count",           CreateFn<CountFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "local-name",      CreateFn<LocalNameFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "namespace-uri",   CreateFn<NamespaceURIFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "name",            CreateFn<NameFn<string_type, string_adaptor>, string_type, string_adaptor> },
        // string functions
        {"string",           CreateFn<StringFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"concat",           CreateFn<ConcatFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"starts-with",      CreateFn<StartsWithFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"contains",         CreateFn<ContainsFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"substring-before", CreateFn<SubstringBeforeFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"substring-after",  CreateFn<SubstringAfterFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"substring",        CreateFn<SubstringFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"string-length",    CreateFn<StringLengthFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"normalize-space",  CreateFn<NormalizeSpaceFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"translate",        CreateFn<TranslateFn<string_type, string_adaptor>, string_type, string_adaptor> },
        // boolean functions
        {"boolean",          CreateFn<BooleanFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"not",              CreateFn<NotFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"true",             CreateFn<TrueFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"false",            CreateFn<FalseFn<string_type, string_adaptor>, string_type, string_adaptor> },
        // number functions
        {"number",           CreateFn<NumberFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"sum",              CreateFn<SumFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"floor",            CreateFn<FloorFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"ceiling",          CreateFn<CeilingFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"round",            CreateFn<RoundFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {0,                  0}
      };

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
