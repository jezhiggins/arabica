#ifndef ARABICA_XSLT_STYLESHEETCONSTANT_HPP
#define ARABICA_XSLT_STYLESHEETCONSTANT_HPP

#include <XML/XMLCharacterClasses.hpp>
#include <XPath/impl/xpath_namespace_context.hpp>
#include <memory>

#include "xslt_stylesheet_parser.hpp"
#include "xslt_stylesheet.hpp"
#include "xslt_compilation_context.hpp"
#include "xslt_functions.hpp"
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
    top_(true)
  {
    context_.root(*this);
    includer_.context(context_, this);      
  } // StylesheetHandler

  virtual void startElement(const std::string& namespaceURI,
                            const std::string& localName,
                            const std::string& qName,
                            const SAX::Attributes<std::string>& atts)
  {
    if(top_)
    {
      if(namespaceURI != StylesheetConstant::NamespaceURI())
        throw SAX::SAXException("The source file does not look like a stylesheet.");
      if(localName != "stylesheet" && localName != "transform")
        throw SAX::SAXException("Top-level element must be 'stylesheet' or 'transform'.");
      if(atts.getValue("version") == "")
        throw SAX::SAXException("stylesheet element must have a version attribute.");
      if(atts.getValue("version") != StylesheetConstant::Version())
        throw SAX::SAXException("I'm only a poor version 1.0 XSLT Transformer.");

      top_ = false;

      return;
    } // if(stylesheet_ == 0)

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

    throw SAX::SAXException("xsl:stylesheet does not allow " + qName + " here.");
  } // startElement

  virtual void endElement(const std::string& namespaceURI,
                          const std::string& localName,
                          const std::string& qName)
  {
  } // endElement

  virtual void characters(const std::string& ch)
  {
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

class StylesheetCompiler :
    private Arabica::XPath::FunctionResolver<std::string>,
    private Arabica::XPath::NamespaceContext<std::string, Arabica::default_string_adaptor<std::string> >
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

    Arabica::XPath::XPath<std::string> xpathCompiler;
    xpathCompiler.setNamespaceContext(*this);
    xpathCompiler.setFunctionResolver(*this);

    std::auto_ptr<Stylesheet> stylesheet(new Stylesheet());

    CompilationContext context(parser_, 
                               xpathCompiler,
                               *stylesheet.get());

    StylesheetHandler stylesheetHandler(context);

    parser_.setContentHandler(stylesheetHandler);
    //parser_.setErrorHandler(*this);
  
    //if(entityResolver_)
    //  parser_.setEntityResolver(*entityResolver_);
    try {
      parser_.parse(source);
    } // try
    catch(std::exception& ex)
    {
      error_ = ex.what();
      //std::cerr << "Compilation Failed : " << ex.what() << std::endl;
      stylesheet.reset();
    } // catch

    return stylesheet;
  } // compile

  const std::string& error() const
  {
    return error_;
  } // error

private:
  virtual void fatalError(const SAX::SAXException& exception)
  {
    std::cerr << "Error: " << exception.what() << std::endl;
    stylesheet_.reset();
  } // fatalError

  // FunctionResolver 
  virtual Arabica::XPath::XPathFunction<std::string>* resolveFunction(
                                         const std::string& namespace_uri, 
                                         const std::string& name,
                                         const std::vector<Arabica::XPath::XPathExpression<std::string> >& argExprs) const
  {
    if(!namespace_uri.empty())
      return 0;

    // document
    if(name == "document")
      return new DocumentFunction(parser_.currentBase(), argExprs);
    // key
    // format-number
    if(name == "current")
      return new CurrentFunction(argExprs);
    // unparsed-entity-uri
    // generate-id
    if(name == "system-property")
      return new SystemPropertyFunction(argExprs);
    return 0;
  } // resolveFunction

  // NamespaceContext 
  virtual std::string namespaceURI(const std::string& prefix) const
  {
    return parser_.namespaceURI(prefix);
  } // namespaceURI

  StylesheetParser parser_;
  std::auto_ptr<Stylesheet> stylesheet_;
  std::string error_;
}; // class StylesheetCompiler

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_STYLESHEETCOMPILER_HPP

