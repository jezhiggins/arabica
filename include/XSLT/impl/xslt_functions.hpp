#ifndef ARABICA_XSLT_FUNCTIONS_HPP
#define ARABICA_XSLT_FUNCTIONS_HPP

#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

namespace Arabica
{
namespace XSLT
{

// node-set document(object, node-set?)
class DocumentFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  DocumentFunction(const std::string& currentBase, 
                   const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
      Arabica::XPath::XPathFunction<std::string>(1, 2, args),
      baseURI_(currentBase)
  { } 

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::NODE_SET; }

  virtual Arabica::XPath::XPathValue_impl<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    Arabica::XPath::NodeSet<std::string> nodes;
     
    Arabica::XPath::XPathValue<std::string> a0 = arg(0, context, executionContext);
    if(a0.type() != Arabica::XPath::NODE_SET)
      load_document(a0.asString(), nodes);
    else 
      throw Arabica::XPath::UnsupportedException("node-set arg version of document()");
    return new Arabica::XPath::NodeSetValue<std::string>(nodes);
  } // evaluate

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
class KeyFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  KeyFunction(const DeclaredKeys& keys,
              const std::map<std::string, std::string>& inscopeNamespaces,	      
              const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::XPathFunction<std::string>(2, 2, args),
    keys_(keys),
    namespaces_(inscopeNamespaces)
  { 
  } // KeyFunction

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::NODE_SET; }

  virtual Arabica::XPath::XPathValue_impl<std::string>* evaluate(const DOM::Node<std::string>& context,
                                                                 const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    std::string keyname = argAsString(0, context, executionContext);
    std::string keyClarkName = XML::QualifiedName<std::string>::parseQName(keyname, true, UriMapper(namespaces_)).clarkName();

    Arabica::XPath::XPathValue<std::string> a1 = baseT::arg(1, context, executionContext);
    if(a1.type() == Arabica::XPath::NODE_SET)
      return nodeSetUnion(keyClarkName, a1.asNodeSet(), executionContext);

    return new Arabica::XPath::NodeSetValue<std::string>(keys_.lookup(keyClarkName, a1.asString(), executionContext));
  } // evaluate

  Arabica::XPath::XPathValue_impl<std::string>* nodeSetUnion(const std::string& keyClarkName, 
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
    return new Arabica::XPath::NodeSetValue<std::string>(results);
  } // nodeSetUnion

private:
  const DeclaredKeys& keys_;
  std::map<std::string, std::string> namespaces_;

  class UriMapper
  {
  public:
    UriMapper(const std::map<std::string, std::string>& namespaces) : namespaces_(namespaces) { }

    std::string operator()(const std::string& prefix) const
    {
      std::map<std::string, std::string>::const_iterator ns = namespaces_.find(prefix);
      if(ns == namespaces_.end())
        return "";
      return ns->second;
    } //operator()

  private:
    const std::map<std::string, std::string>& namespaces_;

    UriMapper(const UriMapper&);
  }; // class UriMapper

}; // class KeyFunction

// string format-number(number, string, string?)

// node-set current()
class CurrentFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  CurrentFunction(const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
      Arabica::XPath::XPathFunction<std::string>(0, 0, args) { }

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::NODE_SET; }

  virtual Arabica::XPath::XPathValue_impl<std::string>* evaluate(const DOM::Node<std::string>& context, 
                                                                 const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    Arabica::XPath::NodeSet<std::string> set;
    set.push_back(executionContext.currentNode());
    return new Arabica::XPath::NodeSetValue<std::string>(set);
  } // evaluate
}; // CurrentFunction

// string unparsed-entity-uri(string)
class UnparsedEntityUriFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  UnparsedEntityUriFunction(const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::XPathFunction<std::string>(1, 1, args) { }

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::STRING; }

  virtual Arabica::XPath::XPathValue_impl<std::string>* evaluate(const DOM::Node<std::string>& context, 
                                            const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    // This is a minimal, but I think conformant, implementation
    return new Arabica::XPath::StringValue<std::string>("");
  } // evaluate
}; // UnparsedEntityUri

// string generate-id(node-set?)
class GenerateIdFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  GenerateIdFunction(const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
    Arabica::XPath::XPathFunction<std::string>(0, 1, args) { }

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::STRING; }

  virtual Arabica::XPath::XPathValue_impl<std::string>* evaluate(const DOM::Node<std::string>& context, 
                                            const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    DOM::Node<std::string> node;
    if(baseT::argCount() == 0)
      node = context;
    else
    {
      Arabica::XPath::NodeSet<std::string> ns = baseT::argAsNodeSet(0, context, executionContext);
      if(ns.size() == 0)
        return new Arabica::XPath::StringValue<std::string>("");
      node = ns.top();
    } // if ...

    std::ostringstream os;
    os << node.underlying_impl();
    return new Arabica::XPath::StringValue<std::string>(os.str());
  } //evaluate
}; // class GenerateIdFunction

// object system-property(string)
class SystemPropertyFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  SystemPropertyFunction (const std::vector<Arabica::XPath::XPathExpression<std::string> >& args) :
      Arabica::XPath::XPathFunction<std::string>(1, 1, args) { }

  virtual Arabica::XPath::ValueType type() const { return Arabica::XPath::STRING; }

  virtual Arabica::XPath::XPathValue_impl<std::string>* evaluate(const DOM::Node<std::string>& context, 
                                            const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    std::string property = baseT::argAsString(0, context, executionContext);
    std::string result;
    if(property == "xsl:version")
      result = "1.0";
    else if(property == "xsl:vendor")
      result = "Jez Higgins, Jez UK Ltd";
    else if(property == "xsl:vendor-url")
      result = "http://www.jezuk.co.uk/arabica";
    return new Arabica::XPath::StringValue<std::string>(result);
  } // evaluate
}; // SystemPropertyFunction

// boolean element-available(string)
// boolean function-available(string)

} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_FUNCTIONS_HPP


