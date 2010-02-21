#ifndef ARABICA_XSLT_FUNCTIONS_HPP
#define ARABICA_XSLT_FUNCTIONS_HPP

#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

namespace Arabica
{
namespace XSLT
{

// node-set document(object, node-set?)
class DocumentFunction : public Arabica::XPath::NodeSetXPathFunction<std::string>
{
  typedef Arabica::XPath::NodeSetXPathFunction<std::string> baseT;

public:
  DocumentFunction(const std::string& currentBase, 
                   const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
      Arabica::XPath::NodeSetXPathFunction<std::string>(1, 2, args),
      baseURI_(currentBase)
  { } 

protected:
  virtual Arabica::XPath::NodeSet<std::string> doEvaluate(const DOM::Node<std::string>& context,
                                                          const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    Arabica::XPath::NodeSet<std::string> nodes;
     
    Arabica::XPath::XPathValue<std::string> a0 = arg(0, context, executionContext);
    if(argCount() != 1)
      throw Arabica::XPath::UnsupportedException("two arg version of document()");
    if(a0.type() != Arabica::XPath::STRING)
      throw Arabica::XPath::UnsupportedException("node-set arg version of document()");

    load_document(a0.asString(), nodes);
    return nodes;
  } // doEvaluate

private:
  void load_document(const std::string& location,
                     Arabica::XPath::NodeSet<std::string>& nodes) const
  {
    SAX2DOM::Parser<std::string> domParser;
    SAX::CatchErrorHandler<std::string> eh;
    domParser.setErrorHandler(eh);

    Arabica::io::URI base(baseURI_);
    Arabica::io::URI absolute(base, location);

    SAX::InputSource<std::string> is(absolute.as_string());
    domParser.parse(is);

    if(!eh.errorsReported())
        nodes.push_back(domParser.getDocument());
    else
        std::cerr << eh.errors() << std::endl;
  } // load_document

  std::string baseURI_; 
}; // DocumentFunction

// node-set key(string, object)
class KeyFunction : public Arabica::XPath::NodeSetXPathFunction<std::string>
{
  typedef Arabica::XPath::NodeSetXPathFunction<std::string> baseT;
public:
  KeyFunction(const DeclaredKeys& keys,
              const std::map<std::string, std::string>& inscopeNamespaces,	      
              const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::NodeSetXPathFunction<std::string>(2, 2, args),
    keys_(keys),
    namespaces_(inscopeNamespaces)
  { 
  } // KeyFunction

protected:
  virtual Arabica::XPath::NodeSet<std::string> doEvaluate(const DOM::Node<std::string>& context,
                                                          const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    std::string keyname = argAsString(0, context, executionContext);
    std::string keyClarkName = XML::QualifiedName<std::string>::parseQName(keyname, true, namespaces_).clarkName();

    Arabica::XPath::XPathValue<std::string> a1 = baseT::arg(1, context, executionContext);
    if(a1.type() == Arabica::XPath::NODE_SET)
      return nodeSetUnion(keyClarkName, a1.asNodeSet(), executionContext);

    return keys_.lookup(keyClarkName, a1.asString(), executionContext);
  } // doEvaluate

  Arabica::XPath::NodeSet<std::string> nodeSetUnion(const std::string& keyClarkName, 
							     const Arabica::XPath::NodeSet<std::string> nodes,
							     const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    Arabica::XPath::NodeSet<std::string> results;
    for(Arabica::XPath::NodeSet<std::string>::const_iterator n = nodes.begin(), ne = nodes.end(); n != ne; ++n)
    {
      std::string id = Arabica::XPath::impl::nodeStringValue<std::string, Arabica::default_string_adaptor<std::string> >(*n);
      results.push_back(keys_.lookup(keyClarkName, id, executionContext));
    } // for ...
    results.to_document_order();
    return results;
  } // nodeSetUnion

private:
  const DeclaredKeys& keys_;
  std::map<std::string, std::string> namespaces_;

}; // class KeyFunction

// string format-number(number, string, string?)

// node-set current()
class CurrentFunction : public Arabica::XPath::NodeSetXPathFunction<std::string>
{
  typedef Arabica::XPath::NodeSetXPathFunction<std::string> baseT;
public:
  CurrentFunction(const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
      Arabica::XPath::NodeSetXPathFunction<std::string>(0, 0, args) { }

protected:
  virtual Arabica::XPath::NodeSet<std::string> doEvaluate(const DOM::Node<std::string>& /* context */, 
							  const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    Arabica::XPath::NodeSet<std::string> set;
    set.push_back(executionContext.currentNode());
    return set;
  } // doEvaluate
}; // CurrentFunction

// string unparsed-entity-uri(string)
class UnparsedEntityUriFunction : public Arabica::XPath::StringXPathFunction<std::string>
{
public:
  UnparsedEntityUriFunction(const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::StringXPathFunction<std::string>(1, 1, args) { }

protected:
  virtual std::string doEvaluate(const DOM::Node<std::string>& /* context */, 
                                 const Arabica::XPath::ExecutionContext<std::string>& /* executionContext */) const
  {
    // This is a minimal, but I think conformant, implementation
    return "";
  } // evaluate
}; // UnparsedEntityUri

// string generate-id(node-set?)
class GenerateIdFunction : public Arabica::XPath::StringXPathFunction<std::string>
{
  typedef Arabica::XPath::StringXPathFunction<std::string> baseT;
public:
  GenerateIdFunction(const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::StringXPathFunction<std::string>(0, 1, args) { }

protected:
  virtual std::string doEvaluate(const DOM::Node<std::string>& context, 
                                 const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    DOM::Node<std::string> node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      Arabica::XPath::NodeSet<std::string> ns = baseT::argAsNodeSet(0, context, executionContext);
      if(ns.size() == 0)
        return "";
      node = ns.top();
    } // if ...

    std::ostringstream os;
    os << node.underlying_impl();
    return os.str();
  } // doEvaluate
}; // class GenerateIdFunction

// object system-property(string)
class SystemPropertyFunction : public Arabica::XPath::StringXPathFunction<std::string>
{
  typedef Arabica::XPath::StringXPathFunction<std::string> baseT;
public:
  SystemPropertyFunction (const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
      Arabica::XPath::StringXPathFunction<std::string>(1, 1, args) { }

protected:
  virtual std::string doEvaluate(const DOM::Node<std::string>& context, 
                                 const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    std::string property = baseT::argAsString(0, context, executionContext);
    std::string result;
    if(property == "xsl:version")
      return "1.0";
    if(property == "xsl:vendor")
      return "Jez Higgins, Jez UK Ltd";
    else if(property == "xsl:vendor-url")
      return "http://www.jezuk.co.uk/arabica";
    return "";
  } // evaluate
}; // SystemPropertyFunction

// boolean element-available(string)
class ElementAvailableFunction : public Arabica::XPath::BooleanXPathFunction<std::string>
{
  typedef Arabica::XPath::BooleanXPathFunction<std::string> baseT;
public:
  ElementAvailableFunction(const std::vector<std::pair<std::string, std::string> >& names,
			   const std::map<std::string, std::string>& inscopeNamespaces,
			   const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::BooleanXPathFunction<std::string>(1, 1, args),
    namespaces_(inscopeNamespaces),
    elementNames_(names)
  {
  } // ElementAvailableFunction

protected:
  virtual bool doEvaluate(const DOM::Node<std::string>& context,
			  const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    const std::string functionName = baseT::argAsString(0, context, executionContext);
    const XML::QualifiedName<std::string> expandedName = XML::QualifiedName<std::string>::parseQName(functionName, true, namespaces_);

    if(expandedName.namespaceUri() != StylesheetConstant::NamespaceURI())
      return false;

    static const char* XSLTNames[] = { "apply-imports", "apply-templates", "attributes", 
				       "call-template", "choose", "comment", "copy", 
				       "copy-of", "element", "fallback", "for-each", 
				       "if", "message", "number", "processing-instruction",
				       "text", "value-of", "variable", 0 };

    for(int i = 0; XSLTNames[i] != 0; ++i)
      if(expandedName.localName() == XSLTNames[i])
	return true;
    
    return false;
  } // doEvaluate

private:
  const std::map<std::string, std::string> namespaces_;
  std::vector<std::pair<std::string, std::string> > elementNames_;
}; // class ElementAvailableFunction

// boolean function-available(string)
class FunctionAvailableFunction : public Arabica::XPath::BooleanXPathFunction<std::string>
{
  typedef Arabica::XPath::BooleanXPathFunction<std::string> baseT;
public:
  FunctionAvailableFunction(const std::vector<std::pair<std::string, std::string> >& names, 
			    const std::map<std::string, std::string>& inscopeNamespaces,
			    const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::BooleanXPathFunction<std::string>(1, 1, args),
    namespaces_(inscopeNamespaces),
    functionNames_(names)
  { 
    Arabica::XPath::StandardXPathFunctionResolver<std::string> standardResolver;
    const std::vector<std::pair<std::string, std::string> > standardNames = standardResolver.validNames();
    functionNames_.insert(functionNames_.begin(), standardNames.begin(), standardNames.end());
  } // FunctionAvailableFunction

protected:
  virtual bool doEvaluate(const DOM::Node<std::string>& context,
			  const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    const std::string functionName = baseT::argAsString(0, context, executionContext);
    const XML::QualifiedName<std::string> expandedName = XML::QualifiedName<std::string>::parseQName(functionName, true, namespaces_);

    const std::pair<std::string, std::string> name_to_check = std::make_pair(expandedName.namespaceUri(), expandedName.localName());

    return (std::find(functionNames_.begin(), functionNames_.end(), name_to_check) != functionNames_.end());
  } // doEvaluate

private:
  const std::map<std::string, std::string> namespaces_;
  std::vector<std::pair<std::string, std::string> > functionNames_;
}; // class FunctionAvailableFunction

class UndefinedFunction : public Arabica::XPath::BooleanXPathFunction<std::string>
{
public:
  UndefinedFunction(const std::string namespace_uri,
		    const std::string name,
		    const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::BooleanXPathFunction<std::string>(-1, -1, args)
  {
    if(!namespace_uri.empty())
    {
      error_ += "{";
      error_ += namespace_uri;
      error_ += "}";
    } // if .. 

    error_ += name;
  } // UndefinedFunction

protected:
  virtual bool doEvaluate(const DOM::Node<std::string>&,
			  const Arabica::XPath::ExecutionContext<std::string>&) const
  {
    throw Arabica::XPath::UndefinedFunctionException(error_);
  } // doEvaluate

  std::string error_;
}; // class UndefinedFunction

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_FUNCTIONS_HPP


