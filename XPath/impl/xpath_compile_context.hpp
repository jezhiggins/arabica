#ifndef ARABICA_XPATH_COMPILE_CONTEXT_HPP
#define ARABICA_XPATH_COMPILE_CONTEXT_HPP

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> > class XPath;
class NamespaceContext;
class FunctionResolver;

template<class string_type>
class CompilationContext
{
public:
  CompilationContext(const XPath<string_type>& xpathCompiler,
                     const NamespaceContext& namespaceContext,
                     const FunctionResolver& functionResolver) :
      xpath_(xpathCompiler),
      namespaceContext_(namespaceContext),
      functionResolver_(functionResolver)
  { 
  } // CompilationContext

  const XPath<string_type>& xpath() const { return xpath_; }
  const NamespaceContext& namespaceContext() const { return namespaceContext_; }
  const FunctionResolver& functionResolver() const { return functionResolver_; }

private:
  const XPath<string_type>& xpath_;
  const NamespaceContext& namespaceContext_;
  const FunctionResolver& functionResolver_;

  CompilationContext(const CompilationContext&);
  CompilationContext& operator=(const CompilationContext&);
  bool operator==(const CompilationContext&) const;
}; // class CompilationContext

} // namespace XPath
} // namespace Arabica

#endif
