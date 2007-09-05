#ifndef ARABICA_XML_FILTER_IMPL_H
#define ARABICA_XML_FILTER_IMPL_H

// XMLFilterImpl.h

#include <SAX/ArabicaConfig.hpp>
#include <string>
#include <SAX/XMLFilter.hpp>
#include <SAX/helpers/DefaultHandler.hpp>
#include <SAX/SAXNotRecognizedException.hpp>
#include <Utils/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Base class for deriving an XML filter.
 *
 * <p>This class is designed to sit between an {@link XMLReader
 * XMLReader} and the client application's event handlers.  By default, it
 * does nothing but pass requests up to the reader and events
 * on to the handlers unmodified, but subclasses can override
 * specific methods to modify the event stream or the configuration
 * requests as they pass through.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see XMLFilter
 * @see XMLReader
 * @see EntityResolver
 * @see DTDHandler
 * @see ContentHandler
 * @see ErrorHandler
 */
template<class string_type, class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
class XMLFilterImpl : public XMLFilter<string_type>,
                            public EntityResolver<string_type>, 
                  					public DTDHandler<string_type>,
					                  public ContentHandler<string_type>, 
					                  public ErrorHandler<string_type>,
                            public DeclHandler<string_type>,
                            public LexicalHandler<string_type>
{
public:
  typedef string_type stringT;
  typedef string_adaptor_type string_adaptorT;
  typedef XMLReaderInterface<stringT> XMLReaderT;
  typedef EntityResolver<stringT> EntityResolverT;
  typedef DTDHandler<stringT> DTDHandlerT;
  typedef ContentHandler<stringT> ContentHandlerT;
  typedef InputSource<stringT> InputSourceT;
  typedef Locator<stringT> LocatorT;
  typedef ErrorHandler<stringT> ErrorHandlerT;
  typedef DeclHandler<stringT> DeclHandlerT;
  typedef LexicalHandler<stringT> LexicalHandlerT;
  typedef typename ErrorHandler<stringT>::SAXParseExceptionT SAXParseExceptionT;


  XMLFilterImpl() : 
    parent_(0)
  { 
    setDefaults();
  } // XMLFilterImpl
  XMLFilterImpl(XMLReaderT& parent) : 
    parent_(&parent) 
  {
    setDefaults();
  } // XMLFilterImpl

  virtual ~XMLFilterImpl() { }

  /////////////////////////////////////////////////
  // XMLFilter implementation
  /**
   * Set the parent reader.
   *
   * <p>This is the {@link XMLReader XMLReader} from which 
   * this filter will obtain its events and to which it will pass its 
   * configuration requests.  The parent may itself be another filter.</p>
   *
   * <p>If there is no parent reader set, any attempt to parse
   * or to set or get a feature or property will fail.</p>
   *
   * @param parent The parent XML reader.
   * @see #getParent
   */
  virtual void setParent(XMLReaderT& parent) { parent_ = &parent; } 
  /**
   * Get the parent reader.
   *
   * @return The parent XML reader, or null if none is set.
   * @see #setParent
   */
  virtual XMLReaderT* getParent() const { return parent_; }

  /////////////////////////////////////////////////
  // XMLReader implementation
  /**
   * Set the state of a feature.
   *
   * <p>This will always fail if the parent is null.</p>
   *
   * @param name The feature name.
   * @param value The requested feature value.
   * @exception SAXNotRecognizedException When the
   *            XMLReader does not recognize the feature name.
   * @exception SAXNotSupportedException When the
   *            XMLReader recognizes the feature name but 
   *            cannot set the requested value.
   * @see XMLReader#setFeature
   */
  virtual void setFeature(const stringT& name, bool value)
  {
  	if(!parent_)
    {
      stringT ex = string_adaptorT::construct_from_utf8("Feature: ");
      string_adaptorT::append(ex, name);
      throw SAXNotRecognizedException(string_adaptorT::asStdString(ex));
    } // if ...

    parent_->setFeature(name, value);
  } // setFeature
  /**
   * Look up the state of a feature.
   *
   * <p>This will always fail if the parent is null.</p>
   *
   * @param name The feature name.
   * @return The current state of the feature.
   * @exception SAXNotRecognizedException When the
   *            XMLReader does not recognize the feature name.
   * @exception SAXNotSupportedException When the
   *            XMLReader recognizes the feature name but 
   *            cannot determine its state at this time.
   * @see XMLReader#getFeature
   */
  virtual bool getFeature(const stringT& name) const
  {
  	if(!parent_)
    {
      stringT ex = string_adaptorT::construct_from_utf8("Feature: ");
      string_adaptorT::append(ex, name);
      throw SAXNotRecognizedException(string_adaptorT::asStdString(ex));
    } // if ...

    return parent_->getFeature(name);
  } // setFeature
  
  /**
   * Set the entity resolver.
   *
   * @param resolver The new entity resolver.
   * @see XMLReader#setEntityResolver
   */
  virtual void setEntityResolver(EntityResolverT& resolver) { entityResolver_ = &resolver; }
  /**
   * Get the current entity resolver.
   *
   * @return The current entity resolver, or null if none was set.
   * @see XMLReader#getEntityResolver
   */
  virtual EntityResolverT* getEntityResolver() const { return entityResolver_ ; }
  /**
   * Set the DTD event handler.
   *
   * @param handler The new DTD handler.
   * @see XMLReader#setDTDHandler
   */
  virtual void setDTDHandler(DTDHandlerT& handler) { dtdHandler_ = &handler; }
  /**
   * Get the current DTD event handler.
   *
   * @return The current DTD handler, or null if none was set.
   * @see XMLReader#getDTDHandler
   */
  virtual DTDHandlerT* getDTDHandler() const { return dtdHandler_; }
  /**
   * Set the content event handler.
   *
   * @param handler The new content handler.
   * @see XMLReader#setContentHandler
   */
  virtual void setContentHandler(ContentHandlerT& handler) { contentHandler_ = &handler; }
  /**
   * Get the content event handler.
   *
   * @return The current content handler, or null if none was set.
   * @see XMLReader#getContentHandler
   */
  virtual ContentHandlerT* getContentHandler() const { return contentHandler_; }
  /**
   * Set the error event handler.
   *
   * @param handler The new error handler.
   * @see XMLReader#setErrorHandler
   */
  virtual void setErrorHandler(ErrorHandlerT& handler) { errorHandler_ = &handler; }
  /**
   * Get the current error event handler.
   *
   * @return The current error handler, or null if none was set.
   * @see XMLReader#getErrorHandler
   */
  virtual ErrorHandlerT* getErrorHandler() const { return errorHandler_; }

  virtual void setDeclHandler(DeclHandlerT& handler) { declHandler_ = &handler; }
  virtual DeclHandlerT* getDeclHandler() const { return declHandler_; }
  virtual void setLexicalHandler(LexicalHandlerT& handler) { lexicalHandler_ = &handler; }
  virtual LexicalHandlerT* getLexicalHandler() const { return lexicalHandler_; }

  /**
   * Parse a document.
   *
   * @param input The input source for the document entity.
   * @see XMLReader#parse(InputSource)
   */
  virtual void parse(InputSourceT& input)
  {
    setupParse();
    parent_->parse(input);
  } // parse

  virtual std::auto_ptr<typename XMLReaderT::PropertyBase> doGetProperty(const stringT& name)
  {
   	if(parent_)
	    return parent_->doGetProperty(name);

    stringT ex = string_adaptorT::construct_from_utf8("Property: ");
    string_adaptorT::append(ex, name);
    throw SAXNotRecognizedException(string_adaptorT::asStdString(ex));
  } // doGetProperty

  virtual void doSetProperty(const stringT& name, typename std::auto_ptr<typename XMLReaderT::PropertyBase> value)
  {
    if(parent_)
    {
      parent_->doSetProperty(name, value);
      return;
    } // if(parent_)

    stringT ex = string_adaptorT::construct_from_utf8("Property: ");
    string_adaptorT::append(ex, name);
    throw SAXNotRecognizedException(string_adaptorT::asStdString(ex));
  } // doSetProperty

public:
  //////////////////////////////////////////////////
  // EntityResolver
  /**
   * Filter an external entity resolution.
   *
   * @param publicId The entity's public identifier, or an empty string.
   * @param systemId The entity's system identifier.
   * @return A new InputSource or a default-constructed
   *         <code>InputSourceT</code> for the default.
   * @see EntityResolver#resolveEntity
   */
  virtual InputSourceT resolveEntity(const stringT& publicId, const stringT& systemId)
  {
    if(entityResolver_)
      return entityResolver_->resolveEntity(publicId, systemId);
    return InputSourceT();
  } // resolveEntity

  //////////////////////////////////////////////////
  // DTDHandler
  /**
   * Filter a notation declaration event.
   *
   * @param name The notation name.
   * @param publicId The notation's public identifier, or an empty string.
   * @param systemId The notation's system identifier, or an empty string.
   * @see DTDHandler#notationDecl
   */
  virtual void notationDecl(const stringT& name,
                            const stringT& publicId,
                            const stringT& systemId)
  {
    dtdHandler_->notationDecl(name, publicId, systemId);
  } // notationDecl

  /**
   * Filter an unparsed entity declaration event.
   *
   * @param name The entity name.
   * @param publicId The entity's public identifier, or an empty string.
   * @param systemId The entity's system identifier, or an empty string.
   * @param notationName The name of the associated notation.
   * @see DTDHandler#unparsedEntityDecl
   */
  virtual void unparsedEntityDecl(const stringT& name,
	                                const stringT& publicId,
                                  const stringT& systemId,
                                  const stringT& notationName)
  {
    dtdHandler_->unparsedEntityDecl(name, publicId, systemId, notationName);
  } // unparsedEntityDecl

  //////////////////////////////////////////////////
  // ContentHandler
  /**
   * Filter a new document locator event.
   *
   * @param locator The document locator.
   * @see ContentHandler#setDocumentLocator
   */
  virtual void setDocumentLocator(const LocatorT& locator) 
  { 
    contentHandler_->setDocumentLocator(locator);
  } // setDocumentLocator

  /**
   * Filter a start document event.
   *
   * @see ContentHandler#startDocument
   */
  virtual void startDocument() 
  { 
    contentHandler_->startDocument();
  } // startDocument

  /**
   * Filter an end document event.
   *
   * @see ContentHandler#endDocument
   */
  virtual void endDocument() 
  { 
    contentHandler_->endDocument();
  } // endDocument

  /**
   * Filter a start Namespace prefix mapping event.
   *
   * @param prefix The Namespace prefix.
   * @param uri The Namespace URI.
   * @see ContentHandler#startPrefixMapping
   */
  virtual void startPrefixMapping(const stringT& prefix, const stringT& uri) 
  { 
    contentHandler_->startPrefixMapping(prefix, uri);
  } // startPrefixMapping

  /**
   * Filter an end Namespace prefix mapping event.
   *
   * @param prefix The Namespace prefix.
   * @see ContentHandler#endPrefixMapping
   */
  virtual void endPrefixMapping(const stringT& prefix) 
  { 
    contentHandler_->endPrefixMapping(prefix);
  } // endPrefixMapping

  /**
   * Filter a start element event.
   *
   * @param namespaceURI The element's Namespace URI, or the empty string.
   * @param localName The element's local name, or the empty string.
   * @param qName The element's qualified (prefixed) name, or the empty
   *        string.
   * @param atts The element's attributes.
   * @see ContentHandler#startElement
   */
  virtual void startElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName, const typename ContentHandlerT::AttributesT& atts) 
  { 
    contentHandler_->startElement(namespaceURI, localName, qName, atts);
  } // startElement

  /**
   * Filter an end element event.
   *
   * @param namespaceURI The element's Namespace URI, or the empty string.
   * @param localName The element's local name, or the empty string.
   * @param qName The element's qualified (prefixed) name, or the empty
   *        string.
   * @see ContentHandler#endElement
   */
  virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                          const stringT& qName) 
  { 
    contentHandler_->endElement(namespaceURI, localName, qName);
  }  // endElement

  /**
   * Filter a character data event.
   *
   * @param ch The characters.
   * @see ContentHandler#characters
   */
  virtual void characters(const stringT& ch) 
  { 
    contentHandler_->characters(ch);
  } // characters

  /**
   * Filter an ignorable whitespace event.
   *
   * @param ch The whitespace
   * @see ContentHandler#ignorableWhitespace
   */
  virtual void ignorableWhitespace(const stringT& ch) 
  { 
    contentHandler_->ignorableWhitespace(ch);
  } // ignorableWhitespace

  /**
   * Filter a processing instruction event.
   *
   * @param target The processing instruction target.
   * @param data The text following the target.
   * @see ContentHandler#processingInstruction
   */
  virtual void processingInstruction(const stringT& target, const stringT& data) 
  { 
    contentHandler_->processingInstruction(target, data);
  } // processingInstruction

  /**
   * Filter a skipped entity event.
   *
   * @param name The name of the skipped entity.
   * @see ContentHandler#skippedEntity
   */
  virtual void skippedEntity(const stringT& name) 
  { 
    contentHandler_->skippedEntity(name);
  } // skippedEntity

  //////////////////////////////////////////////////
  // ErrorHandler
  /**
   * Filter a warning event.
   *
   * @param exception The warning as an exception.
   * @see ErrorHandler#warning
   */
  virtual void warning(const SAXParseExceptionT& exception) 
  { 
    errorHandler_->warning(exception);
  } // warning

  /**
   * Filter an error event.
   *
   * @param exception The error as an exception.
   * @see ErrorHandler#error
   */
  virtual void error(const SAXParseExceptionT& exception) 
  { 
    errorHandler_->error(exception);
  } // error

  /**
   * Filter a fatal error event.
   *
   * @param exception The error as an exception.
   * @see ErrorHandler#fatalError
   */
  virtual void fatalError(const SAXParseExceptionT& exception) 
  { 
    errorHandler_->fatalError(exception);
  } // fatalError

  ////////////////////////////////////////////////////////////
  // DeclHandler
  /**
   * Filter an element type declaration.
   */
  virtual void elementDecl(const stringT& name, const stringT& model) 
  { 
    declHandler_->elementDecl(name, model);
  } // elementDecl

  /**
   * Filter an attribute type declaration.
   */
  virtual void attributeDecl(const stringT& elementName,
                             const stringT& attributeName,
                             const stringT& type,
                             const stringT& valueDefault,
                             const stringT& value) 
  { 
    declHandler_->attributeDecl(elementName, attributeName, type, valueDefault, value);
  } // attributeDecl

  /**
   * Filter an internal entity declaration.
   */
  virtual void internalEntityDecl(const stringT& name, const stringT& value) 
  { 
    declHandler_->internalEntityDecl(name, value);
  } // internalEntityDecl

  /**
   * Filter a parsed external entity declaration.
   */
  virtual void externalEntityDecl(const stringT& name, 
                                  const stringT& publicId,
                                  const stringT& systemId) 
  { 
    declHandler_->externalEntityDecl(name, publicId, systemId);
  } // externalEntityDecl

  //////////////////////////////////////////////////////////
  // LexicalHandler
  /**
   * Filter the start of DTD declarations, if any.
   */
  virtual void startDTD(const stringT& name,
                        const stringT& publicId,
                        const stringT& systemId) 
  { 
    lexicalHandler_->startDTD(name, publicId, systemId);
  } // startDTD

  /**
   * Filter the end of DTD declarations.
   */
  virtual void endDTD() 
  { 
    lexicalHandler_->endDTD();
  } // endDTD

  /**
   * Filter the beginning of some internal and external XML entities.
   */
  virtual void startEntity(const stringT& name) 
  { 
    lexicalHandler_->startEntity(name);
  } // startEntity

  /**
   * Filter the end of an entity.
   */
  virtual void endEntity(const stringT& name) 
  { 
    lexicalHandler_->endEntity(name);
  } // endEntity

  /**
   * Filter the start of a CDATA section.
   */
  virtual void startCDATA() 
  { 
    lexicalHandler_->startCDATA();
  } // startCDATA

  /**
   * Filter the end of a CDATA section.
   */
  virtual void endCDATA() 
  { 
    lexicalHandler_->endCDATA();
  } // endCDATA

  /**
   * Filter an XML comment anywhere in the document.
   */
  virtual void comment(const stringT& text) 
  { 
    lexicalHandler_->comment(text);
  } // comment

private:
  void setDefaults() 
  {
    setEntityResolver(defaultHandler_);
    setDTDHandler(defaultHandler_);
    setContentHandler(defaultHandler_);
    setErrorHandler(defaultHandler_);
    setDeclHandler(defaultHandler_);
    setLexicalHandler(defaultHandler_);
  } // setDefaults

  void setupParse()
  {
    parent_->setEntityResolver(*this);
    parent_->setDTDHandler(*this);
    parent_->setContentHandler(*this);
    parent_->setErrorHandler(*this);
    parent_->setDeclHandler(*this);
    parent_->setLexicalHandler(*this);
  } // setupParse

  XMLFilterImpl(const XMLFilterImpl&);
  XMLFilterImpl& operator=(const XMLFilterImpl&); // no impl
  bool operator==(const XMLFilterImpl&); // no impl

  XMLReaderT* parent_;
  EntityResolverT* entityResolver_;
  DTDHandlerT* dtdHandler_;
  ContentHandlerT* contentHandler_;
  ErrorHandlerT* errorHandler_;
  DeclHandlerT* declHandler_;
  LexicalHandlerT* lexicalHandler_;
  DefaultHandler<stringT> defaultHandler_;
}; // class XMLFilter

} // namespace SAX
} // namespace Arabica

#endif
// end of file
