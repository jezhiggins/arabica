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
  typedef StylesheetConstant<string_type, string_adaptor> SC;
public:
  TemplateHandler(CompilationContext<string_type, string_adaptor>& context) :
    baseT(context),
    done_params_(false)
  {
  } // TemplateHandler

  virtual void characters(const string_type& ch)
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
    static const ValueRule<string_type> rules[] = { { SC::match, false, 0, 0 },
                                                    { SC::mode, false, 0, 0 },
                                                    { SC::name, false, 0, 0 }, 
                                                    { SC::priority, false, 0, 0 },
				                                            { string_adaptor::empty_string(), false, 0, 0 } };
    std::map<string_type, string_type> attributes = gatherAttributes(qName, atts, rules);
                                       
    const string_type& match = attributes[SC::match];
    if((match == string_adaptor::empty_string()) && (attributes[SC::name] == string_adaptor::empty_string()))
      throw SAX::SAXException("xsl:template must have a match and/or a name attribute");

    int index = atts.getIndex(SC::mode);
    if(index != -1)
    {
      const string_type& mode = attributes[SC::mode];
      if(mode == string_adaptor::empty_string())
        throw SAX::SAXException("xsl:template mode cannot be empty");
      if(match == string_adaptor::empty_string())
        throw SAX::SAXException("xsl:template may not have a mode without a match");
    } // ...

    const string_type& priority = attributes[SC::priority];
    if((atts.getIndex(SC::priority) != -1) && (priority == string_adaptor::empty_string()))
      throw SAX::SAXException("xsl:template priority cannot be empty");

    string_type name;
    if(attributes[SC::name] != string_adaptor::empty_string())
      name = baseT::context().processInternalQName(attributes[SC::name]).clarkName();

    string_type mode;
    if(attributes[SC::mode] != string_adaptor::empty_string())
      mode = baseT::context().processInternalQName(attributes[SC::mode]).clarkName();

    if(match == string_adaptor::empty_string())
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
    if((namespaceURI == SC::NamespaceURI) &&
       (localName == SC::param))
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

