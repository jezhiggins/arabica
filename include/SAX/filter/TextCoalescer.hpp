#ifndef ARABICA_TEXT_COALESCER_HPP
#define ARABICA_TEXT_COALESCER_HPP

#include <SAX/ArabicaConfig.h>
#include <SAX/helpers/XMLFilterImpl.h>
#include <Utils/StringAdaptor.h>

namespace SAX
{

/**
  Parsers are not required to report text in contiguous lumps.  It's perfectly legal to 
  report a block of text in one, two or many calls to characters(...).  Sometimes this isn't 
  an issue, and sometimes it makes things a little awkward.  
  This filter buffers up multiple calls to characters(...) and reports text in a single lump.
 */
template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class TextCoalescer : public basic_XMLFilterImpl<string_type>
{
  typedef basic_XMLFilterImpl<string_type> XMLFilterT;

public:
  typedef basic_XMLReader<string_type> XMLReaderT;
  typedef basic_Attributes<string_type> AttributesT;

  TextCoalescer() : 
    XMLFilterT()
  { 
  } // basic_TextCoalescer

  TextCoalescer(XMLReaderT& parent) : 
    XMLFilterT(parent) 
  {
  } // basic_TextCoalescer

  virtual void startElement(const string_type& namespaceURI, const string_type& localName,
                            const string_type& qName, const AttributesT& atts) 
  { 
    flush();
    XMLFilterT::startElement(namespaceURI, localName, qName, atts);
  } // startElement

  virtual void endElement(const string_type& namespaceURI, const string_type& localName,
                          const string_type& qName) 
  { 
    flush();
    XMLFilterT::endElement(namespaceURI, localName, qName);
  }  // endElement

  virtual void characters(const string_type& ch) 
  { 
    string_adaptor::append(buffer_, ch);
  } // characters

  virtual void ignorableWhitespace(const string_type& ch) 
  { 
    string_adaptor::append(buffer_, ch);
  } // ignorableWhitespace

  virtual void processingInstruction(const string_type& target, const string_type& data) 
  { 
    flush();
    XMLFilterT::processingInstruction(target, data);
  } // processingInstruction

  virtual void startCDATA() 
  { 
    flush();
    XMLFilterT::startCDATA();
  } // startCDATA

  virtual void endCDATA() 
  { 
    flush();
    XMLFilterT::endCDATA();
  } // endCDATA

  virtual void comment(const string_type& text) 
  { 
    flush();
    XMLFilterT::comment(text);
  } // comment

private:
  void flush()
  {
    if(string_adaptor::empty(buffer_))
      return;

    XMLFilterT::characters(buffer_);
    buffer_ = string_adaptor::empty_string();
  } // flush
  string_type buffer_;
}; // class basic_TextCoalescer

} // namespace SAX
#endif
