#pragma hdrstop
#ifdef __BORLANDC__
#include <condefs.h>
#endif

#pragma warning(disable:4786)


#include "SimpleHandler.h"
#include <SAX/InputSource.h>
#include <iostream>
#include <sstream>

SAX::basic_XMLReader<std::string>* parserFactory(std::string name)
{
#ifdef USE_EXPAT
  if(name == "expat")
    return new SAX::expat_wrapper<std::string>;
#endif
#ifdef USE_GARDEN
  if(name == "garden")
    return new SAX::Garden;
#endif
#ifdef USE_MSXML
  if(name == "msxml")
    return new SAX::msxml2_wrapper<std::string>;
#endif
#ifdef USE_LIBXML2
  if(name == "libxml")
    return new SAX::libxml2_wrapper<std::string>;
#endif
#ifdef USE_XERCES
  if(name == "xerces")
    return new SAX::xerces_wrapper<std::string>;
#endif
  std::cout << "unknown parser -> " << name << std::endl;
  exit(0);
} 

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if(argc < 3) 
  {
    std::cout << "Usage : " << argv[0] << " parser_name xmlfile ... " << std::endl;
    return 0;
  } // if(argc == 0)

	SimpleHandler myHandler;
  SAX::FeatureNames<std::string> fNames;
  SAX::PropertyNames<std::string> pNames;

	for(int i = 2; i < argc; ++i)
  {
    std::auto_ptr<SAX::basic_XMLReader<std::string> > parser(parserFactory(argv[1]));

    try 
    {
      parser->setFeature(fNames.external_general, true);
      parser->setFeature(fNames.validation, true);
      parser->setFeature(fNames.namespaces, true);
      parser->setFeature(fNames.namespace_prefixes, true);
    }
    catch(SAX::SAXException& e) 
    { 
      std::cerr << e.what() << std::endl;
    }

    parser->setContentHandler(myHandler);
    parser->setDTDHandler(myHandler); 
    parser->setErrorHandler(myHandler);
    parser->setEntityResolver(myHandler);

    try 
    {
      parser->setProperty(pNames.declHandler, static_cast<SAX::DeclHandler&>(myHandler));
      parser->setProperty(pNames.lexicalHandler, static_cast<SAX::LexicalHandler&>(myHandler));
    }
    catch(SAX::SAXException& e)
    {
      std::cout << e.what() << std::endl;
    } // catch

    std::string file(argv[i]);

    if(file != "-")
      parser->parse(file);
    else
    {
      SAX::InputSource is;
      is.setSystemId("stdin");
      is.setByteStream(std::cin);

      parser->parse(is);
    } // 
  }

  
  return 0;
} // main

// end of file
