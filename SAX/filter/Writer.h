#ifndef ARABICA_SAX_WRITER_H
#define ARABICA_SAX_WRITER_H

#include <SAX/ArabicaConfig.h>
#include <SAX/helpers/XMLFilterImpl.h>
#include <SAX/ext/LexicalHandler.h>
#include <XML/UnicodeCharacters.h>
#include <SAX/helpers/PropertyNames.h>
#include <ostream>
#include <algorithm>
#include <typeinfo>

namespace SAX {

template<class string_type>
class basic_Writer : public basic_XMLFilterImpl<string_type>,
                     private basic_LexicalHandler<string_type>
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
    typedef Unicode<charT> UnicodeT;
  private:
    typedef basic_LexicalHandler<stringT> LexicalHandlerT;
    typedef typename XMLReaderT::InputSourceT InputSourceT;
    typedef typename XMLReaderT::PropertyBase PropertyBase;

  public:
    basic_Writer(ostreamT& stream) :
      inCDATA_(false),
      inDTD_(false),
      indent_(2),
      depth_(0),
      stream_(&stream),
      lexicalHandler_(0)
    {
    } // basic_Writer

    basic_Writer(ostreamT& stream, XMLReaderT& parent) :
      XMLFilterT(parent),
      inCDATA_(false),
      inDTD_(false),
      indent_(2),
      depth_(0),
      stream_(&stream),
      lexicalHandler_(0)
    {
    } // basic_Writer

    virtual void startDocument();
    virtual void endDocument();

    virtual void startElement(const stringT& namespaceURI, const stringT& localName,
                              const stringT& qName, const AttributesT& atts);
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
    bool inDTD_;
    int indent_;
    int depth_;
    ostreamT* stream_;

    LexicalHandlerT* lexicalHandler_;
    const SAX::PropertyNames<stringT> properties_;

    template<typename char_type, typename traits_type>
    class escaper
    {
      private:
        typedef char_type charT;
        typedef traits_type traitsT;
        typedef std::basic_ostream<charT, traitsT> ostreamT;
        typedef Unicode<charT> UnicodeT;

      public:
        escaper(ostreamT* stream) : stream_(stream) { }
        void operator()(charT ch)
        {
	  if(ch == UnicodeT::LESS_THAN_SIGN)
	  {
              *stream_ << UnicodeT::AMPERSAND
                       << UnicodeT::LOWERCASE_L
                       << UnicodeT::LOWERCASE_T
                       << UnicodeT::SEMI_COLON;
	      return;
          } // if(ch == UnicodeT::LESS_THAN_SIGN)
          if(ch == UnicodeT::GREATER_THAN_SIGN)
	  {
              *stream_ << UnicodeT::AMPERSAND
                       << UnicodeT::LOWERCASE_G
                       << UnicodeT::LOWERCASE_T
                       << UnicodeT::SEMI_COLON;
              return;
	  } // if(ch == UnicodeT::GREATER_THAN_SIGN)
          if(ch == UnicodeT::AMPERSAND)
	  {
              *stream_ << UnicodeT::AMPERSAND
                       << UnicodeT::LOWERCASE_A
                       << UnicodeT::LOWERCASE_M
                       << UnicodeT::LOWERCASE_P
                       << UnicodeT::SEMI_COLON;
	      return;
          } // if(ch == case UnicodeT::AMPERSAND)
          if(ch == UnicodeT::QUOTATION_MARK)
	  {
              *stream_ << UnicodeT::AMPERSAND
                       << UnicodeT::LOWERCASE_Q
                       << UnicodeT::LOWERCASE_U
                       << UnicodeT::LOWERCASE_O
                       << UnicodeT::LOWERCASE_T
                       << UnicodeT::SEMI_COLON;
              return;
	  } // if(ch == UnicodeT::QUOTATION_MARK)

          *stream_ << ch;
        } // operator()

      private:
        ostreamT* stream_;
    }; // escaper

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
           << UnicodeT::QUOTATION_MARK
           << UnicodeT::QUESTION_MARK
           << UnicodeT::GREATER_THAN_SIGN
           << std::endl;



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
                              const stringT& qName, const AttributesT& atts)
{ 
  doIndent();
  *stream_ << UnicodeT::LESS_THAN_SIGN << (!qName.empty() ? qName : localName);
  
  for(int i = 0; i < atts.getLength(); ++i)
  {
    *stream_ << UnicodeT::SPACE 
             << atts.getQName(i) 
             << UnicodeT::EQUALS_SIGN
             << UnicodeT::QUOTATION_MARK;
    stringT value = atts.getValue(i); 
    std::for_each(value.begin(), value.end(), escaper<charT, traitsT>(stream_));
    *stream_ << UnicodeT::QUOTATION_MARK;
  }

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
           << (!qName.empty() ? qName : localName)
           << UnicodeT::GREATER_THAN_SIGN
           << UnicodeT::LINE_FEED;

  XMLFilterT::endElement(namespaceURI, localName, qName);
} // endElement

template<class string_type>
void basic_Writer<string_type>::characters(const stringT& ch)
{
  if(!inCDATA_)
    std::for_each(ch.begin(), ch.end(), escaper<charT, traitsT>(stream_));
  else
    *stream_ << ch;

  XMLFilterT::characters(ch);
} // characters

template<class string_type>
void basic_Writer<string_type>::processingInstruction(const stringT& target, const stringT& data)
{
  *stream_ << UnicodeT::LESS_THAN_SIGN
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
    *stream_ << UnicodeT::AMPERSAND << name << UnicodeT::SEMI_COLON;
} // skippedEntity

template<class string_type>
void basic_Writer<string_type>::parse(InputSourceT& input)
{
  try 
  {
    XMLReaderT* parent = getParent();
    if(parent)
      parent->setProperty(properties_.lexicalHandler, static_cast<LexicalHandlerT&>(*this));
  }
  catch(...)
  {  }

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
     name[1] == UnicodeT::LOWERCASE_D &&
     name[2] == UnicodeT::LOWERCASE_T &&
     name[3] == UnicodeT::LOWERCASE_D &&
     name[4] == UnicodeT::RIGHT_SQUARE_BRACKET);
} // isDtd

#ifndef ARABICA_VS6_WORKAROUND
template<class string_type>
std::auto_ptr<typename basic_Writer<string_type>::PropertyBase> basic_Writer<string_type>::doGetProperty(const string_type& name)
#else
template<class string_type>
std::auto_ptr<basic_Writer<string_type>::PropertyBase> basic_Writer<string_type>::doGetProperty(const string_type& name)
#endif
{
  if(name == properties_.lexicalHandler)
  {
    XMLReaderT::Property<LexicalHandlerT*>* prop = 
          new XMLReaderT::Property<LexicalHandlerT*>(lexicalHandler_);
    return std::auto_ptr<PropertyBase>(prop);
  }

  return XMLFilterT::doGetProperty(name);
} // doGetProperty

#ifndef ARABICA_VS6_WORKAROUND
template<class string_type>
void basic_Writer<string_type>::doSetProperty(const string_type& name, std::auto_ptr<typename basic_Writer<string_type>::PropertyBase> value)
#else
template<class string_type>
void basic_Writer<string_type>::doSetProperty(const string_type& name, std::auto_ptr<basic_Writer<string_type>::PropertyBase> value)
#endif
{
  if(name == properties_.lexicalHandler)
  {
    XMLReaderT::Property<LexicalHandlerT&>* prop = 
          dynamic_cast<XMLReaderT::Property<LexicalHandlerT&>*>(value.get());

    if(!prop)
      throw std::bad_cast();

    lexicalHandler_ = &(prop->get());
  }
  
  XMLFilterT::doSetProperty(name, value);
} // doSetProperty

template<class string_type>
void basic_Writer<string_type>::startDTD(const stringT& name, const stringT& publicId, const stringT& systemId)
{
  inDTD_ = true;

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
           << name
           << UnicodeT::SPACE;
  if(publicId != stringT())
    *stream_ << UnicodeT::CAPITAL_P
             << UnicodeT::CAPITAL_U
             << UnicodeT::CAPITAL_B
             << UnicodeT::CAPITAL_L
             << UnicodeT::CAPITAL_I
             << UnicodeT::CAPITAL_C
             << UnicodeT::SPACE
             << UnicodeT::QUOTATION_MARK
             << publicId
             << UnicodeT::QUOTATION_MARK
             << UnicodeT::SPACE;
  else
    *stream_ << UnicodeT::CAPITAL_S
             << UnicodeT::CAPITAL_Y
             << UnicodeT::CAPITAL_S
             << UnicodeT::CAPITAL_T
             << UnicodeT::CAPITAL_E
             << UnicodeT::CAPITAL_M;
  *stream_ << UnicodeT::SPACE
           << UnicodeT::QUOTATION_MARK
           << systemId
           << UnicodeT::QUOTATION_MARK
           << UnicodeT::GREATER_THAN_SIGN
           << std::endl;

  if(lexicalHandler_)
    lexicalHandler_->startDTD(name, publicId, systemId);
} // startDTD

template<class string_type>
void basic_Writer<string_type>::endDTD()
{
  inDTD_ = false;

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

  *stream_ << UnicodeT::LESS_THAN_SIGN
           << UnicodeT::EXCLAMATION_MARK
           << UnicodeT::LEFT_SQUARE_BRACKET
           << UnicodeT::CAPITAL_C
           << UnicodeT::CAPITAL_D
           << UnicodeT::CAPITAL_A
           << UnicodeT::CAPITAL_T
           << UnicodeT::CAPITAL_A
           << UnicodeT::LEFT_SQUARE_BRACKET;

  if(lexicalHandler_)
    lexicalHandler_->startCDATA();
} // startCDATA

template<class string_type>
void basic_Writer<string_type>::endCDATA()
{
  *stream_ << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::RIGHT_SQUARE_BRACKET
           << UnicodeT::GREATER_THAN_SIGN;

  inCDATA_ = false;

  if(lexicalHandler_)
    lexicalHandler_->endCDATA();
} // endCDATA

template<class string_type>
void basic_Writer<string_type>::comment(const stringT& text)
{
  if(!inDTD_)
    *stream_ << UnicodeT::LESS_THAN_SIGN
            << UnicodeT::EXCLAMATION_MARK
            << UnicodeT::HYPHEN_MINUS
            << UnicodeT::HYPHEN_MINUS
            << text
            << UnicodeT::HYPHEN_MINUS
            << UnicodeT::HYPHEN_MINUS
            << UnicodeT::GREATER_THAN_SIGN;

  if(lexicalHandler_)
    lexicalHandler_->comment(text);
} // comment

typedef basic_Writer<std::string> Writer;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_Writer<std::wstring> wWriter;
#endif 

} // namespace SAX

#endif
