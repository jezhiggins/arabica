#ifndef ARABICA_UTILS_ESCAPER_HPP
#define ARABICA_UTILS_ESCAPER_HPP

#include <iostream>
#include <text/UnicodeCharacters.hpp>

namespace Arabica {
namespace XML {

template<typename char_type, typename traits_type = std::char_traits<char_type> >
class text_escaper
{
  private:
    typedef char_type charT;
    typedef traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef Arabica::text::Unicode<charT> UnicodeT;

  public:
    text_escaper(ostreamT& stream) : stream_(stream) { }
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

      stream_ << ch;
    } // operator()

  protected:
    ostreamT& stream_;
}; // text_escaper

template<typename char_type, typename traits_type = std::char_traits<char_type> >
class attribute_escaper : private text_escaper<char_type, traits_type>
{
  private:
    typedef char_type charT;
    typedef traits_type traitsT;
    typedef std::basic_ostream<charT, traitsT> ostreamT;
    typedef Arabica::text::Unicode<charT> UnicodeT;

public:
    attribute_escaper(ostreamT& stream) : text_escaper<char_type, traits_type>(stream) { }
    void operator()(charT ch)
    {
      if(ch == UnicodeT::QUOTATION_MARK)
      {
        this->stream_ << UnicodeT::AMPERSAND
                << UnicodeT::LOWERCASE_Q
                << UnicodeT::LOWERCASE_U
                << UnicodeT::LOWERCASE_O
                << UnicodeT::LOWERCASE_T
                << UnicodeT::SEMI_COLON;
        return;
      } // if(ch == UnicodeT::QUOTATION_MARK)
      if(ch == UnicodeT::HORIZONTAL_TABULATION)
      {
	this->stream_ << UnicodeT::AMPERSAND
		<< UnicodeT::NUMBER_SIGN
		<< UnicodeT::LOWERCASE_X
		<< UnicodeT::NUMBER_9
		<< UnicodeT::SEMI_COLON;
	return;
      } // if(ch == UnicodeT::HORIZONTAL_TABULATION)
      if(ch == UnicodeT::LINE_FEED)
      {
	this->stream_ << UnicodeT::AMPERSAND
		<< UnicodeT::NUMBER_SIGN
		<< UnicodeT::LOWERCASE_X
		<< UnicodeT::CAPITAL_A
		<< UnicodeT::SEMI_COLON;
	return;
      } // if(ch == UnicodeT::LINE_FEED)
      if(ch == UnicodeT::CARRIAGE_RETURN)
      {
	this->stream_ << UnicodeT::AMPERSAND
		<< UnicodeT::NUMBER_SIGN
		<< UnicodeT::LOWERCASE_X
		<< UnicodeT::CAPITAL_D
		<< UnicodeT::SEMI_COLON;
	return;
      } // if(ch == UnicodeT::CARRIAGE_RETURN)

      text_escaper<char_type, traits_type>::operator()(ch);
    } // operator()
}; // attribute_escaper

} // namespace XML
} // namespace Arabica
#endif // ARABICA_UTILS_ESCAPER_HPP

