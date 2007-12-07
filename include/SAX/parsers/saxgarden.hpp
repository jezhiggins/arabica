#ifndef ARABICA_GARDEN_H
#define ARABICA_GARDEN_H

#include <SAX/ArabicaConfig.hpp>
#include <boost/spirit.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <SAX/XMLReader.hpp>
#include <SAX/SAXParseException.hpp>
#include <SAX/SAXNotRecognizedException.hpp>
#include <SAX/helpers/InputSourceResolver.hpp>
#include <SAX/helpers/AttributesImpl.hpp>
#include <Arabica/StringAdaptor.hpp>
#include <Arabica/getparam.hpp>

namespace Arabica 
{
namespace SAX 
{

template<class string_type, 
         class T0 = Arabica::nil_t,
         class T1 = Arabica::nil_t>
class Garden : public XMLReaderInterface<string_type, T0, T1>
{
public:
  typedef XMLReaderInterface<string_type, T0, T1> XMLReaderT;
  typedef typename XMLReaderT::string_adaptor string_adaptor;
  typedef EntityResolver<string_type, string_adaptor> EntityResolverT;
  typedef DTDHandler<string_type, string_adaptor> DTDHandlerT;
  typedef ContentHandler<string_type, string_adaptor> ContentHandlerT;
  typedef InputSource<string_type, string_adaptor> InputSourceT;
  typedef AttributesImpl<string_type, string_adaptor> AttributesImplT;
  typedef ErrorHandler<string_type, string_adaptor> ErrorHandlerT;
  typedef DeclHandler<string_type, string_adaptor> declHandlerT;
  typedef LexicalHandler<string_type, string_adaptor> lexicalHandlerT;
  typedef typename XMLReaderT::PropertyBase PropertyBase;

  Garden();

  virtual bool getFeature(const string_type& name) const;
  virtual void setFeature(const string_type& name, bool value);

  virtual void setEntityResolver(EntityResolverT& resolver) { entityResolver_ = &resolver; }
  virtual EntityResolverT* getEntityResolver() const { return entityResolver_; }
  virtual void setDTDHandler(DTDHandlerT& handler) { dtdHandler_ = &handler; }
  virtual DTDHandlerT* getDTDHandler() const { return dtdHandler_; }
  virtual void setContentHandler(ContentHandlerT& handler) { contentHandler_ = &handler; }
  virtual ContentHandlerT* getContentHandler() const { return contentHandler_; }
  virtual void setErrorHandler(ErrorHandlerT& handler) { errorHandler_ = &handler; }
  virtual ErrorHandlerT* getErrorHandler() const { return errorHandler_; }
  virtual void setDeclHandler(declHandlerT& handler) { throw SAXNotSupportedException("decl-handler"); }
  virtual declHandlerT* getDeclHandler() const { throw SAXNotSupportedException("decl-handler"); }
  virtual void setLexicalHandler(lexicalHandlerT& handler) { throw SAXNotSupportedException("lexical-handler"); }
  virtual lexicalHandlerT* getLexicalHandler() const { throw SAXNotSupportedException("lexical-handler"); }

  virtual void parse(InputSourceT& input);

  virtual std::auto_ptr<PropertyBase> doGetProperty(const string_type& name);
  virtual void doSetProperty(const string_type& name, std::auto_ptr<PropertyBase> value);

private:
  void reportError(const std::string& message, bool fatal = false);

  typedef typename string_adaptor::value_type char_t;
  typedef std::vector<char_t> vector_t;
  typedef typename vector_t::iterator iterator_t;
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

  string_type str(iterator_t s, iterator_t e, int trim = 0)
  {
    return string_adaptor::construct(s, e-trim);
  } // str

  //////////////////////////////
  // member variables
  EntityResolverT* entityResolver_;
  DTDHandlerT* dtdHandler_;
  ContentHandlerT* contentHandler_;
  ErrorHandlerT* errorHandler_;

  std::stack<string_type> elements_;
  AttributesImplT attrs_;
  typedef typename AttributesImplT::Attr Attr;
  Attr currentAttr_;
  string_type piTarget_;
  string_type piData_;
  string_type entityRef_;
  std::map<string_type, string_type> declaredEntities_;
  std::map<char, int> conversion_;
}; // parser

template<class string_type, class T0, class T1>
Garden<string_type, T0, T1>::Garden() :
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
  CharData = (*(CharDataChar - boost::spirit::str_p("]]>")))[boost::bind(&Garden<string_type, T0, T1>::elementContent, this, _1, _2)];

  // Section 2.5 - Comments
  Comment =        boost::spirit::str_p("<!--") >> Comment1 >> boost::spirit::str_p("-->");
  Comment1 = *((Char - boost::spirit::ch_p('-')) | (boost::spirit::ch_p('-') >> (Char - boost::spirit::ch_p('-'))));
 
  // Section 2.6 - Processing Instructions
  PI = boost::spirit::str_p("<?") >> (PITarget)[boost::bind(&Garden<string_type, T0, T1>::piTarget, this, _1, _2)] >> !Spaces >> (PIData)[boost::bind(&Garden<string_type, T0, T1>::piData, this, _1, _2)] >> (boost::spirit::str_p("?>"))[boost::bind(&Garden<string_type, T0, T1>::piEnd, this, _1, _2)];
  PITarget = Name - boost::spirit::as_lower_d[boost::spirit::str_p("xml")];
  PIData = !(!Spaces >> (*(Char - boost::spirit::str_p("?>"))));

  // Section 2.7 - CDATA
  CDSect  = CDStart >> (CData)[boost::bind(&Garden<string_type, T0, T1>::elementContent, this, _1, _2)] >> CDEnd;
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
  element = STag >> (EmptyElemTag | (boost::spirit::str_p(">"))[boost::bind(&Garden<string_type, T0, T1>::closeElement, this, _1, _2)] >> content >> ETag);
  STag = '<' >> (Name)[boost::bind(&Garden<string_type, T0, T1>::openElement, this, _1, _2)] >> *(Spaces >> Attribute) >> !Spaces;
  Attribute = (Name)[boost::bind(&Garden<string_type, T0, T1>::attributeName, this, _1, _2)] >> Eq >> AttValue;
  EmptyElemTag = (boost::spirit::str_p("/>"))[boost::bind(&Garden<string_type, T0, T1>::closeEmptyElement, this, _1, _2)];
  ETag = (boost::spirit::str_p("</") >> (Name)[boost::bind(&Garden<string_type, T0, T1>::endElementName, this, _1, _2)] >> !Spaces >> '>')[boost::bind(&Garden<string_type, T0, T1>::endElement, this, _1, _2)];
  
  AttValue =   '"' >> (*((boost::spirit::anychar_p - (chset_t('<') | '&' | '"')) | Reference))[boost::bind(&Garden<string_type, T0, T1>::attributeValue, this, _1, _2)] >> '"'
            | '\'' >> (*((boost::spirit::anychar_p - (chset_t('<') | '&' | '\'')) | Reference))[boost::bind(&Garden<string_type, T0, T1>::attributeValue, this, _1, _2)] >> '\'';
  
  content =        !CharData >> *((element | Reference | CDSect | Comment | PI) >> !CharData);

  // Section 4.1 - Character and entity references
  CharRef = boost::spirit::str_p("&#") >> (+boost::spirit::digit_p >> ';')[boost::bind(&Garden<string_type, T0, T1>::decimalCharacterRef, this, _1, _2)] |
            boost::spirit::str_p("&#x") >> (+boost::spirit::xdigit_p >> ';')[boost::bind(&Garden<string_type, T0, T1>::hexCharacterRef, this, _1, _2)];
  Reference = EntityRef | CharRef;
  EntityRef = '&' >> (Name >> boost::spirit::ch_p(';'))[boost::bind(&Garden<string_type, T0, T1>::entityRef, this, _1, _2)];

  EncodingDecl =    Spaces >> boost::spirit::str_p("encoding") >> Eq >> (boost::spirit::ch_p('"') >> EncName >> '"' |
                          boost::spirit::ch_p('\'') >> EncName >> '\'');
  chset_t EncNameCh = VersionNumCh - chset_t(':');
  EncName =        boost::spirit::alpha_p >> *(EncNameCh);


  /////////////////
  declaredEntities_.insert(std::make_pair<string_type, string_type>(string_adaptor::construct("lt"), string_adaptor::construct("<")));
  declaredEntities_.insert(std::make_pair<string_type, string_type>(string_adaptor::construct("gt"), string_adaptor::construct(">")));
  declaredEntities_.insert(std::make_pair<string_type, string_type>(string_adaptor::construct("amp"), string_adaptor::construct("&")));
  declaredEntities_.insert(std::make_pair<string_type, string_type>(string_adaptor::construct("apos"), string_adaptor::construct("'")));
  declaredEntities_.insert(std::make_pair<string_type, string_type>(string_adaptor::construct("quot"), string_adaptor::construct("\"")));

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
template<class string_type, class T0, class T1>
bool Garden<string_type, T0, T1>::getFeature(const string_type& name) const
{
  throw SAXNotRecognizedException(string_adaptor::asStdString(name));
} // getFeature

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::setFeature(const string_type& name, bool value)
{
  throw SAXNotRecognizedException(string_adaptor::asStdString(name));
} // setFeature

///////////////////////////////////////
// properties
template<class string_type, class T0, class T1>
std::auto_ptr<typename Garden<string_type, T0, T1>::PropertyBase> Garden<string_type, T0, T1>::doGetProperty(const string_type& name)
{
  throw SAXNotRecognizedException(string_adaptor::asStdString(name));
} // doGetProperty

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::doSetProperty(const string_type& name, std::auto_ptr<typename XMLReaderInterface<string_type, T0, T1>::PropertyBase> value)
{
  throw SAXNotRecognizedException(string_adaptor::asStdString(name));
} // doSetProperty

//////////////////////////////////////////
// parse
template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::parse(InputSourceT& input)
{
  InputSourceResolver is(input, string_adaptor());
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
  typedef typename boost::spirit::parser_result<rule_t, scanner_t>::type result_t;

  if(contentHandler_)
    contentHandler_->startDocument();
  result_t r = document_.parse(scanner);
  if(contentHandler_)
    contentHandler_->endDocument();

  if(!(r && first == last))
  {
    std::cout << string_adaptor::asStdString(input.getSystemId()) << " Fails Parsing\n" << std::endl;
    for (int i = 0; i < 50; ++i)
    {
        std::cout << *first++;
    }
    std::cout << std::endl;
  } // if ...
} // parse

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::openElement(iterator_t s, iterator_t e)
{
  elements_.push(str(s, e));
  attrs_.clear();
} // openElement

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::closeElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->startElement(string_adaptor::empty_string(), elements_.top(), string_adaptor::empty_string(), attrs_);
} // closeElement

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::closeEmptyElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
  {
    contentHandler_->startElement(string_adaptor::empty_string(), elements_.top(), string_adaptor::empty_string(), attrs_);
    contentHandler_->endElement(string_adaptor::empty_string(), elements_.top(), string_adaptor::empty_string());
    elements_.pop();
  } // if ...
} // closeEmptyElement

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::endElementName(iterator_t s, iterator_t e)
{
  string_type name = str(s, e);
  if(name != elements_.top())
    reportError("Expect end element " + string_adaptor::asStdString(elements_.top()), true);
} // endElementName

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::endElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->endElement(string_adaptor::empty_string(), elements_.top(), string_adaptor::empty_string());
  elements_.pop();
} // endElement

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::attributeName(iterator_t s, iterator_t e)
{
  currentAttr_ = typename AttributesImplT::Attr();
  currentAttr_.localName_ = str(s, e);
} // attributeName

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::attributeValue(iterator_t s, iterator_t e)
{
  currentAttr_.value_ = str(s, e);
  currentAttr_.type_ = Attributes<string_type, string_adaptor>::Type::CDATA;
  attrs_.addAttribute(currentAttr_);
} // attributeValue

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::elementContent(iterator_t s, iterator_t e)
{
  if(contentHandler_ && (s != e))
    contentHandler_->characters(str(s, e));
} // Garden<string_type, T0, T1>::elementContent
  
// processing instructions
template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::piTarget(iterator_t s, iterator_t e)
{
  piTarget_ = str(s, e);
  piData_ = string_adaptor::empty_string();
} // piTarget

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::piData(iterator_t s, iterator_t e)
{
  piData_ = str(s, e);
} // piData

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::piEnd(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->processingInstruction(piTarget_, piData_);
} // piEnd

//entity refs
template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::entityRef(iterator_t s, iterator_t e)
{
  if(contentHandler_)
  {
    string_type name(str(s, e, 1));

    typedef typename std::map<string_type, string_type>::iterator entity_iterator;

    entity_iterator ent = declaredEntities_.find(name);
    if(ent != declaredEntities_.end())
    { 
      contentHandler_->characters((*ent).second);
      return;
    } 
    else
    {
      reportError("Undeclared entity " + string_adaptor::asStdString(name));
      return;
    } // if ...

    contentHandler_->skippedEntity(name);
  } // if ... 
} // entityRef
  
template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::decimalCharacterRef(iterator_t s, iterator_t e)
{
  characterRef(s, e, 10);
} // decimalCharacterRef

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::hexCharacterRef(iterator_t s, iterator_t e)
{
  characterRef(s, e, 16);
} // hexCharacterRef

template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::characterRef(iterator_t s, iterator_t e, int base)
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

  contentHandler_->characters(string_adaptor::construct("?"));//string_type(1, val));
} // characterRef

///////////////////////////////  
template<class string_type, class T0, class T1>
void Garden<string_type, T0, T1>::reportError(const std::string& message, bool fatal)
{
  if(!errorHandler_)
    return;
  
  SAX::SAXParseException<string_type> e(message);

  if(fatal)
    errorHandler_->fatalError(e);
  else
    errorHandler_->error(e);
} // reportError

} // namespace SAX
} // namespace Arabica

#endif
