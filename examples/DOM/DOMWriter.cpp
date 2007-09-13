// DOMWriter.cpp : Defines the entry point for the application.
//

#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include <string>
#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>
#include <DOM/io/Stream.hpp>

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if(argc < 2) 
  {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
    return 0;
  } // if(argc < 2)

  { // narrow
    Arabica::SAX2DOM::Parser<std::string> domParser;
    Arabica::SAX::CatchErrorHandler<std::string> eh;
    domParser.setErrorHandler(eh);

	  for(int i = 1; i < argc; ++i)
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
        doc.normalize();
        std::cout << doc;
     }
      else
      {
        std::cerr << eh.errors() << std::endl;
        eh.reset();
      } // if ...
    } // for ...

  } 

/*
  { // wide
    SAX2Arabica::DOM::Parser<std::wstring> domParser;

    Arabica::SAX::wInputSource is;
    is.setSystemId(L"stdin");
    is.setByteStream(std::cin);

    domParser.parse(is);

    Arabica::DOM::Document<std::wstring> doc = domParser.getDocument();

    std::wcout << doc;
  }
*/

  return 0;
} // main

// end of file
