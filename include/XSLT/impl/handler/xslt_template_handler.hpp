#ifndef ARABICA_XSLT_TEMPLATE_HANDLER_HPP
#define ARABICA_XSLT_TEMPLATE_HANDLER_HPP

#include "../xslt_template.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class TemplateHandler : public ItemContainerHandler<Template>
{
public:
  TemplateHandler(CompilationContext& context) :
    ItemContainerHandler<Template>(context),
    done_params_(false)
  {
  } // TemplateHandler

  virtual void characters(const std::string& ch)
  {
    if(!done_params_)
    {
     for(std::string::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
      if(!Arabica::XML::is_space(*i))
      {
        done_params_ = true;
        break;
      } // if ...
    } // if(!done_params_)

    ItemContainerHandler<Template>::characters(ch);
  } // characters

protected:
  virtual Template* createContainer(const std::string& /* namespaceURI */,
                                    const std::string& /* localName */,
                                    const std::string& qName,
                                    const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "match", false, 0, 0 },
                                       { "mode", false, 0, 0 },
                                       { "name", false, 0, 0 }, 
                                       { "priority", false, 0, 0 },
				       { 0, false, 0, 0 } };
    std::map<std::string, std::string> attributes = gatherAttributes(qName, atts, rules);
                                       
    const std::string& match = attributes["match"];
    if((match == "") && (attributes["name"] == ""))
      throw SAX::SAXException("xsl:template must have a match and/or a name attribute");

    int index = atts.getIndex("mode");
    if(index != -1)
    {
      const std::string& mode = attributes["mode"];
      if(mode == "")
        throw SAX::SAXException("xsl:template mode cannot be empty");
      if(match == "")
        throw SAX::SAXException("xsl:template may not have a mode without a match");
    } // ...

    const std::string& priority = attributes["priority"];
    if((atts.getIndex("priority") != -1) && (priority == ""))
      throw SAX::SAXException("xsl:template priority cannot be empty");

    std::string name;
    if(attributes["name"] != "")
      name = context().processInternalQName(attributes["name"]).clarkName();

    std::string mode;
    if(attributes["mode"] != "")
      mode = context().processInternalQName(attributes["mode"]).clarkName();

    if(match == "")
      return new Template(name,
			  mode,
			  priority,
        context().precedence());

    return new Template(context().xpath_match(match),
			name,
			mode,
			priority,
      context().precedence());
  } // createContainer

  virtual bool createChild(const std::string& namespaceURI,
                           const std::string& localName,
                           const std::string& qName,
                           const SAX::Attributes<std::string>& atts)
  {
    if((namespaceURI == StylesheetConstant::NamespaceURI()) &&
       (localName == "param"))
    {
      if(!done_params_)
      {
        context().push(container(),
                       new VariableHandler<Param>(context()),
                       namespaceURI, 
                       localName, 
                       qName, 
                       atts);
        return true;
      }
      else
        throw SAX::SAXException("xsl:param must immediately follow xsl:template");
    }

    done_params_ = true;
    return ItemContainerHandler<Template>::createChild(namespaceURI, localName, qName, atts);
  } // createChild

public:
  virtual void endElement(const std::string& /* namespaceURI */,
                          const std::string& /* localName */,
                          const std::string& /* qName */)
  {
    context().stylesheet().add_template(container());
    context().pop();
  } // endElement

private:
  bool done_params_;
}; // class TemplateHandler

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_TEMPLATE_HANDLER_HPP

