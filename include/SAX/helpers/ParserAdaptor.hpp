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

namespace SAX
{

/**
 * Adapt a SAX1 Parser as a SAX2 XMLReader.
 *
 * <p>This class wraps a SAX1 {@link basic_Parser Parser}
 * and makes it act as a SAX2 {@link basic_XMLReader XMLReader},
 * with feature, property, and Namespace support.  Note
 * that it is not possible to report {@link basic_ContentHandler#skippedEntity
 * skippedEntity} events, since SAX1 does not make that information available.</p>
 *
 * <p>This adapter does not test for duplicate Namespace-qualified
 * attribute names.</p>
 *
 * @since SAX 2.0
 * @author Jez Higgins,
 *         <a href="mailto:jez@jezuk.co.uk">jez@jezuk.co.uk</a>
 * @version 2.0
 * @see basic_XMLReader
 * @see basic_Parser
 */
template<class string_type, class string_adaptor_type>
class basic_ParserAdaptor : public basic_XMLReader<string_type>, 
                            public basic_DocumentHandler<string_type>
{
public:
  typedef string_type stringT;
  typedef string_adaptor_type string_adaptorT;
  typedef basic_Parser<stringT> ParserT;
  typedef basic_EntityResolver<stringT> EntityResolverT;
  typedef basic_DTDHandler<stringT> DTDHandlerT;
  typedef basic_DocumentHandler<stringT> DocumentHandlerT;
  typedef basic_ContentHandler<stringT> ContentHandlerT;
  typedef basic_InputSource<stringT> InputSourceT;
  typedef basic_Locator<stringT> LocatorT;
  typedef basic_SAXParseException<stringT> SAXParseExceptionT;
  typedef basic_AttributeList<stringT> AttributeListT;

  basic_ParserAdaptor(ParserT& parser) :
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
   * @see basic_XMLReader#setFeature
   */
  virtual void setFeature(const stringT& name, bool value)
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
   * @see basic_XMLReader#setFeature
   */
  virtual bool getFeature(const stringT& name) const
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
  virtual std::auto_ptr<PropertyBase> doGetProperty(const stringT& name)
  {
    throw SAXNotRecognizedException("Property not recognized " + makeString(name));
  } // doGetProperty

  virtual void doSetProperty(const stringT& name, std::auto_ptr<PropertyBase> value)
  {
    throw SAXNotRecognizedException("Property not recognized " + makeString(name));
  } // doSetProperty

public:
  /**
   * Set the entity resolver.
   *
   * @param resolver The new entity resolver.
   * @see basic_XMLReader#setEntityResolver
   */
  virtual void setEntityResolver(EntityResolverT& resolver) { entityResolver_ = &resolver; }
  /**
   * Return the current entity resolver.
   *
   * @return The current entity resolver, or null if none was supplied.
   * @see basic_XMLReader#getEntityResolver
   */
  virtual EntityResolverT* getEntityResolver() const { return entityResolver_; }
  
  /**
   * Set the DTD handler.
   *
   * @param handler The new DTD handler.
   * @see basic_XMLReader#setEntityResolver
   */
  virtual void setDTDHandler(DTDHandlerT& handler) { dtdHandler_ = &handler; } 
  /**
   * Return the current DTD handler.
   *
   * @return The current DTD handler, or null if none was supplied.
   * @see basic_XMLReader#getEntityResolver
   */
  virtual DTDHandlerT* getDTDHandler() const { return dtdHandler_; }
  
  /**
   * Set the content handler.
   *
   * @param handler The new content handler.
   * @see basic_XMLReader#setEntityResolver
   */
  virtual void setContentHandler(ContentHandlerT& handler) { contentHandler_ = &handler; }
  /**
   * Return the current content handler.
   *
   * @return The current content handler, or null if none was supplied.
   * @see basic_XMLReader#getEntityResolver
   */
  virtual ContentHandlerT* getContentHandler() const { return contentHandler_; }

  /**
   * Set the error handler.
   *
   * @param handler The new error handler.
   * @see basic_XMLReader#setEntityResolver
   */
  virtual void setErrorHandler(ErrorHandler& handler) { errorHandler_ = &handler; }
  /**
   * Return the current error handler.
   *
   * @return The current error handler, or null if none was supplied.
   * @see basic_XMLReader#getEntityResolver
   */
  virtual ErrorHandler* getErrorHandler() const { return errorHandler_; }

  /**
   * Parse an XML document.
   *
   * @param input An input source for the document.
   * @see basic_Parser#parse(InputSource&)
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
   * @see basic_ContentHandler#setDocumentLocator
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
   * @see basic_DocumentHandler#startDocument
   */
  virtual void startDocument()
  {
    if(contentHandler_)
      contentHandler_->startDocument();
  } // startDocument

  /**
   * Adapt a SAX1 end document event.
   *
   * @see basic_DocumentHandler#endDocument
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
  virtual void startElement(const stringT& qName,
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
      stringT attQName = qAtts.getName(i);
      stringT type = qAtts.getType(i);
      stringT value = qAtts.getValue(i);

      // declaration?
      if(attQName.find(NamespaceSupportT::XMLNS) == 0) 
      {
        stringT prefix;
        int n = attQName.find(NamespaceSupportT::COLON);
        if(n != stringT::npos())
            prefix = stringT(attQName.begin() + n + 1, attQName.end());
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
         stringT attQName = atts_.getQName(i);
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
   * @see basic_DocumentHandler#endElement
   */
  void endElement(const stringT& qName)
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
   * @see basic_DocumentHandler#characters
   */
  virtual void characters(const stringT& ch)
  {
    if(contentHandler_)
      contentHandler_->characters(ch);
  } // characters

  /**
   * Adapt a SAX1 ignorable whitespace event.
   *
   * @param ch Thecharacters.
   * @see basic_DocumentHandler#ignorableWhitespace
   */
  virtual void ignorableWhitespace(const stringT& ch)
  {
    if(contentHandler_)
      contentHandler_->ignorableWhitespace(ch);
  } // ignorableWhitespace

  /**
   * Adapt a SAX1 processing instruction event.
   *
   * @param target The processing instruction target.
   * @param data The remainder of the processing instruction
   * @see basic_DocumentHandler#processingInstruction
   */
  virtual void processingInstruction(const stringT& target, const stringT& data) 
  {
    if(contentHandler_)
      contentHandler_->processingInstruction(target, data);
  } // processingInstruction

private:
  typedef basic_NamespaceSupport<stringT, string_adaptorT> NamespaceSupportT;
  typedef basic_AttributesImpl<stringT> AttributesImplT;

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

  NamespaceSupportT::Parts processName(const stringT& qName, bool isAttribute)
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

  void checkNotParsing(const std::string& type, const stringT& name)
  {
    if(parsing_)
       throw SAXNotSupportedException("Can't change feature while parsing");
  } // checkNotParsing

  std::string makeString(const stringT& str) const
  {
    return string_adaptorT().asStdString(str);
  } // makeString

  // This wrapper is used only when Namespace support is disabled.
  class AttributesListAdaptor : public basic_Attributes<stringT>
  {
  public:  
    typedef typename basic_ParserAdaptor<stringT, string_adaptorT> ParserAdaptorT;
    typedef typename basic_AttributeList<stringT> AttributeListT;

    void setAttributeList(const AttributeListT& attList)
    {
      attList_ = &attList;
    } // setAttributeList

    virtual int getLength() const { return attList_->getLength(); }
    virtual stringT getURI(int) const { return stringT(); } 
    virtual stringT getLocalName(int) const { return stringT(); }
    virtual stringT getQName(int i) const { return attList_->getName(i); }
    virtual stringT getType(int i) const { return attList_->getType(i); }
    virtual stringT getValue(int i) const { return attList_->getValue(i); }

    virtual int getIndex(const stringT&, const stringT&) const { return -1; }
    virtual int getIndex(const stringT& qName) const
    {
      int max = attList_->getLength();
      for(int i = 0; i < max; ++i)
        if(attList_->getName(i) == qName)
            return i;
      return -1;
    } // getIndex
    virtual stringT getType(const stringT&, const stringT&) const { return stringT(); }
    virtual stringT getType(const stringT& qName) const { return attList_->getType(qName); }
    virtual stringT getValue(const stringT&, const stringT&) const { return stringT(); }
    virtual stringT getValue(const stringT& qName) const { return attList_->getValue(qName); }

  private:
    static stringT empty_;
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
  const stringT NULL_STRING;

private:
  basic_ParserAdaptor();
  basic_ParserAdaptor(const basic_ParserAdaptor&);
  basic_ParserAdaptor& operator=(const basic_ParserAdaptor&);
  bool operator==(const basic_ParserAdaptor&);
}; // ParserAdaptor

typedef basic_ParserAdaptor<std::string, char> ParserAdaptor;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_ParserAdaptor<std::wstring, wchar_t> wParserAdaptor;
#endif

} // namespace SAX

#endif
