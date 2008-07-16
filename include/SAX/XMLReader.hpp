#ifndef ARABICA_XML_READER_H
#define ARABICA_XML_READER_H

// XMLReader.h
// $Id$

#include <string>
#include <memory>

#include <SAX/ArabicaConfig.hpp>

#include <SAX/ContentHandler.hpp>
#include <SAX/EntityResolver.hpp>
#include <SAX/DTDHandler.hpp>
#include <SAX/ErrorHandler.hpp>
#include <SAX/InputSource.hpp>
#include <SAX/ext/LexicalHandler.hpp>
#include <SAX/ext/DeclHandler.hpp>
#include <SAX/SAXNotSupportedException.hpp>

#include <Arabica/StringAdaptor.hpp>
#include <Arabica/getparam.hpp>

namespace Arabica
{
namespace SAX
{

/**
 * Interface for reading an XML document using callbacks.
 *
 * <p>XMLReader is the interface that an XML parser's SAX2 driver must
 * implement.  This interface allows an application to set and
 * query features and properties in the parser, to register
 * event handlers for document processing, and to initiate
 * a document parse.</p>
 *
 * <p>All SAX interfaces are assumed to be synchronous: the
 * {@link #parse parse} methods must not return until parsing
 * is complete, and readers must wait for an event-handler callback
 * to return before reporting the next event.</p>
 *
 * <p>This interface replaces the (now deprecated) SAX 1.0 {@link
 * Parser Parser} interface.  The XMLReader interface
 * contains two important enhancements over the old Parser
 * interface:</p>
 *
 * <ol>
 * <li>it adds a standard way to query and set features and 
 *  properties; and</li>
 * <li>it adds Namespace support, which is required for many
 *  higher-level XML standards.</li>
 * </ol>
 *
 * <p>There are adapters available to convert a SAX1 Parser to
 * a SAX2 XMLReader and vice-versa.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins, 
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see XMLFilter
 * @see helpers.ParserAdapter
 * @see helpers.XMLReaderAdapter 
 */
class XMLReaderInterface_tag { };

template<class string_type, class string_adaptor_type>
class XMLReaderInterface : public XMLReaderInterface_tag 
{
public:
  typedef string_adaptor_type string_adaptor;
  typedef EntityResolver<string_type, string_adaptor> EntityResolverT;
  typedef DTDHandler<string_type, string_adaptor> DTDHandlerT;
  typedef ContentHandler<string_type, string_adaptor> ContentHandlerT;
  typedef InputSource<string_type, string_adaptor> InputSourceT;
  typedef ErrorHandler<string_type, string_adaptor> ErrorHandlerT;
  typedef DeclHandler<string_type, string_adaptor> DeclHandlerT;
  typedef LexicalHandler<string_type, string_adaptor> LexicalHandlerT;

  virtual ~XMLReaderInterface() { }

  /////////////////////////////////////////////////
  // Configuration
  /**
   * Look up the value of a feature.
   *
   * <p>The feature name is any fully-qualified URI.  It is
   * possible for an XMLReader to recognize a feature name but
   * to be unable to return its value; this is especially true
   * in the case of an adapter for a SAX1 Parser, which has
   * no way of knowing whether the underlying parser is
   * performing validation or expanding external entities.</p>
   *
   * <p>All XMLReaders are required to recognize the
   * http://xml.org/sax/features/namespaces and the
   * http://xml.org/sax/features/namespace-prefixes feature names.</p>
   *
   * <p>Some feature values may be available only in specific
   * contexts, such as before, during, or after a parse.</p>
   *
   * <p>Typical usage is something like this:</p>
   *
   * <pre>
   * XMLReader r = new MySAXDriver();
   *
   *                         // try to activate validation
   * try {
   *   r.setFeature("http://xml.org/sax/features/validation", true);
   * } catch (SAXException e) {
   *   System.err.println("Cannot activate validation."); 
   * }
   *
   *                         // register event handlers
   * r.setContentHandler(new MyContentHandler());
   * r.setErrorHandler(new MyErrorHandler());
   *
   *                         // parse the first document
   * try {
   *   r.parse("http://www.foo.com/mydoc.xml");
   * } catch (IOException e) {
   *   System.err.println("I/O exception reading XML document");
   * } catch (SAXException e) {
   *   System.err.println("XML exception reading document.");
   * }
   * </pre>
   *
   * <p>Implementors are free (and encouraged) to invent their own features,
   * using names built on their own URIs.</p>
   *
   * @param name The feature name, which is a fully-qualified URI.
   * @return The current state of the feature (true or false).
   * @see #setFeature
   */
  virtual bool getFeature(const string_type& name) const = 0;
  /**
   * Set the state of a feature.
   *
   * <p>The feature name is any fully-qualified URI.  It is
   * possible for an XMLReader to recognize a feature name but
   * to be unable to set its value; this is especially true
   * in the case of an adapter for a SAX1 {@link Parser Parser},
   * which has no way of affecting whether the underlying parser is
   * validating, for example.</p>
   *
   * <p>All XMLReaders are required to support setting
   * http://xml.org/sax/features/namespaces to true and
   * http://xml.org/sax/features/namespace-prefixes to false.</p>
   *
   * <p>Some feature values may be immutable or mutable only 
   * in specific contexts, such as before, during, or after 
   * a parse.</p>
   *
   * @param name The feature name, which is a fully-qualified URI.
   * @param value The requested value of the feature (true or false).
   * @exception SAXNotRecognizedException When the
   *            XMLReader does not recognize the feature name.
   * @exception SAXNotSupportedException When the
   *            XMLReader recognizes the feature name but 
   *            cannot set the requested value.
   * @see #getFeature
   * @see FeatureNames
   * @see http://www.saxproject.org/apidoc/org/xml/sax/package-summary.html#package_description for a list of SAX2 features.
   */
  virtual void setFeature(const string_type& name, bool value) = 0;
  
  /////////////////////////////////////////////////
  // Event Handlers
  /**
   * Allow an application to register an entity resolver.
   *
   * <p>If the application does not register an entity resolver,
   * the XMLReader will perform its own default resolution.</p>
   *
   * <p>Applications may register a new or different resolver in the
   * middle of a parse, and the SAX parser must begin using the new
   * resolver immediately.</p>
   *
   * @param resolver The entity resolver.
   * @see #getEntityResolver
   */
  virtual void setEntityResolver(EntityResolverT& resolver) = 0; 
  /**
   * Return the current entity resolver.
   *
   * @return The current entity resolver, or null if none
   *         has been registered.
   * @see #setEntityResolver
   */
  virtual EntityResolverT* getEntityResolver() const = 0;

  /**
   * Allow an application to register a DTD event handler.
   *
   * <p>If the application does not register a DTD handler, all DTD
   * events reported by the SAX parser will be silently ignored.</p>
   *
   * <p>Applications may register a new or different handler in the
   * middle of a parse, and the SAX parser must begin using the new
   * handler immediately.</p>
   *
   * @param handler The DTD handler.
   * @see #getDTDHandler
   */
  virtual void setDTDHandler(DTDHandlerT& handler) = 0;
  /**
   * Return the current DTD handler.
   *
   * @return The current DTD handler, or null if none
   *         has been registered.
   * @see #setDTDHandler
   */
  virtual DTDHandlerT* getDTDHandler() const = 0;
  
  /**
   * Allow an application to register a content event handler.
   *
   * <p>If the application does not register a content handler, all
   * content events reported by the SAX parser will be silently
   * ignored.</p>
   *
   * <p>Applications may register a new or different handler in the
   * middle of a parse, and the SAX parser must begin using the new
   * handler immediately.</p>
   *
   * @param handler The content handler.
   * @see #getContentHandler
   */
  virtual void setContentHandler(ContentHandlerT& handler) = 0;
  /**
   * Return the current content handler.
   *
   * @return The current content handler, or null if none
   *         has been registered.
   * @see #setContentHandler
   */
  virtual ContentHandlerT* getContentHandler() const = 0;
  
  /**
   * Allow an application to register an error event handler.
   *
   * <p>If the application does not register an error handler, all
   * error events reported by the SAX parser will be silently
   * ignored; however, normal processing may not continue.  It is
   * highly recommended that all SAX applications implement an
   * error handler to avoid unexpected bugs.</p>
   *
   * <p>Applications may register a new or different handler in the
   * middle of a parse, and the SAX parser must begin using the new
   * handler immediately.</p>
   *
   * @param handler The error handler.
   * @see #getErrorHandler
   */
  virtual void setErrorHandler(ErrorHandlerT& handler) = 0;
  /**
   * Return the current error handler.
   *
   * @return The current error handler, or null if none
   *         has been registered.
   * @see #setErrorHandler
   */
  virtual ErrorHandlerT* getErrorHandler() const = 0;

  virtual void setDeclHandler(DeclHandlerT& handler) = 0;
  /**
   * Return the current decl handler.
   *
   * @return The current decl handler, or 0 if none has been registered
   * @see #setDeclHandler
   */
  virtual DeclHandlerT* getDeclHandler() const = 0;

  virtual void setLexicalHandler(LexicalHandlerT& handler) = 0;
  /**
   * Return the current lexical handler.
   *
   * @return The current lexical handler, or 0 if none has been registered
   * @see #setLexicalHandler
   */
  virtual LexicalHandlerT* getLexicalHandler() const = 0;

  //////////////////////////////////////////////////
  // Parsing
  /**
   * Parse an XML document from a system identifier (URI).
   *
   * <p>This method is a shortcut for the common case of reading a
   * document from a system identifier.  It is the exact
   * equivalent of the following:</p>
   *
   * <pre>
   * InputSource is(systemId);
   * parse(is);
   * </pre>
   *
   * <p>If the system identifier is a URL, it must be fully resolved
   * by the application before it is passed to the parser.</p>
   *
   * @param systemId The system identifier (URI).
   * @see #parse(InputSource&)
   */
  void parse(const string_type& systemId)
  {
    InputSourceT is(systemId);
    parse(is);
  } // parser
  /**
   * Parse an XML document.
   *
   * <p>The application can use this method to instruct the XML
   * reader to begin parsing an XML document from any valid input
   * source (a character stream, a byte stream, or a URI).</p>
   *
   * <p>Applications may not invoke this method while a parse is in
   * progress (they should create a new XMLReader instead for each
   * nested XML document).  Once a parse is complete, an
   * application may reuse the same XMLReader object, possibly with a
   * different input source.</p>
   *
   * <p>During the parse, the XMLReader will provide information
   * about the XML document through the registered event
   * handlers.</p>
   *
   * <p>This method is synchronous: it will not return until parsing
   * has ended.  If a client application wants to terminate 
   * parsing early, it should throw an exception.</p>
   *
   * @param input The input source for the top-level of the
   *        XML document.
   * @see InputSource
   * @see #parse(const string_type&)
   * @see #setEntityResolver
   * @see #setDTDHandler
   * @see #setContentHandler
   * @see #setErrorHandler 
   */
  virtual void parse(InputSourceT& input) = 0;

  ////////////////////////////////////////////////////
  // property implementation
protected:
  class PropertyBase 
  {
  public:
    virtual ~PropertyBase() { }
  }; // PropertyBase

  template<typename propertyTypeT>
  class Property : public PropertyBase
  {
  public:
    Property(propertyTypeT wrappee) : wrappee_(wrappee) { }

    propertyTypeT get() { return wrappee_; }

  private:
    propertyTypeT wrappee_;
  }; // class Property

public:
  virtual std::auto_ptr<PropertyBase> doGetProperty(const string_type& name) = 0;
  virtual void doSetProperty(const string_type& name, std::auto_ptr<PropertyBase> value) = 0;

  /**
   * Look up the value of a property.
   *
   * <p>The property name is any fully-qualified URI.  It is
   * possible for an XMLReader to recognize a property name but
   * to be unable to return its state; this is especially true
   * in the case of an adapter for a SAX1 {@link Parser
   * Parser}.</p>
   *
   * <p>XMLReaders are not required to recognize any specific
   * property names, though an initial core set is documented for
   * SAX2.</p>
   *
   * <p>Some property values may be available only in specific
   * contexts, such as before, during, or after a parse.</p>
   *
   * <p>Implementors are free (and encouraged) to invent their own properties,
   * using names built on their own URIs.</p>
   *
   * @param name The property name, which is a fully-qualified URI.
   * @return The current value of the property.
   * @exception SAXNotRecognizedException When the
   *            XMLReader does not recognize the property name.
   * @exception SAXNotSupportedException When the
   *            XMLReader recognizes the property name but 
   *            cannot determine its value at this time.
   * @see #setProperty
   */
  template<typename propertyTypeT>
  propertyTypeT& getProperty(const string_type& name) const
  {
    std::auto_ptr<PropertyBase> pb = doGetProperty(name);
    Property<propertyTypeT&>* prop = dynamic_cast<Property<propertyTypeT&>* >(pb.get());

    if(!prop)
      throw SAX::SAXNotSupportedException("Property " + name + " is wrong type.");

    return prop->get();
  } // getProperty

  /**
   * Set the value of a property.
   *
   * <p>The property name is any fully-qualified URI.  It is
   * possible for an XMLReader to recognize a property name but
   * to be unable to set its value; this is especially true
   * in the case of an adapter for a SAX1 {@link Parser
   * Parser}.</p>
   *
   * <p>XMLReaders are not required to recognize setting
   * any specific property names, though a core set is provided with 
   * SAX2.</p>
   *
   * <p>Some property values may be immutable or mutable only 
   * in specific contexts, such as before, during, or after 
   * a parse.</p>
   *
   * <p>This method is also the standard mechanism for setting
   * extended handlers.</p>
   *
   * @param name The property name, which is a fully-qualified URI.
   * @param value The requested value for the property.
   * @exception SAXNotRecognizedException When the
   *            XMLReader does not recognize the property name.
   * @exception SAXNotSupportedException When the
   *            XMLReader recognizes the property name but 
   *            cannot set the requested value.
   */
  template<typename propertyTypeT>
  void setProperty(const string_type& name, propertyTypeT& value)
  {
    Property<propertyTypeT&>* prop = new Property<propertyTypeT&>(value);
    doSetProperty(name, std::auto_ptr<PropertyBase>(prop));
  } // setProperty
}; // class XMLReaderInterface

} // namespace SAX
} // namespace Arabica

/* Included to ensure that #include<SAX/XMLReader.hpp> defines a class called
 * XMLReader.
 */
#include <SAX/ParserConfig.hpp>

#endif
// end of file
