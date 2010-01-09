#ifndef SimpleHandlerH
#define SimpleHandlerH

#include <string>
#include <SAX/XMLReader.hpp>
#include <SAX/EntityResolver.hpp>
#include <SAX/DTDHandler.hpp>
#include <SAX/ContentHandler.hpp>
#include <SAX/ErrorHandler.hpp>
#include <SAX/Locator.hpp>
#include <SAX/Attributes.hpp>
#include <SAX/ext/LexicalHandler.hpp>
#include <SAX/ext/DeclHandler.hpp>
#include <SAX/SAXException.hpp>

class SimpleHandler : public Arabica::SAX::EntityResolver<std::string>, 
					public Arabica::SAX::DTDHandler<std::string>,
					public Arabica::SAX::ContentHandler<std::string>, 
          public Arabica::SAX::ErrorHandler<std::string>,
          public Arabica::SAX::LexicalHandler<std::string>,
          public Arabica::SAX::DeclHandler<std::string>
{
public:
  SimpleHandler() { }
  virtual ~SimpleHandler() { }

  //////////////////////////////////////////////
  // EntityResolver
  virtual Arabica::SAX::InputSource<std::string> resolveEntity(const std::string& publicId, const std::string& systemId);

  //////////////////////////////////////////////
  // DTDHandler
  virtual void notationDecl(const std::string& name,
                            const std::string& publicId,
                            const std::string& systemId);
  virtual void unparsedEntityDecl(const std::string& name,
	                                const std::string& publicId,
                                  const std::string& systemId,
                                  const std::string& notationName);

  ////////////////////////////////////////////////////
  // ContentHandler
  virtual void setDocumentLocator(const LocatorT& /* locator */) { }
  virtual void startDocument();
  virtual void endDocument();
  virtual void startPrefixMapping(const std::string& prefix, const std::string& uri);
  virtual void endPrefixMapping(const std::string& prefix);
  virtual void startElement(const std::string& namespaceURI, const std::string& localName,
                            const std::string& qName, const AttributesT& atts);
  virtual void endElement(const std::string& namespaceURI, const std::string& localName,
                          const std::string& qName);
  virtual void characters(const std::string& ch);
  virtual void ignorableWhitespace(const std::string& ch);
  virtual void processingInstruction(const std::string& target, const std::string& data);
  virtual void skippedEntity(const std::string& name);

  /////////////////////////////////////////////////////
  // ErrorHandler
  virtual void warning(const Arabica::SAX::SAXParseException<std::string>&);
  virtual void error(const Arabica::SAX::SAXParseException<std::string>&);
  virtual void fatalError(const Arabica::SAX::SAXParseException<std::string>& exception);

  ///////////////////////////////////////////////////////
  // LexicalHandler
  virtual void startDTD(const std::string& name,
                        const std::string& publicId,
                        const std::string& systemId);
  virtual void endDTD();
  virtual void startEntity(const std::string& name);
  virtual void endEntity(const std::string& name);
  virtual void startCDATA();
  virtual void endCDATA();
  virtual void comment(const std::string& text);


  ///////////////////////////////////////////////
  // Declhandler
  virtual void elementDecl(const std::string& name, const std::string& model);
  virtual void attributeDecl(const std::string& elementName,
                             const std::string& attributeName,
                             const std::string& type,
                             const std::string& valueDefault,
                             const std::string& value);
  virtual void internalEntityDecl(const std::string& name, const std::string& value);
  virtual void externalEntityDecl(const std::string& name, 
                                  const std::string& publicId,
                                  const std::string& systemId);

private:
  SimpleHandler(const SimpleHandler&);
  SimpleHandler& operator=(const SimpleHandler&);
  bool operator==(const SimpleHandler&);
}; // class SimpleHandler

#endif

