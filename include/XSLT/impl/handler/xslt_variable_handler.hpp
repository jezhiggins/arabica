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
      ItemContainerHandler<VType>(context)
  {
  } // VariableHandler

protected:
  virtual VType* createContainer(const std::string& namespaceURI,
                                 const std::string& localName,
                                 const std::string& qName,
                                 const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "name", true, 0 },
                                       { "select", false, 0 },
                                       { 0, false, 0} };

    
    std::map<std::string, std::string> attrs = gatherAttributes(qName, atts, rules);

    const std::string& select = atts.getValue("select");
    Arabica::XPath::XPathExpressionPtr<std::string> xpath;
    if(select != "")
      xpath = this->context().xpath_expression(select);

    std::pair<std::string, std::string> name = this->context().processQName(attrs["name"]);
    return new VType(name.first, name.second, xpath);
  } // createContainer
}; // class VariableHandler

template<class VType>
class TopLevelVariableHandler : public VariableHandler<VType>
{
public:
  TopLevelVariableHandler(CompilationContext& context) :
      VariableHandler<VType>(context)
  {
  } // VariableHandler

  virtual void endElement(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName)
  {
    this->context().stylesheet().add_item(this->container());
    this->context().pop();
  } // endElement

}; // class TopLevelVariableHandler

} // namespace XSLT
} // namespace Arabica
#endif 

