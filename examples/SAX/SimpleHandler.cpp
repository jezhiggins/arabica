#ifdef _MSC_VER
#  pragma warning(disable:4786)
#endif

#include "SimpleHandler.hpp"
#include <iostream>

//////////////////////////////////////////////
// EntityResolver
Arabica::SAX::InputSource<std::string> SimpleHandler::resolveEntity(const std::string& /* publicId */, const std::string& /* systemId */)
{
  return Arabica::SAX::InputSource<std::string>();
} // resolveEntity

//////////////////////////////////////////////
// DTDHandler
void SimpleHandler::notationDecl(const std::string& name,
                          const std::string& publicId,
                          const std::string& systemId)
{
  std::cout << "notationDecl " << name << std::endl;
  std::cout << "    public : " << publicId << std::endl;
  std::cout << "    system : " << systemId << std::endl;
} // notationDecl

void SimpleHandler::unparsedEntityDecl(const std::string& name,
	                              const std::string& publicId,
                                const std::string& systemId,
                                const std::string& notationName)
{
  std::cout << "unparsedEntityDecl " << name << std::endl;
  std::cout << "    public : " << publicId << std::endl;
  std::cout << "    system : " << systemId << std::endl;
  std::cout << "    notation : " << notationName << std::endl;
} // unparsedEntityDecl
  
////////////////////////////////////////////////////
// ContentHandler
void SimpleHandler::startDocument()
{
  std::cout << "startDocument" << std::endl;
} // startDocument

void SimpleHandler::endDocument()
{
  std::cout << "endDocument" << std::endl;
} // endDocument

void SimpleHandler::startPrefixMapping(const std::string& prefix, const std::string& uri)
{
  std::cout << "startPrefixMapping " << prefix << " -> " << uri << std::endl;
} // startPrefixMapping 

void SimpleHandler::endPrefixMapping(const std::string& prefix)
{
  std::cout << "endPrefixMapping " << prefix << std::endl;
} // startPrefixMapping 

void SimpleHandler::startElement(const std::string& namespaceURI, 
                                 const std::string& localName,
                                 const std::string& qName, 
                                 const Arabica::SAX::Attributes<std::string>& /* atts */)
{
  if(localName.length())
	  std::cout << "Start Element: " << namespaceURI << ":" << localName << std::endl;
  else
	  std::cout << "Start Element: " << qName << std::endl;
} // startElement

void SimpleHandler::endElement(const std::string& namespaceURI, 
                               const std::string& localName,
                               const std::string& /* qName */)
{
	std::cout << "endElement: " << namespaceURI << ":" << localName << std::endl;
} // endElement

void SimpleHandler::characters(const std::string& ch)
{
	std::cout << "Characters: " << ch << std::endl;
} // characters

void SimpleHandler::ignorableWhitespace(const std::string& ch)
{
	std::cout << "Whitespace: " << ch << std::endl;
} // characters

void SimpleHandler::processingInstruction(const std::string& target, const std::string& data)
{
  std::cout << "processingInstruction " << target << " - " << data << std::endl;
}

void SimpleHandler::skippedEntity(const std::string& name)
{
  std::cout << "skippedEntity " << name << std::endl;
} // 

/////////////////////////////////////////////////////
// ErrorHandler
void SimpleHandler::warning(const Arabica::SAX::SAXParseException<std::string>& exception)
{
  std::cerr << "WARNING: " << exception.what() << std::endl;
} // warning

void SimpleHandler::error(const Arabica::SAX::SAXParseException<std::string>& exception)
{
  std::cerr << "ERROR  : " << exception.what() << std::endl;
} // error

void SimpleHandler::fatalError(const Arabica::SAX::SAXParseException<std::string>& exception)
{
  std::cerr << "FATAL  : " << exception.what() << std::endl;
} // fatalError

///////////////////////////////////////////////////////
// LexicalHandler
void SimpleHandler::startDTD(const std::string& name,
                      const std::string& publicId,
                      const std::string& systemId)
{
  std::cout << "startDTD : " << name << std::endl 
    << "  publicId : " << publicId << std::endl 
    << "  systemId : " << systemId << std::endl;
} // startDTD

void SimpleHandler::endDTD()
{
  std::cout << "endDTD" << std::endl;
} // endDTD

void SimpleHandler::startEntity(const std::string& name)
{
  std::cout << "startEntity : " << name << std::endl;
} 

void SimpleHandler::endEntity(const std::string& name)
{
  std::cout << "endEntity : " << name << std::endl;
} 

void SimpleHandler::startCDATA()
{
  std::cout << "startCDATA" << std::endl;
} 

void SimpleHandler::endCDATA()
{
  std::cout << "endCDATA" << std::endl;
} 

void SimpleHandler::comment(const std::string& text)
{
  std::cout << "comment " << text << std::endl;
}

///////////////////////////////////////////////
// Declhandler
void SimpleHandler::elementDecl(const std::string& name, const std::string& model)
{
  std::cout << "elementDecl " << name << " - " << model << std::endl;
}

void SimpleHandler::attributeDecl(const std::string& elementName,
                           const std::string& attributeName,
                           const std::string& type,
                           const std::string& valueDefault,
                           const std::string& value)
{
  std::cout << "attributeDecl " << elementName << "." << attributeName << std::endl
    << "  type " << type << std::endl
    << "  default " << valueDefault << std::endl
    << "  value " << value << std::endl;
}

void SimpleHandler::internalEntityDecl(const std::string& name, const std::string& value)
{
  std::cout << "internalEntityDecl " << name << " = " << value << std::endl;
} 

void SimpleHandler::externalEntityDecl(const std::string& name, 
                                const std::string& publicId,
                                const std::string& systemId)
{
  std::cout << "externalEntityDecl " << name << std::endl 
    << "  publicId : " << publicId << std::endl 
    << "  systemId : " << systemId << std::endl;
} // startDTD

// end of file
