#ifdef _MSC_VER
#  pragma warning(disable:4786)
#endif

#include <SAX/XMLReader.h>
#include <SAX/helpers/FeatureNames.h>
#include <SAX/InputSource.h>
#include <iostream>
#include <SAX/filter/Writer.h>

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if(argc < 2) 
  {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
    return 0;
  } // if(argc < 2)


  SAX::FeatureNames<std::string> fNames;
  SAX::XMLReader<std::string> parser;
  SAX::Writer writer(std::cout);
  writer.setParent(parser);

	for(int i = 1; i < argc; ++i)
  {
    std::string file(argv[i]);
    SAX::InputSource is;
    is.setSystemId(file);

    if(file != "-")
      writer.parse(is);
    else
    {
      is.setSystemId("stdin");
      is.setByteStream(std::cin);

      writer.parse(is);
    } // if(file != "-")
  } // for ...

  
  return 0;
} // main

// end of file
