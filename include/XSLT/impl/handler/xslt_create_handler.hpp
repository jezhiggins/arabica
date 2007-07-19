#ifndef ARABICA_XSLT_CREATE_HANDLER_HPP
#define ARABICA_XSLT_CREATE_HANDLER_HPP

#include <SAX/XMLReader.h>
#include <SAX/helpers/DefaultHandler.h>
#include <XPath/XPath.hpp>

#include "../xslt_compilation_context.hpp"
#include "../xslt_stylesheet.hpp"
#include "xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

template<class Handler>
SAX::DefaultHandler* CreateHandler(CompilationContext& context)
{
  return new Handler(context);
} // create

class NotImplementedYetHandler : public SAX::DefaultHandler
{
public:
  NotImplementedYetHandler(CompilationContext& context) { }

    virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes& atts)
  {
    throw SAX::SAXException("Haven't implemented " + qName + " yet");
  } // startElement
}; // NotImplementedYetHandler

typedef SAX::DefaultHandler* (*CreateHandlerPtr)(CompilationContext&);

struct ChildElement
{
  const char* const name;
  CreateHandlerPtr createHandler;
}; // struct ChildElement

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CONSTANTS_HPP

