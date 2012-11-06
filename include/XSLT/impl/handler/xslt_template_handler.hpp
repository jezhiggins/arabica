#ifndef ARABICA_XSLT_TEMPLATE_HANDLER_HPP
#define ARABICA_XSLT_TEMPLATE_HANDLER_HPP

#include "../xslt_template.hpp"
#include "xslt_item_container_handler.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class TemplateHandler : public ItemContainerHandler<Template<string_type, string_adaptor> >
{
  typedef ItemContainerHandler<Template<string_type, string_adaptor> > baseT;
public:
  TemplateHandler(CompilationContext<string_type, string_adaptor>& context) :
    baseT(context),
    done_params_(false)
  {
  } // TemplateHandler

  virtual void characters(const std::string& ch)
  {
    if(!done_params_)
    {
     for(typename string_type::const_iterator i = ch.begin(), e = ch.end(); i != e; ++i)
      if(!Arabica::XML::is_space(*i))
      {
        done_params_ = true;
        break;
      } // if ...
    } // if(!done_params_)

    baseT::characters(ch);
  } // characters

protected:
  virtual Template<string_type, string_adaptor>* createContainer(const string_type& /* namespaceURI */,
                                    const string_type& /* localName */,
                                    const string_type& qName,
                                    const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const ValueRule rules[] = { { "match", false, 0, 0 },
                                       { "mode", false, 0, 0 },
                                       { "name", false, 0, 0 }, 
                                       { "priority", false, 0, 0 },
				       { 0, false, 0, 0 } };
    std::map<string_type, string_type> attributes = gatherAttributes(qName, atts, rules);
                                       
    const string_type& match = attributes["match"];
    if((match == "") && (attributes["name"] == ""))
      throw SAX::SAXException("xsl:template must have a match and/or a name attribute");

    int index = atts.getIndex("mode");
    if(index != -1)
    {
      const string_type& mode = attributes["mode"];
      if(mode == "")
        throw SAX::SAXException("xsl:template mode cannot be empty");
      if(match == "")
        throw SAX::SAXException("xsl:template may not have a mode without a match");
    } // ...

    const string_type& priority = attributes["priority"];
    if((atts.getIndex("priority") != -1) && (priority == ""))
      throw SAX::SAXException("xsl:template priority cannot be empty");

    string_type name;
    if(attributes["name"] != "")
      name = baseT::context().processInternalQName(attributes["name"]).clarkName();

    string_type mode;
    if(attributes["mode"] != "")
      mode = baseT::context().processInternalQName(attributes["mode"]).clarkName();

    if(match == "")
      return new Template<string_type, string_adaptor>(name,
			  mode,
			  priority,
        baseT::context().precedence());

    return new Template<string_type, string_adaptor>(baseT::context().xpath_match(match),
			name,
			mode,
			priority,
      baseT::context().precedence());
  } // createContainer

  virtual bool createChild(const string_type& namespaceURI,
                           const string_type& localName,
                           const string_type& qName,
                           const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if((namespaceURI == StylesheetConstant::NamespaceURI()) &&
       (localName == "param"))
    {
      if(!done_params_)
      {
        baseT::context().push(baseT::container(),
                       new VariableHandler<Param<string_type, string_adaptor> >(baseT::context()),
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
    return baseT::createChild(namespaceURI, localName, qName, atts);
  } // createChild

public:
  virtual void endElement(const string_type& /* namespaceURI */,
                          const string_type& /* localName */,
                          const string_type& /* qName */)
  {
    baseT::context().stylesheet().add_template(baseT::container());
    baseT::context().pop();
  } // endElement

private:
  bool done_params_;
}; // class TemplateHandler

} // namespace XSLT
} // namespace Arabica
#endif // ARABICA_XSLT_TEMPLATE_HANDLER_HPP

