#ifndef WHITESPACE_STRIPPER_FILTER_HPP
#define WHITESPACE_STRIPPER_FILTER_HPP

#include <SAX/helpers/XMLFilterImpl.hpp>

#include <Utils/normalize_whitespace.hpp>

namespace Arabica
{
namespace SAX
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class WhitespaceStripper : public SAX::XMLFilterImpl<string_type>
{
  public:
    typedef string_type stringT;
    typedef SAX::XMLFilterImpl<stringT> baseT;
    typedef SAX::XMLReader<stringT> XMLReaderT;

    WhitespaceStripper() : 
      baseT() 
    { 
    } // WhitespaceStripper

    WhitespaceStripper(XMLReaderT& parent) :
      baseT(parent)
    {
    } // WhitespaceStripper    

    virtual void characters(const stringT& ch)
    { 
      baseT::characters(Arabica::string::normalize_whitespace<string_type, string_adaptor>(ch));
    } // characters

    virtual void ignorableWhitespace(const stringT& ch)
    {
    } // ignorableWhitespace
}; // class WhitespaceStripper

} // namespace SAX
} // namespace Arabica

#endif
// end of file
