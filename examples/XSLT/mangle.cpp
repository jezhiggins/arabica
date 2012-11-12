#ifdef _MSC_VER
#pragma warning(disable : 4250)
#endif

#include <iostream>
#include <string>
#include <sstream>

#include <SAX/InputSource.hpp>
#include <DOM/SAX2DOM/SAX2DOM.hpp>
#include <DOM/io/Stream.hpp>
#include <XSLT/XSLT.hpp>

Arabica::DOM::Document<std::wstring> buildDOM(const std::wstring& xml);
typedef Arabica::default_string_adaptor<std::wstring> adaptor;

int main(int argc, const char* argv[])
{

  if(argc != 3)
  {
    std::cout << "mangle is an (in-development) XSLT processor\n" 
              << argv[0] << " xmlfile xsltfile" << std::endl;
    return 0;
  } // if ...

  Arabica::XSLT::StylesheetCompiler<std::wstring> compiler;
  std::wostringstream errors;
  try 
  {
    Arabica::SAX::InputSource<std::wstring> source(adaptor::construct_from_utf8(argv[2]));
    std::auto_ptr<Arabica::XSLT::Stylesheet<std::wstring> > stylesheet = compiler.compile(source);
    if(stylesheet.get() == 0)
    {
      std::cerr << "Couldn't compile stylesheet: " << compiler.error() << std::endl;
      return -1;
    } // if ...

    stylesheet->set_error_output(errors);

    Arabica::DOM::Document<std::wstring> document = buildDOM(adaptor::construct_from_utf8(argv[1])); 
    if(document == 0)
    {
      std::cerr << "Could not parse XML source" << std::endl;
      return 0;
    } // if ...
    //document.normalize();
    stylesheet->execute(document);

/*
    std::cout << "\n==============" << std::endl;

    Arabica::XSLT::DOMSink output;
    stylesheet->set_output(output);

    stylesheet->execute(document);

    Arabica::DOM::Node<std::wstring> node = output.node();
    std::cout << node << std::endl;
*/
  }
  catch(const std::runtime_error& ex)
  {
    std::cerr << ex.what() << std::endl;
  } // catch

  std::wcerr << "\n\n" << errors.str() << std::endl;

  return 0;
} // main

Arabica::DOM::Document<std::wstring> buildDOM(const std::wstring& filename)
{
  Arabica::SAX::InputSource<std::wstring> is(filename);
  Arabica::SAX2DOM::Parser<std::wstring> parser;
  parser.parse(is);       

  return parser.getDocument();
} // buildDOM

