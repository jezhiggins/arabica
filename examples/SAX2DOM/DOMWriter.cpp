// DOMWriter.cpp : Defines the entry point for the application.
//

#ifdef _MSC_VER
#pragma warning(disable: 4786 4250 4503)
#endif

#include <string>
#include <DOM/SAX2DOM/SAX2DOM.h>
#include <SAX/helpers/CatchErrorHandler.h>
#include <DOM/Utils/Stream.h>

////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  if(argc < 2) 
  {
    std::cout << "Usage : " << argv[0] << " xmlfile ... " << std::endl;
    return 0;
  } // if(argc < 2)

  { // narrow
    SAX2DOM::Parser<std::string> domParser;
    SAX::CatchErrorHandler<std::string> eh;
    domParser.setErrorHandler(eh);

	  for(int i = 1; i < argc; ++i)
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
    SAX2DOM::Parser<std::wstring> domParser;

    SAX::wInputSource is;
    is.setSystemId(L"stdin");
    is.setByteStream(std::cin);

    domParser.parse(is);

    DOM::Document<std::wstring> doc = domParser.getDocument();

    std::wcout << doc;
  }
*/

  return 0;
} // main

// end of file
