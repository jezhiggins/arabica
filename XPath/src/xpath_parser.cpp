#ifdef _MSC_VER
#pragma warning(disable:4224 4180 4244)
#endif 

#include <XPath/impl/xpath_parser.hpp>

namespace Arabica
{
namespace XPath
{

long getNodeId(node_iter_t const& node)
{
  return static_cast<long>(node->value.id().to_long());
} // getNodeId

node_iter_t& skipWhitespace(node_iter_t& node)
{
  while(getNodeId(node) == impl::S_id)
    ++node;
  return node;
} // skipWhitespace

} // namespace XPath

} // namespace Arabica
// end 
