#ifndef ARABICA_SAX_WRITER_H
#define ARABICA_SAX_WRITER_H

#include <SAX/ArabicaConfig.hpp>
#include <SAX/helpers/XMLFilterImpl.hpp>
#include <SAX/ext/LexicalHandler.hpp>
#include <SAX/ext/DeclHandler.hpp>
#include <text/UnicodeCharacters.hpp>
#include <SAX/helpers/PropertyNames.hpp>
#include <XML/escaper.hpp>
#include <Arabica/StringAdaptor.hpp>
#include <Arabica/getparam.hpp>
#include <ostream>
#include <algorithm>
#include <typeinfo>

namespace Arabica
{
namespace SAX 
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class Writer : public XMLFilterImpl<string_type, string_adaptor>
{
  public:
    typedef Writer<string_type, string_adaptor> WriterT;
    typedef typename string_type::value_type charT;
    typedef typename string_type::traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef XMLReaderInterface<string_type, string_adaptor> XMLReaderT;
    typedef XMLFilterImpl<string_type, string_adaptor> XMLFilterT;
    typedef typename XMLFilterImpl<string_type, string_adaptor>::AttributesT AttributesT;
    typedef Arabica::text::Unicode<charT> UnicodeT;
    typedef Arabica::XML::text_escaper<charT, traitsT> text_escaperT;
    typedef Arabica::XML::attribute_escaper<charT, traitsT> attribute_escaperT;
  private:
    typedef LexicalHandler<string_type, string_adaptor> LexicalHandlerT;
    typedef DeclHandler<string_type, string_adaptor> DeclHandlerT;
    typedef typename XMLReaderT::InputSourceT InputSourceT;
    typedef typename XMLReaderT::PropertyBase PropertyBaseT;
    using XMLFilterT::getParent;

  public:
    Writer(ostreamT& stream, unsigned int indent = 2) :
      inCDATA_(false),
      inDTD_(false),
      internalSubset_(true),
      indent_(indent),
      depth_(0),
      stream_(&stream),
      encoding_(),
      lastTag_(startTag)
    {
    } // Writer

    Writer(ostreamT& stream, XMLReaderT& parent, unsigned int indent = 2) :
      XMLFilterT(parent),
      inCDATA_(false),
      inDTD_(false),
      internalSubset_(true),
      indent_(indent),
      depth_(0),
      stream_(&stream),
      encoding_(),
      lastTag_(startTag)
    {
    } // Writer

    Writer(ostreamT& stream, const string_type& encoding, unsigned int indent = 2) :
      inCDATA_(false),
      inDTD_(false),
      internalSubset_(true),
      indent_(indent),
      depth_(0),
      stream_(&stream),
      encoding_(encoding),
      lastTag_(startTag)
    {
    } // Writer

    Writer(ostreamT& stream, XMLReaderT& parent, const string_type& encoding, unsigned int indent = 2) :
      XMLFilterT(parent),
      inCDATA_(false),
      inDTD_(false),
      internalSubset_(true),
      indent_(indent),
      depth_(0),
      stream_(&stream),
      encoding_(encoding),
      lastTag_(startTag)
    {
    } // Writer

    // setEncoding
    // Sets the encoding included in the XML declaration.  If not set, then the encoding 
    // declaration will be omitted.
    // NOTE:  This is merely a label.  The writer will not perform any transcoding.  It is 
    // your responsibility to ensure that the data is already properly encoded, or that the 
    // destination stream will perform any necessary transcoding.
    void setEncoding(const string_type& encoding) { encoding_ = encoding; }

  public:
    // ContentHandler
    virtual void startDocument();
    virtual void endDocument();
    virtual void startElement(const string_type& namespaceURI, const string_type& localName,
                              const string_type& qName, const AttributesT& atts);
    virtual void endElement(const string_type& namespaceURI, const string_type& localName,
                            const string_type& qName);
    virtual void characters(const string_type& ch);
    virtual void ignorableWhitespace(const string_type& ch);
    virtual void processingInstruction(const string_type& target, const string_type& data);
    virtual void skippedEntity(const string_type& name);

    // Lexical Handler
    virtual void startDTD(const string_type& name, const string_type& publicId, const string_type& systemId);
    virtual void endDTD();
    virtual void startEntity(const string_type& name);
    virtual void endEntity(const string_type& name);
    virtual void startCDATA();
    virtual void endCDATA();
    virtual void comment(const string_type& text);

    // DTD Handler
    virtual void notationDecl(const string_type& name, const string_type& publicId, const string_type& systemId);
    virtual void unparsedEntityDecl(const string_type& name, const string_type& publicId, const string_type& systemId, const string_type& notationName);

    // Decl Handler
    virtual void elementDecl(const string_type& name, const string_type& model);
    virtual void attributeDecl(const string_type& elementName, const string_type& attributeName,
                               const string_type& type, const string_type& valueDefault, const string_type& value);
    virtual void internalEntityDecl(const string_type& name, const string_type& value);
    virtual void externalEntityDecl(const string_type& name, const string_type& publicId, const string_type& systemId);

  protected:
    /////////////////
    void startEntityDecl(const string_type& name);
    void publicAndSystem(const string_type& publicId, const string_type& systemId);
    void doIndent();
    bool isDtd(const string_type& name);

  private:
    bool inCDATA_;
    bool inDTD_;
    bool internalSubset_;
    int indent_;
    int depth_;
    ostreamT* stream_;
    string_type encoding_;
    enum { startTag, endTag, docTag } lastTag_;
    const SAX::PropertyNames<string_type> properties_;

}; // class Writer

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::startDocument()
{
  *stream_ << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::QUESTION_MARK
           << UnicodeT::LOWERCASE_X
           << UnicodeT::LOWERCASE_M
           << UnicodeT::LOWERCASE_L
           << UnicodeT::SPACE
           << UnicodeT::LOWERCASE_V
           << UnicodeT::LOWERCASE_E
           << UnicodeT::LOWERCASE_R
           << UnicodeT::LOWERCASE_S
           << UnicodeT::LOWERCASE_I
           << UnicodeT::LOWERCASE_O
           << UnicodeT::LOWERCASE_N
           << UnicodeT::EQUALS_SIGN
           << UnicodeT::QUOTATION_MARK
           << UnicodeT::NUMBER_1
           << UnicodeT::FULL_STOP
           << UnicodeT::NUMBER_0
           << UnicodeT::QUOTATION_MARK;

  if(encoding_.size())
    *stream_ << UnicodeT::SPACE
             << UnicodeT::LOWERCASE_E
             << UnicodeT::LOWERCASE_N
             << UnicodeT::LOWERCASE_C
             << UnicodeT::LOWERCASE_O
             << UnicodeT::LOWERCASE_D
             << UnicodeT::LOWERCASE_I
             << UnicodeT::LOWERCASE_N
             << UnicodeT::LOWERCASE_G
             << UnicodeT::EQUALS_SIGN
             << UnicodeT::QUOTATION_MARK
             << encoding_
             << UnicodeT::QUOTATION_MARK;

  *stream_ << UnicodeT::QUESTION_MARK
           << UnicodeT::GREATER_THAN_SIGN
           << UnicodeT::LINE_FEED;

  depth_ = 0;
  inCDATA_ = false;

  XMLFilterT::startDocument();

  lastTag_ = docTag;
} // startDocument

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::endDocument()
{
  XMLFilterT::endDocument();
  lastTag_ = endTag;
} // endDocument

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::startElement(
                              const string_type& namespaceURI, const string_type& localName,
                              const string_type& qName, const AttributesT& atts)
{ 
  if((lastTag_ == startTag) && (indent_ > 0))
    *stream_ << UnicodeT::LINE_FEED;
  doIndent();
  *stream_ << UnicodeT::LESS_THAN_SIGN << (!qName.empty() ? qName : localName);
  
  for(int i = 0; i < atts.getLength(); ++i)
  {
    *stream_ << UnicodeT::SPACE 
             << (!atts.getQName(i).empty() ? atts.getQName(i) : atts.getLocalName(i))
             << UnicodeT::EQUALS_SIGN
             << UnicodeT::QUOTATION_MARK;
    string_type value = atts.getValue(i); 
    std::for_each(value.begin(), value.end(), attribute_escaperT(*stream_));
    *stream_ << UnicodeT::QUOTATION_MARK;
  }

  *stream_ << UnicodeT::GREATER_THAN_SIGN;
  depth_ += indent_;
  lastTag_ = startTag;

  XMLFilterT::startElement(namespaceURI, localName, qName, atts);
} // startElement

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::endElement(
                            const string_type& namespaceURI, const string_type& localName,
                            const string_type& qName)
{
  depth_ -= indent_;
  if(lastTag_ == endTag)
    doIndent();
  *stream_ << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::SLASH
           << (!qName.empty() ? qName : localName)
           << UnicodeT::GREATER_THAN_SIGN;
  if(indent_ != 0)
    *stream_ << UnicodeT::LINE_FEED;
  lastTag_ = endTag;

  XMLFilterT::endElement(namespaceURI, localName, qName);
} // endElement

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::characters(const string_type& ch)
{
  if(!inCDATA_)
    std::for_each(ch.begin(), ch.end(), text_escaperT(*stream_));
  else
    *stream_ << ch;

  XMLFilterT::characters(ch);
} // characters

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::ignorableWhitespace(const string_type& ch)
{
  *stream_ << ch;

  XMLFilterT::ignorableWhitespace(ch);
} // ignorableWhitespace

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::processingInstruction(const string_type& target, const string_type& data)
{
  if((!inDTD_) || (inDTD_ && internalSubset_))
  {
    *stream_ << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::QUESTION_MARK
           << target;

    if(data.length())
      *stream_ << UnicodeT::SPACE << data;

    *stream_ << UnicodeT::QUESTION_MARK
             << UnicodeT::GREATER_THAN_SIGN;
  }

  XMLFilterT::processingInstruction(target, data);
} // processingInstruction

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::skippedEntity(const string_type& name)
{
  if(!isDtd(name))
    *stream_ << UnicodeT::AMPERSAND << name << UnicodeT::SEMI_COLON;

  XMLFilterT::skippedEntity(name);
} // skippedEntity

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::doIndent()
{
  for(int i = 0; i < depth_; ++i)
    *stream_ << UnicodeT::SPACE;
} // doIndent

template<class string_type, class string_adaptor>
bool Writer<string_type, string_adaptor>::isDtd(const string_type& name)
{
  return (name.length() == 5 && 
     name[0] == UnicodeT::LEFT_SQUARE_BRACKET &&
     name[1] == UnicodeT::LOWERCASE_D &&
     name[2] == UnicodeT::LOWERCASE_T &&
     name[3] == UnicodeT::LOWERCASE_D &&
     name[4] == UnicodeT::RIGHT_SQUARE_BRACKET);
} // isDtd

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::startDTD(const string_type& name, const string_type& publicId, const string_type& systemId)
{
  inDTD_ = true;
  depth_ += indent_;

  *stream_ << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::EXCLAMATION_MARK
           << UnicodeT::CAPITAL_D
           << UnicodeT::CAPITAL_O
           << UnicodeT::CAPITAL_C
           << UnicodeT::CAPITAL_T
           << UnicodeT::CAPITAL_Y
           << UnicodeT::CAPITAL_P
           << UnicodeT::CAPITAL_E
           << UnicodeT::SPACE
           << name;

  publicAndSystem(publicId, systemId);

  *stream_ << UnicodeT::SPACE
           << UnicodeT::LEFT_SQUARE_BRACKET
           << std::endl;

  XMLFilterT::startDTD(name, publicId, systemId);
} // startDTD

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::endDTD()
{
  *stream_ << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::GREATER_THAN_SIGN
           << std::endl;

  inDTD_ = false;
  depth_ -= indent_;

  XMLFilterT::endDTD();
} // endDTD

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::startEntity(const string_type& name)
{
  if(isDtd(name))
    internalSubset_ = false;

  XMLFilterT::startEntity(name);
} // startEntity

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::endEntity(const string_type& name)
{
  if(isDtd(name))
    internalSubset_ = true;

  XMLFilterT::endEntity(name);
} // endEntity

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::startCDATA()
{
  inCDATA_ = true;

  *stream_ << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::EXCLAMATION_MARK
           << UnicodeT::LEFT_SQUARE_BRACKET
           << UnicodeT::CAPITAL_C
           << UnicodeT::CAPITAL_D
           << UnicodeT::CAPITAL_A
           << UnicodeT::CAPITAL_T
           << UnicodeT::CAPITAL_A
           << UnicodeT::LEFT_SQUARE_BRACKET;

  XMLFilterT::startCDATA();
} // startCDATA

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::endCDATA()
{
  *stream_ << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::GREATER_THAN_SIGN;

  inCDATA_ = false;

  XMLFilterT::endCDATA();
} // endCDATA

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::comment(const string_type& text)
{
  if((!inDTD_) || (inDTD_ && internalSubset_))
    *stream_ << UnicodeT::LESS_THAN_SIGN
            << UnicodeT::EXCLAMATION_MARK
            << UnicodeT::HYPHEN_MINUS
            << UnicodeT::HYPHEN_MINUS
            << text
            << UnicodeT::HYPHEN_MINUS
            << UnicodeT::HYPHEN_MINUS
            << UnicodeT::GREATER_THAN_SIGN;

  XMLFilterT::comment(text);
} // comment

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::notationDecl(const string_type& name, const string_type& publicId, const string_type& systemId)
{
  if(inDTD_ && internalSubset_)
  {
    doIndent();

    *stream_ << UnicodeT::LESS_THAN_SIGN
            << UnicodeT::EXCLAMATION_MARK
            << UnicodeT::CAPITAL_N
            << UnicodeT::CAPITAL_O
            << UnicodeT::CAPITAL_T
            << UnicodeT::CAPITAL_A
            << UnicodeT::CAPITAL_T
            << UnicodeT::CAPITAL_I
            << UnicodeT::CAPITAL_O
            << UnicodeT::CAPITAL_N
            << UnicodeT::SPACE
            << name;

    publicAndSystem(publicId, systemId);

    *stream_ << UnicodeT::GREATER_THAN_SIGN
            << std::endl;
  } // if ...

  XMLFilterT::notationDecl(name, publicId, systemId);
} // notationDecl

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::unparsedEntityDecl(const string_type& name, const string_type& publicId, const string_type& systemId, const string_type& notationName)
{
  if(inDTD_ && internalSubset_)
  {
    doIndent();

    startEntityDecl(name);
    publicAndSystem(publicId, systemId);

    *stream_ << UnicodeT::SPACE
             << UnicodeT::CAPITAL_N
             << UnicodeT::CAPITAL_D
             << UnicodeT::CAPITAL_A
             << UnicodeT::CAPITAL_T
             << UnicodeT::CAPITAL_A
             << UnicodeT::SPACE
             << notationName
             << UnicodeT::GREATER_THAN_SIGN
             << std::endl;
  } // if ...

  XMLFilterT::unparsedEntityDecl(name, publicId, systemId, notationName);
} // unparsedEntityDecl

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::elementDecl(const string_type& name, const string_type& model)
{
  if(inDTD_ && internalSubset_)
  {
    doIndent();

    *stream_ << UnicodeT::LESS_THAN_SIGN
            << UnicodeT::EXCLAMATION_MARK
            << UnicodeT::CAPITAL_E
            << UnicodeT::CAPITAL_L
            << UnicodeT::CAPITAL_E
            << UnicodeT::CAPITAL_M
            << UnicodeT::CAPITAL_E
            << UnicodeT::CAPITAL_N
            << UnicodeT::CAPITAL_T
            << UnicodeT::SPACE
            << name
            << UnicodeT::SPACE
            << model
            << UnicodeT::GREATER_THAN_SIGN
            << std::endl;

  } // if ...

  XMLFilterT::elementDecl(name, model);
} // elementDecl

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::attributeDecl(const string_type& elementName, const string_type& attributeName,
                               const string_type& type, const string_type& valueDefault, const string_type& value)
{
  if(inDTD_ && internalSubset_)
  {
    doIndent();

    *stream_ << UnicodeT::LESS_THAN_SIGN
            << UnicodeT::EXCLAMATION_MARK
            << UnicodeT::CAPITAL_A
            << UnicodeT::CAPITAL_T
            << UnicodeT::CAPITAL_T
            << UnicodeT::CAPITAL_L
            << UnicodeT::CAPITAL_I
            << UnicodeT::CAPITAL_S
            << UnicodeT::CAPITAL_T
            << UnicodeT::SPACE
            << elementName
            << UnicodeT::SPACE
            << attributeName
            << UnicodeT::SPACE
            << type;

    if(!valueDefault.empty())
      *stream_ << UnicodeT::SPACE
               << valueDefault;

    if(!value.empty())
      *stream_ << UnicodeT::SPACE
               << UnicodeT::QUOTATION_MARK
               << value
               << UnicodeT::QUOTATION_MARK;

    *stream_ << UnicodeT::GREATER_THAN_SIGN
             << std::endl;
  } // if ...

  XMLFilterT::attributeDecl(elementName, attributeName, type, valueDefault, value);
} // attributeDecl

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::internalEntityDecl(const string_type& name, const string_type& value)
{
  if(inDTD_ && internalSubset_)
  {
    doIndent();
    startEntityDecl(name);
    *stream_ << UnicodeT::SPACE
             << UnicodeT::QUOTATION_MARK
             << value
             << UnicodeT::QUOTATION_MARK
             << UnicodeT::GREATER_THAN_SIGN
             << std::endl;
  } // if ...

  XMLFilterT::internalEntityDecl(name, value);
} // internalEntityDecl

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::externalEntityDecl(const string_type& name, const string_type& publicId, const string_type& systemId)
{
  if(inDTD_ && internalSubset_)
  {
    doIndent();
    startEntityDecl(name);
    publicAndSystem(publicId, systemId);
    *stream_ << UnicodeT::GREATER_THAN_SIGN
            << std::endl;
  } // if ...

  XMLFilterT::externalEntityDecl(name, publicId, systemId);
} // externalEntityDecl

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::startEntityDecl(const string_type& name)
{
  *stream_ << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::EXCLAMATION_MARK
           << UnicodeT::CAPITAL_E
           << UnicodeT::CAPITAL_N
           << UnicodeT::CAPITAL_T
           << UnicodeT::CAPITAL_I
           << UnicodeT::CAPITAL_T
           << UnicodeT::CAPITAL_Y
           << UnicodeT::SPACE
           << name;
} // startEntityDecl

template<class string_type, class string_adaptor>
void Writer<string_type, string_adaptor>::publicAndSystem(const string_type& publicId, const string_type& systemId)
{
  *stream_ << UnicodeT::SPACE;

  if(!publicId.empty())
    *stream_ << UnicodeT::CAPITAL_P
             << UnicodeT::CAPITAL_U
             << UnicodeT::CAPITAL_B
             << UnicodeT::CAPITAL_L
             << UnicodeT::CAPITAL_I
             << UnicodeT::CAPITAL_C
             << UnicodeT::SPACE
             << UnicodeT::QUOTATION_MARK
             << publicId
             << UnicodeT::QUOTATION_MARK;
  
  if(!systemId.empty())
  {
    if(publicId.empty())
      *stream_ << UnicodeT::CAPITAL_S
               << UnicodeT::CAPITAL_Y
               << UnicodeT::CAPITAL_S
               << UnicodeT::CAPITAL_T
               << UnicodeT::CAPITAL_E
               << UnicodeT::CAPITAL_M;
    *stream_ << UnicodeT::SPACE
             << UnicodeT::QUOTATION_MARK
             << systemId
             << UnicodeT::QUOTATION_MARK;
  } // if ...
} // publicAndSystem

} // namespace SAX
} // namespace Arabica

#endif
