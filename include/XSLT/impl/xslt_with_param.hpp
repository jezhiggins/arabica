#ifndef ARABICA_XSLT_WITH_PARAM_HPP
#define ARABICA_XSLT_WITH_PARAM_HPP

#include "xslt_variable_impl.hpp"

namespace Arabica
{
namespace XSLT
{

class WithParam : public Variable_impl
{
public:
  WithParam(const std::string& namespace_uri,
            const std::string& name, 
            Arabica::XPath::XPathExpressionPtr<std::string> select) :
      Variable_impl(namespace_uri, name, select)
  {
  } // WithParam

  virtual ~WithParam() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const 
  {
    context.passParam(node, *this);
  } // declare
}; // WithParam

class WithParamable
{
protected:
  WithParamable()
  {
  } // WithParamable

  ~WithParamable()
  {
  } // ~WithParamable

  void passParams(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    for(boost::ptr_vector<WithParam>::const_iterator s = withparams_.begin(), e = withparams_.end(); s != e; ++s)
      s->execute(node, context);
  } // execute

public:
  void add_with_param(WithParam* withparam)
  {
    withparams_.push_back(withparam);
  } // add_WithParam

  boost::ptr_vector<WithParam> withparams_;

  friend class PassParam;
}; // class WithParamable

} // namespace XSLT
} // namespace Arabica
#endif

