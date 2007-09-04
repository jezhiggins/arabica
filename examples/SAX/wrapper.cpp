#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include "SimpleHandler.hpp"
#include <SAX/InputSource.hpp>
#include <SAX/helpers/FeatureNames.hpp>
#include <SAX/helpers/PropertyNames.hpp>
#include <iostream>
#include <sstream>

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if(argc < 2) 
  {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
    return 0;
  } // if(argc == 0)

  SimpleHandler myHandler;
  SAX::FeatureNames<std::string> fNames;
  SAX::PropertyNames<std::string> pNames;

  for(int i = 1; i < argc; ++i)
  {
    SAX::XMLReader<std::string> parser;

    try 
    {
      parser.setFeature(fNames.external_general, true);
      parser.setFeature(fNames.validation, true);
      parser.setFeature(fNames.namespaces, true);
      parser.setFeature(fNames.namespace_prefixes, true);
    }
    catch(SAX::SAXException& e) 
    { 
      std::cerr << e.what() << std::endl;
    }

    parser.setContentHandler(myHandler);
    parser.setDTDHandler(myHandler); 
    parser.setErrorHandler(myHandler);
    parser.setEntityResolver(myHandler);
    parser.setDeclHandler(myHandler);
    parser.setLexicalHandler(myHandler);

    std::string file(argv[i]);

    if(file != "-")
    {
      SAX::InputSource is(file); 
      parser.parse(is);
    }
    else
    {
      SAX::InputSource is;
      is.setSystemId("stdin");
      is.setByteStream(std::cin);

      parser.parse(is);
    } // 
  }

  
  return 0;
} // main

// end of file
