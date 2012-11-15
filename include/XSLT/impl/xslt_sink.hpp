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

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class Sink
{
public:
  virtual ~Sink() { }

  virtual Output<string_type, string_adaptor>& asOutput() = 0;
}; // class Sink

template<class string_type, class string_adaptor>
class SinkHolder
{
public:
  SinkHolder(Sink<string_type, string_adaptor>* sink) :
    sink_(sink),
    owned_(true) 
  {
  } // SinkHolder

  SinkHolder(Sink<string_type, string_adaptor>& sink) :
    sink_(&sink),
    owned_(false)
  {
  } // SinkHolder

  ~SinkHolder()
  {
    clear();
  } // ~SinkHolder

  void reset(Sink<string_type, string_adaptor>* sink) 
  { 
    clear();
    sink_ = sink;
    owned_ = true;
  } // assign

  void reset(Sink<string_type, string_adaptor>& sink)
  {
    clear();
    sink_ = &sink;
    owned_ = false;
  } // reset

  Sink<string_type, string_adaptor>& get() const
  {
    return *sink_;
  } // get

private:
  void clear()
  {
    if(owned_)
      delete sink_;
  } // clear
  
  Sink<string_type, string_adaptor>* sink_;
  bool owned_;

  SinkHolder(const SinkHolder&);
  bool operator==(const SinkHolder&) const;
  SinkHolder& operator=(const SinkHolder&);
}; // class SinkHolder

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class StreamSink : public Sink<string_type, string_adaptor>, private Output<string_type, string_adaptor>
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;

public:
  StreamSink(std::basic_ostream<typename string_adaptor::value_type>& stream) :
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

  virtual Output<string_type, string_adaptor>& asOutput() { return *this; }

protected:
  typedef typename Output<string_type, string_adaptor>::Settings Settings;

  void do_start_document(const Settings& settings)
  {
    seen_root_ = false;
    settings_ = settings;
    if(setting(SC::indent) == SC::yes)
      indent_ = 0;
  } // do_start_document

  void do_end_document()
  {
  } // do_end_document

  void do_start_element(const string_type& qName, 
                        const string_type& /* namespaceURI */,
                        const SAX::Attributes<string_type, string_adaptor>& atts)
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
      string_type ch = atts.getValue(a);
      std::for_each(ch.begin(), ch.end(), Arabica::XML::attribute_escaper<typename string_adaptor::value_type>(stream_));
      stream_ << '\"';
    }
    empty_ = true;
  } // do_start_element

  void do_end_element(const string_type& qName, 
		                  const string_type& /* namespaceURI */)
  { 
    if(!seen_root_)
      do_decl(string_adaptor::empty_string());

    preoutdent(empty_);

    if(empty_)
      stream_ << "/>";
    else
      stream_ << "</" << qName << ">";

    outdent(empty_);

    empty_ = false;
  } // do_end_element

  void do_characters(const string_type& ch)
  { 
    close_element_if_empty();

    if(!disable_output_escaping_ && !in_cdata_)
      std::for_each(ch.begin(), ch.end(), Arabica::XML::text_escaper<typename string_adaptor::value_type>(stream_));
    else if(in_cdata_) 
    {
      size_t breakAt = ch.find(SC::CDATAEnd);
      if(breakAt == string_type::npos)
      {
        stream_ << ch;
        return;
      }
      size_t start = 0;
      do
      {
        breakAt += 2;
        stream_ << ch.substr(start, breakAt);
        do_end_CDATA();
        start = breakAt;
        do_start_CDATA();
        breakAt = ch.find(SC::CDATAEnd, breakAt);
      }
      while(breakAt != string_type::npos);
      stream_ << ch.substr(start);
    }
    else
      stream_ << ch;
  } // characters

  void do_start_CDATA()
  {
    close_element_if_empty();

    in_cdata_ = true;
    stream_ << SC::CDATAStart;
  } // do_start_CDATA

  void do_end_CDATA()
  {
    in_cdata_ = false;
    stream_ << SC::CDATAEnd;
  } // do_end_CDATA

  void do_comment(const string_type& ch)
  {
    close_element_if_empty();

    stream_ << SC::CommentStart
	    << ch
	    << SC::CommentEnd;
  } // do_comment

  void do_processing_instruction(const string_type& target,
				 const string_type& data)
  {
    close_element_if_empty();

    stream_ << SC::PIStart 
	    << target
	    << " "
	    << data
	    << SC::PIEnd;
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
      do_decl(string_adaptor::empty_string());
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
 
  void do_decl(const string_type& qName)
  {
    if((setting(SC::method) == SC::text) || (setting(SC::omit_xml_declaration) == SC::yes))
      return;

    {
      string_type version = setting(SC::version);
      if(version.empty())
        version = SC::Version;
      stream_ << "<?xml version=\"" << version << "\""; 
    }
    {
      string_type s = setting(SC::standalone);
      if(!s.empty())
        stream_ << " standalone=\"" << s << "\"";
    }
    stream_ << "?>\n";

    if(!qName.empty())
    {
      string_type pub = setting(SC::doctype_public);
      string_type sys = setting(SC::doctype_system);

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

  string_type setting(const string_type& name)
  {
    typename Settings::const_iterator i = settings_.find(name);
    if(i == settings_.end())
      return string_adaptor::empty_string();
    return i->second;
  } // setting

  std::basic_ostream<typename string_adaptor::value_type>& stream_;
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

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class DOMSink : public Sink<string_type, string_adaptor>, private Output<string_type, string_adaptor>
{
  typedef StylesheetConstant<string_type, string_adaptor> SC;
public:
  DOMSink() :
    indent_(-1),
    out_again_(false)
  {
  } // DOMSink

  ~DOMSink() 
  {
  } // ~DOMSink

  virtual Output<string_type, string_adaptor>& asOutput() { return *this; }
  DOM::Node<string_type, string_adaptor> node() const { return documentFrag_; }

protected:
  typedef typename Output<string_type, string_adaptor>::Settings Settings;

  void do_start_document(const Settings& settings)
  {
    typename Settings::const_iterator i = settings.find(SC::indent);
    if((i != settings.end()) &&
       (i->second == SC::yes))
      indent_ = 0;
  } // do_start_document

  void do_end_document()
  {
  } // do_end_document

  void do_characters(const string_type& ch)
  {
    DOM::Node<string_type> lc = current().getLastChild();
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
    DOM::Node<string_type> lc = current().getLastChild();
    if(lc.getNodeType() == DOM::Node_base::TEXT_NODE)
      current().replaceChild(document().createCDATASection(lc.getNodeValue()), lc);
  } // do_end_CDATA

  void do_comment(const string_type& ch)
  {
    current().appendChild(document().createComment(ch));
  } // do_comment

  void do_processing_instruction(const string_type& target,
                                 const string_type& data)
  {
    current().appendChild(document().createProcessingInstruction(target, data));
  } // do_processing_instruction

  void do_disableOutputEscaping(bool /* disable */) { }

  bool want_namespace_declarations() const { return false; }

  void do_start_element(const string_type& qName,
                        const string_type& namespaceURI,
                        const SAX::Attributes<string_type, string_adaptor>& atts)
  {
    indent();
    DOM::Element<string_type, string_adaptor> elem = document().createElementNS(namespaceURI, qName);
    current().appendChild(elem);

    // attributes here
    for(int i = 0; i < atts.getLength(); ++i)
      elem.setAttributeNS(atts.getURI(i), atts.getQName(i), atts.getValue(i));

    current_ = elem;
  } // do_start_element

  void do_end_element(const string_type& /* qName */, 
                      const string_type& /* namespaceURI */)
  {
    outdent();
    current_ = current_.getParentNode();
  } // do_end_element

private:
  DOM::Document<string_type>& document()
  {
    if(document_ != 0)
      return document_;

    DOM::DOMImplementation<string_type, string_adaptor> di = SimpleDOM::DOMImplementation<string_type, string_adaptor>::getDOMImplementation();
    document_ = di.createDocument(string_adaptor::empty_string(), string_adaptor::empty_string(), 0);
    return document_;
  } // document

  DOM::Node<string_type>& current()
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

    string_type sps;
    if(indent_ != 0)
    {
      sps += '\n';
      std::fill_n(std::back_inserter<string_type>(sps), indent_, ' ');
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
      do_characters(SC::newline);

    indent_ -= 2;
    out_again_ = true;
  } // outdent

  DOM::Document<string_type, string_adaptor> document_;
  DOM::DocumentFragment<string_type, string_adaptor> documentFrag_;
  DOM::Node<string_type, string_adaptor> current_;

  int indent_;
  bool out_again_;
}; // DOMSink

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_SINK_HPP

