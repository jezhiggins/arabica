#ifndef SAXWriter_H
#define SAXWriter_H

#include <SAX/helpers/XMLFilterImpl.h>
#include <SAX/ext/LexicalHandler.h>
#include <XML/UnicodeCharacters.h>
#include <ostream>

namespace SAX {

template<class string_type>
class basic_Writer : public basic_XMLFilterImpl<string_type>,
                     private basic_LexicalHandler<string_type>
{
  public:
    typedef string_type stringT;
    typedef typename string_type::value_type charT;
    typedef typename string_type::traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef basic_XMLReader<stringT> XMLReaderT;
    typedef basic_XMLFilterImpl<stringT> XMLFilterT;
    typedef Unicode<charT> UnicodeT;
  private:
    typedef basic_LexicalHandler<stringT> LexicalHandlerT;

  public:
    basic_Writer(ostreamT& stream) :
      lexicalHandler_(0),
      indent_(2),
      stream_(&stream),
      inCDATA_(false)
    {
    } // basic_Writer

    basic_Writer(ostreamT& stream, XMLReaderT& parent) :
      XMLFilterT(parent),
      lexicalHandler_(0),
      indent_(2),
      stream_(&stream),
      inCDATA_(false)
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

    virtual void parse(InputSourceT& input);

  protected:
    virtual std::auto_ptr<PropertyBase> doGetProperty(const stringT& name);
    virtual void doSetProperty(const stringT& name, std::auto_ptr<PropertyBase> value);

  private:
    virtual void startDTD(const stringT& name, const stringT& publicId, const stringT& systemId);
    virtual void endDTD();
    virtual void startEntity(const stringT& name);
    virtual void endEntity(const stringT& name);
    virtual void startCDATA();
    virtual void endCDATA();
    virtual void comment(const stringT& text);

    void doIndent();
    bool isDtd(const stringT& name);

    bool inCDATA_;
    int indent_;
    int depth_;
    ostreamT* stream_;

    LexicalHandlerT* lexicalHandler_;
    const SAX::PropertyNames<stringT> properties_;
}; // class basic_Writer

template<class string_type>
void basic_Writer<string_type>::startDocument()
{
  *stream_ << "<?xml version=\"1.0\"?>" << std::endl;

  depth_ = 0;
  inCDATA_ = false;

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
void basic_Writer<string_type>::parse(InputSourceT& input)
{
  XMLReaderT* parent = getParent();
  if(parent)
    parent->setProperty(properties_.lexicalHandler, static_cast<SAX::LexicalHandler&>(*this));

  XMLFilterT::parse(input);
} // parse

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

template<class string_type>
std::auto_ptr<typename basic_Writer<string_type>::XMLReaderT::PropertyBase> basic_Writer<string_type>::doGetProperty(const string_type& name)
{
  if(name == properties_.lexicalHandler)
  {
    XMLReaderT::Property<LexicalHandlerT*>* prop = 
          new XMLReaderT::Property<LexicalHandlerT*>(lexicalHandler_);
    return std::auto_ptr<XMLReaderT::PropertyBase>(prop);
  }

  return XMLFilterT::doGetProperty(name);
} // doGetProperty

template<class string_type>
void basic_Writer<string_type>::doSetProperty(const string_type& name, typename std::auto_ptr<typename basic_Writer<string_type>::XMLReaderT::PropertyBase> value)
{
  if(name == properties_.lexicalHandler)
  {
    XMLReaderT::Property<LexicalHandlerT&>* prop = 
          dynamic_cast<XMLReaderT::Property<LexicalHandlerT&>*>(value.get());

    if(!prop)
      throw std::bad_cast();

    lexicalHandler_ = &(prop->get());
  }
  return XMLFilterT::doSetProperty(name, value);
} // doSetProperty

template<class string_type>
void basic_Writer<string_type>::startDTD(const stringT& name, const stringT& publicId, const stringT& systemId)
{
  if(lexicalHandler_)
    lexicalHandler_->startDTD(name, publicId, systemId);
} // startDTD

template<class string_type>
void basic_Writer<string_type>::endDTD()
{
  if(lexicalHandler_)
    lexicalHandler_->endDTD();
} // endDTD

template<class string_type>
void basic_Writer<string_type>::startEntity(const stringT& name)
{
  if(lexicalHandler_)
    lexicalHandler_->startEntity(name);
} // startEntity

template<class string_type>
void basic_Writer<string_type>::endEntity(const stringT& name)
{
  if(lexicalHandler_)
    lexicalHandler_->endEntity(name);
} // endEntity

template<class string_type>
void basic_Writer<string_type>::startCDATA()
{
  inCDATA_ = true;

  std::cout << UnicodeT::LESS_THAN_SIGN
            << UnicodeT::EXCLAMATION_MARK
            << UnicodeT::LEFT_SQUARE_BRACKET
            << static_cast<charT>('C')
            << static_cast<charT>('D')
            << static_cast<charT>('A')
            << static_cast<charT>('T')
            << static_cast<charT>('A')
            << UnicodeT::LEFT_SQUARE_BRACKET;

  if(lexicalHandler_)
    lexicalHandler_->startCDATA();
} // startCDATA

template<class string_type>
void basic_Writer<string_type>::endCDATA()
{
  std::cout << UnicodeT::RIGHT_SQUARE_BRACKET
            << UnicodeT::RIGHT_SQUARE_BRACKET
            << UnicodeT::GREATER_THAN_SIGN;

  inCDATA_ = false;

  if(lexicalHandler_)
    lexicalHandler_->endCDATA();
} // endCDATA

template<class string_type>
void basic_Writer<string_type>::comment(const stringT& text)
{
  if(lexicalHandler_)
    lexicalHandler_->comment(text);
} // comment
    
typedef basic_Writer<std::string> Writer;
typedef basic_Writer<std::wstring> wWriter;

} // namespace SAX

#endif
