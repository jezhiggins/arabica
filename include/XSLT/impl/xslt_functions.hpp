#ifndef ARABICA_XSLT_FUNCTIONS_HPP
#define ARABICA_XSLT_FUNCTIONS_HPP

#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

namespace Arabica
{
namespace XSLT
{

// node-set document(object, node-set?)
template<class string_type, class string_adaptor>
class DocumentFunction : public Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;

  typedef Arabica::XPath::XPathValue<string_type, string_adaptor> XPathValue;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;

  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
  
public:
  static const string_type& name()
  {
    static const string_type n = string_adaptor::construct_from_utf8("document");
    return n;
  } // name

  DocumentFunction(const string_type& currentBase, 
                   const ArgList& args) :
      baseT(1, 2, args),
      baseURI_(currentBase)
  { } 

protected:
  virtual NodeSet doEvaluate(const DOMNode& context,
                             const XPathExecutionContext& executionContext) const
  {
    NodeSet nodes;
     
    XPathValue a0 = this->arg(0, context, executionContext);
    if(baseT::argCount() != 1)
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

    Arabica::io::URI base(string_adaptor::asStdString(baseURI_));
    Arabica::io::URI absolute(base, string_adaptor::asStdString(location));
    SAX::InputSource<string_type, string_adaptor> is(string_adaptor::construct_from_utf8(absolute.as_string().c_str()));
    domParser.parse(is);

    if(!eh.errorsReported())
      nodes.push_back(domParser.getDocument());
    else
      std::cerr << eh.errors() << std::endl;
  } // load_document

  string_type baseURI_; 
}; // DocumentFunction

// node-set key(string, object)
template<class string_type, class string_adaptor>
class KeyFunction : public Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;
  typedef Arabica::XPath::XPathValue<string_type, string_adaptor> XPathValue;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
  typedef XML::QualifiedName<string_type, string_adaptor> QualifiedName;
public:
  static const string_type& name()
  {
    static const string_type n = string_adaptor::construct_from_utf8("key");
    return n;
  } // name

  KeyFunction(const DeclaredKeys<string_type, string_adaptor>& keys,
              const std::map<string_type, string_type>& inscopeNamespaces,	      
              const ArgList& args) :
    baseT(2, 2, args),
    keys_(keys),
    namespaces_(inscopeNamespaces)
  { 
  } // KeyFunction

protected:
  virtual NodeSet doEvaluate(const DOMNode& context,
                             const XPathExecutionContext& executionContext) const
  {
    string_type keyname      = this->argAsString(0, context, executionContext);
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
template<class string_type, class string_adaptor>
class CurrentFunction : public Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::NodeSetXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
public:
  static const string_type& name()
  {
    static const string_type n = string_adaptor::construct_from_utf8("current");
    return n;
  } // name

  CurrentFunction(const ArgList& args) :
    baseT(0, 0, args) { }

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
template<class string_type, class string_adaptor>
class UnparsedEntityUriFunction : public Arabica::XPath::StringXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::StringXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
public:
  static const string_type& name()
  {
    static const string_type n = string_adaptor::construct_from_utf8("unparsed-entity-uri");
    return n;
  } // name

  UnparsedEntityUriFunction(const ArgList& args) :
    baseT(1, 1, args) { }

protected:
  virtual string_type doEvaluate(const DOMNode& /* context */, 
                                 const XPathExecutionContext& /* executionContext */) const
  {
    // This is a minimal, but I think conformant, implementation
    return string_adaptor::empty_string();
  } // evaluate
}; // UnparsedEntityUri

// string generate-id(node-set?)
template<class string_type, class string_adaptor>
class GenerateIdFunction : public Arabica::XPath::StringXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::StringXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;
  typedef Arabica::XPath::NodeSet<string_type, string_adaptor> NodeSet;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
public:
  static const string_type& name()
  {
    static const string_type n = string_adaptor::construct_from_utf8("generate-id");
    return n;
  } // name

  GenerateIdFunction(const ArgList& args) :
    baseT(0, 1, args) { }

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
        return string_adaptor::empty_string();
      node = ns.top();
    } // if ...

    std::basic_ostringstream<typename string_adaptor::value_type> os;
    os << node.underlying_impl();
    return string_adaptor::construct(os.str());
  } // doEvaluate
}; // class GenerateIdFunction

// object system-property(string)
template<class string_type, class string_adaptor>
class SystemPropertyFunction : public Arabica::XPath::StringXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::StringXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
public:
  static const string_type& name()
  {
    static const string_type n = string_adaptor::construct_from_utf8("system-property");
    return n;
  } // name

  SystemPropertyFunction (const ArgList& args) :
      baseT(1, 1, args) { }

protected:
  virtual string_type doEvaluate(const DOMNode& context, 
                                 const XPathExecutionContext& executionContext) const
  {
    typedef StylesheetConstant<string_type, string_adaptor> SC;

    string_type property = baseT::argAsString(0, context, executionContext);
    string_type result;
    if(property == SC::version_property)
      return SC::Version;
    if(property == SC::vendor_property)
      return SC::Vendor;
    else if(property == SC::vendor_url_property)
      return SC::VendorUrl;
    return string_adaptor::empty_string();
  } // evaluate
}; // SystemPropertyFunction

// boolean element-available(string)
template<class string_type, class string_adaptor>
class ElementAvailableFunction : public Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
  typedef XML::QualifiedName<string_type, string_adaptor> QualifiedName;
public:
  static const string_type& name()
  {
    static const string_type n = string_adaptor::construct_from_utf8("element-available");
    return n;
  } // name

  ElementAvailableFunction(const std::vector<std::pair<string_type, string_type> >& names,
			                     const std::map<string_type, string_type>& inscopeNamespaces,
			                     const ArgList& args) :
    baseT(1, 1, args),
    namespaces_(inscopeNamespaces),
    elementNames_(names)
  {
  } // ElementAvailableFunction

protected:
  virtual bool doEvaluate(const DOMNode& context,
			                    const XPathExecutionContext& executionContext) const
  {
    typedef StylesheetConstant<string_type, string_adaptor> SC;

    const string_type functionName = baseT::argAsString(0, context, executionContext);
    const QualifiedName expandedName = QualifiedName::parseQName(functionName, true, namespaces_);

    if((expandedName.namespaceUri() != StylesheetConstant<string_type, string_adaptor>::NamespaceURI) &&
       (!string_adaptor::empty(expandedName.namespaceUri())))
      return false;

    static string_type XSLTNames[] = { SC::apply_imports, 
                                       SC::apply_templates, 
                                       SC::attribute, 
				                               SC::call_template, 
                                       SC::choose, 
                                       SC::comment, 
                                       SC::copy, 
				                               SC::copy_of, 
                                       SC::element, 
                                       SC::fallback, 
                                       SC::for_each, 
				                               SC::if_, 
                                       SC::message, 
                                       SC::number, 
                                       SC::processing_instruction,
				                               SC::text, 
                                       SC::value_of, 
                                       SC::variable, 
                                       string_adaptor::empty_string() };

    for(int i = 0; XSLTNames[i] != string_adaptor::empty_string(); ++i)
      if(expandedName.localName() == XSLTNames[i])
        return true;
    
    return false;
  } // doEvaluate

private:
  const std::map<string_type, string_type> namespaces_;
  std::vector<std::pair<string_type, string_type> > elementNames_;
}; // class ElementAvailableFunction

// boolean function-available(string)
template<class string_type, class string_adaptor>
class FunctionAvailableFunction : public Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
  typedef XML::QualifiedName<string_type, string_adaptor> QualifiedName;
public:
  static const string_type& name()
  {
    static const string_type n = string_adaptor::construct_from_utf8("function-available");
    return n;
  } // name

  FunctionAvailableFunction(const std::vector<std::pair<string_type, string_type> >& names, 
			                      const std::map<string_type, string_type>& inscopeNamespaces,
			                      const ArgList& args) :
    baseT(1, 1, args),
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

template<class string_type, class string_adaptor>
class UndefinedFunction : public Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor>
{
  typedef Arabica::XPath::BooleanXPathFunction<string_type, string_adaptor> baseT;

  typedef Arabica::XPath::XPathExpression<string_type, string_adaptor> XPathExpression;
  typedef std::vector<XPathExpression> ArgList;
  typedef Arabica::XPath::ExecutionContext<string_type, string_adaptor> XPathExecutionContext;
  typedef DOM::Node<string_type, string_adaptor> DOMNode;
public:
  UndefinedFunction(const string_type namespace_uri,
            		    const string_type name,
		                const ArgList& args) :
    baseT(-1, -1, args)
  {
    typedef Arabica::text::Unicode<typename string_adaptor::value_type> UnicodeT;

    if(!string_adaptor::empty(namespace_uri))
    {
      string_adaptor::append(error_, UnicodeT::LEFT_SQUARE_BRACKET);
      string_adaptor::append(error_, namespace_uri);
      string_adaptor::append(error_, UnicodeT::RIGHT_SQUARE_BRACKET);
    } // if .. 

    string_adaptor::append(error_, name);
  } // UndefinedFunction

protected:
  virtual bool doEvaluate(const DOMNode&, const XPathExecutionContext&) const
  {
    throw Arabica::XPath::UndefinedFunctionException(string_adaptor::asStdString(error_));
  } // doEvaluate

  string_type error_;
}; // class UndefinedFunction

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_FUNCTIONS_HPP


