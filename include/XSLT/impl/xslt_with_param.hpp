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
  WithParam(const std::string& name, 
            const Arabica::XPath::XPathExpressionPtr<std::string>& select, 
            const Precedence& precedence) :
      Variable_impl(name, select, precedence)
  {
  } // WithParam

  virtual ~WithParam() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const 
  {
    name_ = context.passParam(node, *this);
  } // declare

  void unpass(ExecutionContext& context) const
  {
    context.unpassParam(name_);
  } // unpass

private:
  mutable std::string name_;
}; // WithParam

class WithParamable
{
protected:
  WithParamable()
  {
  } // WithParamable

  ~WithParamable()
  {
    for(WithParamList::const_iterator s = withparams_.begin(), e = withparams_.end(); s != e; ++s)
      delete (*s);
  } // ~WithParamable

public:
  void add_with_param(WithParam* withparam)
  {
    withparams_.push_back(withparam);
  } // add_WithParam

private:
  void passParams(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    for(WithParamList::const_iterator s = withparams_.begin(), e = withparams_.end(); s != e; ++s)
      (*s)->execute(node, context);
  } // execute

  void unpassParams(ExecutionContext& context) const
  {
    for(WithParamList::const_iterator s = withparams_.begin(), e = withparams_.end(); s != e; ++s)
      (*s)->unpass(context);
  } // unpassParams

  typedef std::vector<WithParam*> WithParamList;
  WithParamList withparams_;

  friend class ParamPasser;
}; // class WithParamable

class ParamPasser
{
public:
  ParamPasser(const WithParamable& paramable,
              const DOM::Node<std::string>& node, 
              ExecutionContext& context) :
    paramable_(paramable),
    context_(context)
  {
    paramable_.passParams(node, context_);
  } // ParamPasser

  ~ParamPasser()
  {
    paramable_.unpassParams(context_);
  } // ~ParamPasser

private:
  const WithParamable& paramable_;
  ExecutionContext& context_;

  ParamPasser(const ParamPasser&);
  ParamPasser& operator=(const ParamPasser&);
  bool operator==(const ParamPasser&) const;
}; // class ParamPasser

} // namespace XSLT
} // namespace Arabica
#endif

