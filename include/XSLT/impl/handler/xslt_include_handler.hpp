
#ifndef ARABICA_XSLT_INCLUDE_HANDLER_HPP
#define ARABICA_XSLT_INCLUDE_HANDLER_HPP

#include <algorithm>
#include "xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class IncludeHandler : public SAX::DefaultHandler<string_type, string_adaptor>
{
  struct ImportHref;

public:
  IncludeHandler() :
    context_(0),
    compiler_(0),
    no_content_(false)
  {
  } // IncludeHandler

  void context(CompilationContext<string_type, string_adaptor>& context, 
               SAX::DefaultHandler<string_type, string_adaptor>* compiler)
  {
    context_ = &context;
    compiler_ = compiler;
  } // context

  void start_include(const string_type& namespaceURI,
                     const string_type& localName,
                     const string_type& qName,
                     const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    context_->parser().setContentHandler(*this);
    startElement(namespaceURI, localName, qName, atts);
  } // start_include

  virtual void startDocument()
  {
    context_->parentHandler().startDocument();
  } // startDocument

  virtual void startElement(const string_type& namespaceURI,
                            const string_type& localName,
                            const string_type& qName,
                            const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    if(no_content_)
      throw SAX::SAXException("xsl:include must be empty");

    if(namespaceURI == StylesheetConstant<string_type, string_adaptor>::NamespaceURI())
    {
      if(localName == "import")
      {
        string_type href = validate_href(qName, atts);
        import_stack_.push_back(href, context_->next_precedence(), current_includes_);
        return;
      } // if(localName == "import")
      if(localName == "include")
      {
        href_.push_back(validate_href(qName, atts));
        return;
      } // if(localName == "include")
    } // if ...

    context_->parentHandler().startElement(namespaceURI,
                                           localName, 
                                           qName,
                                           atts); 
  } // startElement

  virtual void startPrefixMapping(const string_type& prefix, const string_type& uri)
  {
    context_->parentHandler().startPrefixMapping(prefix, uri);
  } // startPrefixMapping


  virtual void endElement(const string_type& namespaceURI,
                          const string_type& localName,
                          const string_type& qName)
  {
    if(no_content_ &&
       (namespaceURI == StylesheetConstant<string_type, string_adaptor>::NamespaceURI()))
    {
      no_content_ = false;
      if(localName == "include")
      {
        include_stylesheet(href_.back(), context_->precedence());
        href_.pop_back();
      } // if ...
      if(href_.empty())
        context_->parser().setContentHandler(*compiler_);
      return;
    } // if ...

    context_->parentHandler().endElement(namespaceURI,
                                         localName, 
                                         qName);
  } // endElement

  virtual void characters(const string_type& ch)
  {
    if(no_content_)
      verifyNoCharacterData<string_type>(ch, "xsl:include/xsl:import");
    context_->parentHandler().characters(ch);
  } // characters

  void unwind_imports()
  {
    while(!import_stack_.empty())
    {      
      import_stylesheet(import_stack_.current());
      import_stack_.pop();
    } // while ...
  } // unwind_imports

private:
  string_type validate_href(const string_type& qName, const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    static const ValueRule rules[] = { { "href", true, 0, 0 },
				       { 0, false, 0, 0 } };
    string_type href = gatherAttributes(qName, atts, rules)["href"];
    no_content_ = true;
    // std::cout << "Base : "  << context_->currentBase() << ", href : " << href << "\n";
    return context_->makeAbsolute(href);
  } // validate_href

  void check_for_loops(const string_type& href)
  {
    if(std::find(current_includes_.begin(), current_includes_.end(), href) != current_includes_.end())
    {
      string_type error = "Stylesheet '" + href + "' includes/imports itself ";
      for(HrefStack::const_iterator i = current_includes_.begin(), ie = current_includes_.end(); i != ie; ++i)
        error += "\n  " + *i;
      throw std::runtime_error(error);
    } // if ...
  } // check_for_loops

  void import_stylesheet(const ImportHref& import)
  {
    current_includes_ = import.includes;
    include_stylesheet(import.href, import.precedence);
  } // import_stylesheet

  void include_stylesheet(const string_type& href, const Precedence& precedence)
  {
    check_for_loops(href);
    current_includes_.push_back(href);

    string_type prev = context_->setBase(href);
    context_->set_precedence(precedence);

    SAX::InputSource<string_type, string_adaptor> source(href);
    SAX::XMLReader<string_type, string_adaptor> include_parser;
    SAX::CatchErrorHandler<string_type, string_adaptor> errorHandler;
 
    include_parser.setContentHandler(*this);
    include_parser.setErrorHandler(errorHandler);
    
    include_parser.parse(source);

    context_->setBase(prev);

    if(errorHandler.errorsReported())
      throw std::runtime_error("Could not import/include stylesheet '" + href + "' - " + errorHandler.errors());

    current_includes_.pop_back();
  } // include_stylesheet

  CompilationContext<string_type, string_adaptor>* context_;
  SAX::DefaultHandler<string_type, string_adaptor>* compiler_;
  bool no_content_;

  typedef std::vector<string_type> HrefStack;

  struct ImportHref
  {
    string_type href;
    Precedence precedence;
    HrefStack includes;
    
    ImportHref() { }
    
    ImportHref(const string_type& h, const Precedence& p, const HrefStack& i) :
      href(h),
      precedence(p),
      includes(i)
    {
    } // ImportHref
    
    ImportHref& operator=(const ImportHref& rhs)
    {
      href = rhs.href;
      precedence = rhs.precedence;
      includes = rhs.includes;
      return *this;
    } // operator=
  }; // string ImportHref

  class ImportStack
  {
  public:
    ImportStack() { }

    void push_back(const string_type& href, const Precedence& precedence, const HrefStack& includes)
    {
      stack_.push_back(ImportHref(href, precedence, includes));
    } // push_back

    bool empty() const { return stack_.empty(); }

    const ImportHref& current() const 
    {
      most_recent_ = stack_.size() - 1;
      return stack_[most_recent_];
    } // current

    void pop()
    {
      stack_.erase(stack_.begin() + most_recent_);
    } // pop

  private:
    std::vector<ImportHref> stack_;
    mutable size_t most_recent_;
  }; // class ImportStack

  ImportStack import_stack_;
  HrefStack current_includes_;

  HrefStack href_;
}; // class IncludeHandler

} // namespace XSLT
} // namespace Arabica

#endif

