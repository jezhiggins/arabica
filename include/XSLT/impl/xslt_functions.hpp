#ifndef ARABICA_XSLT_FUNCTIONS_HPP
#define ARABICA_XSLT_FUNCTIONS_HPP

#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

namespace Arabica
{
namespace XSLT
{

template<class string_type, class string_adaptor>
class Functions
{
public:

typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
typedef std::vector<XPathExpression> ArgList;

typedef Arabica::XPath::XPathValue<string_type, string_adaptor> XPathValue;

typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;

typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
typedef DOM::Node<string_type, string_adaptor> DOMNode;

typedef XML::QualifiedName<string_type, string_adaptor> QualifiedName;

// node-set document(object, node-set?)
class DocumentFunction : public Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor> baseT;

public:
  DocumentFunction(const string_type& currentBase, 
                   const ArgList& args) :
      Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>(1, 2, args),
      baseURI_(currentBase)
  { } 

protected:
  virtual NodeSet doEvaluate(const DOMNode& context,
                             const XPathExecutionContext& executionContext) const
  {
    NodeSet nodes;
     
    XPathValue a0 = arg(0, context, executionContext);
    if(argCount() != 1)
      throw Arabica::XPath::UnsupportedException("two arg version of document()");
    if(a0.type() != Arabica::XPath::STRING)
      throw Arabica::XPath::UnsupportedException("node-set arg version of document()");

    load_document(a0.asString(), nodes);
    return nodes;
  } // doEvaluate

private:
  void load_document(const string_type& location, NodeSet& nodes) const
  {
    SAX2DOM::Parser<string_type, string_adaptor> domParser;
    SAX::CatchErrorHandler<string_type, string_adaptor> eh;
    domParser.setErrorHandler(eh);

    Arabica::io::URI base(baseURI_);
    Arabica::io::URI absolute(base, location);

    SAX::InputSource<string_type, string_adaptor> is(absolute.as_string());
    domParser.parse(is);

    if(!eh.errorsReported())
      nodes.push_back(domParser.getDocument());
    else
      std::cerr << eh.errors() << std::endl;
  } // load_document

  string_type baseURI_; 
}; // DocumentFunction

// node-set key(string, object)
class KeyFunction : public Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor> baseT;
public:
  KeyFunction(const DeclaredKeys<string_type, string_adaptor>& keys,
              const std::map<string_type, string_type>& inscopeNamespaces,	      
              const ArgList& args) :
    Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>(2, 2, args),
    keys_(keys),
    namespaces_(inscopeNamespaces)
  { 
  } // KeyFunction

protected:
  virtual NodeSet doEvaluate(const DOMNode& context,
                             const XPathExecutionContext& executionContext) const
  {
    string_type keyname = argAsString(0, context, executionContext);
    string_type keyClarkName = QualifiedName::parseQName(keyname, true, namespaces_).clarkName();

    XPathValue a1 = baseT::arg(1, context, executionContext);
    if(a1.type() == Arabica::XPath::NODE_SET)
      return nodeSetUnion(keyClarkName, a1.asNodeSet(), executionContext);

    return keys_.lookup(keyClarkName, a1.asString(), executionContext);
  } // doEvaluate

  NodeSet nodeSetUnion(const string_type& keyClarkName, 
                       const NodeSet nodes,
			      			     const XPathExecutionContext& executionContext) const
  {
    NodeSet results;
    for(typename NodeSet::const_iterator n = nodes.begin(), ne = nodes.end(); n != ne; ++n)
    {
      string_type id = Arabica::XPath::impl::nodeStringValue<string_type, string_adaptor>(*n);
      results.push_back(keys_.lookup(keyClarkName, id, executionContext));
    } // for ...
    results.to_document_order();
    return results;
  } // nodeSetUnion

private:
  const DeclaredKeys<string_type, string_adaptor>& keys_;
  std::map<string_type, string_type> namespaces_;

}; // class KeyFunction

// string format-number(number, string, string?)

// node-set current()
class CurrentFunction : public Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor> baseT;
public:
  CurrentFunction(const ArgList& args) :
      Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>(0, 0, args) { }

protected:
  virtual NodeSet doEvaluate(const DOMNode& /* context */, 
							               const XPathExecutionContext& executionContext) const
  {
    NodeSet set;
    set.push_back(executionContext.currentNode());
    return set;
  } // doEvaluate
}; // CurrentFunction

// string unparsed-entity-uri(string)
class UnparsedEntityUriFunction : public Arabica::XPath::StringXPathFunction<string_type, string_adaptor>
{
public:
  UnparsedEntityUriFunction(const ArgList& args) :
    Arabica::XPath::StringXPathFunction<string_type, string_adaptor>(1, 1, args) { }

protected:
  virtual string_type doEvaluate(const DOMNode& /* context */, 
                                 const XPathExecutionContext& /* executionContext */) const
  {
    // This is a minimal, but I think conformant, implementation
    return "";
  } // evaluate
}; // UnparsedEntityUri

// string generate-id(node-set?)
class GenerateIdFunction : public Arabica::XPath::StringXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::StringXPathFunction<string_type, string_adaptor> baseT;
public:
  GenerateIdFunction(const ArgList& args) :
    Arabica::XPath::StringXPathFunction<string_type, string_adaptor>(0, 1, args) { }

protected:
  virtual string_type doEvaluate(const DOMNode& context, 
                                 const XPathExecutionContext& executionContext) const
  {
    DOMNode node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      NodeSet ns = baseT::argAsNodeSet(0, context, executionContext);
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
class SystemPropertyFunction : public Arabica::XPath::StringXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::StringXPathFunction<string_type, string_adaptor> baseT;
public:
  SystemPropertyFunction (const ArgList& args) :
      Arabica::XPath::StringXPathFunction<string_type, string_adaptor>(1, 1, args) { }

protected:
  virtual string_type doEvaluate(const DOMNode& context, 
                                 const XPathExecutionContext& executionContext) const
  {
    string_type property = baseT::argAsString(0, context, executionContext);
    string_type result;
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
class ElementAvailableFunction : public Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor> baseT;
public:
  ElementAvailableFunction(const std::vector<std::pair<string_type, string_type> >& names,
			                     const std::map<string_type, string_type>& inscopeNamespaces,
			                     const ArgList& args) :
    Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>(1, 1, args),
    namespaces_(inscopeNamespaces),
    elementNames_(names)
  {
  } // ElementAvailableFunction

protected:
  virtual bool doEvaluate(const DOMNode& context,
			                    const XPathExecutionContext& executionContext) const
  {
    const string_type functionName = baseT::argAsString(0, context, executionContext);
    const QualifiedName expandedName = QualifiedName::parseQName(functionName, true, namespaces_);

    if((expandedName.namespaceUri() != StylesheetConstant::NamespaceURI()) &&
       (!expandedName.namespaceUri().empty()))
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
  const std::map<string_type, string_type> namespaces_;
  std::vector<std::pair<string_type, string_type> > elementNames_;
}; // class ElementAvailableFunction

// boolean function-available(string)
class FunctionAvailableFunction : public Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor> baseT;
public:
  FunctionAvailableFunction(const std::vector<std::pair<string_type, string_type> >& names, 
			                      const std::map<string_type, string_type>& inscopeNamespaces,
			                      const ArgList& args) :
    Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>(1, 1, args),
    namespaces_(inscopeNamespaces),
    functionNames_(names)
  { 
    Arabica::XPath::StandardXPathFunctionResolver<string_type, string_adaptor> standardResolver;
    const std::vector<std::pair<string_type, string_type> > standardNames = standardResolver.validNames();
    functionNames_.insert(functionNames_.begin(), standardNames.begin(), standardNames.end());
  } // FunctionAvailableFunction

protected:
  virtual bool doEvaluate(const DOMNode& context,
			  const XPathExecutionContext& executionContext) const
  {
    const string_type functionName = baseT::argAsString(0, context, executionContext);
    const QualifiedName expandedName = QualifiedName::parseQName(functionName, true, namespaces_);

    const std::pair<string_type, string_type> name_to_check = std::make_pair(expandedName.namespaceUri(), expandedName.localName());

    return (std::find(functionNames_.begin(), functionNames_.end(), name_to_check) != functionNames_.end());
  } // doEvaluate

private:
  const std::map<string_type, string_type> namespaces_;
  std::vector<std::pair<string_type, string_type> > functionNames_;
}; // class FunctionAvailableFunction

class UndefinedFunction : public Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>
{
public:
  UndefinedFunction(const string_type namespace_uri,
		    const string_type name,
		    const ArgList& args) :
    Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>(-1, -1, args)
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
  virtual bool doEvaluate(const DOMNode&,
			  const XPathExecutionContext&) const
  {
    throw Arabica::XPath::UndefinedFunctionException(error_);
  } // doEvaluate

  string_type error_;
}; // class UndefinedFunction

}; // class Functions

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_FUNCTIONS_HPP


