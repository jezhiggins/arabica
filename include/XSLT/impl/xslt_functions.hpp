#ifndef ARABICA_XSLT_FUNCTIONS_HPP
#define ARABICA_XSLT_FUNCTIONS_HPP

#include <DOM/SAX2DOM/SAX2DOM.h>
#include <SAX/helpers/CatchErrorHandler.h>

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
  DocumentFunction(const std::vector<Arabica::XPath::XPathExpressionPtr<std::string> >& args) :
      Arabica::XPath::XPathFunction<std::string>(1, 2, args)
  { } 

  /*
  The document function allows access to XML documents 
  other than the main source document.

  When the document function has exactly one argument and the 
  argument is a node-set, then the result is the union, for 
  each node in the argument node-set, of the result of calling 
  the document function with the first argument being the 
  string-value of the node, and the second argument being a 
  node-set with the node as its only member. When the document 
  function has two arguments and the first argument is a 
  node-set, then the result is the union, for each node in 
  the argument node-set, of the result of calling the document 
  function with the first argument being the string-value of 
  the node, and with the second argument being the second 
  argument passed to the document function.

  When the first argument to the document function is not 
  a node-set, the first argument is converted to a string 
  as if by a call to the string function. This string is 
  treated as a URI reference; the resource identified by 
  the URI is retrieved. The data resulting from the retrieval 
  action is parsed as an XML document and a tree is constructed 
  in accordance with the data model (see [3 Data Model]). 
  If there is an error retrieving the resource, then the 
  XSLT processor may signal an error; if it does not signal 
  an error, it must recover by returning an empty node-set. 
  One possible kind of retrieval error is that the XSLT 
  processor does not support the URI scheme used by the URI. 
  An XSLT processor is not required to support any 
  particular URI schemes. The documentation for an XSLT 
  processor should specify which URI schemes the XSLT 
  processor supports.

  If the URI reference does not contain a fragment 
  identifier, then a node-set containing just the root node 
  of the document is returned. If the URI reference does 
  contain a fragment identifier, the function returns a 
  node-set containing the nodes in the tree identified 
  by the fragment identifier of the URI reference. The 
  semantics of the fragment identifier is dependent on 
  the media type of the result of retrieving the URI. If 
  there is an error in processing the fragment identifier, 
  the XSLT processor may signal the error; if it does 
  not signal the error, it must recover by returning an 
  empty node-set. Possible errors include:

      * The fragment identifier identifies something that 
      cannot be represented by an XSLT node-set (such as a 
      range of characters within a text node).
      * The XSLT processor does not support fragment 
      identifiers for the media-type of the retrieval result. 
      An XSLT processor is not required to support any 
      particular media types. The documentation for an XSLT 
      processor should specify for which media types the 
      XSLT processor supports fragment identifiers.

  The data resulting from the retrieval action is parsed 
  as an XML document regardless of the media type of the 
  retrieval result; if the top-level media type is text, 
  then it is parsed in the same way as if the media type 
  were text/xml; otherwise, it is parsed in the same way 
  as if the media type were application/xml.

      NOTE:Since there is no top-level xml media type, 
      data with a media type other than text/xml or 
      application/xml may in fact be XML.

  The URI reference may be relative. The base URI (see 
  [3.2 Base URI]) of the node in the second argument 
  node-set that is first in document order is used as the 
  base URI for resolving the relative URI into an 
  absolute URI. If the second argument is omitted, then 
  it defaults to the node in the stylesheet that 
  contains the expression that includes the call to 
  the document function. Note that a zero-length URI 
  reference is a reference to the document relative to 
  which the URI reference is being resolved; thus 
  document("") refers to the root node of the stylesheet; 
  the tree representation of the stylesheet is exactly 
  the same as if the XML document containing the stylesheet 
  was the initial source document.

  Two documents are treated as the same document if they 
  are identified by the same URI. The URI used for the 
  comparison is the absolute URI into which any relative 
  URI was resolved and does not include any fragment 
  identifier. One root node is treated as the same node 
  as another root node if the two nodes are from the 
  same document. Thus, the following expression will 
  always be true:

  generate-id(document("foo.xml"))=generate-id(document("foo.xml"))

  The document function gives rise to the possibility that 
  a node-set may contain nodes from more than one document. 
  With such a node-set, the relative document order of 
  two nodes in the same document is the normal document order 
  defined by XPath [XPath]. The relative document order of two 
  nodes in different documents is determined by an 
  implementation-dependent ordering of the documents 
  containing the two nodes. There are no constraints on how 
  the implementation orders documents other than that it must 
  do so consistently: an implementation must always use the 
  same order for the same set of documents.
  */
  virtual Arabica::XPath::XPathValue<std::string>* evaluate(const DOM::Node<std::string>& context,
                                            const Arabica::XPath::ExecutionContext<std::string>& executionContext) const
  {
    Arabica::XPath::XPathValuePtr<std::string> a1 = arg(0, context, executionContext);
    if(a1->type() != Arabica::XPath::NODE_SET)
      return load_document(a1->asString());

    throw Arabica::XPath::UnsupportedException("node-set arg version of document()");
  } // evaluate

private:
  Arabica::XPath::XPathValue<std::string>* load_document(const std::string& url) const
  {
    if(url.empty())
      throw Arabica::XPath::UnsupportedException("document('')");

    SAX2DOM::Parser<std::string> domParser;
    SAX::CatchErrorHandler<std::string> eh;
    domParser.setErrorHandler(eh);

    SAX::InputSource is(url);
    domParser.parse(is);

    Arabica::XPath::NodeSet<std::string> set;

    if(!eh.errorsReported())
        set.push_back(domParser.getDocument());
    else
        std::cerr << eh.errors() << std::endl;

    return new Arabica::XPath::NodeSetValue<std::string>(set);
  } // load_document
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

class XsltFunctionResolver : public Arabica::XPath::FunctionResolver<std::string>
{
public:
  virtual Arabica::XPath::XPathFunction<std::string>* resolveFunction(
                                         const std::string& namespace_uri, 
                                         const std::string& name,
                                         const std::vector<Arabica::XPath::XPathExpressionPtr<std::string> >& argExprs) const
  {
    if(!namespace_uri.empty())
      return 0;

    // document
    if(name == "document")
      return new DocumentFunction(argExprs);
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
}; // class XsltFunctionResolver


} // namespace XSLT
} // namespace Arabica

#endif // ARABICA_XSLT_FUNCTIONS_HPP


