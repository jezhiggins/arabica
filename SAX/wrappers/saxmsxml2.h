#ifndef ARABICA_SAX_MSXML2_H
#define ARABICA_SAX_MSXML2_H
//---------------------------------------------------------------------------
// A SAX2 wrapper class for MSXML component.
//
// $Id$
//
// Changes:
//   21-Jul-2002 Major tweaks to use #include <header> rather then
//               #import <type_library>.  The latter is sensitive to
//               the exact name/version of the library provided by
//               Microsoft and various options provided to the type
//               library reader.  (Found the issue when I attempted
//               to build with MSXML4 rather then MSXML3.)  [kas]
//
//   31-Jul-2002 Created the default PROGID define.  M$. in their
//               wisdom, removed the version independent IDs starting
//               in version 4.0 of the MSXML library.  Saves a lot of
//               'DLL hell' problems but creates others for maintainers.
//               The initialization code will now try the 4.0 ID and
//               then the older (version independant) name.   [kas]
//
//
// Known issues:
//      1. The destructor (~msxml2_wrapper) should release the COM
//         interfaces.  It doesn't because of problem 2.
//
//      2. The classes don't handle non-initialization well.  Failure
//         to get the COM interfaces during instance construction will
//         cause a crash at some later point.
//
//---------------------------------------------------------------------------

#include <SAX/ArabicaConfig.h>
#include <SAX/XMLReader.h>
#include <SAX/InputSource.h>
#include <SAX/SAXParseException.h>
#include <SAX/SAXNotRecognizedException.h>
#include <SAX/SAXNotSupportedException.h>
#include <SAX/ext/LexicalHandler.h>
#include <SAX/ext/DeclHandler.h>
#include <SAX/helpers/PropertyNames.h>
#include <SAX/helpers/StringAdaptor.h>
#include <iostream>

// Include the MSXML definitions.
#include <msxml2.h>

// Declare the ProgID used in the version dependent MSXML 4.0 library
// up here rather then buried somewhere in the code.
#define MSXML_PROGID_NAME   "Msxml2.SAXXMLReader.4.0"

//
// Declare the 'smart pointer' type to simplify COM handling.
#include <comdef.h>
_COM_SMARTPTR_TYPEDEF(ISAXXMLReader, __uuidof(ISAXXMLReader));

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
    typedef SAX::basic_ErrorHandler<stringT> errorHandlerT;
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
    virtual void setErrorHandler(SAX::basic_ErrorHandler<stringT>& handler);
    virtual SAX::basic_ErrorHandler<stringT>* getErrorHandler() const;

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
        LocatorAdaptor(ISAXLocator __RPC_FAR* locator) : locator_(0) { setLocator(locator); } 
        ~LocatorAdaptor() { setLocator(0); }

        stringT getPublicId() const
        {
          if(!locator_) 
            return stringT();

          const wchar_t* pwchPublicId;
          locator_->getPublicId(&pwchPublicId);
          stringT publicId(SA_.makeStringT(pwchPublicId));
          return publicId;
        } // getPublicId
    
        stringT getSystemId() const
        {
          if(!locator_)
            return stringT();

          const wchar_t* pwchSystemId;
          locator_->getSystemId(&pwchSystemId);
          stringT systemId(SA_.makeStringT(pwchSystemId));
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
        string_adaptorT SA_;
    }; // class LocatorAdaptor

    class DTDHandlerAdaptor : public ISAXDTDHandler 
    {
      public:
        DTDHandlerAdaptor() : dtdHandler_(0) { }
        ~DTDHandlerAdaptor() { }

        void setDTDHandler(SAX::basic_DTDHandler<stringT>& handler) { dtdHandler_ = &handler; }
        SAX::basic_DTDHandler<stringT>* getDTDHandler() const { return dtdHandler_; }

    virtual HRESULT STDMETHODCALLTYPE notationDecl( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t *pwchSystemId,
            /* [in] */ int cchSystemId)
        {
          if(dtdHandler_)
            dtdHandler_->notationDecl(SA_.makeStringT(pwchName, cchName),
                                      SA_.makeStringT(pwchPublicId, cchPublicId),
                                      SA_.makeStringT(pwchSystemId, cchSystemId));
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

    class ContentHandlerAdaptor : public ISAXContentHandler 
    {
      public:
        ContentHandlerAdaptor() : contentHandler_(0) { } 
        ~ContentHandlerAdaptor() { }

        void setContentHandler(SAX::basic_ContentHandler<stringT>& handler) { contentHandler_ = &handler; }
        SAX::basic_ContentHandler<stringT>* getContentHandler() const { return contentHandler_; }


        virtual HRESULT STDMETHODCALLTYPE putDocumentLocator( 
                               /* [in] */ ISAXLocator *pLocator)
        {
          locator_.setLocator(pLocator);
          if(contentHandler_) contentHandler_->setDocumentLocator(locator_);
          return S_OK;
        } // putDocumentLocation
        
        virtual HRESULT STDMETHODCALLTYPE startDocument( void)
        {
          if(contentHandler_) contentHandler_->startDocument();
          return S_OK;
        } // startDocument
        
        virtual HRESULT STDMETHODCALLTYPE endDocument( void)
        {
          if(contentHandler_) contentHandler_->endDocument();
          return S_OK;
        } // endDocument
        
        virtual HRESULT STDMETHODCALLTYPE startPrefixMapping( 
                                /* [in] */ const wchar_t *pwchPrefix,
                                /* [in] */ int cchPrefix,
                                /* [in] */ const wchar_t *pwchUri,
                                /* [in] */ int cchUri)

        {
          if(contentHandler_)
            contentHandler_->startPrefixMapping(SA_.makeStringT(pwchPrefix, cchPrefix),
                                                SA_.makeStringT(pwchUri, cchUri));
          return S_OK;
        } // startPrefixMapping
       
        virtual HRESULT STDMETHODCALLTYPE endPrefixMapping( 
                                /* [in] */ const wchar_t *pwchPrefix,
                                /* [in] */ int cchPrefix)
        {
          if(contentHandler_) contentHandler_->endPrefixMapping(SA_.makeStringT(pwchPrefix, cchPrefix));
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
            AttributesAdaptor attrs(pAttributes);
            contentHandler_->startElement(SA_.makeStringT(pwchNamespaceUri, cchNamespaceUri), 
                                          SA_.makeStringT(pwchLocalName, cchLocalName), 
                                          SA_.makeStringT(pwchQName, cchQName), 
                                          attrs);
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
            contentHandler_->endElement(SA_.makeStringT(pwchNamespaceUri, cchNamespaceUri), 
                                        SA_.makeStringT(pwchLocalName, cchLocalName), 
                                        SA_.makeStringT(pwchQName, cchQName));
          return S_OK;
        } // endElement
        
        virtual HRESULT STDMETHODCALLTYPE characters( 
            /* [in] */ const wchar_t *pwchChars,
            /* [in] */ int cchChars)
        {
          if(contentHandler_) contentHandler_->characters(SA_.makeStringT(pwchChars, cchChars));
          return S_OK;
        } // characters
        
        virtual HRESULT STDMETHODCALLTYPE ignorableWhitespace( 
            /* [in] */ const wchar_t *pwchChars,
            /* [in] */ int cchChars)
        {
          if(contentHandler_)
            contentHandler_->ignorableWhitespace(SA_.makeStringT(pwchChars, cchChars));
          return S_OK;
        } // ignorableWhitespace
        
        virtual HRESULT STDMETHODCALLTYPE processingInstruction( 
            /* [in] */ const wchar_t *pwchTarget,
            /* [in] */ int cchTarget,
            /* [in] */ const wchar_t *pwchData,
            /* [in] */ int cchData)
        {
          if(contentHandler_)
            contentHandler_->processingInstruction(SA_.makeStringT(pwchTarget, cchTarget),
                                                   SA_.makeStringT(pwchData, cchData));
          return S_OK;
        } // processingInstruction
        
        virtual HRESULT STDMETHODCALLTYPE skippedEntity( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName)
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

            virtual stringT getURI(unsigned int index) const
            {
              const wchar_t* pwchUri;
              int cchUri;
              HRESULT hr = attributes_->getURI(index, &pwchUri, &cchUri);
              if (FAILED(hr))
                return stringT();
              stringT uri(SA_.makeStringT(pwchUri, cchUri));
              return uri;
            } // getURI

            virtual stringT getLocalName(unsigned int index) const
            {
              const wchar_t* pwchLocalName;
              int cchLocalName;
              HRESULT hr = attributes_->getLocalName(index, &pwchLocalName, &cchLocalName);
              if (FAILED(hr))
                return stringT();
              stringT localName(SA_.makeStringT(pwchLocalName, cchLocalName));
              return localName;
            } // getLocalName

            virtual stringT getQName(unsigned int index) const
            {
              const wchar_t* pwchQName;
              int cchQName;
              HRESULT hr = attributes_->getQName(index, &pwchQName, &cchQName);
              if (FAILED(hr))
                return stringT();
              stringT qName(SA_.makeStringT(pwchQName, cchQName));
              return qName;
            } // getQName

            virtual stringT getType(unsigned int index) const
            {
              const wchar_t* pwchType;
              int cchType;
              HRESULT hr = attributes_->getType(index, &pwchType, &cchType);
              if (FAILED(hr))
                return stringT();
              stringT type(SA_.makeStringT(pwchType, cchType));
              return type;
            } // getType

            virtual stringT getValue(unsigned int index) const
            {
              const wchar_t* pwchValue;
              int cchValue;
              HRESULT hr = attributes_->getValue(index, &pwchValue, &cchValue);
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
              HRESULT hr = attributes_->getIndexFromName(wUri.data(), static_cast<int>(wUri.length()),
                                                         wLocalName.data(), static_cast<int>(wLocalName.length()),
                                                         &index);
              return index;
            } // getIndex

            virtual int getIndex(const stringT& qName) const
            {
              int index = -1;
              std::wstring wQName(SA_.asStdWString(qName));
              attributes_->getIndexFromQName(wQName.data(), static_cast<int>(wQName.length()), &index);
              return index;
            } // getIndex

            virtual stringT getType(const stringT& uri, const stringT& localName) const
            {
              const wchar_t* pwchType;
              int cchType;
              std::wstring wUri(SA_.asStdWString(uri));
              std::wstring wLocalName(SA_.asStdWString(localName));
              HRESULT hr = attributes_->getTypeFromName(wUri.data(), static_cast<int>(wUri.length()),
                                                        wLocalName.data(), static_cast<int>(wLocalName.length()),
                                                        &pwchType, &cchType);
              if (FAILED(hr))
                return stringT();
              stringT type(SA_.makeStringT(pwchType, cchType));
              return type;
            } // getType

            virtual stringT getType(const stringT& qName) const
            {
              const wchar_t* pwchType;
              int cchType;
              std::wstring wQName(SA_.asStdWString(qName));
              HRESULT hr = attributes_->getTypeFromQName(wQName.data(), static_cast<int>(wQName.length()),
                                                         &pwchType, &cchType);
              if (FAILED(hr))
                return stringT();
              stringT type(SA_.makeStringT(pwchType, cchType));
              return type;
            } // getType

            virtual stringT getValue(const stringT& uri, const stringT& localName) const
            {
              const wchar_t* pwchValue;
              int cchValue;
              std::wstring wUri(SA_.asStdWString(uri));
              std::wstring wLocalName(SA_.asStdWString(localName));
              HRESULT hr = attributes_->getValueFromName(wUri.data(), static_cast<int>(wUri.length()),
                                                         wLocalName.data(), static_cast<int>(wLocalName.length()),
                                                         &pwchValue, &cchValue);
              if (FAILED(hr))
                return stringT();
              stringT value(SA_.makeStringT(pwchValue, cchValue));
              return value;
            } // getValue

            virtual stringT getValue(const stringT& qname) const
            {
              const wchar_t* pwchValue;
              int cchValue;
              std::wstring wQName(SA_.asStdWString(qname));
              HRESULT hr = attributes_->getValueFromQName(wQName.data(), static_cast<int>(wQName.length()),
                                                          &pwchValue, &cchValue);
              if (FAILED(hr))
                return stringT();
              stringT value(SA_.makeStringT(pwchValue, cchValue));
              return value;
            } // getValue

          private:
            ISAXAttributes __RPC_FAR *attributes_;
            string_adaptorT SA_;

            AttributesAdaptor();
        }; // class AttributesAdaptor
    }; // class ContentHandlerAdaptor

    class ErrorHandlerAdaptor : public ISAXErrorHandler 
    {
      public:
        ErrorHandlerAdaptor() :   errorHandler_(0) { }
        virtual ~ErrorHandlerAdaptor() { }

        void setErrorHandler(SAX::basic_ErrorHandler<stringT>& handler) { errorHandler_ = &handler; }
        SAX::basic_ErrorHandler<stringT>* getErrorHandler() const { return errorHandler_; }

        virtual HRESULT STDMETHODCALLTYPE error( 
            /* [in] */ ISAXLocator *pLocator,
            /* [in] */ const wchar_t *pwchErrorMessage,
            /* [in] */ HRESULT hrErrorCode)
        {
          stringT errorMsg(SA_.makeStringT(pwchErrorMessage));
          if(errorHandler_)
            errorHandler_->error(SAX::basic_SAXParseException<stringT>(SA_.asStdString(errorMsg), LocatorAdaptor(pLocator)));
          return S_OK;
        } // error

        virtual HRESULT STDMETHODCALLTYPE fatalError( 
            /* [in] */ ISAXLocator *pLocator,
            /* [in] */ const wchar_t *pwchErrorMessage,
            /* [in] */ HRESULT hrErrorCode)
        {
          stringT errorMsg(SA_.makeStringT(pwchErrorMessage));
          if(errorHandler_)
            errorHandler_->fatalError(SAX::basic_SAXParseException<stringT>(SA_.asStdString(errorMsg), LocatorAdaptor(pLocator)));
          return S_OK;
        } // fatalError

        virtual HRESULT STDMETHODCALLTYPE ignorableWarning( 
            /* [in] */ ISAXLocator *pLocator,
            /* [in] */ const wchar_t *pwchErrorMessage,
            /* [in] */ HRESULT hrErrorCode)
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
        SAX::basic_ErrorHandler<stringT>* errorHandler_;
        string_adaptorT SA_;
    }; // class ErrorHandlerAdaptor

    class LexicalHandlerAdaptor : public ISAXLexicalHandler 
    {
      public:
        LexicalHandlerAdaptor() : lexicalHandler_(0) { }
        virtual ~LexicalHandlerAdaptor() { }

        void setLexicalHandler(SAX::basic_LexicalHandler<stringT>& handler) { lexicalHandler_ = &handler; }
        SAX::basic_LexicalHandler<stringT>* getLexicalHandler() const { return lexicalHandler_; }

        virtual HRESULT STDMETHODCALLTYPE startDTD( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t *pwchSystemId,
            /* [in] */ int cchSystemId)
        {
          if(lexicalHandler_)
            lexicalHandler_->startDTD(SA_.makeStringT(pwchName, cchName),
                                      SA_.makeStringT(pwchPublicId, cchPublicId),
                                      SA_.makeStringT(pwchSystemId, cchSystemId));
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
            lexicalHandler_->startEntity(SA_.makeStringT(pwchName, cchName));
          return S_OK;
        } // startEntity

        virtual HRESULT STDMETHODCALLTYPE endEntity( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName)
        {
          if(lexicalHandler_)
            lexicalHandler_->endEntity(SA_.makeStringT(pwchName, cchName));
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
            lexicalHandler_->comment(SA_.makeStringT(pwchChars, cchChars));
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
        SAX::basic_LexicalHandler<stringT>* lexicalHandler_;
        string_adaptorT SA_;
    }; // class LexicalHandlerAdaptor

    class DeclHandlerAdaptor : public ISAXDeclHandler 
    {
      public:
        DeclHandlerAdaptor() : declHandler_(0) { }
        virtual ~DeclHandlerAdaptor() { }

        void setDeclHandler(SAX::basic_DeclHandler<stringT>& handler) { declHandler_ = &handler; }
        SAX::basic_DeclHandler<stringT>* getDeclHandler() const { return declHandler_; }

        virtual HRESULT STDMETHODCALLTYPE elementDecl( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchModel,
            /* [in] */ int cchModel)
        {
          if(declHandler_)
            declHandler_->elementDecl(SA_.makeStringT(pwchName, cchName),
                                      SA_.makeStringT(pwchModel, cchModel));
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
            declHandler_->attributeDecl(SA_.makeStringT(pwchElementName, cchElementName),
                                        SA_.makeStringT(pwchAttributeName, cchAttributeName),
                                        SA_.makeStringT(pwchType, cchType),
                                        SA_.makeStringT(pwchValueDefault, cchValueDefault),
                                        SA_.makeStringT(pwchValue, cchValue));
          return S_OK;
        } // attributeDecl

        virtual HRESULT STDMETHODCALLTYPE internalEntityDecl( 
            /* [in] */ const wchar_t *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t *pwchValue,
            /* [in] */ int cchValue)
        {
          if(declHandler_)
            declHandler_->internalEntityDecl(SA_.makeStringT(pwchName, cchName),
                                             SA_.makeStringT(pwchValue, cchValue));
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
          if(riid == __uuidof(ISAXDeclHandler))
            *ppvObject = reinterpret_cast<void*>(this);
          return 0;
        } // QueryInterface

        unsigned long __stdcall AddRef() { return 0; }
        unsigned long __stdcall Release() { return 0; }

      private:
        SAX::basic_DeclHandler<stringT>* declHandler_;
        string_adaptorT SA_;
    }; // class DeclHandlerAdaptor

    class StreamAdaptor : public ISequentialStream
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

    ISAXXMLReaderPtr reader_;
    string_adaptorT SA_;
    SAX::PropertyNames<stringT, string_adaptorT> properties_;
}; // class msxml

template<class stringT, class COMInitializerT, class string_adaptorT>
msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::msxml2_wrapper()
{

  reader_.CreateInstance(MSXML_PROGID_NAME);
  if (reader_.GetInterfacePtr() == NULL)
  {
    std::cerr << "MSXML SAX Reader 4.0 not instanciated, trying older versions." 
              << std::endl << std::flush;
    reader_.CreateInstance(__uuidof(ISAXXMLReader));
    if (reader_.GetInterfacePtr() == NULL)
    {
      std::cerr << "MSXML SAX Reader (pre-4.0) not instanciated." 
                << std::endl << std::flush;
      exit(1);
    }
  }
  reader_.AddRef();
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

template<class stringT, class COMInitializerT, class string_adaptorT>
msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::~msxml2_wrapper()
{
} // ~msxml2_wrapper

template<class stringT, class COMInitializerT, class string_adaptorT>
bool msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::getFeature(const stringT& name) const
{
  VARIANT_BOOL feature;
  std::wstring wName(SA_.asStdWString(name));
  reader_->getFeature(wName.c_str(), &feature);
  return (feature == VARIANT_TRUE) ? true : false;
} // msxml2_wrapper::getFeature

template<class stringT, class COMInitializerT, class string_adaptorT>
void msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::setFeature(const stringT& name, bool value)
{
  std::wstring wName(SA_.asStdWString(name));
  reader_->putFeature(wName.c_str(), value);
} // setFeature

template<class stringT, class COMInitializerT, class string_adaptorT>
void msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::setErrorHandler(SAX::basic_ErrorHandler<stringT>& handler)
{
	errorHandler_.setErrorHandler(handler);
} // setErrorHandler

template<class stringT, class COMInitializerT, class string_adaptorT>
SAX::basic_ErrorHandler<stringT>* msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::getErrorHandler() const
{
  return errorHandler_.getErrorHandler();
} // getErrorHandler

template<class stringT, class COMInitializerT, class string_adaptorT>
#ifndef ARABICA_VS6_WORKAROUND
std::auto_ptr<typename SAX::basic_XMLReader<stringT>::PropertyBase> msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::doGetProperty(const stringT& name)
#else
std::auto_ptr<SAX::basic_XMLReader<stringT>::PropertyBase> msxml2_wrapper<stringT, COMInitializerT, string_adaptorT>::doGetProperty(const stringT& name)
#endif
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
} // parse

} // namespace SAX

#endif
// end of file

