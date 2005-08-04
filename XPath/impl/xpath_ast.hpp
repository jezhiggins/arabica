#ifndef ARABICA_XPATHIC_XPATH_AST_HPP
#define ARABICA_XPATHIC_XPATH_AST_HPP

#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/ast.hpp>

namespace Arabica
{
namespace XPath
{

typedef std::string::const_iterator str_iter_t;

typedef boost::spirit::tree_match<str_iter_t> tree_match_t;
typedef tree_match_t::tree_iterator node_iter_t;
typedef boost::spirit::tree_parse_info<str_iter_t> tree_info_t;

long getNodeId(node_iter_t const& node);
node_iter_t& skipWhitespace(node_iter_t& node);

class XPathExpression;
class CompilationContext;
XPathExpression* compile_expression(node_iter_t const& i, CompilationContext& context);

} // namespace XPath
} // namespace Arabica
#endif
