#ifndef ARABICA_XSLT_TEMPLATE_HPP
#define ARABICA_XSLT_TEMPLATE_HPP

#include "xslt_item.hpp"
#include "xslt_precedence.hpp"

namespace Arabica
{
namespace XSLT
{

class Template : public ItemContainer
{
public:
  Template(const std::string& name,
      	   const std::string& mode,
           const std::string& /* priority */,
	   const Precedence& precedence) :
    matches_(),
    name_(name),
    mode_(mode),
    precedence_(precedence)
  {
  } // Template

  Template(const std::vector<Arabica::XPath::MatchExpr<std::string> >& matches,
           const std::string& name,
           const std::string& mode,
           const std::string& priority,
           const Precedence& precedence) :
    matches_(matches),
    name_(name),
    mode_(mode),
    precedence_(precedence)
  {
    if(!priority.empty())
    {
      double p = boost::lexical_cast<double>(Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(priority));
      for(std::vector<Arabica::XPath::MatchExpr<std::string> >::iterator m = matches_.begin(), me = matches_.end(); m != me; ++m)
        m->override_priority(p);
    } // if ... 
  } // Template

  virtual ~Template()
  {
  } // ~Template

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    execute_children(node, context);
  } // execute

  const std::vector<Arabica::XPath::MatchExpr<std::string> >& compiled_matches() const { return matches_; }
  bool has_name() const { return !name_.empty(); }
  const std::string& name() const { return name_; }
  const std::string& mode() const { return mode_; }
  const Precedence& precedence() const { return precedence_; }

private:
  std::vector<Arabica::XPath::MatchExpr<std::string> > matches_;
  std::string name_;
  std::string mode_;
  const Precedence precedence_;
}; // class Template

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_TEMPLATE_HPP

