#ifndef ARABICA_XPATH_FUNCTION_HOLDER_HPP
#define ARABICA_XPATH_FUNCTION_HOLDER_HPP

#include <boost/shared_ptr.hpp>
#include "xpath_value.hpp"
#include "xpath_function.hpp"

namespace Arabica
{
namespace XPath
{

template<class function_type>
XPathFunction* CreateFn(const std::vector<XPathExpressionPtr>& argExprs) { return new function_type(argExprs); }

typedef XPathFunction* (*CreateFnPtr)(const std::vector<XPathExpressionPtr>& argExprs);

struct NamedFunction { const char* name; CreateFnPtr creator; };

const NamedFunction FunctionLookupTable[] = { // node-set functions
                                        { "position",        CreateFn<PositionFn> },
                                        { "last",            CreateFn<LastFn> },
                                        { "count",           CreateFn<CountFn> },
                                        { "local-name",      CreateFn<LocalNameFn> },
                                        { "namespace-uri",   CreateFn<NamespaceURIFn> },
                                        { "name",            CreateFn<NameFn> },
                                        // string functions
                                        {"string",           CreateFn<StringFn> },
                                        {"concat",           CreateFn<ConcatFn> },
                                        {"starts-with",      CreateFn<StartsWithFn> },
                                        {"contains",         CreateFn<ContainsFn> },
                                        {"substring-before", CreateFn<SubstringBeforeFn> },
                                        {"substring-after",  CreateFn<SubstringAfterFn> },
                                        {"substring",        CreateFn<SubstringFn> },
                                        {"string-length",    CreateFn<StringLengthFn> },
                                        {"normalize-space",  CreateFn<NormalizeSpaceFn> },
                                        {"translate",        CreateFn<TranslateFn> },
                                        // boolean functions
                                        {"boolean",          CreateFn<BooleanFn> },
                                        {"not",              CreateFn<NotFn> },
                                        {"true",             CreateFn<TrueFn> },
                                        {"false",            CreateFn<FalseFn> },
                                        // number functions
                                        {"number",           CreateFn<NumberFn> },
                                        {"sum",              CreateFn<SumFn> },
                                        {"floor",            CreateFn<FloorFn> },
                                        {"ceiling",          CreateFn<CeilingFn> },
                                        {"round",            CreateFn<RoundFn> },
                                        {0,                  0}
                                      };

class FunctionHolder : public XPathExpression
{
public:
  FunctionHolder(XPathFunction* func) :
    func_(func)
  {
  } // FunctionHolder

  virtual ~FunctionHolder()
  {
    delete func_;
  } // ~FunctionHolder

  virtual XPathValuePtr evaluate(const DOM::Node<std::string>& context, 
                                 const ExecutionContext& executionContext) const
  {
    return XPathValuePtr(func_->evaluate(context, executionContext));
  } // evaluate

  static FunctionHolder* createFunction(const std::string& name, 
                                        const std::vector<XPathExpressionPtr>& argExprs,
                                        const CompilationContext& context)
  {
    for(const NamedFunction* fn = FunctionLookupTable; fn->name != 0; ++fn)
      if(name == fn->name)
        return new FunctionHolder(fn->creator(argExprs));

    XPathFunction* func = context.functionResolver().resolveFunction(name, argExprs);
    if(func == 0)
      throw std::runtime_error("Function " + name + " not implemented");
    return new FunctionHolder(func);
  } // createFunction

private:
  XPathFunction* func_;
}; // class FunctionResolver

} // namespace XPath
} // namespace Arabica

#endif
