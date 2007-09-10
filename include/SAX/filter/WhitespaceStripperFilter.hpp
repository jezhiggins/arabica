#ifndef WHITESPACE_STRIPPER_FILTER_HPP
#define WHITESPACE_STRIPPER_FILTER_HPP

#include <SAX/helpers/XMLFilterImpl.hpp>

#include <text/normalize_whitespace.hpp>

namespace Arabica
{
namespace SAX
{

template<class string_type, class T0 = Arabica::nil_t, class T1 = Arabica::nil_t>
class WhitespaceStripper : public SAX::XMLFilterImpl<string_type, T0, T1>
{
  public:
    typedef SAX::XMLReader<string_type, T0, T1> XMLReaderT;
    typedef SAX::XMLFilterImpl<string_type, T0, T1> XMLFilterT;
    typedef typename XMLFilterT::string_adaptor string_adaptor;

    WhitespaceStripper() : 
      XMLFilterT() 
    { 
    } // WhitespaceStripper

    WhitespaceStripper(XMLReaderT& parent) :
      XMLFilterT(parent)
    {
    } // WhitespaceStripper    

    virtual void characters(const string_type& ch)
    { 
      XMLFilterT::characters(Arabica::text::normalize_whitespace<string_type, string_adaptor>(ch));
    } // characters

    virtual void ignorableWhitespace(const string_type& ch)
    {
    } // ignorableWhitespace
}; // class WhitespaceStripper

} // namespace SAX
} // namespace Arabica

#endif
// end of file
