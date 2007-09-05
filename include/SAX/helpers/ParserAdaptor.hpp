#ifndef ARABICA_PARSER_ADAPTOR_H
#define ARABICA_PARSER_ADAPTOR_H

// ParserAdaptor
// Adapts a SAX1 Parser to a SAX2 XMLReader.
// $Id$

#include <SAX/ArabicaConfig.hpp>
#include <SAX/XMLReader.hpp>
#include <SAX/Parser.hpp>
#include <SAX/DocumentHandler.hpp>
#include <SAX/helpers/NamespaceSupport.hpp>
#include <SAX/AttributeList.hpp>
#include <SAX/helpers/AttributesImpl.hpp>
#include <SAX/SAXParseException.hpp>
#include <SAX/SAXNotSupportedException.hpp>
#include <SAX/SAXNotRecognizedException.hpp>
#include <sstream>

namespace Arabica
{
namespace SAX
{

/**
 * Adapt a SAX1 Parser as a SAX2 XMLReader.
 *
 * <p>This class wraps a SAX1 {@link Parser Parser}
 * and makes it act as a SAX2 {@link XMLReader XMLReader},
 * with feature, property, and Namespace support.  Note
 * that it is not possible to report {@link ContentHandler#skippedEntity
 * skippedEntity} events, since SAX1 does not make that information available.</p>
 *
 * <p>This adapter does not test for duplicate Namespace-qualified
 * attribute names.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see XMLReader
 * @see Parser
 */
template<class string_type, class string_adaptor_type>
class ParserAdaptor : public XMLReaderInterface<string_type, string_adaptor, int>, 
                            public DocumentHandler<string_type, string_adaptor>
{
public:
  typedef Parser<string_type, string_adaptor> ParserT;
  typedef EntityResolver<string_type, string_adaptor> EntityResolverT;
  typedef DTDHandler<string_type, string_adaptor> DTDHandlerT;
  typedef DocumentHandler<string_type, string_adaptor> DocumentHandlerT;
  typedef ContentHandler<string_type, string_adaptor> ContentHandlerT;
  typedef InputSource<string_type, string_adaptor> InputSourceT;
  typedef Locator<string_type, string_adaptor> LocatorT;
  typedef SAXParseException<string_type, string_adaptor> SAXParseExceptionT;
  typedef AttributeList<string_type, string_adaptor> AttributeListT;

  ParserAdaptor(ParserT& parser) :
    parser_(parser),
    parsing_(false),
    locator_(0),
    namespaces_(true),
    prefixes_(false),
    entityResolver_(0),
    dtdHandler_(0),
    contentHandler_(0),
    errorHandler_(0)
  {
  } // ParserAdaptor

  ////////////////////////////////
  // implement XMLReader
  /**
   * Set a feature for the parser.
   *
   * <p>The only features supported are namespaces and 
   * namespace-prefixes.</p>
   *
   * @param name The feature name, as a complete URI.
   * @param value The requested feature value.
   * @exception SAXNotRecognizedException If the feature
   *            name is not known.
   * @exception SAXNotSupportedException If the feature
   *            state is not supported.
   * @see XMLReader#setFeature
   */
  virtual void setFeature(const string_type& name, bool value)
  {
    if(name == NAMESPACES)
    {
      checkNotParsing("feature", name);
      namespaces_ = value;
      if(!namespaces_ && !prefixes_)
        prefixes_ = true;
    }
    else if(name == NAMESPACE_PREFIXES)
    {
      checkNotParsing("feature", name);
      prefixes_ = value;
      if(!prefixes_ && !namespaces_)
        namespaces_ = true;
    }
    else if(name == VALIDATION ||
            name == EXTERNAL_GENERAL ||
            name == EXTERNAL_PARAMETER)
    {
      throw SAXNotSupportedException("Feature not supported " + makeString(name));
    }
    else
    {
      throw SAXNotRecognizedException("Feature not recognized " + makeString(name));
    }
  } // setFeature

  /**
   * Check a parser feature.
   *
   * <p>The only features supported are namespaces and 
   * namespace-prefixes.</p>
   *
   * @param name The feature name, as a complete URI.
   * @return The current feature state.
   * @exception SAXNotRecognizedException If the feature
   *            name is not known.
   * @exception SAXNotSupportedException If querying the
   *            feature state is not supported.
   * @see XMLReader#setFeature
   */
  virtual bool getFeature(const string_type& name) const
  {
    if(name == NAMESPACES)
    {
      return namespaces_;
    }
    else if(name == NAMESPACE_PREFIXES)
    {
      return prefixes_;
    }
    else if(name == VALIDATION ||
            name == EXTERNAL_GENERAL ||
            name == EXTERNAL_PARAMETER)
    {
      throw SAXNotSupportedException("Feature not supported " + makeString(name));
    }
    else
    {
      throw SAXNotRecognizedException("Feature not recognized " + makeString(name));
    }
  } // getFeature

protected:
  virtual std::auto_ptr<PropertyBase> doGetProperty(const string_type& name)
  {
    throw SAXNotRecognizedException("Property not recognized " + makeString(name));
  } // doGetProperty

  virtual void doSetProperty(const string_type& name, std::auto_ptr<PropertyBase> value)
  {
    throw SAXNotRecognizedException("Property not recognized " + makeString(name));
  } // doSetProperty

public:
  /**
   * Set the entity resolver.
   *
   * @param resolver The new entity resolver.
   * @see XMLReader#setEntityResolver
   */
  virtual void setEntityResolver(EntityResolverT& resolver) { entityResolver_ = &resolver; }
  /**
   * Return the current entity resolver.
   *
   * @return The current entity resolver, or null if none was supplied.
   * @see XMLReader#getEntityResolver
   */
  virtual EntityResolverT* getEntityResolver() const { return entityResolver_; }
  
  /**
   * Set the DTD handler.
   *
   * @param handler The new DTD handler.
   * @see XMLReader#setEntityResolver
   */
  virtual void setDTDHandler(DTDHandlerT& handler) { dtdHandler_ = &handler; } 
  /**
   * Return the current DTD handler.
   *
   * @return The current DTD handler, or null if none was supplied.
   * @see XMLReader#getEntityResolver
   */
  virtual DTDHandlerT* getDTDHandler() const { return dtdHandler_; }
  
  /**
   * Set the content handler.
   *
   * @param handler The new content handler.
   * @see XMLReader#setEntityResolver
   */
  virtual void setContentHandler(ContentHandlerT& handler) { contentHandler_ = &handler; }
  /**
   * Return the current content handler.
   *
   * @return The current content handler, or null if none was supplied.
   * @see XMLReader#getEntityResolver
   */
  virtual ContentHandlerT* getContentHandler() const { return contentHandler_; }

  /**
   * Set the error handler.
   *
   * @param handler The new error handler.
   * @see XMLReader#setEntityResolver
   */
  virtual void setErrorHandler(ErrorHandler& handler) { errorHandler_ = &handler; }
  /**
   * Return the current error handler.
   *
   * @return The current error handler, or null if none was supplied.
   * @see XMLReader#getEntityResolver
   */
  virtual ErrorHandler* getErrorHandler() const { return errorHandler_; }

  /**
   * Parse an XML document.
   *
   * @param input An input source for the document.
   * @see Parser#parse(InputSource&)
   */
  virtual void parse(InputSourceT& input)
  {
    if(parsing_)
      throw SAXException("Parser is already in use.");
    setupParser();
    parsing_ = true;
    try
    {
      parser_.parse(input);
    }
    catch(...)
    {
      parsing_ = false;
      throw;
    }
    parsing_ = false;
  } // parse

  /////////////////////////////////////
  // DocumentHandler implementation
  /**
   * Adapt a SAX1 document locator event.
   *
   * @param locator A document locator.
   * @see ContentHandler#setDocumentLocator
   */
  virtual void setDocumentLocator(const LocatorT& locator)
  {
    locator_ = &locator;
    if(contentHandler_)
      contentHandler_->setDocumentLocator(locator);
  } // setDocumentLocator

  /**
   * Adapt a SAX1 start document event.
   *
   * @see DocumentHandler#startDocument
   */
  virtual void startDocument()
  {
    if(contentHandler_)
      contentHandler_->startDocument();
  } // startDocument

  /**
   * Adapt a SAX1 end document event.
   *
   * @see DocumentHandler#endDocument
   */
  virtual void endDocument()
  {
    if(contentHandler_)
      contentHandler_->endDocument();
  } // endDocument

  /**
   * Adapt a SAX1 startElement event.
   *
   * <p>If necessary, perform Namespace processing.</p>
   *
   * @param qName The qualified (prefixed) name.
   * @param qAtts The XML 1.0 attribute list (with qnames).
   */
  virtual void startElement(const string_type& qName,
	                          const AttributeListT& qAtts)
  {
    if(!namespaces_)
    {
      if(contentHandler_) 
      {
        attAdaptor_.setAttributeList(qAtts);
        contentHandler_->startElement(NULL_STRING, NULL_STRING, qName, attAdaptor_);
      } // if(contentHandler_)
      return;
    } // if(!namespaces)

    // OK we're doing Namespaces
    nsSupport_.pushContext();
    bool seenDecl = false;
    atts_.clear();

    // take a first pass and copy all the attributes, noting any declarations
    int length = qAtts.getLength();
    for(int i = 0; i < length; ++i)
    {
      string_type attQName = qAtts.getName(i);
      string_type type = qAtts.getType(i);
      string_type value = qAtts.getValue(i);

      // declaration?
      if(attQName.find(NamespaceSupportT::XMLNS) == 0) 
      {
        string_type prefix;
        int n = attQName.find(NamespaceSupportT::COLON);
        if(n != string_type::npos())
            prefix = string_type(attQName.begin() + n + 1, attQName.end());
        if(!nsSupport_.declarePrefix(prefix, value)) 
          reportError("Illegal Namespace prefix " + makeString(prefix));
        if(contentHandler_)
          contentHandler_->startPrefixMapping(prefix, value);
        if(prefixes_)
          atts_.addAttribute(NULL_STRING, NULL_STRING, attQName, type, value);
        seenDecl = true;
      }
      else
      {
        NamespaceSupportT::Parts attName = processName(attQName, true);
        atts_.addAttribute(attName.URI, attName.localName, attName.rawName, type, value);
      }
    } // for ...

    // if there was a Namespace decl we have to go around again
    if(seenDecl)
    {
       int length = atts_.getLength();
       for(int i = 0; i < length; ++i)
       {
         string_type attQName = atts_.getQName(i);
         if(attQName.find(NamespaceSupportT::XMLNS)) 
         {
           NamespaceSupportT::Parts attName = processName(attQName, true);
           atts_.setURI(i, attName.URI);
           atts_.setLocalName(i, attName.localName);
         } // if ...
       } // for ... 
    } // if(seenDecl)

    // at last! report the event
    if(contentHandler_)
    {
      NamespaceSupportT::Parts name = processName(qName, false);
      contentHandler_->startElement(name.URI, name.localName, name.rawName, atts_);
    } // if(contentHandler_)
  } // startElement


  /**
   * Adapt a SAX1 end element event.
   *
   * @param qName The qualified (prefixed) name.
   * @see DocumentHandler#endElement
   */
  void endElement(const string_type& qName)
  {
      if(!namespaces_) 
      {
        if(contentHandler_)
          contentHandler_->endElement(NULL_STRING, NULL_STRING, qName);
        return;
      } // if(!namespaces_)

      NamespaceSupportT::Parts name = processName(qName, false);
      if(contentHandler_) 
      {
        contentHandler_->endElement(name.URI, name.localName, name.rawName);
        NamespaceSupportT::stringListT prefixes = nsSupport_.getDeclaredPrefixes();
        for(int i = 0, end = prefixes.size(); i != end; ++i)
          contentHandler_->endPrefixMapping(prefixes[i]);
      } // if(contentHandler_)
      nsSupport_.popContext();
  } // endElement

  /**
   * Adapt a SAX1 characters event.
   *
   * @param ch The characters.
   * @see DocumentHandler#characters
   */
  virtual void characters(const string_type& ch)
  {
    if(contentHandler_)
      contentHandler_->characters(ch);
  } // characters

  /**
   * Adapt a SAX1 ignorable whitespace event.
   *
   * @param ch Thecharacters.
   * @see DocumentHandler#ignorableWhitespace
   */
  virtual void ignorableWhitespace(const string_type& ch)
  {
    if(contentHandler_)
      contentHandler_->ignorableWhitespace(ch);
  } // ignorableWhitespace

  /**
   * Adapt a SAX1 processing instruction event.
   *
   * @param target The processing instruction target.
   * @param data The remainder of the processing instruction
   * @see DocumentHandler#processingInstruction
   */
  virtual void processingInstruction(const string_type& target, const string_type& data) 
  {
    if(contentHandler_)
      contentHandler_->processingInstruction(target, data);
  } // processingInstruction

private:
  typedef NamespaceSupport<string_type, string_adaptor> NamespaceSupportT;
  typedef AttributesImpl<string_type> AttributesImplT;

  void setupParser()
  {
    nsSupport_.reset();

    if(entityResolver_)
      parser_.setEntityResolver(*entityResolver_);
    if(dtdHandler_)
      parser_.setDTDHandler(*dtdHandler_);
    if(errorHandler_)
      parser_.setErrorHandler(*errorHandler_);
    parser_.setDocumentHandler(*this);
    locator_ = 0;
  } // setupParser

  NamespaceSupportT::Parts processName(const string_type& qName, bool isAttribute)
  {
    NamespaceSupportT::Parts p = nsSupport_.processName(qName, isAttribute);
    if(p.URI == NULL_STRING && p.prefix != NULL_STRING)
      reportError("Undeclared prefix " + makeString(qName));
    return p;
  } // processName

  void reportError(const std::string& message)
  {
    if(errorHandler_ == 0)
      return;

    if(locator_)
      errorHandler_->error(SAXParseExceptionT(message, *locator_));
    else
      errorHandler_->error(SAXParseExceptionT(message, NULL_STRING, NULL_STRING, -1, -1));
  } // reportError

  void checkNotParsing(const std::string& type, const string_type& name)
  {
    if(parsing_)
       throw SAXNotSupportedException("Can't change feature while parsing");
  } // checkNotParsing

  std::string makeString(const string_type& str) const
  {
    return string_adaptor::asStdString(str);
  } // makeString

  // This wrapper is used only when Namespace support is disabled.
  class AttributesListAdaptor : public Attributes<string_type>
  {
  public:  
    typedef typename ParserAdaptor<string_type, string_adaptor> ParserAdaptorT;
    typedef typename AttributeList<string_type, string_adaptor> AttributeListT;

    void setAttributeList(const AttributeListT& attList)
    {
      attList_ = &attList;
    } // setAttributeList

    virtual int getLength() const { return attList_->getLength(); }
    virtual string_type getURI(int) const { return string_type(); } 
    virtual string_type getLocalName(int) const { return string_type(); }
    virtual string_type getQName(int i) const { return attList_->getName(i); }
    virtual string_type getType(int i) const { return attList_->getType(i); }
    virtual string_type getValue(int i) const { return attList_->getValue(i); }

    virtual int getIndex(const string_type&, const string_type&) const { return -1; }
    virtual int getIndex(const string_type& qName) const
    {
      int max = attList_->getLength();
      for(int i = 0; i < max; ++i)
        if(attList_->getName(i) == qName)
            return i;
      return -1;
    } // getIndex
    virtual string_type getType(const string_type&, const string_type&) const { return string_type(); }
    virtual string_type getType(const string_type& qName) const { return attList_->getType(qName); }
    virtual string_type getValue(const string_type&, const string_type&) const { return string_type(); }
    virtual string_type getValue(const string_type& qName) const { return attList_->getValue(qName); }

  private:
    static string_type empty_;
    const AttributeListT* attList_;
  }; // AttributesListAdaptor

  // member variables
  NamespaceSupportT nsSupport_;
  AttributesListAdaptor attAdaptor_;

  bool parsing_;
  // strings?
  ParserT& parser_;
  AttributesImplT atts_;

  // features
  bool namespaces_;
  bool prefixes_;

  // handlers
  const LocatorT* locator_;
  EntityResolverT* entityResolver_;
  DTDHandlerT* dtdHandler_;
  ContentHandlerT* contentHandler_;
  ErrorHandler* errorHandler_;

public:
  const string_type NULL_STRING;

private:
  ParserAdaptor();
  ParserAdaptor(const ParserAdaptor&);
  ParserAdaptor& operator=(const ParserAdaptor&);
  bool operator==(const ParserAdaptor&);
}; // ParserAdaptor

} // namespace SAX
} // namespace Arabica

#endif
