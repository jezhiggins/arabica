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
  VariableHandler(CompilationContext& context) :
    ItemContainerHandler<VType>(context),
    has_select_(false),
    precedence_(Precedence::FrozenPrecedence())
  {
  } // VariableHandler

  VariableHandler(CompilationContext& context, const Precedence& precedence) :
    ItemContainerHandler<VType>(context),
    has_select_(false),
    precedence_(precedence)
  {
  } // VariableHandler

protected:
  virtual VType* createContainer(const std::string& /* namespaceURI */,
                                 const std::string& /* localName */,
                                 const std::string& qName,
                                 const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "name", true, 0, 0 },
                                       { "select", false, 0, 0 },
                                       { 0, false, 0, 0 } };

    
    std::map<std::string, std::string> attrs = gatherAttributes(qName, atts, rules);

    const std::string& select = atts.getValue("select");
    Arabica::XPath::XPathExpressionPtr<std::string> xpath;
    if(select != "")
    {
      xpath = this->context().xpath_expression(select);
      has_select_ = true;
    } // if ...

    std::string name = this->context().processInternalQName(attrs["name"]).clarkName();
    return new VType(name, xpath, precedence_);
  } // createContainer

  virtual void characters(const std::string& ch)
  {
    if(has_select_)
    {
      for(std::string::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
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
  TopLevelVariableHandler(CompilationContext& context) :
      VariableHandler<VType>(context, context.precedence())
  {
  } // VariableHandler

  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    this->context().stylesheet().add_variable(this->container());
    this->context().pop();
  } // endElement

}; // class TopLevelVariableHandler

} // namespace XSLT
} // namespace Arabica
#endif 

