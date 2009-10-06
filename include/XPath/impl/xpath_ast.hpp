#ifndef ARABICA_XPATHIC_XPATH_AST_HPP
#define ARABICA_XPATHIC_XPATH_AST_HPP


#include <boost/version.hpp>

#if BOOST_VERSION >= 103800
#define BOOST_SPIRIT_USE_OLD_NAMESPACE 1
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_ast.hpp>
#else
#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/ast.hpp>
#endif

#include "xpath_ast_ids.hpp"

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class string_adaptor>
class types
{
public:
  typedef typename string_adaptor::const_iterator str_iter_t;
  typedef boost::spirit::tree_match<str_iter_t> tree_match_t;
  typedef typename tree_match_t::tree_iterator node_iter_t;
  typedef boost::spirit::tree_parse_info<str_iter_t> tree_info_t;
}; // types

template<class string_adaptor>
long getNodeId(typename types<string_adaptor>::node_iter_t const& node)
{
  return static_cast<long>(node->value.id().to_long());
} // getNodeId

template<class string_adaptor>
typename types<string_adaptor>::node_iter_t& skipWhitespace(typename types<string_adaptor>::node_iter_t& node)
{
  while(getNodeId<string_adaptor>(node) == impl::S_id)
    ++node;
  return node;
} // skipWhitespace

} // namespace impl
} // namespace XPath
} // namespace Arabica
#endif
