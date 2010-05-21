#ifndef ARABICA_SAX_MSXML2_H
#define ARABICA_SAX_MSXML2_H
//---------------------------------------------------------------------------
// A SAX2 wrapper class for MSXML component.
//---------------------------------------------------------------------------

#include <SAX/ArabicaConfig.hpp>
#include <SAX/XMLReader.hpp>
#include <SAX/InputSource.hpp>
#include <SAX/SAXParseException.hpp>
#include <SAX/SAXNotRecognizedException.hpp>
#include <SAX/SAXNotSupportedException.hpp>
#include <SAX/helpers/PropertyNames.hpp>
#include <Arabica/StringAdaptor.hpp>
#include <iostream>
#include <Arabica/getparam.hpp>

// Include the MSXML definitions.
#include <msxml2.h>

//
// Declare the 'smart pointer' type to simplify COM handling.
#include <comdef.h>
_COM_SMARTPTR_TYPEDEF(ISAXXMLReader, __uuidof(ISAXXMLReader));

namespace Arabica
{
namespace SAX
{

struct COMInitializer_tag { };

/**
 * use this as COMInitializer_type if you call 
 * CoInitialize/CoInitializeEx in your own code
 */
class COMExternalInitializer : public COMInitializer_tag
{
  public:
    COMExternalInitializer() { }
    ~COMExternalInitializer() { }
}; // COMExternalInitializer

class COMSingleThreadInitializer : public COMInitializer_tag
{
  public:
    COMSingleThreadInitializer() { ::CoInitialize(NULL);  }
    ~COMSingleThreadInitializer() { ::CoUninitialize(); }
}; // COMSingleThreadInitializer

#if(_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)
class COMMultiThreadInitializer  : public COMInitializer_tag
{
  public:
    COMMultiThreadInitializer() { ::CoInitializeEx(NULL, COINIT_MULTITHREADED); } 
    ~COMMultiThreadInitializer() { ::CoUninitialize(); }
};
#endif

template<class string_type, 
         class T0 = Arabica::nil_t,
         class T1 = Arabica::nil_t>
class msxml2_wrapper : 
    public SAX::XMLReaderInterface<string_type, 
                                   typename Arabica::get_string_adaptor<string_type, T0, T1>::type>
{
  public:
    typedef SAX::XMLReaderInterface<string_type, typename Arabica::get_param<Arabica::string_adaptor_tag, 
                                     Arabica::default_string_adaptor<string_type>, 
                                     T0, 
                                     T1>::type> XMLReaderT;
    typedef typename XMLReaderT::string_adaptor string_adaptor;
    typedef typename Arabica::get_param<COMInitializer_tag, 
                                        COMSingleThreadInitializer, 
                                        T1, 
                                        T0>::type COMInitializer_type;

    typedef SAX::EntityResolver<string_type, string_adaptor> entityResolverT;
    typedef SAX::DTDHandler<string_type, string_adaptor> dtdHandlerT;
    typedef SAX::ContentHandler<string_type, string_adaptor> contentHandlerT;
    typedef SAX::DeclHandler<string_type, string_adaptor> declHandlerT;
    typedef SAX::LexicalHandler<string_type, string_adaptor> lexicalHandlerT;
    typedef SAX::InputSource<string_type, string_adaptor> inputSourceT;
    typedef SAX::Locator<string_type, string_adaptor> locatorT;
    typedef SAX::ErrorHandler<string_type, string_adaptor> errorHandlerT;
    typedef SAX::Attributes<string_type, string_adaptor> attributesT;

    msxml2_wrapper();
    virtual ~msxml2_wrapper();

    /////////////////////////////////////////////////
    // Configuration
    virtual bool getFeature(const string_type& name) const;
    virtual void setFeature(const string_type& name, bool value);
  
    /////////////////////////////////////////////////
    // Event Handlers
    /* MSXML does not use EntityResolver currently */
    virtual void setEntityResolver(entityResolverT& resolver) { } 
    virtual entityResolverT* getEntityResolver() const { return 0; }
    virtual void setDTDHandler(dtdHandlerT& handler) { dtdHandler_.setDTDHandler(handler); } 
    virtual dtdHandlerT* getDTDHandler() const { return dtdHandler_.getDTDHandler(); }
    virtual void setContentHandler(contentHandlerT& handler) {	contentHandler_.setContentHandler(handler); }
    virtual contentHandlerT* getContentHandler() const { return contentHandler_.getContentHandler(); }
    virtual void setErrorHandler(errorHandlerT& handler);
    virtual errorHandlerT* getErrorHandler() const { return errorHandler_.getErrorHandler(); }
    virtual void setDeclHandler(declHandlerT& handler) { declHandler_.setDeclHandler(handler); }
    virtual declHandlerT* getDeclHandler() const { return declHandler_.getDeclHandler(); }
    virtual void setLexicalHandler(lexicalHandlerT& handler) { lexicalHandler_.setLexicalHandler(handler); }
    virtual lexicalHandlerT* getLexicalHandler() const { return lexicalHandler_.getLexicalHandler(); }

    //////////////////////////////////////////////////
    // Parsing
    virtual void parse(inputSourceT& input);

  protected:
  	virtual std::auto_ptr<typename XMLReaderT::PropertyBase> doGetProperty(const string_type& name)
    {
      if(name == properties_.lexicalHandler)
      {
        Property<lexicalHandlerT*>* prop = new Property<lexicalHandlerT*>(lexicalHandler_.getLexicalHandler());
        return std::auto_ptr<XMLReaderT::PropertyBase>(prop);
      }
      if(name == properties_.declHandler)
      {
        Property<declHandlerT*>* prop = new Property<declHandlerT*>(declHandler_.getDeclHandler());
        return std::auto_ptr<XMLReaderT::PropertyBase>(prop);
      }
      throw SAX::SAXNotRecognizedException("Property not recognized ");    
    } // doGetProperty

	  virtual void doSetProperty(const string_type& name, std::auto_ptr<typename XMLReaderT::PropertyBase> value)
    {
      if(name == properties_.lexicalHandler)
      {
	      Property<lexicalHandlerT&>* prop = dynamic_cast<Property<lexicalHandlerT&>*>(value.get());

        if(!prop)
          throw std::runtime_error("bad_cast: Property LexicalHandler is wrong type, should be SAX::LexicalHandler&");

        lexicalHandler_.setLexicalHandler(prop->get());
        return;
      } // if ...
      if(name == properties_.declHandler)
      {
        Property<declHandlerT&>* prop = dynamic_cast<Property<declHandlerT&>*>(value.get());

        if(!prop)
          throw std::runtime_error("bad_cast: Property DeclHandler is wrong type, should be SAX::DeclHandler&");

        declHandler_.setDeclHandler(prop->get());
        return;
      } // if ...
      throw SAX::SAXNotRecognizedException("Property not recognized ");    
    } // doSetProperty

	private:
    //////////////////////////////////////////////////////
    // COM interface -> C++ interface adaptors
    class LocatorAdaptor : public locatorT
    {
      public:
        LocatorAdaptor() : locator_(0) { }
        LocatorAdaptor(ISAXLocator __RPC_FAR* locator) : locator_(0) { setLocator(locator); } 
        ~LocatorAdaptor() { setLocator(0); }

        string_type getPublicId() const
        {
          if(!locator_) 
            return string_type();

		  const wchar_t* pwchPublicId;
          locator_->getPublicId(&pwchPublicId);
          string_type publicId(string_adaptor::construct_from_utf16(pwchPublicId));
          return publicId;
        } // getPublicId
    
        string_type getSystemId() const
        {
          if(!locator_)
            return string_type();

          const wchar_t* pwchSystemId;
          locator_->getSystemId(&pwchSystemId);
          string_type systemId(string_adaptor::construct_from_utf16(pwchSystemId));
          return systemId;
        } // getSystemId
    
        int getLineNumber() const
        {
          if(!locator_)
            return -1;

          int lineNumber;
          locator_->getLineNumber(&lineNumber);
          return lineNumber;
        } // getLineNumber
    
		int getColumnNumber() const
        {
          if(!locator_)
            return -1;

          int columnNumber;
          locator_->getColumnNumber(&columnNumber);
          return columnNumber;
        } // getColumnNumber
    
        void setLocator(ISAXLocator __RPC_FAR* locator)
        {
          locator_ = locator;
          // no need to AddRef or Release as the ISAXLocator  points to the MSXML instance
          // and we'll clean that up properly anyway
        } // setLocator

      private:
        ISAXLocator __RPC_FAR *locator_;
    }; // class LocatorAdaptor

    class DTDHandlerAdaptor : public ISAXDTDHandler 
    {
      public:
        DTDHandlerAdaptor() : dtdHandler_(0) { }
        ~DTDHandlerAdaptor() { }

		void setDTDHandler(dtdHandlerT& handler) { dtdHandler_ = &handler; }
        dtdHandlerT* getDTDHandler() const { return dtdHandler_; }

    virtual HRESULT STDMETHODCALLTYPE notationDecl( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t *pwchSystemId,
            /* [in] */ int cchSystemId)
        {
          if(dtdHandler_)
            dtdHandler_->notationDecl(string_adaptor::construct_from_utf16(pwchName, cchName),
                                      string_adaptor::construct_from_utf16(pwchPublicId, cchPublicId),
                                      string_adaptor::construct_from_utf16(pwchSystemId, cchSystemId));
          return S_OK;
        } // notationDecl

    virtual HRESULT STDMETHODCALLTYPE unparsedEntityDecl( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t *pwchSystemId,
            /* [in] */ int cchSystemId,
            /* [in] */ const wchar_t *pwchNotationName,
            /* [in] */ int cchNotationName)
	   {
          if(dtdHandler_)
            dtdHandler_->unparsedEntityDecl(string_adaptor::construct_from_utf16(pwchName, cchName),
                                            string_adaptor::construct_from_utf16(pwchPublicId, cchPublicId),
                                            string_adaptor::construct_from_utf16(pwchSystemId, cchSystemId),
                                            string_adaptor::construct_from_utf16(pwchNotationName, cchNotationName));
          return S_OK;
        } // unparsedEntityDecl

        // satify COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject) { return 0; }
        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        dtdHandlerT* dtdHandler_;
    }; // class DTDHandlerAdaptor

    class ErrorHandlerAdaptor : public ISAXErrorHandler 
    {
      public:
        ErrorHandlerAdaptor() : errorHandler_(0), 
                                bWarning_(false), bError_(false), bFatal_(false),
                                eWarning_("none"), eError_("none"), eFatal_("none")
                                { }
        virtual ~ErrorHandlerAdaptor() { }

        void setErrorHandler(errorHandlerT& handler) { errorHandler_ = &handler; }
        errorHandlerT* getErrorHandler() const { return errorHandler_; }

        void setSupplementaryMessage(const std::exception& supplementary) 
        { 
          supplementary_ = supplementary.what(); 
        } // setSupplementaryMessage

        virtual HRESULT STDMETHODCALLTYPE error( 
            /* [in] */ ISAXLocator *pLocator,
            /* [in] */ const wchar_t *pwchErrorMessage,
			/* [in] */ HRESULT hrErrorCode)
        {
          bError_ = true;
          eError_ = SAXParseExceptionT(formatError(pwchErrorMessage), LocatorAdaptor(pLocator));
          return S_OK;
        } // error

        virtual HRESULT STDMETHODCALLTYPE fatalError( 
            /* [in] */ ISAXLocator *pLocator,
            /* [in] */ const wchar_t *pwchErrorMessage,
            /* [in] */ HRESULT hrErrorCode)
        {
          bFatal_ = true;
          eFatal_ = SAXParseExceptionT(formatError(pwchErrorMessage), LocatorAdaptor(pLocator));
          return S_FALSE;
        } // fatalError

        virtual HRESULT STDMETHODCALLTYPE ignorableWarning( 
            /* [in] */ ISAXLocator *pLocator,
            /* [in] */ const wchar_t *pwchErrorMessage,
            /* [in] */ HRESULT hrErrorCode)
        {
          bWarning_ = true;
          eWarning_ = SAXParseExceptionT(formatError(pwchErrorMessage), LocatorAdaptor(pLocator));
          return S_OK;
        } // ignorableWarning

        void report()
        {
          if(!errorHandler_)
            return;

          bool bWarning = bWarning_;
          bool bError = bError_;
          bool bFatal = bFatal_;

          bWarning_ = bError_ = bFatal_ = false;

          if(bFatal)
            errorHandler_->fatalError(eFatal_);
          if(bError)
            errorHandler_->error(eError_);
          if(bWarning)
            errorHandler_->warning(eWarning_);
        } // report

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject) { return 0; }
        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

	  private:
        std::string formatError(const wchar_t *pwchErrorMessage) const
        {
          std::string errorMsg = string_adaptor::asStdString((string_adaptor::construct_from_utf16(pwchErrorMessage)));
          if(!supplementary_.empty())
            errorMsg += ": " + supplementary_;
          return errorMsg;
        } // formatError

        ErrorHandlerAdaptor(const ErrorHandlerAdaptor&);

        typedef SAX::SAXParseException<string_type, string_adaptor> SAXParseExceptionT;
        bool bWarning_;
        bool bError_;
        bool bFatal_;
        SAXParseExceptionT eWarning_;
        SAXParseExceptionT eError_;
        SAXParseExceptionT eFatal_;
        std::string supplementary_;

        errorHandlerT* errorHandler_;
    }; // class ErrorHandlerAdaptor

    class ContentHandlerAdaptor : public ISAXContentHandler 
    {
      public:
        ContentHandlerAdaptor(ErrorHandlerAdaptor& eh) : contentHandler_(0), eh_(eh) { } 
        ~ContentHandlerAdaptor() { }

        void setContentHandler(contentHandlerT& handler) { contentHandler_ = &handler; }
        contentHandlerT* getContentHandler() const { return contentHandler_; }

        virtual HRESULT STDMETHODCALLTYPE putDocumentLocator( 
                               /* [in] */ ISAXLocator *pLocator)
        {
          locator_.setLocator(pLocator);
          if(contentHandler_) 
            try {
              contentHandler_->setDocumentLocator(locator_);
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // putDocumentLocation
        
        virtual HRESULT STDMETHODCALLTYPE startDocument( void)
        {
          if(contentHandler_) 
            try {
              contentHandler_->startDocument();
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // startDocument
        
        virtual HRESULT STDMETHODCALLTYPE endDocument( void)
        {
          if(contentHandler_) 
            try {
              contentHandler_->endDocument();
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // endDocument
        
        virtual HRESULT STDMETHODCALLTYPE startPrefixMapping( 
                                /* [in] */ const wchar_t *pwchPrefix,
                                /* [in] */ int cchPrefix,
                                /* [in] */ const wchar_t *pwchUri,
                                /* [in] */ int cchUri)

        {
          if(contentHandler_)
            try {
              contentHandler_->startPrefixMapping(string_adaptor::construct_from_utf16(pwchPrefix, cchPrefix),
                                                string_adaptor::construct_from_utf16(pwchUri, cchUri));
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // startPrefixMapping
       
        virtual HRESULT STDMETHODCALLTYPE endPrefixMapping( 
                                /* [in] */ const wchar_t *pwchPrefix,
                                /* [in] */ int cchPrefix)
        {
          if(contentHandler_) 
            try {
              contentHandler_->endPrefixMapping(string_adaptor::construct_from_utf16(pwchPrefix, cchPrefix));
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // endPrefixMapping
        
        virtual HRESULT STDMETHODCALLTYPE startElement( 
                                /* [in] */ const wchar_t *pwchNamespaceUri,
                                /* [in] */ int cchNamespaceUri,
                                /* [in] */ const wchar_t *pwchLocalName,
                                /* [in] */ int cchLocalName,
                                /* [in] */ const wchar_t *pwchQName,
                                /* [in] */ int cchQName,
                                /* [in] */ ISAXAttributes *pAttributes)
        {
          if(contentHandler_)
          {
            try {
              AttributesAdaptor attrs(pAttributes);
              contentHandler_->startElement(string_adaptor::construct_from_utf16(pwchNamespaceUri, cchNamespaceUri),
                                            string_adaptor::construct_from_utf16(pwchLocalName, cchLocalName), 
                                            string_adaptor::construct_from_utf16(pwchQName, cchQName), 
                                            attrs);
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          } // if ...
          return S_OK;
        } // startElement
        
        virtual HRESULT STDMETHODCALLTYPE endElement( 
                                /* [in] */ const wchar_t *pwchNamespaceUri,
                                /* [in] */ int cchNamespaceUri,
                                /* [in] */ const wchar_t *pwchLocalName,
                                /* [in] */ int cchLocalName,
                                /* [in] */ const wchar_t *pwchQName,
                                /* [in] */ int cchQName)
        {
          if(contentHandler_)
            try {
              contentHandler_->endElement(string_adaptor::construct_from_utf16(pwchNamespaceUri, cchNamespaceUri), 
                                          string_adaptor::construct_from_utf16(pwchLocalName, cchLocalName), 
                                          string_adaptor::construct_from_utf16(pwchQName, cchQName));
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // endElement
        
        virtual HRESULT STDMETHODCALLTYPE characters( 
            /* [in] */ const wchar_t *pwchChars,
            /* [in] */ int cchChars)
        {
	        if(contentHandler_) 
            try {
              contentHandler_->characters(string_adaptor::construct_from_utf16(pwchChars, cchChars));
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // characters
        
        virtual HRESULT STDMETHODCALLTYPE ignorableWhitespace( 
            /* [in] */ const wchar_t *pwchChars,
            /* [in] */ int cchChars)
        {
          if(contentHandler_)
            try {
               contentHandler_->ignorableWhitespace(string_adaptor::construct_from_utf16(pwchChars, cchChars));
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // ignorableWhitespace
        
        virtual HRESULT STDMETHODCALLTYPE processingInstruction( 
            /* [in] */ const wchar_t *pwchTarget,
            /* [in] */ int cchTarget,
            /* [in] */ const wchar_t *pwchData,
            /* [in] */ int cchData)
        {
          if(contentHandler_)
            try {
              contentHandler_->processingInstruction(string_adaptor::construct_from_utf16(pwchTarget, cchTarget),
                                                     string_adaptor::construct_from_utf16(pwchData, cchData));
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // processingInstruction
        
        virtual HRESULT STDMETHODCALLTYPE skippedEntity( 
            /* [in] */ const wchar_t *pwchName,
			      /* [in] */ int cchName)
        {
          if(contentHandler_)
            try {
              contentHandler_->skippedEntity(string_adaptor::construct_from_utf16(pwchName, cchName));
            }
            catch(const std::exception& e) {
              eh_.setSupplementaryMessage(e);
              throw;
            } // catch
            catch(...) {
              throw;
            }
          return S_OK;
        } // skippedEntity

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject) { return 0; }
        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        ////////////////////////////////////////////////
        // member varaibles
        contentHandlerT* contentHandler_;
        ErrorHandlerAdaptor& eh_;
        LocatorAdaptor locator_;

        //////////////////////////////////////////////////////
        // COM interface -> C++ interface adaptors
        class AttributesAdaptor : public attributesT
        {
          public:
            AttributesAdaptor(ISAXAttributes __RPC_FAR *pAttributes) : attributes_(pAttributes) { }
            ~AttributesAdaptor() { }

            /////////////////////////
			// indexed access
            virtual int getLength() const
            {
              int length;
              attributes_->getLength(&length);
              return length;
            } // getLength

            virtual string_type getURI(unsigned int index) const
            {
              const wchar_t* pwchUri;
              int cchUri;
              HRESULT hr = attributes_->getURI(index, &pwchUri, &cchUri);
              if (FAILED(hr))
                return string_type();
              string_type uri(string_adaptor::construct_from_utf16(pwchUri, cchUri));
              return uri;
            } // getURI

            virtual string_type getLocalName(unsigned int index) const
            {
              const wchar_t* pwchLocalName;
              int cchLocalName;
              HRESULT hr = attributes_->getLocalName(index, &pwchLocalName, &cchLocalName);
              if (FAILED(hr))
                return string_type();
              string_type localName(string_adaptor::construct_from_utf16(pwchLocalName, cchLocalName));
			  return localName;
            } // getLocalName

            virtual string_type getQName(unsigned int index) const
            {
              const wchar_t* pwchQName;
              int cchQName;
              HRESULT hr = attributes_->getQName(index, &pwchQName, &cchQName);
              if (FAILED(hr))
                return string_type();
              string_type qName(string_adaptor::construct_from_utf16(pwchQName, cchQName));
              return qName;
            } // getQName

            virtual string_type getType(unsigned int index) const
            {
              const wchar_t* pwchType;
              int cchType;
              HRESULT hr = attributes_->getType(index, &pwchType, &cchType);
              if (FAILED(hr))
                return string_type();
              string_type type(string_adaptor::construct_from_utf16(pwchType, cchType));
              return type;
            } // getType

            virtual string_type getValue(unsigned int index) const
            {
			  const wchar_t* pwchValue;
              int cchValue;
              HRESULT hr = attributes_->getValue(index, &pwchValue, &cchValue);
              if (FAILED(hr))
                return string_type();
              string_type value(string_adaptor::construct_from_utf16(pwchValue, cchValue));
              return value;
            } // getValue

            /////////////////////////
            // name based query
            virtual int getIndex(const string_type& uri, const string_type& localName) const
            {
              int index = -1;
              std::wstring wUri(string_adaptor::asStdWString(uri));
              std::wstring wLocalName(string_adaptor::asStdWString(localName));
              HRESULT hr = attributes_->getIndexFromName(wUri.data(), static_cast<int>(wUri.length()),
                                                         wLocalName.data(), static_cast<int>(wLocalName.length()),
                                                         &index);
              return index;
            } // getIndex

            virtual int getIndex(const string_type& qName) const
            {
              int index = -1;
              std::wstring wQName(string_adaptor::asStdWString(qName));
              attributes_->getIndexFromQName(wQName.data(), static_cast<int>(wQName.length()), &index);
			  return index;
            } // getIndex

            virtual string_type getType(const string_type& uri, const string_type& localName) const
            {
              const wchar_t* pwchType;
              int cchType;
              std::wstring wUri(string_adaptor::asStdWString(uri));
              std::wstring wLocalName(string_adaptor::asStdWString(localName));
              HRESULT hr = attributes_->getTypeFromName(wUri.data(), static_cast<int>(wUri.length()),
                                                        wLocalName.data(), static_cast<int>(wLocalName.length()),
                                                        &pwchType, &cchType);
              if (FAILED(hr))
                return string_type();
              string_type type(string_adaptor::construct_from_utf16(pwchType, cchType));
              return type;
            } // getType

            virtual string_type getType(const string_type& qName) const
            {
              const wchar_t* pwchType;
              int cchType;
              std::wstring wQName(string_adaptor::asStdWString(qName));
              HRESULT hr = attributes_->getTypeFromQName(wQName.data(), static_cast<int>(wQName.length()),
                                                         &pwchType, &cchType);
              if (FAILED(hr))
                return string_type();
			  string_type type(string_adaptor::construct_from_utf16(pwchType, cchType));
              return type;
            } // getType

            virtual string_type getValue(const string_type& uri, const string_type& localName) const
            {
              const wchar_t* pwchValue;
              int cchValue;
              std::wstring wUri(string_adaptor::asStdWString(uri));
              std::wstring wLocalName(string_adaptor::asStdWString(localName));
              HRESULT hr = attributes_->getValueFromName(wUri.data(), static_cast<int>(wUri.length()),
                                                         wLocalName.data(), static_cast<int>(wLocalName.length()),
                                                         &pwchValue, &cchValue);
              if (FAILED(hr))
                return string_type();
              string_type value(string_adaptor::construct_from_utf16(pwchValue, cchValue));
              return value;
            } // getValue

            virtual string_type getValue(const string_type& qname) const
            {
              const wchar_t* pwchValue;
              int cchValue;
              std::wstring wQName(string_adaptor::asStdWString(qname));
              HRESULT hr = attributes_->getValueFromQName(wQName.data(), static_cast<int>(wQName.length()),
                                                          &pwchValue, &cchValue);
              if (FAILED(hr))
				return string_type();
              string_type value(string_adaptor::construct_from_utf16(pwchValue, cchValue));
              return value;
            } // getValue

          private:
            ISAXAttributes __RPC_FAR *attributes_;

            AttributesAdaptor();
        }; // class AttributesAdaptor
    }; // class ContentHandlerAdaptor

    class LexicalHandlerAdaptor : public ISAXLexicalHandler 
    {
      public:
        LexicalHandlerAdaptor() : lexicalHandler_(0) { }
        virtual ~LexicalHandlerAdaptor() { }

        void setLexicalHandler(lexicalHandlerT& handler) { lexicalHandler_ = &handler; }
        lexicalHandlerT* getLexicalHandler() const { return lexicalHandler_; }

        virtual HRESULT STDMETHODCALLTYPE startDTD( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t *pwchSystemId,
			/* [in] */ int cchSystemId)
        {
          if(lexicalHandler_)
            lexicalHandler_->startDTD(string_adaptor::construct_from_utf16(pwchName, cchName),
                                      string_adaptor::construct_from_utf16(pwchPublicId, cchPublicId),
                                      string_adaptor::construct_from_utf16(pwchSystemId, cchSystemId));
          return S_OK;
        } // startDTD

        virtual HRESULT STDMETHODCALLTYPE endDTD( void)
        {
          if(lexicalHandler_)
            lexicalHandler_->endDTD();
          return S_OK;
        } // endDTD

        virtual HRESULT STDMETHODCALLTYPE startEntity( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName)
        {
          if(lexicalHandler_)
            lexicalHandler_->startEntity(string_adaptor::construct_from_utf16(pwchName, cchName));
          return S_OK;
        } // startEntity

        virtual HRESULT STDMETHODCALLTYPE endEntity( 
            /* [in] */ const wchar_t *pwchName,
			/* [in] */ int cchName)
        {
          if(lexicalHandler_)
            lexicalHandler_->endEntity(string_adaptor::construct_from_utf16(pwchName, cchName));
          return S_OK;
        } // endEntity

        virtual HRESULT __stdcall startCDATA()
        {
          if(lexicalHandler_)
            lexicalHandler_->startCDATA();
          return S_OK;
        } // startCDATA

        virtual HRESULT __stdcall endCDATA()
        {
          if(lexicalHandler_)
            lexicalHandler_->endCDATA();
          return S_OK;
        } // endCDATA

        virtual HRESULT STDMETHODCALLTYPE comment( 
            /* [in] */ const wchar_t *pwchChars,
            /* [in] */ int cchChars)
        {
          if(lexicalHandler_)
            lexicalHandler_->comment(string_adaptor::construct_from_utf16(pwchChars, cchChars));
		  return S_OK;
        } // comment

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject)
        {
          // we have to implement this, because we pass this as an IUnknown but it needs an
          // ISAXLexicalHandler interface
          if(riid == __uuidof(ISAXLexicalHandler))
            *ppvObject = this;
          return 0;
        } // QueryInterface
        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        lexicalHandlerT* lexicalHandler_;
    }; // class LexicalHandlerAdaptor

    class DeclHandlerAdaptor : public ISAXDeclHandler 
    {
      public:
        DeclHandlerAdaptor() : declHandler_(0) { }
        virtual ~DeclHandlerAdaptor() { }

        void setDeclHandler(declHandlerT& handler) { declHandler_ = &handler; }
        declHandlerT* getDeclHandler() const { return declHandler_; }

        virtual HRESULT STDMETHODCALLTYPE elementDecl( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchModel,
            /* [in] */ int cchModel)
        {
          if(declHandler_)
            declHandler_->elementDecl(string_adaptor::construct_from_utf16(pwchName, cchName),
                                      string_adaptor::construct_from_utf16(pwchModel, cchModel));
          return S_OK;
        } // elementDecl

        virtual HRESULT STDMETHODCALLTYPE attributeDecl( 
            /* [in] */ const wchar_t *pwchElementName,
            /* [in] */ int cchElementName,
            /* [in] */ const wchar_t *pwchAttributeName,
            /* [in] */ int cchAttributeName,
            /* [in] */ const wchar_t *pwchType,
            /* [in] */ int cchType,
            /* [in] */ const wchar_t *pwchValueDefault,
            /* [in] */ int cchValueDefault,
            /* [in] */ const wchar_t *pwchValue,
            /* [in] */ int cchValue)
        {
          if(declHandler_)
            declHandler_->attributeDecl(string_adaptor::construct_from_utf16(pwchElementName, cchElementName),
										string_adaptor::construct_from_utf16(pwchAttributeName, cchAttributeName),
                                        string_adaptor::construct_from_utf16(pwchType, cchType),
                                        string_adaptor::construct_from_utf16(pwchValueDefault, cchValueDefault),
                                        string_adaptor::construct_from_utf16(pwchValue, cchValue));
          return S_OK;
        } // attributeDecl

        virtual HRESULT STDMETHODCALLTYPE internalEntityDecl( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchValue,
            /* [in] */ int cchValue)
        {
          if(declHandler_)
            declHandler_->internalEntityDecl(string_adaptor::construct_from_utf16(pwchName, cchName),
                                             string_adaptor::construct_from_utf16(pwchValue, cchValue));
          return S_OK;
        } // internalEntityDecl

        virtual HRESULT STDMETHODCALLTYPE externalEntityDecl( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t *pwchSystemId,
            /* [in] */ int cchSystemId)
        {
		  if(declHandler_)
            declHandler_->externalEntityDecl(string_adaptor::construct_from_utf16(pwchName, cchName),
                                             string_adaptor::construct_from_utf16(pwchPublicId, cchPublicId),
                                             string_adaptor::construct_from_utf16(pwchSystemId, cchSystemId));
          return S_OK;
        } // externalEntityDecl

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject)
        {
          // we have to implement this, because we pass this as an IUnknown but it needs an
          // ISAXDeclHandler interface
          if(riid == __uuidof(ISAXDeclHandler))
            *ppvObject = reinterpret_cast<void*>(this);
          return 0;
        } // QueryInterface

        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        declHandlerT* declHandler_;
    }; // class DeclHandlerAdaptor

    class StreamAdaptor : public ISequentialStream
    {
      public:
		StreamAdaptor(inputSourceT& source) :
          source_(source)
        {
        } // StreamAdaptor

        virtual HRESULT __stdcall Read(void* pv, ULONG cb, ULONG* pcbRead)
        {
          source_.getByteStream()->read(reinterpret_cast<char*>(pv), cb);
          *pcbRead = static_cast<ULONG>(source_.getByteStream()->gcount());
          return S_OK;
        } // Read

        virtual HRESULT __stdcall Write(const void __RPC_FAR *pv, ULONG cb, ULONG __RPC_FAR *pcbWritten)
        {
          return S_FALSE;
        } // Write

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject)
        {
          // we have to implement this, because we pass this as an IUnknown but it needs an
          // IStream interface
          if(riid == __uuidof(ISequentialStream))
          {
            *ppvObject = reinterpret_cast<void*>(this);
            return S_OK;
          } // if ...
		  return E_NOINTERFACE;
        } // QueryInterface

        unsigned long __stdcall AddRef() { return 1; }
        unsigned long __stdcall Release() { return 1; }

      private:
        inputSourceT& source_;
    }; // StreamAdaptor


    //////////////////////////////////////////////////////
    // member variables
    COMInitializer_type init;
    DTDHandlerAdaptor dtdHandler_;
    ErrorHandlerAdaptor errorHandler_;
    ContentHandlerAdaptor contentHandler_;
    LexicalHandlerAdaptor lexicalHandler_;
    DeclHandlerAdaptor declHandler_;

    ISAXXMLReaderPtr reader_;
    SAX::PropertyNames<string_type, string_adaptor> properties_;
}; // class msxml

template<class string_type, class T0, class T1>
msxml2_wrapper<string_type, T0, T1>::msxml2_wrapper() :
    init(),
    dtdHandler_(),
    errorHandler_(),
    contentHandler_(errorHandler_),
    lexicalHandler_(),
    declHandler_(),
    reader_(),
    properties_()
{
  reader_.CreateInstance("Msxml2.SAXXMLReader.6.0");
  if(reader_.GetInterfacePtr() == 0)
    reader_.CreateInstance("Msxml2.SAXXMLReader.5.0");
  if(reader_.GetInterfacePtr() == 0)
    reader_.CreateInstance("Msxml2.SAXXMLReader.4.0");
  if(reader_.GetInterfacePtr() == 0)
    reader_.CreateInstance("Msxml2.SAXXMLReader.3.0");
  if(reader_.GetInterfacePtr() == 0)
    reader_.CreateInstance(__uuidof(ISAXXMLReader));

  if(reader_.GetInterfacePtr() == 0)
    throw SAXException("MSXML SAX Reader (pre-4.0) could not be instantiated");

  reader_->putContentHandler(&contentHandler_);
  reader_->putErrorHandler(&errorHandler_);
  reader_->putDTDHandler(&dtdHandler_);

  VARIANT wrapper;
  wrapper.vt = VT_UNKNOWN;
  wrapper.punkVal = static_cast<ISAXLexicalHandler*>(&lexicalHandler_);
  reader_->putProperty(L"http://xml.org/sax/properties/lexical-handler", wrapper);
  wrapper.punkVal = static_cast<ISAXDeclHandler*>(&declHandler_);
  reader_->putProperty(L"http://xml.org/sax/properties/declaration-handler", wrapper);
} // msxml2_wrapper

template<class string_type, class T0, class T1>
msxml2_wrapper<string_type, T0, T1>::~msxml2_wrapper()
{
  if(reader_.GetInterfacePtr())
    reader_.Release();
} // ~msxml2_wrapper

template<class string_type, class T0, class T1>
bool msxml2_wrapper<string_type, T0, T1>::getFeature(const string_type& name) const
{
  VARIANT_BOOL feature;
  std::wstring wName(string_adaptor::asStdWString(name));
  reader_->getFeature(wName.c_str(), &feature);
  return (feature == VARIANT_TRUE) ? true : false;
} // msxml2_wrapper::getFeature

template<class string_type, class T0, class T1>
void msxml2_wrapper<string_type, T0, T1>::setFeature(const string_type& name, bool value)
{
  std::wstring wName(string_adaptor::asStdWString(name));
  reader_->putFeature(wName.c_str(), value);
} // setFeature

template<class string_type, class T0, class T1>
void msxml2_wrapper<string_type, T0, T1>::setErrorHandler(errorHandlerT& handler)
{
	errorHandler_.setErrorHandler(handler);
} // setErrorHandler

template<class string_type, class T0, class T1>
void msxml2_wrapper<string_type, T0, T1>::parse(inputSourceT& source)
{
  if(source.getByteStream() == 0)
  {
    std::wstring wSysId(string_adaptor::asStdWString(source.getSystemId()));
    reader_->parseURL(wSysId.c_str());
  }
  else
  {
    StreamAdaptor sa(source);
    VARIANT wrapper;
    wrapper.vt = VT_UNKNOWN;
    wrapper.punkVal = static_cast<ISequentialStream*>(&sa);
    reader_->parse(wrapper);
  } // if ...
  errorHandler_.report();
} // parse

} // namespace SAX
} // namespace Arabica

#endif
// end of file

