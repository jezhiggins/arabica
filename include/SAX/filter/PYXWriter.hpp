#ifndef ARABICA_SAX_PYX_WRITER_H
#define ARABICA_SAX_PYX_WRITER_H

#include <SAX/ArabicaConfig.hpp>
#include <SAX/helpers/XMLFilterImpl.hpp>
#include <text/UnicodeCharacters.hpp>
#include <ostream>

namespace Arabica
{
namespace SAX 
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class PYXWriter : public XMLFilterImpl<string_type, string_adaptor>
{
  public:
    typedef XMLReaderInterface<string_type, string_adaptor> XMLReaderT;
    typedef XMLFilterImpl<string_type, string_adaptor> XMLFilterT;
    typedef typename XMLFilterT::AttributesT AttributesT;
    typedef typename string_type::value_type charT;
    typedef typename string_type::traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef Arabica::text::Unicode<charT> UnicodeT;
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
    virtual void startElement(const string_type& namespaceURI, const string_type& localName,
                              const string_type& qName, const AttributesT& atts);
    virtual void endElement(const string_type& namespaceURI, const string_type& localName,
                            const string_type& qName);
    virtual void characters(const string_type& ch);
    virtual void processingInstruction(const string_type& target, const string_type& data);

  private: 
    void escape(const string_type& ch);

    ostreamT* stream_;
}; // class PYXWriter

template<class string_type, class string_adaptor>
void PYXWriter<string_type, string_adaptor>::startElement(
                              const string_type& namespaceURI, const string_type& localName,
                              const string_type& qName, const AttributesT& atts)
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

template<class string_type, class string_adaptor>
void PYXWriter<string_type, string_adaptor>::endElement(
                            const string_type& namespaceURI, const string_type& localName,
                            const string_type& qName)
{
  *stream_ << UnicodeT::RIGHT_PARENTHESIS << localName << std::endl;

  XMLFilterT::endElement(namespaceURI, localName, qName);
} // endElement

template<class string_type, class string_adaptor>
void PYXWriter<string_type, string_adaptor>::characters(const string_type& ch)
{
  *stream_ << UnicodeT::HYPHEN_MINUS;
  escape(ch);
  *stream_ << std::endl;

  XMLFilterT::characters(ch);
} // characters

template<class string_type, class string_adaptor>
void PYXWriter<string_type, string_adaptor>::processingInstruction(const string_type& target, const string_type& data)
{
  *stream_ << UnicodeT::QUESTION_MARK << target
           << UnicodeT::SPACE << data
           << std::endl;

  XMLFilterT::processingInstruction(target, data);
} // processingInstruction

template<class string_type, class string_adaptor>
void PYXWriter<string_type, string_adaptor>::escape(const string_type& ch)
{
  for(typename string_type::const_iterator s = ch.begin(), se = ch.end(); s != se; ++s)
    if(*s == UnicodeT::LINE_FEED)
      *stream_ << UnicodeT::BACK_SLASH << UnicodeT::LOWERCASE_N;
    else
      *stream_ << *s;
} // escape

} // namespace SAX
} // namespace Arabica

#endif
