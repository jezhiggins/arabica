#ifndef ARABICA_XSLT_APPLY_IMPORTS_HPP
#define ARABICA_XSLT_APPLY_IMPORTS_HPP

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class ApplyImports : public Item<string_type, string_adaptor>
{
public:
  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext<string_type, string_adaptor>& context) const
  {
    context.stylesheet().applyImports(node, context);
  } // execute
}; // class ApplyImports

} // namespace XSLT
} // namespace Arabica

#endif
