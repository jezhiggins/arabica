#ifndef ARABICA_XSLT_STYLESHEETCONSTANT_HPP
#define ARABICA_XSLT_STYLESHEETCONSTANT_HPP

#include <XML/XMLCharacterClasses.hpp>
#include <XPath/impl/xpath_namespace_context.hpp>
#include <memory>

#include "xslt_stylesheet_parser.hpp"
#include "xslt_compiled_stylesheet.hpp"
#include "xslt_compilation_context.hpp"
#include "handler/xslt_template_handler.hpp"
#include "handler/xslt_include_handler.hpp"
#include "handler/xslt_output_handler.hpp"
#include "handler/xslt_namespace_alias_handler.hpp"

namespace Arabica
{
namespace XSLT
{

class StylesheetHandler : public SAX::DefaultHandler<std::string>
{
public:
  StylesheetHandler(CompilationContext& context) :
    context_(context),
    top_(false),
    foreign_(0)
  {
    context_.root(*this);
    includer_.context(context_, this);      
  } // StylesheetHandler

  virtual void startDocument()
  {
    top_ = true;
  } // startDocument

  virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(foreign_)
    {
      ++foreign_;
      return;
    } // if(foreign_)

    if(top_)
    {
      if(namespaceURI != StylesheetConstant::NamespaceURI())
        throw SAX::SAXException("The source file does not look like a stylesheet.");
      if(localName != "stylesheet" && localName != "transform")
        throw SAX::SAXException("Top-level element must be 'stylesheet' or 'transform'.");

      static const ValueRule rules[] = { { "version", true, 0 },
					 { "extension-element-prefixes", false, 0 },
					 { "exclude-result-prefixes", false, 0 },
                                         { 0, false, 0 } };
      std::map<std::string, std::string> attributes = gatherAttributes(qName, atts, rules);
      if(attributes["version"] != StylesheetConstant::Version())
        throw SAX::SAXException("I'm only a poor version 1.0 XSLT Transformer.");

      top_ = false;

      return;
    } // if(top_)

    if(namespaceURI == StylesheetConstant::NamespaceURI())
    {
      if((localName == "import") || (localName == "include"))
      {
        include_stylesheet(namespaceURI, localName, qName, atts);
        return;
      } // if ...

      for(const ChildElement* c = allowedChildren; c->name != 0; ++c)
        if(c->name == localName)
        {
          context_.push(0,
                        c->createHandler(context_),
                        namespaceURI, 
                        qName, 
                        localName, 
                        atts);
          return;
        } // if ...
    } // if ... 
    else if(!namespaceURI.empty())
    {
      ++foreign_;
      return;
    } // if(!namespaceURI.empty())

    throw SAX::SAXException("xsl:stylesheet does not allow " + qName + " here.");
  } // startElement

  virtual void endElement(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName)
  {
    if(foreign_)
      --foreign_;
  } // endElement

  virtual void characters(const std::string& ch)
  {
    if(foreign_)
      return;

    for(std::string::const_iterator s = ch.begin(), e = ch.end(); s != e; ++s)
      if(!Arabica::XML::is_space(*s))
        throw SAX::SAXException("stylesheet element can not contain character data :'" + ch +"'");
  } // characters

  virtual void endDocument()
  {
    includer_.unwind_imports();
    context_.stylesheet().prepare();
  } // endDocument

private:
  void include_stylesheet(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName,
                          const SAX::Attributes<std::string>& atts)
  {
    includer_.start_include(namespaceURI, localName, qName, atts);
  } // include_stylesheet

  CompilationContext& context_;
  SAX::DefaultHandler<std::string>* child_;
  IncludeHandler includer_;
  bool top_;
  unsigned int foreign_;

  static const ChildElement allowedChildren[];
}; // class StylesheetHandler

const ChildElement StylesheetHandler::allowedChildren[] =
  {
    { "attribute-set", CreateHandler<NotImplementedYetHandler>},
    { "decimal-format", CreateHandler<NotImplementedYetHandler>},
    //"import"
    //"include"
    { "key", CreateHandler<NotImplementedYetHandler>},
    { "namespace-alias", CreateHandler<NamespaceAliasHandler>},
    { "output", CreateHandler<OutputHandler>},
    { "param", CreateHandler<TopLevelVariableHandler<Param> >},
    { "preserve-space", CreateHandler<NotImplementedYetHandler>},
    { "strip-space", CreateHandler<NotImplementedYetHandler>},
    { "template", CreateHandler<TemplateHandler> },
    { "variable", CreateHandler<TopLevelVariableHandler<Variable> > },
    { 0, 0 }
  }; // StylesheetHandler::allowedChildren

class StylesheetCompiler 
{
public:
  StylesheetCompiler() 
  {
  } // StylesheetCompiler

  ~StylesheetCompiler()
  {
  } // ~StylesheetCompiler

  std::auto_ptr<Stylesheet> compile(SAX::InputSource<std::string>& source)
  {
    error_ = "";

    std::auto_ptr<CompiledStylesheet> stylesheet(new CompiledStylesheet());

    StylesheetParser parser;
    CompilationContext context(parser, *stylesheet.get());

    StylesheetHandler stylesheetHandler(context);
    parser.setContentHandler(stylesheetHandler);
    //parser.setErrorHandler(*this);
  
    //if(entityResolver_)
    //  parser.setEntityResolver(*entityResolver_);
    try {
      parser.parse(source);
    } // try
    catch(std::exception& ex)
    {
      error_ = ex.what();
      //std::cerr << "Compilation Failed : " << ex.what() << std::endl;
      stylesheet.reset();
    } // catch

    return std::auto_ptr<Stylesheet>(stylesheet.release());
  } // compile

  const std::string& error() const
  {
    return error_;
  } // error

private:
  std::string error_;
}; // class StylesheetCompiler

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_STYLESHEETCOMPILER_HPP

