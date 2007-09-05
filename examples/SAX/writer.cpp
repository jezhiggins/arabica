#ifdef _MSC_VER
#  pragma warning(disable:4786)
#endif

#include <SAX/XMLReader.hpp>
#include <SAX/helpers/FeatureNames.hpp>
#include <SAX/InputSource.hpp>
#include <iostream>
#include <SAX/filter/Writer.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if(argc < 2) 
  {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
    return 0;
  } // if(argc < 2)

  { // narrow
    Arabica::SAX::FeatureNames<std::string> fNames;
    Arabica::SAX::XMLReader<std::string> parser;
    Arabica::SAX::Writer<std::string> writer(std::cout, 4);
    Arabica::SAX::CatchErrorHandler<std::string> eh;

    writer.setParent(parser);
    writer.setErrorHandler(eh);

  	for(int i = 1; i < argc; ++i)
    {
      std::string file(argv[i]);
      Arabica::SAX::InputSource<std::string> is;
      is.setSystemId(file);

      if(file != "-")
        writer.parse(is);
      else
      { 
        is.setSystemId("stdin");
        is.setByteStream(std::cin);

        writer.parse(is);
      } // if(file != "-")

      if(eh.errorsReported())
      {
        std::cerr << eh.errors() << std::endl;
        eh.reset();
      } // if ...
    } // for ...
  }

  return 0;
} // main

// end of file
