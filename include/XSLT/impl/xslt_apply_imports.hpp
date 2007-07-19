#ifndef ARABICA_XSLT_APPLY_IMPORTS_HPP
#define ARABICA_XSLT_APPLY_IMPORTS_HPP

namespace Arabica
{
namespace XSLT
{

class ApplyImports : public Item
{
public:
  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    context.stylesheet().applyImports(node, context);
  } // execute
}; // class ApplyImports

} // namespace XSLT
} // namespace Arabica

#endif
