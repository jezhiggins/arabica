#ifndef ARABICA_XSLT_WITH_PARAM_HPP
#define ARABICA_XSLT_WITH_PARAM_HPP

#include "xslt_variable_impl.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class WithParam : public Variable_impl
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  WithParam(const string_type& name, 
            const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& select, 
            const Precedence& precedence) :
      Variable_impl(name, select, precedence)
  {
  } // WithParam

  virtual ~WithParam() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, 
                       ExecutionContext& context) const 
  {
    name_ = context.passParam(node, *this);
  } // declare

  void unpass(ExecutionContext& context) const
  {
    context.unpassParam(name_);
  } // unpass

private:
  mutable string_type name_;
}; // WithParam

template<class string_type, class string_adaptor>
class WithParamable
{
protected:
  WithParamable()
  {
  } // WithParamable

  ~WithParamable()
  {
    for(WithParamListIterator s = withparams_.begin(), e = withparams_.end(); s != e; ++s)
      delete (*s);
  } // ~WithParamable

public:
  void add_with_param(WithParam<string_type, string_adaptor>* withparam)
  {
    withparams_.push_back(withparam);
  } // add_WithParam

private:
  void passParams(const DOM::Node<string_type, string_adaptor>& node, 
                  ExecutionContext& context) const
  {
    for(WithParamListIterator s = withparams_.begin(), e = withparams_.end(); s != e; ++s)
      (*s)->execute(node, context);
  } // execute

  void unpassParams(ExecutionContext& context) const
  {
    for(WithParamListIterator s = withparams_.begin(), e = withparams_.end(); s != e; ++s)
      (*s)->unpass(context);
  } // unpassParams

  typedef std::vector<WithParam<string_type, string_adaptor>*> WithParamList;
  typedef typename WithParamList::const_iterator WithParamListIterator;
  WithParamList withparams_;

  template<class string_type, class string_adaptor> friend class ParamPasser;
}; // class WithParamable

template<class string_type, class string_adaptor>
class ParamPasser
{
public:
  ParamPasser(const WithParamable<string_type, string_adaptor>& paramable,
              const DOM::Node<string_type, string_adaptor>& node, 
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
  const WithParamable<string_type, string_adaptor>& paramable_;
  ExecutionContext& context_;

  ParamPasser(const ParamPasser&);
  ParamPasser& operator=(const ParamPasser&);
  bool operator==(const ParamPasser&) const;
}; // class ParamPasser

} // namespace XSLT
} // namespace Arabica
#endif

