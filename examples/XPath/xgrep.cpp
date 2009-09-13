#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include <string>
#include <SAX/helpers/CatchErrorHandler.hpp>
#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <DOM/io/Stream.hpp>
#include <XPath/XPath.hpp>

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if(argc < 3) 
  {
    std::cout << "Usage : " << argv[0] << " xpath xmlfile ... " << std::endl;
    return 0;
  } // if(argc < 3)

  Arabica::XPath::XPath<std::string> xpathParser;
  Arabica::XPath::XPathExpressionPtr<std::string> xpath;
  try {
    //xpath = xpathParser.compile(argv[1]);
    xpath = xpathParser.compile_expr(argv[1]);
  }
  catch(const std::runtime_error& error) {
    std::cout << "XPath compilation error: " << error.what() << std::endl;
    return 0;
  }
  
  
  Arabica::SAX2DOM::Parser<std::string> domParser;
  Arabica::SAX::CatchErrorHandler<std::string> eh;
  domParser.setErrorHandler(eh);

	for(int i = 2; i < argc; ++i)
  {
    std::string file(argv[i]);
    Arabica::SAX::InputSource<std::string> is;
    is.setSystemId(file);

    if(file != "-")
      domParser.parse(is);
    else
    {
      is.setSystemId("stdin");
      is.setByteStream(std::cin);

      domParser.parse(is);
    } // if(file != "-")

    if(!eh.errorsReported())
    {
      Arabica::DOM::Document<std::string> doc = domParser.getDocument();
 //     doc.normalize();
      Arabica::XPath::XPathValuePtr<std::string> result;
      result = xpath->evaluate(doc);

      std::cout << file << std::endl;
      switch(result->type())
      {
        case Arabica::XPath::NODE_SET:
          {
            const Arabica::XPath::NodeSet<std::string>& ns = result->asNodeSet();
            for(unsigned int i = 0; i < ns.size(); ++i)
            {
              Arabica::DOM::Node<std::string> n = ns[i];
              std::cout << n << std::endl;
            }
          } 
          break;
        default:
          std::cout << result->asString() << std::endl;
      } // switch
    }
    else
    {
      std::cerr << eh.errors() << std::endl;
      eh.reset();
    } // if ...
  } // for ...

  return 0;
} // main

// end of file
