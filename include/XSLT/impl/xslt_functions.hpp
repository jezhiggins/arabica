#ifndef ARABICA_XSLT_FUNCTIONS_HPP
#define ARABICA_XSLT_FUNCTIONS_HPP

#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

namespace Arabica
{
namespace XSLT
{

// node-set current()
class CurrentFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  CurrentFunction(const std::vector<Arabica::XPath::XPathExpressionPtr<std::string> >& args) :
      Arabica::XPath::XPathFunction<std::string>(0, 0, args) { }

  virtual Arabica::XPath::XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context, 
                                            const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    Arabica::XPath::NodeSet<std::string> set;
    set.push_back(executionContext.currentNode());
    return new Arabica::XPath::NodeSetValue<std::string>(set);
  } // evaluate
}; // CurrentFunction

// node-set document(object, node-set?)
class DocumentFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  DocumentFunction(const std::string& currentBase, 
                   const std::vector<Arabica::XPath::XPathExpressionPtr<std::string> >& args) :
      Arabica::XPath::XPathFunction<std::string>(1, 2, args),
      baseURI_(currentBase)
  { } 

  virtual Arabica::XPath::XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    Arabica::XPath::NodeSet<std::string> nodes;
     
    Arabica::XPath::XPathValuePtr<std::string> a1 = arg(0, context, executionContext);
    if(a1->type() != Arabica::XPath::NODE_SET)
      load_document(a1->asString(), nodes);
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

// object system-property(string)
class SystemPropertyFunction : public Arabica::XPath::XPathFunction<std::string>
{
  typedef Arabica::XPath::XPathFunction<std::string> baseT;

public:
  SystemPropertyFunction (const std::vector<Arabica::XPath::XPathExpressionPtr<std::string> >& args) :
      Arabica::XPath::XPathFunction<std::string>(1, 1, args) { }

  virtual Arabica::XPath::XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context, 
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


} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_FUNCTIONS_HPP


