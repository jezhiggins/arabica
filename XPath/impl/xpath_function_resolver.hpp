#ifndef ARABICA_XPATH_FUNCTION_RESOLVER_HPP
#define ARABICA_XPATH_FUNCTION_RESOLVER_HPP

#include <boost/shared_ptr.hpp>

namespace Arabica
{
namespace XPath
{

class XPathFunction;
class XPathExpression;
typedef boost::shared_ptr<XPathExpression> XPathExpressionPtr;

class UndefinedFunctionException : public std::runtime_error
{
public:
  UndefinedFunctionException(const std::string& thing) : std::runtime_error("The function '" + thing + "' is undefined.") { }
}; // class UndefinedFunctionException

class FunctionResolver
{
public:
  virtual ~FunctionResolver() { }

  // TODO: should make this a QName
  virtual XPathFunction* resolveFunction(const std::string& name,
                                         const std::vector<XPathExpressionPtr>& argExprs) const = 0; 
}; // class FunctionResolver

typedef boost::shared_ptr<FunctionResolver> FunctionResolverPtr;

class NullFunctionResolver : public FunctionResolver
{
public:
  virtual XPathFunction* resolveFunction(const std::string& name,
                                         const std::vector<XPathExpressionPtr>& argExprs) const
  {
    throw UndefinedFunctionException(name);
  } // resolveVariable
}; // NullFunctionResolver

} // namespace XPath
} // namespace Arabica

#endif
