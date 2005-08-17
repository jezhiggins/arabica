#ifndef ARABICA_XPATH_FUNCTION_RESOLVER_HPP
#define ARABICA_XPATH_FUNCTION_RESOLVER_HPP

namespace Arabica
{
namespace XPath
{

class XPathFunction;
template<class string_type, class string_adaptor> class XPathExpressionPtr;

class UndefinedFunctionException : public std::runtime_error
{
public:
  UndefinedFunctionException(const std::string& thing) : std::runtime_error("The function '" + thing + "' is undefined.") { }
}; // class UndefinedFunctionException

template<class string_type, class string_adaptor>
class FunctionResolver
{
public:
  virtual ~FunctionResolver() { }

  // TODO: should make this a QName
  virtual XPathFunction* resolveFunction(const string_type& name,
                                         const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& argExprs) const = 0; 
}; // class FunctionResolver

template<class string_type, class string_adaptor>
class FunctionResolverPtr : public boost::shared_ptr<FunctionResolver<string_type, string_adaptor> > 
{
public:
  explicit FunctionResolverPtr(FunctionResolver<string_type, string_adaptor>* fr) : 
      boost::shared_ptr<FunctionResolver<string_type, string_adaptor> >(fr) 
  { 
  } // FunctionResolverPtr
}; // class FunctionResolverPtr

template<class string_type, class string_adaptor>
class NullFunctionResolver : public FunctionResolver<string_type, string_adaptor> 
{
public:
  virtual XPathFunction* resolveFunction(const string_type& name,
                                         const std::vector<XPathExpressionPtr<string_type, string_adaptor> >& argExprs) const 
  {
    throw UndefinedFunctionException(string_adaptor().asStdString(name));
  } // resolveVariable
}; // NullFunctionResolver

} // namespace XPath
} // namespace Arabica

#endif
