#ifndef ARABICA_XSLT_TOP_LEVEL_PARAM_HPP
#define ARABICA_XSLT_TOP_LEVEL_PARAM_HPP

namespace Arabica
{
namespace XSLT
{

class TopLevelParam : public Variable_declaration
{
public:
  TopLevelParam(const std::string& namespace_uri,
                const std::string& name, 
                Arabica::XPath::XPathValue<std::string> value) :
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

  virtual const std::string& namespace_uri() const { return namespace_uri_; }
  virtual const std::string& name() const { return name_; }
  virtual Arabica::XPath::XPathValue<std::string> value(const DOM::Node<std::string>& /* node */, 
                                                        ExecutionContext& /* context */,
                                                        DOMSink& /* sink */) const 
  {
    return value_;
  } // value
  virtual const Precedence& precedence() const { return Precedence::InitialPrecedence(); }

private:
  static DOM::Node<std::string> null_node;
  std::string namespace_uri_;
  std::string name_;
  Arabica::XPath::XPathValue<std::string> value_;
}; // class TopLevelParam

DOM::Node<std::string> TopLevelParam::null_node;

} // namespace XSLT
} // namespace Arabica
#endif

