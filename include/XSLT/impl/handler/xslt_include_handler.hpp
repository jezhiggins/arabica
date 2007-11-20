#ifndef ARABICA_XSLT_INCLUDE_HANDLER_HPP
#define ARABICA_XSLT_INCLUDE_HANDLER_HPP

#include <algorithm>
#include "xslt_constants.hpp"
#include "xslt_value_validation.hpp"

namespace Arabica
{
namespace XSLT
{

class IncludeHandler : public SAX::DefaultHandler<std::string>
{
public:
  IncludeHandler() :
    context_(0),
    compiler_(0),
    pass_through_(0),
    no_content_(false),
    including_(false)
  {
  } // IncludeHandler

  bool active() const { return including_; }

  void context(CompilationContext& context, SAX::DefaultHandler<std::string>* compiler)
  {
    context_ = &context;
    compiler_ = compiler;
  } // context

  void start_include(const std::string& namespaceURI,
                     const std::string& localName,
                     const std::string& qName,
                     const SAX::Attributes<std::string>& atts)
  {
    context_->parser().setContentHandler(*this);
    startElement(namespaceURI, localName, qName, atts);
  } // start_include

  virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(no_content_)
      throw SAX::SAXException("xsl:include must be empty");

    bool start_pass_through = false;
    if(namespaceURI == StylesheetConstant::NamespaceURI())
    {
      if((localName == "template") || 
         (localName == "param") ||
         (localName == "variable") ||
         (localName == "stylesheet") ||
         (localName == "transform"))
        start_pass_through = true;
      if(localName == "import")
      {
        std::string href = validate_href(qName, atts);
        check_for_loops(import_stack_, href);
        import_stack_.push_back(href);
        return;
      } // if(localName == "import")
      if(localName == "include")
      {
        href_.push_back(validate_href(qName, atts));
        return;
      } // if(localName == "include")
    } // if ...

    if(pass_through_ || start_pass_through)
    {
      context_->parentHandler().startElement(namespaceURI,
                                             localName, 
                                             qName,
                                             atts); 
      ++pass_through_;
    }  
  } // startElement

  virtual void startPrefixMapping(const std::string& prefix, const std::string& uri)
  {
    context_->parentHandler().startPrefixMapping(prefix, uri);
  } // startPrefixMapping


  virtual void endElement(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName)
  {
    if(no_content_ &&
       (namespaceURI == StylesheetConstant::NamespaceURI()))
    {
      no_content_ = false;
      if(localName == "include")
      {
        include_stylesheet(href_.back());
        href_.pop_back();
      } // if ...
      if(href_.empty())
        context_->parser().setContentHandler(*compiler_);
      return;
    } // if ...

    if(pass_through_)
    {
      context_->parentHandler().endElement(namespaceURI,
                                           localName, 
                                           qName);
      --pass_through_;
    } // if ...
  } // endElement

  virtual void characters(const std::string& ch)
  {
    if(no_content_)
      throw SAX::SAXException("xsl:include/xsl:import must be empty");
    context_->parentHandler().characters(ch);
  } // characters

  void unwind_imports()
  {
    while(!import_stack_.empty())
    {      
      std::vector<std::string>::iterator import = import_stack_.end()-1;
      size_t index = import_stack_.size() - 1;
      context_->stylesheet().push_import_precedence();
      include_stylesheet(import_stack_.back());
      import_stack_.erase(import_stack_.begin() + index);
    } // while ...
  } // unwind_imports

private:
  std::string validate_href(const std::string& qName, const SAX::Attributes<std::string>& atts)
  {
    static const ValueRule rules[] = { { "href", true, 0 },
                                        { 0, false, 0 } };
    std::string href = gatherAttributes(qName, atts, rules)["href"];
    no_content_ = true;
    return context_->makeAbsolute(href);
  } // validate_href

  void check_for_loops(const std::vector<std::string>& stack, const std::string& href)
  {
    if(std::find(stack.begin(), stack.end(), href) != stack.end())
    {
      std::string error = "Stylesheet '" + href + "' includes/imports itself ";
      for(std::vector<std::string>::const_iterator i = stack.begin(), ie = stack.end(); i != ie; ++i)
        error += "\n  " + *i;
      throw std::runtime_error(error);
    } // if ...
  } // check_for_loops

  void include_stylesheet(const std::string& href)
  {
    check_for_loops(current_includes_, href);
    current_includes_.push_back(href);

    std::string prev = context_->setBase(href);

    SAX::InputSource<std::string> source(href);
    SAX::XMLReader<std::string> include_parser;
    SAX::CatchErrorHandler<std::string> errorHandler;
 
    include_parser.setContentHandler(*this);
    include_parser.setErrorHandler(errorHandler);
    
    including_ = true;
    include_parser.parse(source);
    including_ = false;

    context_->setBase(prev);

    if(errorHandler.errorsReported())
      throw std::runtime_error("Could not import/include stylesheet '" + href + "' - " + errorHandler.errors());

    current_includes_.pop_back();
  } // include_stylesheet

  SAX::DefaultHandler<std::string>* compiler_;
  CompilationContext* context_;
  unsigned int pass_through_;
  bool no_content_;
  bool including_;
  std::vector<std::string> import_stack_;
  std::vector<std::string> current_includes_;

  std::vector<std::string> href_;
}; // class IncludeHandler

} // namespace XSLT
} // namespace Arabica

#endif

