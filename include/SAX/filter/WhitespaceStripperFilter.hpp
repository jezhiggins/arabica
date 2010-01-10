#ifndef WHITESPACE_STRIPPER_FILTER_HPP
#define WHITESPACE_STRIPPER_FILTER_HPP

#include <SAX/helpers/XMLFilterImpl.hpp>

#include <text/normalize_whitespace.hpp>

namespace Arabica
{
namespace SAX
{

template<class string_type, class string_adaptor = Arabica::default_string_adaptor<string_type> >
class WhitespaceStripper : public SAX::XMLFilterImpl<string_type, string_adaptor>
{
  public:
    typedef SAX::XMLReaderInterface<string_type, string_adaptor> XMLReaderT;
    typedef SAX::XMLFilterImpl<string_type, string_adaptor> XMLFilterT;

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

    virtual void ignorableWhitespace(const string_type& /* ch */)
    {
    } // ignorableWhitespace
}; // class WhitespaceStripper

} // namespace SAX
} // namespace Arabica

#endif
// end of file
