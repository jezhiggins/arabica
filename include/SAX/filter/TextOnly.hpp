#ifndef ARABICA_TEXT_ONLY_HPP
#define ARABICA_TEXT_ONLY_HPP

#include <SAX/ArabicaConfig.hpp>
#include <SAX/helpers/XMLFilterImpl.hpp>
#include <Arabica/StringAdaptor.hpp>

namespace Arabica
{
namespace SAX
{

/**
  Strips out everything except startDocument, endDocument and text
 */
template<class string_type, class string_adaptor=Arabica::default_string_adaptor<string_type> >
class TextOnly : public XMLFilterImpl<string_type, string_adaptor>
{
  typedef XMLFilterImpl<string_type, string_adaptor> XMLFilterT;

public:
  typedef XMLReaderInterface<string_type, string_adaptor> XMLReaderT;

  TextOnly() : 
    XMLFilterT(0)
  { 
  } // TextOnly

  TextOnly(XMLReaderT& parent) : 
    XMLFilterT(parent) 
  {
  } // TextOnly

  // ContentHandler
  virtual void startElement(const stringT& namespaceURI, const stringT& localName,
                            const stringT& qName, const AttributesT& atts) { }
  virtual void endElement(const stringT& namespaceURI, const stringT& localName,
                          const stringT& qName) { }
  virtual void processingInstruction(const stringT& target, const stringT& data) { }
  virtual void skippedEntity(const stringT& name) { }

  // Lexical Handler
  virtual void startDTD(const stringT& name, const stringT& publicId, const stringT& systemId) { }
  virtual void endDTD() { }
  virtual void startEntity(const stringT& name) { }
  virtual void endEntity(const stringT& name) { }
  virtual void startCDATA() { }
  virtual void endCDATA() { }
  virtual void comment(const stringT& text) { }

  // DTD Handler
  virtual void notationDecl(const stringT& name, const stringT& publicId, const stringT& systemId) { }
  virtual void unparsedEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId, const stringT& notationName) { }

  // Decl Handler
  virtual void elementDecl(const stringT& name, const stringT& model) { }
  virtual void attributeDecl(const stringT& elementName, const stringT& attributeName,
                              const stringT& type, const stringT& valueDefault, const stringT& value) { }
  virtual void internalEntityDecl(const stringT& name, const stringT& value) { }
  virtual void externalEntityDecl(const stringT& name, const stringT& publicId, const stringT& systemId) { }
}; // class TextOnly

} // namespace SAX
} // namespace Arabica

#endif
