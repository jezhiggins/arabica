#ifndef ARABICA_XSLT_VARIABLES_HANDLER_HPP
#define ARABICA_XSLT_VARIABLES_HANDLER_HPP

#include "../xslt_param.hpp"
#include "../xslt_variable.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class VType>
class VariableHandler : public ItemContainerHandler<VType>
{
public:
  typedef typename VType::string_type string_type;
  typedef typename VType::string_adaptor string_adaptor;
private:
  typedef StylesheetConstant<string_type, string_adaptor> SC;
  typedef AttributeValidators<string_type, string_adaptor> AV;
  typedef ItemContainerHandler<VType> baseT;

public:
  VariableHandler(CompilationContext<string_type, string_adaptor>& context) :
    baseT(context),
    has_select_(false),
    precedence_(Precedence::FrozenPrecedence())
  {
  } // VariableHandler

  VariableHandler(CompilationContext<string_type, string_adaptor>& context, const Precedence& precedence) :
    baseT(context),
    has_select_(false),
    precedence_(precedence)
  {
  } // VariableHandler

protected:
  virtual VType* createContainer(const string_type& /* namespaceURI */,
                                 const string_type& /* localName */,
                                 const string_type& qName,
                                 const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const AV rules = AV::rule(SC::name, true)
                               .rule(SC::select, false);
    
    std::map<string_type, string_type> attrs = rules.gather(qName, atts);

    const string_type& select = atts.getValue(SC::select);
    Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> xpath;
    if(select != string_adaptor::empty_string())
    {
      xpath = baseT::context().xpath_expression(select);
      has_select_ = true;
    } // if ...

    string_type name = baseT::context().processInternalQName(attrs[SC::name]).clarkName();
    return new VType(name, xpath, precedence_);
  } // createContainer

  virtual void characters(const string_type& ch)
  {
    if(has_select_)
    {
      for(typename string_type::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
	    if(!Arabica::XML::is_space(*i))
	      throw SAX::SAXException("A variable or param can not have both a select attribute and text context");
    }
    ItemContainerHandler<VType>::characters(ch);
  } // characters

private:
  bool has_select_;
  const Precedence precedence_;
}; // class VariableHandler

template<class VType>
class TopLevelVariableHandler : public VariableHandler<VType>
{
public:
  typedef typename VType::string_type string_type;
  typedef typename VType::string_adaptor string_adaptor;
  typedef VariableHandler<VType> baseT;

  TopLevelVariableHandler(CompilationContext<string_type, string_adaptor>& context) :
      baseT(context, context.precedence())
  {
  } // VariableHandler

  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    baseT::context().stylesheet().add_variable(baseT::container());
    baseT::context().pop();
  } // endElement

}; // class TopLevelVariableHandler

} // namespace XSLT
} // namespace Arabica
#endif 

