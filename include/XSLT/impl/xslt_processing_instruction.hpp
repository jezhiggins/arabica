#ifndef ARABICA_XSLT_PROCESSING_INSTRUCTION_HPP
#define ARABICA_XSLT_PROCESSING_INSTRUCTION_HPP

#include <XML/strings.hpp>
#include <text/UnicodeCharacters.hpp>
#include "xslt_item.hpp"

namespace Arabica
{
namespace XSLT
{

template<class stringT, class adaptorT>
class ProcessingInstruction : public ItemContainer<stringT, adaptorT>
{
public:
  typedef stringT string_type;
  typedef adaptorT string_adaptor;

  ProcessingInstruction(const Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor>& name) :
    name_(name)
  { 
  } // ProcessingInstruction

  virtual ~ProcessingInstruction() { }

  virtual void execute(const DOM::Node<string_type, string_adaptor>& node, ExecutionContext<string_type, string_adaptor>& context) const
  {
    string_type name = name_->evaluateAsString(node, context.xpathContext());
    validate_name(name);

    context.sink().start_processing_instruction(name);
    execute_children(node, context);
    context.sink().end_processing_instruction();
  } // execute

private:
  void validate_name(const string_type& name) const
  {
    if(string_adaptor::empty(name))
      throw SAX::SAXException("xsl:processing-instruction : name attribute must evaluate to a valid name");

    if(!Arabica::XML::is_ncname<string_adaptor>(name))
      throw SAX::SAXException("xsl:processing-instruction : '" + string_adaptor::asStdString(name) + "' is not valid as the name");

    if(string_adaptor::length(name) != 3)
      return;

    typedef Arabica::text::Unicode<char> UnicodeT;

    typename string_adaptor::const_iterator i = string_adaptor::begin(name);

    if((*i != UnicodeT::CAPITAL_X) &&
       (*i != UnicodeT::LOWERCASE_X))
      return;
    ++i;
    if((*i != UnicodeT::CAPITAL_M) &&
       (*i != UnicodeT::LOWERCASE_M))
      return;
    ++i;
    if((*i != UnicodeT::CAPITAL_L) &&
       (*i != UnicodeT::LOWERCASE_L))
      return;
      
    throw SAX::SAXException("xsl:processing-instruction name can not be 'xml'");
  } // validate_name

  Arabica::XPath::XPathExpressionPtr<string_type, string_adaptor> name_;
}; // class ProcessingInstruction

} // namespace XSLT
} // namespace Arabica

#endif

