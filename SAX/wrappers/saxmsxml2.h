#ifndef saxmsxml2H
#define saxmsxml2H
//---------------------------------------------------------------------------
// A SAX2 wrapper class for MSXML component.
//
// $Id$
//---------------------------------------------------------------------------

#include <SAX/XMLReader.h>
#include <SAX/InputSource.h>
#include <SAX/SAXParseException.h>
#include <SAX/SAXNotRecognizedException.h>
#include <SAX/SAXNotSupportedException.h>
#include <SAX/ext/LexicalHandler.h>
#include <SAX/ext/DeclHandler.h>
#include <SAX/helpers/PropertyNames.h>
#include <SAX/helpers/StringAdaptor.h>

#import <msxml3.dll>

namespace SAX
{

/**
 * use this as COMInitializer_type if you call 
 * CoInitialize/CoInitializeEx in your own code
 */
class COMExternalInitializer 
{
  public:
    COMExternalInitializer() { }
    ~COMExternalInitializer() { }
}; // COMExternalInitializer

class COMSingleThreadInitializer 
{
  public:
    COMSingleThreadInitializer() { ::CoInitialize(NULL); }
    ~COMSingleThreadInitializer() { ::CoUninitialize(); }
}; // COMSingleThreadInitializer

#if(_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)
class COMMultiThreadInitializer 
{
  public:
    COMMultiThreadInitializer() { ::CoInitializeEx(NULL, COINIT_MULTITHREADED); } 
    ~COMMultiThreadInitializer() { ::CoUninitialize(); }
};
#endif

template<class string_type, 
         class COMInitializer_type = COMSingleThreadInitializer,
         class string_adaptor_type = SAX::default_string_adaptor<string_type> >
class msxml2_wrapper : public SAX::basic_XMLReader<string_type>
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
    typedef COMInitializer_type COMInitializerT;

    msxml2_wrapper();
		virtual ~msxml2_wrapper();

    /////////////////////////////////////////////////
    // Configuration
    virtual bool getFeature(const stringT& name) const;
    virtual void setFeature(const stringT& name, bool value);
  
    /////////////////////////////////////////////////
    // Event Handlers
    /* MSXML does not use EntityResolver currently */
    virtual void setEntityResolver(SAX::basic_EntityResolver<stringT>& resolver) { } 
    virtual SAX::basic_EntityResolver<stringT>* getEntityResolver() const { return 0; }
    virtual void setDTDHandler(SAX::basic_DTDHandler<stringT>& handler) { dtdHandler_.setDTDHandler(handler); } 
    virtual SAX::basic_DTDHandler<stringT>* getDTDHandler() const { return dtdHandler_.getDTDHandler(); }
    virtual void setContentHandler(SAX::basic_ContentHandler<stringT>& handler) {	contentHandler_.setContentHandler(handler); }
    virtual SAX::basic_ContentHandler<stringT>* getContentHandler() const { return contentHandler_.getContentHandler(); }
    virtual void setErrorHandler(SAX::ErrorHandler& handler);
    virtual SAX::ErrorHandler* getErrorHandler() const;

    //////////////////////////////////////////////////
    // Parsing
    virtual void parse(SAX::basic_InputSource<stringT>& input);

  protected:
    virtual std::auto_ptr<SAX::basic_XMLReader<stringT>::PropertyBase> doGetProperty(const stringT& name);
    virtual void doSetProperty(const stringT& name, std::auto_ptr<SAX::basic_XMLReader<stringT>::PropertyBase> value);

	private:
    //////////////////////////////////////////////////////
    // COM interface -> C++ interface adaptors
    class LocatorAdaptor : public SAX::basic_Locator<stringT>
    {
      public:
        LocatorAdaptor() : locator_(0) { }
        LocatorAdaptor(MSXML2::ISAXLocator __RPC_FAR* locator) : locator_(0) { setLocator(locator); } 
        ~LocatorAdaptor() { setLocator(0); }

        stringT getPublicId() const
        {
          if(!locator_) 
            return stringT();

          unsigned short* pwchPublicId;
          locator_->raw_getPublicId(&pwchPublicId);
          stringT publicId(SA_.makeStringT(pwchPublicId));
          return publicId;
        } // getPublicId
    
        stringT getSystemId() const
        {
          if(!locator_)
            return stringT();

          unsigned short* pwchSystemId;
          locator_->raw_getSystemId(&pwchSystemId);
          stringT systemId(SA_.makeStringT(pwchSystemId));
          return systemId;
        } // getSystemId
    
        int getLineNumber() const
        {
          if(!locator_)
            return -1;

          int lineNumber;
          locator_->raw_getLineNumber(&lineNumber);
          return lineNumber;
        } // getLineNumber
    
        int getColumnNumber() const
        {
          if(!locator_)
            return -1;

          int columnNumber;
          locator_->raw_getColumnNumber(&columnNumber);
          return columnNumber;
        } // getColumnNumber
    
        void setLocator(MSXML2::ISAXLocator __RPC_FAR* locator)
        {
          if(locator_)
          {
            locator_->Release();
            locator_ = 0;
          } // if ...

          if(locator)
          {
            locator_ = locator;
            locator_->AddRef();
          } // if ...
        } // setLocator

      private:
        MSXML2::ISAXLocator __RPC_FAR *locator_;
        string_adaptorT SA_;
    }; // class LocatorAdaptor

    class DTDHandlerAdaptor : public MSXML2::ISAXDTDHandler 
    {
      public:
        DTDHandlerAdaptor() : dtdHandler_(0) { }
        ~DTDHandlerAdaptor() { }

        void setDTDHandler(SAX::basic_DTDHandler<stringT>& handler) { dtdHandler_ = &handler; }
        SAX::basic_DTDHandler<stringT>* getDTDHandler() const { return dtdHandler_; }

        virtual HRESULT __stdcall raw_notationDecl(unsigned short* pwchName, int cchName,
                                               unsigned short* pwchPublicId, int cchPublicId,
                                               unsigned short* pwchSystemId, int cchSystemId)
        {
          if(dtdHandler_)
            dtdHandler_->notationDecl(SA_.makeStringT(pwchName, cchName),
                                      SA_.makeStringT(pwchPublicId, cchPublicId),
                                      SA_.makeStringT(pwchSystemId, cchSystemId));
          return S_OK;
        } // notationDecl
        virtual HRESULT __stdcall raw_unparsedEntityDecl(unsigned short* pwchName, int cchName,
                                                     unsigned short* pwchPublicId, int cchPublicId,
                                                     unsigned short* pwchSystemId, int cchSystemId,
                                                     unsigned short* pwchNotationName, int cchNotationName)
        {
          if(dtdHandler_)
            dtdHandler_->unparsedEntityDecl(SA_.makeStringT(pwchName, cchName),
                                            SA_.makeStringT(pwchPublicId, cchPublicId),
                                            SA_.makeStringT(pwchSystemId, cchSystemId),
                                            SA_.makeStringT(pwchNotationName, cchNotationName));
          return S_OK;
        } // unparsedEntityDecl

        // satify COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject) { return 0; }
        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        SAX::basic_DTDHandler<stringT>* dtdHandler_;
        string_adaptorT SA_;
    }; // class DTDHandlerAdaptor

    class ContentHandlerAdaptor : public MSXML2::ISAXContentHandler 
    {
      public:
        ContentHandlerAdaptor() : contentHandler_(0) { } 
        ~ContentHandlerAdaptor() { }

        void setContentHandler(SAX::basic_ContentHandler<stringT>& handler) { contentHandler_ = &handler; }
        SAX::basic_ContentHandler<stringT>* getContentHandler() const { return contentHandler_; }

        virtual HRESULT __stdcall raw_putDocumentLocator(MSXML2::ISAXLocator __RPC_FAR *pLocator)
        {
          locator_.setLocator(pLocator);
          if(contentHandler_) contentHandler_->setDocumentLocator(locator_);
          return S_OK;
        } // putDocumentLocation
        
        virtual HRESULT __stdcall raw_startDocument(void)
        {
          if(contentHandler_) contentHandler_->startDocument();
          return S_OK;
        } // startDocument
        
        virtual HRESULT __stdcall raw_endDocument(void)
        {
          if(contentHandler_) contentHandler_->endDocument();
          return S_OK;
        } // endDocument
        
        virtual HRESULT __stdcall raw_startPrefixMapping(wchar_t __RPC_FAR *pwchPrefix, int cchPrefix,
                                                     wchar_t __RPC_FAR *pwchUri, int cchUri)

        {
          if(contentHandler_)
            contentHandler_->startPrefixMapping(SA_.makeStringT(pwchPrefix, cchPrefix),
                                                SA_.makeStringT(pwchUri, cchUri));
          return S_OK;
        } // startPrefixMapping
       
        virtual HRESULT __stdcall raw_endPrefixMapping(wchar_t __RPC_FAR *pwchPrefix, int cchPrefix)
        {
          if(contentHandler_) contentHandler_->endPrefixMapping(SA_.makeStringT(pwchPrefix, cchPrefix));
          return S_OK;
        } // endPrefixMapping
        
        virtual HRESULT __stdcall raw_startElement(wchar_t __RPC_FAR *pwchNamespaceUri, int cchNamespaceUri,
                                               wchar_t __RPC_FAR *pwchLocalName, int cchLocalName,
                                               wchar_t __RPC_FAR *pwchRawName, int cchRawName,
                                               MSXML2::ISAXAttributes __RPC_FAR *pAttributes)
        {
          if(contentHandler_)
          {
            AttributesAdaptor attrs(pAttributes);
            contentHandler_->startElement(SA_.makeStringT(pwchNamespaceUri, cchNamespaceUri),
                                          SA_.makeStringT(pwchLocalName, cchLocalName),
                                          SA_.makeStringT(pwchRawName, cchRawName),
                                          attrs);
          } // if ...
          return S_OK;
        } // startElement
        
        virtual HRESULT __stdcall raw_endElement(wchar_t __RPC_FAR *pwchNamespaceUri, int cchNamespaceUri,
                                             wchar_t __RPC_FAR *pwchLocalName, int cchLocalName,
                                             wchar_t __RPC_FAR *pwchRawName, int cchRawName)
        {
          if(contentHandler_)
            contentHandler_->endElement(SA_.makeStringT(pwchNamespaceUri, cchNamespaceUri),
                                        SA_.makeStringT(pwchLocalName, cchLocalName),
                                        SA_.makeStringT(pwchRawName, cchRawName));
          return S_OK;
        } // endElement
        
        virtual HRESULT __stdcall raw_characters(wchar_t __RPC_FAR *pwchChars, int cchChars)
        {
          if(contentHandler_) contentHandler_->characters(SA_.makeStringT(pwchChars, cchChars));
          return S_OK;
        } // characters
        
        virtual HRESULT __stdcall raw_ignorableWhitespace(wchar_t __RPC_FAR *pwchChars, int cchChars)
        {
          if(contentHandler_)
            contentHandler_->ignorableWhitespace(SA_.makeStringT(pwchChars, cchChars));
          return S_OK;
        } // ignorableWhitespace
        
        virtual HRESULT __stdcall raw_processingInstruction(wchar_t __RPC_FAR *pwchTarget, int cchTarget,
                                                        wchar_t __RPC_FAR *pwchData, int cchData)
        {
          if(contentHandler_)
            contentHandler_->processingInstruction(SA_.makeStringT(pwchTarget, cchTarget),
                                                   SA_.makeStringT(pwchData, cchData));
          return S_OK;
        } // processingInstruction
        
        virtual HRESULT __stdcall raw_skippedEntity(wchar_t __RPC_FAR *pwchName, int cchName)
        {
          if(contentHandler_)
            contentHandler_->skippedEntity(SA_.makeStringT(pwchName, cchName));
          return S_OK;
        } // skippedEntity

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject) { return 0; }
        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        ////////////////////////////////////////////////
        // member varaibles
        SAX::basic_ContentHandler<stringT>* contentHandler_;
        LocatorAdaptor locator_;
        string_adaptorT SA_;

        //////////////////////////////////////////////////////
        // COM interface -> C++ interface adaptors
        class AttributesAdaptor : public SAX::basic_Attributes<stringT>
        {
          public:
            AttributesAdaptor(MSXML2::ISAXAttributes __RPC_FAR *pAttributes) : attributes_(pAttributes) { }
            ~AttributesAdaptor() { }

            /////////////////////////
            // indexed access
            virtual int getLength() const
            {
              int length;
              attributes_->raw_getLength(&length);
              return length;
            } // getLength
            virtual stringT getURI(unsigned int index) const
            {
              unsigned short* pwchUri;
              int cchUri;
              HRESULT hr = attributes_->raw_getURI(index, &pwchUri, &cchUri);
              if (FAILED(hr))
                return stringT();
              stringT uri(SA_.makeStringT(pwchUri, cchUri));
              return uri;
            } // getURI
            virtual stringT getLocalName(unsigned int index) const
            {
              unsigned short* pwchLocalName;
              int cchLocalName;
              HRESULT hr = attributes_->raw_getLocalName(index, &pwchLocalName, &cchLocalName);
              if (FAILED(hr))
                return stringT();
              stringT localName(SA_.makeStringT(pwchLocalName, cchLocalName));
              return localName;
            } // getLocalName
            virtual stringT getQName(unsigned int index) const
            {
              unsigned short* pwchQName;
              int cchQName;
              HRESULT hr = attributes_->raw_getQName(index, &pwchQName, &cchQName);
              if (FAILED(hr))
                return stringT();
              stringT qName(SA_.makeStringT(pwchQName, cchQName));
              return qName;
            } // getQName
            virtual stringT getType(unsigned int index) const
            {
              unsigned short* pwchType;
              int cchType;
              HRESULT hr = attributes_->raw_getType(index, &pwchType, &cchType);
              if (FAILED(hr))
                return stringT();
              stringT type(SA_.makeStringT(pwchType, cchType));
              return type;
            } // getType
            virtual stringT getValue(unsigned int index) const
            {
              unsigned short* pwchValue;
              int cchValue;
              HRESULT hr = attributes_->raw_getValue(index, &pwchValue, &cchValue);
              if (FAILED(hr))
                return stringT();
              stringT value(SA_.makeStringT(pwchValue, cchValue));
              return value;
            } // getValue

            /////////////////////////
            // name based query
            virtual int getIndex(const stringT& uri, const stringT& localName) const
            {
              int index = -1;
              std::wstring wUri(SA_.asStdWString(uri));
              std::wstring wLocalName(SA_.asStdWString(localName));
              HRESULT hr = attributes_->raw_getIndexFromName(const_cast<unsigned short*>(wUri.data()), wUri.length(),
                                                         const_cast<unsigned short*>(wLocalName.data()), wLocalName.length(),
                                                         &index);
              return index;
            } // getIndex
            virtual int getIndex(const stringT& qName) const
            {
              int index = -1;
              std::wstring wQName(SA_.asStdWString(qName));
              attributes_->raw_getIndexFromQName(const_cast<unsigned short*>(wQName.data()), wQName.length(), &index);
              return index;
            } // getIndex
            virtual stringT getType(const stringT& uri, const stringT& localName) const
            {
              unsigned short* pwchType;
              int cchType;
              std::wstring wUri(SA_.asStdWString(uri));
              std::wstring wLocalName(SA_.asStdWString(localName));
              HRESULT hr = attributes_->raw_getTypeFromName(const_cast<unsigned short*>(wUri.data()), wUri.length(),
                                                        const_cast<unsigned short*>(wLocalName.data()), wLocalName.length(),
                                                        &pwchType, &cchType);
              if (FAILED(hr))
                return stringT();
              stringT type(SA_.makeStringT(pwchType, cchType));
              return type;
            } // getType
            virtual stringT getType(const stringT& qName) const
            {
              unsigned short* pwchType;
              int cchType;
              std::wstring wQName(SA_.asStdWString(qName));
              HRESULT hr = attributes_->raw_getTypeFromQName(const_cast<unsigned short*>(wQName.data()), wQName.length(),
                                                         &pwchType, &cchType);
              if (FAILED(hr))
                return stringT();
              stringT type(SA_.makeStringT(pwchType, cchType));
              return type;
            } // getType
            virtual stringT getValue(const stringT& uri, const stringT& localName) const
            {
              unsigned short* pwchValue;
              int cchValue;
              std::wstring wUri(SA_.asStdWString(uri));
              std::wstring wLocalName(SA_.asStdWString(localName));
              HRESULT hr = attributes_->raw_getValueFromName(const_cast<unsigned short*>(wUri.data()), wUri.length(),
                                                         const_cast<unsigned short*>(wLocalName.data()), wLocalName.length(),
                                                         &pwchValue, &cchValue);
              if (FAILED(hr))
                return stringT();
              stringT value(SA_.makeStringT(pwchValue, cchValue));
              return value;
            } // getValue
            virtual stringT getValue(const stringT& qname) const
            {
              unsigned short* pwchValue;
              int cchValue;
              std::wstring wQName(SA_.asStdWString(qname));
              HRESULT hr = attributes_->raw_getValueFromQName(const_cast<unsigned short*>(wQName.data()), wQName.length(),
                                                          &pwchValue, &cchValue);
              if (FAILED(hr))
                return stringT();
              stringT value(SA_.makeStringT(pwchValue, cchValue));
              return value;
            } // getValue

          private:
            MSXML2::ISAXAttributes __RPC_FAR *attributes_;
            string_adaptorT SA_;

            AttributesAdaptor();
        }; // class AttributesAdaptor
    }; // class ContentHandlerAdaptor

    class ErrorHandlerAdaptor : public MSXML2::ISAXErrorHandler 
    {
      public:
        ErrorHandlerAdaptor() :   errorHandler_(0) { }
        virtual ~ErrorHandlerAdaptor() { }

        void setErrorHandler(SAX::ErrorHandler& handler) { errorHandler_ = &handler; }
        SAX::ErrorHandler* getErrorHandler() const { return errorHandler_; }

        virtual HRESULT __stdcall raw_error(struct MSXML2::ISAXLocator* pLocator,
                                        unsigned short * pwchErrorMessage, HRESULT hrErrorCode)
        {
          stringT errorMsg(SA_.makeStringT(pwchErrorMessage));
          if(errorHandler_)
            errorHandler_->error(SAX::basic_SAXParseException<stringT>(SA_.asStdString(errorMsg), LocatorAdaptor(pLocator)));
          return S_OK;
        } // error
        virtual HRESULT __stdcall raw_fatalError(struct MSXML2::ISAXLocator* pLocator,
                                             unsigned short * pwchErrorMessage, HRESULT hrErrorCode)
        {
          stringT errorMsg(SA_.makeStringT(pwchErrorMessage));
          if(errorHandler_)
            errorHandler_->fatalError(SAX::basic_SAXParseException<stringT>(SA_.asStdString(errorMsg), LocatorAdaptor(pLocator)));
          return S_OK;
        } // fatalError
        virtual HRESULT __stdcall raw_ignorableWarning(struct MSXML2::ISAXLocator* pLocator,
                                                   unsigned short * pwchErrorMessage, HRESULT hrErrorCode)
        {
          stringT errorMsg(SA_.makeStringT(pwchErrorMessage));
          if(errorHandler_)
            errorHandler_->warning(SAX::basic_SAXParseException<stringT>(SA_.asStdString(errorMsg), LocatorAdaptor(pLocator)));
          return S_OK;
        } // ignorableWarning

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject) { return 0; }
        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        SAX::ErrorHandler* errorHandler_;
        string_adaptorT SA_;
    }; // class ErrorHandlerAdaptor

    class LexicalHandlerAdaptor : public MSXML2::ISAXLexicalHandler 
    {
      public:
        LexicalHandlerAdaptor() : lexicalHandler_(0) { }
        virtual ~LexicalHandlerAdaptor() { }

        void setLexicalHandler(SAX::basic_LexicalHandler<stringT>& handler) { lexicalHandler_ = &handler; }
        SAX::basic_LexicalHandler<stringT>* getLexicalHandler() const { return lexicalHandler_; }

        virtual HRESULT __stdcall raw_startDTD(unsigned short* pwchName, int cchName,
                                           unsigned short* pwchPublicId, int cchPublicId,
                                           unsigned short* pwchSystemId, int cchSystemId)
        {
          if(lexicalHandler_)
            lexicalHandler_->startDTD(SA_.makeStringT(pwchName, cchName),
                                      SA_.makeStringT(pwchPublicId, cchPublicId),
                                      SA_.makeStringT(pwchSystemId, cchSystemId));
          return S_OK;
        } // startDTD

        virtual HRESULT __stdcall raw_endDTD()
        {
          if(lexicalHandler_)
            lexicalHandler_->endDTD();
          return S_OK;
        } // endDTD

        virtual HRESULT __stdcall raw_startEntity(unsigned short* pwchName, int cchName)
        {
          if(lexicalHandler_)
            lexicalHandler_->startEntity(SA_.makeStringT(pwchName, cchName));
          return S_OK;
        } // startEntity

        virtual HRESULT __stdcall raw_endEntity(unsigned short* pwchName, int cchName)
        {
          if(lexicalHandler_)
            lexicalHandler_->endEntity(SA_.makeStringT(pwchName, cchName));
          return S_OK;
        } // endEntity

        virtual HRESULT __stdcall raw_startCDATA()
        {
          if(lexicalHandler_)
            lexicalHandler_->startCDATA();
          return S_OK;
        } // startCDATA

        virtual HRESULT __stdcall raw_endCDATA()
        {
          if(lexicalHandler_)
            lexicalHandler_->endCDATA();
          return S_OK;
        } // endCDATA

        virtual HRESULT __stdcall raw_comment(unsigned short* pwchChars, int cchChars)
        {
          if(lexicalHandler_)
            lexicalHandler_->comment(SA_.makeStringT(pwchChars, cchChars));
          return S_OK;
        } // comment

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject)
        {
          // we have to implement this, because we pass this as an IUnknown but it needs an
          // ISAXLexicalHandler interface
          if(riid == __uuidof(MSXML2::ISAXLexicalHandler))
            *ppvObject = this;
          return 0;
        } // QueryInterface
        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        SAX::basic_LexicalHandler<stringT>* lexicalHandler_;
        string_adaptorT SA_;
    }; // class LexicalHandlerAdaptor

    class DeclHandlerAdaptor : public MSXML2::ISAXDeclHandler 
    {
      public:
        DeclHandlerAdaptor() : declHandler_(0) { }
        virtual ~DeclHandlerAdaptor() { }

        void setDeclHandler(SAX::basic_DeclHandler<stringT>& handler) { declHandler_ = &handler; }
        SAX::basic_DeclHandler<stringT>* getDeclHandler() const { return declHandler_; }

        virtual HRESULT __stdcall raw_elementDecl(unsigned short* pwchName, int cchName,
                                              unsigned short* pwchModel, int cchModel)
        {
          if(declHandler_)
            declHandler_->elementDecl(SA_.makeStringT(pwchName, cchName),
                                      SA_.makeStringT(pwchModel, cchModel));
          return S_OK;
        } // elementDecl

        virtual HRESULT __stdcall raw_attributeDecl(unsigned short* pwchElementName, int cchElementName,
                                                unsigned short* pwchAttributeName, int cchAttributeName,
                                                unsigned short* pwchType, int cchType,
                                                unsigned short* pwchValueDefault, int cchValueDefault,
                                                unsigned short* pwchValue, int cchValue)
        {
          if(declHandler_)
            declHandler_->attributeDecl(SA_.makeStringT(pwchElementName, cchElementName),
                                        SA_.makeStringT(pwchAttributeName, cchAttributeName),
                                        SA_.makeStringT(pwchType, cchType),
                                        SA_.makeStringT(pwchValueDefault, cchValueDefault),
                                        SA_.makeStringT(pwchValue, cchValue));
          return S_OK;
        } // attributeDecl

        virtual HRESULT __stdcall raw_internalEntityDecl(unsigned short* pwchName, int cchName,
                                                     unsigned short* pwchValue, int cchValue)
        {
          if(declHandler_)
            declHandler_->internalEntityDecl(SA_.makeStringT(pwchName, cchName),
                                             SA_.makeStringT(pwchValue, cchValue));
          return S_OK;
        } // internalEntityDecl

        virtual HRESULT __stdcall raw_externalEntityDecl(unsigned short* pwchName, int cchName,
                                                     unsigned short* pwchPublicId, int cchPublicId,
                                                     unsigned short* pwchSystemId, int cchSystemId)
        {
          if(declHandler_)
            declHandler_->externalEntityDecl(SA_.makeStringT(pwchName, cchName),
                                             SA_.makeStringT(pwchPublicId, cchPublicId),
                                             SA_.makeStringT(pwchSystemId, cchSystemId));
          return S_OK;
        } // externalEntityDecl

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject)
        {
          // we have to implement this, because we pass this as an IUnknown but it needs an
          // ISAXDeclHandler interface
          if(riid == __uuidof(MSXML2::ISAXDeclHandler))
            *ppvObject = reinterpret_cast<void*>(this);
          return 0;
        } // QueryInterface

        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        SAX::basic_DeclHandler<stringT>* declHandler_;
        string_adaptorT SA_;
    }; // class DeclHandlerAdaptor

    class StreamAdaptor : public IStream
    {
      public:
        StreamAdaptor(SAX::basic_InputSource<stringT>& source) :
          source_(source)
        {
        } // StreamAdaptor

        virtual HRESULT __stdcall Read(void* pv, ULONG cb, ULONG* pcbRead)
        {
          source_.getByteStream()->read(reinterpret_cast<char*>(pv), cb);
          *pcbRead = source_.getByteStream()->gcount();
          return S_OK;
        } // Read

        // stub implementations of everything else
        virtual HRESULT __stdcall Write(const void* pv, ULONG cb, ULONG* pcbWritten)
        {
          return S_FALSE;
        } // Write

        virtual HRESULT __stdcall Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
        {
          return S_FALSE;
        } // Seek

        virtual HRESULT __stdcall SetSize(ULARGE_INTEGER libNewSize)
        {
          return S_FALSE;
        } // SetSize

        virtual HRESULT __stdcall CopyTo(IStream* pstm, ULARGE_INTEGER db, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten)
        {
          return S_FALSE;
        } // CopyTo

        virtual HRESULT __stdcall Commit(DWORD grfCommitFlags)
        {
          return S_FALSE;
        } // Commit

        virtual HRESULT __stdcall Revert()
        {
          return S_FALSE;
        } // Revert

        virtual HRESULT __stdcall LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
        {
          return S_FALSE;
        } // LockRegion

        virtual HRESULT __stdcall UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER db, DWORD dwLockType)
        {
          return S_FALSE;
        } // UnlockRegion

        virtual HRESULT __stdcall Stat(STATSTG* pstatstg, DWORD grfStatFlag)
        {
          return S_FALSE;
        } // Stat

        virtual HRESULT __stdcall Clone(IStream** ppstm)
        {
          return S_FALSE;
        } // Clone

        // satisfy COM interface even if we're not a COM object
        long __stdcall QueryInterface(const struct _GUID &riid,void **ppvObject)
        {
          // we have to implement this, because we pass this as an IUnknown but it needs an
          // IStream interface
          if(riid == __uuidof(IStream))
            *ppvObject = reinterpret_cast<void*>(this);
          return 0;
        } // QueryInterface

        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        SAX::basic_InputSource<stringT>& source_;
    }; // StreamAdaptor

    //////////////////////////////////////////////////////
    // member variables
    COMInitializer_type init;
    DTDHandlerAdaptor dtdHandler_;
    ContentHandlerAdaptor contentHandler_;
    ErrorHandlerAdaptor errorHandler_;
    LexicalHandlerAdaptor lexicalHandler_;
    DeclHandlerAdaptor declHandler_;
    MSXML2::ISAXXMLReaderPtr reader_;
    string_adaptorT SA_;
    SAX::PropertyNames<stringT, string_adaptorT> properties_;
}; // class msxml

template<class stringT, class COMInitializerT, class string_adaptorT>
msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::msxml2_wrapper()
{
  reader_.CreateInstance(__uuidof(MSXML2::SAXXMLReader));

  reader_->putContentHandler(&contentHandler_);
  reader_->putErrorHandler(&errorHandler_);
  reader_->putDTDHandler(&dtdHandler_);


  VARIANT wrapper;
  wrapper.vt = VT_UNKNOWN;
  wrapper.punkVal = static_cast<MSXML2::ISAXLexicalHandler*>(&lexicalHandler_);
  reader_->putProperty(L"http://xml.org/sax/properties/lexical-handler", wrapper);
  wrapper.punkVal = static_cast<MSXML2::ISAXDeclHandler*>(&declHandler_);
  reader_->putProperty(L"http://xml.org/sax/properties/declaration-handler", wrapper);
} // msxml2_wrapper

template<class stringT, class COMInitializerT, class string_adaptorT>
msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::~msxml2_wrapper()
{
} // ~msxml

template<class stringT, class COMInitializerT, class string_adaptorT>
bool msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::getFeature(const stringT& name) const
{
  VARIANT_BOOL feature;
  std::wstring wName(SA_.asStdWString(name));
  reader_->raw_getFeature(const_cast<unsigned short*>(wName.c_str()), &feature);
  return (feature == VARIANT_TRUE) ? true : false;
} // getFeature

template<class stringT, class COMInitializerT, class string_adaptorT>
void msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::setFeature(const stringT& name, bool value)
{
  std::wstring wName(SA_.asStdWString(name));
  reader_->raw_putFeature(const_cast<unsigned short*>(wName.c_str()), value);
} // setFeature

template<class stringT, class COMInitializerT, class string_adaptorT>
void msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::setErrorHandler(SAX::ErrorHandler& handler)
{
	errorHandler_.setErrorHandler(handler);
} // setErrorHandler

template<class stringT, class COMInitializerT, class string_adaptorT>
SAX::ErrorHandler* msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::getErrorHandler() const
{
  return errorHandler_.getErrorHandler();
} // getErrorHandler

template<class stringT, class COMInitializerT, class string_adaptorT>
std::auto_ptr<SAX::basic_XMLReader<stringT>::PropertyBase> msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::doGetProperty(const stringT& name)
{
  if(name == properties_.lexicalHandler)
  {
    Property<SAX::basic_LexicalHandler<stringT>*>* prop = new Property<SAX::basic_LexicalHandler<stringT>*>(lexicalHandler_.getLexicalHandler());
    return std::auto_ptr<SAX::basic_XMLReader<stringT>::PropertyBase>(prop);
  }
  if(name == properties_.declHandler)
  {
    Property<SAX::basic_DeclHandler<stringT>*>* prop = new Property<SAX::basic_DeclHandler<stringT>*>(declHandler_.getDeclHandler());
    return std::auto_ptr<SAX::basic_XMLReader<stringT>::PropertyBase>(prop);
  }
  throw SAX::SAXNotRecognizedException("Property not recognized ");    
} // doGetProperty

template<class stringT, class COMInitializerT, class string_adaptorT>
void msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::doSetProperty(const stringT& name, std::auto_ptr<SAX::basic_XMLReader<stringT>::PropertyBase> value)
{
  if(name == properties_.lexicalHandler)
  {
    Property<SAX::basic_LexicalHandler<stringT>&>* prop = dynamic_cast<Property<SAX::basic_LexicalHandler<stringT>&>*>(value.get());

    if(!prop)
      throw std::bad_cast("Property LexicalHandler is wrong type, should be SAX::LexicalHandler&");

    lexicalHandler_.setLexicalHandler(prop->get());
    return;
  } // if ...
  if(name == properties_.declHandler)
  {
    Property<SAX::basic_DeclHandler<stringT>&>* prop = dynamic_cast<Property<SAX::basic_DeclHandler<stringT>&>*>(value.get());

    if(!prop)
      throw std::bad_cast("Property DeclHandler is wrong type, should be SAX::DeclHandler&");

    declHandler_.setDeclHandler(prop->get());
    return;
  } // if ...
  throw SAX::SAXNotRecognizedException("Property not recognized ");    
} // doSetProperty

template<class stringT, class COMInitializerT, class string_adaptorT>
void msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::parse(SAX::basic_InputSource<stringT>& source)
{
  if(source.getByteStream() == 0)
  {
    std::wstring wSysId(SA_.asStdWString(source.getSystemId()));
    reader_->raw_parseURL(const_cast<unsigned short*>(wSysId.c_str()));
  }
  else
  {
    StreamAdaptor sa(source);
    VARIANT wrapper;
    wrapper.vt = VT_UNKNOWN;
    wrapper.punkVal = static_cast<IStream*>(&sa);
    reader_->raw_parse(wrapper);
  } // if ...
} // parse

} // namespace SAX

#endif
// end of file