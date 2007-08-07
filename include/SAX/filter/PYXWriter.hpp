#ifndef ARABICA_SAX_PYX_WRITER_H
#define ARABICA_SAX_PYX_WRITER_H

#include <SAX/ArabicaConfig.h>
#include <SAX/helpers/XMLFilterImpl.h>
#include <XML/UnicodeCharacters.h>
#include <ostream>

namespace SAX {

template<class string_type>
class PYXWriter : public basic_XMLFilterImpl<string_type>
{
  public:
    typedef string_type stringT;
    typedef PYXWriter<stringT> PYXWriterT;
    typedef typename string_type::value_type charT;
    typedef typename string_type::traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef basic_XMLReader<stringT> XMLReaderT;
    typedef basic_XMLFilterImpl<stringT> XMLFilterT;
    typedef typename basic_XMLFilterImpl<stringT>::AttributesT AttributesT;
    typedef Arabica::Unicode<charT> UnicodeT;
  private:
    using XMLFilterT::getParent;

  public:
    PYXWriter(ostreamT& stream) :
      XMLFilterT(),
      stream_(&stream)
    {
    } // PYXWriter

    PYXWriter(ostreamT& stream, XMLReaderT& parent) :
      XMLFilterT(parent),
      stream_(&stream)
    {
    } // PYXWriter

  public:
    // ContentHandler
    virtual void startElement(const stringT& namespaceURI, const stringT& localName,
                              const stringT& qName, const AttributesT& atts);
    virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName);
    virtual void characters(const stringT& ch);
    virtual void processingInstruction(const stringT& target, const stringT& data);

  private: 
    void escape(const stringT& ch);

    ostreamT* stream_;
}; // class PYXWriter

template<class string_type>
void PYXWriter<string_type>::startElement(
                              const stringT& namespaceURI, const stringT& localName,
                              const stringT& qName, const AttributesT& atts)
{ 
  *stream_ << UnicodeT::LEFT_PARENTHESIS << localName << std::endl;
  for(int i = 0; i < atts.getLength(); ++i)
  {
    *stream_ << UnicodeT::CAPITAL_A << atts.getLocalName(i) 
             << UnicodeT::SPACE;
    escape(atts.getValue(i));
    *stream_ << std::endl; 
  }

  XMLFilterT::startElement(namespaceURI, localName, qName, atts);
} // startElement

template<class string_type>
void PYXWriter<string_type>::endElement(
                            const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName)
{
  *stream_ << UnicodeT::RIGHT_PARENTHESIS << localName << std::endl;

  XMLFilterT::endElement(namespaceURI, localName, qName);
} // endElement

template<class string_type>
void PYXWriter<string_type>::characters(const stringT& ch)
{
  *stream_ << UnicodeT::HYPHEN_MINUS;
  escape(ch);
  *stream_ << std::endl;

  XMLFilterT::characters(ch);
} // characters

template<class string_type>
void PYXWriter<string_type>::processingInstruction(const stringT& target, const stringT& data)
{
  *stream_ << UnicodeT::QUESTION_MARK << target
           << UnicodeT::SPACE << data
           << std::endl;

  XMLFilterT::processingInstruction(target, data);
} // processingInstruction

template<class string_type>
void PYXWriter<string_type>::escape(const stringT& ch)
{
  for(typename stringT::const_iterator s = ch.begin(), se = ch.end(); s != se; ++s)
    if(*s == UnicodeT::LINE_FEED)
      *stream_ << UnicodeT::BACK_SLASH << UnicodeT::LOWERCASE_N;
    else
      *stream_ << *s;
} // escape

} // namespace SAX

#endif
