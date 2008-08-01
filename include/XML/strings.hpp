#ifndef ARABICA_XML_STRINGS_HPP
#define ARABICA_XML_STRINGS_HPP

#include <XML/XMLCharacterClasses.hpp>
#include <text/UnicodeCharacters.hpp>

  // QName 
  //[7]  QName	   ::=   	PrefixedName | UnprefixedName
  //[8]  PrefixedName	   ::=   	Prefix ':' LocalPart
  //[9]  UnprefixedName	   ::=   	LocalPart
  //[10] Prefix	   ::=   	NCName
  //[11] LocalPart	   ::=   	NCName

  // NCName 
  // [4] NCName	   ::=   	NCNameStartChar NCNameChar*	//An XML Name, minus the ":"
  // [5] NCNameChar	   ::=   	NameChar - ':'
  // [6] NCNameStartChar	   ::=   	Letter | '_' } // namespace XML

namespace Arabica
{
namespace XML
{
  bool is_ncname(const std::string::const_iterator& b,
		 const std::string::const_iterator& e);

  inline bool is_ncname(const std::string& str)
  {
    return is_ncname(str.begin(), str.end());
  } // is_ncname

  inline bool is_ncname(const std::string::const_iterator& b,
			const std::string::const_iterator& e)
  {
    using namespace Arabica::text;

    if(b == e)
      return false;  // zero length

    std::string::const_iterator s = b;
    if(!(is_letter(*s) || (*s == Unicode<char>::LOW_LINE)))
       return false;

    ++s;
    for( ; s != e; ++s)
    {
      wchar_t c = static_cast<wchar_t>(*s);
      if(!is_ncname_char(c))
        return false;
    }
    return true;
  } // is_ncname  

  inline bool is_qname(const std::string& str)
  {
    using namespace Arabica::text;
   
    size_t colon_index = str.find(Unicode<char>::COLON);

    if(colon_index == std::string::npos)
      return is_ncname(str);

    std::string::const_iterator b = str.begin();
    return is_ncname(b, b+colon_index) && 
           is_ncname(b+(colon_index+1), str.end());
  } // is_qname

} // namespace XML
} // namespace Arabica


#endif
