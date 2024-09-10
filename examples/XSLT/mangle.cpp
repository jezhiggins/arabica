#ifdef _MSC_VER
#pragma warning(disable : 4250 4244)
#endif

#include <iostream>
#include <string>
#include <sstream>

#include <XSLT/XSLT.hpp>

Arabica::DOM::Document<std::string> buildDOM(const std::string & xml);

int main(int argc, const char* argv[])
{

  if(argc != 3)
  {
    std::cout << "mangle is an (in-development) XSLT processor\n" 
              << argv[0] << " xmlfile xsltfile" << std::endl;
    return 0;
  } // if ...

  try
  {
    Arabica::SAX::InputSource<std::string> source(argv[2]);
    Arabica::XSLT::StylesheetCompiler<std::string> compiler;
    std::unique_ptr<Arabica::XSLT::Stylesheet<std::string> > stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
    {
      std::cerr << "Couldn't compile stylesheet: " << compiler.error() << std::endl;
      return -1;
    } // if ...

    stylesheet->set_error_output(std::cerr);

    Arabica::DOM::Document<std::string> document = buildDOM(argv[1]); 
    if(document == 0)
    {
      std::cerr << "Could not parse XML source" << std::endl;
      return 0;
    } // if ...
    stylesheet->execute(document);
  }
  catch(const std::runtime_error& ex)
  {
    std::cerr << ex.what() << std::endl;
  } // catch

  return 0;
} // main

Arabica::DOM::Document<std::string> buildDOM(const std::string & filename)
{
  Arabica::SAX::InputSource<std::string> is(filename);
  Arabica::SAX2DOM::Parser<std::string> parser;
  parser.parse(is);       

  return parser.getDocument();
} // buildDOM

