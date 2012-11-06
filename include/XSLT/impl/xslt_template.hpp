#ifndef ARABICA_XSLT_TEMPLATE_HPP
#define ARABICA_XSLT_TEMPLATE_HPP

#include "xslt_item.hpp"
#include "xslt_precedence.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class Template : public ItemContainer
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  typedef Arabica::XPath::MatchExpr<string_type, string_adaptor> MatchExpr;
  typedef std::vector<MatchExpr> MatchExprList;

  Template(const string_type& name,
      	   const string_type& mode,
           const string_type& /* priority */,
	   const Precedence& precedence) :
    matches_(),
    name_(name),
    mode_(mode),
    precedence_(precedence)
  {
  } // Template

  Template(const MatchExprList& matches,
           const string_type& name,
           const string_type& mode,
           const string_type& priority,
           const Precedence& precedence) :
    matches_(matches),
    name_(name),
    mode_(mode),
    precedence_(precedence)
  {
    if(!priority.empty())
    {
      double p = boost::lexical_cast<double>(Arabica::text::normalize_whitespace<string_type, string_adaptor>(priority));
      for(typename MatchExprList::iterator m = matches_.begin(), me = matches_.end(); m != me; ++m)
        m->override_priority(p);
    } // if ... 
  } // Template

  virtual ~Template()
  {
  } // ~Template

  virtual void execute(const DOM::Node<string_type>& node, ExecutionContext& context) const
  {
    execute_children(node, context);
  } // execute

  const MatchExprList& compiled_matches() const { return matches_; }
  bool has_name() const { return !name_.empty(); }
  const string_type& name() const { return name_; }
  const string_type& mode() const { return mode_; }
  const Precedence& precedence() const { return precedence_; }

private:
  MatchExprList matches_;
  string_type name_;
  string_type mode_;
  const Precedence precedence_;
}; // class Template

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_TEMPLATE_HPP

