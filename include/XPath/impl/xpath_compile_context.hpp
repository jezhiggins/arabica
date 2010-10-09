#ifndef ARABICA_XPATH_COMPILE_CONTEXT_HPP
#define ARABICA_XPATH_COMPILE_CONTEXT_HPP

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor> class XPath;
template<class string_type, class string_adaptor> class NamespaceContext;
template<class string_type, class string_adaptor> class FunctionResolver;
template<class string_type, class string_adaptor> class VariableCompileTimeResolver;

namespace impl
{

template<class string_type, class string_adaptor>
class CompilationContext : private NamespaceContext<string_type, string_adaptor>
{
public:
  CompilationContext(const XPath<string_type, string_adaptor>& xpathCompiler,
                     const NamespaceContext<string_type, string_adaptor>& namespaceContext,
                     const FunctionResolver<string_type, string_adaptor>& functionResolver,
		     const VariableCompileTimeResolver<string_type, string_adaptor>& variableCompileTimeResolver) :
      xpath_(xpathCompiler),
      namespaceContext_(namespaceContext),
      functionResolver_(functionResolver),
      ctVariableResolver_(variableCompileTimeResolver)
  { 
  } // CompilationContext

  const XPath<string_type, string_adaptor>& xpath() const { return xpath_; }
  const NamespaceContext<string_type, string_adaptor>& namespaceContext() const { return *this; }
  const FunctionResolver<string_type, string_adaptor>& functionResolver() const { return functionResolver_; }
  const VariableCompileTimeResolver<string_type, string_adaptor>& ctVariableResolver() const { return ctVariableResolver_; }

private:
  virtual string_type namespaceURI(const string_type& prefix) const
  {
    string_type uri = namespaceContext_.namespaceURI(prefix);
    if(string_adaptor::empty(uri))
      throw Arabica::XPath::UnboundNamespacePrefixException(string_adaptor::asStdString(prefix)); 
    return uri;
  } // namespaceURI


  const XPath<string_type, string_adaptor>& xpath_;
  const NamespaceContext<string_type, string_adaptor>& namespaceContext_;
  const FunctionResolver<string_type, string_adaptor>& functionResolver_;
  const VariableCompileTimeResolver<string_type, string_adaptor>& ctVariableResolver_;

  CompilationContext(const CompilationContext&);
  CompilationContext& operator=(const CompilationContext&);
  bool operator==(const CompilationContext&) const;
}; // class CompilationContext

} // namespace impl
} // namespace XPath
} // namespace Arabica

#endif
