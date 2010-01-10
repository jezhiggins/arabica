#ifndef ARABICA_XSLT_CREATE_HANDLER_HPP
#define ARABICA_XSLT_CREATE_HANDLER_HPP

#include <SAX/XMLReader.hpp>
#include <SAX/helpers/DefaultHandler.hpp>
#include <XPath/XPath.hpp>

#include "../xslt_compilation_context.hpp"
#include "../xslt_compiled_stylesheet.hpp"
#include "xslt_constants.hpp"

namespace Arabica
{
namespace XSLT
{

template<class Handler>
SAX::DefaultHandler<std::string>* CreateHandler(CompilationContext& context)
{
  return new Handler(context);
} // create

class NotImplementedYetHandler : public SAX::DefaultHandler<std::string>
{
public:
  NotImplementedYetHandler(CompilationContext& /* context */) { }

  virtual void startElement(const std::string& /* namespaceURI */,
                            const std::string& /* localName */,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& /* atts */)
  {
    throw SAX::SAXException("Haven't implemented " + qName + " yet");
  } // startElement
}; // NotImplementedYetHandler

typedef SAX::DefaultHandler<std::string>* (*CreateHandlerPtr)(CompilationContext&);

struct ChildElement
{
  const char* const name;
  CreateHandlerPtr createHandler;
}; // struct ChildElement

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_CONSTANTS_HPP

