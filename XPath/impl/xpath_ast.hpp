#ifndef ARABICA_XPATHIC_XPATH_AST_HPP
#define ARABICA_XPATHIC_XPATH_AST_HPP

#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/ast.hpp>

#include "xpath_ast_ids.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type>
class types
{
public:
  typedef typename string_type::const_iterator str_iter_t;
  typedef boost::spirit::tree_match<str_iter_t> tree_match_t;
  typedef typename tree_match_t::tree_iterator node_iter_t;
  typedef boost::spirit::tree_parse_info<str_iter_t> tree_info_t;

private:
  ~types();
}; // types

template<class string_type>
long getNodeId(typename types<string_type>::node_iter_t const& node)
{
  return static_cast<long>(node->value.id().to_long());
} // getNodeId

template<class string_type>
typename types<string_type>::node_iter_t& skipWhitespace(typename types<string_type>::node_iter_t& node)
{
  while(getNodeId<string_type>(node) == impl::S_id)
    ++node;
  return node;
} // skipWhitespace

} // namespace XPath
} // namespace Arabica
#endif
