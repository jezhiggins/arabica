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
  template<typename string_adaptor>
  inline bool is_ncname(const typename string_adaptor::const_iterator& b,
                        const typename string_adaptor::const_iterator& e)
  {
    using namespace Arabica::text;
    typedef typename string_adaptor::const_iterator const_iterator;
    typedef typename string_adaptor::value_type value_type;

    if(b == e)
      return false;  // zero length

    const_iterator s = b;
    if(!(is_letter(*s) || (*s == Unicode<value_type>::LOW_LINE)))
       return false;

    ++s;
    for( ; s != e; ++s)
    {
      value_type c = *s;
      if(!is_ncname_char(c))
        return false;
    }
    return true;
  } // is_ncname  

  template<typename string_adaptor>
  inline bool is_ncname(const typename string_adaptor::string_type& str)
  {
    return is_ncname<string_adaptor>(string_adaptor::begin(str), 
                                     string_adaptor::end(str));
  } // is_ncname

  template<typename string_adaptor>
  inline bool is_qname(const typename string_adaptor::string_type& str)
  {
    using namespace Arabica::text;
    typedef typename string_adaptor::const_iterator const_iterator;
    typedef typename string_adaptor::value_type value_type;
   
    size_t colon_index = string_adaptor::find(str, Unicode<value_type>::COLON);

    if(colon_index == string_adaptor::npos())
      return is_ncname<string_adaptor>(str);

    const_iterator b = string_adaptor::begin(str);
    const_iterator e = string_adaptor::end(str);
    return is_ncname<string_adaptor>(b, b+colon_index) && 
           is_ncname<string_adaptor>(b+(colon_index+1), e);
  } // is_qname

} // namespace XML
} // namespace Arabica


#endif
