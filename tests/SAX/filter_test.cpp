#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <SAX/XMLReader.h>
#include <SAX/InputSource.h>
#include <SAX/filter/Writer.h>
#include <SAX/helpers/CatchErrorHandler.h>
#include <XML/XMLCharacterClasses.h>
#include <sstream>

#include <Utils/normalize_whitespace.hpp>

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class basic_WhitespaceStripper : public SAX::basic_XMLFilterImpl<string_type>
{
  public:
    typedef string_type stringT;
    typedef SAX::basic_XMLFilterImpl<stringT> baseT;

    basic_WhitespaceStripper() { }

    virtual void characters(const stringT& ch)
    { 
      baseT::characters(Arabica::string::normalize_whitespace<string_type, string_adaptor>(ch));
    } // characters

    virtual void ignorableWhitespace(const stringT& ch)
    {
    } // ignorableWhitespace
}; // class basic_WhitespaceStripper


int main(int argc, char* argv[])
{
  std::cout << "tests go here" << std::endl;

  std::ostringstream output;
  std::ostringstream output2;
  SAX::Writer writer2(output2, 0);
  basic_WhitespaceStripper<std::string> stripper;
  SAX::Writer writer(output, 2);

  SAX::XMLReader<std::string> parser;
  SAX::CatchErrorHandler<std::string> eh;
  writer.setParent(parser);
  writer.setErrorHandler(eh);
  stripper.setParent(writer);
  writer2.setParent(stripper);
  writer2.setErrorHandler(eh);

  std::stringstream ss;
  ss << "<test><p>   Woo baby    hooray                                           </p><!-- yea --></test>";

  SAX::InputSource is(ss);

  writer2.parse(is);

  std::cout << "1: " << output.str() << std::endl;
  std::cout << "2: " << output2.str() << std::endl;

  
  return 5;
} // main

// end of file
