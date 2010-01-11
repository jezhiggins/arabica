#ifndef ARABICA_XSLT_SINK_HPP
#define ARABICA_XSLT_SINK_HPP

#include <ostream>
#include <sstream>
#include <XML/escaper.hpp>
#include <SAX/ContentHandler.hpp>
#include <SAX/ext/LexicalHandler.hpp>
#include <SAX/helpers/AttributesImpl.hpp>
#include "xslt_output.hpp"
#include "handler/xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

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
    in_cdata_(false),
    empty_(false),
    seen_root_(true),
    indent_(-1),
    out_again_(false)
  { 
  } // StreamSink

  StreamSink(const StreamSink& rhs) :
    stream_(rhs.stream_),
    disable_output_escaping_(rhs.disable_output_escaping_),
    in_cdata_(rhs.in_cdata_),
    empty_(false),
    seen_root_(rhs.seen_root_),
    indent_(rhs.indent_),
    out_again_(rhs.out_again_),
    settings_(rhs.settings_)
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
                        const std::string& /* namespaceURI */,
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

  void do_end_element(const std::string& qName, 
		      const std::string& /* namespaceURI */)
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

    if(!disable_output_escaping_ && !in_cdata_)
      std::for_each(ch.begin(), ch.end(), Arabica::XML::text_escaper<char>(stream_));
    else
      stream_ << ch;
  } // characters

  void do_start_CDATA()
  {
    close_element_if_empty();

    in_cdata_ = true;
    stream_ << "<![CDATA[";
  } // do_start_CDATA

  void do_end_CDATA()
  {
    in_cdata_ = false;
    stream_ << "]]>";
  } // do_end_CDATA

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
  bool in_cdata_;
  bool empty_;
  bool seen_root_;
  int indent_;
  bool out_again_;
  Settings settings_;

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

  void do_start_CDATA()
  {
  } // do_start_CDATA

  void do_end_CDATA()
  {
    DOM::Node<std::string> lc = current().getLastChild();
    if(lc.getNodeType() == DOM::Node_base::TEXT_NODE)
      current().replaceChild(document().createCDATASection(lc.getNodeValue()), lc);
  } // do_end_CDATA

  void do_comment(const std::string& ch)
  {
    current().appendChild(document().createComment(ch));
  } // do_comment

  void do_processing_instruction(const std::string& target,
                                 const std::string& data)
  {
    current().appendChild(document().createProcessingInstruction(target, data));
  } // do_processing_instruction

  void do_disableOutputEscaping(bool /* disable */) { }

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

  void do_end_element(const std::string& /* qName */, 
                      const std::string& /* namespaceURI */)
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

