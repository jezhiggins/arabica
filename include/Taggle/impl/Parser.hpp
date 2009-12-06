#ifndef ARABICA_SAX_TAGGLE_PARSER_HPP
#define ARABICA_SAX_TAGGLE_PARSER_HPP


#include <map>
#include <vector>
#include <SAX/helpers/DefaultHandler.hpp>
#include <SAX/XMLReader.hpp>
#include <SAX/helpers/InputSourceResolver.hpp>
#include <text/normalize_whitespace.hpp>
#include <XML/XMLCharacterClasses.hpp>
#include <io/uri.hpp>
#include "ScanHandler.hpp"

namespace Arabica
{

namespace SAX
{

/**
The Taggle SAX parser class.

Based on code from John Cowan's super TagSoup package
**/
template<class string_type, 
         class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
class Taggle  : 
    public XMLReaderInterface<string_type, string_adaptor_type>,
    private DefaultHandler<string_type, string_adaptor_type>,
    private ScanHandler
{
public:
  typedef XMLReaderInterface<string_type, string_adaptor_type> XMLReaderT;
  typedef typename XMLReaderT::string_adaptor string_adaptor;
  typedef ContentHandler<string_type, string_adaptor> ContentHandlerT;
  typedef LexicalHandler<string_type, string_adaptor> LexicalHandlerT;
  typedef DeclHandler<string_type, string_adaptor> DeclHandlerT;
  typedef DTDHandler<string_type, string_adaptor> DTDHandlerT;
  typedef ErrorHandler<string_type, string_adaptor> ErrorHandlerT;
  typedef EntityResolver<string_type, string_adaptor> EntityResolverT;
  typedef InputSource<string_type, string_adaptor> InputSourceT;
  typedef Locator<string_type, string_adaptor> LocatorT;


  /**
  A value of "true" indicates namespace URIs and unprefixed local
  names for element and attribute names will be available.
  **/
  static const string_type namespacesFeature;

  /**
  A value of "true" indicates that XML qualified names (with prefixes)
  and attributes (including xmlns* attributes) will be available.
  We don't support this value.
  **/
  static const string_type namespacePrefixesFeature;

  /**
  Reports whether this parser processes external general entities
  (it doesn't).
  **/
  static const string_type externalGeneralEntitiesFeature;

  /**
  Reports whether this parser processes external parameter entities
  (it doesn't).
  **/
  static const string_type externalParameterEntitiesFeature;

  /**
  May be examined only during a parse, after the startDocument()
  callback has been completed; read-only. The value is true if
  the document specified standalone="yes" in its XML declaration,
  and otherwise is false.  (It's always false.)
  **/
  static const string_type isStandaloneFeature;

  /**
  A value of "true" indicates that the LexicalHandler will report
  the beginning and end of parameter entities (it won't).
  **/
  static const string_type lexicalHandlerParameterEntitiesFeature;

  /**
  A value of "true" indicates that system IDs in declarations will
  be absolutized (relative to their base URIs) before reporting.
  (This returns true but doesn't actually do anything.)
  **/
  static const string_type resolveDTDURIsFeature;

  /**
  Has a value of "true" if all XML names (for elements,
  prefixes, attributes, entities, notations, and local
  names), as well as Namespace URIs, will have been interned
  using java.lang.String.intern. This supports fast testing of
  equality/inequality against string constants, rather than forcing
  slower calls to String.equals().  (We always intern.)
  **/
  static const string_type stringInterningFeature;

  /**
  Returns "true" if the Attributes objects passed by this
  parser in ContentHandler.startElement() implement the
  org.xml.sax.ext.Attributes2 interface.  (They don't.)
  **/
  static const string_type useAttributes2Feature;

  /**
  Returns "true" if the Locator objects passed by this parser
  in ContentHandler.setDocumentLocator() implement the
  org.xml.sax.ext.Locator2 interface.  (They don't.)
  **/
  static const string_type useLocator2Feature;

  /**
  Returns "true" if, when setEntityResolver is given an object
  implementing the org.xml.sax.ext.EntityResolver2 interface,
  those new methods will be used.  (They won't be.)
  **/
  static const string_type useEntityResolver2Feature;

  /**
  Controls whether the parser is reporting all validity errors
  (We don't report any validity errors.)
  **/
  static const string_type validationFeature;

  /**
  Controls whether the parser reports Unicode normalization
  errors as described in section 2.13 and Appendix B of the XML
  1.1 Recommendation.  (We don't normalize.)
  **/
  static const string_type unicodeNormalizationCheckingFeature;

  /**
  Controls whether, when the namespace-prefixes feature is set,
  the parser treats namespace declaration attributes as being in
  the http://www.w3.org/2000/xmlns/ namespace.  (It doesn't.)
  **/
  static const string_type xmlnsURIsFeature;

  /**
  Returns "true" if the parser supports both XML 1.1 and XML 1.0.
  (Always false.)
  **/
  static const string_type XML11Feature;

  /**
  A value of "true" indicates that the parser will ignore
  unknown elements.
  **/
  static const string_type ignoreBogonsFeature;

  /**
  A value of "true" indicates that the parser will give unknown
  elements a content model of EMPTY; a value of "false", a
  content model of ANY.
  **/
  static const string_type bogonsEmptyFeature;

  /**
  A value of "true" indicates that the parser will allow unknown
  elements to be the root element.
  **/
  static const string_type rootBogonsFeature;

  /**
  A value of "true" indicates that the parser will return default
  attribute values for missing attributes that have default values.
  **/
  static const string_type defaultAttributesFeature;

  /**
  A value of "true" indicates that the parser will 
  translate colons into underscores in names.
  **/
  static const string_type translateColonsFeature;

  /**
  A value of "true" indicates that the parser will 
  attempt to restart the restartable elements.
  **/
  static const string_type restartElementsFeature;

  /**
  A value of "true" indicates that the parser will 
  transmit whitespace in element-only content via the SAX
  ignorableWhitespace callback.  Normally this is not done,
  because HTML is an SGML application and SGML suppresses
  such whitespace.
  **/
  static const string_type ignorableWhitespaceFeature;

  /**
  A value of "true" indicates that the parser will treat CDATA
  elements specially.  Normally true, since the input is by
  default HTML.
  **/
  static const string_type CDATAElementsFeature;

  /**
  Used to see some syntax events that are essential in some
  applications: comments, CDATA delimiters, selected general
  entity inclusions, and the start and end of the DTD (and
  declaration of document element name). The Object must implement
  org.xml.sax.ext.LexicalHandler.
  **/
  static const string_type lexicalHandlerProperty;

  /**
  Specifies the Scanner object this Parser uses.
  **/
  static const string_type scannerProperty;

  /**
  Specifies the Schema object this Parser uses.
  **/
  static const string_type schemaProperty;

  /**
  Specifies the AutoDetector (for encoding detection) this Parser uses.
  **/
  static const string_type autoDetectorProperty;

private:
  // Default values for feature flags
  static bool DEFAULT_NAMESPACES;
  static bool DEFAULT_IGNORE_BOGONS;
  static bool DEFAULT_BOGONS_EMPTY;
  static bool DEFAULT_ROOT_BOGONS;
  static bool DEFAULT_DEFAULT_ATTRIBUTES;
  static bool DEFAULT_TRANSLATE_COLONS;
  static bool DEFAULT_RESTART_ELEMENTS;
  static bool DEFAULT_IGNORABLE_WHITESPACE;
  static bool DEFAULT_CDATA_ELEMENTS;

  static const string_type legal;

  typedef std::map<string_type, bool> FeatureMapT;

  // XMLReader implementation
  ContentHandlerT* contentHandler_;
  LexicalHandlerT* lexicalHandler_;
  DTDHandlerT* dtdHandler_;
  ErrorHandlerT* errorHandler_;
  EntityResolverT* entityResolver_;
  Schema* schema_;
  bool ownSchema_;
  Scanner* scanner_;
  bool ownScanner_;
  FeatureMapT features_;
  Element newElement_;
  std::string attributeName_;
  bool doctypeIsPresent_;
  std::string doctypePublicId_;
  std::string doctypeSystemId_;
  std::string doctypeName_;
  std::string piTarget_;
  Element stack_;
  Element saved_;
  Element pcdata_;
  int entity_;

  // Feature flags.  
  bool namespaces;
  bool ignoreBogons;
  bool bogonsEmpty;
  bool rootBogons;
  bool defaultAttributes;
  bool translateColons;
  bool restartElements;
  bool ignorableWhitespace;
  bool CDATAElements;
  bool virginStack;

public:
  Taggle() :
    contentHandler_(0),
    lexicalHandler_(0),
    dtdHandler_(0),
    errorHandler_(0),
    entityResolver_(0),
    schema_(0),
    ownSchema_(false),
    scanner_(0),
    ownScanner_(false),
    features_(initialFeatures()),
    newElement_(Element::Null),
    attributeName_(),
    doctypeIsPresent_(false),
    doctypePublicId_(),
    doctypeSystemId_(),
    doctypeName_(),
    piTarget_(),
    stack_(Element::Null),
    saved_(Element::Null),
    pcdata_(Element::Null),
    entity_(0),
    namespaces(DEFAULT_NAMESPACES),
    ignoreBogons(DEFAULT_IGNORE_BOGONS),
    bogonsEmpty(DEFAULT_BOGONS_EMPTY),
    rootBogons(DEFAULT_ROOT_BOGONS),
    defaultAttributes(DEFAULT_DEFAULT_ATTRIBUTES),
    translateColons(DEFAULT_TRANSLATE_COLONS),
    restartElements(DEFAULT_RESTART_ELEMENTS),
    ignorableWhitespace(DEFAULT_IGNORABLE_WHITESPACE),
    CDATAElements(DEFAULT_CDATA_ELEMENTS),
    virginStack(true)
  {
    contentHandler_ = this;
    lexicalHandler_ = this;
    dtdHandler_ = this;
    errorHandler_ = this;
    entityResolver_ = this;
  } // Taggle

  ~Taggle()
  {
    if(ownSchema_)
      delete schema_;
    if(ownScanner_)
      delete scanner_;
  } // ~Taggle

private:
  static FeatureMapT initialFeatures() 
  {
    FeatureMapT features;
    features[namespacesFeature] = DEFAULT_NAMESPACES;
    features[namespacePrefixesFeature] = false;
    features[externalGeneralEntitiesFeature] = false;
    features[externalParameterEntitiesFeature] = false;
    features[isStandaloneFeature] = false;
    features[lexicalHandlerParameterEntitiesFeature] =  false;
    features[resolveDTDURIsFeature] = true;
    features[stringInterningFeature] = true;
    features[useAttributes2Feature] = false;
    features[useLocator2Feature] = false;
    features[useEntityResolver2Feature] = false;
    features[validationFeature] = false;
    features[xmlnsURIsFeature] = false;
    features[xmlnsURIsFeature] = false;
    features[XML11Feature] = false;
    features[ignoreBogonsFeature] = DEFAULT_IGNORE_BOGONS;
    features[bogonsEmptyFeature] = DEFAULT_BOGONS_EMPTY;
    features[rootBogonsFeature] = DEFAULT_ROOT_BOGONS;
    features[defaultAttributesFeature] = DEFAULT_DEFAULT_ATTRIBUTES;
    features[translateColonsFeature] = DEFAULT_TRANSLATE_COLONS;
    features[restartElementsFeature] = DEFAULT_RESTART_ELEMENTS;
    features[ignorableWhitespaceFeature] = DEFAULT_IGNORABLE_WHITESPACE;
    features[CDATAElementsFeature] = DEFAULT_CDATA_ELEMENTS;
    return features;
  } // initialFeatures

public:
  ///////////////////////////////////////////////////
  // XMLReader
  bool getFeature(const string_type& name) const 
  {
    typename FeatureMapT::const_iterator b = features_.find(name);
    if(b == features_.end()) 
    {
      throw SAXNotRecognizedException("Unknown feature " + string_adaptor::asStdString(name));
    }
    return b->second;
  } // getFeature

  void setFeature(const string_type& name, bool value)
  {
    typename FeatureMapT::iterator b = features_.find(name);
    if(b == features_.end()) 
    {
      throw SAXNotRecognizedException("Unknown feature " + string_adaptor::asStdString(name));
    }

    features_[name] = value;

    if(name == namespacesFeature)
      namespaces = value;
    else if(name == ignoreBogonsFeature) 
      ignoreBogons = value;
    else if(name == bogonsEmptyFeature) 
      bogonsEmpty = value;
    else if(name == rootBogonsFeature) 
      rootBogons = value;
    else if(name == defaultAttributesFeature) 
      defaultAttributes = value;
    else if(name == translateColonsFeature) 
      translateColons = value;
    else if(name == restartElementsFeature) 
      restartElements = value;
    else if(name == ignorableWhitespaceFeature) 
      ignorableWhitespace = value;
    else if(name == CDATAElementsFeature) 
      CDATAElements = value;
  } // setFeature

  typedef typename XMLReaderInterface<string_type, string_adaptor_type>::PropertyBase PropertyBaseT;
  virtual std::auto_ptr<PropertyBaseT> doGetProperty(const string_type& /*name*/)
  {
    return std::auto_ptr<PropertyBaseT>(0);
  } // doGetProperty

  virtual void doSetProperty(const string_type& /*name*/, std::auto_ptr<PropertyBaseT> /*value*/)
  {
  } // doSetProperty

  /*
  Object getProperty (std::string name)
  {
    if(name.equals(lexicalHandlerProperty)) 
    {
      return lexicalHandler_ == this ? null : lexicalHandler_;
    }
    else if(name.equals(scannerProperty)) 
    {
      return scanner_;
    }
    else if(name.equals(schemaProperty)) 
    {
      return schema_;
    }
    else if(name.equals(autoDetectorProperty)) 
    {
      return theAutoDetector;
    }
    else 
    {
      throw new SAXNotRecognizedException("Unknown property " + name);
    }
  } // getProperty

  void setProperty (std::string name, Object value)
  {
    if(name.equals(lexicalHandlerProperty)) 
    {
      if(value == null) 
      {
        lexicalHandler_ = this;
      }
      else if(value instanceof LexicalHandler) 
      {
        lexicalHandler_ = (LexicalHandler)value;
      }
      else 
      {
        throw new SAXNotSupportedException("Your lexical handler is not a LexicalHandler");
      }
    }
    else if(name.equals(scannerProperty)) 
    {
      if(value instanceof Scanner) {
        scanner_ = (Scanner)value;
        }
      else {
        throw new SAXNotSupportedException("Your scanner is not a Scanner");
        }
      }
    else if(name.equals(schemaProperty)) {
      if(value instanceof Schema) {
        schema_ = (Schema)value;
        }
      else {
         throw new SAXNotSupportedException("Your schema is not a Schema");
        }
      }
    else if(name.equals(autoDetectorProperty)) {
      if(value instanceof AutoDetector) {
        theAutoDetector = (AutoDetector)value;
        }
      else {
        throw new SAXNotSupportedException("Your auto-detector is not an AutoDetector");
        }
      }
    else {
      throw new SAXNotRecognizedException("Unknown property " + name);
      }
    }
*/

  virtual void setEntityResolver(EntityResolverT& resolver) 
  {
    entityResolver_ = &resolver;
  } // setEntityResolver

  virtual EntityResolverT* getEntityResolver() const
  {
    return (entityResolver_ == this) ? 0 : entityResolver_;
  } // getEntityResolver

  virtual void setDTDHandler(DTDHandlerT& handler) 
  {
    dtdHandler_ = &handler;
  } // setDTDHandler

  virtual DTDHandlerT* getDTDHandler() const
  {
    return (dtdHandler_ == this) ? 0 : dtdHandler_;
  } // getDTDHandler

  virtual void setContentHandler(ContentHandlerT& handler) 
  {
    contentHandler_ = &handler;
  } // setContentHandler

  virtual ContentHandlerT* getContentHandler() const 
  {
    return (contentHandler_ == this) ? 0 : contentHandler_;
  } // getContentHandler

  virtual void setErrorHandler(ErrorHandlerT& handler) 
  {
    errorHandler_ = &handler;
  } // setErrorHandler

  virtual ErrorHandlerT* getErrorHandler() const
  {
    return (errorHandler_ == this) ? 0 : errorHandler_;
  } // getErrorHandler

  virtual void setDeclHandler(DeclHandlerT& /*handler*/)
  {
  } // setDeclHandler

  virtual DeclHandlerT* getDeclHandler() const
  {
    return 0;
  } // getDeclHandler

  virtual void setLexicalHandler(LexicalHandlerT& handler)
  {
    lexicalHandler_ = &handler;
  } // setLexicalHandler

  virtual LexicalHandlerT* getLexicalHandler() const
  {
    return (lexicalHandler_ == this) ? 0 : lexicalHandler_;
  } // getLexicalHandler

  virtual void parse(InputSourceT& input) 
  {
    setup();

    InputSourceResolver is(input, string_adaptor());
    if(is.resolve() == 0)
    {
      reportError("Could not resolve XML document", true);
      return;
    } // if(is.resolver() == 0)

    contentHandler_->startDocument();
    scanner_->resetDocumentLocator(string_adaptor::asStdString(input.getPublicId()), string_adaptor::asStdString(input.getSystemId()));

    if(dynamic_cast<LocatorT*>(scanner_) != 0) 
      contentHandler_->setDocumentLocator(*(dynamic_cast<LocatorT*>(scanner_)));

    if(schema_->getURI() != "")
      contentHandler_->startPrefixMapping(S(schema_->getPrefix()), 
                                          S(schema_->getURI()));
    scanner_->scan(*is.resolve(), *this);
  } // parse

private:
  // Sets up instance variables that haven't been set by setFeature
  void setup() 
  {
    if(schema_ && ownSchema_)
    {
      delete schema_;
      schema_ = 0;
    } // if ...
    if(schema_ == 0)
    {
      schema_ = new HTMLSchema();
      ownSchema_ = true;
    } // if ...

    if(scanner_ && ownScanner_)
    {
      delete scanner_;
      scanner_ = 0;
    } // if ...
    if(scanner_ == 0) 
    {
      scanner_ = new HTMLScanner();
      ownScanner_ = true;
    } // if ...

    stack_ = Element(schema_->getElementType("<root>"), defaultAttributes);
    pcdata_ = Element(schema_->getElementType("<pcdata>"), defaultAttributes);

    newElement_ = Element::Null;
    attributeName_ = "";
    piTarget_ = "";
    saved_ = Element::Null;
    entity_ = 0;
    virginStack = true;
    doctypeName_ = doctypePublicId_ = doctypeSystemId_ = "";
  } // setup

  ///////////////////////////////////////////////////////
  // ScanHandler implementation
  virtual void adup(const std::string& /*buff*/)
  {
    // std::cerr << "adup(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(newElement_ == Element::Null || attributeName_ == "") 
      return;
    newElement_.setAttribute(attributeName_, "", attributeName_);
    attributeName_ = "";
  } // adup

  virtual void aname(const std::string& buff) 
  {
    // std::cerr << "aname(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(newElement_ == Element::Null) 
      return;
    // Currently we don't rely on Schema to canonicalize
    // attribute names.
    attributeName_ = lower_case(makeName(buff));
  } // aname

  virtual void aval(const std::string& buff) 
  {
    // std::cerr << "aval(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(newElement_ == Element::Null || attributeName_ == "") 
      return;
    std::string value = expandEntities(buff);
    newElement_.setAttribute(attributeName_, "", value);
    attributeName_ = "";
  } // aval

  // Expand entity references in attribute values selectively.
  // Currently we expand a reference iff it is properly terminated
  // with a semicolon.
  std::string expandEntities(std::string src) 
  {
    size_t refStart = std::string::npos;
    std::string dst;
    for(std::string::const_iterator i = src.begin(), ie = src.end(); i != ie; ++i)
    {
      char ch = *i;
      dst.push_back(ch);
      if(ch == '&' && refStart == std::string::npos)
      {
        // start of a ref excluding &
        refStart = dst.length();
      }
      else if(refStart == std::string::npos) 
      {
        // not in a ref
      }
      else if(Arabica::XML::is_letter_or_digit(ch) || ch == '#') 
      {
        // valid entity char
      }
      else if(ch == ';') 
      {
        // properly terminated ref
        int ent = lookupEntity(dst.substr(refStart, dst.size() - refStart - 1));
        if(ent > 0xFFFF) 
        {
          ent -= 0x10000;
          dst[refStart - 1] = (char)((ent>>10) + 0xD800);
          dst[refStart] = (char)((ent&0x3FF) + 0xDC00);
          dst.erase(refStart + 1);
        }
        else if(ent != 0) 
        {
          dst[refStart - 1] = (char)ent;
          dst.erase(refStart);  
        }
        refStart = std::string::npos;
      }
      else 
      {
        // improperly terminated ref
        refStart = std::string::npos;
      } // if ...
    } // for ...
    return std::string(dst, 0, dst.size());
  } // expandEntities

  virtual void entity(const std::string& buff) 
  {
    entity_ = lookupEntity(buff);
  } // entity

  // Process numeric character references,
  // deferring to the schema for named ones.
  int lookupEntity(const std::string& buff) 
  {
    int result = 0;
    if(buff.length() < 1) 
      return result;

    if(buff[0] == '#') 
    {
      const char* b = buff.c_str();
      char* end;
      if(buff.length() > 1 && (buff[1] == 'x' || buff[1] == 'X')) 
        return strtol(b + 2, &end, 16);
      return strtol(b + 1, &end, 10);
    }
    return schema_->getEntity(buff);
  } // lookupEntity

  virtual void eof(const std::string& /*buff*/) 
  {
    if(virginStack) 
      rectify(pcdata_);
    while (stack_.next() != Element::Null) 
    {
      pop();
    }
    if(schema_->getURI() != "")
      contentHandler_->endPrefixMapping(S(schema_->getPrefix()));
    contentHandler_->endDocument();
  } // eof

  virtual void etag(const std::string& buff) 
  {
    // std::cerr << "etag(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(etag_cdata(buff))
      return;
    etag_basic(buff);
  } // etag

  bool etag_cdata(const std::string& buff) 
  {
    std::string currentName = stack_.name();
    // If this is a CDATA element and the tag doesn't match,
    // or isn't properly formed (junk after the name),
    // restart CDATA mode and process the tag as characters.
    if(CDATAElements && (stack_.flags() & Schema::F_CDATA) != 0) 
    {
      bool realTag = (buff.length() == currentName.length());
      if(realTag) 
      {
        std::string buffl = lower_case(buff);
        std::string currentl = lower_case(currentName);
        for (size_t i = 0; i < buffl.length(); ++i) 
        {
          if(buffl[i] != currentl[i]) 
          {
            realTag = false;
            break;
          } // if ...
        } // for ...
      } // if ...
      if(!realTag) 
      {
        contentHandler_->characters(S("</"));
        contentHandler_->characters(S(buff));
        contentHandler_->characters(S(">"));
        scanner_->startCDATA();
        return true;
      } // if ...
    } // if ...
    return false;
  } // etag_cdata

  void etag_basic(const std::string& buff) 
  {
    newElement_ = Element::Null;
    std::string name;
    if(!buff.empty())
    {
      // Canonicalize case of name
      name = makeName(buff);
      ElementType& type = schema_->getElementType(name);
      if(type == ElementType::Null) 
        return;  // mysterious end-tag
      name = type.name();
    }
    else
    {
      name = stack_.name();
    }

    Element sp = Element::Null;
    bool inNoforce = false;
    for (sp = stack_; sp != Element::Null; sp = sp.next()) 
    {
      if(sp.name() == name) 
        break;
      if((sp.flags() & Schema::F_NOFORCE) != 0) 
        inNoforce = true;
    } // for ...

    if(sp == Element::Null)
      return;    // Ignore unknown etags
    if(sp.next() == Element::Null || sp.next().next() == Element::Null) 
      return;
    if(inNoforce) 
    {    // inside an F_NOFORCE element?
      sp.preclose();    // preclose the matching element
    }
    else 
    {      // restartably pop everything above us
      while (stack_ != sp) 
        restartablyPop();
      pop();
    }
    // pop any preclosed elements now at the top
    while (stack_.isPreclosed()) 
      pop();
    restart(Element::Null);
  } // etag_basic

  // Push restartables on the stack if possible
  // e is the next element to be started, if we know what it is
  void restart(Element e) 
  {
    while (saved_ != Element::Null && stack_.canContain(saved_) &&
        (e == Element::Null || saved_.canContain(e))) 
    {
      Element next = saved_.next();
      push(saved_);
      saved_ = next;
    } // while ...
  } // restart

  // Pop the stack irrevocably
  void pop() 
  {
    if(stack_ == Element::Null) 
      return;    // empty stack
    std::string name = stack_.name();
    std::string localName = stack_.localName();
    std::string namespaceName = stack_.namespaceName();
    std::string prefix = prefixOf(name);

    if(!namespaces) 
      namespaceName = localName = "";
    contentHandler_->endElement(S(namespaceName), 
                                S(localName), 
                                S(name));
    if(foreign(prefix, namespaceName)) 
      contentHandler_->endPrefixMapping(S(prefix));

    const Attributes<std::string>& atts = stack_.atts();
    for (int i = atts.getLength() - 1; i >= 0; i--) 
    {
      std::string attNamespace = atts.getURI(i);
      std::string attPrefix = prefixOf(atts.getQName(i));
      if(foreign(attPrefix, attNamespace)) 
        contentHandler_->endPrefixMapping(S(attPrefix));
    } // for ...
    stack_ = stack_.next();
  } // pop

  // Pop the stack restartably
  void restartablyPop() 
  {
    Element popped = stack_;
    pop();
    if(restartElements && (popped.flags() & Schema::F_RESTART) != 0) 
    {
      popped.anonymize();
      popped.setNext(saved_);
      saved_ = popped;
    } // if ...
  } // restartablyPop

  // Push element onto stack
  void push(Element e) 
  {
    std::string name = e.name();
    std::string localName = e.localName();
    std::string namespaceName = e.namespaceName();
    std::string prefix = prefixOf(name);

    e.clean();
    if(!namespaces) 
      namespaceName = localName = "";
    if(virginStack && (lower_case(localName) == lower_case(doctypeName_))) 
      entityResolver_->resolveEntity(S(doctypePublicId_), S(doctypeSystemId_));
    if(foreign(prefix, namespaceName)) 
      contentHandler_->startPrefixMapping(S(prefix), S(namespaceName));
    
    AttributesImpl<string_type, string_adaptor> atts;
    int len = e.atts().getLength();
    for (int i = 0; i != len; ++i) 
    {
      std::string attNamespace = e.atts().getURI(i);
      std::string attPrefix = prefixOf(e.atts().getQName(i));
      if(foreign(attPrefix, attNamespace)) 
        contentHandler_->startPrefixMapping(S(attPrefix), S(attNamespace));

      atts.addAttribute(S(e.atts().getURI(i)),
                        S(e.atts().getLocalName(i)),
                        S(e.atts().getQName(i)),
                        S(e.atts().getType(i)),
                        S(e.atts().getValue(i)));
    } // for ...
    contentHandler_->startElement(S(namespaceName), S(localName), S(name), atts);

    e.setNext(stack_);
    stack_ = e;
    virginStack = false;
    if(CDATAElements && (stack_.flags() & Schema::F_CDATA) != 0) 
      scanner_->startCDATA();
  } // push 

  // Get the prefix from a QName
  std::string prefixOf(std::string name) 
  {
    size_t i = name.find(':');
    std::string prefix = "";
    if(i != std::string::npos) 
      prefix = name.substr(0, i);
    return prefix;
  } // prefixOf

  // Return true if we have a foreign name
  bool foreign(std::string prefix, std::string namespaceName) 
  {
    bool foreign = !((prefix == "") || (namespaceName == "") || (namespaceName == schema_->getURI()));
    return foreign;
  } // foreign

  /**
   * Parsing the complete XML Document Type Definition is way too complex,
   * but for many simple cases we can extract something useful from it.
   *
   * doctypedecl  ::= '<!DOCTYPE' S Name (S ExternalID)? S? ('[' intSubset ']' S?)? '>'
   *  DeclSep     ::= PEReference | S
   *  intSubset   ::= (markupdecl | DeclSep)*
   *  markupdecl  ::= elementdecl | AttlistDecl | EntityDecl | NotationDecl | PI | Comment
   *  ExternalID  ::= 'SYSTEM' S SystemLiteral | 'PUBLIC' S PubidLiteral S SystemLiteral
   */

  virtual void decl(const std::string& buff) 
  {
    // std::cerr << "decl(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    std::string name;
    std::string systemid;
    std::string publicid;
    std::vector<std::string> v = split(buff);
    if((v.size() > 0) && ("DOCTYPE" == v[0])) 
    {
      if(doctypeIsPresent_) 
        return;    // one doctype only!
      doctypeIsPresent_ = true;
      if(v.size() > 1) 
      {
        name = v[1];
        if(v.size()>3 && "SYSTEM" == v[2]) 
        {
          systemid = v[3];
        }
        else if(v.size() > 3 && "PUBLIC" == v[2]) 
        {
          publicid = v[3];
          if(v.size() > 4) 
          {
            systemid = v[4];
          }
          else 
          {
            systemid = "";
          }
        }
      }
    }
    publicid = trimquotes(publicid);
    systemid = trimquotes(systemid);
    if(name != "") 
    {
      publicid = cleanPublicid(publicid);
      lexicalHandler_->startDTD(S(name), S(publicid), S(systemid));
      lexicalHandler_->endDTD();
      doctypeName_ = name;
      doctypePublicId_ = publicid;
      if(dynamic_cast<LocatorT*>(scanner_))
      {    // Must resolve systemid
        doctypeSystemId_  = string_adaptor::asStdString(dynamic_cast<LocatorT*>(scanner_)->getSystemId());
        doctypeSystemId_ = Arabica::io::URI(doctypeSystemId_, systemid).as_string();
      } // if ...
    } // if ...
  } // decl

  // If the String is quoted, trim the quotes.
  static std::string trimquotes(const std::string& in) 
  {
    size_t length = in.length();
    if(length == 0) 
      return in;
    char s = in[0];
    char e = in[length - 1];
    if(s == e && (s == '\'' || s == '"')) 
      return in.substr(1, length - 1);
    return in;
  } // trimquotes

  // Split the supplied String into words or phrases seperated by spaces.
  // Recognises quotes around a phrase and doesn't split it.
  static std::vector<std::string> split(const std::string& val) 
  {
    std::vector<std::string> splits;

    std::string v = Arabica::text::normalize_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(val);
    if(v.length() == 0) 
    {
      splits.push_back(v);
      return splits;
    }

    size_t s = 0;
    size_t e = 0;
    bool sq = false;  // single quote
    bool dq = false;  // double quote
    char lastc = 0;
    size_t len = v.length();
    for(e=0; e < len; ++e) 
    {
      char c = v[e];
      if(!dq && c == '\'' && lastc != '\\') 
      {
			  sq = !sq;
        if(s == std::string::npos) 
          s = e;
      }
      else if(!sq && c == '\"' && lastc != '\\') 
      {
			  dq = !dq;
			  if(s == std::string::npos) 
          s = e;
      }
      else if(!sq && !dq) 
      {
        if(Arabica::XML::is_space(c)) 
        {
          splits.push_back(v.substr(s, e));
				  s = std::string::npos;
				}
        else if(s == std::string::npos && c != ' ') 
        {
          s = e;
        } 
      }
      lastc = c;
    } // for ...
    splits.push_back(v.substr(s, e));

    return splits;
  } // split

  // Replace junk in publicids with spaces
  std::string cleanPublicid(const std::string& src) 
  {
    std::string dst;
    bool suppressSpace = true;
    for(std::string::const_iterator i = src.begin(), ie = src.end(); i != ie; ++i)
    {
      if(legal.find(*i) != std::string::npos) 
      {   
        // legal but not whitespace
        dst.push_back(*i);
        suppressSpace = false;
      }
      else if(suppressSpace) 
      {  // normalizable whitespace or junk
        ;
      }
      else 
      {
        dst.push_back(' ');
        suppressSpace = true;
      }
    }
    return dst;
  } // cleanPublicId

  virtual void gi(const std::string& buff) 
  {
    // std::cerr << "gi(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(newElement_ != Element::Null) 
      return;
    std::string name = makeName(buff);
    if(name == "") 
      return;
    ElementType* type = &schema_->getElementType(name);
    if(*type == ElementType::Null) 
    {
      // Suppress unknown elements if ignore-bogons is on
      if(ignoreBogons) 
        return;
      int bogonModel = bogonsEmpty ? Schema::M_EMPTY : Schema::M_ANY;
      int bogonMemberOf = rootBogons ? Schema::M_ANY : (Schema::M_ANY & ~Schema::M_ROOT);
      schema_->elementType(name, bogonModel, bogonMemberOf, 0);
      if(!rootBogons) 
        schema_->parent(name, schema_->rootElementType().name());
      type = &schema_->getElementType(name);
    } // if ...

    newElement_ = Element(*type, defaultAttributes);
  } // gi

  virtual void cdsect(const std::string& buff) 
  {
    // std::cerr << "cdsect(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    lexicalHandler_->startCDATA();
    pcdata(buff);
    lexicalHandler_->endCDATA();
  } // cdsect
  
  virtual void pcdata(const std::string& buff) 
  {
    // std::cerr << "pcdata(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(buff.empty())
      return;
    bool allWhite = true;
    for (std::string::const_iterator i = buff.begin(), ie = buff.end(); i != ie; ++i)
    {
      if(!Arabica::XML::is_space(*i)) 
        allWhite = false;
    } // for ...
    if(allWhite && !stack_.canContain(pcdata_)) 
    {
      if(ignorableWhitespace) 
        contentHandler_->ignorableWhitespace(S(buff));
    }
    else 
    {
      rectify(pcdata_);
      contentHandler_->characters(S(buff));
    } // if ...
  } // pcdata

  virtual void pitarget(const std::string& buff) 
  {
    // std::cerr << "pitarget(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(newElement_ != Element::Null) 
      return;
    std::string name = makeName(buff);
    size_t colon = name.find(':');
    while(colon != std::string::npos)
    {
      name[colon] = '_';
      colon = name.find(':');
    } // while
    piTarget_ = name;
  } // pitarget

  virtual void pi(const std::string& buff) 
  {
    // std::cerr << "pi(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(newElement_ != Element::Null || piTarget_ == "") 
      return;
    if("xml" == lower_case(piTarget_)) 
      return;
    size_t length = buff.length();
    if((length > 0) && (buff[length - 1] == '?')) 
      length--;  // remove trailing ?
    contentHandler_->processingInstruction(S(piTarget_),
                                           S(buff.substr(0, length)));
    piTarget_ = "";
  } // pi

  virtual void stagc(const std::string& buff) 
  {
    // std::cerr << "stagc(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(newElement_ == Element::Null) 
      return;
    rectify(newElement_);
    if(stack_.model() == Schema::M_EMPTY) 
    {
      // Force an immediate end tag
      etag_basic(buff);
    } // if ...
  } // stagc

  virtual void stage(const std::string& buff) 
  {
    // std::cerr << "stage(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    if(newElement_ == Element::Null) 
      return;
    rectify(newElement_);
    // Force an immediate end tag
    etag_basic(buff);
  } // stage

  // Comment buffer is twice the size of the output buffer
  virtual void cmnt(const std::string& buff) 
  {
    // std::cerr << "cmnt(\"" << buff.substr(offset, length) << "\", " << offset << ", " << length << ")" << std::endl;
    lexicalHandler_->comment(S(buff));
  } // cmnt

  // Rectify the stack, pushing and popping as needed
  // so that the argument can be safely pushed
  void rectify(Element e) 
  {
    Element sp = Element::Null;
    while (true) 
    {
      for (sp = stack_; sp != Element::Null; sp = sp.next()) 
      {
        if(sp.canContain(e)) 
          break;
      } // for ...
      if(sp != Element::Null) 
        break;
      ElementType& parentType = e.parent();
      if(parentType == ElementType::Null) 
        break;
      Element parent = Element(parentType, defaultAttributes);
      parent.setNext(e);
      e = parent;
    } // while ...
    if(sp == Element::Null) 
      return;    // don't know what to do
    while (stack_ != sp) 
    {
      if(stack_ == Element::Null || stack_.next() == Element::Null || stack_.next().next() == Element::Null) 
        break;
      restartablyPop();
    } // while ...
    while (e != Element::Null) 
    {
      Element nexte = e.next();
      if(e.name() != "<pcdata>") 
        push(e);
      e = nexte;
      restart(e);
    } // while ...
    newElement_ = Element::Null;
  } // rectify

  virtual int getEntity() 
  {
    return entity_;
  } // getEntity

  // Return the argument as a valid XML name
  // This no longer lowercases the result: we depend on Schema to
  // canonicalize case.
  std::string makeName(const std::string& buff) 
  {
    std::string dst;
    bool seenColon = false;
    bool start = true;
//    String src = new String(buff, offset, length); // DEBUG
    for(std::string::const_iterator ch = buff.begin(), che = buff.end(); ch != che; ++ch)
    {
      if(Arabica::XML::is_letter(*ch) || *ch == '_') 
      {
        start = false;
        dst.push_back(*ch);
      }
      else if(Arabica::XML::is_digit(*ch) || *ch == '-' || *ch == '.') 
      {
        if(start) 
          dst.push_back('_');
        start = false;
        dst.push_back(*ch);
      }
      else if(*ch == ':' && !seenColon) 
      {
        seenColon = true;
        if(start) 
          dst.push_back('_');
        start = true;
        dst.push_back(translateColons ? '_' : *ch);
      } 
    } // for ...
    size_t dstLength = dst.length();
    if(dstLength == 0 || dst[dstLength - 1] == ':') 
      dst.push_back('_');
    return dst;
  } // makeName

  static std::string lower_case(const std::string& str) 
  {
    std::string lower;
    std::transform(str.begin(), str.end(), std::back_inserter(lower), (int(*)(int))std::tolower);
    return lower;
  } // lower_case

  void reportError(const std::string& message, bool fatal)
  {
    SAXParseException<string_type> e(message,
                                     S("<public-id>"),
                                     S("<system-id>"),
                                     -1,
                                     -1);
    if(fatal)
      errorHandler_->fatalError(e);
    else
      errorHandler_->error(e);
  } // reportError

public:
  static string_type S(const std::string& s)
  {
    return string_adaptor::construct_from_utf8(s.c_str());
  } // S
 
  static string_type S(const char* s)
  {
    return string_adaptor::construct_from_utf8(s);
  } // S
}; // class Taggle

template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_NAMESPACES = true;
template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_IGNORE_BOGONS = false;
template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_BOGONS_EMPTY = false;
template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_ROOT_BOGONS = true;
template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_DEFAULT_ATTRIBUTES = true;
template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_TRANSLATE_COLONS = false;
template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_RESTART_ELEMENTS = true;
template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_IGNORABLE_WHITESPACE = false;
template<class string_type, class string_adaptor_type>
bool Taggle<string_type, string_adaptor_type>::DEFAULT_CDATA_ELEMENTS = true;

template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::namespacesFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/namespaces");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::namespacePrefixesFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/namespace-prefixes");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::externalGeneralEntitiesFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/external-general-entities");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::externalParameterEntitiesFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/external-parameter-entities");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::isStandaloneFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/is-standalone");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::lexicalHandlerParameterEntitiesFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/lexical-handler/parameter-entities");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::resolveDTDURIsFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/resolve-dtd-uris");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::stringInterningFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/string-interning");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::useAttributes2Feature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/use-attributes2");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::useLocator2Feature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/use-locator2");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::useEntityResolver2Feature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/use-entity-resolver2");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::validationFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/validation");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::unicodeNormalizationCheckingFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/unicode-normalization-checking");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::xmlnsURIsFeature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/xmlns-uris");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::XML11Feature = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/features/xml-1.1");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::ignoreBogonsFeature = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/features/ignore-bogons");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::bogonsEmptyFeature = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/features/bogons-empty");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::rootBogonsFeature = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/features/root-bogons");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::defaultAttributesFeature = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/features/default-attributes");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::translateColonsFeature = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/features/translate-colons");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::restartElementsFeature = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/features/restart-elements");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::ignorableWhitespaceFeature = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/features/ignorable-whitespace");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::CDATAElementsFeature = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/features/cdata-elements");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::lexicalHandlerProperty = Taggle<string_type, string_adaptor_type>::S("http://xml.org/sax/properties/lexical-handler");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::scannerProperty = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/properties/scanner");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::schemaProperty = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/properties/schema");
template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::autoDetectorProperty = Taggle<string_type, string_adaptor_type>::S("http://www.ccil.org/~cowan/tagsoup/properties/auto-detector");

template<class string_type, class string_adaptor_type>
const string_type Taggle<string_type, string_adaptor_type>::legal =
  Taggle<string_type, string_adaptor_type>::S("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-'()+,./:=?;!*#@$_%");

} // namespace SAX

} // namespace Arabica
#endif

