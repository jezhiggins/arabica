#ifndef ARABICA_UTILS_ESCAPER_HPP
#define ARABICA_UTILS_ESCAPER_HPP

#include <iostream>
#include <XML/UnicodeCharacters.h>

namespace Arabica {
namespace XML {

template<typename char_type, typename traits_type = std::char_traits<char_type> >
class escaper
{
  private:
    typedef char_type charT;
    typedef traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef Arabica::Unicode<charT> UnicodeT;

  public:
    escaper(ostreamT& stream) : stream_(stream) { }
    void operator()(charT ch)
    {
	    if(ch == UnicodeT::LESS_THAN_SIGN)
	    {
        stream_ << UnicodeT::AMPERSAND
                << UnicodeT::LOWERCASE_L
                << UnicodeT::LOWERCASE_T
                << UnicodeT::SEMI_COLON;
        return;
      } // if(ch == UnicodeT::LESS_THAN_SIGN)
      if(ch == UnicodeT::GREATER_THAN_SIGN)
      {
        stream_ << UnicodeT::AMPERSAND
                << UnicodeT::LOWERCASE_G
                << UnicodeT::LOWERCASE_T
                << UnicodeT::SEMI_COLON;
        return;
	    } // if(ch == UnicodeT::GREATER_THAN_SIGN)
      if(ch == UnicodeT::AMPERSAND)
	    {
        stream_ << UnicodeT::AMPERSAND
                << UnicodeT::LOWERCASE_A
                << UnicodeT::LOWERCASE_M
                << UnicodeT::LOWERCASE_P
                << UnicodeT::SEMI_COLON;
	      return;
      } // if(ch == case UnicodeT::AMPERSAND)
      if(ch == UnicodeT::QUOTATION_MARK)
	    {
        stream_ << UnicodeT::AMPERSAND
                << UnicodeT::LOWERCASE_Q
                << UnicodeT::LOWERCASE_U
                << UnicodeT::LOWERCASE_O
                << UnicodeT::LOWERCASE_T
                << UnicodeT::SEMI_COLON;
        return;
	    } // if(ch == UnicodeT::QUOTATION_MARK)

      stream_ << ch;
    } // operator()

  private:
    ostreamT& stream_;
}; // escaper

} // namespace XML
} // namespace Arabica
#endif // ARABICA_UTILS_ESCAPER_HPP

