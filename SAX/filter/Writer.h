#ifndef SAXWriter_H
#define SAXWriter_H

#include <SAX/helpers/XMLFilterImpl.h>
#include <XML/UnicodeCharacters.h>
#include <ostream>

namespace SAX {

template<class string_type>
class basic_Writer : public basic_XMLFilterImpl<string_type>
{
  public:
    typedef string_type stringT;
    typedef typename string_type::value_type charT;
    typedef typename string_type::traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef basic_XMLReader<stringT> XMLReaderT;
    typedef basic_XMLFilterImpl<stringT> XMLFilterT;
    typedef Unicode<charT> UnicodeT;

    basic_Writer(std::ostream& stream) :
      indent_(2),
      stream_(&stream)
    {
    } // basic_Writer

    basic_Writer(ostreamT& stream, XMLReaderT& parent) :
      XMLFilterT(parent),
      indent_(2),
      stream_(&stream)
    {
    } // basic_Writer

    virtual void startDocument();
    virtual void endDocument();

    virtual void startElement(const stringT& namespaceURI, const stringT& localName,
                              const stringT& qName, const typename XMLFilterT::AttributesT& atts);
    virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName);

    virtual void characters(const stringT& ch);

    virtual void processingInstruction(const stringT& target, const stringT& data);
    virtual void skippedEntity(const stringT& name);

  private:
    void doIndent();
    bool isDtd(const stringT& name);

    int indent_;
    int depth_;
    ostreamT* stream_;
}; // class basic_Writer

template<class string_type>
void basic_Writer<string_type>::startDocument()
{
  *stream_ << "<?xml version=\"1.0\"?>" << std::endl;

  depth_ = 0;
  XMLFilterT::startDocument();
} // startDocument

template<class string_type>
void basic_Writer<string_type>::endDocument()
{
  XMLFilterT::endDocument();
} // endDocument

template<class string_type>
void basic_Writer<string_type>::startElement(
                              const stringT& namespaceURI, const stringT& localName,
                              const stringT& qName, const typename XMLFilterT::AttributesT& atts)
{ 
  doIndent();
  *stream_ << UnicodeT::LESS_THAN_SIGN << qName;
  
  for(int i = 0; i < atts.getLength(); ++i)
    *stream_ << UnicodeT::SPACE 
             << atts.getQName(i) 
             << UnicodeT::EQUALS_SIGN
             << UnicodeT::QUOTATION_MARK
             << atts.getValue(i) 
             << UnicodeT::QUOTATION_MARK;

  *stream_ << UnicodeT::GREATER_THAN_SIGN;
  ++depth_;

  XMLFilterT::startElement(namespaceURI, localName, qName, atts);
} // startElement

template<class string_type>
void basic_Writer<string_type>::endElement(
                            const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName)
{
  --depth_;
  doIndent();
  *stream_ << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::SLASH
           << qName 
           << UnicodeT::GREATER_THAN_SIGN
           << UnicodeT::LINE_FEED;

  XMLFilterT::endElement(namespaceURI, localName, qName);
} // endElement

template<class string_type>
void basic_Writer<string_type>::characters(const stringT& ch)
{
  *stream_ << ch;

  XMLFilterT::characters(ch);
} // characters

template<class string_type>
void basic_Writer<string_type>::processingInstruction(const stringT& target, const stringT& data)
{
  std::cout << UnicodeT::LESS_THAN_SIGN
            << UnicodeT::QUESTION_MARK
            << target 
            << UnicodeT::SPACE
            << data 
            << UnicodeT::QUESTION_MARK
            << UnicodeT::GREATER_THAN_SIGN;
} // processingInstruction

template<class string_type>
void basic_Writer<string_type>::skippedEntity(const stringT& name)
{
  if(!isDtd(name))
    std::cout << UnicodeT::AMPERSAND << name << UnicodeT::SEMI_COLON;
} // skippedEntity


template<class string_type>
void basic_Writer<string_type>::doIndent()
{
  for(int i = 0; i < depth_; ++i)
    *stream_ << UnicodeT::SPACE << UnicodeT::SPACE;
} // doIndent

template<class string_type>
bool basic_Writer<string_type>::isDtd(const string_type& name)
{
  return (name.length() == 5 && 
     name[0] == UnicodeT::LEFT_SQUARE_BRACKET &&
     name[1] == static_cast<charT>('d') &&
     name[2] == static_cast<charT>('t') &&
     name[3] == static_cast<charT>('d') &&
     name[4] == UnicodeT::RIGHT_SQUARE_BRACKET);
} // isDtd

    
typedef basic_Writer<std::string> Writer;
typedef basic_Writer<std::wstring> wWriter;

} // namespace SAX

#endif
