#ifndef ARABICA_XSLT_TOP_LEVEL_PARAM_HPP
#define ARABICA_XSLT_TOP_LEVEL_PARAM_HPP

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class TopLevelParam : public Variable_declaration
{
public:
  TopLevelParam(const string_type& namespace_uri,
                const string_type& name, 
                Arabica::XPath::XPathValue<string_type, string_adaptor> value) :
      namespace_uri_(namespace_uri),
      name_(name),
      value_(value)
  {
  } // TopLevelParam

  virtual ~TopLevelParam() { }

  virtual void declare(ExecutionContext& context) const 
  {
    context.topLevelParam(null_node, *this);
  } // declare

  virtual const string_type& namespace_uri() const { return namespace_uri_; }
  virtual const string_type& name() const { return name_; }
  virtual Arabica::XPath::XPathValue<string_type, string_adaptor> value(const DOM::Node<string_type, string_adaptor>& /* node */, 
                                                        ExecutionContext& /* context */,
                                                        DOMSink& /* sink */) const 
  {
    return value_;
  } // value
  virtual const Precedence& precedence() const { return Precedence::InitialPrecedence(); }

private:
  static DOM::Node<string_type, string_adaptor> null_node;
  string_type namespace_uri_;
  string_type name_;
  Arabica::XPath::XPathValue<string_type, string_adaptor> value_;
}; // class TopLevelParam

template<class string_type, class string_adaptor>
DOM::Node<string_type, string_adaptor> TopLevelParam<string_type, string_adaptor>::null_node;

} // namespace XSLT
} // namespace Arabica
#endif

