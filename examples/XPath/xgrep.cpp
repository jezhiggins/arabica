// DOMWriter.cpp : Defines the entry point for the application.
//

#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include <string>
#include <SAX/helpers/CatchErrorHandler.h>
#include <DOM/SAX2DOM/SAX2DOM.h>
#include <DOM/Utils/Stream.h>
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
  Arabica::XPath::XPathExpressionPtr<std::string> xpath = xpathParser.compile(argv[1]);
  
  SAX2DOM::Parser<std::string> domParser;
  SAX::CatchErrorHandler<std::string> eh;
  domParser.setErrorHandler(eh);

	for(int i = 2; i < argc; ++i)
  {
    std::string file(argv[i]);
    SAX::InputSource is;
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
      DOM::Document<std::string> doc = domParser.getDocument();
      Arabica::XPath::XPathValuePtr<std::string> result;
      result = xpath->evaluate(doc);
      if(result->asBool())
      {
        std::cout << file << std::endl;
        if(result->type() == Arabica::XPath::NODE_SET)
        {
          const Arabica::XPath::NodeSet<std::string>& ns = result->asNodeSet();
          for(unsigned int i = 0; i < ns.size(); ++i)
          {
            DOM::Element<std::string> n = static_cast<DOM::Element<std::string> >(ns[i]);
            std::cout << n << std::endl;
          }
        } // if ..
      } // if ...
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
