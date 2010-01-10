#ifdef _MSC_VER
#pragma warning(disable: 4250)
#endif

#include <iostream>
#include <SAX/filter/Writer.hpp>
#include <SAX/helpers/CatchErrorHandler.hpp>
#include <Taggle/Taggle.hpp>

int main(int argc, const char* argv[])
{
  if(argc == 1) 
  {
    std::cout << "taggle [file1] [file2] ... [filen]\n" 
              << "  taggle reads arbitrary HTML, outputting it as well-formed XML\n";
    return 0;
  } // if(argc == 1)

  Arabica::SAX::Taggle<std::string> parser;
  std::ostringstream sink;
  Arabica::SAX::Writer<std::string> writer(sink, 4);
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

    std::cout << sink.str();
  } // for ...
  
  return 0;
} // main 
