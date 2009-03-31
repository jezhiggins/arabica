#ifndef ARABICA_XSLT_OUTPUT_HPP
#define ARABICA_XSLT_OUTPUT_HPP

#include <XML/escaper.hpp>
#include <SAX/ext/LexicalHandler.hpp>
#include "xslt_namespace_stack.hpp"
#include "xslt_qname.hpp"
#include "handler/xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

class Output
{
public:
  typedef std::map<std::string, std::string> Settings;

protected:
  Output() :
    buffering_(0),
    pending_element_(false),
    pending_attribute_(-1),
    text_mode_(false),
    warning_sink_(0)
  {
  } // Output
  ~Output() 
  { 
  } // ~Output

public:
  void start_document(const Settings& settings)
  {
    Settings::const_iterator method = settings.find("method");
    text_mode_ = (method != settings.end() && method->second == "text");
    if(text_mode_)
      do_disableOutputEscaping(true);

    do_start_document(settings);
  } // start_document

  void end_document()
  {
    do_end_document();
  } // end_document

  bool start_element(const std::string& qName, const std::string& namespaceURI)
  {
    QName en = QName::create(qName, namespaceURI);
    return start_element(en.prefix, en.localName, en.namespaceURI);
  } // start_element

  bool start_element(const std::string& prefix, const std::string& localName, const std::string& namespaceURI)
  {
    if(is_buffering())
      return false;

    flush_element();

    namespaceStack_.pushScope();
    if(!namespaceURI.empty())
      namespaceStack_.declareNamespace(prefix, namespaceURI);

    std::string mapped_prefix = namespaceStack_.findPrefix(namespaceURI);

    element_stack_.push(QName(mapped_prefix, localName, namespaceURI));

    atts_.clear();
    pending_element_ = true;

    namespaceStack_.pushScope();
    return true;
  } // start_element

  void end_element(const std::string& qName, const std::string& namespaceURI)
  {
    QName en = QName::create(qName, namespaceURI);
    end_element(en.prefix, en.localName, en.namespaceURI);
  } // end_element

  void end_element(const std::string& prefix, const std::string& localName, const std::string& namespaceURI)
  {
    if(pop_if_buffering())
      return;

    flush_element();

    if(!text_mode_)
    {
      std::string mapped_prefix = namespaceStack_.findPrefix(namespaceURI);
      do_end_element((!mapped_prefix.empty()) ? mapped_prefix + ':' + localName : localName, namespaceURI);
      element_stack_.pop();
    } // end_element

    namespaceStack_.popScope();
  } // end_element

  void start_attribute(const std::string& qName, const std::string& namespaceURI)
  {
    QName qn = QName::create(qName, namespaceURI);
    start_attribute(qn.prefix, qn.localName, qn.namespaceURI);
  } // start_attribute

  void start_attribute(const std::string& prefix, const std::string& localName, const std::string& namespaceURI)
  {
    if(push_buffering())
      return;

    if(!pending_element_)
    {
      warning("WARNING: Cannot write attribute, no open element");
      return;
    } // if ...

    if(!namespaceURI.empty())
      namespaceStack_.declareNamespace(prefix, namespaceURI, true);

    std::string mapped_prefix = namespaceStack_.findPrefix(namespaceURI);
    std::string qName = (!mapped_prefix.empty()) ? mapped_prefix + ':' + localName : localName;

    atts_.addOrReplaceAttribute(namespaceURI,
                                localName,
                                qName,
                                "",
                                "");
    pending_attribute_ = atts_.getIndex(qName);
  } // start_attribute

  void end_attribute()
  {
    if(pop_buffering())
      return;
    
    if(pending_attribute_ == -1)
      return;

    atts_.setValue(pending_attribute_, buffer_.str());   

    pending_attribute_ = -1;
  } // end_attribute

  void add_attribute(const std::string& uri,
            		     const std::string& localName,
		                 const std::string& qName,
		                 const std::string& value) 
  {
    if(!pending_element_)
    {  
      warning("WARNING: Cannot write attribute, no open element");
      return;
    } // if ...

    atts_.addAttribute(uri, localName, qName, "", value); 
  } // add_attribute

  void characters(const std::string& ch)
  {
    if(buffering_)
    {
      if(buffering_ == 1)
        buffer_ << ch;
      return;
    } // if ...

    flush_element();

    if(pending_attribute_ != -1)
    {   
      atts_.setValue(pending_attribute_, atts_.getValue(pending_attribute_) + ch);
      return;
    } // if ...

    if(!buffering_)
      do_characters(ch);
  } // characters

  void start_comment()
  {
    if(push_buffering())
      return;

    flush_element();
  } // start_comment
  
  void end_comment()
  {
    if(pop_buffering())
      return;

    if(!text_mode_)
    {
      std::string comment = escape(buffer_.str(), "--", "- -");
      if(comment.length() && *(comment.rbegin()) == '-')
        comment.append(" ");
      do_comment(comment);
    } // if ...
  } // end_comment

  void start_processing_instruction(const std::string& target)
  {
    if(push_buffering())
      return;

    flush_element();

    target_ = target;
  } // start_processing_instruction

  void end_processing_instruction() 
  {
    if(pop_buffering())
      return;

    if(!text_mode_)
    {
      std::string data = escape(buffer_.str(), "?>", "? >");
      do_processing_instruction(target_, data);
    } // if ...
  } // end_processing_instruction

  void disableOutputEscaping(bool disable)
  {
    if(!text_mode_)
      do_disableOutputEscaping(disable);
  } // disableOutputEscaping

  void set_warning_sink(Output& warning_sink)
  {
    warning_sink_ = &warning_sink;
  } // set_warning_sink

protected:
  virtual void do_start_document(const Settings& settings) = 0;
  virtual void do_end_document() = 0;
  virtual void do_start_element(const std::string& qName, const std::string& namespaceURI, const SAX::Attributes<std::string>& atts) = 0;
  virtual void do_end_element(const std::string& qName, const std::string& namespaceURI) = 0;
  virtual void do_characters(const std::string& ch) = 0;
  virtual void do_comment(const std::string& ch) = 0;
  virtual void do_processing_instruction(const std::string& target, const std::string& data) = 0;
  virtual void do_disableOutputEscaping(bool disable) = 0;
  virtual bool want_namespace_declarations() const = 0;

private:
  std::string escape(std::string str, const std::string& t, const std::string& r) const
  {
    std::string::size_type naughty = str.find(t);
    while(naughty != std::string::npos)
    {
      str.replace(naughty, t.length(), r, 0, r.length());
      naughty = str.find(t, naughty);
    } // while
    return str;
  } // escape

  bool push_buffering()
  {
    bool is_buf = is_buffering();
    ++buffering_;

    if(is_buf)
      return true;

    buffer_.str("");
    return false;
  } // push_buffering

  bool is_buffering()
  {
    if(!buffering_)
      return false;
    warning("WARNING: non-text ignored when creating processing instruction, comment or attribute");
    return true;
  } // is_buffering

  bool pop_if_buffering()
  {
    if(!buffering_)
      return false;
    --buffering_;
    return true;
  } // pop_if_buffering

  bool pop_buffering()
  {
    --buffering_;
    return (buffering_ != 0); // oh, Visual Studio how I curse you warning C4800
  } // pop_buffering

  void flush_element()
  {
    if((!pending_element_) || (pending_attribute_ != -1))
      return;

    if(text_mode_)
      return;

    bool want_decs = want_namespace_declarations();
    if(want_decs)
      addNamespaceDeclarations();
    namespaceStack_.popScope();
    if(want_decs)
      addNamespaceDeclarations();

    do_start_element(element_stack_.top().qname, element_stack_.top().namespaceURI, atts_);
    pending_element_ = false;
  } // flush_element

  void addNamespaceDeclarations()
  {
    for(NamespaceStack::Scope::const_iterator n = namespaceStack_.begin(), ne = namespaceStack_.end(); n != ne; ++n)
    {
      if(n->first == "xml")
        continue;

      std::string qName = (n->first.empty()) ? "xmlns" : "xmlns:" + n->first;
      atts_.addAttribute("http://www.w3.org/2000/xmlns",
                         n->first,
                         qName,
                         "",
                         n->second);
    }
  } // addNamespaceDeclarations

  void warning(const std::string& warning_message)
  {
    warning_sink_->characters(warning_message);
    warning_sink_->characters("\n");
  } // warning

  int buffering_;
  bool pending_element_;
  int pending_attribute_;
  std::stack<QName> element_stack_;
  std::string target_;
  SAX::AttributesImpl<std::string, Arabica::default_string_adaptor<std::string> > atts_;
  std::stringstream buffer_;
  bool text_mode_;
  NamespaceStack namespaceStack_;
  Output* warning_sink_;
}; // class Output

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_OUTPUT_HPP

