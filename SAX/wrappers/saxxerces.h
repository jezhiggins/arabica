#ifndef ARABICA_SAX_XERCES_H
#define ARABICA_SAX_XERCES_H
//---------------------------------------------------------------------------
// A SAX2 wrapper class for Xerces.
//
// $Id$
//---------------------------------------------------------------------------

// Debugging code for the doSetProperty and doGetProperty methods.
// Since these methods use runtime casting, it is often helpful to
// know the exact type of a method's arguments to compare with
// what is expected.  This is hard, even with current (2003)
// debuggers, so this code can print it out, assuming you've
// compiled with gcc 3.2
//
// Example usage is given in doSetProperty

// Use only with GCC 3.2
#ifdef SAXXERCES_DEBUG

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

// Demangle Run-Time Type Information std::type_info struct.
std::ostream& operator<<(std::ostream& o, const std::type_info& ti)
{
  int status;
  char *realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
  if (status != 0)
    o.setstate(std::ios_base::failbit);
  o << realname;
  free(realname);
  return o;
}
#endif

#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include <SAX/Attributes.h>
#include <SAX/InputSource.h>
#include <SAX/XMLReader.h>
#include <SAX/ext/ProgressiveParser.h>
#include <SAX/SAXParseException.h>
#include <SAX/SAXNotRecognizedException.h>
#include <SAX/SAXNotSupportedException.h>
#include <SAX/ext/LexicalHandler.h>
#include <SAX/ext/DeclHandler.h>
#include <SAX/IStreamHandle.h>
#include <SAX/wrappers/XercesPropertyNames.h>
#include <SAX/wrappers/XercesFeatureNames.h>

// Xerces Includes
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/ContentHandler.hpp>
#include <xercesc/sax2/LexicalHandler.hpp>
#include <xercesc/sax2/DeclHandler.hpp>
#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/sax/DTDHandler.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/Janitor.hpp>

#include <xercesc/util/TransService.hpp>

#ifndef XERCES_HAS_CPP_NAMESPACE
#define XERCES_CPP_NAMESPACE
#endif

namespace SAX
{

namespace XercesImpl
{
  ///////////////////////////////
  // Xerces platform initializer
  /**
    * Class to handle calls to XMLPlatformUtils::Initialize() and
    * XMLPlatformUtils::Terminate().
    *
    * Without such a class, calls to Initialize() and Terminate() may be nested
    * and cause evil consequences.  Eg. A typical use of the old xerces_wrapper
    * could have resulted in:
    * <pre>
    * // Construct two xerces_wrappers.
    *     XMLPlatformUtils::Initialize()
    *     XMLPlatformUtils::Initialize()
    *     
    * // do stuff
    *
    * // Get rid of one of the xerces_wrappers
    *     XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate()
    *     
    * // do more stuff -- this is _after_ a call to Terminate()...
    *
    *     XMLPlatformUtils::Terminate()
    * </pre>
    */
  class xerces_initializer
  {
    public:
      xerces_initializer() { doInitialize(); }
      ~xerces_initializer() { doTerminate(); }

    private:
      void doInitialize();
      void doTerminate();

      static int count_;
  }; // class xerces_initializer
} // namespace XercesImpl

template<class string_type, class string_adaptor_type = SAX::default_string_adaptor<string_type> >
class xerces_wrapper : public SAX::basic_ProgressiveParser<string_type>
{
  private:
    typedef string_adaptor_type string_adaptorT;

  protected:
    typedef SAX::basic_XMLReader<string_type> base;

  public:
    typedef typename base::EntityResolverT EntityResolverT;
    typedef typename base::DTDHandlerT DTDHandlerT;
    typedef typename base::ContentHandlerT ContentHandlerT;
    typedef typename base::InputSourceT InputSourceT;
    typedef SAX::basic_LexicalHandler<string_type> LexicalHandlerT;
    typedef SAX::basic_Locator<string_type> LocatorT;
    typedef SAX::basic_Attributes<string_type> AttributesT;
    typedef SAX::basic_DeclHandler<string_type> DeclHandlerT;

    typedef SAX::XercesFeatureNames<string_type, string_adaptorT> featuresT;

    xerces_wrapper();
    virtual ~xerces_wrapper();

    /////////////////////////////////////////////////
    // Configuration
    virtual bool getFeature(const string_type& name) const;
    virtual void setFeature(const string_type& name, bool value);
  
    /////////////////////////////////////////////////
    // Event Handlers
    virtual void setEntityResolver(EntityResolverT& resolver) { entityResolverAdaptor_.setEntityResolver(resolver); }
    virtual EntityResolverT* getEntityResolver() const { return entityResolverAdaptor_.getEntityResolver(); }
    virtual void setDTDHandler(DTDHandlerT& handler) { dtdHandlerAdaptor_.setDTDHandler(handler); }
    virtual DTDHandlerT* getDTDHandler() const { return dtdHandlerAdaptor_.getDTDHandler(); }
    virtual void setContentHandler(ContentHandlerT& handler) { contentHandlerAdaptor_.setContentHandler(handler); }
    virtual ContentHandlerT* getContentHandler() const { return contentHandlerAdaptor_.getContentHandler(); }
    virtual void setErrorHandler(ErrorHandler& handler) { errorHandlerAdaptor_.setErrorHandler(handler); }
    virtual ErrorHandler* getErrorHandler() const { return errorHandlerAdaptor_.getErrorHandler(); }

    //////////////////////////////////////////////////
    // Parsing
    virtual void parse(InputSourceT& input);

    //////////////////////////////////////////////////
    // Progressive Parsing
    //////////////////////////////////////////////////

    /** @name Progressive Parsing */
    //@{
    virtual bool parseFirst(const string_type& systemId, XMLPScanToken& toFill)
    {
      InputSourceT is(systemId);
      return parseFirst(is, toFill);
    }

    virtual bool parseFirst(InputSourceT& input,
                            XMLPScanToken& toFill);

    virtual bool parseNext(XMLPScanToken& token);

    virtual void parseReset(XMLPScanToken& token);
    //@}

  protected:
    virtual std::auto_ptr<typename base::PropertyBase> doGetProperty(const string_type& name);
    virtual void doSetProperty(const string_type& name, std::auto_ptr<typename base::PropertyBase> value);

  private:
    ///////////////////////////////
    // String adaptor for XMLCh
    // * For the null-terminated version, we convert the array of XMLCh to a
    //   null-terminated vector of wchar_t.  We then pass &vector[0] to the
    //   parent method.
    // * For the known length version, we convert the the array of XMLCh to a
    //   vector of wchar_t.  We then pass &vector[0] and length to the parent
    //   method.
    class xerces_string_adaptor : public string_adaptorT
    {
      public:
        typedef typename string_type::value_type value_type;
        typedef string_adaptorT base;

        typedef std::vector<wchar_t> wVector;

        string_type makeStringT(const XMLCh* str) const
        {
          if (str)
          {
            wVector buffer;
            std::insert_iterator<wVector> inserter(buffer, buffer.begin());

            // We want the trailing 0 character.
            *inserter = *str;
            while (*str != 0)  // str points to the character we've just copied
            {
              *++inserter = *++str;
            }
            return base::makeStringT(&buffer[0]);
          }
          else
          {
            return base::makeStringT("");
          }
        } // makeStringT

        string_type makeStringT(const XMLCh* str, int length) const
        {
          if (str && length)
          {
            wVector buffer;
            std::insert_iterator<wVector> inserter(buffer, buffer.begin());

            // We don't want any trailing characters.
            const XMLCh* end = str + length;
            while (str < end)
            {
              *inserter++ = *str++;
            }
            return base::makeStringT(&buffer[0], length);
          }
          else
          {
            return base::makeStringT("");
          }
        } // makeStringT
      
        XMLCh* asXMLChString(const string_type& s) const
	      {
	        std::string str = base::asStdString(s);
	        return XERCES_CPP_NAMESPACE::XMLString::transcode(str.c_str());
	      } // asXMLChString
    }; // class xerces_string_adaptor

    ///////////////////////////////
    // Adaptors
    class LocatorAdaptor : public LocatorT
    {
      public:
        LocatorAdaptor() : locator_(0) { }
        LocatorAdaptor(const XERCES_CPP_NAMESPACE::Locator* const locator) : locator_(locator) { } 
        ~LocatorAdaptor() { }

        string_type getPublicId() const
        {
          if(!locator_) 
            return string_type();

          return SA_.makeStringT(locator_->getPublicId());
        } // getPublicId
    
        string_type getSystemId() const
        {
          if(!locator_)
            return string_type();

          return SA_.makeStringT(locator_->getSystemId());
        } // getSystemId
    
        int getLineNumber() const
        {
          if(!locator_)
            return -1;

          return locator_->getLineNumber();
        } // getLineNumber
    
        int getColumnNumber() const
        {
          if(!locator_)
            return -1;

          return locator_->getColumnNumber();
        } // getColumnNumber
    
        void setLocator(const XERCES_CPP_NAMESPACE::Locator* const locator)
        {
          locator_ = locator;
        } // setLocator

      private:
        const XERCES_CPP_NAMESPACE::Locator* locator_;
        xerces_string_adaptor SA_;
    }; // class LocatorAdaptor

    class EntityResolverAdaptor : public XERCES_CPP_NAMESPACE::EntityResolver
    {
      public:
        EntityResolverAdaptor() : entityResolverHandler_(0) { }
        ~EntityResolverAdaptor() { }

        void setEntityResolver(EntityResolverT& handler) 
              {
                entityResolverHandler_ = &handler; 
              }
        EntityResolverT* getEntityResolver() const
        {
            return entityResolverHandler_;
        }

        virtual XERCES_CPP_NAMESPACE::InputSource* resolveEntity(const XMLCh* const publicId,
                                           const XMLCh* const systemId)
              {
                InputSourceT source;
            if(entityResolverHandler_)
                  {
                    source = entityResolverHandler_->resolveEntity(SA_.makeStringT(publicId),
                                                           SA_.makeStringT(systemId));
                  }
                  // If all of these are empty, the EntityResolver has requested that we
                  // use the default entity resolver.
                  if ((source.getByteStream() == 0) &&
                      (source.getPublicId().empty()) &&
                      (source.getSystemId().empty()))
                  {
                // Xerces-C takes a NULL (0) return to mean "use the default entity
                // resolver".
                      return 0;
                  }
                  else
                  {
                      return new InputSourceAdaptor(source);
                  }
              }

      private:
        EntityResolverT* entityResolverHandler_;
        xerces_string_adaptor SA_;
    }; // class EntityResolverAdaptor

    class DTDHandlerAdaptor : public XERCES_CPP_NAMESPACE::DTDHandler 
    {
      public:
        DTDHandlerAdaptor() : dtdHandler_(0) { }
        ~DTDHandlerAdaptor() { }

        void setDTDHandler(DTDHandlerT& handler) { dtdHandler_ = &handler; }
        DTDHandlerT* getDTDHandler() const { return dtdHandler_; }

        virtual void notationDecl(const XMLCh* const name,
                                  const XMLCh* const publicId, 
                                  const XMLCh* const systemId)
        {
          if(dtdHandler_)
            dtdHandler_->notationDecl(SA_.makeStringT(name),
                                      SA_.makeStringT(publicId),
                                      SA_.makeStringT(systemId));
        } // notationDecl
        virtual void unparsedEntityDecl(const XMLCh* const name,
                                        const XMLCh* const publicId, 
                                        const XMLCh* const systemId,
                                        const XMLCh* const notationName)
        {
          if(dtdHandler_)
            dtdHandler_->unparsedEntityDecl(SA_.makeStringT(name),
                                            SA_.makeStringT(publicId),
                                            SA_.makeStringT(systemId),
                                            SA_.makeStringT(notationName));
        } // unparsedEntityDecl

        virtual void resetDocType() 
        {
          // no op
        } // resetDocType

      private:
        DTDHandlerT* dtdHandler_;
        xerces_string_adaptor SA_;
    }; // class DTDHandlerAdaptor

    class ContentHandlerAdaptor : public XERCES_CPP_NAMESPACE::ContentHandler 
    {
      public:
        ContentHandlerAdaptor() : contentHandler_(0) { } 
        ~ContentHandlerAdaptor() { }

        void setContentHandler(ContentHandlerT& handler) { contentHandler_ = &handler; }
        ContentHandlerT* getContentHandler() const { return contentHandler_; }

        virtual void setDocumentLocator(const XERCES_CPP_NAMESPACE::Locator* const locator)
        {
          locator_.setLocator(locator);
          if(contentHandler_) 
            contentHandler_->setDocumentLocator(locator_);
        } // putDocumentLocation
        
        virtual void startDocument()
        {
          if(contentHandler_) 
            contentHandler_->startDocument();
        } // startDocument
        
        virtual void endDocument()
        {
          if(contentHandler_) 
            contentHandler_->endDocument();
        } // endDocument
        
        virtual void startPrefixMapping(const XMLCh* const prefix, const XMLCh* const uri)
        {
          if(contentHandler_)
            contentHandler_->startPrefixMapping(SA_.makeStringT(prefix), SA_.makeStringT(uri));
        } // startPrefixMapping
       
        virtual void endPrefixMapping(const XMLCh* const prefix)
        {
          if(contentHandler_)
            contentHandler_->endPrefixMapping(SA_.makeStringT(prefix));
        } // endPrefixMapping
        
        virtual void startElement(const XMLCh* const namespaceUri,
                                  const XMLCh* const localName,
                                  const XMLCh* const rawName,
                                  const XERCES_CPP_NAMESPACE::Attributes& attrs)
        {
          if(contentHandler_)
          {
            AttributesAdaptor attrAdaptor(attrs);
            contentHandler_->startElement(SA_.makeStringT(namespaceUri),
                                          SA_.makeStringT(localName),
                                          SA_.makeStringT(rawName),
                                          attrAdaptor);
          } // if ...
        } // startElement
        
        virtual void endElement(const XMLCh* const namespaceUri,
                                const XMLCh* const localName,
                                const XMLCh* const rawName)
        {
          if(contentHandler_)
            contentHandler_->endElement(SA_.makeStringT(namespaceUri),
                                        SA_.makeStringT(localName),
                                        SA_.makeStringT(rawName));
        } // endElement
        
        virtual void characters(const XMLCh* const chars, const unsigned int length)
        {
          if(contentHandler_) 
            contentHandler_->characters(SA_.makeStringT(chars, length));
        } // characters
        
        virtual void ignorableWhitespace(const XMLCh* const chars, const unsigned int length)
        {
          if(contentHandler_)
            contentHandler_->ignorableWhitespace(SA_.makeStringT(chars, length));
        } // ignorableWhitespace
        
        virtual void processingInstruction(const XMLCh* const target,
                                           const XMLCh* const data)
        {
          if(contentHandler_)
            contentHandler_->processingInstruction(SA_.makeStringT(target),
                                                   SA_.makeStringT(data));
        } // processingInstruction
        
        virtual void skippedEntity(const XMLCh* const name)
        {
          if(contentHandler_)
            contentHandler_->skippedEntity(SA_.makeStringT(name));
        } // skippedEntity

      private:
        ////////////////////////////////////////////////
        // member varaibles
        ContentHandlerT* contentHandler_;
        LocatorAdaptor locator_;
        xerces_string_adaptor SA_;

        //////////////////////////////////////////////////////
        // COM interface -> C++ interface adaptors
        class AttributesAdaptor : public AttributesT
        {
          public:
            AttributesAdaptor(const XERCES_CPP_NAMESPACE::Attributes& attrs) : attributes_(attrs) { }
            ~AttributesAdaptor() { }

            /////////////////////////
            // indexed access
            virtual int getLength() const
            {
              return attributes_.getLength();
            } // getLength
            virtual string_type getURI(unsigned int index) const
            {
              return SA_.makeStringT(attributes_.getURI(index));
            } // getURI
            virtual string_type getLocalName(unsigned int index) const
            {
              return SA_.makeStringT(attributes_.getLocalName(index));
            } // getLocalName
            virtual string_type getQName(unsigned int index) const
            {
              return SA_.makeStringT(attributes_.getQName(index));
            } // getQName
            virtual string_type getType(unsigned int index) const
            {
              return SA_.makeStringT(attributes_.getType(index));
            } // getType
            virtual string_type getValue(unsigned int index) const
            {
              return SA_.makeStringT(attributes_.getValue(index));
            } // getValue

            /////////////////////////
            // name based query
            virtual int getIndex(const string_type& uri, const string_type& localName) const
            {
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wUri(SA_.asXMLChString(uri));
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wLocalName(SA_.asXMLChString(localName));
              return attributes_.getIndex(&wUri[0], &wLocalName[0]);
            } // getIndex
            virtual int getIndex(const string_type& qName) const
            {
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wQName(SA_.asXMLChString(qName));
              return attributes_.getIndex(&wQName[0]);
            } // getIndex
            virtual string_type getType(const string_type& uri, const string_type& localName) const
            {
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wUri(SA_.asXMLChString(uri));
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wLocalName(SA_.asXMLChString(localName));
              return SA_.makeStringT(attributes_.getType(&wUri[0], &wLocalName[0]));
            } // getType
            virtual string_type getType(const string_type& qName) const
            {
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wQName(SA_.asXMLChString(qName));
              return SA_.makeStringT(attributes_.getType(&wQName[0]));
            } // getType
            virtual string_type getValue(const string_type& uri, const string_type& localName) const
            {
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wUri(SA_.asXMLChString(uri));
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wLocalName(SA_.asXMLChString(localName));
              return SA_.makeStringT(attributes_.getValue(&wUri[0], &wLocalName[0]));
            } // getValue
            virtual string_type getValue(const string_type& qname) const
            {
              XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wQName(SA_.asXMLChString(qname));
              return SA_.makeStringT(attributes_.getValue(&wQName[0]));
            } // getValue

          private:
            const XERCES_CPP_NAMESPACE::Attributes& attributes_;
            xerces_string_adaptor SA_;

            AttributesAdaptor();
        }; // class AttributesAdaptor
    }; // class ContentHandlerAdaptor

    class ErrorHandlerAdaptor : public XERCES_CPP_NAMESPACE::ErrorHandler 
    {
      public:
        ErrorHandlerAdaptor() :   errorHandler_(0) { }
        virtual ~ErrorHandlerAdaptor() { }

        void setErrorHandler(SAX::ErrorHandler& handler) { errorHandler_ = &handler; }
        SAX::ErrorHandler* getErrorHandler() const { return errorHandler_; }

        virtual void warning(const XERCES_CPP_NAMESPACE::SAXParseException& exception)
        {
          handleError(exception, &SAX::ErrorHandler::warning);
        } // warning

        virtual void error(const XERCES_CPP_NAMESPACE::SAXParseException& exception)
        {
          handleError(exception, &SAX::ErrorHandler::error);
        } // error

        virtual void fatalError(const XERCES_CPP_NAMESPACE::SAXParseException& exception)
        {
          handleError(exception, &SAX::ErrorHandler::fatalError);
        } // fatalError

        virtual void resetErrors() 
        { 
          // no op 
        } // resetErrors

      private:
        typedef void(SAX::ErrorHandler::* ErrorFn)(const SAX::SAXParseException&);

        void handleError(const XERCES_CPP_NAMESPACE::SAXParseException& exception, ErrorFn fn)
        {
          if(!errorHandler_)
            return;

          string_type errorMsg(SA_.makeStringT(exception.getMessage()));
          string_type publicId(SA_.makeStringT(exception.getPublicId()));
          string_type systemId(SA_.makeStringT(exception.getSystemId()));
          SAX::SAXParseException sp(SA_.asStdString(errorMsg),
                                                    SA_.asStdString(publicId),
                                                    SA_.asStdString(systemId),
                                                   exception.getLineNumber(),
                                                   exception.getColumnNumber());
          (errorHandler_->*fn)(sp);
        } // handleError

        SAX::ErrorHandler* errorHandler_;
        xerces_string_adaptor SA_;
    }; // class ErrorHandlerAdaptor

    class LexicalHandlerAdaptor : public XERCES_CPP_NAMESPACE::LexicalHandler 
    {
      public:
        LexicalHandlerAdaptor() : lexicalHandler_(0) { }
        virtual ~LexicalHandlerAdaptor() { }

        void setLexicalHandler(LexicalHandlerT& handler) { lexicalHandler_ = &handler; }
        LexicalHandlerT* getLexicalHandler() const { return lexicalHandler_; }

        virtual void startDTD(const XMLCh* const name,
                              const XMLCh* const publicId,
                              const XMLCh* const systemId)
        {
          if(lexicalHandler_)
            lexicalHandler_->startDTD(SA_.makeStringT(name),
                                      SA_.makeStringT(publicId),
                                      SA_.makeStringT(systemId));
        } // startDTD

        virtual void endDTD()
        {
          if(lexicalHandler_)
            lexicalHandler_->endDTD();
        } // endDTD

        virtual void startEntity(const XMLCh* const name)
        {
          if(lexicalHandler_)
            lexicalHandler_->startEntity(SA_.makeStringT(name));
        } // startEntity

        virtual void endEntity(const XMLCh* const name)
        {
          if(lexicalHandler_)
            lexicalHandler_->endEntity(SA_.makeStringT(name));
        } // endEntity

        virtual void startCDATA()
        {
          if(lexicalHandler_)
            lexicalHandler_->startCDATA();
        } // startCDATA

        virtual void endCDATA()
        {
          if(lexicalHandler_)
            lexicalHandler_->endCDATA();
        } // endCDATA

        virtual void comment(const XMLCh* const chars, const unsigned int length)
        {
          if(lexicalHandler_)
            lexicalHandler_->comment(SA_.makeStringT(chars, length));
        } // comment

      private:
        LexicalHandlerT* lexicalHandler_;
        xerces_string_adaptor SA_;
    }; // class LexicalHandlerAdaptor

    class DeclHandlerAdaptor : public XERCES_CPP_NAMESPACE::DeclHandler 
    {
      public:
        DeclHandlerAdaptor() : declHandler_(0) { }
        virtual ~DeclHandlerAdaptor() { }

        void setDeclHandler(DeclHandlerT& handler) { declHandler_ = &handler; }
        DeclHandlerT* getDeclHandler() const { return declHandler_; }

        virtual void elementDecl(const XMLCh* const name,
                                 const XMLCh* const model)
        {
          if(declHandler_)
            declHandler_->elementDecl(SA_.makeStringT(name),
                                      SA_.makeStringT(model));
        } // elementDecl

        virtual void attributeDecl(const XMLCh* const elementName,
                                   const XMLCh* const attributeName,
                                   const XMLCh* const type,
                                   const XMLCh* const valueDefault,
                                   const XMLCh* const value)
        {
          if(declHandler_)
          {
            const XMLCh* tmpValueDefault = valueDefault;
            if (tmpValueDefault == XERCES_CPP_NAMESPACE::XMLUni::fgNullString)
              tmpValueDefault = 0;
            declHandler_->attributeDecl(SA_.makeStringT(elementName),
                                        SA_.makeStringT(attributeName),
                                        SA_.makeStringT(type),
                                        SA_.makeStringT(tmpValueDefault),
                                        SA_.makeStringT(value));
          }
        } // attributeDecl

        virtual void internalEntityDecl(const XMLCh* const name,
                                        const XMLCh* const value)
        {
          if(declHandler_)
            declHandler_->internalEntityDecl(SA_.makeStringT(name),
                                             SA_.makeStringT(value));
        } // internalEntityDecl

        virtual void externalEntityDecl(const XMLCh* const name,
                                        const XMLCh* const publicId,
                                        const XMLCh* const systemId)
        {
          if(declHandler_)
            declHandler_->externalEntityDecl(SA_.makeStringT(name),
                                             SA_.makeStringT(publicId),
                                             SA_.makeStringT(systemId));
        } // externalEntityDecl

      private:
        DeclHandlerT* declHandler_;
        xerces_string_adaptor SA_;
    }; // class DeclHandlerAdaptor

    class IStreamAdaptor : public XERCES_CPP_NAMESPACE::BinInputStream
    {
      public:
        IStreamAdaptor(IStreamHandle istream)
        :   istream_(istream),
            curPos_(0)
        { }

        virtual ~IStreamAdaptor() { }

        virtual unsigned int curPos() const
        {
          return curPos_;
        } // curPos

        virtual unsigned int readBytes(XMLByte* const toFill,
                                       const unsigned int maxToRead)
        {
          istream_.get()->read(reinterpret_cast<char*>(toFill), maxToRead);
          curPos_ += istream_.get()->gcount();
          return istream_.get()->gcount();
        } // readBytes

      private:
        IStreamHandle istream_;
        unsigned int curPos_;
    }; // IStreamAdaptor

    class InputSourceAdaptor : public XERCES_CPP_NAMESPACE::InputSource
    {
      public:
        InputSourceAdaptor(const InputSourceT& source) 
        :   inputSource_(source) 
        { 
            XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wSystemId(SA_.asXMLChString(source.getSystemId()));
            XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wPublicId(SA_.asXMLChString(source.getPublicId()));
            setSystemId(&wSystemId[0]);
            setPublicId(&wPublicId[0]);
        } // InputSourceAdaptor
        virtual ~InputSourceAdaptor() { }

        virtual XERCES_CPP_NAMESPACE::BinInputStream* makeStream() const
        {
          return new IStreamAdaptor(inputSource_.getByteStreamHandle());
        } // makeStream
     
      private:
        // This is a local copy, so we do not rely on someone else keeping
        // their InputSourceT around for us.
        InputSourceT inputSource_;
        xerces_string_adaptor SA_;
    }; // class InputSourceAdaptor

    class XercesXMLPScanToken : public ::SAX::XMLPScanTokenParserImpl
    {
      public:
        XERCES_CPP_NAMESPACE::XMLPScanToken token_;
    };

    /////////////////////////////////////////////
    // Member variables
    std::auto_ptr<XercesImpl::xerces_initializer> initializer_;
    XERCES_CPP_NAMESPACE::SAX2XMLReader* xerces_;
    ContentHandlerAdaptor contentHandlerAdaptor_;
    EntityResolverAdaptor entityResolverAdaptor_;
    DTDHandlerAdaptor dtdHandlerAdaptor_;
    ErrorHandlerAdaptor errorHandlerAdaptor_;
    LexicalHandlerAdaptor lexicalHandlerAdaptor_;
    DeclHandlerAdaptor declHandlerAdaptor_;
    xerces_string_adaptor SA_;
    SAX::XercesPropertyNames<string_type, string_adaptorT> properties_;

    // Property values to return by reference
    string_type externalSchemaLocation_;
    string_type externalNoNamespaceSchemaLocation_;
}; // class xerces_wrapper

template<class string_type, class string_adaptorT>
xerces_wrapper<string_type, string_adaptorT>::xerces_wrapper()
{
  try
  {
    std::auto_ptr<XercesImpl::xerces_initializer> init(new XercesImpl::xerces_initializer());
    initializer_ = init;
  }
  catch(const XERCES_CPP_NAMESPACE::XMLException& toCatch)
  {
    string_type s = SA_.makeStringT(toCatch.getMessage());
    throw SAX::SAXException(SA_.asStdString(s));
  } // catch

  xerces_ = XERCES_CPP_NAMESPACE::XMLReaderFactory::createXMLReader();

  xerces_->setContentHandler(&contentHandlerAdaptor_);
  xerces_->setEntityResolver(&entityResolverAdaptor_);
  xerces_->setDTDHandler(&dtdHandlerAdaptor_);
  xerces_->setErrorHandler(&errorHandlerAdaptor_);
  xerces_->setLexicalHandler(&lexicalHandlerAdaptor_);
  xerces_->setDeclarationHandler(&declHandlerAdaptor_);
} // xerces_wrapper

template<class string_type, class string_adaptorT>
xerces_wrapper<string_type, string_adaptorT>::~xerces_wrapper()
{
  delete xerces_;
} // ~xerces_wrapper

template<class string_type, class string_adaptorT>
bool xerces_wrapper<string_type, string_adaptorT>::getFeature(const string_type& name) const
{
  try 
  {
    XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wName(SA_.asXMLChString(name));
    return xerces_->getFeature(&wName[0]);
  } // try
  catch(XERCES_CPP_NAMESPACE::SAXNotSupportedException& e) 
  {
    throw SAX::SAXNotSupportedException(SA_.makeStringT(e.getMessage()));
  } // catch(SAXNotSupportedException& e)
  catch(XERCES_CPP_NAMESPACE::SAXNotRecognizedException& e) 
  {
    throw SAX::SAXNotRecognizedException(SA_.makeStringT(e.getMessage()));
  } // catch(SAXNotRecognizedException& e)
} // getFeature

template<class string_type, class string_adaptorT>
void xerces_wrapper<string_type, string_adaptorT>::setFeature(const string_type& name, bool value)
{
  try 
  {
    XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> wName(SA_.asXMLChString(name));
    xerces_->setFeature(&wName[0], value);
  } // try
  catch(XERCES_CPP_NAMESPACE::SAXNotSupportedException& e) 
  {
    throw SAX::SAXNotSupportedException(SA_.makeStringT(e.getMessage()));
  } // catch(SAXNotSupportedException& e)
  catch(XERCES_CPP_NAMESPACE::SAXNotRecognizedException& e) 
  {
    throw SAX::SAXNotRecognizedException(SA_.makeStringT(e.getMessage()));
  } // catch(SAXNotRecognizedException& e)
} // setFeature

template<class string_type, class string_adaptorT>
std::auto_ptr<typename SAX::basic_XMLReader<string_type>::PropertyBase> xerces_wrapper<string_type, string_adaptorT>::doGetProperty(const string_type& name)
{
  if(name == properties_.lexicalHandler)
  {
    SAX::basic_XMLReader<string_type>::Property<LexicalHandlerT *> *prop = new SAX::basic_XMLReader<string_type>::Property<LexicalHandlerT *>(lexicalHandlerAdaptor_.getLexicalHandler());
    return std::auto_ptr<typename base::PropertyBase>(prop);
  }
  if(name == properties_.declHandler)
  {
    SAX::basic_XMLReader<string_type>::Property<DeclHandlerT*>* prop = new SAX::basic_XMLReader<string_type>::Property<DeclHandlerT*>(declHandlerAdaptor_.getDeclHandler());
    return std::auto_ptr<typename base::PropertyBase>(prop);
  }
  if (name == properties_.externalSchemaLocation)
  {
    typedef SAX::basic_XMLReader<string_type>::Property<string_type&> StringPropertyType;

    XMLCh* xercesExternalSchemaLocation = 
        static_cast<XMLCh*>(xerces_->getProperty(
            XERCES_CPP_NAMESPACE::XMLUni::fgXercesSchemaExternalSchemaLocation));

    externalSchemaLocation_ = SA_.makeStringT(xercesExternalSchemaLocation);
    std::auto_ptr<typename base::PropertyBase> toReturn(
            new StringPropertyType(externalSchemaLocation_));
#ifdef SAXXERCES_DEBUG
    std::cerr << "Returning " << typeid(toReturn)
              << "(*(" << typeid(*toReturn.get()) << ")" 
              <<  toReturn.get() << ")" 
              << " containing value [" << externalSchemaLocation_ << "]"
              <<  std::endl;
#endif
    return toReturn;
  }
  if (name == properties_.externalNoNamespaceSchemaLocation)
  {
    typedef SAX::basic_XMLReader<string_type>::Property<string_type&> StringPropertyType;

    XMLCh* xercesExternalNoNamespaceSchemaLocation = 
        static_cast<XMLCh*>(xerces_->getProperty(
            XERCES_CPP_NAMESPACE::XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation));

    externalNoNamespaceSchemaLocation_ = 
        SA_.makeStringT(xercesExternalNoNamespaceSchemaLocation);
    return std::auto_ptr<typename base::PropertyBase>(
            new StringPropertyType(externalNoNamespaceSchemaLocation_));
  }
  throw SAX::SAXNotRecognizedException("Property not recognized ");    
} // doGetProperty

template<class string_type, class string_adaptorT>
void xerces_wrapper<string_type, string_adaptorT>::doSetProperty(const string_type& name, std::auto_ptr<typename base::PropertyBase> value)
{
  if(name == properties_.lexicalHandler)
  {
    SAX::basic_XMLReader<string_type>::Property<LexicalHandlerT&>* prop = dynamic_cast<SAX::basic_XMLReader<string_type>::Property<LexicalHandlerT&>*>(value.get());

    if(!prop)
    {
      throw SAXNotSupportedException("Property LexicalHandler is wrong type, should be SAX::LexicalHandler&");
    }

    lexicalHandlerAdaptor_.setLexicalHandler(prop->get());
    return;
  } // if ...

  if(name == properties_.declHandler)
  {
    SAX::basic_XMLReader<string_type>::Property<DeclHandlerT&>* prop = dynamic_cast<SAX::basic_XMLReader<string_type>::Property<DeclHandlerT&>*>(value.get());

    if(!prop)
    {
      throw SAXNotSupportedException("Property DeclHandler is wrong type, should be SAX::DeclHandler&");
    }
    declHandlerAdaptor_.setDeclHandler(prop->get());
    return;
  } // if ...

  if (name == properties_.externalSchemaLocation)
  {
    typename base::PropertyBase* propBase = value.get();
#ifdef SAXXERCES_DEBUG
    std::cerr << "doSetProperty(externalSchemaLocation, &("
              << typeid(*propBase) << "))" << std::endl;
#endif
    typedef base::Property<string_type&> propertyType;
    propertyType* prop = dynamic_cast<propertyType*>(propBase);
#ifdef SAXXERCES_DEBUG
    std::cerr << "    Extracted property to " << typeid(prop)
              << "(" << prop << ")" << std::endl;
#endif
    if (prop)
    {
      externalSchemaLocation_ = prop->get();
#ifdef SAXXERCES_DEBUG
      std::cerr << "    Setting property to " << externalSchemaLocation_ << std::endl;
#endif
      XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> toDelete(SA_.asXMLChString(externalSchemaLocation_));
      xerces_->setProperty(XERCES_CPP_NAMESPACE::XMLUni::fgXercesSchemaExternalSchemaLocation, &toDelete[0]);
    }
    else
    {
      throw SAXNotSupportedException("Property ExternalShemaLocation is wrong type, should be string_type");
    }
    return;
  }

  if (name == properties_.externalNoNamespaceSchemaLocation)
  {
    typename base::PropertyBase* propBase = value.get();
    typedef base::Property<string_type&> propertyType;
#ifdef SAXXERCES_DEBUG
    std::cerr << "doSetProperty(externalNoNamespaceSchemaLocation, &("
              << typeid(*propBase) << "))" << std::endl;
#endif
    propertyType* prop = dynamic_cast<propertyType*>(propBase);
#ifdef SAXXERCES_DEBUG
    std::cerr << "    Extracted property to " << typeid(prop)
              << "(" << prop << ")" << std::endl;
#endif
    if (prop)
    {
      externalNoNamespaceSchemaLocation_ = prop->get();
#ifdef SAXXERCES_DEBUG
      std::cerr << "    Setting property to " << externalNoNamespaceSchemaLocation_ << std::endl;
#endif
      XERCES_CPP_NAMESPACE::ArrayJanitor<XMLCh> toDelete(SA_.asXMLChString(externalNoNamespaceSchemaLocation_));
      xerces_->setProperty(XERCES_CPP_NAMESPACE::XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation, &toDelete[0]);
    }
    else
    {
      throw SAXNotSupportedException("Property ExternalNoNamespaceSchemaLocation is wrong type, should be string_type");
    }
    return;
  }

  throw SAX::SAXNotRecognizedException("Property not recognized ");    
}


template<class string_type, class string_adaptorT>
void xerces_wrapper<string_type, string_adaptorT>::parse(InputSourceT& source)
{
  // if no stream is open, let Xerces deal with it
  if(source.getByteStream() == 0)
    xerces_->parse(SA_.asStdString(source.getSystemId()).c_str()); 
  else
  {
    // we have to wrap everything up in a Xerces friendly way
    InputSourceAdaptor isAdaptor(source);
    xerces_->parse(isAdaptor);
  } // if ...
} // parse

template<class string_type, class string_adaptorT>
bool xerces_wrapper<string_type, 
                    string_adaptorT>::parseFirst(InputSourceT& input,
                                                 XMLPScanToken& toFill)
{
  std::auto_ptr<XercesXMLPScanToken> newToken(new XercesXMLPScanToken);
  // To store the result from Xerces parseFirst().
  bool result = false;
  if (input.getByteStream() == 0)
  {
    // We can just pass the systemID to parseFirst and let Xerces open the
    // stream.
    const char* systemID = SA_.asStdString(input.getSystemId()).c_str();
    result = xerces_->parseFirst(systemID, newToken->token_);
  }
  else
  {
    // We need to wrap input in an InputSourceAdaptor.

    // isAdaptor can be a local variable because Xerces has to open any streams
    // within the parseFirst() call, so it should not need the
    // InputSourceAdaptor to hang around.
    InputSourceAdaptor isAdaptor(input);
    result = xerces_->parseFirst(isAdaptor, newToken->token_);
  }
  if (result) {
    // We need to explicitly convert to auto_ptr<base class>.
    std::auto_ptr<XMLPScanTokenParserImpl> toSet(newToken);
    toFill.setParserData(toSet);
  }
  return result;
} // parseFirst

template<class string_type, class string_adaptorT>
bool xerces_wrapper<string_type, string_adaptorT>::parseNext(XMLPScanToken& token)
{
  // Extract the XercesXMLPScanToken from within token.
  XercesXMLPScanToken* xercesToken = 
          dynamic_cast<XercesXMLPScanToken*>(token.parserImpl());
  if (xercesToken == 0)
  {
    // If it failed to cast, we can simply refuse to parse, because this call
    // clearly isn't following a successful parseFirst().
    return false;
  }
  else
  {
    // Otherwise, just pass the token to Xerces.
    return xerces_->parseNext(xercesToken->token_);
  }
} // parseNext

template<class string_type, class string_adaptorT>
void xerces_wrapper<string_type, string_adaptorT>::parseReset(XMLPScanToken& token)
{
  // Extract the XercesXMLPScanToken from within token.
  XercesXMLPScanToken* xercesToken = 
        dynamic_cast<XercesXMLPScanToken*>(token.parserImpl());
  // If it failed to cast, we can simply ignore it, because this call clearly
  // isn't following a successful parseFirst().
  if (xercesToken != 0)
  {
    xerces_->parseReset(xercesToken->token_);
  }
} // parseReset

} // namespace SAX

#endif
// end of file
