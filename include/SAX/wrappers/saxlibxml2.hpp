#ifndef ARABICA_SAX_LIBXML2_H
#define ARABICA_SAX_LIBXML2_H
////////////////////////////////////////////////////////////////
// A SAX2 Wrapper for libxml2
////////////////////////////////////////////////////////////////

#include <SAX/ArabicaConfig.hpp>
#include <SAX/XMLReader.hpp>
#include <SAX/SAXParseException.hpp>
#include <SAX/InputSource.hpp>
#include <SAX/SAXNotSupportedException.hpp>
#include <SAX/SAXNotRecognizedException.hpp>
#include <libxml/parser.h>

#include <string>
#include <cstdarg>
#include <typeinfo>

#include <SAX/helpers/FeatureNames.hpp>
#include <SAX/helpers/PropertyNames.hpp>
#include <SAX/helpers/NamespaceSupport.hpp>
#include <SAX/helpers/AttributeDefaults.hpp>
#include <SAX/helpers/AttributeTypes.hpp>
#include <SAX/helpers/InputSourceResolver.hpp>
#include <SAX/helpers/AttributesImpl.hpp>
#include <Arabica/getparam.hpp>

namespace Arabica
{
namespace SAX
{

////////////////////////////////////////////////////////////////////////////
// the callback functions for libxml
namespace libxml2_wrapper_impl_tiddle
{

extern "C"
{

class libxml2_base
{
  protected:
    virtual ~libxml2_base() { }

  private:
    virtual void SAXstartDocument() = 0;
    virtual void SAXendDocument() = 0;
    virtual void SAXlocator(xmlSAXLocatorPtr locator) = 0;
    virtual void SAXcharacters(const xmlChar* ch, int len) = 0;
    virtual void SAXignorableWhitespace(const xmlChar* ch, int len) = 0;
    virtual void SAXwarning(const std::string& warning) = 0;
    virtual void SAXerror(const std::string& error) = 0;
    virtual void SAXfatalError(const std::string& fatal) = 0;
    virtual void SAXprocessingInstruction(const xmlChar* target, const xmlChar* data) = 0;
    virtual void SAXcomment(const xmlChar* comment) = 0;
    virtual void SAXstartElement(const xmlChar* name, const xmlChar** attrs) = 0;
    virtual void SAXendElement(const xmlChar* name) = 0;
    virtual void SAXnotationDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId) = 0;
    virtual void SAXunparsedEntityDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName) = 0;
    virtual void SAXelementDecl(const xmlChar* name, int type, xmlElementContentPtr content) = 0;
    virtual void SAXattributeDecl(const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree) = 0;
    virtual void SAXentityDecl(const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId,	xmlChar *content) = 0;
    virtual xmlParserInputPtr SAXresolveEntity(const xmlChar* publicId, const xmlChar* systemId) = 0;

    friend void lwit_startDocument(void* user_data);
    friend void lwit_endDocument(void* user_data);
    friend void lwit_characters(void *user_data, const xmlChar* ch, int len);
    friend void lwit_ignorableWhitespace(void *user_data, const xmlChar* ch, int len);
    friend void lwit_locator(void* user_data, xmlSAXLocatorPtr locator);
    friend void lwit_warning(void *user_data, const char* fmt, ...);
    friend void lwit_error(void* user_data, const char* fmt, ...);
    friend void lwit_fatalError(void* user_data, const char* fmt, ...);
    friend void lwit_processingInstruction(void *user_data, const xmlChar* target, const xmlChar* data);
    friend void lwit_comment(void *user_data, const xmlChar* comment);
    friend void lwit_startElement(void *user_data, const xmlChar* name, const xmlChar** attrs);
    friend void lwit_endElement(void* user_data, const xmlChar* name);
    friend void lwit_notationDecl(void* user_data, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId);
    friend void lwit_unparsedEntityDecl(void* user_data, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName);
    friend void lwit_elementDecl(void* user_data, const xmlChar *name, int type, xmlElementContentPtr content);
    friend void lwit_attributeDecl(void* user_data, const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree);
    friend void lwit_entityDecl(void* user_data, const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId,	xmlChar *content);
    friend xmlParserInputPtr lwit_resolveEntity(void* user_data, const xmlChar* publicId, const xmlChar* systemId);
}; // class libxml2_base

void lwit_startDocument(void* user_data);
void lwit_endDocument(void* user_data);
void lwit_startElement(void *user_data, const xmlChar* name, const xmlChar** attrs);
void lwit_endElement(void *user_data, const xmlChar* name);
void lwit_characters(void* user_data, const xmlChar* ch, int len);
void lwit_ignorableWhitespace(void *user_data, const xmlChar* ch, int len);
void lwit_processingInstruction(void *user_data, const xmlChar* target, const xmlChar* data);
void lwit_comment(void *user_data, const xmlChar* comment);
void lwit_warning(void *user_data, const char* fmt, ...);
void lwit_error(void* user_data, const char* fmt, ...);
void lwit_fatalError(void* user_data, const char* fmt, ...);
void lwit_locator(void* user_data, xmlSAXLocatorPtr locator);
void lwit_notationDecl(void* user_data, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId);
void lwit_unparsedEntityDecl(void* user_data,
                           const xmlChar *name, const xmlChar *publicId,
			                     const xmlChar *systemId, const xmlChar *notationName);
void lwit_elementDecl(void* user_date, const xmlChar *name, int type, xmlElementContentPtr content);
void lwit_attributeDecl(void *user_data, const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree);
void lwit_entityDecl(void* user_data, const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId,	xmlChar *content);
void lwit_setFeature(xmlParserCtxtPtr context, const char* name, bool value);
bool lwit_getFeature(xmlParserCtxtPtr context, const char* name);
xmlParserInputPtr lwit_resolveEntity(void* user_data, const xmlChar* publicId, const xmlChar* systemId);
xmlSAXHandler* lwit_SaxHandler();
} // extern "C"

} // namespace libxml2_wrapper_impl_tiddle

template<class string_type,
         class T0 = Arabica::nil_t,
         class T1 = Arabica::nil_t>
class libxml2_wrapper :
    public SAX::XMLReaderInterface<string_type,
                                   typename Arabica::get_string_adaptor<string_type, T0, T1>::type>,
    public SAX::Locator<string_type, typename Arabica::get_string_adaptor<string_type, T0, T1>::type>,
    protected libxml2_wrapper_impl_tiddle::libxml2_base
{
  public:
    typedef SAX::XMLReaderInterface<string_type,
                                    typename Arabica::get_string_adaptor<string_type, T0, T1>::type> XMLReaderT;
    typedef typename XMLReaderT::string_adaptor string_adaptor;
    typedef SAX::EntityResolver<string_type, string_adaptor> entityResolverT;
    typedef SAX::DTDHandler<string_type, string_adaptor> dtdHandlerT;
    typedef SAX::ContentHandler<string_type, string_adaptor> contentHandlerT;
    typedef SAX::Attributes<string_type, string_adaptor> attributesT;
    typedef SAX::AttributeType<string_type, string_adaptor> attributeTypeT;
    typedef SAX::DeclHandler<string_type, string_adaptor> declHandlerT;
    typedef SAX::LexicalHandler<string_type, string_adaptor> lexicalHandlerT;
    typedef SAX::InputSource<string_type, string_adaptor> inputSourceT;
    typedef SAX::Locator<string_type, string_adaptor> locatorT;
    typedef SAX::NamespaceSupport<string_type, string_adaptor> namespaceSupportT;
    typedef SAX::ErrorHandler<string_type, string_adaptor> errorHandlerT;
    typedef SAX::SAXParseException<string_type, string_adaptor> SAXParseExceptionT;
    typedef typename XMLReaderT::PropertyBase PropertyBaseT;
    typedef typename XMLReaderT::template Property<lexicalHandlerT*> getLexicalHandlerT;
    typedef typename XMLReaderT::template Property<lexicalHandlerT&> setLexicalHandlerT;
    typedef typename XMLReaderT::template Property<declHandlerT*> getDeclHandlerT;
    typedef typename XMLReaderT::template Property<declHandlerT&> setDeclHandlerT;
    typedef XML::QualifiedName<string_type, string_adaptor> qualifiedNameT;

    libxml2_wrapper();
    ~libxml2_wrapper();

    ////////////////////////////////////////////////
    // configuration
    virtual bool getFeature(const string_type& name) const;
    virtual void setFeature(const string_type& name, bool value);

    ////////////////////////////////////////////////
    // Event Handlers
    virtual void setEntityResolver(entityResolverT& resolver) { entityResolver_ = &resolver; }
    virtual entityResolverT* getEntityResolver() const { return entityResolver_; }
    virtual void setDTDHandler(dtdHandlerT& handler) { dtdHandler_ = &handler; }
    virtual dtdHandlerT* getDTDHandler() const { return dtdHandler_; }
    virtual void setContentHandler(contentHandlerT& handler) { contentHandler_ = &handler; }
    virtual contentHandlerT* getContentHandler() const { return contentHandler_; }
    virtual void setErrorHandler(errorHandlerT& handler) { errorHandler_ = &handler; }
    virtual errorHandlerT* getErrorHandler() const { return errorHandler_; }
    virtual void setDeclHandler(declHandlerT& handler) { declHandler_ = &handler; }
    virtual declHandlerT* getDeclHandler() const { return declHandler_; }
    virtual void setLexicalHandler(lexicalHandlerT& handler) { lexicalHandler_ = &handler; }
    virtual lexicalHandlerT* getLexicalHandler() const { return lexicalHandler_; }

    ////////////////////////////////////////////////
    // parsing
    virtual void parse(inputSourceT& source);

  protected:
    ////////////////////////////////////////////////
    // properties
    virtual std::auto_ptr<PropertyBaseT> doGetProperty(const string_type& name);
    virtual void doSetProperty(const string_type& name, std::auto_ptr<PropertyBaseT> value);

  public:
    virtual string_type getPublicId() const;
    virtual string_type getSystemId() const;
    virtual int getLineNumber() const;
    virtual int getColumnNumber() const;

  private:
    virtual void SAXstartDocument();
    virtual void SAXendDocument();
    virtual void SAXlocator(xmlSAXLocatorPtr locator) { locator_ = locator; }
    virtual void SAXcharacters(const xmlChar* ch, int len);
    virtual void SAXignorableWhitespace(const xmlChar* ch, int len);
    virtual void SAXwarning(const std::string& warning);
    virtual void SAXerror(const std::string& error);
    virtual void SAXfatalError(const std::string& fatal);
    virtual void SAXprocessingInstruction(const xmlChar* target, const xmlChar* data);
    virtual void SAXcomment(const xmlChar* comment);
    virtual void SAXstartElement(const xmlChar* name, const xmlChar** attrs);
    virtual void SAXstartElementNoNS(const xmlChar* name, const xmlChar** attrs);
    virtual void SAXendElement(const xmlChar* name);
    virtual void SAXendElementNoNS(const xmlChar* name);
    virtual void SAXnotationDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId);
    virtual void SAXunparsedEntityDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName);
    virtual void SAXelementDecl(const xmlChar* name, int type, xmlElementContentPtr content);
    void convertXML_Content(std::ostream& os, int type, xmlElementContentPtr model, bool isChild) const;
    virtual void SAXattributeDecl(const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree);
    string_type stringAttrEnum(xmlEnumerationPtr tree, bool leadingSpace) const;
    virtual void SAXentityDecl(const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId,	xmlChar *content);
    virtual xmlParserInputPtr SAXresolveEntity(const xmlChar* publicId, const xmlChar* systemId);

    qualifiedNameT processName(const string_type& qName, bool isAttribute);
    void reportError(const std::string& message, bool fatal = false);
    void checkNotParsing(const string_type& type, const string_type& name) const;

  private:
    // member variables
    entityResolverT* entityResolver_;
    dtdHandlerT* dtdHandler_;
    contentHandlerT* contentHandler_;
    errorHandlerT* errorHandler_;
    namespaceSupportT nsSupport_;
    declHandlerT* declHandler_;
    lexicalHandlerT* lexicalHandler_;

    xmlParserCtxtPtr context_;
		xmlSAXLocatorPtr locator_;

    bool parsing_;

    bool namespaces_;
    bool prefixes_;

    string_type emptyString_;
    const FeatureNames<string_type, string_adaptor> features_;
    const PropertyNames<string_type, string_adaptor> properties_;
    const NamespaceConstants<string_type, string_adaptor> nsc_;
    const AttributeDefaults<string_type, string_adaptor> attrDefaults_;
    const AttributeTypes<string_type, string_adaptor> attrTypes_;
}; // class libxml2_wrapper

template<class string_type, class T0, class T1>
libxml2_wrapper<string_type, T0, T1>::libxml2_wrapper() :
  entityResolver_(0),
  dtdHandler_(0),
  contentHandler_(0),
  errorHandler_(0),
  declHandler_(0),
  lexicalHandler_(0),
  locator_(0),
  parsing_(false),
  namespaces_(true),
  prefixes_(true)
{
  context_ = xmlCreatePushParserCtxt(libxml2_wrapper_impl_tiddle::lwit_SaxHandler(),
                                     reinterpret_cast<void*>(static_cast<libxml2_wrapper_impl_tiddle::libxml2_base*>(this)),
                                     0,
                                     0,
                                     0);
  xmlCtxtUseOptions(context_, XML_PARSE_DTDLOAD + XML_PARSE_DTDVALID + XML_PARSE_NOBLANKS);
} // libxml2_wrapper

template<class string_type, class T0, class T1>
libxml2_wrapper<string_type, T0, T1>::~libxml2_wrapper()
{
	xmlFreeParserCtxt(context_);
} // ~libxml2_wrapper

template<class string_type, class T0, class T1>
bool libxml2_wrapper<string_type, T0, T1>::getFeature(const string_type& name) const
{
  if(name == features_.namespaces)
    return namespaces_;

  if(name == features_.namespace_prefixes)
    return prefixes_;

  if(name == features_.validation)
    return libxml2_wrapper_impl_tiddle::lwit_getFeature(context_, "validate");

  if(name == features_.external_general)
    return libxml2_wrapper_impl_tiddle::lwit_getFeature(context_, "fetch external entities");

  if(name == features_.external_parameter)
  {
    throw SAX::SAXNotSupportedException(std::string("Feature not supported ") + string_adaptor::asStdString(name));
  }
  else
  {
    throw SAX::SAXNotRecognizedException(std::string("Feature not recognized ") + string_adaptor::asStdString(name));
  }
} // getFeature

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::setFeature(const string_type& name, bool value)
{
  if(name == features_.namespaces)
  {
    checkNotParsing(string_adaptor::construct_from_utf8("feature"), name);
    namespaces_ = value;
    if(!namespaces_ && !prefixes_)
      prefixes_ = true;
    return;
  }

  if(name == features_.namespace_prefixes)
  {
    checkNotParsing(string_adaptor::construct_from_utf8("feature"), name);
    prefixes_ = value;
    if(prefixes_ && !namespaces_)
      namespaces_ = true;
    return;
  }

  if(name == features_.validation)
  {
    libxml2_wrapper_impl_tiddle::lwit_setFeature(context_, "validate", value);
    return;
  } // if ...

  if(name == features_.external_general)
  {
    libxml2_wrapper_impl_tiddle::lwit_setFeature(context_, "fetch external entities", value);
    return;
  } // if ...

  if(name == features_.external_parameter)
  {
    std::ostringstream os;
    os << "Feature not supported " << string_adaptor::asStdString(name);
    throw SAX::SAXNotSupportedException(os.str());
  }
  else
  {
    std::ostringstream os;
    os << "Feature not recognized " << string_adaptor::asStdString(name);
    throw SAX::SAXNotRecognizedException(os.str());
  }
} // setFeature

template<class string_type, class T0, class T1>
std::auto_ptr<typename libxml2_wrapper<string_type, T0, T1>::PropertyBaseT> libxml2_wrapper<string_type, T0, T1>::doGetProperty(const string_type& name)
{
  if(name == properties_.declHandler)
  {
    getDeclHandlerT* prop = new getDeclHandlerT(declHandler_);
    return std::auto_ptr<PropertyBaseT>(prop);
  }
	if(name == properties_.lexicalHandler)
  {
    getLexicalHandlerT* prop = new getLexicalHandlerT(lexicalHandler_);
    return std::auto_ptr<PropertyBaseT>(prop);
  }

  throw SAX::SAXNotRecognizedException(std::string("Property not recognized ") + string_adaptor::asStdString(name));
} // doGetProperty

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::doSetProperty(const string_type& name, std::auto_ptr<PropertyBaseT> value)
{
  if(name == properties_.declHandler)
  {
    setDeclHandlerT* prop = dynamic_cast<setDeclHandlerT*>(value.get());

    if(!prop)
      throw std::bad_cast();

    declHandler_ = &(prop->get());
  }
	if(name == properties_.lexicalHandler)
  {
    setLexicalHandlerT* prop = dynamic_cast<setLexicalHandlerT*>(value.get());

    if(!prop)
      throw std::bad_cast();

    lexicalHandler_ = &(prop->get());
  }

  throw SAX::SAXNotRecognizedException(std::string("Property not recognized ") + string_adaptor::asStdString(name));
} // doSetProperty

template<class string_type, class T0, class T1>
typename XML::QualifiedName<string_type, typename libxml2_wrapper<string_type, T0, T1>::string_adaptor> libxml2_wrapper<string_type, T0, T1>::processName(const string_type& qName, bool isAttribute)
{
  qualifiedNameT p = nsSupport_.processName(qName, isAttribute);
  if(string_adaptor::empty(p.namespaceUri()) && !string_adaptor::empty(p.prefix()))
    reportError(std::string("Undeclared prefix ") + string_adaptor::asStdString(qName));
  return p;
} // processName

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::reportError(const std::string& message, bool fatal)
{
  if(!errorHandler_)
    return;

  SAXParseExceptionT e(message, *this);
  if(fatal)
    errorHandler_->fatalError(e);
  else
    errorHandler_->error(e);
} // reportError

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::checkNotParsing(const string_type& type, const string_type& name) const
{
  if(parsing_)
  {
    std::ostringstream os;
    os << "Can't change " << string_adaptor::asStdString(type) << " " << string_adaptor::asStdString(name) << " while parsing";
    throw SAX::SAXNotSupportedException(os.str());
  } // if(parsing_)
} // checkNotParsing

template<class string_type, class T0, class T1>
string_type libxml2_wrapper<string_type, T0, T1>::getPublicId() const
{
  if(locator_)
	  return string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(locator_->getPublicId(context_)));
  return string_type();
} // getPublicId

template<class string_type, class T0, class T1>
string_type libxml2_wrapper<string_type, T0, T1>::getSystemId() const
{
  if(locator_)
	  return string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(locator_->getSystemId(context_)));
  return string_type();
} // getSystemId

template<class string_type, class T0, class T1>
int libxml2_wrapper<string_type, T0, T1>::getLineNumber() const
{
  if(locator_)
    return locator_->getLineNumber(context_);
  return -1;
} // getLineNumber

template<class string_type, class T0, class T1>
int libxml2_wrapper<string_type, T0, T1>::getColumnNumber() const
{
  if(locator_)
    return locator_->getColumnNumber(context_);
  return -1;
} // getColumnNumber

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::parse(inputSourceT& source)
{
  if(contentHandler_)
    contentHandler_->setDocumentLocator(*this);

  InputSourceResolver is(source, string_adaptor());
  if(is.resolve() == 0)
    return;

  parsing_ = true;

	while(!is.resolve()->eof())
 	{
		char buffer[4096];
		is.resolve()->read(buffer, sizeof(buffer));
		xmlParseChunk(context_, buffer, (int)is.resolve()->gcount(), is.resolve()->eof());
	} // while(!in.eof())

  xmlCtxtResetPush(context_, 0, 0, 0, 0);

  parsing_ = false;
} // parse

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXstartDocument()
{
  if(contentHandler_)
    contentHandler_->startDocument();
} // SAXstartDocument

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXendDocument()
{
  if(contentHandler_)
    contentHandler_->endDocument();
} // SAXendDocument

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXcharacters(const xmlChar* ch, int len)
{
  if(contentHandler_)
    contentHandler_->characters(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(ch), len));
} // SAXcharacters

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXignorableWhitespace(const xmlChar* ch, int len)
{
  if(contentHandler_)
    contentHandler_->ignorableWhitespace(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(ch), len));
} // SAXignorableWhitespace

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXwarning(const std::string& warning)
{
  if(errorHandler_)
    errorHandler_->warning(SAXParseExceptionT(warning, *this));
} // warning

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXerror(const std::string& error)
{
  if(errorHandler_)
    errorHandler_->error(SAXParseExceptionT(error, *this));
} // error

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXfatalError(const std::string& fatal)
{
  if(errorHandler_)
    errorHandler_->fatalError(SAXParseExceptionT(fatal, *this));
} // fatal

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXprocessingInstruction(const xmlChar* target, const xmlChar* data)
{
  if(contentHandler_)
    contentHandler_->processingInstruction(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(target)),
                                           string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(data)));
} // SAXprocessingInstruction

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXcomment(const xmlChar* comment)
{
  if(lexicalHandler_)
    lexicalHandler_->comment(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(comment)));
} // SAXcomment

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXstartElement(const xmlChar* qName, const xmlChar** atts)
{
  if(!contentHandler_)
    return;

  if(!namespaces_)
  {
    SAXstartElementNoNS(qName, atts);
    return;
  } // if(!namespaces)

  // OK we're doing Namespaces
  nsSupport_.pushContext();
  SAX::AttributesImpl<string_type, string_adaptor> attributes;

  // take a first pass and copy all the attributes, noting any declarations
  if(atts && *atts != 0)
  {
    const xmlChar** a1 = atts;
    while(*a1 != 0)
    {
      string_type attQName = string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(*a1++));
      string_type value = string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(*a1++));

      // declaration?
      if(string_adaptor::find(attQName, nsc_.xmlns) == 0)
      {
        string_type prefix;
        typename string_adaptor::size_type n = string_adaptor::find(attQName, nsc_.colon);
        if(n != string_adaptor::npos())
          prefix = string_adaptor::construct(string_adaptor::begin(attQName) + n + 1, string_adaptor::end(attQName));
        if(!nsSupport_.declarePrefix(prefix, value))
          reportError(std::string("Illegal Namespace prefix ") + string_adaptor::asStdString(prefix));
        contentHandler_->startPrefixMapping(prefix, value);
        if(prefixes_)
          attributes.addAttribute(emptyString_,
                                  emptyString_,
                                  attQName,
                                  attributeTypeT::CDATA,
                                  value);
      }
    } // while

    while(*atts != 0)
    {
      string_type attQName = string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(*atts++));
      string_type value = string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(*atts++));

      // declaration?
      if(string_adaptor::find(attQName, nsc_.xmlns) != 0)
      {
        qualifiedNameT attName = processName(attQName, true);
        attributes.addAttribute(attName.namespaceUri(),
                                attName.localName(),
                                attName.rawName(),
                                attributeTypeT::CDATA,
                                value);
      }
    } // while ...
  } // if ...

  // at last! report the event
  qualifiedNameT name = processName(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(qName)), false);
  contentHandler_->startElement(name.namespaceUri(),
				name.localName(),
				name.rawName(),
				attributes);
} // SAXstartElement

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXstartElementNoNS(const xmlChar* qName, const xmlChar** atts)
{
  SAX::AttributesImpl<string_type, string_adaptor> attributes;

  if(atts && *atts != 0)
  {
    while(*atts != 0)
    {
      string_type attQName = string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(*atts++));
      string_type value = string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(*atts++));

      attributes.addAttribute(emptyString_,
                              emptyString_,
                              attQName,
                              attributeTypeT::CDATA,
                              value);
    } // while ..
  } // if ...

  contentHandler_->startElement(emptyString_, emptyString_, string_adaptor::construct_from_utf8((reinterpret_cast<const char*>(qName))), attributes);
} // SAXstartElementNoNS

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXendElement(const xmlChar* qName)
{
  if(!contentHandler_)
    return;

  if(!namespaces_)
  {
    SAXendElementNoNS(qName);
    return;
  } // if(!namespaces_)

  qualifiedNameT name = processName(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(qName)), false);
  contentHandler_->endElement(name.namespaceUri(),
			      name.localName(),
			      name.rawName());
  typename NamespaceSupport<string_type, string_adaptor>::stringListT prefixes = nsSupport_.getDeclaredPrefixes();
  for(size_t i = 0, end = prefixes.size(); i < end; ++i)
    contentHandler_->endPrefixMapping(prefixes[i]);
  nsSupport_.popContext();
} // SAXendElement

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXendElementNoNS(const xmlChar* qName)
{
  if(contentHandler_)
    contentHandler_->endElement(emptyString_, emptyString_, string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(qName)));
} // SAXendElementNoNS

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXnotationDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId)
{
  if(dtdHandler_)
    dtdHandler_->notationDecl(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(name)),
                              string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(publicId)),
                              string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(systemId)));
} // SAXnotationDecl

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXunparsedEntityDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName)
{
  if(dtdHandler_)
    dtdHandler_->unparsedEntityDecl(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(name)),
                                    string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(publicId)),
                                    string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(systemId)),
                                    string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(notationName)));
} // SAXunparsedEntityDecl

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXelementDecl(const xmlChar* name, int type, xmlElementContentPtr content)
{
  if(!declHandler_)
    return;

  std::ostringstream os;
  convertXML_Content(os, type, content, false);
  declHandler_->elementDecl(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(name)), string_adaptor::construct_from_utf8(os.str().c_str()));
} // elementDeclaration

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::convertXML_Content(std::ostream& os, int type, xmlElementContentPtr model, bool isChild) const
{
  char concatenator = ' ';

  switch(type)
  {
    case XML_ELEMENT_TYPE_EMPTY:
      os << "EMPTY";
      break;
    case XML_ELEMENT_TYPE_ANY:
      os << "ANY";
      return;
    case XML_ELEMENT_TYPE_MIXED:
      if(model->c1 == 0)
        os << "(#PCDATA)";
      else
        os << "(#PCDATA";
      concatenator = '|';
      break;
    case XML_ELEMENT_TYPE_ELEMENT:
      break;
  } // switch

  switch(model->type)
  {
    case XML_ELEMENT_CONTENT_ELEMENT:
      if(!isChild)
        os << '(' << model->name << ')';
      else
        os << model->name;
      break;
    case XML_ELEMENT_CONTENT_SEQ:
      concatenator = ',';
      break;
    case XML_ELEMENT_CONTENT_OR:
      concatenator = '|';
      break;
    case XML_ELEMENT_CONTENT_PCDATA:
      break;
  } // switch

  // do children here
  if(model->c1 != 0)
  {
    if(!isChild)
      os << '(';
    convertXML_Content(os, XML_ELEMENT_TYPE_ELEMENT, model->c1, true);
    if(model->c2 != 0)
    {
      os << concatenator;
      convertXML_Content(os, XML_ELEMENT_TYPE_ELEMENT, model->c2, true);
    } // if ...
    if(!isChild)
      os << ')';
  } // if ...

  switch(model->ocur)
  {
    case XML_ELEMENT_CONTENT_ONCE:
      break;
    case XML_ELEMENT_CONTENT_OPT:
      os << "?";
      break;
    case XML_ELEMENT_CONTENT_MULT:
      os << "*";
      break;
    case XML_ELEMENT_CONTENT_PLUS:
      os << "+";
      break;
  } // switch
} // convertXML_Content

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXattributeDecl(const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree)
{
  if(!declHandler_)
    return;

  const string_type* defType = &attrDefaults_.implied;
  if(def)
    defType = (defaultValue) ? &attrDefaults_.fixed : &attrDefaults_.required;

  string_type typeStr;
  switch(type)
  {
    case XML_ATTRIBUTE_CDATA:
      typeStr = attrTypes_.cdata;
      break;
    case XML_ATTRIBUTE_ID:
      typeStr = attrTypes_.id;
      break;
    case XML_ATTRIBUTE_IDREF :
      typeStr = attrTypes_.idref;
      break;
    case XML_ATTRIBUTE_IDREFS:
      typeStr = attrTypes_.idrefs;
      break;
    case XML_ATTRIBUTE_ENTITY:
      typeStr = attrTypes_.entity;
      break;
    case XML_ATTRIBUTE_ENTITIES:
      typeStr = attrTypes_.entities;
      break;
    case XML_ATTRIBUTE_NMTOKEN:
      typeStr = attrTypes_.nmtoken;
      break;
    case XML_ATTRIBUTE_NMTOKENS:
      typeStr = attrTypes_.nmtokens;
      break;
    case XML_ATTRIBUTE_ENUMERATION:
      typeStr = stringAttrEnum(tree, false);
      break;
    case XML_ATTRIBUTE_NOTATION:
      string_adaptor::append(typeStr, attrTypes_.notation);
      string_adaptor::append(typeStr, stringAttrEnum(tree, true));
      break;
  } // switch(type)

  declHandler_->attributeDecl(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(elem)),
                              string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(fullname)),
                              typeStr,
                              *defType,
                              string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(defaultValue)));
} // SAXattributeDecl

template<class string_type, class T0, class T1>
string_type  libxml2_wrapper<string_type, T0, T1>::stringAttrEnum(xmlEnumerationPtr tree, bool leadingSpace) const
{
  std::ostringstream os;
  if(leadingSpace)
    os << " ";
  os << "(";
  while(tree)
  {
    os << tree->name;
    tree = tree->next;
    if(tree)
      os << " | ";
  } // while
  os << ")";

  return string_adaptor::construct_from_utf8(os.str().c_str());
} // stringAttrEnum

template<class string_type, class T0, class T1>
void libxml2_wrapper<string_type, T0, T1>::SAXentityDecl(const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId,	xmlChar *content)
{
  if(!declHandler_)
    return;

  switch(type)
  {
    case 1:  // internal
      declHandler_->internalEntityDecl(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(name)),
                                       string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(content)));
      break;
    case 2:  // external
      declHandler_->externalEntityDecl(string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(name)),
                                       string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(publicId)),
                                       string_adaptor::construct_from_utf8(reinterpret_cast<const char*>(systemId)));
      break;
  } // switch
} // SAXentityDecl

template<class string_type, class T0, class T1>
xmlParserInputPtr libxml2_wrapper<string_type, T0, T1>::SAXresolveEntity(const xmlChar* publicId, const xmlChar* systemId)
{
  if(!entityResolver_)
    return xmlLoadExternalEntity(reinterpret_cast<const char*>(systemId),
                                 reinterpret_cast<const char*>(publicId),
                                 context_);
  return 0;
} // SAXresolveEntity


} // namespace SAX
} // namespace Arabica

#endif
