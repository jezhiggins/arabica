#ifndef ARABICA_XSLT_KEY_HANDLER_HPP
#define ARABICA_XSLT_KEY_HANDLER_HPP

#include "../xslt_key.hpp"
#include <XML/XMLCharacterClasses.hpp>

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class KeyHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
  typedef AttributeValidators<string_type, string_adaptor> AV;
  typedef typename Key<string_type, string_adaptor>::MatchExprList MatchExprList;
public:
  KeyHandler(CompilationContext<string_type, string_adaptor>& context) :
    context_(context),
    key_(0)
  {
  } // KeyHandler

  virtual void startElement(const string_type& /* namespaceURI */,
			    const string_type& /* localName */,
			    const string_type& qName,
			    const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(key_ != 0)
      throw SAX::SAXException(string_adaptor::asStdString(qName) + " can not contain elements");

    static const AV rules = AV::rule(SC::name, true)
                               .rule(SC::match, true)
                               .rule(SC::use, true);

    std::map<string_type, string_type> attrs = rules.gather(qName, atts);
    name_ = context_.processInternalQName(attrs[SC::name]).clarkName();
    try 
    {
      MatchExprList matches = context_.xpath_match_no_variables(attrs[SC::match]);
      Arabica::XPath::XPathExpression<string_type, string_adaptor> use = context_.xpath_expression_no_variables(attrs[SC::use]);

      key_ = new Key<string_type, string_adaptor>(matches, use);
    } // try
    catch(const Arabica::XPath::UnboundVariableException&)
    {
      throw SAX::SAXException("Variable references are not allowed in xsl:key match and use expressions");
    } // catch
  } // startElement

  virtual void endElement(const string_type& /* namespaceURI */,
		                      const string_type& /* localName */,
		                      const string_type& /* qName */)
  {
    context_.stylesheet().add_key(name_, key_);
    context_.pop();
  } // endElement

  virtual void characters(const string_type& ch)
  {
    verifyNoCharacterData<string_type, string_adaptor>(ch, SC::key);
  } // characters

private:
  CompilationContext<string_type, string_adaptor>& context_;
  string_type name_;
  Key<string_type, string_adaptor>* key_;
}; // class KeyHandler

} // namespace XSLT
} // namespace Arabica

#endif
