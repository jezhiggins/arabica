#ifndef saxgarden_h
#define saxgarden_h

#include <SAX/ArabicaConfig.h>
#include <boost/spirit.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <string>
#include <stack>
#include <SAX/XMLReader.h>
#include <SAX/SAXParseException.h>
#include <SAX/SAXNotRecognizedException.h>
#include <SAX/helpers/InputSourceResolver.h>
#include <SAX/helpers/StringAdaptor.h>
#include <SAX/helpers/AttributesImpl.h>

namespace SAX {

template<class string_type>
class Garden : public basic_XMLReader<string_type>
{
public:
  typedef string_type stringT;
  typedef basic_EntityResolver<stringT> EntityResolverT;
  typedef basic_DTDHandler<stringT> DTDHandlerT;
  typedef basic_ContentHandler<stringT> ContentHandlerT;
  typedef basic_InputSource<stringT> InputSourceT;
  typedef basic_AttributesImpl<stringT> AttributesImplT;

  Garden();

  virtual bool getFeature(const stringT& name) const;
  virtual void setFeature(const stringT& name, bool value);

  virtual void setEntityResolver(EntityResolverT& resolver) { entityResolver_ = &resolver; }
  virtual EntityResolverT* getEntityResolver() const { return entityResolver_; }

  virtual void setDTDHandler(DTDHandlerT& handler) { dtdHandler_ = &handler; }
  virtual DTDHandlerT* getDTDHandler() const { return dtdHandler_; }
  
  virtual void setContentHandler(ContentHandlerT& handler) { contentHandler_ = &handler; }
  virtual ContentHandlerT* getContentHandler() const { return contentHandler_; }

  virtual void setErrorHandler(SAX::ErrorHandler& handler) { errorHandler_ = &handler; }
  virtual SAX::ErrorHandler* getErrorHandler() const { return errorHandler_; }

  virtual void parse(InputSourceT& input);

  virtual std::auto_ptr<PropertyBase> doGetProperty(const stringT& name);
  virtual void doSetProperty(const stringT& name, std::auto_ptr<PropertyBase> value);

private:
  void reportError(const std::string& message, bool fatal = false);

  typedef stringT::value_type char_t;
  typedef std::vector<char_t> vector_t;
  typedef vector_t::iterator iterator_t;
  typedef boost::spirit::scanner<iterator_t> scanner_t;
  typedef boost::spirit::rule<scanner_t> rule_t;

  void openElement(iterator_t s, iterator_t e);
  void closeElement(iterator_t s, iterator_t e);
  void closeEmptyElement(iterator_t s, iterator_t e);
  void endElementName(iterator_t s, iterator_t e);
  void endElement(iterator_t s, iterator_t e);
  void attributeName(iterator_t s, iterator_t e);
  void attributeValue(iterator_t s, iterator_t e);
  void elementContent(iterator_t s, iterator_t e);
  void piTarget(iterator_t s, iterator_t e);
  void piData(iterator_t s, iterator_t e);
  void piEnd(iterator_t s, iterator_t e);
  void entityRef(iterator_t s, iterator_t e);
  void decimalCharacterRef(iterator_t s, iterator_t e);
  void hexCharacterRef(iterator_t s, iterator_t e);
  void characterRef(iterator_t s, iterator_t e, int base);

  // Start grammar definition
  rule_t prolog, element, Misc, Reference,
                CDSect, CDStart, CData, CDEnd, 
                PI, PITarget, PIData,
                doctypedecl, XMLDecl, SDDecl, VersionInfo, EncodingDecl,
                VersionNum, Eq, EmptyElemTag, STag, content, ETag, Attribute,
                AttValue, CharData, Comment, 
                CharRef, EntityRef, EncName, document_,
                Name, Comment1, Spaces;

  stringT str(iterator_t s, iterator_t e, int trim = 0);

  //////////////////////////////
  // member variables
  EntityResolverT* entityResolver_;
  DTDHandlerT* dtdHandler_;
  ContentHandlerT* contentHandler_;
  ErrorHandler* errorHandler_;

  std::stack<stringT> elements_;
  AttributesImplT attrs_;
  AttributesImplT::Attr currentAttr_;
  stringT piTarget_;
  stringT piData_;
  stringT entityRef_;
  std::map<stringT, stringT> declaredEntities_;
  std::map<char, int> conversion_;
}; // parser

template<class string_type>
Garden<string_type>::Garden() :
  entityResolver_(0),
  dtdHandler_(0),
  contentHandler_(0),
  errorHandler_(0)
{
  // define the parsing rules
  typedef boost::spirit::chset<char_t> chset_t;
  typedef boost::spirit::chlit<char_t> chlit_t;

  // characters
  chset_t Char("\x9\xA\xD\x20-\xFF");
  chset_t SpaceChar("\x20\x9\xD\xA");
  Spaces = +(SpaceChar);
  chset_t Letter("\x41-\x5A\x61-\x7A\xC0-\xD6\xD8-\xF6\xF8-\xFF");
  chset_t Digit("0-9");
  chlit_t Extender('\xB7');
  chset_t NameChar = Letter | Digit | chset_t("._:-") | Extender;
  Name = (Letter | '_' | ':') >> *(NameChar);

  document_ = prolog >> element >> *Misc;

  chset_t CharDataChar (boost::spirit::anychar_p - (chset_t('<') | chset_t('&')));
  CharData = (*(CharDataChar - boost::spirit::str_p("]]>")))[boost::bind(&Garden<string_type>::elementContent, this, _1, _2)];

  // Section 2.5 - Comments
  Comment =        boost::spirit::str_p("<!--") >> Comment1 >> boost::spirit::str_p("-->");
  Comment1 = *((Char - boost::spirit::ch_p('-')) | (boost::spirit::ch_p('-') >> (Char - boost::spirit::ch_p('-'))));
 
  // Section 2.6 - Processing Instructions
  PI = boost::spirit::str_p("<?") >> (PITarget)[boost::bind(&Garden<string_type>::piTarget, this, _1, _2)] >> !Spaces >> (PIData)[boost::bind(&Garden<string_type>::piData, this, _1, _2)] >> (boost::spirit::str_p("?>"))[boost::bind(&Garden<string_type>::piEnd, this, _1, _2)];
  PITarget = Name - boost::spirit::as_lower_d[boost::spirit::str_p("xml")];
  PIData = !(!Spaces >> (*(Char - boost::spirit::str_p("?>"))));

  // Section 2.7 - CDATA
  CDSect  = CDStart >> (CData)[boost::bind(&Garden<string_type>::elementContent, this, _1, _2)] >> CDEnd;
  CDStart = boost::spirit::str_p("<![CDATA[");
  CData   = *(Char - boost::spirit::str_p("]]>"));
  CDEnd   = boost::spirit::str_p("]]>");

  // bits before the root elemenet
  prolog = !XMLDecl >> *Misc >> !(doctypedecl >> *Misc);
  XMLDecl = boost::spirit::str_p("<?xml") >> VersionInfo >> !EncodingDecl >> !SDDecl >> !Spaces >> boost::spirit::str_p("?>");
  VersionInfo = Spaces >> boost::spirit::str_p("version") >> Eq >> (boost::spirit::ch_p('\'') >> VersionNum >>'\''
                          | boost::spirit::ch_p('"') >> VersionNum >> '"');
  chset_t VersionNumCh("A-Za-z0-9_.:-");
  VersionNum =    +(VersionNumCh);
  doctypedecl =    boost::spirit::str_p("<!DOCTYPE") >> *(Char - (chset_t('[') | '>')) >> !('[' >> *(Char - ']') >> ']') >> '>';
  SDDecl =            Spaces >> boost::spirit::str_p("standalone") >> Eq >> ((boost::spirit::ch_p('\'') >> (boost::spirit::str_p("yes") | boost::spirit::str_p("no")) >> '\'')
                          | (boost::spirit::ch_p('"') >> (boost::spirit::str_p("yes") | boost::spirit::str_p("no")) >> '"'));

  // odd bits
  Eq =                !Spaces >> '=' >> !Spaces;
  Misc =            Comment | Spaces | PI;

  // Elements
  element = STag >> (EmptyElemTag | (boost::spirit::str_p(">"))[boost::bind(&Garden<string_type>::closeElement, this, _1, _2)] >> content >> ETag);
  STag = '<' >> (Name)[boost::bind(&Garden<string_type>::openElement, this, _1, _2)] >> *(Spaces >> Attribute) >> !Spaces;
  Attribute = (Name)[boost::bind(&Garden<string_type>::attributeName, this, _1, _2)] >> Eq >> AttValue;
  EmptyElemTag = (boost::spirit::str_p("/>"))[boost::bind(&Garden<string_type>::closeEmptyElement, this, _1, _2)];
  ETag = (boost::spirit::str_p("</") >> (Name)[boost::bind(&Garden<string_type>::endElementName, this, _1, _2)] >> !Spaces >> '>')[boost::bind(&Garden<string_type>::endElement, this, _1, _2)];
  
  AttValue =   '"' >> (*((boost::spirit::anychar_p - (chset_t('<') | '&' | '"')) | Reference))[boost::bind(&Garden<string_type>::attributeValue, this, _1, _2)] >> '"'
            | '\'' >> (*((boost::spirit::anychar_p - (chset_t('<') | '&' | '\'')) | Reference))[boost::bind(&Garden<string_type>::attributeValue, this, _1, _2)] >> '\'';
  
  content =        !CharData >> *((element | Reference | CDSect | Comment | PI) >> !CharData);

  // Section 4.1 - Character and entity references
  CharRef = boost::spirit::str_p("&#") >> (+boost::spirit::digit_p >> ';')[boost::bind(&Garden<string_type>::decimalCharacterRef, this, _1, _2)] |
            boost::spirit::str_p("&#x") >> (+boost::spirit::xdigit_p >> ';')[boost::bind(&Garden<string_type>::hexCharacterRef, this, _1, _2)];
  Reference = EntityRef | CharRef;
  EntityRef = '&' >> (Name >> boost::spirit::ch_p(';'))[boost::bind(&Garden<string_type>::entityRef, this, _1, _2)];

  EncodingDecl =    Spaces >> boost::spirit::str_p("encoding") >> Eq >> (boost::spirit::ch_p('"') >> EncName >> '"' |
                          boost::spirit::ch_p('\'') >> EncName >> '\'');
  chset_t EncNameCh = VersionNumCh - chset_t(':');
  EncName =        boost::spirit::alpha_p >> *(EncNameCh);


  /////////////////
  declaredEntities_.insert(std::make_pair<stringT, stringT>("lt", "<"));
  declaredEntities_.insert(std::make_pair<stringT, stringT>("gt", ">"));
  declaredEntities_.insert(std::make_pair<stringT, stringT>("amp", "&"));
  declaredEntities_.insert(std::make_pair<stringT, stringT>("apos", "'"));
  declaredEntities_.insert(std::make_pair<stringT, stringT>("quot", "\""));

  conversion_.insert(std::make_pair('0', 0));
  conversion_.insert(std::make_pair('1', 1));
  conversion_.insert(std::make_pair('2', 2));
  conversion_.insert(std::make_pair('3', 3));
  conversion_.insert(std::make_pair('4', 4));
  conversion_.insert(std::make_pair('5', 5));
  conversion_.insert(std::make_pair('6', 6));
  conversion_.insert(std::make_pair('7', 7));
  conversion_.insert(std::make_pair('8', 8));
  conversion_.insert(std::make_pair('9', 9));
  conversion_.insert(std::make_pair('a', 10));
  conversion_.insert(std::make_pair('b', 11));
  conversion_.insert(std::make_pair('c', 12));
  conversion_.insert(std::make_pair('d', 13));
  conversion_.insert(std::make_pair('e', 14));
  conversion_.insert(std::make_pair('f', 15));
  conversion_.insert(std::make_pair('A', 10));
  conversion_.insert(std::make_pair('B', 11));
  conversion_.insert(std::make_pair('C', 12));
  conversion_.insert(std::make_pair('D', 13));
  conversion_.insert(std::make_pair('E', 14));
  conversion_.insert(std::make_pair('F', 15));
} // XMLparser

//////////////////////////////////////
// features
template<class string_type>
bool Garden<string_type>::getFeature(const stringT& name) const
{
  throw SAXNotRecognizedException(name);
} // getFeature

template<class string_type>
void Garden<string_type>::setFeature(const stringT& name, bool value)
{
  throw SAXNotRecognizedException(name);
} // setFeature

///////////////////////////////////////
// properties
template<class string_type>
std::auto_ptr<Garden<string_type>::PropertyBase> Garden<string_type>::doGetProperty(const stringT& name)
{
  throw SAXNotRecognizedException(name);
} // doGetProperty

template<class string_type>
void Garden<string_type>::doSetProperty(const stringT& name, std::auto_ptr<Garden<string_type>::PropertyBase> value)
{
  throw SAXNotRecognizedException(name);
} // doSetProperty

//////////////////////////////////////////
// parse
template<class string_type>
void Garden<string_type>::parse(InputSourceT& input)
{
  InputSourceResolver is(input, default_string_adaptor<stringT>());
	if(is.resolve() == 0)
  {
    reportError("Could not resolve XML document", true);
		return;
  } // if(is.resolver() == 0)

  // Turn of white space skipping on the stream
  is.resolve()->unsetf(std::ios::skipws);

  vector_t data(std::istream_iterator<char_t>(*is.resolve()), std::istream_iterator<char_t>());

  iterator_t first = data.begin();
  iterator_t last = data.end();
  scanner_t scanner(first, last);
  rule_t rool = boost::spirit::real_p;

  if(contentHandler_)
    contentHandler_->startDocument();
  rule_t::result_t r = document_.parse(scanner);
  if(contentHandler_)
    contentHandler_->endDocument();

  if(!(r && first == last))
  {
    std::cout << input.getSystemId() << " Fails Parsing\n" << std::endl;
    for (int i = 0; i < 50; ++i)
    {
        std::cout << *first++;
    }
    std::cout << std::endl;
  } // if ...
} // parse

template<class string_type>
void Garden<string_type>::openElement(iterator_t s, iterator_t e)
{
  elements_.push(str(s, e));
  attrs_.clear();
} // openElement

template<class string_type>
void Garden<string_type>::closeElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->startElement("", elements_.top(), "", attrs_);
} // closeElement

template<class string_type>
void Garden<string_type>::closeEmptyElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
  {
    contentHandler_->startElement("", elements_.top(), "", attrs_);
    contentHandler_->endElement("", elements_.top(), "");
    elements_.pop();
  } // if ...
} // closeEmptyElement

template<class string_type>
void Garden<string_type>::endElementName(iterator_t s, iterator_t e)
{
  stringT name = str(s, e);
  if(name != elements_.top())
    reportError("Expect end element " + elements_.top(), true);
} // endElementName

template<class string_type>
void Garden<string_type>::endElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->endElement("", elements_.top(), "");
  elements_.pop();
} // endElement

template<class string_type>
void Garden<string_type>::attributeName(iterator_t s, iterator_t e)
{
  currentAttr_ = AttributesImplT::Attr();
  currentAttr_.localName_ = str(s, e);
} // attributeName

template<class string_type>
void Garden<string_type>::attributeValue(iterator_t s, iterator_t e)
{
  currentAttr_.value_ = str(s, e);
  currentAttr_.type_ = "CDATA";
  attrs_.addAttribute(currentAttr_);
} // attributeValue

template<class string_type>
void Garden<string_type>::elementContent(iterator_t s, iterator_t e)
{
  if(contentHandler_ && (s != e))
    contentHandler_->characters(str(s, e));
} // Garden<string_type>::elementContent
  
// processing instructions
template<class string_type>
void Garden<string_type>::piTarget(iterator_t s, iterator_t e)
{
  piTarget_ = str(s, e);
  piData_.erase();
} // piTarget

template<class string_type>
void Garden<string_type>::piData(iterator_t s, iterator_t e)
{
  piData_ = str(s, e);
} // piData

template<class string_type>
void Garden<string_type>::piEnd(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->processingInstruction(piTarget_, piData_);
} // piEnd

//entity refs
template<class string_type>
void Garden<string_type>::entityRef(iterator_t s, iterator_t e)
{
  if(contentHandler_)
  {
    stringT name(str(s, e, 1));

    std::map<stringT, stringT>::iterator ent = declaredEntities_.find(name);
    if(ent != declaredEntities_.end())
    { 
      contentHandler_->characters((*ent).second);
      return;
    } 
    else
    {
      reportError("Undeclared entity " + name);
      return;
    } // if ...

    contentHandler_->skippedEntity(name);
  } // if ... 
} // entityRef
  
template<class string_type>
void Garden<string_type>::decimalCharacterRef(iterator_t s, iterator_t e)
{
  characterRef(s, e, 10);
} // decimalCharacterRef

template<class string_type>
void Garden<string_type>::hexCharacterRef(iterator_t s, iterator_t e)
{
  characterRef(s, e, 16);
} // hexCharacterRef

template<class string_type>
void Garden<string_type>::characterRef(iterator_t s, iterator_t e, int base)
{
  if(!contentHandler_)
    return;

  int val = 0;
  char next = *s;
  while(++s != e)
  {
    val *= base;
    val += conversion_[next];
    next = *s;
  } 

  contentHandler_->characters(stringT(1, val));
} // characterRef

///////////////////////////////  
template<class string_type>
Garden<string_type>::stringT Garden<string_type>::str(iterator_t s, iterator_t e, int trim)
{
  stringT str;
  std::copy(s, e, std::inserter(str, str.begin()));
  if(trim)
    str.erase(str.end() - trim);
  return str;
} // str

template<class string_type>
void Garden<string_type>::reportError(const std::string& message, bool fatal)
{
  if(!errorHandler_)
    return;
  
  SAX::basic_SAXParseException<stringT> e(message);

  if(fatal)
    errorHandler_->fatalError(e);
  else
    errorHandler_->error(e);
} // reportError

} // namespace SAX

#endif
