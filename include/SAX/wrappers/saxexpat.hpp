#ifndef ARABICA_SAX_EXPAT_H 
#define ARABICA_SAX_EXPAT_H 
//---------------------------------------------------------------------------
// A SAX2 wrapper class for expat.
//---------------------------------------------------------------------------

#include <SAX/ArabicaConfig.hpp>
#include <SAX/XMLReader.hpp>
#include <expat.h>

#include <sstream>
#include <SAX/InputSource.hpp>
#include <SAX/ContentHandler.hpp>
#include <SAX/SAXParseException.hpp>
#include <SAX/SAXNotRecognizedException.hpp>
#include <SAX/SAXNotSupportedException.hpp>
#include <SAX/helpers/DefaultHandler.hpp>
#include <SAX/helpers/AttributesImpl.hpp>
#include <SAX/helpers/NamespaceSupport.hpp>
#include <SAX/helpers/InputSourceResolver.hpp>
#include <SAX/helpers/FeatureNames.hpp>
#include <SAX/helpers/PropertyNames.hpp>
#include <Arabica/StringAdaptor.hpp>
#include <SAX/helpers/AttributeDefaults.hpp>
#include <typeinfo>
#include <map>
#include <Arabica/getparam.hpp>

namespace Arabica
{
namespace SAX
{

////////////////////////////////////////////////////////////////////////////
// the callback functions for expat
namespace expat_wrapper_impl_mumbojumbo
{

extern "C" 
{
void ewim_charHandler(void* data, const char* txt, int txtlen);
void ewim_startElement(void* data, const char* qName, const char** atts);
void ewim_endElement(void* data, const char* qName);
void ewim_processingInstruction(void* userData, const char* target, const char* data);
void ewim_elementDeclaration(void* userData,
                             const XML_Char* name,
                             XML_Content* model);
void ewim_attListDeclaration(void* userData,
                             const XML_Char* elname,
                             const XML_Char* attname,
                             const XML_Char* att_type,
                             const XML_Char* dflt,
                             int isrequired);
void ewim_entityDeclaration(void* userData, 
                            const XML_Char* entityName,
                            int is_parameter_entity,
                            const XML_Char* value,
                            int value_length,
                            const XML_Char* base,
                            const XML_Char* systemId,
                            const XML_Char* publicId,
                            const XML_Char* notationName);
void ewim_notationDeclaration(void* userData,
                              const XML_Char* notationName,
                              const XML_Char* base,
                              const XML_Char* systemId,
                              const XML_Char* publicId);
void ewim_startDoctypeDecl(void* userData,
                           const XML_Char* doctypeName,
                           const XML_Char* sysid,
                           const XML_Char* pubid,
                           int has_internal_subset);
void ewim_endDoctypeDecl(void* userData);
void ewim_startCdataSection(void* userData);
void ewim_endCdataSection(void* userData);
void ewim_commentHandler(void* userData, const XML_Char* data);
int ewim_externalEntityRefHandler(XML_Parser parser, 
                                  const XML_Char* context,
                                  const XML_Char* base,
                                  const XML_Char* systemId,
                                  const XML_Char* publicId);

} // extern "C"

class expat2base
{
protected:
  virtual ~expat2base() { }

private:
  virtual void charHandler(const char* txt, int txtlen) = 0;
  virtual void startElement(const char* qName, const char** atts) = 0;
  virtual void endElement(const char* qName) = 0;
  virtual void processingInstruction(const char* target, const char* data) = 0;
  virtual void elementDeclaration(const XML_Char* name,
                                  const XML_Content* model) = 0;
  virtual void attListDeclaration(const XML_Char* elname,
                                  const XML_Char* attname,
                                  const XML_Char* att_type,
                                  const XML_Char* dflt,
                                  int  isrequired) = 0;
  virtual void entityDeclaration(const XML_Char* entityName,
                                 int is_parameter_entity,
                                 const XML_Char* value,
                                 int value_length,
                                 const XML_Char* base,
                                 const XML_Char* systemId,
                                 const XML_Char* publicId,
                                 const XML_Char* notationName) = 0;
  virtual void notationDeclaration(const XML_Char* notationName,
                                   const XML_Char* base,
                                   const XML_Char* systemId,
                                   const XML_Char* publicId) = 0;
  virtual void startDoctypeDecl(const XML_Char* doctypeName,
                                const XML_Char* sysid,
                                const XML_Char* pubid,
                                int has_internal_subset) = 0;
  virtual void endDoctypeDecl() = 0;
  virtual void startCdataSection() = 0;
  virtual void endCdataSection() = 0;
  virtual void commentHandler(const XML_Char* data) = 0;
  virtual int externalEntityRefHandler(XML_Parser parser, 
                                       const XML_Char* context,
                                       const XML_Char* base,
                                       const XML_Char* systemId,
                                       const XML_Char* publicId) = 0;


  friend void ewim_charHandler(void*, const char*, int);
  friend void ewim_startElement(void*, const char*, const char**);
  friend void ewim_endElement(void*, const char*);
  friend void ewim_processingInstruction(void*, const char*, const char*);
  friend void ewim_elementDeclaration(void*, const XML_Char*, XML_Content*);
  friend void ewim_attListDeclaration(void*, const XML_Char*, const XML_Char*, const XML_Char*, const XML_Char*,  int);
  friend void ewim_entityDeclaration(void*, const XML_Char*, int, const XML_Char*, int, const XML_Char*, const XML_Char*, const XML_Char*, const XML_Char*);
  friend void ewim_notationDeclaration(void*, const XML_Char*, const XML_Char*, const XML_Char*, const XML_Char*);
  friend void ewim_startDoctypeDecl(void*, const XML_Char*, const XML_Char*, const XML_Char*, int);
  friend void ewim_endDoctypeDecl(void*);
  friend void ewim_startCdataSection(void*);
  friend void ewim_endCdataSection(void*);
  friend void ewim_commentHandler(void*, const XML_Char*);
  friend int ewim_externalEntityRefHandler(XML_Parser, const XML_Char*, const XML_Char*, const XML_Char*, const XML_Char*);

}; // class expat2base

} // namespace expat_wrapper_impl_mumbojumbo

////////////////////////////////////////////////////////////////////////////
// A SAX2 wrapper for expat.  expat has an event-based interface of its own,
// so the SAX wrapper maps more or less directly to it.

/**
 * expat_wrapper puts an {@link XMLReader XMLReader} interface
 * around <a href='http://www.libexpat.org/'>Expat</a>.
 * <p>
 * For general usage:<br>
 * <code>
 * &nbsp;&nbsp;expat_wrapper<std::string> parser;<br>
 * &nbsp;&nbsp;... <br>
 * &nbsp;&nbsp;parser.parse(filename);<br>
 * </code>
 * expat_wrapper<std::string> will hand out std::strings containing UTF-8 encoded
 * data (expat's native format).  
 * <p>
 * If you need std::wstring containing UCS-2 or perhaps you want to use some custom
 * string type, then you can simply instantiate expat_wrapper on your string type and 
 * a policy class which knows how to convert UTF-8 const char*s to your type.
 * <p>
 * The default policy is:
 * <code>
 * template<class stringT><br>
 * class default_expat_string_convertor<br>
 * {<br>
 * public:<br>
 * &nbsp;&nbsp;stringT makeStringT(const char* str) const<br>
 * &nbsp;&nbsp;{<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if(!str)<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;return stringT();<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;return stringT(str);<br>
 * &nbsp;&nbsp;} // makeStringT<br>
 * &nbsp;&nbsp;stringT makeStringT(const char* str, int length) const<br>
 * &nbsp;&nbsp;{<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;return stringT(str, length);<br>
 * &nbsp;&nbsp;} // makeStringT<br>
 * <br>
 * &nbsp;&nbsp;std::string asStdString(const stringT& str) const<br>
 * &nbsp;&nbsp;{<br>
 * &nbsp;&nbsp;&nbsp;&nbsp;return str;<br>
 * &nbsp;&nbsp;} // asStdString<br>
 * }; // class default_string_convertor<br>
 * </code>
 * <p>
 * A custom policy needs to provide the equivalent makeString and asStdString functions.
 * <p>
 * @author Jez Higgins
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version $Id$
 * @see SAX::XMLReader
 */
template<class string_type, 
         class T0 = Arabica::nil_t,
         class T1 = Arabica::nil_t>
class expat_wrapper : 
    public SAX::XMLReaderInterface<string_type, 
                                   typename Arabica::get_string_adaptor<string_type, T0, T1>::type>,
    public SAX::Locator<string_type, typename Arabica::get_string_adaptor<string_type, T0, T1>::type>,
    public expat_wrapper_impl_mumbojumbo::expat2base
{
  public:
    typedef SAX::XMLReaderInterface<string_type, 
                                    typename Arabica::get_string_adaptor<string_type, T0, T1>::type> XMLReaderT;
    typedef typename XMLReaderT::string_adaptor string_adaptor;
    typedef string_adaptor SA;
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

    expat_wrapper();
    virtual ~expat_wrapper();

    /////////////////////////////////////////////////
    // Configuration
    virtual bool getFeature(const string_type& name) const;
    virtual void setFeature(const string_type& name, bool value);
  
    /////////////////////////////////////////////////
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

    //////////////////////////////////////////////////
    // Parsing
    virtual void parse(inputSourceT& input);
  private:
    bool do_parse(inputSourceT& source, XML_Parser parser);

  public:
    //////////////////////////////////////////////////
    // Locator
    virtual string_type getPublicId() const;
    virtual string_type getSystemId() const;
    virtual int getLineNumber() const;
    virtual int getColumnNumber() const;

    ///////////////////////////////////////////////////
    // properties
  protected:
    virtual std::auto_ptr<PropertyBaseT> doGetProperty(const string_type& name);
    virtual void doSetProperty(const string_type& name, std::auto_ptr<PropertyBaseT> value);
  private:
    qualifiedNameT processName(const string_type& qName, bool isAttribute);
    void reportError(const std::string& message, bool fatal = false);
    void checkNotParsing(const string_type& type, const string_type& name) const;
  
  private:
    virtual void charHandler(const char* txt, int txtlen);
    virtual void startElement(const char* qName, const char** atts);
    virtual void endElement(const char* qName);
    virtual void processingInstruction(const char* target, const char* data);
    virtual void elementDeclaration(const XML_Char* name,
                                    const XML_Content* model);
    virtual void attListDeclaration(const XML_Char* elname,
                                    const XML_Char* attname,
                                    const XML_Char* att_type,
                                    const XML_Char* dflt,
                                    int  isrequired);
    virtual void entityDeclaration(const XML_Char* entityName,
                                   int is_parameter_entity,
                                   const XML_Char* value,
                                   int value_length,
                                   const XML_Char* base,
                                   const XML_Char* systemId,
                                   const XML_Char* publicId,
                                   const XML_Char* notationName);
    virtual void notationDeclaration(const XML_Char* notationName,
                                     const XML_Char* base,
                                     const XML_Char* systemId,
                                     const XML_Char* publicId);
    virtual void startDoctypeDecl(const XML_Char* doctypeName,
                                  const XML_Char* sysid,
                                  const XML_Char* pubid,
                                  int has_internal_subset);
    virtual void endDoctypeDecl();
    virtual void startCdataSection();
    virtual void endCdataSection();
    virtual void commentHandler(const XML_Char* data);
    virtual int externalEntityRefHandler(XML_Parser parser, 
                                         const XML_Char* context,
                                         const XML_Char* base,
                                         const XML_Char* systemId,
                                         const XML_Char* publicId);


  private:
    void setCallbacks();
    void startElementNoNS(const char* qName, const char** atts);
    void endElementNoNS(const char* qName);
    void convertXML_Content(std::ostream& os, const XML_Content* model, bool isChild = false);

    // member variables
    entityResolverT* entityResolver_;
    dtdHandlerT* dtdHandler_;
    contentHandlerT* contentHandler_;
    errorHandlerT* errorHandler_;
    declHandlerT* declHandler_;
    lexicalHandlerT* lexicalHandler_;
    namespaceSupportT nsSupport_;

    XML_Parser parser_;
    string_type publicId_;
    string_type systemId_;
    bool parsing_;

    // features
    bool namespaces_;
    bool prefixes_;
    bool externalResolving_;

    string_type emptyString_;
    const SAX::FeatureNames<string_type, string_adaptor> features_;
    const SAX::PropertyNames<string_type, string_adaptor> properties_;
    const SAX::NamespaceConstants<string_type, string_adaptor> nsc_;
    const SAX::AttributeDefaults<string_type, string_adaptor> attrDefaults_;

    std::map<string_type, string_type> declaredExternalEnts_;
}; // class expat_wrapper

//////////////////////////////////////////////////////////////////
// expat wrapper definition
template<class string_type, class T0, class T1>
expat_wrapper<string_type, T0, T1>::expat_wrapper() :
  entityResolver_(0),
  dtdHandler_(0),
  contentHandler_(0),
  errorHandler_(0),
  declHandler_(0),
  lexicalHandler_(0),
  parser_(XML_ParserCreate(0)),
  parsing_(false),
  namespaces_(true),
  prefixes_(true),
  externalResolving_(false)
{
} // expat

template<class string_type, class T0, class T1>
expat_wrapper<string_type, T0, T1>::~expat_wrapper()
{
  XML_ParserFree(parser_);
} // ~expat

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::setCallbacks()
{
  XML_SetUserData(parser_, reinterpret_cast<void*>(static_cast<expat_wrapper_impl_mumbojumbo::expat2base*>(this)));
  XML_SetCharacterDataHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_charHandler);
  XML_SetElementHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_startElement, expat_wrapper_impl_mumbojumbo::ewim_endElement);
  XML_SetElementDeclHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_elementDeclaration);
  XML_SetAttlistDeclHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_attListDeclaration);
  XML_SetEntityDeclHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_entityDeclaration);
  XML_SetNotationDeclHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_notationDeclaration);
  XML_SetDoctypeDeclHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_startDoctypeDecl, expat_wrapper_impl_mumbojumbo::ewim_endDoctypeDecl);
  XML_SetCdataSectionHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_startCdataSection, expat_wrapper_impl_mumbojumbo::ewim_endCdataSection);
  XML_SetCommentHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_commentHandler);
  XML_SetExternalEntityRefHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_externalEntityRefHandler);
  XML_SetProcessingInstructionHandler(parser_, expat_wrapper_impl_mumbojumbo::ewim_processingInstruction);
} // setCallbacks

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::setFeature(const string_type& name, bool value)
{
  if(name == features_.namespaces)
  {
    checkNotParsing(SA::construct_from_utf8("feature"), name);
    namespaces_ = value;
    if(!namespaces_ && !prefixes_)
      prefixes_ = true;
    return;
  } // namespaces

  if(name == features_.namespace_prefixes)
  {
    checkNotParsing(SA::construct_from_utf8("feature"), name);
    prefixes_ = value;
    if(prefixes_ && !namespaces_)
      namespaces_ = true;
    return;
  } // namespace prefixes

  if(name == features_.external_general || name == features_.external_parameter)
  {
    checkNotParsing(SA::construct_from_utf8("feature"), name);
    externalResolving_ = value;
    return;
  } // external entity resolution

#ifndef __BORLANDC__
// this is a hack features validation problem with BCB6 => need to be investigated
  if(name == features_.validation)
  {
    std::ostringstream os; 
    os << "Feature not supported " << SA::asStdString(name);
    throw SAX::SAXNotSupportedException(os.str());
  }
  else
  {
    std::ostringstream os; 
    os << "Feature not recognized " << SA::asStdString(name);
    throw SAX::SAXNotRecognizedException(os.str());
  }
#endif
} // setFeature

template<class string_type, class T0, class T1>
bool expat_wrapper<string_type, T0, T1>::getFeature(const string_type& name) const
{
  if(name == features_.namespaces)
    return namespaces_;

  if(name == features_.namespace_prefixes)
    return prefixes_;

  if(name == features_.external_general || name == features_.external_parameter)
    return externalResolving_;

  if(name == features_.validation)
    return false;

  throw SAX::SAXNotRecognizedException(std::string("Feature not recognized ") + SA::asStdString(name));
} // getFeature

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::parse(inputSourceT& source)
{
  setCallbacks();

  publicId_ = source.getPublicId();
  systemId_ = source.getSystemId();

  if(contentHandler_)
    contentHandler_->setDocumentLocator(*this);

  parsing_ = true;

  if(contentHandler_)
    contentHandler_->startDocument();

  XML_SetParamEntityParsing(parser_, externalResolving_ ? XML_PARAM_ENTITY_PARSING_ALWAYS : XML_PARAM_ENTITY_PARSING_NEVER);

  do_parse(source, parser_);

  if(contentHandler_)
    contentHandler_->endDocument();

  parsing_ = false;

  XML_ParserReset(parser_, 0);
} // parse

template<class string_type, class T0, class T1>
bool expat_wrapper<string_type, T0, T1>::do_parse(inputSourceT& source, XML_Parser parser)  
{
  InputSourceResolver is(source, string_adaptor());
  if(is.resolve() == 0)
  {
    reportError("Could not resolve XML document", true);
    return false;
  } // if(is.resolver() == 0)

  const int BUFF_SIZE = 10*1024;
  while(!is.resolve()->eof())
  {
    char* buffer = (char*)XML_GetBuffer(parser, BUFF_SIZE);
    if(buffer == NULL)
    {
      reportError("Could not acquire expat buffer", true);
      return false;
    } // if ...

    is.resolve()->read(buffer, BUFF_SIZE);
    if(XML_ParseBuffer(parser, is.resolve()->gcount(), is.resolve()->eof()) == 0)
    {
      // error
      reportError(XML_ErrorString(XML_GetErrorCode(parser_)), true);
      return false;
    } // if ...
  } // while

  return true;
} // do_parse

template<class string_type, class T0, class T1>
std::auto_ptr<typename expat_wrapper<string_type, T0, T1>::PropertyBaseT> expat_wrapper<string_type, T0, T1>::doGetProperty(const string_type& name)
{
  if(name == properties_.lexicalHandler)
  {
    getLexicalHandlerT* prop = new getLexicalHandlerT(lexicalHandler_);
    return std::auto_ptr<PropertyBaseT>(prop);
  }
  if(name == properties_.declHandler)
  {
    getDeclHandlerT* prop = new getDeclHandlerT(declHandler_);
    return std::auto_ptr<PropertyBaseT>(prop);
  }

  throw SAX::SAXNotRecognizedException(std::string("Property not recognized ") + SA::asStdString(name));    
} // doGetProperty

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::doSetProperty(const string_type& name, std::auto_ptr<PropertyBaseT> value)
{
  if(name == properties_.lexicalHandler)
  {
    setLexicalHandlerT* prop = dynamic_cast<setLexicalHandlerT*>(value.get());

    if(!prop)
      throw std::bad_cast();

    lexicalHandler_ = &(prop->get());
  }
  else if(name == properties_.declHandler)
  {
    setDeclHandlerT* prop = dynamic_cast<setDeclHandlerT*>(value.get());

    if(!prop)
      throw std::bad_cast();

    declHandler_ = &(prop->get());
  }
  else
  {
    std::ostringstream os;
    os << "Property not recognized " << SA::asStdString(name);
    throw SAX::SAXNotRecognizedException(os.str());
  }
} // doSetProperty

// Locator implementation
template<class string_type, class T0, class T1>
string_type expat_wrapper<string_type, T0, T1>::getPublicId() const
{
  return publicId_;
} // getPublicId

template<class string_type, class T0, class T1>
string_type expat_wrapper<string_type, T0, T1>::getSystemId() const
{
  return systemId_;
} // getSystemId

template<class string_type, class T0, class T1>
int expat_wrapper<string_type, T0, T1>::getLineNumber() const
{
  return XML_GetCurrentLineNumber(parser_);
} // getLineNumber

template<class string_type, class T0, class T1>
int expat_wrapper<string_type, T0, T1>::getColumnNumber() const
{
  return XML_GetCurrentColumnNumber(parser_);
} // getColumnNumber

template<class string_type, class T0, class T1>
typename XML::QualifiedName<string_type, typename expat_wrapper<string_type, T0, T1>::string_adaptor> expat_wrapper<string_type, T0, T1>::processName(const string_type& qName, bool isAttribute)
{
  qualifiedNameT p = nsSupport_.processName(qName, isAttribute);
  if(!p.has_namespaceUri() && p.has_prefix())
    reportError(std::string("Undeclared prefix ") + SA::asStdString(qName));
  return p;
} // processName

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::reportError(const std::string& message, bool fatal)
{
  if(!errorHandler_)
    return;
  
  SAXParseExceptionT e(message,
                       publicId_,
           systemId_,
           XML_GetCurrentLineNumber(parser_),
           XML_GetCurrentColumnNumber(parser_));
  if(fatal)
    errorHandler_->fatalError(e);
  else
    errorHandler_->error(e);
} // reportError

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::checkNotParsing(const string_type& type, const string_type& name) const
{
  if(parsing_)
  {
    std::ostringstream os;
    os << "Can't change " << SA::asStdString(type) << " " << SA::asStdString(name) << " while parsing";
    throw SAX::SAXNotSupportedException(os.str());
  } // if(parsing_)
} // checkNotParsing

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::charHandler(const char* txt, int txtlen)
{
  if(!contentHandler_)
    return;
  contentHandler_->characters(SA::construct_from_utf8(txt, txtlen));
} // charHandler

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::startElement(const char* qName, const char** atts)
{
  if(!contentHandler_)
    return;

  if(!namespaces_)
  {
    startElementNoNS(qName, atts);
    return;
  } // if(!namespaces)

  // OK we're doing Namespaces
  nsSupport_.pushContext();
  SAX::AttributesImpl<string_type, string_adaptor> attributes;

  // take a first pass and copy all the attributes, noting any declarations
  if(atts && *atts != 0)
  {
    const char** a1 = atts;
    while(*a1 != 0)
    {
      string_type attQName = SA::construct_from_utf8(*a1++);
      string_type value = SA::construct_from_utf8(*a1++);

      // declaration?
      if(SA::find(attQName, nsc_.xmlns) == 0) 
      {
        string_type prefix;
        typename SA::size_type n = SA::find(attQName, nsc_.colon);
        if(n != SA::npos())
          prefix = SA::construct(SA::begin(attQName) + n + 1, SA::end(attQName));
        if(!nsSupport_.declarePrefix(prefix, value)) 
          reportError(std::string("Illegal Namespace prefix ") + SA::asStdString(prefix));
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
      string_type attQName = SA::construct_from_utf8(*atts++);
      string_type value = SA::construct_from_utf8(*atts++);

      // declaration?
      if(SA::find(attQName, nsc_.xmlns) != 0) 
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
  qualifiedNameT name = processName(SA::construct_from_utf8(qName), false);
  contentHandler_->startElement(name.namespaceUri(), name.localName(), name.rawName(), attributes);
} // startElement

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::startElementNoNS(const char* qName, const char** atts)
{
  SAX::AttributesImpl<string_type, string_adaptor> attributes;

  if(atts && *atts != 0)
  {
    while(*atts != 0)
    {
      string_type attQName = SA::construct_from_utf8(*atts++);
      string_type value = SA::construct_from_utf8(*atts++);

      attributes.addAttribute(emptyString_, 
                              emptyString_, 
                              attQName, 
                              attributeTypeT::CDATA,
                              value);
    } // while ..
  } // if ...

  contentHandler_->startElement(emptyString_, emptyString_, SA::construct_from_utf8(qName), attributes);
} // startElementNoNS

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::endElement(const char* qName)
{
  if(!contentHandler_)
    return;

  if(!namespaces_)
  {
    endElementNoNS(qName);
    return;
  } // if(!namespaces_)

  qualifiedNameT name = processName(SA::construct_from_utf8(qName), false);
  contentHandler_->endElement(name.namespaceUri(), name.localName(), name.rawName());
  typename namespaceSupportT::stringListT prefixes = nsSupport_.getDeclaredPrefixes();
  for(size_t i = 0, end = prefixes.size(); i < end; ++i)
    contentHandler_->endPrefixMapping(prefixes[i]);
  nsSupport_.popContext();
} // endElement

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::endElementNoNS(const char* qName)
{
  if(contentHandler_)
    contentHandler_->endElement(emptyString_, emptyString_, SA::construct_from_utf8(qName));    
} // endElementNoNS

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::processingInstruction(const char* target, const char* data)
{
  if(contentHandler_)
    contentHandler_->processingInstruction(SA::construct_from_utf8(target), SA::construct_from_utf8(data));
} // processingInstruction

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::elementDeclaration(const XML_Char* name,
                                         const XML_Content* model)
{
  if(!declHandler_)
    return;

  std::ostringstream os;
  convertXML_Content(os, model);
  declHandler_->elementDecl(SA::construct_from_utf8(name), SA::construct_from_utf8(os.str().c_str()));
} // elementDeclaration

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::convertXML_Content(std::ostream& os, const XML_Content* model, bool isChild)
{
/*
enum XML_Content_Type {
  XML_CTYPE_EMPTY = 1,
  XML_CTYPE_ANY,
  XML_CTYPE_MIXED,
  XML_CTYPE_NAME,
  XML_CTYPE_CHOICE,
  XML_CTYPE_SEQ
};

enum XML_Content_Quant {
  XML_CQUANT_NONE,
  XML_CQUANT_OPT,
  XML_CQUANT_REP,
  XML_CQUANT_PLUS
};

 If type == XML_CTYPE_EMPTY or XML_CTYPE_ANY, then quant will be
   XML_CQUANT_NONE, and the other fields will be zero or NULL.
   If type == XML_CTYPE_MIXED, then quant will be NONE or REP and
   numchildren will contain number of elements that may be mixed in
   and children point to an array of XML_Content cells that will be
   all of XML_CTYPE_NAME type with no quantification.

   If type == XML_CTYPE_NAME, then the name points to the name, and
   the numchildren field will be zero and children will be NULL. The
   quant fields indicates any quantifiers placed on the name.

   CHOICE and SEQ will have name NULL, the number of children in
   numchildren and children will point, recursively, to an array
   of XML_Content cells.

   The EMPTY, ANY, and MIXED types will only occur at top level.

typedef struct XML_cp XML_Content;

struct XML_cp {
  enum XML_Content_Type    type;
  enum XML_Content_Quant  quant;
  const XML_Char *    name;
  unsigned int      numchildren;
  XML_Content *      children;
};
*/
  char concatenator = ' ';

  switch(model->type)
  {
    case XML_CTYPE_EMPTY:
      os << "EMPTY";
      break;
    case XML_CTYPE_ANY:
      os << "ANY";
      break;
    case XML_CTYPE_MIXED:
      if(model->numchildren == 0)
        os << "(#PCDATA)";
      else
        os << "(#PCDATA";
      concatenator = '|';
      break;
    case XML_CTYPE_NAME:
      if(!isChild)
        os << '(' << model->name << ')';
      else
        os << model->name;
      break;
    case XML_CTYPE_CHOICE:
      concatenator = '|';
      break;
    case XML_CTYPE_SEQ:
      concatenator = ',';
      break;
  } // switch

  // do children here
  if(model->numchildren)
  {
    if(model->type != XML_CTYPE_MIXED)
      os << '(';

    for(unsigned int i = 0; i < model->numchildren; ++i)
    {
      if(i != 0)
        os << concatenator;
      convertXML_Content(os, &(model->children[i]), true); 
    } // for ... 

    os << ')';
  } // if ... 

  switch(model->quant)
  {
    case XML_CQUANT_NONE:
      break;
    case XML_CQUANT_OPT:
      os << "?";
      break;
    case XML_CQUANT_REP:
      os << "*";
      break;
    case XML_CQUANT_PLUS:
      os << "+";
      break;
  } // switch
} // convertXML_Content

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::attListDeclaration(const XML_Char* elname, 
                                     const XML_Char* attname,
                                     const XML_Char* att_type,
                                     const XML_Char* dflt,
                                     int isrequired)
{
  /* The Attlist declaration handler is called for *each* attribute. So
  a single Attlist declaration with multiple attributes declared will
  generate multiple calls to this handler. The "default" parameter
  may be NULL in the case of the "#IMPLIED" or "#REQUIRED" keyword.
  The "isrequired" parameter will be true and the default value will
  be NULL in the case of "#REQUIRED". If "isrequired" is true and
  default is non-NULL, then this is a "#FIXED" default. */
  if(declHandler_)
  {
    const string_type* defType = &attrDefaults_.implied;
    if(isrequired)
      defType = dflt ? &attrDefaults_.fixed : &attrDefaults_.required;
    declHandler_->attributeDecl(SA::construct_from_utf8(elname), 
                                SA::construct_from_utf8(attname), 
                                SA::construct_from_utf8(att_type), 
                                *defType, 
                                SA::construct_from_utf8(dflt));
  }
} // attListDeclaration

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::entityDeclaration(const XML_Char* entityName,
                           int /*is_parameter_entity*/,
                           const XML_Char* value,
                           int value_length,
                           const XML_Char* /*base*/,
                           const XML_Char* systemId,
                           const XML_Char* publicId,
                           const XML_Char* notationName)
{
/*   For internal entities (<!ENTITY foo "bar">), value will
   be non-null and systemId, publicID, and notationName will be null.
   The value string is NOT null terminated; the length is provided in
   the value_length argument. Since it is legal to have zero-length
   values, do not use this argument to test for internal entities.

   For external entities, value will be null and systemId will be non-null.
   The publicId argument will be null unless a public identifier was
   provided. The notationName argument will have a non-null value only
   for unparsed entity declarations. */

  const string_type s_entityName(SA::construct_from_utf8(entityName));
  if(!systemId && !publicId && !notationName)
  {
    // internal entity!
    if(declHandler_)
      declHandler_->internalEntityDecl(s_entityName, SA::construct_from_utf8(value, value_length));
    return;
  } 

  const string_type s_publicId(SA::construct_from_utf8(publicId));
  const string_type s_systemId(SA::construct_from_utf8(systemId));
  if(notationName == 0)
  {
    if(declHandler_)
      declHandler_->externalEntityDecl(s_entityName, s_publicId, s_systemId);
    declaredExternalEnts_.insert(std::make_pair(s_publicId, s_entityName));
    declaredExternalEnts_.insert(std::make_pair(s_systemId, s_entityName));
  } 
  else
  {
    if(dtdHandler_)
      dtdHandler_->unparsedEntityDecl(s_entityName, s_publicId, s_systemId, SA::construct_from_utf8(notationName));
  } 
} // entityDeclaration

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::notationDeclaration(const XML_Char* notationName,
                             const XML_Char* /*base*/,
                             const XML_Char* systemId,
                             const XML_Char* publicId)
{  
  if(!dtdHandler_)
    return;
  dtdHandler_->notationDecl(SA::construct_from_utf8(notationName), 
                            SA::construct_from_utf8(publicId), 
                            SA::construct_from_utf8(systemId));
} // notationDeclaration

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::startDoctypeDecl(const XML_Char *doctypeName,
                          const XML_Char *systemId,
                          const XML_Char *publicId,
                          int /*has_internal_subset*/)
{
  if(!lexicalHandler_)
    return;

  string_type s_publicId = SA::construct_from_utf8(publicId);
  string_type s_systemId = SA::construct_from_utf8(systemId);
  string_type dtd = SA::construct_from_utf8("[dtd]");
  declaredExternalEnts_.insert(std::make_pair(s_publicId, dtd));
  declaredExternalEnts_.insert(std::make_pair(s_systemId, dtd));
  lexicalHandler_->startDTD(SA::construct_from_utf8(doctypeName),
                            s_publicId, 
                            s_systemId);
} // startDoctypeDecl

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::endDoctypeDecl()
{
  if(lexicalHandler_)
    lexicalHandler_->endDTD();
} // endDoctypeDecl

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::startCdataSection()
{
  if(lexicalHandler_)
    lexicalHandler_->startCDATA();
} // startCdataSection

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::endCdataSection()
{
  if(lexicalHandler_)
    lexicalHandler_->endCDATA();
} // endCdataSection

template<class string_type, class T0, class T1>
void expat_wrapper<string_type, T0, T1>::commentHandler(const XML_Char *data)
{
  if(lexicalHandler_)
    lexicalHandler_->comment(SA::construct_from_utf8(data));
} // commentHandler

template<class string_type, class T0, class T1>
int expat_wrapper<string_type, T0, T1>::externalEntityRefHandler(XML_Parser parser, 
                                                                      const XML_Char* context,
                                                                      const XML_Char* /*base*/,
                                                                      const XML_Char* systemId,
                                                                      const XML_Char* publicId)
{
  string_type pubId(SA::construct_from_utf8(publicId));
  string_type sysId(SA::construct_from_utf8(systemId));

  string_type entityName;
  if(systemId)
    entityName = declaredExternalEnts_[sysId];
  else if(publicId)
    entityName = declaredExternalEnts_[pubId];

  if(!externalResolving_)
  {
    if(!SA::empty(entityName) && contentHandler_)
      contentHandler_->skippedEntity(entityName);

    return 1;
  } // if ...

  ////////////////////////////////////////////////////////
  // resolve external entity
  if(!SA::empty(entityName) && lexicalHandler_)
    lexicalHandler_->startEntity(entityName);

  inputSourceT source;
  if(entityResolver_)
  {
    source = entityResolver_->resolveEntity(pubId, sysId);
    if(SA::empty(source.getPublicId()) && SA::empty(source.getSystemId()))
    {
      source.setPublicId(pubId);
      source.setSystemId(sysId);
    } // if ...
  } 
  else
  {
    source.setPublicId(pubId);
    source.setSystemId(sysId);
  } // if ...

  XML_Parser externalParser = XML_ExternalEntityParserCreate(parser, context, 0);

  bool ok = do_parse(source, externalParser);

  XML_ParserFree(externalParser);

  if(!SA::empty(entityName) && lexicalHandler_)
    lexicalHandler_->endEntity(entityName);

  return ok;
} // externalEntityRefHandler

} // namespace SAX
} // namespace Arabica

#endif
// end of file
