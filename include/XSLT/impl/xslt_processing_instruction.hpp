#ifndef ARABICA_XSLT_PROCESSING_INSTRUCTION_HPP
#define ARABICA_XSLT_PROCESSING_INSTRUCTION_HPP

#include <XML/strings.hpp>
#include <text/UnicodeCharacters.hpp>
#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

class ProcessingInstruction : public ItemContainer
{
public:
  ProcessingInstruction(const Arabica::XPath::XPathExpressionPtr<std::string>& name) :
    name_(name)
  { 
  } // ProcessingInstruction

  virtual ~ProcessingInstruction() { }

  virtual void execute(const DOM::Node<std::string>& node, ExecutionContext& context) const
  {
    std::string name = name_->evaluateAsString(node, context.xpathContext());
    validate_name(name);

    context.sink().start_processing_instruction(name);
    execute_children(node, context);
    context.sink().end_processing_instruction();
  } // execute

private:
  void validate_name(const std::string& name) const
  {
    if(name.empty())
      throw SAX::SAXException("xsl:processing-instruction : name attribute must evaluate to a valid name");

    if(!Arabica::XML::is_ncname<Arabica::default_string_adaptor<std::string> >(name))
      throw SAX::SAXException("xsl:processing-instruction : '" + name + "' is not valid as the name");

    if(name.length() != 3)
      return;

    typedef Arabica::text::Unicode<char> UnicodeT;

    if((name[0] != UnicodeT::CAPITAL_X) &&
       (name[0] != UnicodeT::LOWERCASE_X))
      return;
    if((name[1] != UnicodeT::CAPITAL_M) &&
       (name[1] != UnicodeT::LOWERCASE_M))
      return;
    if((name[2] != UnicodeT::CAPITAL_L) &&
       (name[2] != UnicodeT::LOWERCASE_L))
      return;
      
    throw SAX::SAXException("xsl:processing-instruction name can not be 'xml'");
  } // validate_name

  Arabica::XPath::XPathExpressionPtr<std::string> name_;
}; // class ProcessingInstruction

} // namespace XSLT
} // namespace Arabica

#endif

