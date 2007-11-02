#ifndef ARABICA_XSLT_SINK_HPP
#define ARABICA_XSLT_SINK_HPP

#include <ostream>
#include <sstream>
#include <XML/escaper.hpp>
#include <SAX/ContentHandler.hpp>
#include <SAX/ext/LexicalHandler.hpp>
#include <SAX/helpers/AttributesImpl.hpp>
#include "xslt_namespace_stack.hpp"
#include "xslt_qname.hpp"

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
    text_mode_(false)
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
    QName qn = QName::createQName(qName, namespaceURI);
    return start_element(qn.prefix, qn.localName, qn.namespaceURI);
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
    name_ = (!mapped_prefix.empty()) ? mapped_prefix + ':' + localName : localName;
    namespaceURI_ = namespaceURI;

    atts_.clear();
    pending_element_ = true;

    namespaceStack_.pushScope();
    return true;
  } // start_element

  void end_element(const std::string& qName, const std::string& namespaceURI)
  {
    QName qn = QName::createQName(qName, namespaceURI);
    end_element(qn.prefix, qn.localName, qn.namespaceURI);
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
    } // end_element

    namespaceStack_.popScope();
  } // end_element

  void start_attribute(const std::string& qName, const std::string& namespaceURI)
  {
    QName qn = QName::createQName(qName, namespaceURI);
    start_attribute(qn.prefix, qn.localName, qn.namespaceURI);
  } // start_attribute

  void start_attribute(const std::string& prefix, const std::string& localName, const std::string& namespaceURI)
  {
    if(push_buffering())
      return;

    if(!pending_element_)
    {
      std::cerr << "ERROR: Cannot write attribute, no open element" << std::endl;
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
      std::cerr << "ERROR: Cannot write attribute, no open element" << std::endl;
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
      if(*(comment.rbegin()) == '-')
        comment.append(" ");
      do_comment(comment);
    } // if ...
  } // end_comment

  void start_processing_instruction(const std::string& target)
  {
    if(push_buffering())
      return;

    flush_element();

    name_ = target;
  } // start_processing_instruction

  void end_processing_instruction() 
  {
    if(pop_buffering())
      return;

    if(!text_mode_)
    {
      std::string data = escape(buffer_.str(), "?>", "? >");
      do_processing_instruction(name_, data);
    } // if ...
  } // end_processing_instruction

  void disableOutputEscaping(bool disable)
  {
    if(!text_mode_)
      do_disableOutputEscaping(disable);
  } // disableOutputEscaping

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
    std::cerr << "ERROR: non-text ignored when creating processing instruction, comment or attribute" << std::endl;
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
    return buffering_;
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

    do_start_element(name_, namespaceURI_, atts_);

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

  int buffering_;
  bool pending_element_;
  int pending_attribute_;
  std::string name_;
  std::string namespaceURI_;
  SAX::AttributesImpl<std::string, Arabica::default_string_adaptor<std::string> > atts_;
  std::stringstream buffer_;
  bool text_mode_;
  NamespaceStack namespaceStack_;
}; // class Output

class Sink
{
public:
  virtual ~Sink() { }

  virtual Output& asOutput() = 0;
}; // class Sink

class SinkHolder
{
public:
  SinkHolder(Sink* sink) :
    sink_(sink),
    owned_(true) 
  {
  } // SinkHolder

  SinkHolder(Sink& sink) :
    sink_(&sink),
    owned_(false)
  {
  } // SinkHolder

  ~SinkHolder()
  {
    clear();
  } // ~SinkHolder

  void reset(Sink* sink) 
  { 
    clear();
    sink_ = sink;
    owned_ = true;
  } // assign

  void reset(Sink& sink)
  {
    clear();
    sink_ = &sink;
    owned_ = false;
  } // reset

  Sink& get() const
  {
    return *sink_;
  } // get

private:
  void clear()
  {
    if(owned_)
      delete sink_;
  } // clear
  
  Sink* sink_;
  bool owned_;

  SinkHolder(const SinkHolder&);
  bool operator==(const SinkHolder&) const;
  SinkHolder& operator=(const SinkHolder&);
}; // class SinkHolder

class StreamSink : public Sink, private Output
{
public:
  StreamSink(std::ostream& stream) :
    stream_(stream),
    disable_output_escaping_(false),
    seen_root_(true),
    out_again_(false),
    indent_(-1),
    empty_(false)
  { 
  } // StreamSink

  StreamSink(const StreamSink& rhs) :
    stream_(rhs.stream_),
    disable_output_escaping_(rhs.disable_output_escaping_),
    seen_root_(rhs.seen_root_),
    settings_(rhs.settings_),
    indent_(rhs.indent_),
    empty_(false),
    out_again_(rhs.out_again_)
  {
  } // StreamSink

  ~StreamSink() 
  { 
    stream_.flush();
  } // ~StreamSink

  virtual Output& asOutput() { return *this; }

protected:
  void do_start_document(const Settings& settings)
  {
    seen_root_ = false;
    settings_ = settings;
    if(setting("indent") == "yes")
      indent_ = 0;
  } // do_start_document

  void do_end_document()
  {
  } // do_end_document

  void do_start_element(const std::string& qName, 
                        const std::string& namespaceURI,
                        const SAX::Attributes<std::string>& atts)
  {
    if(!seen_root_)
      do_decl(qName);

    if(empty_)
      stream_ << ">";

    indent();
    stream_ << '<' << qName;
    for(int a = 0; a < atts.getLength(); ++a)
    {
      stream_ << ' ' << atts.getQName(a) << '=' << '\"';
      std::string ch = atts.getValue(a);
      std::for_each(ch.begin(), ch.end(), Arabica::XML::attribute_escaper<char>(stream_));
      stream_ << '\"';
    }
    empty_ = true;
  } // do_start_element

  void do_end_element(const std::string& qName, const std::string& namespaceURI)
  { 
    if(!seen_root_)
      do_decl("");

    preoutdent(empty_);

    if(empty_)
      stream_ << "/>";
    else
      stream_ << "</" << qName << ">";

    outdent(empty_);

    empty_ = false;
  } // do_end_element

  void do_characters(const std::string& ch)
  { 
    close_element_if_empty();

    if(!disable_output_escaping_)
      std::for_each(ch.begin(), ch.end(), Arabica::XML::text_escaper<char>(stream_));
    else
      stream_ << ch;
  } // characters

  void do_comment(const std::string& ch)
  {
    close_element_if_empty();

    stream_ << "<!--"
	    << ch
	    << "-->";
  } // do_comment

  void do_processing_instruction(const std::string& target,
				 const std::string& data)
  {
    close_element_if_empty();

    stream_ << "<?" 
	    << target
	    << " "
	    << data
	    << "?>";
  } // do_processing_instruction

  void do_disableOutputEscaping(bool disable) { disable_output_escaping_ = disable; }

  bool want_namespace_declarations() const { return true; }


private:
  void close_element_if_empty()
  {
    if(empty_)
    {
      stream_ << '>';
      empty_ = false;
    }

    if(!seen_root_)
      do_decl("");
  } // close_element_if_empty

  void indent()
  {
    if(indent_ == -1)
      return;

    if(indent_ != 0)
      stream_ << "\n";

    for(int i = 0; i != indent_; ++i)
      stream_ << " "; 

    indent_ += 2;

    out_again_ = false;
  } // indent

  void preoutdent(bool empty)
  {
    if(out_again_ && !empty)
      stream_ << "\n";
  } // preoutdent

  void outdent(bool empty)
  {
    if(indent_ == -1)
      return;

    if(out_again_ && empty)
      stream_ << "\n";

    indent_ -= 2;
    out_again_ = true;
  } // outdent
 
  void do_decl(const std::string& qName)
  {
    if((setting("method") == "text") || (setting("omit-xml-declaration") == "yes"))
      return;

    {
      std::string version = setting("version");
      if(version.empty())
        version = "1.0";
      stream_ << "<?xml version=\"" << version << "\""; 
    }
    {
      std::string s = setting("standalone");
      if(!s.empty())
        stream_ << " standalone=\"" << s << "\"";
    }
    stream_ << "?>\n";

    if(!qName.empty())
    {
      std::string pub = setting("doctype-public");
      std::string sys = setting("doctype-system");

      if(!sys.empty())
      {
        stream_ << "<!DOCTYPE " << qName << "\n";
        if(!pub.empty())
          stream_ << "  PUBLIC \"" << pub << "\" \"" << sys << "\">\n";
	else
          stream_ << "  SYSTEM \"" << sys << "\">\n";
      } // if(!sys.empty())
    }
    seen_root_ = true;
  } // do_decl 

  std::string setting(const std::string& name)
  {
    Settings::const_iterator i = settings_.find(name);
    if(i == settings_.end())
      return "";
    return i->second;
  } // setting

  std::ostream& stream_;
  bool disable_output_escaping_;
  bool empty_;
  bool seen_root_;
  Settings settings_;
  int indent_;
  bool out_again_;

  bool operator==(const StreamSink&) const;
  StreamSink& operator=(const StreamSink&);
}; // class StreamSink

class DOMSink : public Sink, private Output
{
public:
  DOMSink() :
    indent_(-1),
    out_again_(false)
  {
  } // DOMSink

  ~DOMSink() 
  {
  } // ~DOMSink

  virtual Output& asOutput() { return *this; }
  DOM::Node<std::string> node() const { return documentFrag_; }

protected:
  void do_start_document(const Settings& settings)
  {
    Settings::const_iterator i = settings.find("indent");
    if((i != settings.end()) &&
       (i->second == "yes"))
      indent_ = 0;
  } // do_start_document

  void do_end_document()
  {
  } // do_end_document

  void do_characters(const std::string& ch)
  {
    DOM::Node<std::string> lc = current().getLastChild();
    if(lc == 0 || lc.getNodeType() != DOM::Node_base::TEXT_NODE)
      current().appendChild(document().createTextNode(ch));
    else
      lc.setNodeValue(lc.getNodeValue() + ch);
  } // do_characters

  void do_comment(const std::string& ch)
  {
    current().appendChild(document().createComment(ch));
  } // do_comment

  void do_processing_instruction(const std::string& target,
                                 const std::string& data)
  {
    current().appendChild(document().createProcessingInstruction(target, data));
  } // do_processing_instruction

  void do_disableOutputEscaping(bool disable) { }

  bool want_namespace_declarations() const { return false; }


  void do_start_element(const std::string& qName,
                        const std::string& namespaceURI,
                        const SAX::Attributes<std::string>& atts)
  {
    indent();
    DOM::Element<std::string> elem = document().createElementNS(namespaceURI, qName);
    current().appendChild(elem);

    // attributes here
    for(int i = 0; i < atts.getLength(); ++i)
      elem.setAttributeNS(atts.getURI(i), atts.getQName(i), atts.getValue(i));

    current_ = elem;
  } // do_start_element

  void do_end_element(const std::string& qName, 
                      const std::string& namespaceURI)
  {
    outdent();
    current_ = current_.getParentNode();
  } // do_end_element

private:
  DOM::Document<std::string>& document()
  {
    if(document_ != 0)
      return document_;

    DOM::DOMImplementation<std::string> di = SimpleDOM::DOMImplementation<std::string>::getDOMImplementation();
    document_ = di.createDocument("", "", 0);
    return document_;
  } // document

  DOM::Node<std::string>& current()
  {
    if(current_ != 0)
      return current_;

    documentFrag_ = document().createDocumentFragment();
    current_ = documentFrag_;
    return current_;
  } // current

  void indent()
  {
    if(indent_ == -1)
      return;

    std::string sps;
    if(indent_ != 0)
    {
      sps += '\n';
      std::fill_n(std::back_inserter<std::string>(sps), indent_, ' ');
      do_characters(sps);
    } // if ...

    indent_ += 2;
      
    out_again_ = false;
  } // indent

  void outdent()
  {
    if(indent_ == -1)
      return;

    if(out_again_)
      do_characters("\n");

    indent_ -= 2;
    out_again_ = true;
  } // outdent

  DOM::Document<std::string> document_;
  DOM::DocumentFragment<std::string> documentFrag_;
  DOM::Node<std::string> current_;

  int indent_;
  bool out_again_;
}; // DOMSink

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_SINK_HPP

