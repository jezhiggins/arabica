#ifndef XMLFilterImplH
#define XMLFilterImplH

// XMLFilter.h
// $Id$

#include <string>
#include <SAX/XMLFilter.h>
#include <SAX/helpers/DefaultHandler.h>
#include <SAX/SAXNotRecognizedException.h>

namespace SAX
{

/**
 * Base class for deriving an XML filter.
 *
 * <p>This class is designed to sit between an {@link basic_XMLReader
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
 * @see basic_XMLFilter
 * @see basic_XMLReader
 * @see basic_EntityResolver
 * @see basic_DTDHandler
 * @see basic_ContentHandler
 * @see basic_ErrorHandler
 */
template<class string_type>
class basic_XMLFilterImpl : public basic_XMLFilter<string_type>,
          public basic_EntityResolver<string_type>, 
					public basic_DTDHandler<string_type>,
					public basic_ContentHandler<string_type>, 
					public ErrorHandler
{
public:
  typedef string_type stringT;
  typedef basic_XMLReader<stringT> XMLReaderT;
  typedef basic_EntityResolver<stringT> EntityResolverT;
  typedef basic_DTDHandler<stringT> DTDHandlerT;
  typedef basic_ContentHandler<stringT> ContentHandlerT;
  typedef basic_InputSource<stringT> InputSourceT;
  typedef basic_Locator<stringT> LocatorT;

  basic_XMLFilterImpl() : 
    parent_(0)
  { 
    setDefaults();
  } // basic_XMLFilterImpl
  basic_XMLFilterImpl(XMLReaderT& parent) : 
    parent_(&parent) 
  {
    setDefaults();
  } // basic_XMLFilterImpl

  virtual ~basic_XMLFilterImpl() { }

  /////////////////////////////////////////////////
  // XMLFilter implementation
  /**
   * Set the parent reader.
   *
   * <p>This is the {@link basic_XMLReader XMLReader} from which 
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
   * @param state The requested feature state.
   * @exception SAXNotRecognizedException When the
   *            XMLReader does not recognize the feature name.
   * @exception SAXNotSupportedException When the
   *            XMLReader recognizes the feature name but 
   *            cannot set the requested value.
   * @see basic_XMLReader#setFeature
   */
  virtual void setFeature(const stringT& name, bool value)
  {
  	if(!parent_)
      throw SAXNotRecognizedException("Feature: " + name);

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
   * @see basic_XMLReader#getFeature
   */
  virtual bool getFeature(const stringT& name) const
  {
  	if(!parent_)
      throw SAXNotRecognizedException("Feature: " + name);

    return parent_->getFeature(name);
  } // setFeature
  
  /**
   * Set the entity resolver.
   *
   * @param resolver The new entity resolver.
   * @see basic_XMLReader#setEntityResolver
   */
  virtual void setEntityResolver(EntityResolverT& resolver) { entityResolver_ = &resolver; }
  /**
   * Get the current entity resolver.
   *
   * @return The current entity resolver, or null if none was set.
   * @see basic_XMLReader#getEntityResolver
   */
  virtual EntityResolverT* getEntityResolver() const { return entityResolver_ ; }
  /**
   * Set the DTD event handler.
   *
   * @param resolver The new DTD handler.
   * @see basic_XMLReader#setDTDHandler
   */
  virtual void setDTDHandler(DTDHandlerT& handler) { dtdHandler_ = &handler; }
  /**
   * Get the current DTD event handler.
   *
   * @return The current DTD handler, or null if none was set.
   * @see basic_XMLReader#getDTDHandler
   */
  virtual DTDHandler* getDTDHandler() const { return dtdHandler_; }
  /**
   * Set the content event handler.
   *
   * @param resolver The new content handler.
   * @see basic_XMLReader#setContentHandler
   */
  virtual void setContentHandler(ContentHandler& handler) { contentHandler_ = &handler; }
  /**
   * Get the content event handler.
   *
   * @return The current content handler, or null if none was set.
   * @see basic_XMLReader#getContentHandler
   */
  virtual ContentHandlerT* getContentHandler() const { return contentHandler_; }
  /**
   * Set the error event handler.
   *
   * @param handle The new error handler.
   * @see basic_XMLReader#setErrorHandler
   */
  virtual void setErrorHandler(ErrorHandler& handler) { errorHandler_ = &handler; }
  /**
   * Get the current error event handler.
   *
   * @return The current error handler, or null if none was set.
   * @see basic_XMLReader#getErrorHandler
   */
  virtual ErrorHandler* getErrorHandler() const { return errorHandler_; }

  /**
   * Parse a document.
   *
   * @param input The input source for the document entity.
   * @see basic_XMLReader#parse(basic_InputSource)
   */
  virtual void parse(InputSourceT& input)
  {
    setupParse();
    parent_->parse(input);
  } // parse

  virtual std::auto_ptr<PropertyBase> doGetProperty(const stringT& name)
  {
   	if(parent_)
	    return parent_->doGetProperty(name);

    throw new SAXNotRecognizedException("Property: " + name);
  } // doGetProperty

  virtual void doSetProperty(const stringT& name, std::auto_ptr<PropertyBase> value)
  {
    if(parent_)
    {
      parent_->doSetProperty(name, value);
      return;
    } // if(parent_)

    throw new SAXNotRecognizedException("Property: " + name);
  } // doSetProperty

public:
  //////////////////////////////////////////////////
  // EntityResolver
  /**
   * Filter an external entity resolution.
   *
   * @param publicId The entity's public identifier, or null.
   * @param systemId The entity's system identifier.
   * @return A new InputSource or null for the default.
   * @see basic_EntityResolver#resolveEntity
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
   * @param publicId The notation's public identifier, or null.
   * @param systemId The notation's system identifier, or null.
   * @see basic_DTDHandler#notationDecl
   */
  virtual void notationDecl(const stringT& name,
                            const stringT& publicId,
                            const stringT& systemId)
  {
    if(dtdHandler_)
      dtdHandler_->notationDecl(name, publicId, systemId);
  } // notationDecl

  /**
   * Filter an unparsed entity declaration event.
   *
   * @param name The entity name.
   * @param publicId The entity's public identifier, or null.
   * @param systemId The entity's system identifier, or null.
   * @param notationName The name of the associated notation.
   * @see basic_DTDHandler#unparsedEntityDecl
   */
  virtual void unparsedEntityDecl(const stringT& name,
	                                const stringT& publicId,
                                  const stringT& systemId,
                                  const stringT& notationName)
  {
    if(dtdHandler_)
      dtdHandler_->unparsedEntityDecl(name, publicId, systemId, notationName);
  } // unparsedEntityDecl

  //////////////////////////////////////////////////
  // ContentHandler
  /**
   * Filter a new document locator event.
   *
   * @param locator The document locator.
   * @see basic_ContentHandler#setDocumentLocator
   */
  virtual void setDocumentLocator(const LocatorT& locator) 
  { 
    locator_ = &locator;
    if(contentHandler_)
      contentHandler_->setDocumentLocator(locator);
  } // setDocumentLocator

  /**
   * Filter a start document event.
   *
   * @see basic_ContentHandler#startDocument
   */
  virtual void startDocument() 
  { 
    if(contentHandler_)
      contentHandler_->startDocument();
  } // startDocument

  /**
   * Filter an end document event.
   *
   * @see basic_ContentHandler#endDocument
   */
  virtual void endDocument() 
  { 
    if(contentHandler_)
      contentHandler_->endDocument();
  } // endDocument

  /**
   * Filter a start Namespace prefix mapping event.
   *
   * @param prefix The Namespace prefix.
   * @param uri The Namespace URI.
   * @see basic_ContentHandler#startPrefixMapping
   */
  virtual void startPrefixMapping(const stringT& prefix, const stringT& uri) 
  { 
    if(contentHandler_)
      contentHandler_->startPrefixMapping(prefix, uri);
  } // startPrefixMapping

  /**
   * Filter an end Namespace prefix mapping event.
   *
   * @param prefix The Namespace prefix.
   * @see basic_ContentHandler#endPrefixMapping
   */
  virtual void endPrefixMapping(const stringT& prefix) 
  { 
    if(contentHandler_)
      contentHandler_->endPrefixMapping(prefix);
  } // endPrefixMapping

  /**
   * Filter a start element event.
   *
   * @param uri The element's Namespace URI, or the empty string.
   * @param localName The element's local name, or the empty string.
   * @param qName The element's qualified (prefixed) name, or the empty
   *        string.
   * @param atts The element's attributes.
   * @see basic_ContentHandler#startElement
   */
  virtual void startElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName, const AttributesT& atts) 
  { 
    if(contentHandler_)
      contentHandler_->startElement(namespaceURI, localName, qName, atts);
  } // startElement

  /**
   * Filter an end element event.
   *
   * @param uri The element's Namespace URI, or the empty string.
   * @param localName The element's local name, or the empty string.
   * @param qName The element's qualified (prefixed) name, or the empty
   *        string.
   * @see basic_ContentHandler#endElement
   */
  virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                          const stringT& qName) 
  { 
    if(contentHandler_)
      contentHandler_->endElement(namespaceURI, localName, qName);
  }  // endElement

  /**
   * Filter a character data event.
   *
   * @param ch The characters.
   * @see basic_ContentHandler#characters
   */
  virtual void characters(const stringT& ch) 
  { 
    if(contentHandler_)
      contentHandler_->characters(ch);
  } // characters

  /**
   * Filter an ignorable whitespace event.
   *
   * @param ch The whitespace
   * @see basic_ContentHandler#ignorableWhitespace
   */
  virtual void ignorableWhitespace(const stringT& ch) 
  { 
    if(contentHandler_)
      contentHandler_->ignorableWhitespace(ch);
  } // ignorableWhitespace

  /**
   * Filter a processing instruction event.
   *
   * @param target The processing instruction target.
   * @param data The text following the target.
   * @see basic_ContentHandler#processingInstruction
   */
  virtual void processingInstruction(const stringT& target, const stringT& data) 
  { 
    if(contentHandler_)
      contentHandler_->processingInstruction(target, data);
  } // processingInstruction

  /**
   * Filter a skipped entity event.
   *
   * @param name The name of the skipped entity.
   * @see basic_ContentHandler#skippedEntity
   */
  virtual void skippedEntity(const stringT& name) 
  { 
    if(contentHandler_)
      contentHandler_->skippedEntity(name);
  } // skippedEntity

  //////////////////////////////////////////////////
  // ErrorHandler
  /**
   * Filter a warning event.
   *
   * @param e The warning as an exception.
   * @see basic_ErrorHandler#warning
   */
  virtual void warning(const SAXException& exception) 
  { 
    if(errorHandler_)
      errorHandler_->warning(exception);
  } // warning

  /**
   * Filter an error event.
   *
   * @param e The error as an exception.
   * @see basic_ErrorHandler#error
   */
  virtual void error(const SAXException& exception) 
  { 
    if(errorHandler_)
      errorHandler_->error(exception);
  } // error

  /**
   * Filter a fatal error event.
   *
   * @param e The error as an exception.
   * @see basic_ErrorHandler#fatalError
   */
  virtual void fatalError(const SAXException& exception) 
  { 
    if(errorHandler_)
      errorHandler_->fatalError(exception);
  } // fatalError


private:
  void setDefaults() 
  {
    setEntityResolver(defaultHandler_);
    setDTDHandler(defaultHandler_);
    setContentHandler(defaultHandler_);
    setErrorHandler(defaultHandler_);
  } // setDefaults

  void setupParse()
  {
    parent_->setEntityResolver(*this);
    parent_->setDTDHandler(*this);
    parent_->setContentHandler(*this);
    parent_->setErrorHandler(*this);
  } // setupParse

  basic_XMLFilterImpl(const basic_XMLFilterImpl&);
  basic_XMLFilterImpl& operator=(const basic_XMLFilterImpl&); // no impl
  bool operator==(const basic_XMLFilterImpl&); // no impl

  XMLReaderT* parent_;
  EntityResolverT* entityResolver_;
  DTDHandlerT* dtdHandler_;
  ContentHandlerT* contentHandler_;
  ErrorHandler* errorHandler_;
  const LocatorT* locator_;
  basic_DefaultHandler<stringT> defaultHandler_;
}; // class basic_XMLFilter

typedef basic_XMLFilterImpl<std::string> XMLFilterImpl;
typedef basic_XMLFilterImpl<std::wstring> wXMLFilterImpl;

}; // namespace SAX

#endif
// end of file
