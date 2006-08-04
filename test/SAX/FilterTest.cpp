#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <SAX/XMLReader.h>
#include <SAX/InputSource.h>
#include <SAX/filter/Writer.h>
#include <SAX/helpers/CatchErrorHandler.h>
#include <XML/XMLCharacterClasses.h>
#include <sstream>

template<class string_type, class string_adaptor>
string_type normalise_whitespace(const string_type& ch)
{
	std::string value = string_adaptor::asStdString(ch);

	return string_adaptor::construct_from_utf8(normalise_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(ch));
} // normalise_whitespace

template<>
std::string normalise_whitespace<std::string, Arabica::default_string_adaptor<std::string> >(const std::string& ch)
{
	std::string value(ch);
	std::string::const_iterator i = value.begin(), ie = value.end();
	std::string::iterator p = value.begin(), pe = value.end();

  // string leading space
	while((i != ie) && (Arabica::XML::is_space(static_cast<char>(*i))))
    ++i;
    
  while(i != ie)
  {
    while((i != ie) && (!Arabica::XML::is_space(static_cast<char>(*i)))) 
      *p++ = *i++;
    while((i != ie) && (Arabica::XML::is_space(static_cast<char>(*i))))
      ++i;
    if(i != ie)
      *p++ = Arabica::Unicode<char>::SPACE;
  } // while ...
  if(p != ie)
    *p++ = 0;

	return value;
} // normalise_whitespace

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class basic_WhitespaceStripper : public SAX::basic_XMLFilterImpl<string_type>
{
  public:
    typedef string_type stringT;
    typedef SAX::basic_XMLFilterImpl<stringT> XMLFilterT;

    basic_WhitespaceStripper() { }

    virtual void characters(const stringT& ch)
    {
      XMLFilterT::characters(normalise_whitespace<string_type, string_adaptor>(ch));
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
  SAX::Writer writer2(output2, 2);
  basic_WhitespaceStripper<std::string> stripper;
  SAX::Writer writer(output, 4);

  SAX::XMLReader<std::string> parser;
  SAX::CatchErrorHandler<std::string> eh;
  writer.setParent(parser);
  writer.setErrorHandler(eh);
  stripper.setParent(writer);
  writer2.setParent(stripper);
  writer2.setErrorHandler(eh);

  std::stringstream ss;
  ss << "<test><p>Woo                                                   </p><!-- yea --></test>";

  SAX::InputSource is(ss);

  writer2.parse(is);

  std::cout << "1: " << output.str() << std::endl;
  std::cout << "2: " << output2.str() << std::endl;

	
	return 0;
} // main

// end of file
