#ifndef ARABICA_XPATH_FUNCTION_RESOLVER_HPP
#define ARABICA_XPATH_FUNCTION_RESOLVER_HPP

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor> class XPathFunction;
template<class string_type, class string_adaptor> class XPathExpression;

class UndefinedFunctionException : public std::runtime_error
{
public:
  UndefinedFunctionException(const std::string& thing) : std::runtime_error("The function '" + thing + "' is undefined.") { }
}; // class UndefinedFunctionException

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class FunctionResolver
{
public:
  virtual ~FunctionResolver() { }

  virtual XPathFunction<string_type, string_adaptor>* 
      resolveFunction(const string_type& namespace_uri,
                      const string_type& name,
                      const std::vector<XPathExpression<string_type, string_adaptor> >& argExprs) const = 0; 

  virtual std::vector<std::pair<string_type, string_type> > validNames() const = 0;
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
  virtual XPathFunction<string_type, string_adaptor>* 
      resolveFunction(const string_type& namespace_uri,
                      const string_type& name,
                      const std::vector<XPathExpression<string_type, string_adaptor> >& /* argExprs */) const 
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
  } // resolveFunction

  virtual std::vector<std::pair<string_type, string_type> > validNames() const
  {
    const std::vector<std::pair<string_type, string_type> > none;
    return none;
  } // validNames
}; // NullFunctionResolver

} // namespace XPath
} // namespace Arabica

#endif
