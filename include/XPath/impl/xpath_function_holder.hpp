#ifndef ARABICA_XPATH_FUNCTION_HOLDER_HPP
#define ARABICA_XPATH_FUNCTION_HOLDER_HPP

#include <boost/shared_ptr.hpp>
#include "xpath_expression.hpp"
#include "xpath_function.hpp"

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class function_type, class string_type, class string_adaptor>
XPathFunction<string_type, string_adaptor>* CreateFn(const std::vector<XPathExpression<string_type, string_adaptor> >& argExprs) { return new function_type(argExprs); }

} // namespace impl

  template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class StandardXPathFunctionResolver
{
public:
  virtual ~StandardXPathFunctionResolver() { }

  virtual XPathFunction<string_type, string_adaptor>*
      resolveFunction(const string_type& namespace_uri,
		      const string_type& name, 
		      const std::vector<XPathExpression<string_type, string_adaptor> >& argExprs) const
  {
    return standardFunction(namespace_uri, name, argExprs);
  } // resolveFuncton

  virtual std::vector<std::pair<string_type, string_type> > validNames() const
  {
    std::vector<std::pair<string_type, string_type> > names;
    for(const NamedFunction* fn = FunctionLookupTable; fn->name != 0; ++fn)
      names.push_back(std::make_pair(string_adaptor::empty_string(),
				     string_adaptor::construct_from_utf8(fn->name)));
    return names;
  } // hasFunction    

  static XPathFunction<string_type, string_adaptor>*
      standardFunction(const string_type& namespace_uri,
		       const string_type& name,
		       const std::vector<XPathExpression<string_type, string_adaptor> >& argExprs)
  {
    const NamedFunction* fn = findFunction(namespace_uri, name);
    return (fn != 0) ? fn->creator(argExprs) : 0;
  } // standardFunction

private:
  typedef XPathFunction<string_type, string_adaptor>* (*CreateFnPtr)(const std::vector<XPathExpression<string_type, string_adaptor> >& argExprs);

  struct NamedFunction { const char* name; CreateFnPtr creator; };

  static const NamedFunction FunctionLookupTable[];

  static const NamedFunction* findFunction(const string_type& namespace_uri,
					   const string_type& name) 
  {
    if(!string_adaptor::empty(namespace_uri))
      return 0;

    for(const NamedFunction* fn = FunctionLookupTable; fn->name != 0; ++fn)
      if(name == string_adaptor::construct_from_utf8(fn->name))
	return fn;

    return 0;
  } // findFunction
}; // class StandardXPathFunctionResolver

template<class string_type, class string_adaptor>
const typename StandardXPathFunctionResolver<string_type, string_adaptor>::NamedFunction 
StandardXPathFunctionResolver<string_type, string_adaptor>::FunctionLookupTable[] = 
      { // node-set functions
        { "position",        impl::CreateFn<impl::PositionFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "last",            impl::CreateFn<impl::LastFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "count",           impl::CreateFn<impl::CountFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "local-name",      impl::CreateFn<impl::LocalNameFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "namespace-uri",   impl::CreateFn<impl::NamespaceURIFn<string_type, string_adaptor>, string_type, string_adaptor> },
        { "name",            impl::CreateFn<impl::NameFn<string_type, string_adaptor>, string_type, string_adaptor> },
        // string functions
        {"string",           impl::CreateFn<impl::StringFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"concat",           impl::CreateFn<impl::ConcatFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"starts-with",      impl::CreateFn<impl::StartsWithFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"contains",         impl::CreateFn<impl::ContainsFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"substring-before", impl::CreateFn<impl::SubstringBeforeFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"substring-after",  impl::CreateFn<impl::SubstringAfterFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"substring",        impl::CreateFn<impl::SubstringFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"string-length",    impl::CreateFn<impl::StringLengthFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"normalize-space",  impl::CreateFn<impl::NormalizeSpaceFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"translate",        impl::CreateFn<impl::TranslateFn<string_type, string_adaptor>, string_type, string_adaptor> },
        // boolean functions
        {"boolean",          impl::CreateFn<impl::BooleanFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"not",              impl::CreateFn<impl::NotFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"true",             impl::CreateFn<impl::TrueFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"false",            impl::CreateFn<impl::FalseFn<string_type, string_adaptor>, string_type, string_adaptor> },
        // number functions
        {"number",           impl::CreateFn<impl::NumberFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"sum",              impl::CreateFn<impl::SumFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"floor",            impl::CreateFn<impl::FloorFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"ceiling",          impl::CreateFn<impl::CeilingFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {"round",            impl::CreateFn<impl::RoundFn<string_type, string_adaptor>, string_type, string_adaptor> },
        {0,                  0}
      };

namespace impl 
{

template<class string_type, class string_adaptor>
class FunctionHolder : public XPathExpression_impl<string_type, string_adaptor>
{
public:
  FunctionHolder(XPathFunction<string_type, string_adaptor>* func,
                 const string_type& namespace_uri, 
                 const string_type& name) :
    func_(func),
    namespace_uri_(namespace_uri),
    name_(name)
  {
  } // FunctionHolder

  virtual ~FunctionHolder()
  {
    delete func_;
  } // ~FunctionHolder

  const string_type& namespace_uri() const { return namespace_uri_; }
  const string_type& name() const { return name_; }

  virtual ValueType type() const { return func_->type(); }

  virtual XPathValue<string_type, string_adaptor> evaluate(const DOM::Node<string_type, string_adaptor>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return XPathValue<string_type, string_adaptor>(func_->evaluate(context, executionContext));
  } // evaluate

  static FunctionHolder* createFunction(const string_type& namespace_uri,
                                        const string_type& name, 
                                        const std::vector<XPathExpression<string_type, string_adaptor> >& argExprs,
                                        const CompilationContext<string_type, string_adaptor>& context)
  {
    XPathFunction<string_type, string_adaptor>* func = 0;

    if(string_adaptor::empty(namespace_uri))
      func = StandardXPathFunctionResolver<string_type, string_adaptor>::standardFunction(namespace_uri, name, argExprs);
    if(func == 0)
      func = context.functionResolver().resolveFunction(namespace_uri, name, argExprs);

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
    
    return new FunctionHolder(func, namespace_uri, name);
  } // createFunction

private:
  XPathFunction<string_type, string_adaptor>* func_;
  string_type namespace_uri_;
  string_type name_;
}; // class FunctionHolder

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
