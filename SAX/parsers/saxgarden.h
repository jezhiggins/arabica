#ifndef saxgarden_h
#define saxgarden_h

#include <boost/spirit/spirit.hpp>
#include <boost/multi_pass.hpp>
#include <string>
#include <stack>
#include <SAX/XMLReader.h>
#include <SAX/SAXParseException.h>
#include <SAX/SAXNotRecognizedException.h>
#include <SAX/helpers/InputSourceResolver.h>
#include <SAX/helpers/StringAdaptor.h>
#include <SAX/helpers/AttributesImpl.h>

namespace SAX {

class Garden : public basic_XMLReader<std::string>
{
public:
  typedef std::string stringT;
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

  typedef unsigned char char_t;
  typedef boost::multi_pass<std::istream_iterator<char_t> > iterator_t;

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


  typedef void(Garden::* xmlp_fn)(iterator_t s, iterator_t e);
  class binder
  {
    public:
      binder(Garden* p, xmlp_fn f) : p_(p), fn_(f) { }

      void operator()(iterator_t str, iterator_t end) const 
      {
        (p_->*fn_)(str, end);
      } // operator()

    private:
      Garden* p_;
      xmlp_fn fn_;
  }; // class binder

  // Start grammar definition
  spirit::rule<iterator_t> prolog, element, Misc, Reference,
                CDSect, CDStart, CData, CDEnd, 
                PI, PITarget, PIData,
                doctypedecl, XMLDecl, SDDecl, VersionInfo, EncodingDecl,
                VersionNum, Eq, EmptyElemTag, STag, content, ETag, Attribute,
                AttValue, CharData, Comment, 
                CharRef, EntityRef, EncName, document_,
                Name, Comment1, S;

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


Garden::Garden() :
  entityResolver_(0),
  dtdHandler_(0),
  contentHandler_(0),
  errorHandler_(0)
{
  // define the parsing rules
  typedef spirit::chset<unsigned char> chset_t;
  typedef spirit::chlit<unsigned char> chlit_t;

  // characters
  chset_t Char("\x9\xA\xD\x20-\xFF");
  chset_t Sch("\x20\x9\xD\xA");
  S = +(Sch);
  chset_t Letter("\x41-\x5A\x61-\x7A\xC0-\xD6\xD8-\xF6\xF8-\xFF");
  chset_t Digit("0-9");
  chlit_t Extender('\xB7');
  chset_t NameChar = Letter | Digit | chset_t("._:-") | Extender;
  Name = (Letter | '_' | ':') >> *(NameChar);

  document_ = prolog >> element >> *Misc;

  chset_t CharDataChar (spirit::anychar - (chset_t('<') | chset_t('&')));
  CharData = (*(CharDataChar - spirit::str_p("]]>")))[binder(this, &Garden::elementContent)];

  // Section 2.5 - Comments
  Comment =        spirit::str_p("<!--") >> Comment1 >> spirit::str_p("-->");
  Comment1 = *((Char - spirit::ch_p('-')) | (spirit::ch_p('-') >> (Char - spirit::ch_p('-'))));
 
  // Section 2.6 - Processing Instructions
  PI = spirit::str_p("<?") >> (PITarget)[binder(this, &Garden::piTarget)] >> !S >> (PIData)[binder(this, &Garden::piData)] >> (spirit::str_p("?>"))[binder(this, &Garden::piEnd)];
  PITarget = Name - spirit::nocase[(spirit::str_p("xml"))];
  PIData = !(!S >> (*(Char - spirit::str_p("?>"))));

  // Section 2.7 - CDATA
  CDSect  = CDStart >> (CData)[binder(this, &Garden::elementContent)] >> CDEnd;
  CDStart = spirit::str_p("<![CDATA[");
  CData   = *(Char - spirit::str_p("]]>"));
  CDEnd   = spirit::str_p("]]>");

  prolog =            !XMLDecl >> *Misc >> !(doctypedecl >> *Misc);
  XMLDecl =        spirit::str_p("<?xml") >> VersionInfo >> !EncodingDecl >> !SDDecl >> !S >> spirit::str_p("?>");
  VersionInfo =    S >> spirit::str_p("version") >> Eq >> (spirit::ch_p('\'') >> VersionNum >>'\''
                          | spirit::ch_p('"') >> VersionNum >> '"');
  Eq =                !S >> '=' >> !S;
  chset_t VersionNumCh("A-Za-z0-9_.:-");
  VersionNum =    +(VersionNumCh);
  Misc =            Comment | S | PI;

  doctypedecl =    spirit::str_p("<!DOCTYPE") >> *(Char - (chset_t('[') | '>')) >> !('[' >> *(Char - ']') >> ']') >> '>';

  SDDecl =            S >> spirit::str_p("standalone") >> Eq >> ((spirit::ch_p('\'') >> (spirit::str_p("yes") | spirit::str_p("no")) >> '\'')
                          | (spirit::ch_p('"') >> (spirit::str_p("yes") | spirit::str_p("no")) >> '"'));

  element = STag >> (EmptyElemTag | (spirit::str_p(">"))[binder(this, &Garden::closeElement)] >> content >> ETag);
  STag = '<' >> (Name)[binder(this, &Garden::openElement)] >> *(S >> Attribute) >> !S;
  Attribute = (Name)[binder(this, &Garden::attributeName)] >> Eq >> AttValue;
  EmptyElemTag = (spirit::str_p("/>"))[binder(this, &Garden::closeEmptyElement)];
  ETag = (spirit::str_p("</") >> (Name)[binder(this, &Garden::endElementName)] >> !S >> '>')[binder(this, &Garden::endElement)];
  
  AttValue =   '"' >> (*((spirit::anychar - (chset_t('<') | '&' | '"')) | Reference))[binder(this, &Garden::attributeValue)] >> '"'
            | '\'' >> (*((spirit::anychar - (chset_t('<') | '&' | '\'')) | Reference))[binder(this, &Garden::attributeValue)] >> '\'';
  
  content =        !CharData >> *((element | Reference | CDSect | Comment | PI) >> !CharData);

  // Section 4.1 - Character and entity references
  CharRef = spirit::str_p("&#") >> (+spirit::digit >> ';')[binder(this, &Garden::decimalCharacterRef)] |
            spirit::str_p("&#x") >> (+spirit::xdigit >> ';')[binder(this, &Garden::hexCharacterRef)];
  Reference = EntityRef | CharRef;
  EntityRef = '&' >> (Name >> spirit::ch_p(';'))[binder(this, &Garden::entityRef)];

  EncodingDecl =    S >> spirit::str_p("encoding") >> Eq >> (spirit::ch_p('"') >> EncName >> '"' |
                          spirit::ch_p('\'') >> EncName >> '\'');
  chset_t EncNameCh = VersionNumCh - chset_t(':');
  EncName =        spirit::alpha >> *(EncNameCh);


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
bool Garden::getFeature(const stringT& name) const
{
  throw SAXNotRecognizedException(name);
} // getFeature

void Garden::setFeature(const stringT& name, bool value)
{
  throw SAXNotRecognizedException(name);
} // setFeature

///////////////////////////////////////
// properties
std::auto_ptr<Garden::PropertyBase> Garden::doGetProperty(const stringT& name)
{
  throw SAXNotRecognizedException(name);
} // doGetProperty

void Garden::doSetProperty(const stringT& name, std::auto_ptr<Garden::PropertyBase> value)
{
  throw SAXNotRecognizedException(name);
} // doSetProperty

//////////////////////////////////////////
// parse
void Garden::parse(InputSourceT& input)
{
  InputSourceResolver is(input, default_string_adaptor<stringT>());
	if(is.resolve() == 0)
  {
    reportError("Could not resolve XML document", true);
		return;
  } // if(is.resolver() == 0)

  // Turn of white space skipping on the stream
  is.resolve()->unsetf(std::ios::skipws);

  iterator_t first = boost::make_multi_pass(std::istream_iterator<char_t>(*is.resolve()));
  iterator_t last = boost::make_multi_pass(std::istream_iterator<char_t>());

  if(contentHandler_)
    contentHandler_->startDocument();
  spirit::match m = document_.parse(first, last);
  if(contentHandler_)
    contentHandler_->endDocument();

  if(!(m && first == last))
  {
    std::cout << input.getSystemId() << " Fails Parsing\n" << std::endl;
    for (int i = 0; i < 50; ++i)
    {
        std::cout << *first++;
    }
    std::cout << std::endl;
  } // if ...
} // parse

void Garden::openElement(iterator_t s, iterator_t e)
{
  elements_.push(str(s, e));
  attrs_.clear();
} // openElement

void Garden::closeElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->startElement("", elements_.top(), "", attrs_);
} // closeElement

void Garden::closeEmptyElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
  {
    contentHandler_->startElement("", elements_.top(), "", attrs_);
    contentHandler_->endElement("", elements_.top(), "");
    elements_.pop();
  } // if ...
} // closeEmptyElement

void Garden::endElementName(iterator_t s, iterator_t e)
{
  stringT name = str(s, e);
  if(name != elements_.top())
    reportError("Expect end element " + elements_.top(), true);
} // endElementName

void Garden::endElement(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->endElement("", elements_.top(), "");
  elements_.pop();
} // endElement

void Garden::attributeName(iterator_t s, iterator_t e)
{
  currentAttr_ = AttributesImplT::Attr();
  currentAttr_.localName_ = str(s, e);
} // attributeName

void Garden::attributeValue(iterator_t s, iterator_t e)
{
  currentAttr_.value_ = str(s, e);
  currentAttr_.type_ = "CDATA";
  attrs_.addAttribute(currentAttr_);
} // attributeValue

void Garden::elementContent(iterator_t s, iterator_t e)
{
  if(contentHandler_ && (s != e))
    contentHandler_->characters(str(s, e));
} // Garden::elementContent

// processing instructions
void Garden::piTarget(iterator_t s, iterator_t e)
{
  piTarget_ = str(s, e);
  piData_.erase();
} // piTarget

void Garden::piData(iterator_t s, iterator_t e)
{
  piData_ = str(s, e);
} // piData

void Garden::piEnd(iterator_t s, iterator_t e)
{
  if(contentHandler_)
    contentHandler_->processingInstruction(piTarget_, piData_);
} // piEnd

//entity refs
void Garden::entityRef(iterator_t s, iterator_t e)
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
  
void Garden::decimalCharacterRef(iterator_t s, iterator_t e)
{
  characterRef(s, e, 10);
} // decimalCharacterRef

void Garden::hexCharacterRef(iterator_t s, iterator_t e)
{
  characterRef(s, e, 16);
} // hexCharacterRef

void Garden::characterRef(iterator_t s, iterator_t e, int base)
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
Garden::stringT Garden::str(iterator_t s, iterator_t e, int trim)
{
  stringT str;
  std::copy(s, e, std::inserter(str, str.begin()));
  if(trim)
    str.erase(str.end() - trim);
  return str;
} // str

void Garden::reportError(const std::string& message, bool fatal)
{
  if(!errorHandler_)
    return;
  
  SAX::SAXException e(message);

  if(fatal)
    errorHandler_->fatalError(e);
  else
    errorHandler_->error(e);
} // reportError


} // namespace SAX

#endif
