#ifndef ARABICA_SAX_LIBXML2_H 
#define ARABICA_SAX_LIBXML2_H 
////////////////////////////////////////////////////////////////
// A SAX2 Wrapper for libxml2
//
// $Id$
////////////////////////////////////////////////////////////////

#include <SAX/ArabicaConfig.h>
#include <SAX/XMLReader.h>
#include <SAX/SAXParseException.h>
#include <SAX/InputSource.h>
#include <SAX/SAXNotSupportedException.h>
#include <SAX/SAXNotRecognizedException.h>
#include <libxml/parser.h>

#include <string>
#include <cstdarg>
#include <typeinfo>

#include <SAX/ext/LexicalHandler.h>
#include <SAX/ext/DeclHandler.h>
#include <SAX/helpers/FeatureNames.h>
#include <SAX/helpers/PropertyNames.h>
#include <SAX/helpers/NamespaceSupport.h>
#include <SAX/helpers/AttributeDefaults.h>
#include <SAX/helpers/AttributeTypes.h>
#include <SAX/helpers/InputSourceResolver.h>
#include <SAX/helpers/AttributesImpl.h>

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

template<class string_type, class string_adaptor_type = default_string_adaptor<string_type> >
class libxml2_wrapper : public basic_XMLReader<string_type>,
                        public basic_Locator<string_type>,
                        protected libxml2_wrapper_impl_tiddle::libxml2_base
{
  public:
    typedef string_type stringT;
    typedef string_adaptor_type string_adaptorT;
    typedef SAX::basic_EntityResolver<stringT> entityResolverT;
    typedef SAX::basic_DTDHandler<stringT> dtdHandlerT;
    typedef SAX::basic_ContentHandler<stringT> contentHandlerT;
    typedef SAX::basic_DeclHandler<stringT> declHandlerT;
    typedef SAX::basic_LexicalHandler<stringT> lexicalHandlerT;
    typedef SAX::basic_InputSource<stringT> inputSourceT;
    typedef SAX::basic_Locator<stringT> locatorT;
    typedef SAX::basic_NamespaceSupport<stringT, string_adaptorT> namespaceSupportT;

    libxml2_wrapper();
    ~libxml2_wrapper();

    ////////////////////////////////////////////////
    // configuration
    virtual bool getFeature(const stringT& name) const;
    virtual void setFeature(const stringT& name, bool value);

    ////////////////////////////////////////////////
    // Event Handlers
    virtual void setEntityResolver(basic_EntityResolver<stringT>& resolver) { entityResolver_ = &resolver; }
    virtual basic_EntityResolver<stringT>* getEntityResolver() const { return entityResolver_; }
    virtual void setDTDHandler(basic_DTDHandler<stringT>& handler) { dtdHandler_ = &handler; }
    virtual basic_DTDHandler<stringT>* getDTDHandler() const { return dtdHandler_; }
    virtual void setContentHandler(basic_ContentHandler<stringT>& handler) { contentHandler_ = &handler; }
    virtual basic_ContentHandler<stringT>* getContentHandler() const { return contentHandler_; }
    virtual void setErrorHandler(ErrorHandler& handler) { errorHandler_ = &handler; }
    virtual ErrorHandler* getErrorHandler() const { return errorHandler_; }

    ////////////////////////////////////////////////
    // parsing
    virtual void parse(basic_InputSource<stringT>& source);

  protected:
    ////////////////////////////////////////////////
    // properties
    virtual std::auto_ptr<typename basic_XMLReader<stringT>::PropertyBase> doGetProperty(const stringT& name);
    virtual void doSetProperty(const stringT& name, std::auto_ptr<typename basic_XMLReader<stringT>::PropertyBase> value);

  public:
    virtual stringT getPublicId() const;
    virtual stringT getSystemId() const;
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
    virtual void SAXstartElement(const xmlChar* name, const xmlChar** attrs);
    virtual void SAXstartElementNoNS(const xmlChar* name, const xmlChar** attrs);
    virtual void SAXendElement(const xmlChar* name);
    virtual void SAXendElementNoNS(const xmlChar* name);
    virtual void SAXnotationDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId);
    virtual void SAXunparsedEntityDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName);
    virtual void SAXelementDecl(const xmlChar* name, int type, xmlElementContentPtr content);
    void convertXML_Content(std::ostream& os, int type, xmlElementContentPtr model, bool isChild) const;
    virtual void SAXattributeDecl(const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree);
    stringT stringAttrEnum(xmlEnumerationPtr tree, bool leadingSpace) const;
    virtual void SAXentityDecl(const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId,	xmlChar *content);
    virtual xmlParserInputPtr SAXresolveEntity(const xmlChar* publicId, const xmlChar* systemId);
    
    typename basic_NamespaceSupport<stringT, string_adaptorT>::Parts processName(const stringT& qName, bool isAttribute);
    void reportError(const std::string& message, bool fatal = false);
    void checkNotParsing(const stringT& type, const stringT& name) const;

  private:
    // member variables
    entityResolverT* entityResolver_;
    dtdHandlerT* dtdHandler_;
    contentHandlerT* contentHandler_;
    ErrorHandler* errorHandler_;
    namespaceSupportT nsSupport_;
    declHandlerT* declHandler_;

    xmlParserCtxtPtr context_;
		xmlSAXLocatorPtr locator_;

    bool parsing_;

    bool namespaces_;
    bool prefixes_;

    string_adaptorT SA_;
    stringT emptyString_;
    const FeatureNames<stringT, string_adaptorT> features_;
    const PropertyNames<stringT, string_adaptorT> properties_;
    const NamespaceConstants<stringT, string_adaptorT> nsc_;
    const AttributeDefaults<stringT, string_adaptorT> attrDefaults_;
    const AttributeTypes<stringT, string_adaptorT> attrTypes_;
}; // class libxml2_wrapper

template<class stringT, class string_adaptorT>
libxml2_wrapper<stringT, string_adaptorT>::libxml2_wrapper() :
  entityResolver_(0),
  dtdHandler_(0),
  contentHandler_(0),
  errorHandler_(0),
  declHandler_(0),
  locator_(0),
  parsing_(false),
  namespaces_(true),
  prefixes_(true)
{
  context_ = xmlCreatePushParserCtxt(libxml2_wrapper_impl_tiddle::lwit_SaxHandler(), reinterpret_cast<void*>(static_cast<libxml2_wrapper_impl_tiddle::libxml2_base*>(this)), 0, 0, 0);
} // libxml2_wrapper 

template<class stringT, class string_adaptorT>
libxml2_wrapper<stringT, string_adaptorT>::~libxml2_wrapper()
{
	xmlFreeParserCtxt(context_);
} // ~libxml2_wrapper

template<class stringT, class string_adaptorT>
bool libxml2_wrapper<stringT, string_adaptorT>::getFeature(const stringT& name) const
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
    throw SAX::SAXNotSupportedException(std::string("Feature not supported ") + SA_.asStdString(name));
  }
  else
  {
    throw SAX::SAXNotRecognizedException(std::string("Feature not recognized ") + SA_.asStdString(name));
  }
} // getFeature

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::setFeature(const stringT& name, bool value)
{
  if(name == features_.namespaces)
  {
    checkNotParsing(SA_.makeStringT("feature"), name);
    namespaces_ = value;
    if(!namespaces_ && !prefixes_)
      prefixes_ = true;
    return;
  }

  if(name == features_.namespace_prefixes)
  {
    checkNotParsing(SA_.makeStringT("feature"), name);
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
    os << "Feature not supported " << SA_.asStdString(name);
    throw SAX::SAXNotSupportedException(os.str());
  }
  else
  {
    std::ostringstream os; 
    os << "Feature not recognized " << SA_.asStdString(name);
    throw SAX::SAXNotRecognizedException(os.str());
  }
} // setFeature

template<class stringT, class string_adaptorT>
#ifndef ARABICA_VS6_WORKAROUND
std::auto_ptr<typename basic_XMLReader<stringT>::PropertyBase> libxml2_wrapper<stringT, string_adaptorT>::doGetProperty(const stringT& name)
#else
std::auto_ptr<basic_XMLReader<stringT>::PropertyBase> libxml2_wrapper<stringT, string_adaptorT>::doGetProperty(const stringT& name)
#endif
{
  if(name == properties_.declHandler)
  {
    typedef SAX::basic_XMLReader<stringT>::Property<declHandlerT *> dhp_type;
    dhp_type *prop = new dhp_type(declHandler_);
#ifndef ARABICA_VS6_WORKAROUND
    return std::auto_ptr<typename SAX::basic_XMLReader<stringT>::PropertyBase>(prop);
#else
    return std::auto_ptr<SAX::basic_XMLReader<stringT>::PropertyBase>(prop);
#endif
  }

  if(name == properties_.lexicalHandler)
    throw SAX::SAXNotSupportedException(std::string("Property not supported ") + SA_.asStdString(name));
  else
    throw SAX::SAXNotRecognizedException(std::string("Property not recognized ") + SA_.asStdString(name));    
} // doGetProperty

template<class stringT, class string_adaptorT>
#ifndef ARABICA_VS6_WORKAROUND
void libxml2_wrapper<stringT, string_adaptorT>::doSetProperty(const stringT& name, std::auto_ptr<typename basic_XMLReader<stringT>::PropertyBase> value)
#else
void libxml2_wrapper<stringT, string_adaptorT>::doSetProperty(const stringT& name, std::auto_ptr<basic_XMLReader<stringT>::PropertyBase> value)
#endif
{
  if(name == properties_.declHandler)
  {
    SAX::basic_XMLReader<stringT>::Property<declHandlerT&>* prop = 
          dynamic_cast<SAX::basic_XMLReader<stringT>::Property<declHandlerT&>*>(value.get());

    if(!prop)
      // no std::bad_cast( const char * ) or std::bad_cast( const string& )
      // see ISO-IEC-14882-1998
      throw std::bad_cast(); // ("Property DeclHandler is wrong type, should be SAX::DeclHandler&");

    declHandler_ = &(prop->get());
    return;
  } // if ...

  if(name == properties_.lexicalHandler)
    throw SAX::SAXNotSupportedException(std::string("Property not supported ") + SA_.asStdString(name));
  else
    throw SAX::SAXNotRecognizedException(std::string("Property not recognized ") + SA_.asStdString(name));    
} // doSetProperty

template<class stringT, class string_adaptorT>
typename basic_NamespaceSupport<stringT, string_adaptorT>::Parts libxml2_wrapper<stringT, string_adaptorT>::processName(const stringT& qName, bool isAttribute)
{
  typename basic_NamespaceSupport<stringT, string_adaptorT>::Parts p =
    nsSupport_.processName(qName, isAttribute);
  if(!p.URI.length() && p.prefix.length())
    reportError(std::string("Undeclared prefix ") + SA_.asStdString(qName));
  return p;
} // processName

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::reportError(const std::string& message, bool fatal)
{
  if(!errorHandler_)
    return;
  
  SAX::SAXParseException e(message, *this);
  if(fatal)
    errorHandler_->fatalError(e);
  else
    errorHandler_->error(e);
} // reportError

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::checkNotParsing(const stringT& type, const stringT& name) const
{
  if(parsing_)
  {
    std::ostringstream os;
    os << "Can't change " << SA_.asStdString(type) << " " << SA_.asStdString(name) << " while parsing";
    throw SAX::SAXNotSupportedException(os.str());
  } // if(parsing_)
} // checkNotParsing

template<class stringT, class string_adaptorT>
stringT libxml2_wrapper<stringT, string_adaptorT>::getPublicId() const
{
  if(locator_)
	  return SA_.makeStringT(reinterpret_cast<const char*>(locator_->getPublicId(context_)));
  return std::string();
} // getPublicId

template<class stringT, class string_adaptorT>
stringT libxml2_wrapper<stringT, string_adaptorT>::getSystemId() const
{
  if(locator_)
	  return SA_.makeStringT(reinterpret_cast<const char*>(locator_->getSystemId(context_)));
  return std::string();
} // getSystemId

template<class stringT, class string_adaptorT>
int libxml2_wrapper<stringT, string_adaptorT>::getLineNumber() const
{
  if(locator_)
    return locator_->getLineNumber(context_);
  return -1;
} // getLineNumber

template<class stringT, class string_adaptorT>
int libxml2_wrapper<stringT, string_adaptorT>::getColumnNumber() const
{
  if(locator_)
    return locator_->getColumnNumber(context_);
  return -1;
} // getColumnNumber

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::parse(basic_InputSource<stringT>& source)
{
  if(contentHandler_)
    contentHandler_->setDocumentLocator(*this);

  InputSourceResolver is(source, SA_);
  if(is.resolve() == 0)
    return;

  parsing_ = true;

	while(!is.resolve()->eof())
 	{
		char buffer[1024];
    is.resolve()->read(buffer, sizeof(buffer));
		xmlParseChunk(context_, buffer, is.resolve()->gcount(), is.resolve()->eof());
	} // while(!in.eof())

  parsing_ = false;
} // parse

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXstartDocument()
{
  if(contentHandler_)
    contentHandler_->startDocument();
} // SAXstartDocument

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXendDocument()
{
  if(contentHandler_)
    contentHandler_->endDocument();
} // SAXendDocument

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXcharacters(const xmlChar* ch, int len)
{
  if(contentHandler_)
    contentHandler_->characters(SA_.makeStringT(reinterpret_cast<const char*>(ch), len));
} // SAXcharacters

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXignorableWhitespace(const xmlChar* ch, int len)
{
  if(contentHandler_)
    contentHandler_->ignorableWhitespace(SA_.makeStringT(reinterpret_cast<const char*>(ch), len));
} // SAXignorableWhitespace

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXwarning(const std::string& warning)
{
  if(errorHandler_)
    errorHandler_->warning(basic_SAXParseException<stringT>(warning, *this));
} // warning

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXerror(const std::string& error)
{
  if(errorHandler_)
    errorHandler_->error(basic_SAXParseException<stringT>(error, *this));
} // error

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXfatalError(const std::string& fatal)
{
  if(errorHandler_)
    errorHandler_->fatalError(basic_SAXParseException<stringT>(fatal, *this));
} // fatal

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXprocessingInstruction(const xmlChar* target, const xmlChar* data)
{
  if(contentHandler_)
    contentHandler_->processingInstruction(SA_.makeStringT(reinterpret_cast<const char*>(target)),
                                           SA_.makeStringT(reinterpret_cast<const char*>(data)));
} // SAXprocessingInstruction

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXstartElement(const xmlChar* qName, const xmlChar** atts)
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
  bool seenDecl = false;
  SAX::basic_AttributesImpl<stringT> attributes;

  // take a first pass and copy all the attributes, noting any declarations
  if(atts && *atts != 0)
  {
    while(*atts != 0)
    {
      stringT attQName = SA_.makeStringT(reinterpret_cast<const char*>(*atts++));
      stringT value = SA_.makeStringT(reinterpret_cast<const char*>(*atts++));

      // declaration?
      if(attQName.find(nsc_.xmlns) == 0) 
      {
        stringT prefix;
        typename stringT::size_type n = attQName.find(nsc_.colon);
        if(n != stringT::npos)
          prefix = stringT(attQName.begin() + n + 1, attQName.end());
        if(!nsSupport_.declarePrefix(prefix, value)) 
          reportError(std::string("Illegal Namespace prefix ") + SA_.asStdString(prefix));
        contentHandler_->startPrefixMapping(prefix, value);
        if(prefixes_)
          attributes.addAttribute(emptyString_, 
                                  emptyString_, 
                                  attQName, 
                                  emptyString_, 
                                  value);
        seenDecl = true;
      }
      else
      {
        typename basic_NamespaceSupport<stringT, string_adaptorT>::Parts attName = processName(attQName, true);
        attributes.addAttribute(attName.URI, attName.localName, attName.rawName, emptyString_, value);
      }
    } // while ...
  } // if ...

  // if there was a Namespace decl we have to go around again
  if(seenDecl)
  {
     int length = attributes.getLength();
     for(int i = 0; i < length; ++i)
     {
       stringT attQName = attributes.getQName(i);
       if(attQName.find(nsc_.xmlns)) 
       {
         typename basic_NamespaceSupport<stringT, string_adaptorT>::Parts attName = processName(attQName, true);
         attributes.setURI(i, attName.URI);
         attributes.setLocalName(i, attName.localName);
       } // if ...
     } // for ... 
  } // if(seenDecl)

  // at last! report the event
  typename basic_NamespaceSupport<stringT, string_adaptorT>::Parts name = processName(SA_.makeStringT(reinterpret_cast<const char*>(qName)), false);
  contentHandler_->startElement(name.URI, name.localName, name.rawName, attributes);
} // SAXstartElement

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXstartElementNoNS(const xmlChar* qName, const xmlChar** atts)
{
  SAX::basic_AttributesImpl<stringT> attributes;

  if(atts && *atts != 0)
  {
    while(*atts != 0)
    {
      stringT attQName = SA_.makeStringT(reinterpret_cast<const char*>(*atts++));
      stringT value = SA_.makeStringT(reinterpret_cast<const char*>(*atts++));

      attributes.addAttribute(emptyString_, emptyString_, attQName, emptyString_, value);
    } // while ..
  } // if ...

  contentHandler_->startElement(emptyString_, emptyString_, SA_.makeStringT((reinterpret_cast<const char*>(qName))), attributes);
} // SAXstartElementNoNS

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXendElement(const xmlChar* qName)
{
  if(!contentHandler_)
    return;

  if(!namespaces_)
  {
    SAXendElementNoNS(qName);
    return;
  } // if(!namespaces_)

  typename basic_NamespaceSupport<stringT, string_adaptorT>::Parts name = processName(SA_.makeStringT(reinterpret_cast<const char*>(qName)), false);
  contentHandler_->endElement(name.URI, name.localName, name.rawName);
  typename basic_NamespaceSupport<stringT, string_adaptorT>::stringListT prefixes = nsSupport_.getDeclaredPrefixes();
  for(size_t i = 1, end = prefixes.size(); i < end; ++i)
    contentHandler_->endPrefixMapping(prefixes[i]);
  nsSupport_.popContext();
} // SAXendElement

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXendElementNoNS(const xmlChar* qName)
{
  if(contentHandler_)
    contentHandler_->endElement(emptyString_, emptyString_, SA_.makeStringT(reinterpret_cast<const char*>(qName)));
} // SAXendElementNoNS

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXnotationDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId)
{
  if(dtdHandler_)
    dtdHandler_->notationDecl(SA_.makeStringT(reinterpret_cast<const char*>(name)), 
                              SA_.makeStringT(reinterpret_cast<const char*>(publicId)), 
                              SA_.makeStringT(reinterpret_cast<const char*>(systemId)));
} // SAXnotationDecl

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXunparsedEntityDecl(const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName)
{
  if(dtdHandler_)
    dtdHandler_->unparsedEntityDecl(SA_.makeStringT(reinterpret_cast<const char*>(name)), 
                                    SA_.makeStringT(reinterpret_cast<const char*>(publicId)), 
                                    SA_.makeStringT(reinterpret_cast<const char*>(systemId)),
                                    SA_.makeStringT(reinterpret_cast<const char*>(notationName)));
} // SAXunparsedEntityDecl

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXelementDecl(const xmlChar* name, int type, xmlElementContentPtr content)
{
  if(!declHandler_)
    return;

  std::ostringstream os;
  convertXML_Content(os, type, content, false);
  declHandler_->elementDecl(SA_.makeStringT(reinterpret_cast<const char*>(name)), SA_.makeStringT(os.str().c_str()));
} // elementDeclaration

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::convertXML_Content(std::ostream& os, int type, xmlElementContentPtr model, bool isChild) const
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

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXattributeDecl(const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree)
{
  if(!declHandler_)
    return;

  const stringT* defType = &attrDefaults_.implied;
  if(def)
    defType = (defaultValue) ? &attrDefaults_.fixed : &attrDefaults_.required;

  stringT typeStr;
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
      typeStr = attrTypes_.notation + stringAttrEnum(tree, true);
      break;
  } // switch(type)

  declHandler_->attributeDecl(SA_.makeStringT(reinterpret_cast<const char*>(elem)), 
                              SA_.makeStringT(reinterpret_cast<const char*>(fullname)), 
                              typeStr, 
                              *defType, 
                              SA_.makeStringT(reinterpret_cast<const char*>(defaultValue)));
} // SAXattributeDecl

template<class stringT, class string_adaptorT>
stringT  libxml2_wrapper<stringT, string_adaptorT>::stringAttrEnum(xmlEnumerationPtr tree, bool leadingSpace) const
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

  return SA_.makeStringT(os.str().c_str());
} // stringAttrEnum

template<class stringT, class string_adaptorT>
void libxml2_wrapper<stringT, string_adaptorT>::SAXentityDecl(const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId,	xmlChar *content)
{
  if(!declHandler_)
    return;

  switch(type)
  {
    case 1:  // internal
      declHandler_->internalEntityDecl(SA_.makeStringT(reinterpret_cast<const char*>(name)),
                                       SA_.makeStringT(reinterpret_cast<const char*>(content)));
      break;
    case 2:  // external
      declHandler_->externalEntityDecl(SA_.makeStringT(reinterpret_cast<const char*>(name)),
                                       SA_.makeStringT(reinterpret_cast<const char*>(publicId)),
                                       SA_.makeStringT(reinterpret_cast<const char*>(systemId)));
      break;
  } // switch
} // SAXentityDecl

template<class stringT, class string_adaptorT>
xmlParserInputPtr libxml2_wrapper<stringT, string_adaptorT>::SAXresolveEntity(const xmlChar* publicId, const xmlChar* systemId)
{
  if(!entityResolver_)
    return xmlLoadExternalEntity(reinterpret_cast<const char*>(systemId), 
                                 reinterpret_cast<const char*>(publicId), 
                                 context_);
  return 0;
} // SAXresolveEntity


} // namespace SAX

#endif
