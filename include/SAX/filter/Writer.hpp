#ifndef ARABICA_SAX_WRITER_H
#define ARABICA_SAX_WRITER_H

#include <SAX/ArabicaConfig.hpp>
#include <SAX/helpers/XMLFilterImpl.hpp>
#include <SAX/ext/LexicalHandler.hpp>
#include <SAX/ext/DeclHandler.hpp>
#include <XML/UnicodeCharacters.hpp>
#include <SAX/helpers/PropertyNames.hpp>
#include <XML/escaper.hpp>
#include <ostream>
#include <algorithm>
#include <typeinfo>

namespace Arabica
{
namespace SAX 
{

template<class string_type>
class basic_Writer : public basic_XMLFilterImpl<string_type>
{
  public:
    typedef string_type stringT;
    typedef basic_Writer<stringT> WriterT;
    typedef typename string_type::value_type charT;
    typedef typename string_type::traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef basic_XMLReader<stringT> XMLReaderT;
    typedef basic_XMLFilterImpl<stringT> XMLFilterT;
    typedef typename basic_XMLFilterImpl<stringT>::AttributesT AttributesT;
    typedef Arabica::Unicode<charT> UnicodeT;
    typedef Arabica::XML::text_escaper<charT, traitsT> text_escaperT;
    typedef Arabica::XML::attribute_escaper<charT, traitsT> attribute_escaperT;
  private:
    typedef basic_LexicalHandler<stringT> LexicalHandlerT;
    typedef basic_DeclHandler<stringT> DeclHandlerT;
    typedef typename XMLReaderT::InputSourceT InputSourceT;
    typedef typename XMLReaderT::PropertyBase PropertyBaseT;
    using XMLFilterT::getParent;

  public:
    basic_Writer(ostreamT& stream, unsigned int indent = 2) :
      inCDATA_(false),
      inDTD_(false),
      internalSubset_(true),
      indent_(indent),
      depth_(0),
      stream_(&stream),
      encoding_(),
      lastTag_(startTag)
    {
    } // basic_Writer

    basic_Writer(ostreamT& stream, XMLReaderT& parent, unsigned int indent = 2) :
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
    } // basic_Writer

    basic_Writer(ostreamT& stream, const stringT& encoding, unsigned int indent = 2) :
      inCDATA_(false),
      inDTD_(false),
      internalSubset_(true),
      indent_(indent),
      depth_(0),
      stream_(&stream),
      encoding_(encoding),
      lastTag_(startTag)
    {
    } // basic_Writer

    basic_Writer(ostreamT& stream, XMLReaderT& parent, const stringT& encoding, unsigned int indent = 2) :
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
    } // basic_Writer

    // setEncoding
    // Sets the encoding included in the XML declaration.  If not set, then the encoding 
    // declaration will be omitted.
    // NOTE:  This is merely a label.  The writer will not perform any transcoding.  It is 
    // your responsibility to ensure that the data is already properly encoded, or that the 
    // destination stream will perform any necessary transcoding.
    void setEncoding(const stringT& encoding) { encoding_ = encoding; }

  public:
    // ContentHandler
    virtual void startDocument();
    virtual void endDocument();
    virtual void startElement(const stringT& namespaceURI, const stringT& localName,
                              const stringT& qName, const AttributesT& atts);
    virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName);
    virtual void characters(const stringT& ch);
    virtual void ignorableWhitespace(const stringT& ch);
    virtual void processingInstruction(const stringT& target, const stringT& data);
    virtual void skippedEntity(const stringT& name);

    // Lexical Handler
    virtual void startDTD(const stringT& name, const stringT& publicId, const stringT& systemId);
    virtual void endDTD();
    virtual void startEntity(const stringT& name);
    virtual void endEntity(const stringT& name);
    virtual void startCDATA();
    virtual void endCDATA();
    virtual void comment(const stringT& text);

    // DTD Handler
    virtual void notationDecl(const stringT& name, const stringT& publicId, const stringT& systemId);
    virtual void unparsedEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId, const stringT& notationName);

    // Decl Handler
    virtual void elementDecl(const stringT& name, const stringT& model);
    virtual void attributeDecl(const stringT& elementName, const stringT& attributeName,
                               const stringT& type, const stringT& valueDefault, const stringT& value);
    virtual void internalEntityDecl(const stringT& name, const stringT& value);
    virtual void externalEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId);

  protected:
    /////////////////
    void startEntityDecl(const stringT& name);
    void publicAndSystem(const stringT& publicId, const stringT& systemId);
    void doIndent();
    bool isDtd(const stringT& name);

  private:
    bool inCDATA_;
    bool inDTD_;
    bool internalSubset_;
    int indent_;
    int depth_;
    ostreamT* stream_;
    stringT encoding_;
    enum { startTag, endTag, docTag } lastTag_;
    const SAX::PropertyNames<stringT> properties_;

}; // class basic_Writer

template<class string_type>
void basic_Writer<string_type>::startDocument()
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

template<class string_type>
void basic_Writer<string_type>::endDocument()
{
  XMLFilterT::endDocument();
  lastTag_ = endTag;
} // endDocument

template<class string_type>
void basic_Writer<string_type>::startElement(
                              const stringT& namespaceURI, const stringT& localName,
                              const stringT& qName, const AttributesT& atts)
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
    stringT value = atts.getValue(i); 
    std::for_each(value.begin(), value.end(), attribute_escaperT(*stream_));
    *stream_ << UnicodeT::QUOTATION_MARK;
  }

  *stream_ << UnicodeT::GREATER_THAN_SIGN;
  depth_ += indent_;
  lastTag_ = startTag;

  XMLFilterT::startElement(namespaceURI, localName, qName, atts);
} // startElement

template<class string_type>
void basic_Writer<string_type>::endElement(
                            const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName)
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

template<class string_type>
void basic_Writer<string_type>::characters(const stringT& ch)
{
  if(!inCDATA_)
    std::for_each(ch.begin(), ch.end(), text_escaperT(*stream_));
  else
    *stream_ << ch;

  XMLFilterT::characters(ch);
} // characters

template<class string_type>
void basic_Writer<string_type>::ignorableWhitespace(const stringT& ch)
{
  *stream_ << ch;

  XMLFilterT::ignorableWhitespace(ch);
} // ignorableWhitespace

template<class string_type>
void basic_Writer<string_type>::processingInstruction(const stringT& target, const stringT& data)
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

template<class string_type>
void basic_Writer<string_type>::skippedEntity(const stringT& name)
{
  if(!isDtd(name))
    *stream_ << UnicodeT::AMPERSAND << name << UnicodeT::SEMI_COLON;

  XMLFilterT::skippedEntity(name);
} // skippedEntity

template<class string_type>
void basic_Writer<string_type>::doIndent()
{
  for(int i = 0; i < depth_; ++i)
    *stream_ << UnicodeT::SPACE;
} // doIndent

template<class string_type>
bool basic_Writer<string_type>::isDtd(const string_type& name)
{
  return (name.length() == 5 && 
     name[0] == UnicodeT::LEFT_SQUARE_BRACKET &&
     name[1] == UnicodeT::LOWERCASE_D &&
     name[2] == UnicodeT::LOWERCASE_T &&
     name[3] == UnicodeT::LOWERCASE_D &&
     name[4] == UnicodeT::RIGHT_SQUARE_BRACKET);
} // isDtd

template<class string_type>
void basic_Writer<string_type>::startDTD(const stringT& name, const stringT& publicId, const stringT& systemId)
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

template<class string_type>
void basic_Writer<string_type>::endDTD()
{
  *stream_ << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::GREATER_THAN_SIGN
           << std::endl;

  inDTD_ = false;
  depth_ -= indent_;

  XMLFilterT::endDTD();
} // endDTD

template<class string_type>
void basic_Writer<string_type>::startEntity(const stringT& name)
{
  if(isDtd(name))
    internalSubset_ = false;

  XMLFilterT::startEntity(name);
} // startEntity

template<class string_type>
void basic_Writer<string_type>::endEntity(const stringT& name)
{
  if(isDtd(name))
    internalSubset_ = true;

  XMLFilterT::endEntity(name);
} // endEntity

template<class string_type>
void basic_Writer<string_type>::startCDATA()
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

template<class string_type>
void basic_Writer<string_type>::endCDATA()
{
  *stream_ << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::GREATER_THAN_SIGN;

  inCDATA_ = false;

  XMLFilterT::endCDATA();
} // endCDATA

template<class string_type>
void basic_Writer<string_type>::comment(const stringT& text)
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

template<class string_type>
void basic_Writer<string_type>::notationDecl(const stringT& name, const stringT& publicId, const stringT& systemId)
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

template<class string_type>
void basic_Writer<string_type>::unparsedEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId, const stringT& notationName)
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

template<class string_type>
void basic_Writer<string_type>::elementDecl(const stringT& name, const stringT& model)
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

template<class string_type>
void basic_Writer<string_type>::attributeDecl(const stringT& elementName, const stringT& attributeName,
                               const stringT& type, const stringT& valueDefault, const stringT& value)
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

template<class string_type>
void basic_Writer<string_type>::internalEntityDecl(const stringT& name, const stringT& value)
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

template<class string_type>
void basic_Writer<string_type>::externalEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId)
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

template<class string_type>
void basic_Writer<string_type>::startEntityDecl(const stringT& name)
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

template<class string_type>
void basic_Writer<string_type>::publicAndSystem(const stringT& publicId, const stringT& systemId)
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

typedef basic_Writer<std::string> Writer;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_Writer<std::wstring> wWriter;
#endif 

} // namespace SAX
} // namespace Arabica

#endif
